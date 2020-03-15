#include "../aimbot/aimbot.hpp"

bool _aimbot::is_key_down()
{
	switch (aim_key) {
		case 0: { return (GetAsyncKeyState(VK_LSHIFT) & 0x8000); }
		case 1: { return (GetAsyncKeyState(VK_LBUTTON) & 0x8000); }
		case 2: { return true; }
	}
}

void _aimbot::set_angles(sdk::userCmd *cmd, math::vec3 &angles)
{
	math::clamp_angles(angles);

	if (silent) {
		utils::fix_silent(cmd, angles);
		cmd->viewangles = angles;
	}

	else {
		cmd->viewangles = angles;
		sdk::ifaces::engine->set_view_angles(cmd->viewangles);
	}
}

bool _aimbot::should_autoshoot(sdk::baseEntity *local, sdk::baseCombatWeapon *wep, math::vec3 &aim_pos)
{
	if (!autoshoot)
		return false;

	int wep_slot = wep->get_slot();
	int wep_idx = wep->get_definition_index();

	if (wep_slot < 2)
	{
		switch (local->get_class_num())
		{
			case sdk::sniper: {
				if (wep_slot == 0 && (autoshoot == 2 && !local->is_scoped()) || (local->is_scoped() && !global_info.sniper_can_headshot))
					return false;

				return true;
			}

			case sdk::spy: {
				if ((wep_idx == sdk::spy_p_TheAmbassador || wep_idx == sdk::spy_p_FestiveAmbassador) && !global_info.spy_can_headshot)
					return false;

				return true;
			}

			default: return true;
		}
	}

	else if (wep_slot == 2)
		return (utils::get_distance(local->get_shoot_pos(), aim_pos) < wep->get_swing_range(local)); //quite inaccurate but it does the job

	return false;
}

int _aimbot::get_best_hitbox(sdk::baseEntity *local, sdk::baseCombatWeapon *wep)
{
	int wep_slot = wep->get_slot();
	int wep_idx = wep->get_definition_index();

	switch (local->get_class_num())
	{
		case sdk::sniper: {
			if (wep_slot == 0)
				return sdk::hitbox_head;
		}

		case sdk::spy: {
			if (wep_idx == sdk::spy_p_TheAmbassador || wep_idx == sdk::spy_p_FestiveAmbassador)
				return sdk::hitbox_head;
		}

		default: return sdk::hitbox_pelvis;
	}
}

_aimbot::aimTarget _aimbot::get_target(sdk::baseEntity *local, sdk::baseCombatWeapon *wep, sdk::userCmd *cmd)
{
	math::vec3 local_pos = local->get_shoot_pos();
	math::vec3 local_angs = cmd->viewangles;
	aimTarget out = {};
	float best_fov = FLT_MAX;

	for (int n = ent_list_start; n < max_players; n++)
	{
		sdk::baseEntity *ent = get_ent(n);

		if (!ent
			|| !ent->is_player()
			|| ent == local
			|| !ent->is_alive()
			|| ent->is_dormant()
			|| !ent->is_vulnerable()
			|| ent->get_team_num() == local->get_team_num())
			continue;

		math::vec3 ent_pos		= ent->get_hitbox_pos(aim_hitbox == -1 ? get_best_hitbox(local, wep) : aim_hitbox);
		math::vec3 ang_to_ent	= math::calc_angle(local_pos, ent_pos);
		float fov_to_ent		= math::calc_fov(local_angs, ang_to_ent);

		if (fov_to_ent > aim_fov)
			continue;

		if (fov_to_ent < best_fov) {
			best_fov = fov_to_ent;
			out = { ent, ent_pos, ang_to_ent, local_pos };
		}
	}

	return out;
}

bool _aimbot::try_multipoint(sdk::baseEntity *local, aimTarget &target)
{
	if (multipoint <= 0.5f)
		return false;

	DWORD *model = target.ptr->get_model();
	if (!model)
		return false;

	sdk::studioHdr *hdr = reinterpret_cast<sdk::studioHdr*>(sdk::ifaces::model_info->get_studio_model(model));
	if (!hdr)
		return false;

	math::matrix3x4 bone_matrix[128];
	if (!target.ptr->setup_bones(bone_matrix, 128, 0x100, sdk::ifaces::globals->curtime))
		return false;

	sdk::studioHitboxSet *set = hdr->get_hitbox_set(target.ptr->get_hitbox_set());
	if (!set)
		return false;

	sdk::studioBbox *box = set->hitbox(sdk::hitbox_head);
	if (!box)
		return false;

	math::vec3 bbmax = (box->bbmax * multipoint);
	math::vec3 bbmin = (box->bbmin * multipoint);

	math::vec3 points[8] = {
		math::vec3(bbmax.x, bbmin.y, bbmax.z),
		math::vec3(bbmin.x, bbmin.y, bbmax.z),
		math::vec3(bbmin.x, bbmax.y, bbmax.z),
		math::vec3(bbmax.x, bbmax.y, bbmax.z),
		math::vec3(bbmax.x, bbmin.y, bbmin.z),
		math::vec3(bbmax.x, bbmax.y, bbmin.z),
		math::vec3(bbmin.x, bbmax.y, bbmin.z),
		math::vec3(bbmin.x, bbmin.y, bbmin.z)
	};

	math::vec3 out[8] = { math::vec3() };

	for (int n = 0; n < 8; n++) {
		math::vector_transform(points[n], bone_matrix[box->bone], out[n]);

		if (utils::vis_pos_id(local, target.ptr, out[n], sdk::hitbox_head)) {
			target.pos = out[n];
			return true;
		}
	}

	return false;
}

bool _aimbot::try_hitscan(sdk::baseEntity *local, aimTarget &target)
{
	if (!hitscan)
		return false;

	for (int n = 1; n < target.ptr->get_num_of_hitboxes(); n++) //skip the head
	{
		math::vec3 v = target.ptr->get_hitbox_pos(n);

		if (utils::vis_pos(local, target.ptr, v)) {
			target.pos = v;
			return true;
		}
	}

	return false;
}

void _aimbot::run(sdk::baseEntity *local, sdk::userCmd *cmd)
{
	cur_target_idx = -1;

	if (active && local->is_alive() && !local->is_taunting())
	{
		sdk::baseCombatWeapon *local_wep = local->get_active_weapon();

		if (local_wep)
		{
			if (no_melee && local_wep->get_slot() > 1)
				return;
			
			aimTarget target = get_target(local, local_wep, cmd);

			if (target.ptr)
			{
				int cur_hitbox = (aim_hitbox == -1 ? get_best_hitbox(local, local_wep) : aim_hitbox);
				int vis_hitbox_out = -1;

				if (!utils::vis_pos_id_out(local, target.ptr, target.pos, vis_hitbox_out) || cur_hitbox == sdk::hitbox_head && vis_hitbox_out != cur_hitbox) {
					if (cur_hitbox == sdk::hitbox_head && !try_multipoint(local, target))
						return;

					else if (cur_hitbox == sdk::hitbox_pelvis && !try_hitscan(local, target))
						return;

					target.ang = math::calc_angle(target.local_pos, target.pos); //recalculate because the target pos has changed
				}

				if (is_key_down()) {
					cur_target_idx = target.ptr->get_index();

					set_angles(cmd, target.ang);

					if (should_autoshoot(local, local_wep, target.pos))
						cmd->buttons |= sdk::in_attack;
				}
			}
		}
	}
}

_aimbot aimbot;
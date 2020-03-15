#pragma once
#include "../esp/esp.hpp"

bool _esp::get_ent_bounds(sdk::baseEntity *ent, float &x, float &y, float &w, float &h)
{
	const math::matrix3x4 &transform = ent->get_rgfl_coordinate_frame();

	math::vec3 mins = math::vec3();
	math::vec3 maxs = math::vec3();

	switch (ent->get_class_id())
	{
		case sdk::CTFPlayer: {
			mins = sdk::ifaces::game_movement->get_player_mins(ent->is_ducking());
			maxs = sdk::ifaces::game_movement->get_player_maxs(ent->is_ducking());
			break;
		}

		default: {
			mins = ent->get_collideable_mins();
			maxs = ent->get_collideable_maxs();
			break;
		}
	}

	math::vec3 points[] = {
		math::vec3(mins.x, mins.y, mins.z),
		math::vec3(mins.x, maxs.y, mins.z),
		math::vec3(maxs.x, maxs.y, mins.z),
		math::vec3(maxs.x, mins.y, mins.z),
		math::vec3(maxs.x, maxs.y, maxs.z),
		math::vec3(mins.x, maxs.y, maxs.z),
		math::vec3(mins.x, mins.y, maxs.z),
		math::vec3(maxs.x, mins.y, maxs.z)
	};

	math::vec3 transformed_points[8];
	
	for (int i = 0; i < 8; i++)
		math::vector_transform(points[i], transform, transformed_points[i]);

	math::vec3 ent_pos = ent->get_abs_origin();
	math::vec3 flb, brt, blb, frt, frb, brb, blt, flt;

	if (math::world_to_screen(transformed_points[3], flb) && math::world_to_screen(transformed_points[5], brt)
		&& math::world_to_screen(transformed_points[0], blb) && math::world_to_screen(transformed_points[4], frt)
		&& math::world_to_screen(transformed_points[2], frb) && math::world_to_screen(transformed_points[1], brb)
		&& math::world_to_screen(transformed_points[6], blt) && math::world_to_screen(transformed_points[7], flt)
		&& math::world_to_screen(transformed_points[6], blt) && math::world_to_screen(transformed_points[7], flt)) {
		math::vec3 arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left		= flb.x;
		float top		= flb.y;
		float righ		= flb.x;
		float bottom	= flb.y;

		for (int n = 1; n < 8; n++) {
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		x = left;
		y = bottom;
		w = (righ - left);
		h = (top - bottom);

		if (ent->is_player()) {
			x += ((righ - left) / 8.0f);
			w -= (((righ - left) / 8.0f) * 2.0f);
		}

		return true;
	}

	return false;
}

void _esp::run(sdk::baseEntity *local)
{
	static surfaceWrapper draw = surfaceWrapper("Monsterrat", font_tall, 50, sdk::fontFlags::fontflag_outline);

	if (!active || !sdk::ifaces::engine->is_in_game() || !sdk::ifaces::engine->is_connected())
		return;

	if (spectators && local->is_alive())
	{
		int count = 0;

		for (int n = ent_list_start; n < max_players; n++)
		{
			sdk::baseEntity *ent = get_ent(n);

			if (ent == nullptr || ent->is_alive())
				continue;

			sdk::playerInfo info;

			if (!sdk::ifaces::engine->get_player_info(ent->get_index(), &info))
				continue;

			sdk::baseEntity *observer_target = sdk::ifaces::entity_list->get_client_entity_from_handle(ent->get_observer_target());

			if (observer_target == nullptr || observer_target != local || !observer_target->is_alive())
				continue;

			int observer_mode = ent->get_observer_mode();

			if (observer_mode == sdk::obs_mode_firstperson || observer_mode == sdk::obs_mode_thirdperson)
				draw.string((screen_size.w / 5), (count++ * font_tall), col_white, info.name);
		}
	}

	entities.clear();

	for (int n = ent_list_start; n < ent_list_end; n++)
	{
		sdk::baseEntity *ent = get_ent(n);

		if (ent == nullptr
			|| ent == local
			|| !ent->is_player() && !ent->is_building() && !ent->is_pickup()
			|| ent->is_dormant())
			continue;

		float dist_to_ent = local->get_abs_origin().dist_to(ent->get_abs_origin());

		if (ent->is_player()) {
			if (!ent->is_alive() || no_teammate_players && ent->get_team_num() == local->get_team_num())
				continue;

			color clr = (no_teammate_players ? col_enemy : utils::get_team_color(ent->get_team_num()));

			if (!ent->is_vulnerable())
				clr = col_invuln;

			else if (ent->get_index() == aimbot.cur_target_idx)
				clr = col_target;

			entities.push_back({ ent, dist_to_ent, espEntType::player, clr });
		}

		else if (ent->is_building()) {
			if (!ent->is_alive() || no_teammate_buildings && ent->get_team_num() == local->get_team_num())
				continue;

			entities.push_back({ ent, dist_to_ent, espEntType::building, (no_teammate_buildings ? col_enemy : utils::get_team_color(ent->get_team_num())) });
		}

		else if (ent->is_pickup())
			entities.push_back({ ent, dist_to_ent, espEntType::pickup, col_white });
	}

	if (entities.empty())
		return;

	std::sort(entities.begin(), entities.end(), [&](const espEntity &a, const espEntity &b) -> bool {
		return (a.dist_to_ent > b.dist_to_ent);
	});

	for (auto &v : entities)
	{
		float x_flt = 0.0f, y_flt = 0.0f, w_flt = 0.0f, h_flt = 0.0f;

		if (!get_ent_bounds(v.ptr, x_flt, y_flt, w_flt, h_flt))
			continue;

		int x = static_cast<int>(x_flt);
		int y = static_cast<int>(y_flt);
		int w = static_cast<int>(w_flt);
		int h = static_cast<int>(h_flt);

		if (x > screen_size.w || (x + w) < 0 || y > screen_size.h || (y + h) < 0)
			continue;

		switch (v.type)
		{
			case espEntType::player:
			{
				if (!players)
					continue;

				float text_offset = 0.0f;

				if (player_name) {
					sdk::playerInfo info;
					sdk::ifaces::engine->get_player_info(v.ptr->get_index(), &info);

					draw.string(((x + w) + draw_offset), (y + text_offset), v.draw_col, info.name);
					text_offset += font_tall;
				}

				if (player_health) {
					float hp = v.ptr->get_health();
					float max_hp = v.ptr->get_max_health();

					if (hp > max_hp)
						hp = max_hp;

					float p	= ((1.0f - hp / max_hp) / 2.0f);

					color hp_col = utils::get_health_color(hp, max_hp);

					draw.rect(x - 1, ((y + h) + hpbar_offset - 1), (w + 2), (hpbar_h + 2), col_outline);
					draw.rect((x + w * p), ((y + h) + hpbar_offset), (w - w * p * 2), hpbar_h, hp_col);
				}

				if (player_class) {
					draw.string(((x + w) + draw_offset), (y + text_offset), v.draw_col, v.ptr->get_class_string());
					text_offset += font_tall;
				}

				if (player_cond) {
					std::string cond_str;

					if (v.ptr->is_ubered())
						cond_str += "UBERED | ";

					if (v.ptr->is_bonked())
						cond_str += "BONKED | ";

					if (v.ptr->is_crit_boosted())
						cond_str += "KRITZED | ";

					if (v.ptr->is_cloaked())
						cond_str += "CLOAKED | ";

					if (v.ptr->is_scoped())
						cond_str += "SCOPED | ";

					if (v.ptr->is_taunting())
						cond_str += "TAUNTING | ";

					if (cond_str.size() > 0)
						cond_str.erase((cond_str.end() - 3), (cond_str.end() - 1));

					int str_w = 0, str_h = 0;
					sdk::ifaces::surface->get_text_size(draw.font, utils::to_wchar(cond_str.c_str()).c_str(), str_w, str_h);

					draw.string((x + (w / 2) - (str_w / 2)), (y - font_tall), col_white, cond_str.c_str());
				}

				if (player_rect) {
					draw.outline_rect(x, y, w, h, v.draw_col);
					draw.outline_rect((x - 1), (y - 1), (w + 2), (h + 2), col_outline);
				}

				break;
			}

			case espEntType::building:
			{
				if (!buildings)
					continue;

				float text_offset = 0.0f;

				if (building_name) {
					std::string name_str = "";

					switch (v.ptr->get_class_id())
					{
						case sdk::CObjectSentrygun: {
							name_str = "sentrygun";
							break;
						}

						case sdk::CObjectDispenser: {
							name_str = "dispenser";
							break;
						}

						case sdk::CObjectTeleporter: {
							name_str = "teleporter";
							break;
						}
					}

					draw.string(((x + w) + draw_offset), (y + text_offset), v.draw_col, name_str.c_str());
					text_offset += font_tall;
				}

				if (building_level) {
					std::string level_str = ("level " + std::to_string(reinterpret_cast<sdk::baseObject*>(v.ptr)->get_level()));

					draw.string(((x + w) + draw_offset), (y + text_offset), v.draw_col, level_str.c_str());
					text_offset += font_tall;
				}

				if (building_health) {
					sdk::baseObject *obj = reinterpret_cast<sdk::baseObject*>(v.ptr);

					float hp = obj->get_health();
					float max_hp = obj->get_max_health();

					if (hp > max_hp)
						hp = max_hp;

					float p = ((1.0f - hp / max_hp) / 2.0f);

					color hp_col = utils::get_health_color(hp, max_hp);

					draw.rect(x - 1, ((y + h) + hpbar_offset - 1), (w + 2), (hpbar_h + 2), col_outline);
					draw.rect((x + w * p), ((y + h) + hpbar_offset), (w - w * p * 2), hpbar_h, hp_col);
				}

				if (building_rect) {
					draw.outline_rect(x, y, w, h, v.draw_col);
					draw.outline_rect((x - 1), (y - 1), (w + 2), (h + 2), col_outline);
				}

				break;
			}

			case espEntType::pickup:
			{
				if (!pickups)
					continue;

				if (pickup_name)
				{
					const char *model_name = v.ptr->get_model_name();

					std::string name_str = "";

					if (model_name[13] == 'm' && model_name[20] == 's'
						|| model_name[33] == 'm' && model_name[40] == 's')
						name_str = "health";		//"small medkit"

					else if (model_name[13] == 'm' && model_name[20] == 'm'
						|| model_name[33] == 'm' && model_name[40] == 'm')
						name_str = "health";		//"medium medkit"

					else if (model_name[13] == 'm' && model_name[20] == 'l'
						|| model_name[33] == 'm' && model_name[40] == 'l')
						name_str = "health";		//"large medkit"

					else if (model_name[13] == 'p' && model_name[16] == 't'
						|| model_name[24] == 's' && model_name[28] == 'w')
						name_str = "sandwich";		//"sandwich"

					else if (model_name[13] == 'a' && model_name[22] == 's')
						name_str = "ammo";			//"small ammo"

					else if (model_name[13] == 'a' && model_name[22] == 'm')
						name_str = "ammo";			//"medium ammo"

					else if (model_name[13] == 'a' && model_name[22] == 'l')
						name_str = "ammo";			//"large ammo"

					if (!name_str.empty()) {
						int str_w = 0, str_h = 0;
						sdk::ifaces::surface->get_text_size(draw.font, utils::to_wchar(name_str.c_str()).c_str(), str_w, str_h);
						draw.string((x + (w / 2) - (str_w / 2)), (y + (h / 2) - (str_h / 2)), v.draw_col, name_str.c_str());
					}
				}

				break;
			}
		}
	}
}

void _esp::run_glow(sdk::baseEntity *local, sdk::clientFrameStage frame)
{
	bool glow_players = (active && players && player_glow && !sdk::ifaces::engine->is_console_visible());
	bool glow_buildings = (active && buildings && building_glow && !sdk::ifaces::engine->is_console_visible());

	if (frame == sdk::frame_net_update_postdataupdate_start)
	{
		for (int n = ent_list_start; n < ent_list_end; n++) {
			sdk::baseEntity *ent = get_ent(n);

			if (ent == nullptr || ent == local || !ent->is_player() && !ent->is_building())
				continue;

			if (ent->is_player()) {
				if (!ent->has_glow_effect())
					ent->register_glow_object(col_white, true, true);

				ent->set_glow_enabled(glow_players && ent->is_alive() && !ent->is_dormant());
			}

			else if (ent->is_building()) {
				if (!ent->has_glow_effect())
					ent->register_glow_object(col_white, true, true);

				ent->set_glow_enabled(glow_buildings && ent->is_alive() && !ent->is_dormant());
			}

			ent->update_glow_effect();
		}
	}

	else if (frame == sdk::frame_render_start)
	{
		for (int n = 0; n < sdk::ifaces::glow_object->glow_objects.Count(); n++) {
			sdk::glowObjectDefinition &object = sdk::ifaces::glow_object->glow_objects[n];

			if (object.next_free_slot != sdk::ENTRY_IN_USE)
				continue;

			sdk::baseEntity *ent = sdk::ifaces::entity_list->get_client_entity_from_handle(object.entity);

			if (ent == nullptr)
				continue;

			if (ent->is_player()) {
				if (glow_players && (no_teammate_players ? (ent->get_team_num() != local->get_team_num()) : true)) {
					color clr = (no_teammate_players ? col_enemy : utils::get_team_color(ent->get_team_num()));

					if (!ent->is_vulnerable())
						clr = col_invuln;

					else if (ent->get_index() == aimbot.cur_target_idx)
						clr = col_target;

					object.glow_color = clr.get_vec3();
					object.glow_alpha = clr.get_a_fl();
				}

				else object.glow_alpha = 0.0f;
			}

			else if (ent->is_building()) {
				if (glow_buildings && (no_teammate_buildings ? (ent->get_team_num() != local->get_team_num()) : true)) {
					color clr = (no_teammate_buildings ? col_enemy : utils::get_team_color(ent->get_team_num()));

					object.glow_color = clr.get_vec3();
					object.glow_alpha = clr.get_a_fl();
				}

				else object.glow_alpha = 0.0f;
			}
		}
	}
}

_esp esp;
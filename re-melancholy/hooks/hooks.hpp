#pragma once
#include "../modules/menu/menu.hpp"

namespace hooks
{
	namespace create_move
	{
		const int offset = 21;
		using fn = bool(__thiscall *)(void *, float, sdk::userCmd *);

		inline void engine_prediciton(sdk::baseEntity *local, sdk::userCmd *cmd)
		{
			char move_data[512];
			memset(move_data, 0, sizeof(move_data));

			float old_cur_time		= sdk::ifaces::globals->curtime;
			float old_frame_time	= sdk::ifaces::globals->frametime;
			int old_tick_count		= sdk::ifaces::globals->tickcount;

			sdk::ifaces::globals->curtime	= (local->get_tick_base() * sdk::ifaces::globals->interval_per_tick);
			sdk::ifaces::globals->frametime = sdk::ifaces::globals->interval_per_tick;
			sdk::ifaces::globals->tickcount = local->get_tick_base();

			local->set_current_cmd(cmd);

			sdk::ifaces::prediction->setup_move(local, cmd, sdk::ifaces::move_helper, move_data);
			sdk::ifaces::game_movement->process_movement(local, move_data);
			sdk::ifaces::prediction->finish_move(local, cmd, move_data);

			local->set_current_cmd(nullptr);

			sdk::ifaces::globals->curtime	= old_cur_time;
			sdk::ifaces::globals->frametime = old_frame_time;
			sdk::ifaces::globals->tickcount = old_tick_count;
		}

		bool __fastcall hook(void *client_mode, int edx, float input_sample_frametime, sdk::userCmd *cmd)
		{
			vmtManager &hk = vmtManager::get_hook(client_mode);
			bool b = hk.get_method<fn>(offset)(client_mode, input_sample_frametime, cmd);

			if (!cmd
				|| !cmd->command_number
				|| !sdk::ifaces::engine->is_connected()
				|| !sdk::ifaces::engine->is_in_game())
				return false;

			sdk::baseEntity *local = get_ent(local_ent_idx);

			if (local == nullptr)
				return false;

			if (local->is_alive()) { //from my testing baseCombatWeapon is never a nullptr when local is alive
				global_info.sniper_can_headshot = utils::can_sniper_headshot(local);
				global_info.spy_can_headshot = utils::can_spy_headshot(local);
			}

			misc.run(local, cmd);
			engine_prediciton(local, cmd);
			aimbot.run(local, cmd);

			return (aimbot.silent ? false : b);
		}
	}

	namespace run_command
	{
		int offset = 17;
		using fn = void(__thiscall *)(void *, sdk::baseEntity *, sdk::userCmd *, sdk::moveHelper *);

		void __fastcall hook(void *prediction, int edx, sdk::baseEntity *entity, sdk::userCmd *cmd, sdk::moveHelper *move_helper)
		{
			vmtManager &hk = vmtManager::get_hook(prediction);
			hk.get_method<fn>(offset)(prediction, entity, cmd, move_helper);

			if (move_helper && !sdk::ifaces::move_helper)
				sdk::ifaces::move_helper = move_helper;
		}
	}

	namespace paint_traverse
	{
		const int offset = 41;
		using fn = void(__thiscall *)(void *, unsigned int, bool, bool);

		void __fastcall hook(void *panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force)
		{
			if (esp.active && esp.no_scope) {
				const char *hud_scope = sdk::ifaces::panels->get_name(vgui_panel);

				if (hud_scope[0] == 'H' && hud_scope[3] == 'S' && hud_scope[8] == '\0')
					return;
			}

			vmtManager &hk = vmtManager::get_hook(panels);
			hk.get_method<fn>(offset)(panels, vgui_panel, force_repaint, allow_force);

			static unsigned int top_panel;

			if (top_panel == 0) {
				const char *name = sdk::ifaces::panels->get_name(vgui_panel);

				if (name[0] == 'M' && name[3] == 'S')
					top_panel = vgui_panel;
			}

			if (top_panel == vgui_panel)
			{
				sdk::baseEntity *local = get_ent(local_ent_idx);

				if (local != nullptr) {
					local->force_taunt_camera(local->is_alive() && esp.active && esp.thirdperson);
					esp.run(local);
				}
				
				menu.run();
			}
		}
	}

	namespace override_view
	{
		const int offset = 16;
		using fn = void(__thiscall *)(void *, sdk::viewSetup *);

		void __fastcall hook(void *client_mode, int edx, sdk::viewSetup *view_setup)
		{
			vmtManager &hk = vmtManager::get_hook(client_mode);
			hk.get_method<fn>(offset)(client_mode, view_setup);

			sdk::baseEntity *local = get_ent(local_ent_idx);

			if (local == nullptr || !local->is_alive())
				return;

			if (!esp.active)
				return;

			if (esp.no_zoom) {
				view_setup->fov = esp.local_fov;
				local->set(0x1034, esp.local_fov); //0x1034 m_iFOV
			}

			else
			{
				if (!local->is_scoped()) {
					view_setup->fov = esp.local_fov;
					local->set(0x1034, esp.local_fov);
				}
			}
		}
	}

	namespace lock_cursor
	{
		const int offset = 62;
		using fn = void(__fastcall *)();

		void __fastcall hook(void *surface, int edx)
		{
			vmtManager &hk = vmtManager::get_hook(surface);
			hk.get_method<fn>(offset)();

			if (menu.active)
				sdk::ifaces::surface->unlock_cursor();
			
			else hk.get_method<fn>(offset)();
		}
	}

	namespace should_draw_viewmodel
	{
		const int offset = 24;
		using fn = bool(__fastcall *)();

		bool __fastcall hook(void *client_mode, int edx)
		{
			vmtManager &hk = vmtManager::get_hook(client_mode);
			
			sdk::baseEntity *local = get_ent(local_ent_idx);

			if (local == nullptr || !local->is_alive())
				return false;

			if (esp.active && esp.no_scope && esp.no_zoom) {
				if (local->is_scoped())
					return true;

				return hk.get_method<fn>(offset)();
			}

			return hk.get_method<fn>(offset)();
		}
	}

	namespace frame_stage_notify
	{
		int offset = 35;
		using fn = void(__thiscall *)(void *, sdk::clientFrameStage);

		inline void fix_thirdperson_drawing(sdk::baseEntity *local)
		{
			if (!esp.thirdperson || !local->is_alive() || !local->is_scoped())
				return;

			local->remove_effect(sdk::ef_nodraw);
			local->get_active_weapon()->remove_effect(sdk::ef_nodraw);

			//TODO: wearables. There's a NETVAR called m_hMyWearables but I couldn't get it to work and an ent loop just for the cosmetics is baaad
		}

		void __fastcall hook(void *client, int edx, sdk::clientFrameStage frame)
		{
			vmtManager &hk = vmtManager::get_hook(client);
			hk.get_method<fn>(offset)(client, frame);

			sdk::baseEntity *local = get_ent(local_ent_idx);

			if (local == nullptr)
				return;

			esp.run_glow(local, frame);

			switch (frame)
			{
				case sdk::frame_render_start: {
					fix_thirdperson_drawing(local);
					break;
				}

				default: break;
			}
		}
	}

	void initialize()
	{
		if (sdk::ifaces::client_mode) {
			vmtBaseManager *client_mode_hook = new vmtBaseManager();
			client_mode_hook->init(sdk::ifaces::client_mode);
			client_mode_hook->hook_method(&create_move::hook, create_move::offset);
			client_mode_hook->hook_method(&override_view::hook, override_view::offset);
			client_mode_hook->hook_method(&should_draw_viewmodel::hook, should_draw_viewmodel::offset);
			client_mode_hook->rehook();
		}

		if (sdk::ifaces::prediction) {
			vmtBaseManager *prediction_hook = new vmtBaseManager();
			prediction_hook->init(sdk::ifaces::prediction);
			prediction_hook->hook_method(&run_command::hook, run_command::offset);
			prediction_hook->rehook();
		}

		if (sdk::ifaces::panels) {
			vmtBaseManager *panels_hook = new vmtBaseManager();
			panels_hook->init(sdk::ifaces::panels);
			panels_hook->hook_method(&paint_traverse::hook, paint_traverse::offset);
			panels_hook->rehook();
		}

		if (sdk::ifaces::surface) {
			vmtBaseManager *surface_hook = new vmtBaseManager();
			surface_hook->init(sdk::ifaces::surface);
			surface_hook->hook_method(&lock_cursor::hook, lock_cursor::offset);
			surface_hook->rehook();
		}

		if (sdk::ifaces::client) {
			vmtBaseManager *client_hook = new vmtBaseManager();
			client_hook->init(sdk::ifaces::client);
			client_hook->hook_method(&frame_stage_notify::hook, frame_stage_notify::offset);
			client_hook->rehook();
		}
	}
}
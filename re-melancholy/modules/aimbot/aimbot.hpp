#pragma once
#include "../../sdk/sdk.hpp"

class _aimbot
{
private:
	struct aimTarget {
		sdk::baseEntity *ptr = nullptr;
		math::vec3 pos = math::vec3();
		math::vec3 ang = math::vec3();
		math::vec3 local_pos = math::vec3();
	};

	bool is_key_down();
	void set_angles(sdk::userCmd *cmd, math::vec3 &angles);
	bool should_autoshoot(sdk::baseEntity *local, sdk::baseCombatWeapon *wep, math::vec3 &aim_pos);
	int get_best_hitbox(sdk::baseEntity *local, sdk::baseCombatWeapon *wep);
	aimTarget get_target(sdk::baseEntity *local, sdk::baseCombatWeapon *wep, sdk::userCmd *cmd);
	bool try_multipoint(sdk::baseEntity *local, aimTarget &target);
	bool try_hitscan(sdk::baseEntity *local, aimTarget &target);

public:
	bool active			= false;
	bool silent			= false;
	int aim_key			= 0;		//0 lshift, 1 lbutton, 2 always
	int autoshoot		= 0;		//0 off, 1 on, 2 same as 1 but checks if sniper is scoped and can headshot
	float aim_fov		= 45.0f;
	int aim_hitbox		= -1;		//-1 auto
	bool no_melee		= false;
	float multipoint	= 0.5f;		//0.5 is off
	bool hitscan		= true;

	int cur_target_idx = -1;

	void run(sdk::baseEntity *local, sdk::userCmd *cmd);
};

extern _aimbot aimbot;
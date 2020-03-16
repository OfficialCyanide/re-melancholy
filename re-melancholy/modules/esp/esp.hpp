#pragma once
#include "../aimbot/aimbot.hpp"

class _esp 
{
private:
	enum struct espEntType
	{
		unknown = -1,
		player,
		building,
		pickup
	};

	struct espEntity {
		sdk::baseEntity *ptr	= nullptr;
		float dist_to_ent		= FLT_MAX;
		espEntType type			= espEntType::unknown;
		color draw_col			= color();
	};

	std::vector<espEntity> entities;

	bool get_ent_bounds(sdk::baseEntity *ent, float &x, float &y, float &w, float &h);

	color col_enemy		= color(100, 170, 75, 255);
	color col_target	= color(255, 200, 0, 255);
	color col_invuln	= color(60, 100, 130, 255);
	color col_white		= color(255, 255, 255, 255);
	color col_green		= color(0, 255, 0, 255);
	color col_outline	= color(0, 0, 0, 200);

	int font_tall		= 11;
	int draw_offset		= 3;
	int hpbar_offset	= 2;
	int hpbar_h			= 4;

public:
	bool active					= false;
	bool no_scope				= true;
	bool no_zoom				= true;
	bool thirdperson			= false;
	bool spectators				= true;
	int local_fov				= 100;

	bool players				= true;
	bool no_teammate_players	= true;
	bool ignore_cloaked			= false;
	bool player_name			= true;
	bool player_health			= true;
	bool player_class			= true;
	bool player_cond			= true;
	bool player_rect			= true;
	bool player_glow			= true;

	bool buildings				= true;
	bool no_teammate_buildings	= true;
	bool building_name			= true;
	bool building_level			= true;
	bool building_health		= true;
	bool building_rect			= true;
	bool building_glow			= true;

	bool pickups		= true;
	bool pickup_name	= true;
	
	void run(sdk::baseEntity *local);
	void run_glow(sdk::baseEntity *local, sdk::clientFrameStage frame);
};

extern _esp esp;
#pragma once
#include "../../modules/modules.hpp"
#include <sstream>
#include <iomanip>

namespace key
{
	//credits to elitepleb for get_key_state()

	enum state
	{
		none,
		pressed,
		held
	};

	inline state get_key_state(int16_t key)
	{
		static state keys[256] = { none };

		if (GetKeyState(key) & 0x8000)
		{
			if (keys[key] == pressed)
				keys[key] = held;

			else if (keys[key] != held)
				keys[key] = pressed;
		}

		else keys[key] = none;

		return keys[key];
	}

	inline bool is_pressed(int16_t key) {
		return (get_key_state(key) == pressed);
	}

	inline bool is_held(int16_t key) {
		return (get_key_state(key) == held);
	}

	inline bool is_pressed_and_held(int16_t key) {
		state key_state = get_key_state(key);

		static std::chrono::time_point<std::chrono::steady_clock> start[256] = { std::chrono::steady_clock::now() };

		if (key_state == pressed) {
			start[key] = std::chrono::steady_clock::now();
			return true;
		}

		if (key_state == held && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start[key]).count() > 400)
			return true;

		return false;
	}
}

inline std::string format_flt(float x, int precision)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << x;
	return stream.str();
}

class _menu
{
private:
	enum struct itemType {
		DEFAULT = -1,
		BOOL,
		INT,
		FLOAT,
		ALIAS,
		TAB
	};

	struct itemBase {
		itemType type		= itemType::DEFAULT;
		std::string name	= "";
		void *ptr			= nullptr;

		itemBase(itemType type, std::string name, void *ptr) : type(type), name(name), ptr(ptr) {};
	};

	struct itemBool : public itemBase {
		itemBool(std::string name, bool *ptr) : itemBase(itemType::BOOL, name, ptr) {};
		~itemBool() { delete this; }
	};

	struct itemInt : public itemBase {
		int min = 0, max = 0;

		itemInt(std::string name, int *ptr, int min, int max) : itemBase(itemType::INT, name, ptr), min(min), max(max) {};
		~itemInt() { delete this; }
	};

	struct itemFloat : public itemBase {
		float min = 0.0f, max = 0.0f;
		float step = 1.0f;
		int precision = 0;

		itemFloat(std::string name, float *ptr, float min, float max, float step = 1.0f, int precision = 0) : itemBase(itemType::FLOAT, name, ptr), min(min), max(max), step(step), precision(precision) {};
		~itemFloat() { delete this; }
	};

	struct itemAlias : public itemBase {
		std::vector<std::pair<int, std::string>> aliases;
		int cur_alias_idx = 0;

		itemAlias(std::string name, int *ptr, std::vector<std::pair<int, std::string>> aliases) : itemBase(itemType::ALIAS, name, ptr), aliases(aliases) {};
		~itemAlias() { delete this; }
	};

	struct itemTab : public itemBase {
		std::vector<itemBase*> items;
		bool open = true;

		itemTab(std::string name, std::vector<itemBase*> items, bool open = true) : itemBase(itemType::TAB, name, nullptr), items(items), open(open) {};
		~itemTab() { delete this; }
	};

	std::vector<itemBase*> items;

	int menu_x			= 350,
		menu_y			= 150,
		menu_w			= 220, //TODO: find dynamically?
		font_tall		= 16,
		val_offset_x	= 150, //item's value is drawn at menu_x + val_offset_x
		name_offset_x	= 5;

	color col_frame_bg			= color(30, 30, 30, 255);
	color col_frame_bg_tab		= color(20, 20, 20, 255);
	color col_frame_bg_light	= color(45, 45, 45, 255);
	color col_frame_outline		= color(15, 15, 15, 255);
	color col_item_normal		= color(255, 255, 255, 255);
	color col_item_selected		= color(255, 200, 0, 255);
	color col_tab_hightlight	= color(255, 200, 0, 180);

	surfaceWrapper draw;
	int drawn_count = 0;

	void do_menu(std::vector<itemBase*> to_draw, int mx, int my)
	{
		for (auto &v : to_draw) //update & draw
		{
			bool is_hovered = (mx > menu_x && mx < (menu_x + menu_w) && my > (menu_y + (font_tall * drawn_count)) && my < (menu_y + (font_tall * (drawn_count + 1))));

			int h = (font_tall + 1);
			color bg = col_frame_bg;

			if (v->type == itemType::TAB) {
				itemTab *tab = reinterpret_cast<itemTab*>(v);
				h = (tab->open ? (font_tall * tab->items.size()) : font_tall);
				bg = col_frame_bg_tab;
			}

			draw.rect(menu_x, (menu_y + (font_tall * drawn_count)), menu_w, h, (is_hovered ? col_frame_bg_light : bg));
			draw.outline_rect(menu_x, (menu_y + (font_tall * drawn_count)), menu_w, h, col_frame_outline);

			switch (v->type)
			{
				case itemType::BOOL:
				{
					bool *ptr = reinterpret_cast<bool*>(v->ptr);

					if (is_hovered && key::is_pressed(VK_LBUTTON))
						*ptr = !*ptr;

					draw.string(
						(menu_x + name_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						v->name.c_str());

					draw.string(
						(menu_x + val_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						(*ptr ? "on" : "off"));

					drawn_count++;
					break;
				}

				case itemType::INT:
				{
					int *ptr	= reinterpret_cast<int*>(v->ptr);
					int min		= reinterpret_cast<itemInt*>(v)->min;
					int max		= reinterpret_cast<itemInt*>(v)->max;

					if (is_hovered) {
						if (key::is_pressed_and_held(VK_LBUTTON))
							if (*ptr > min)
								*ptr -= 1;

						if (key::is_pressed_and_held(VK_RBUTTON))
							if (*ptr < max)
								*ptr += 1;
					}

					std::string val = std::to_string(*ptr);

					if (*ptr != min && *ptr != max)
						val = ("< " + val + " >");

					else if (*ptr == min)
						val = (val + " >");

					else if (*ptr == max)
						val = ("< " + val);

					draw.string(
						(menu_x + name_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						v->name.c_str());

					draw.string(
						(menu_x + val_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						val.c_str());

					drawn_count++;
					break;
				}

				case itemType::FLOAT:
				{
					float *ptr		= reinterpret_cast<float*>(v->ptr);
					float min		= reinterpret_cast<itemFloat*>(v)->min;
					float max		= reinterpret_cast<itemFloat*>(v)->max;
					float step		= reinterpret_cast<itemFloat*>(v)->step;
					int precision	= reinterpret_cast<itemFloat*>(v)->precision;

					if (is_hovered) {
						if (key::is_pressed_and_held(VK_LBUTTON))
							if (*ptr > min)
								*ptr -= step;

						if (key::is_pressed_and_held(VK_RBUTTON))
							if (*ptr < max)
								*ptr += step;
					}

					std::string val = (precision > 0 ? format_flt(*ptr, precision) : std::to_string(static_cast<int>(*ptr)));

					if (*ptr != min && *ptr != max)
						val = ("< " + val + " >");

					else if (*ptr == min)
						val = (val + " >");

					else if (*ptr == max)
						val = ("< " + val);

					draw.string(
						(menu_x + name_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						v->name.c_str());

					draw.string(
						(menu_x + val_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						val.c_str());

					drawn_count++;
					break;
				}

				case itemType::ALIAS:
				{
					itemAlias *alias	= reinterpret_cast<itemAlias*>(v);
					int *ptr			= reinterpret_cast<int*>(alias->ptr);
					int min				= 0;
					int max				= (alias->aliases.size() - 1);

					if (is_hovered) {
						if (key::is_pressed(VK_LBUTTON))
							if (alias->cur_alias_idx != 0)
								*ptr = alias->aliases.at(--alias->cur_alias_idx).first;

						if (key::is_pressed(VK_RBUTTON))
							if (alias->cur_alias_idx != (alias->aliases.size() - 1))
								*ptr = alias->aliases.at(++alias->cur_alias_idx).first;
					}

					std::string val = alias->aliases.at(alias->cur_alias_idx).second;

					if (alias->cur_alias_idx != min && alias->cur_alias_idx != max)
						val = ("< " + val + " >");

					else if (alias->cur_alias_idx == min)
						val = (val + " >");

					else if (alias->cur_alias_idx == max)
						val = ("< " + val);

					draw.string(
						(menu_x + name_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						v->name.c_str());

					draw.string(
						(menu_x + val_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						val.c_str());

					drawn_count++;
					break;
				}

				case itemType::TAB:
				{
					itemTab *tab = reinterpret_cast<itemTab*>(v);

					if (is_hovered && key::is_pressed(VK_LBUTTON))
						tab->open = !tab->open;

					draw.string(
						(menu_x + name_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						v->name.c_str());

					draw.string(
						(menu_x + val_offset_x),
						(menu_y + (font_tall * drawn_count)),
						(is_hovered ? col_item_selected : col_item_normal),
						(tab->open ? "-" : "+"));

					drawn_count++;

					if (tab->open)
						do_menu(tab->items, mx, my);

					break;
				}
			}
		}
	}

public:
	bool active = false;

	void run()
	{
		static bool init = false;

		if (!init)
		{
			draw = surfaceWrapper("Arial", (font_tall - 1), 200, sdk::fontflag_none);

			items =
			{
				new itemTab("AIMBOT", {
					new itemBool	("active",			&aimbot.active),
					new itemBool	("silent",			&aimbot.silent),
					new itemAlias	("key",				&aimbot.aim_key,		{ { 0, "lshift" }, { 1, "lbutton" }, { 2, "always" } }),
					new itemAlias	("auto shoot",		&aimbot.autoshoot,		{ { 0, "off" }, { 1, "on" }, { 2, "SO" } }),
					new itemFloat	("fov",				&aimbot.aim_fov,		1.0f, 180.0f),
					new itemAlias	("hitbox",			&aimbot.aim_hitbox,		{ { -1, "auto" }, { sdk::hitbox_head, "head" }, { sdk::hitbox_pelvis, "body" } }),
					new itemBool	("no melee",		&aimbot.no_melee),
					new itemFloat	("multipoint",		&aimbot.multipoint,		0.5f, 0.9f, 0.05f, 2),
					new itemBool	("hitscan",			&aimbot.hitscan),
					new itemBool	("ignore cloaked",	&aimbot.ignore_cloaked)
				}),

				new itemTab("ESP", {
					new itemBool("active", &esp.active),

					new itemTab("ESP - LOCAL", {
						new itemBool("no scope",	&esp.no_scope),
						new itemBool("no zoom",		&esp.no_zoom),
						new itemBool("thirdperson", &esp.thirdperson),
						new itemBool("spectators",	&esp.spectators),
						new itemInt("fov",			&esp.local_fov, 70, 130)
					}, false),

					new itemTab("ESP - PLAYERS", {
						new itemBool("active",			&esp.players),
						new itemBool("no teammates",	&esp.no_teammate_players),
						new itemBool("ignore cloaked",	&esp.ignore_cloaked),
						new itemBool("name",			&esp.player_name),
						new itemBool("health",			&esp.player_health),
						new itemBool("class",			&esp.player_class),
						new itemBool("cond",			&esp.player_cond),
						new itemBool("rect",			&esp.player_rect),
						new itemBool("glow",			&esp.player_glow)
					}, false),

					new itemTab("ESP - BUILDINGS", {
						new itemBool("active",			&esp.buildings),
						new itemBool("no teammates",	&esp.no_teammate_buildings),
						new itemBool("name",			&esp.building_name),
						new itemBool("level",			&esp.building_level),
						new itemBool("health",			&esp.building_health),
						new itemBool("rect",			&esp.building_rect),
						new itemBool("glow",			&esp.building_glow)
					}, false),

					new itemTab("ESP - PICKUPS", {
						new itemBool("active",	&esp.pickups),
						new itemBool("name",	&esp.pickup_name)
					}, false)
				}),

				new itemTab("MISC", {
					new itemBool("bunnyhop", &misc.bunnyhop)
				})
			};

			init = true;
		}

		if (key::is_pressed(VK_INSERT) && sdk::ifaces::engine->is_connected()) {
			active = !active;
			sdk::ifaces::surface->set_cursor_always_visible(active);
			screen_size.update();
		}

		if (active)
		{
			int mouse_x = 0, mouse_y = 0;
			sdk::ifaces::surface->get_cursor_pos(mouse_x, mouse_y);

			if (key::is_held(VK_MBUTTON)) {
				menu_x = mouse_x;
				menu_y = mouse_y;
			}

			drawn_count = 0;
			do_menu(items, mouse_x, mouse_y);
		}
	}
};

extern _menu menu;
#pragma once
#include "../misc/misc.hpp"

void _misc::run(sdk::baseEntity *local, sdk::userCmd *cmd)
{
	if (!local->is_alive())
		return;

	if (bunnyhop)
	{
		static bool jump_state = false;

		if (cmd->buttons & sdk::in_jump)
		{
			if (!jump_state && !local->is_on_ground())
				cmd->buttons &= ~sdk::in_jump;

			else if (jump_state)
				jump_state = false;
		}

		else if (!jump_state)
			jump_state = true;
	}
}

_misc misc;
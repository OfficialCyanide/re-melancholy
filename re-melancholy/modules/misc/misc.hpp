#include "../../sdk/sdk.hpp"

class _misc
{
public:
	bool bunnyhop = true;

	void run(sdk::baseEntity *local, sdk::userCmd *cmd);
};

extern _misc misc;
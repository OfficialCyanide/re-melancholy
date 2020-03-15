#include "hooks/hooks.hpp"

unsigned long __stdcall main_thread(void *params)
{
	net_vars.initialize();
	sdk::ifaces::initialize();
	hooks::initialize();
	screen_size.update();

	return 0x0;
}

int __stdcall DllMain(void *instance, unsigned long reason, void *reserved)
{
	if (reason == 0x1)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main_thread), nullptr, 0x0, nullptr);

	return 1;
}
#pragma once
#include <Windows.h>

#undef interface //thonk

namespace interface
{
	typedef void *(*instantiateInterface)();

	class interface
	{
	public:
		instantiateInterface _interface;
		char *interface_name;
		interface *next_interface;
	};

	inline void *get(const char *module, const char *object)
	{
		ULONG create_interface = (ULONG)GetProcAddress(GetModuleHandleA(module), "CreateInterface");
		ULONG short_jump = (ULONG)create_interface + 5;
		ULONG jump = (((ULONG)create_interface + 5) + *(ULONG*)short_jump) + 4;
		interface* list = **(interface***)(jump + 6);

		do
		{
			if (list)
				if (strstr(list->interface_name, object) && (strlen(list->interface_name) - strlen(object)) < 5) 
					return list->_interface();

		} while (list = list->next_interface);

		return nullptr;
	}
};
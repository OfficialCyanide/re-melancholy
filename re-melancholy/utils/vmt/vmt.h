#pragma once
#include <cassert>
#include <cstdlib>

//credits to Casual_Hacker

inline unsigned int count_funcs(void **pVMT) {
	unsigned int i = -1;
	do ++i; while (pVMT[i]);
	return i;
}

inline int find_func(void **pVMT, void *pFunc, unsigned int vfuncs = 0) {
	if (!vfuncs)
		vfuncs = count_funcs(pVMT);

	for (unsigned int i = 0; i < vfuncs; i++)
		if (pVMT[i] == pFunc)
			return i;

	return -1;
}

class vmtBaseManager
{
public:
	enum { GUARD = 0xFAC0D775 };

	vmtBaseManager &init(void *inst, unsigned int offset = 0, unsigned int vfuncs = 0);
	void kill();
	bool is_initialized() const;
	vmtBaseManager &hook_method(void *newfunc, unsigned int index);
	vmtBaseManager &unhook_method(unsigned int index);
	void erase_hooks();
	vmtBaseManager &unhook();
	vmtBaseManager &rehook();
	bool hooked() const;
	template <typename t>
	const t &get_method(unsigned int index) const {
		assert(index < count_funcs(_array + 3));
		return *(const t *)&_oldvmt[index];
	}
	static bool hook_present(void *inst, unsigned int offset = 0);
	static vmtBaseManager &get_hook(void *inst, unsigned int offset = 0);

protected:
	static void **&_getvtbl(void *inst, unsigned int offset);

protected:
	void ***_vftable;
	void **_oldvmt;
	void **_array;
};

class vmtManager : public vmtBaseManager
{
	vmtManager(const vmtManager &);

public:
	vmtManager(void *inst, unsigned int offset = 0, unsigned int vfuncs = 0);
	~vmtManager();
	void poof();
	static vmtManager &get_hook(void *inst, unsigned int offset = 0);
};
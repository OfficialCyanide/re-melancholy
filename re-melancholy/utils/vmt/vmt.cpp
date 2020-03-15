#include "../vmt/vmt.h"

vmtBaseManager &vmtBaseManager::init(void *inst, unsigned int offset, unsigned int vfuncs)
{
	_vftable = &_getvtbl(inst, offset);
	_oldvmt = *_vftable;

	if (!vfuncs) {
		vfuncs = count_funcs(_oldvmt);
		assert(vfuncs >= 1);
	}

	void **arr = _array = (void **) ::malloc((vfuncs + 4) * sizeof(void *));
	arr[0] = this;
	arr[1] = (void *)GUARD;
	(arr + 3)[vfuncs] = nullptr;

	{
		unsigned int i = -1;
		do arr[i + 3] = _oldvmt[i];
		while (++i < vfuncs);
	}

	return *this;
}

void vmtBaseManager::kill()
{
	if (is_initialized()) {
		unhook();
		_vftable = nullptr;
	}

	::free(_array);
	_array = nullptr;
}

bool vmtBaseManager::is_initialized() const
{
	return _vftable != nullptr;
}

vmtBaseManager &vmtBaseManager::hook_method(void *newfunc, unsigned int index)
{
	assert(index < count_funcs(_array + 3) && is_initialized());
	_array[index + 3] = newfunc;
	return *this;
}

vmtBaseManager &vmtBaseManager::unhook_method(unsigned int index)
{
	assert(index < count_funcs(_array + 3) && is_initialized());
	_array[index + 3] = _oldvmt[index];
	return *this;
}

void vmtBaseManager::erase_hooks()
{
	unsigned int i = 0;
	void **vmt = _array + 3;
	do vmt[i] = _oldvmt[i];
	while (vmt[++i]);
}

vmtBaseManager &vmtBaseManager::unhook()
{
	*_vftable = _oldvmt;
	return *this;
}

vmtBaseManager &vmtBaseManager::rehook()
{
	*_vftable = _array + 3;
	return *this;
}

bool vmtBaseManager::hooked() const
{
	return *_vftable != _oldvmt;
}

bool vmtBaseManager::hook_present(void *inst, unsigned int offset)
{
	void **vmt = _getvtbl(inst, offset);
	return vmt[-2] == (void *)GUARD;
}

vmtBaseManager &vmtBaseManager::get_hook(void *inst, unsigned int offset)
{
	void **vmt = _getvtbl(inst, offset);
	return *reinterpret_cast<vmtBaseManager *>(vmt[-3]);
}

void **&vmtBaseManager::_getvtbl(void *inst, unsigned int offset)
{
	return *reinterpret_cast<void ***>((char *)inst + offset);
}

vmtManager::vmtManager(void *inst, unsigned int offset, unsigned int vfuncs)
{
	init(inst, offset, vfuncs).rehook();
}

vmtManager::~vmtManager()
{
	kill();
}

void vmtManager::poof()
{
	_vftable = nullptr;
}

vmtManager &vmtManager::get_hook(void *inst, unsigned int offset)
{
	return static_cast<vmtManager &>(vmtBaseManager::get_hook(inst, offset));
}
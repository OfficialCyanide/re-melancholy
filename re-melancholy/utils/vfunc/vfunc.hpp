#pragma once

namespace vfunc
{
	inline void **&get_vtable(void *inst, size_t offset = 0)
	{
		return *reinterpret_cast<void***>((size_t)inst + offset);
	}

	inline const void **get_vtable(const void *inst, size_t offset = 0)
	{
		return *reinterpret_cast<const void***>((size_t)inst + offset);
	}

	template<typename T>
	inline T get_vfunc(const void *inst, size_t index, size_t offset = 0)
	{
		return reinterpret_cast<T>(get_vtable(inst, offset)[index]);
	}
}
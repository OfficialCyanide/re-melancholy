#pragma once
#include "../sdk/dt_recv2.hpp"
#include "../utils/utils.hpp"

class clientClassEx
{
private:
	char padding[8];
public:
	char *name;
	RecvTable *table;
	clientClassEx *next_class;
	int	class_id;
};

class hlClientEx
{
public:
	clientClassEx *get_all_classes(void)
	{
		typedef clientClassEx *(__thiscall * OriginalFn)(void *);
		return vfunc::get_vfunc<OriginalFn>(this, 8)(this);
	}
};

class netVars
{
	struct node;
	using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

	struct node
	{
		node(DWORD offset) : offset(offset) {}
		map_type nodes;
		DWORD offset;
	};

	map_type nodes;

	hlClientEx *clientEx = nullptr;

public:
	void initialize();

private:
	void populate_nodes(class RecvTable *recv_table, map_type *map);

	DWORD get_offset_recursive(map_type &map, int acc, const char *name)
	{
		return acc + map[name]->offset;
	}

	template<typename ...args_t>
	DWORD get_offset_recursive(map_type &map, int acc, const char *name, args_t ...args)
	{
		const auto &node = map[name];
		return get_offset_recursive(node->nodes, acc + node->offset, args...);
	}

public:
	template<typename ...args_t>
	DWORD get_offset(const char *name, args_t ...args)
	{
		const auto &node = nodes[name];
		return get_offset_recursive(node->nodes, node->offset, args...);
	}
};

extern netVars net_vars;

template<typename T>
class dynamicNetvar
{
	DWORD off;

public:
	template<typename... args_t>
	dynamicNetvar(args_t... a)
	{
		off = net_vars.get_offset(a...);
	}

	template<typename... args_t>
	dynamicNetvar(int offset, args_t... a)
	{
		off = net_vars.get_offset(a...) + offset;
	}

	T get_value(PVOID base)
	{
		return *reinterpret_cast<T *>((DWORD)base + (DWORD)off);
	}

	void set_value(PVOID base, T val)
	{
		*reinterpret_cast<T *>((DWORD)(base)+((DWORD)(off))) = val;
	}
};

#define DYNVAR(name, type, ...) static dynamicNetvar<type> ##name(__VA_ARGS__)
#define DYNVAR_RETURN(type, base, ...) DYNVAR(n, type, __VA_ARGS__); return n.get_value(base)
#define DYNVAR_SET(type, base, value, ...) DYNVAR(n, type, __VA_ARGS__); n.set_value(base, value)
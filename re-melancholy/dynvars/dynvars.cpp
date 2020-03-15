#include "../dynvars/dynvars.hpp"

#undef GetProp

void netVars::initialize()
{
	while (!clientEx)
		clientEx = reinterpret_cast<hlClientEx*>(interface::get("client.dll", "VClient017"));

	const clientClassEx *client_class = clientEx->get_all_classes();

	while (client_class != nullptr)
	{
		const auto class_info = std::make_shared<node>(0);
		auto *recv_table = client_class->table;
		populate_nodes(recv_table, &class_info->nodes);
		nodes.emplace(recv_table->GetName(), class_info);

		client_class = client_class->next_class;
	}
}

void netVars::populate_nodes(RecvTable *recv_table, map_type *map)
{
	for (auto i = 0; i < recv_table->GetNumProps(); i++)
	{
		const auto *prop = recv_table->GetProp(i);
		const auto prop_info = std::make_shared<node>(prop->GetOffset());

		if (prop->GetType() == DPT_DataTable)
			populate_nodes(prop->GetDataTable(), &prop_info->nodes);

		map->emplace(prop->GetName(), prop_info);
	}
}

netVars net_vars;
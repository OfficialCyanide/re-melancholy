#include "../sdk/sdk.hpp"

sdk::hlClient			*sdk::ifaces::client		= nullptr;
sdk::engineClient		*sdk::ifaces::engine		= nullptr;
sdk::iGlobals			*sdk::ifaces::globals		= nullptr;
sdk::modelInfo			*sdk::ifaces::model_info	= nullptr;
sdk::entityList			*sdk::ifaces::entity_list	= nullptr;
sdk::iPanel				*sdk::ifaces::panels		= nullptr;
sdk::iSurface			*sdk::ifaces::surface		= nullptr;
sdk::clientModeShared	*sdk::ifaces::client_mode	= nullptr;
sdk::engineTrace		*sdk::ifaces::engine_trace	= nullptr;
sdk::moveHelper			*sdk::ifaces::move_helper	= nullptr;
sdk::iPrediction		*sdk::ifaces::prediction	= nullptr;
sdk::gameMovement		*sdk::ifaces::game_movement	= nullptr;
sdk::glowObjectManager	*sdk::ifaces::glow_object	= nullptr;

void sdk::ifaces::initialize()
{
	client			= reinterpret_cast<hlClient*>				(interface::get("client.dll", "VClient017"));
	engine			= reinterpret_cast<engineClient*>			(interface::get("engine.dll", "VEngineClient013"));
	globals			= *reinterpret_cast<iGlobals**>				(pattern::find_in_engine("A1 ? ? ? ? 8B 11 68") + 0x8);
	model_info		= reinterpret_cast<modelInfo*>				(interface::get("engine.dll", "VModelInfoClient006"));
	entity_list		= reinterpret_cast<entityList*>				(interface::get("client.dll", "VClientEntityList003"));
	panels			= reinterpret_cast<iPanel*>					(interface::get("vgui2.dll", "VGUI_Panel009"));
	surface			= reinterpret_cast<iSurface*>				(interface::get("vguimatsurface.dll", "VGUI_Surface030"));
	client_mode		= **reinterpret_cast<clientModeShared***>	(pattern::find_in_client("8B 0D ? ? ? ? 8B 02 D9 05") + 0x2);
	engine_trace	= reinterpret_cast<engineTrace*>			(interface::get("engine.dll", "EngineTraceClient003"));
	prediction		= reinterpret_cast<iPrediction*>			(interface::get("client.dll", "VClientPrediction001"));
	game_movement	= reinterpret_cast<gameMovement*>			(interface::get("client.dll", "GameMovement001"));
	glow_object		= *reinterpret_cast<glowObjectManager**>	(pattern::find_in_client("8B 0D ? ? ? ? A1 ? ? ? ? 56 8B 37") + 0x2);
}

globalInfo global_info;
screenSize screen_size;
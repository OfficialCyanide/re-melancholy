#pragma once
#include "../dynvars/dynvars.hpp"

namespace sdk
{
	#pragma region

	class hlClient;
	class engineClient;
	class iGlobals;
	class modelInfo;
	class entityList;
	class iPanel;
	class iSurface;
	class clientModeShared;
	class engineTrace;
	class moveHelper;
	class iPrediction;
	class gameMovement;
	class glowObjectManager;

	namespace ifaces
	{
		extern hlClient				*client;
		extern engineClient			*engine;
		extern iGlobals				*globals;
		extern modelInfo			*model_info;
		extern entityList			*entity_list;
		extern iPanel				*panels;
		extern iSurface				*surface;
		extern clientModeShared		*client_mode;
		extern engineTrace			*engine_trace;
		extern moveHelper			*move_helper;
		extern iPrediction			*prediction;
		extern gameMovement			*game_movement;
		extern glowObjectManager	*glow_object;

		void initialize();
	}

	#pragma endregion interfaces

	enum playerClasses
	{
		scout		= 1,
		soldier		= 3,
		pyro		= 7,
		demoman		= 4,
		heavy		= 6,
		engineer	= 9,
		medic		= 5,
		sniper		= 2,
		spy			= 8
	};

	enum playerLifeStates
	{
		alive	= 0,
		dead	= 2
	};

	enum playerFlags
	{
		on_ground	= (1 << 0),
		ducking		= (1 << 1),
		in_water	= (1 << 10) //not sure if this works :thonk:
	};

	enum playerConditions
	{
		//did gir comment these? whoever did it, thank you
	    cond_slowed						= (1 << 0),		//toggled when a player is slowed down. 
	    cond_zoomed						= (1 << 1),		//toggled when a player is zoomed. 
	    cond_disguising					= (1 << 2),		//toggled when a spy is disguising.  
	    cond_disguised					= (1 << 3),		//toggled when a spy is disguised. 
	    cond_cloaked					= (1 << 4),		//toggled when a spy is invisible. 
	    cond_ubercharged				= (1 << 5),		//toggled when a player is übercharged. 
	    cond_teleported_glow			= (1 << 6),		//toggled when someone leaves a teleporter and has glow beneath their feet. 
	    cond_taunting					= (1 << 7),		//toggled when a player is taunting. 
	    cond_ubercharge_fading			= (1 << 8),		//toggled when the übercharge is fading. 
	    cond_cloak_flicker				= (1 << 9),		//toggled when a spy is visible during cloak. 
	    cond_teleporting				= (1 << 10),	//only activates for a brief second when the player is being teleported; not very useful. 
	    cond_kritzkrieged				= (1 << 11),	//toggled when a player is being crit buffed by the kritzkrieg. 
	    cond_tmp_damage_bonus			= (1 << 12),	//unknown what this is for. name taken from the alliedmodders sdk. 
	    cond_dead_ringered				= (1 << 13),	//toggled when a player is taking reduced damage from the deadringer. 
	    cond_bonked						= (1 << 14),	//toggled when a player is under the effects of the bonk! atomic punch. 
	    cond_stunned					= (1 << 15),	//toggled when a player's speed is reduced from airblast or a sandman ball. 
	    cond_buffed						= (1 << 16),	//toggled when a player is within range of an activated buff banner. 
	    cond_charging					= (1 << 17),	//toggled when a demoman charges with the shield. 
	    cond_demo_buff					= (1 << 18),	//toggled when a demoman has heads from the eyelander. 
	    cond_crit_cola					= (1 << 19),	//toggled when the player is under the effect of the crit-a-cola. 
	    cond_in_heal_radius				= (1 << 20),	//unused condition, name taken from alliedmodders sdk. 
	    cond_healing					= (1 << 21),	//toggled when someone is being healed by a medic or a dispenser. 
	    cond_on_fire					= (1 << 22),	//toggled when a player is on fire. 
	    cond_overhealed					= (1 << 23),	//toggled when a player has >100% health. 
	    cond_jarated					= (1 << 24),	//toggled when a player is hit with a sniper's jarate. 
	    cond_bleeding					= (1 << 25),	//toggled when a player is taking bleeding damage. 
	    cond_defense_buffed				= (1 << 26),	//toggled when a player is within range of an activated battalion's backup. 
	    cond_milked						= (1 << 27),	//player was hit with a jar of mad milk. 
	    cond_mega_heal					= (1 << 28),	//player is under the effect of quick-fix charge. 
	    cond_regen_buffed				= (1 << 29),	//toggled when a player is within a concheror's range. 
	    cond_marked_for_death			= (1 << 30),	//player is marked for death by a fan o'war hit. effects are similar to tfcond_jarated. 
		cond_no_healing_damage_buff		= (1 << 31),	//unknown what this is used for.
	    cond_speed_buff_ally			= (1 << 0),		//toggled when a player gets hit with the disciplinary action. 
	    cond_halloween_crit_candy		= (1 << 1),		//only for scream fortress event maps that drop crit candy. 
		cond_crit_canteen				= (1 << 2),		//player is getting a crit boost from a mvm canteen.
		cond_crit_demo_charge			= (1 << 3),		//from demo's shield
		cond_crit_hype					= (1 << 4),		//soda popper crits. 
	    cond_crit_on_first_blood		= (1 << 5),		//arena first blood crit buff. 
	    cond_crit_on_win				= (1 << 6),		//end of round crits. 
	    cond_crit_on_flag_capture		= (1 << 7),		//ctf intelligence capture crits. 
	    cond_crit_on_kill				= (1 << 8),		//unknown what this is for. 
	    cond_restrict_to_melee			= (1 << 9),		//unknown what this is for. 
		cond_defense_buff_no_crit_block	= (1 << 10),	//mvm buff.
		cond_reprogrammed				= (1 << 11),	//mvm bot has been reprogrammed.
	    cond_pyro_crits					= (1 << 12),	//player is getting crits from the mmmph charge. 
	    cond_pyro_heal					= (1 << 13),	//player is being healed from the mmmph charge. 
		cond_focus_buff					= (1 << 14),	//player is getting a focus buff.
		cond_disguised_removed			= (1 << 15),	//disguised remove from a bot.
		cond_marked_for_death_silent	= (1 << 16),	//player is under the effects of the escape plan/equalizer or gru.
		cond_disguised_as_dispenser		= (1 << 17),	//bot is disguised as dispenser.
		cond_sapped						= (1 << 18),	//mvm bot is being sapped.
		cond_ubercharged_hidden			= (1 << 19),	//mvm related
		cond_ubercharged_canteen		= (1 << 20),	//player is receiving übercharge from a canteen.
		cond_halloween_bomb_head		= (1 << 21),	//player has a bomb on their head from merasmus.
		cond_halloween_thriller			= (1 << 22),	//players are forced to dance from merasmus.
		cond_bullet_charge				= (1 << 26),	//player is receiving 75% reduced damage from bullets.
		cond_explosive_charge			= (1 << 27),	//player is receiving 75% reduced damage from explosives.
		cond_fire_charge				= (1 << 28),	//player is receiving 75% reduced damage from fire.
		cond_bullet_resistance			= (1 << 29),	//player is receiving 10% reduced damage from bullets.
		cond_explosive_resistance		= (1 << 30),	//player is receiving 10% reduced damage from explosives.
		cond_fire_resistance			= (1 << 31),	//player is receiving 10% reduced damage from fire.
		cond_stealthed					= (1 << 0),
		cond_medigun_debuff				= (1 << 1),
		cond_stealthed_user_buff_fade	= (1 << 2),
		cond_bullet_immune				= (1 << 3),
		cond_blast_immune				= (1 << 4),
		cond_fire_immune				= (1 << 5),
		cond_prevent_death				= (1 << 6),
		cond_mvm_bot_radiowave			= (1 << 7),
		cond_halloween_speed_boost		= (1 << 8),		//wheel has granted player speed boost.
		cond_halloween_quick_heal		= (1 << 9),		//wheel has granted player quick heal.
		cond_halloween_giant			= (1 << 10),	//wheel has granted player giant mode.
		cond_halloween_tiny				= (1 << 11),	//wheel has granted player tiny mode.
		cond_halloween_in_hell			= (1 << 12),	//wheel has granted player in hell mode.
		cond_halloween_ghost_mode		= (1 << 13),	//wheel has granted player ghost mode.
		cond_parachute					= (1 << 16),	//player has deployed the base jumper.
		cond_blast_jumping				= (1 << 17),	//player has sticky or rocket jumped.
	};

	enum playerHitboxes
	{
		hitbox_head,
		hitbox_neck,
		hitbox_lower_neck,
		hitbox_pelvis,
		hitbox_body,
		hitbox_thorax,
		hitbox_chest,
		hitbox_upper_chest,
		hitbox_right_thigh,
		hitbox_left_thigh,
		hitbox_right_calf,
		hitbox_left_calf,
		hitbox_right_foot,
		hitbox_left_foot,
		hitbox_right_hand,
		hitbox_left_hand,
		hitbox_right_upper_arm,
		hitbox_right_forearm,
		hitbox_left_upper_arm,
		hitbox_left_forearm,
		hitbox_max
	};

	enum playerWeapons
	{
		//p	- primary
		//s	- secondary
		//m	- melee
		//w	- watch
		//some of these names require game knowledge to understand xd

		scout_p_Scattergun                               = 13,
		scout_p_ScattergunR                              = 200,
		scout_p_ForceANature                             = 45,
		scout_p_TheShortstop                             = 220,
		scout_p_TheSodaPopper                            = 448,
		scout_p_FestiveScattergun                        = 669,
		scout_p_BabyFacesBlaster                         = 772,
		scout_p_SilverBotkillerScattergunMkI             = 799,
		scout_p_GoldBotkillerScattergunMkI               = 808,
		scout_p_RustBotkillerScattergunMkI               = 888,
		scout_p_BloodBotkillerScattergunMkI              = 897,
		scout_p_CarbonadoBotkillerScattergunMkI          = 906,
		scout_p_DiamondBotkillerScattergunMkI            = 915,
		scout_p_SilverBotkillerScattergunMkII            = 964,
		scout_p_GoldBotkillerScattergunMkII              = 973,
		scout_p_FestiveForceANature                      = 1078,
		scout_p_TheBackScatter                           = 1103,
		scout_p_NightTerror                              = 15002,
		scout_p_TartanTorpedo                            = 15015,
		scout_p_CountryCrusher                           = 15021,
		scout_p_BackcountryBlaster                       = 15029,
		scout_p_SpruceDeuce                              = 15036,
		scout_p_CurrentEvent                             = 15053,
		scout_p_MacabreWeb                               = 15065,
		scout_p_Nutcracker                               = 15069,
		scout_p_BlueMew                                  = 15106,
		scout_p_FlowerPower                              = 15107,
		scout_p_ShottoHell                               = 15108,
		scout_p_CoffinNail                               = 15131,
		scout_p_KillerBee                                = 15151,
		scout_p_Corsair                                  = 15157,
		scout_s_ScoutsPistol                             = 23,
		scout_s_PistolR                                  = 209,
		scout_s_BonkAtomicPunch                          = 46,
		scout_s_VintageLugermorph                        = 160,
		scout_s_CritaCola                                = 163,
		scout_s_MadMilk                                  = 222,
		scout_s_Lugermorph                               = 294,
		scout_s_TheWinger                                = 449,
		scout_s_PrettyBoysPocketPistol                   = 773,
		scout_s_TheFlyingGuillotine                      = 812,
		scout_s_TheFlyingGuillotineG                     = 833,
		scout_s_MutatedMilk                              = 1121,
		scout_s_FestiveBonk                              = 1145,
		scout_s_RedRockRoscoe                            = 15013,
		scout_s_HomemadeHeater                           = 15018,
		scout_s_HickoryHolepuncher                       = 15035,
		scout_s_LocalHero                                = 15041,
		scout_s_BlackDahlia                              = 15046,
		scout_s_SandstoneSpecial                         = 15056,
		scout_s_MacabreWeb                               = 15060,
		scout_s_Nutcracker                               = 15061,
		scout_s_BlueMew                                  = 15100,
		scout_s_BrainCandy                               = 15101,
		scout_s_ShottoHell                               = 15102,
		scout_s_DressedToKill                            = 15126,
		scout_s_Blitzkrieg                               = 15148,
		scout_s_TheCAPPER                                = 30666,
		scout_m_Bat                                      = 0,
		scout_m_BatR                                     = 190,
		scout_m_TheSandman                               = 44,
		scout_m_TheHolyMackerel                          = 221,
		scout_m_TheCandyCane                             = 317,
		scout_m_TheBostonBasher                          = 325,
		scout_m_SunonaStick                              = 349,
		scout_m_TheFanOWar                               = 355,
		scout_m_TheAtomizer                              = 450,
		scout_m_ThreeRuneBlade                           = 452,
		scout_m_TheConscientiousObjector                 = 474,
		scout_m_UnarmedCombat                            = 572,
		scout_m_TheWrapAssassin                          = 648,
		scout_m_FestiveBat                               = 660,
		scout_m_TheFreedomStaff                          = 880,
		scout_m_TheBatOuttaHell                          = 939,
		scout_m_TheMemoryMaker                           = 954,
		scout_m_FestiveHolyMackerel                      = 999,
		scout_m_TheHamShank                              = 1013,
		scout_m_TheNecroSmasher                          = 1123,
		scout_m_TheCrossingGuard                         = 1127,
		scout_m_Batsaber                                 = 30667,
		scout_m_PrinnyMachete                            = 30758,
		soldier_p_RocketLauncher                         = 18,
		soldier_p_RocketLauncherR                        = 205,
		soldier_p_TheDirectHit                           = 127,
		soldier_p_TheBlackBox                            = 228,
		soldier_p_RocketJumper                           = 237,
		soldier_p_TheLibertyLauncher                     = 414,
		soldier_p_TheCowMangler5000                      = 441,
		soldier_p_TheOriginal                            = 513,
		soldier_p_FestiveRocketLauncher                  = 658,
		soldier_p_TheBeggarsBazooka                      = 730,
		soldier_p_SilverBotkillerRocketLauncherMkI       = 800,
		soldier_p_GoldBotkillerRocketLauncherMkI         = 809,
		soldier_p_RustBotkillerRocketLauncherMkI         = 889,
		soldier_p_BloodBotkillerRocketLauncherMkI        = 898,
		soldier_p_CarbonadoBotkillerRocketLauncherMkI    = 907,
		soldier_p_DiamondBotkillerRocketLauncherMkI      = 916,
		soldier_p_SilverBotkillerRocketLauncherMkII      = 965,
		soldier_p_GoldBotkillerRocketLauncherMkII        = 974,
		soldier_p_FestiveBlackBox                        = 1085,
		soldier_p_TheAirStrike                           = 1104,
		soldier_p_WoodlandWarrior                        = 15006,
		soldier_p_SandCannon                             = 15014,
		soldier_p_AmericanPastoral                       = 15028,
		soldier_p_SmalltownBringdown                     = 15043,
		soldier_p_ShellShocker                           = 15052,
		soldier_p_AquaMarine                             = 15057,
		soldier_p_Autumn                                 = 15081,
		soldier_p_BlueMew                                = 15104,
		soldier_p_BrainCandy                             = 15105,
		soldier_p_CoffinNail                             = 15129,
		soldier_p_HighRollers                            = 15130,
		soldier_p_Warhawk                                = 15150,
		soldier_s_SoldiersShotgun                        = 10,
		soldier_s_ShotgunR                               = 199,
		soldier_s_TheBuffBanner                          = 129,
		soldier_s_Gunboats                               = 133,
		soldier_s_TheBattalionsBackup                    = 226,
		soldier_s_TheConcheror                           = 354,
		soldier_s_TheReserveShooter                      = 415,
		soldier_s_TheRighteousBison                      = 442,
		soldier_s_TheMantreads                           = 444,
		soldier_s_FestiveBuffBanner                      = 1001,
		soldier_s_TheBASEJumper                          = 1101,
		soldier_s_FestiveShotgun                         = 1141,
		soldier_s_PanicAttack                            = 1153,
		soldier_s_BackwoodsBoomstick                     = 15003,
		soldier_s_RusticRuiner                           = 15016,
		soldier_s_CivicDuty                              = 15044,
		soldier_s_LightningRod                           = 15047,
		soldier_s_Autumn                                 = 15085,
		soldier_s_FlowerPower                            = 15109,
		soldier_s_CoffinNail                             = 15132,
		soldier_s_DressedtoKill                          = 15133,
		soldier_s_RedBear                                = 15152,
		soldier_m_Shovel                                 = 6,
		soldier_m_ShovelR                                = 196,
		soldier_m_TheEqualizer                           = 128,
		soldier_m_ThePainTrain                           = 154,
		soldier_m_TheHalfZatoichi                        = 357,
		soldier_m_TheMarketGardener                      = 416,
		soldier_m_TheDisciplinaryAction                  = 447,
		soldier_m_TheConscientiousObjector               = 474,
		soldier_m_TheEscapePlan                          = 775,
		soldier_m_TheFreedomStaff                        = 880,
		soldier_m_TheBatOuttaHell                        = 939,
		soldier_m_TheMemoryMaker                         = 954,
		soldier_m_TheHamShank                            = 1013,
		soldier_m_TheNecroSmasher                        = 1123,
		soldier_m_TheCrossingGuard                       = 1127,
		soldier_m_PrinnyMachete                          = 30758,
		pyro_p_FlameThrower                              = 21,
		pyro_p_FlameThrowerR                             = 208,
		pyro_p_TheBackburner                             = 40,
		pyro_p_TheDegreaser                              = 215,
		pyro_p_ThePhlogistinator                         = 594,
		pyro_p_FestiveFlameThrower                       = 659,
		pyro_p_TheRainblower                             = 741,
		pyro_p_SilverBotkillerFlameThrowerMkI            = 798,
		pyro_p_GoldBotkillerFlameThrowerMkI              = 807,
		pyro_p_RustBotkillerFlameThrowerMkI              = 887,
		pyro_p_BloodBotkillerFlameThrowerMkI             = 896,
		pyro_p_CarbonadoBotkillerFlameThrowerMkI         = 905,
		pyro_p_DiamondBotkillerFlameThrowerMkI           = 914,
		pyro_p_SilverBotkillerFlameThrowerMkII           = 963,
		pyro_p_GoldBotkillerFlameThrowerMkII             = 972,
		pyro_p_FestiveBackburner                         = 1146,
		pyro_p_DragonsFury                               = 1178,
		pyro_p_ForestFire                                = 15005,
		pyro_p_BarnBurner                                = 15017,
		pyro_p_BovineBlazemaker                          = 15030,
		pyro_p_EarthSkyandFire                           = 15034,
		pyro_p_FlashFryer                                = 15049,
		pyro_p_TurbineTorcher                            = 15054,
		pyro_p_Autumn                                    = 15066,
		pyro_p_PumpkinPatch                              = 15067,
		pyro_p_Nutcracker                                = 15068,
		pyro_p_Balloonicorn                              = 15089,
		pyro_p_Rainbow                                   = 15090,
		pyro_p_CoffinNail                                = 15115,
		pyro_p_Warhawk                                   = 15141,
		pyro_p_NostromoNapalmer                          = 30474,
		pyro_s_PyrosShotgun                              = 12,
		pyro_s_ShotgunR                                  = 199,
		pyro_s_TheFlareGun                               = 39,
		pyro_s_TheDetonator                              = 351,
		pyro_s_TheReserveShooter                         = 415,
		pyro_s_TheManmelter                              = 595,
		pyro_s_TheScorchShot                             = 740,
		pyro_s_FestiveFlareGun                           = 1081,
		pyro_s_FestiveShotgun                            = 1141,
		pyro_s_PanicAttack                               = 1153,
		pyro_s_ThermalThruster                           = 1179,
		pyro_s_GasPasser                                 = 1180,
		pyro_s_BackwoodsBoomstick                        = 15003,
		pyro_s_RusticRuiner                              = 15016,
		pyro_s_CivicDuty                                 = 15044,
		pyro_s_LightningRod                              = 15047,
		pyro_s_Autumn                                    = 15085,
		pyro_s_FlowerPower                               = 15109,
		pyro_s_CoffinNail                                = 15132,
		pyro_s_DressedtoKill                             = 15133,
		pyro_s_RedBear                                   = 15152,
		pyro_m_FireAxe                                   = 2,
		pyro_m_FireAxeR                                  = 192,
		pyro_m_TheAxtinguisher                           = 38,
		pyro_m_Homewrecker                               = 153,
		pyro_m_ThePowerjack                              = 214,
		pyro_m_TheBackScratcher                          = 326,
		pyro_m_SharpenedVolcanoFragment                  = 348,
		pyro_m_ThePostalPummeler                         = 457,
		pyro_m_TheMaul                                   = 466,
		pyro_m_TheConscientiousObjector                  = 474,
		pyro_m_TheThirdDegree                            = 593,
		pyro_m_TheLollichop                              = 739,
		pyro_m_NeonAnnihilator                           = 813,
		pyro_m_NeonAnnihilatorG                          = 834,
		pyro_m_TheFreedomStaff                           = 880,
		pyro_m_TheBatOuttaHell                           = 939,
		pyro_m_TheMemoryMaker                            = 954,
		pyro_m_TheFestiveAxtinguisher                    = 1000,
		pyro_m_TheHamShank                               = 1013,
		pyro_m_TheNecroSmasher                           = 1123,
		pyro_m_TheCrossingGuard                          = 1127,
		pyro_m_HotHand                                   = 1181,
		pyro_m_PrinnyMachete                             = 30758,
		demoman_p_GrenadeLauncher                        = 19,
		demoman_p_GrenadeLauncherR                       = 206,
		demoman_p_TheLochnLoad                           = 308,
		demoman_p_AliBabasWeeBooties                     = 405,
		demoman_p_TheBootlegger                          = 608,
		demoman_p_TheLooseCannon                         = 996,
		demoman_p_FestiveGrenadeLauncher                 = 1007,
		demoman_p_TheBASEJumper                          = 1101,
		demoman_p_TheIronBomber                          = 1151,
		demoman_p_Autumn                                 = 15077,
		demoman_p_MacabreWeb                             = 15079,
		demoman_p_Rainbow                                = 15091,
		demoman_p_SweetDreams                            = 15092,
		demoman_p_CoffinNail                             = 15116,
		demoman_p_TopShelf                               = 15117,
		demoman_p_Warhawk                                = 15142,
		demoman_p_ButcherBird                            = 15158,
		demoman_s_StickybombLauncher                     = 20,
		demoman_s_StickybombLauncherR                    = 207,
		demoman_s_TheScottishResistance                  = 130,
		demoman_s_TheCharginTarge                        = 131,
		demoman_s_StickyJumper                           = 265,
		demoman_s_TheSplendidScreen                      = 406,
		demoman_s_FestiveStickybombLauncher              = 661,
		demoman_s_SilverBotkillerStickybombLauncherMkI   = 797,
		demoman_s_GoldBotkillerStickybombLauncherMkI     = 806,
		demoman_s_RustBotkillerStickybombLauncherMkI     = 886,
		demoman_s_BloodBotkillerStickybombLauncherMkI    = 895,
		demoman_s_CarbonadoBotkillerStickybombLauncherMkI= 904,
		demoman_s_DiamondBotkillerStickybombLauncherMkI  = 913,
		demoman_s_SilverBotkillerStickybombLauncherMkII  = 962,
		demoman_s_GoldBotkillerStickybombLauncherMkII    = 971,
		demoman_s_TheTideTurner                          = 1099,
		demoman_s_FestiveTarge                           = 1144,
		demoman_s_TheQuickiebombLauncher                 = 1150,
		demoman_s_SuddenFlurry                           = 15009,
		demoman_s_CarpetBomber                           = 15012,
		demoman_s_BlastedBombardier                      = 15024,
		demoman_s_RooftopWrangler                        = 15038,
		demoman_s_LiquidAsset                            = 15045,
		demoman_s_PinkElephant                           = 15048,
		demoman_s_Autumn                                 = 15082,
		demoman_s_PumpkinPatch                           = 15083,
		demoman_s_MacabreWeb                             = 15084,
		demoman_s_SweetDreams                            = 15113,
		demoman_s_CoffinNail                             = 15137,
		demoman_s_DressedtoKill                          = 15138,
		demoman_s_Blitzkrieg                             = 15155,
		demoman_m_Bottle                                 = 1,
		demoman_m_BottleR                                = 191,
		demoman_m_TheEyelander                           = 132,
		demoman_m_ThePainTrain                           = 154,
		demoman_m_TheScotsmansSkullcutter                = 172,
		demoman_m_HorselessHeadlessHorsemannsHeadtaker   = 266,
		demoman_m_UllapoolCaber                          = 307,
		demoman_m_TheClaidheamhMor                       = 327,
		demoman_m_TheHalfZatoichi                        = 357,
		demoman_m_ThePersianPersuader                    = 404,
		demoman_m_TheConscientiousObjector               = 474,
		demoman_m_NessiesNineIron                        = 482,
		demoman_m_TheScottishHandshake                   = 609,
		demoman_m_TheFreedomStaff                        = 880,
		demoman_m_TheBatOuttaHell                        = 939,
		demoman_m_TheMemoryMaker                         = 954,
		demoman_m_TheHamShank                            = 1013,
		demoman_m_FestiveEyelander                       = 1082,
		demoman_m_TheNecroSmasher                        = 1123,
		demoman_m_TheCrossingGuard                       = 1127,
		demoman_m_PrinnyMachete                          = 30758,
		heavy_p_Minigun                                  = 15,
		heavy_p_MinigunR                                 = 202,
		heavy_p_Natascha                                 = 41,
		heavy_p_IronCurtain                              = 298,
		heavy_p_TheBrassBeast                            = 312,
		heavy_p_Tomislav                                 = 424,
		heavy_p_FestiveMinigun                           = 654,
		heavy_p_SilverBotkillerMinigunMkI                = 793,
		heavy_p_GoldBotkillerMinigunMkI                  = 802,
		heavy_p_TheHuoLongHeater                         = 811,
		heavy_p_TheHuoLongHeaterG                        = 832,
		heavy_p_Deflector_mvm                            = 850,
		heavy_p_RustBotkillerMinigunMkI                  = 882,
		heavy_p_BloodBotkillerMinigunMkI                 = 891,
		heavy_p_CarbonadoBotkillerMinigunMkI             = 900,
		heavy_p_DiamondBotkillerMinigunMkI               = 909,
		heavy_p_SilverBotkillerMinigunMkII               = 958,
		heavy_p_GoldBotkillerMinigunMkII                 = 967,
		heavy_p_KingoftheJungle                          = 15004,
		heavy_p_IronWood                                 = 15020,
		heavy_p_AntiqueAnnihilator                       = 15026,
		heavy_p_WarRoom                                  = 15031,
		heavy_p_CitizenPain                              = 15040,
		heavy_p_BrickHouse                               = 15055,
		heavy_p_MacabreWeb                               = 15086,
		heavy_p_PumpkinPatch                             = 15087,
		heavy_p_Nutcracker                               = 15088,
		heavy_p_BrainCandy                               = 15098,
		heavy_p_MisterCuddles                            = 15099,
		heavy_p_CoffinNail                               = 15123,
		heavy_p_DressedtoKill                            = 15124,
		heavy_p_TopShelf                                 = 15125,
		heavy_p_ButcherBird                              = 15147,
		heavy_s_HeavysShotgun                            = 11,
		heavy_s_ShotgunR                                 = 199,
		heavy_s_Sandvich                                 = 42,
		heavy_s_TheDalokohsBar                           = 159,
		heavy_s_TheBuffaloSteakSandvich                  = 311,
		heavy_s_TheFamilyBusiness                        = 425,
		heavy_s_Fishcake                                 = 433,
		heavy_s_RoboSandvich                             = 863,
		heavy_s_FestiveSandvich                          = 1002,
		heavy_s_FestiveShotgun                           = 1141,
		heavy_s_PanicAttack                              = 1153,
		heavy_s_SecondBanana                             = 1190,
		heavy_s_BackwoodsBoomstick                       = 15003,
		heavy_s_RusticRuiner                             = 15016,
		heavy_s_CivicDuty                                = 15044,
		heavy_s_LightningRod                             = 15047,
		heavy_s_Autumn                                   = 15085,
		heavy_s_FlowerPower                              = 15109,
		heavy_s_CoffinNail                               = 15132,
		heavy_s_DressedtoKill                            = 15133,
		heavy_s_RedBear                                  = 15152,
		heavy_m_Fists                                    = 5,
		heavy_m_FistsR                                   = 195,
		heavy_m_TheKillingGlovesofBoxing                 = 43,
		heavy_m_GlovesofRunningUrgently                  = 239,
		heavy_m_WarriorsSpirit                           = 310,
		heavy_m_FistsofSteel                             = 331,
		heavy_m_TheEvictionNotice                        = 426,
		heavy_m_TheConscientiousObjector                 = 474,
		heavy_m_ApocoFists                               = 587,
		heavy_m_TheHolidayPunch                          = 656,
		heavy_m_TheFreedomStaff                          = 880,
		heavy_m_TheBatOuttaHell                          = 939,
		heavy_m_TheMemoryMaker                           = 954,
		heavy_m_TheHamShank                              = 1013,
		heavy_m_FestiveGlovesofRunningUrgently           = 1084,
		heavy_m_TheBreadBite                             = 1100,
		heavy_m_TheNecroSmasher                          = 1123,
		heavy_m_TheCrossingGuard                         = 1127,
		heavy_m_GlovesofRunningUrgentlyMvM               = 1184,
		heavy_m_PrinnyMachete                            = 30758,
		engi_p_EngineersShotgun                          = 9,
		engi_p_ShotgunR                                  = 199,
		engi_p_TheFrontierJustice                        = 141,
		engi_p_TheWidowmaker                             = 527,
		engi_p_ThePomson6000                             = 588,
		engi_p_TheRescueRanger                           = 997,
		engi_p_FestiveFrontierJustice                    = 1004,
		engi_p_FestiveShotgun                            = 1141,
		engi_p_PanicAttack                               = 1153,
		engi_p_BackwoodsBoomstick                        = 15003,
		engi_p_RusticRuiner                              = 15016,
		engi_p_CivicDuty                                 = 15044,
		engi_p_LightningRod                              = 15047,
		engi_p_Autumn                                    = 15085,
		engi_p_FlowerPower                               = 15109,
		engi_p_CoffinNail                                = 15132,
		engi_p_DressedtoKill                             = 15133,
		engi_p_RedBear                                   = 15152,
		engi_s_EngineersPistol                           = 22,
		engi_s_PistolR                                   = 209,
		engi_s_TheWrangler                               = 140,
		engi_s_VintageLugermorph                         = 160,
		engi_s_Lugermorph                                = 294,
		engi_s_TheShortCircuit                           = 528,
		engi_s_FestiveWrangler                           = 1086,
		engi_s_RedRockRoscoe                             = 15013,
		engi_s_HomemadeHeater                            = 15018,
		engi_s_HickoryHolepuncher                        = 15035,
		engi_s_LocalHero                                 = 15041,
		engi_s_BlackDahlia                               = 15046,
		engi_s_SandstoneSpecial                          = 15056,
		engi_s_MacabreWeb                                = 15060,
		engi_s_Nutcracker                                = 15061,
		engi_s_BlueMew                                   = 15100,
		engi_s_BrainCandy                                = 15101,
		engi_s_ShottoHell                                = 15102,
		engi_s_DressedToKill                             = 15126,
		engi_s_Blitzkrieg                                = 15148,
		engi_s_TheCAPPER                                 = 30666,
		engi_s_TheGigarCounter                           = 30668,
		engi_m_Wrench                                    = 7,
		engi_m_WrenchR                                   = 197,
		engi_m_TheGunslinger                             = 142,
		engi_m_TheSouthernHospitality                    = 155,
		engi_m_GoldenWrench                              = 169,
		engi_m_TheJag                                    = 329,
		engi_m_TheEurekaEffect                           = 589,
		engi_m_FestiveWrench                             = 662,
		engi_m_SilverBotkillerWrenchMkI                  = 795,
		engi_m_GoldBotkillerWrenchMkI                    = 804,
		engi_m_RustBotkillerWrenchMkI                    = 884,
		engi_m_BloodBotkillerWrenchMkI                   = 893,
		engi_m_CarbonadoBotkillerWrenchMkI               = 902,
		engi_m_DiamondBotkillerWrenchMkI                 = 911,
		engi_m_SilverBotkillerWrenchMkII                 = 960,
		engi_m_GoldBotkillerWrenchMkII                   = 969,
		engi_m_TheNecroSmasher                           = 1123,
		engi_m_Nutcracker                                = 15073,
		engi_m_Autumn                                    = 15074,
		engi_m_Boneyard                                  = 15075,
		engi_m_DressedtoKill                             = 15139,
		engi_m_TopShelf                                  = 15140,
		engi_m_TorquedtoHell                             = 15114,
		engi_m_Airwolf                                   = 15156,
		engi_m_PrinnyMachete                             = 30758,
		engi_p_ConstructionPDA                           = 25,
		engi_p_ConstructionPDAR                          = 737,
		engi_p_DestructionPDA                            = 26,
		engi_p_PDA                                       = 28,
		medic_p_SyringeGun                               = 17,
		medic_p_SyringeGunR                              = 204,
		medic_p_TheBlutsauger                            = 36,
		medic_p_CrusadersCrossbow                        = 305,
		medic_p_TheOverdose                              = 412,
		medic_p_FestiveCrusadersCrossbow                 = 1079,
		medic_s_MediGun                                  = 29,
		medic_s_MediGunR                                 = 211,
		medic_s_TheKritzkrieg                            = 35,
		medic_s_TheQuickFix                              = 411,
		medic_s_FestiveMediGun                           = 663,
		medic_s_SilverBotkillerMediGunMkI                = 796,
		medic_s_GoldBotkillerMediGunMkI                  = 805,
		medic_s_RustBotkillerMediGunMkI                  = 885,
		medic_s_BloodBotkillerMediGunMkI                 = 894,
		medic_s_CarbonadoBotkillerMediGunMkI             = 903,
		medic_s_DiamondBotkillerMediGunMkI               = 912,
		medic_s_SilverBotkillerMediGunMkII               = 961,
		medic_s_GoldBotkillerMediGunMkII                 = 970,
		medic_s_TheVaccinator                            = 998,
		medic_s_MaskedMender                             = 15008,
		medic_s_WrappedReviver                           = 15010,
		medic_s_ReclaimedReanimator                      = 15025,
		medic_s_CivilServant                             = 15039,
		medic_s_SparkofLife                              = 15050,
		medic_s_Wildwood                                 = 15078,
		medic_s_FlowerPower                              = 15097,
		medic_s_DressedToKill                            = 15121,
		medic_s_HighRollers                              = 15122,
		medic_s_CoffinNail                               = 15123,
		medic_s_Blitzkrieg                               = 15145,
		medic_s_Corsair                                  = 15146,
		medic_m_Bonesaw                                  = 8,
		medic_m_BonesawR                                 = 198,
		medic_m_TheUbersaw                               = 37,
		medic_m_TheVitaSaw                               = 173,
		medic_m_Amputator                                = 304,
		medic_m_TheSolemnVow                             = 413,
		medic_m_TheConscientiousObjector                 = 474,
		medic_m_TheFreedomStaff                          = 880,
		medic_m_TheBatOuttaHell                          = 939,
		medic_m_TheMemoryMaker                           = 954,
		medic_m_FestiveUbersaw                           = 1003,
		medic_m_TheHamShank                              = 1013,
		medic_m_TheNecroSmasher                          = 1123,
		medic_m_TheCrossingGuard                         = 1127,
		medic_m_FestiveBonesaw                           = 1143,
		medic_m_PrinnyMachete                            = 30758,
		sniper_p_SniperRifle                             = 14,
		sniper_p_SniperRifleR                            = 201,
		sniper_p_TheHuntsman                             = 56,
		sniper_p_TheSydneySleeper                        = 230,
		sniper_p_TheBazaarBargain                        = 402,
		sniper_p_TheMachina                              = 526,
		sniper_p_FestiveSniperRifle                      = 664,
		sniper_p_TheHitmansHeatmaker                     = 752,
		sniper_p_SilverBotkillerSniperRifleMkI           = 792,
		sniper_p_GoldBotkillerSniperRifleMkI             = 801,
		sniper_p_TheAWPerHand                            = 851,
		sniper_p_RustBotkillerSniperRifleMkI             = 881,
		sniper_p_BloodBotkillerSniperRifleMkI            = 890,
		sniper_p_CarbonadoBotkillerSniperRifleMkI        = 899,
		sniper_p_DiamondBotkillerSniperRifleMkI          = 908,
		sniper_p_SilverBotkillerSniperRifleMkII          = 957,
		sniper_p_GoldBotkillerSniperRifleMkII            = 966,
		sniper_p_FestiveHuntsman                         = 1005,
		sniper_p_TheFortifiedCompound                    = 1092,
		sniper_p_TheClassic                              = 1098,
		sniper_p_NightOwl                                = 15000,
		sniper_p_PurpleRange                             = 15007,
		sniper_p_LumberFromDownUnder                     = 15019,
		sniper_p_ShotintheDark                           = 15023,
		sniper_p_Bogtrotter                              = 15033,
		sniper_p_Thunderbolt                             = 15059,
		sniper_p_PumpkinPatch                            = 15070,
		sniper_p_Boneyard                                = 15071,
		sniper_p_Wildwood                                = 15072,
		sniper_p_Balloonicorn                            = 15111,
		sniper_p_Rainbow                                 = 15112,
		sniper_p_CoffinNail                              = 15135,
		sniper_p_DressedtoKill                           = 15136,
		sniper_p_Airwolf                                 = 15154,
		sniper_p_ShootingStar                            = 30665,
		sniper_s_SMG                                     = 16,
		sniper_s_SMGR                                    = 203,
		sniper_s_TheRazorback                            = 57,
		sniper_s_Jarate                                  = 58,
		sniper_s_DarwinsDangerShield                     = 231,
		sniper_s_CozyCamper                              = 642,
		sniper_s_TheCleanersCarbine                      = 751,
		sniper_s_FestiveJarate                           = 1083,
		sniper_s_TheSelfAwareBeautyMark                  = 1105,
		sniper_s_FestiveSMG                              = 1149,
		sniper_s_WoodsyWidowmaker                        = 15001,
		sniper_s_PlaidPotshotter                         = 15022,
		sniper_s_TreadplateTormenter                     = 15032,
		sniper_s_TeamSprayer                             = 15037,
		sniper_s_LowProfile                              = 15058,
		sniper_s_Wildwood                                = 15076,
		sniper_s_BlueMew                                 = 15110,
		sniper_s_HighRollers                             = 15134,
		sniper_s_Blitzkrieg                              = 15153,
		sniper_m_Kukri                                   = 3,
		sniper_m_KukriR                                  = 193,
		sniper_m_TheTribalmansShiv                       = 171,
		sniper_m_TheBushwacka                            = 232,
		sniper_m_TheShahanshah                           = 401,
		sniper_m_TheConscientiousObjector                = 474,
		sniper_m_TheFreedomStaff                         = 880,
		sniper_m_TheBatOuttaHell                         = 939,
		sniper_m_TheMemoryMaker                          = 954,
		sniper_m_TheHamShank                             = 1013,
		sniper_m_TheNecroSmasher                         = 1123,
		sniper_m_TheCrossingGuard                        = 1127,
		sniper_m_PrinnyMachete                           = 30758,
		spy_p_Revolver                                   = 24,
		spy_p_RevolverR                                  = 210,
		spy_p_TheAmbassador                              = 61,
		spy_p_BigKill                                    = 161,
		spy_p_LEtranger                                  = 224,
		spy_p_TheEnforcer                                = 460,
		spy_p_TheDiamondback                             = 525,
		spy_p_FestiveAmbassador                          = 1006,
		spy_p_FestiveRevolver                            = 1142,
		spy_p_PsychedelicSlugger                         = 15011,
		spy_p_OldCountry                                 = 15027,
		spy_p_Mayor                                      = 15042,
		spy_p_DeadReckoner                               = 15051,
		spy_p_Boneyard                                   = 15062,
		spy_p_Wildwood                                   = 15063,
		spy_p_MacabreWeb                                 = 15064,
		spy_p_FlowerPower                                = 15103,
		spy_p_TopShelf                                   = 15128,
		spy_p_CoffinNail                                 = 15129,
		spy_p_Blitzkrieg                                 = 15149,
		spy_s_Sapper                                     = 735,
		spy_s_SapperR                                    = 736,
		spy_s_TheRedTapeRecorder                         = 810,
		spy_s_TheRedTapeRecorderG                        = 831,
		spy_s_TheApSapG                                  = 933,
		spy_s_FestiveSapper                              = 1080,
		spy_s_TheSnackAttack                             = 1102,
		spy_m_Knife                                      = 4,
		spy_m_KnifeR                                     = 194,
		spy_m_YourEternalReward                          = 225,
		spy_m_ConniversKunai                             = 356,
		spy_m_TheBigEarner                               = 461,
		spy_m_TheWangaPrick                              = 574,
		spy_m_TheSharpDresser                            = 638,
		spy_m_TheSpycicle                                = 649,
		spy_m_FestiveKnife                               = 665,
		spy_m_TheBlackRose                               = 727,
		spy_m_SilverBotkillerKnifeMkI                    = 794,
		spy_m_GoldBotkillerKnifeMkI                      = 803,
		spy_m_RustBotkillerKnifeMkI                      = 883,
		spy_m_BloodBotkillerKnifeMkI                     = 892,
		spy_m_CarbonadoBotkillerKnifeMkI                 = 901,
		spy_m_DiamondBotkillerKnifeMkI                   = 910,
		spy_m_SilverBotkillerKnifeMkII                   = 959,
		spy_m_GoldBotkillerKnifeMkII                     = 968,
		spy_m_Boneyard                                   = 15062,
		spy_m_BlueMew                                    = 15094,
		spy_m_BrainCandy                                 = 15095,
		spy_m_StabbedtoHell                              = 15096,
		spy_m_DressedtoKill                              = 15118,
		spy_m_TopShelf                                   = 15119,
		spy_m_Blitzkrieg                                 = 15143,
		spy_m_Airwolf                                    = 15144,
		spy_m_PrinnyMachete                              = 30758,
		spy_d_DisguiseKitPDA                             = 27,
		spy_w_InvisWatch                                 = 30,
		spy_w_InvisWatchR                                = 212,
		spy_w_TheDeadRinger                              = 59,
		spy_w_TheCloakandDagger                          = 60,
		spy_w_EnthusiastsTimepiece                       = 297,
		spy_w_TheQuackenbirdt                            = 947,
		misc_m_FryingPan                                 = 264,
		misc_m_GoldFryingPan                             = 1071,
		misc_m_Saxxy                                     = 423
	};

	enum playerControls
	{
		in_attack		= (1 << 0),
		in_jump			= (1 << 1),
		in_duck			= (1 << 2),
		in_forward		= (1 << 3),
		in_back			= (1 << 4),
		in_use			= (1 << 5),
		in_cancel		= (1 << 6),
		in_left			= (1 << 7),
		in_right		= (1 << 8),
		in_moveleft		= (1 << 9),
		in_moveright	= (1 << 10),
		in_attack2		= (1 << 11),
		in_run			= (1 << 12),
		in_reload		= (1 << 13),
		in_alt1			= (1 << 14),
		in_alt2			= (1 << 15),
		in_score		= (1 << 16),
		in_speed		= (1 << 17),
		in_walk			= (1 << 18),
		in_zoom			= (1 << 19),
		in_weapon1		= (1 << 20),
		in_weapon2		= (1 << 21),
		in_bullrush		= (1 << 22)
	};

	enum entityClasses
	{
		CAI_BaseNPC                          = 0,
		CBaseAnimating                       = 1,
		CBaseAnimatingOverlay                = 2,
		CBaseAttributableItem                = 3,
		CBaseCombatCharacter                 = 4,
		CBaseCombatWeaponEx                  = 5,
		CBaseDoor                            = 6,
		CBaseEntityEx                        = 7,
		CBaseFlex                            = 8,
		CBaseGrenade                         = 9,
		CBaseObjectEx                        = 10,
		CBaseObjectUpgrade                   = 11,
		CBaseParticleEntity                  = 12,
		CBasePlayerEx                        = 13,
		CBaseProjectile                      = 14,
		CBasePropDoor                        = 15,
		CBaseTeamObjectiveResource           = 16,
		CBaseTempEntity                      = 17,
		CBaseViewModel                       = 18,
		CBeam                                = 19,
		CBoneFollower                        = 20,
		CBonusDuckPickup                     = 21,
		CBonusPack                           = 22,
		CBonusRoundLogic                     = 23,
		CBreakableProp                       = 24,
		CBreakableSurface                    = 25,
		CCaptureFlag                         = 26,
		CCaptureFlagReturnIcon               = 27,
		CCaptureZone                         = 28,
		CColorCorrection                     = 29,
		CColorCorrectionVolume               = 30,
		CCurrencyPack                        = 31,
		CDynamicLight                        = 32,
		CDynamicProp                         = 33,
		CEconEntity                          = 34,
		CEconWearable                        = 35,
		CEmbers                              = 36,
		CEntityDissolve                      = 37,
		CEntityFlame                         = 38,
		CEntityParticleTrail                 = 39,
		CEnvDetailController                 = 40,
		CEnvParticleScript                   = 41,
		CEnvProjectedTexture                 = 42,
		CEnvQuadraticBeam                    = 43,
		CEnvScreenEffect                     = 44,
		CEnvScreenOverlay                    = 45,
		CEnvTonemapController                = 46,
		CEnvWind                             = 47,
		CEyeballBoss                         = 48,
		CFireSmoke                           = 49,
		CFireTrail                           = 50,
		CFish                                = 51,
		CFogController                       = 52,
		CFuncAreaPortalWindow                = 55,
		CFuncConveyor                        = 56,
		CFuncForceField                      = 57,
		CFuncLadder                          = 58,
		CFuncMonitor                         = 59,
		CFuncOccluder                        = 60,
		CFuncPasstimeGoal                    = 61,
		CFuncReflectiveGlass                 = 62,
		CFuncRespawnRoom                     = 63,
		CFuncRespawnRoomVisualizer           = 64,
		CFuncRotating                        = 65,
		CFuncSmokeVolume                     = 66,
		CFuncTrackTrain                      = 67,
		CFunc_Dust                           = 53,
		CFunc_LOD                            = 54,
		CGameRulesProxy                      = 68,
		CHalloweenGiftPickup                 = 69,
		CHalloweenPickup                     = 70,
		CHalloweenSoulPack                   = 71,
		CHandleTest                          = 72,
		CHeadlessHatman                      = 73,
		CHightower_TeleportVortex            = 74,
		CInfoLadderDismount                  = 75,
		CInfoLightingRelative                = 76,
		CInfoOverlayAccessor                 = 77,
		CLaserDot                            = 78,
		CLightGlow                           = 79,
		CMannVsMachineStats                  = 80,
		CMaterialModifyControl               = 81,
		CMerasmus                            = 82,
		CMerasmusDancer                      = 83,
		CMonsterResource                     = 84,
		CObjectCartDispenser                 = 85,
		CObjectDispenser                     = 86,
		CObjectSapper                        = 87,
		CObjectSentrygun                     = 88,
		CObjectTeleporter                    = 89,
		CParticleFire                        = 90,
		CParticlePerformanceMonitor          = 91,
		CParticleSystem                      = 92,
		CPasstimeBall                        = 93,
		CPasstimeGun                         = 94,
		CPhysBox                             = 95,
		CPhysBoxMultiplayer                  = 96,
		CPhysMagnet                          = 99,
		CPhysicsProp                         = 97,
		CPhysicsPropMultiplayer              = 98,
		CPlasma                              = 100,
		CPlayerDestructionDispenser          = 101,
		CPlayerResource                      = 102,
		CPointCamera                         = 103,
		CPointCommentaryNode                 = 104,
		CPoseController                      = 105,
		CPrecipitation                       = 106,
		CPropVehicleDriveable                = 107,
		CRagdollManager                      = 108,
		CRagdollProp                         = 109,
		CRagdollPropAttached                 = 110,
		CRobotDispenser                      = 111,
		CRopeKeyframe                        = 112,
		CSceneEntity                         = 113,
		CShadowControl                       = 114,
		CSlideshowDisplay                    = 115,
		CSmokeStack                          = 116,
		CSniperDot                           = 117,
		CSpotlightEnd                        = 118,
		CSprite                              = 119,
		CSpriteOriented                      = 120,
		CSpriteTrail                         = 121,
		CSteamJet                            = 122,
		CSun                                 = 123,
		CTEArmorRicochet                     = 128,
		CTEBSPDecal                          = 141,
		CTEBaseBeam                          = 129,
		CTEBeamEntPoint                      = 130,
		CTEBeamEnts                          = 131,
		CTEBeamFollow                        = 132,
		CTEBeamLaser                         = 133,
		CTEBeamPoints                        = 134,
		CTEBeamRing                          = 135,
		CTEBeamRingPoint                     = 136,
		CTEBeamSpline                        = 137,
		CTEBloodSprite                       = 138,
		CTEBloodStream                       = 139,
		CTEBreakModel                        = 140,
		CTEBubbleTrail                       = 143,
		CTEBubbles                           = 142,
		CTEClientProjectile                  = 144,
		CTEDecal                             = 145,
		CTEDust                              = 146,
		CTEDynamicLight                      = 147,
		CTEEffectDispatch                    = 148,
		CTEEnergySplash                      = 149,
		CTEExplosion                         = 150,
		CTEFireBullets                       = 151,
		CTEFizz                              = 152,
		CTEFootprintDecal                    = 153,
		CTEGaussExplosion                    = 154,
		CTEGlowSprite                        = 155,
		CTEImpact                            = 156,
		CTEKillPlayerAttachments             = 157,
		CTELargeFunnel                       = 158,
		CTEMetalSparks                       = 160,
		CTEMuzzleFlash                       = 161,
		CTEParticleSystem                    = 162,
		CTEPhysicsProp                       = 163,
		CTEPlayerAnimEvent                   = 164,
		CTEPlayerDecal                       = 165,
		CTEProjectedDecal                    = 166,
		CTEShatterSurface                    = 167,
		CTEShowLine                          = 168,
		CTESmoke                             = 170,
		CTESparks                            = 171,
		CTESprite                            = 172,
		CTESpriteSpray                       = 173,
		CTETFBlood                           = 176,
		CTETFExplosion                       = 177,
		CTETFParticleEffect                  = 178,
		CTEWorldDecal                        = 179,
		CTFAmmoPack                          = 180,
		CTFBall_Ornament                     = 181,
		CTFBaseBoss                          = 182,
		CTFBaseProjectile                    = 183,
		CTFBaseRocket                        = 184,
		CTFBat                               = 185,
		CTFBat_Fish                          = 186,
		CTFBat_Giftwrap                      = 187,
		CTFBat_Wood                          = 188,
		CTFBonesaw                           = 189,
		CTFBotHintEngineerNest               = 190,
		CTFBottle                            = 191,
		CTFBreakableMelee                    = 192,
		CTFBreakableSign                     = 193,
		CTFBuffItem                          = 194,
		CTFCannon                            = 195,
		CTFChargedSMG                        = 196,
		CTFCleaver                           = 197,
		CTFClub                              = 198,
		CTFCompoundBow                       = 199,
		CTFCrossbow                          = 200,
		CTFDRGPomson                         = 201,
		CTFDroppedWeapon                     = 202,
		CTFFireAxe                           = 203,
		CTFFists                             = 204,
		CTFFlameManager                      = 205,
		CTFFlameRocket                       = 206,
		CTFFlameThrower                      = 207,
		CTFFlareGun                          = 208,
		CTFFlareGun_Revenge                  = 209,
		CTFGameRulesProxy                    = 210,
		CTFGasManager                        = 211,
		CTFGenericBomb                       = 212,
		CTFGlow                              = 213,
		CTFGrapplingHook                     = 214,
		CTFGrenadeLauncher                   = 215,
		CTFGrenadePipebombProjectile         = 216,
		CTFHalloweenMinigame                 = 217,
		CTFHalloweenMinigame_FallingPlatforms= 218,
		CTFHellZap                           = 219,
		CTFItem                              = 220,
		CTFJar                               = 221,
		CTFJarGas                            = 222,
		CTFJarMilk                           = 223,
		CTFKatana                            = 224,
		CTFKnife                             = 225,
		CTFLaserPointer                      = 226,
		CTFLunchBox                          = 227,
		CTFLunchBox_Drink                    = 228,
		CTFMechanicalArm                     = 229,
		CTFMedigunShield                     = 230,
		CTFMiniGame                          = 231,
		CTFMinigameLogic                     = 232,
		CTFMinigun                           = 233,
		CTFObjectiveResource                 = 234,
		CTFPEPBrawlerBlaster                 = 240,
		CTFParachute                         = 235,
		CTFParachute_Primary                 = 236,
		CTFParachute_Secondary               = 237,
		CTFParticleCannon                    = 238,
		CTFPasstimeLogic                     = 239,
		CTFPipebombLauncher                  = 241,
		CTFPistol                            = 242,
		CTFPistol_Scout                      = 243,
		CTFPistol_ScoutPrimary               = 244,
		CTFPistol_ScoutSecondary             = 245,
		CTFPlayer                            = 246,
		CTFPlayerDestructionLogic            = 247,
		CTFPlayerResource                    = 248,
		CTFPointManager                      = 249,
		CTFPowerupBottle                     = 250,
		CTFProjectile_Arrow                  = 251,
		CTFProjectile_BallOfFire             = 252,
		CTFProjectile_Cleaver                = 253,
		CTFProjectile_EnergyBall             = 254,
		CTFProjectile_EnergyRing             = 255,
		CTFProjectile_Flare                  = 256,
		CTFProjectile_GrapplingHook          = 257,
		CTFProjectile_HealingBolt            = 258,
		CTFProjectile_Jar                    = 259,
		CTFProjectile_JarGas                 = 260,
		CTFProjectile_JarMilk                = 261,
		CTFProjectile_MechanicalArmOrb       = 262,
		CTFProjectile_Rocket                 = 263,
		CTFProjectile_SentryRocket           = 264,
		CTFProjectile_SpellBats              = 265,
		CTFProjectile_SpellFireball          = 266,
		CTFProjectile_SpellKartBats          = 267,
		CTFProjectile_SpellKartOrb           = 268,
		CTFProjectile_SpellLightningOrb      = 269,
		CTFProjectile_SpellMeteorShower      = 270,
		CTFProjectile_SpellMirv              = 271,
		CTFProjectile_SpellPumpkin           = 272,
		CTFProjectile_SpellSpawnBoss         = 273,
		CTFProjectile_SpellSpawnHorde        = 274,
		CTFProjectile_SpellSpawnZombie       = 275,
		CTFProjectile_SpellTransposeTeleport = 276,
		CTFProjectile_Throwable              = 277,
		CTFProjectile_ThrowableBreadMonster  = 278,
		CTFProjectile_ThrowableBrick         = 279,
		CTFProjectile_ThrowableRepel         = 280,
		CTFPumpkinBomb                       = 281,
		CTFRagdoll                           = 282,
		CTFRaygun                            = 283,
		CTFReviveMarker                      = 284,
		CTFRevolver                          = 285,
		CTFRobotArm                          = 286,
		CTFRobotDestructionLogic             = 290,
		CTFRobotDestruction_Robot            = 287,
		CTFRobotDestruction_RobotGroup       = 288,
		CTFRobotDestruction_RobotSpawn       = 289,
		CTFRocketLauncher                    = 291,
		CTFRocketLauncher_AirStrike          = 292,
		CTFRocketLauncher_DirectHit          = 293,
		CTFRocketLauncher_Mortar             = 294,
		CTFRocketPack                        = 295,
		CTFSMG                               = 305,
		CTFScatterGun                        = 296,
		CTFShotgun                           = 297,
		CTFShotgunBuildingRescue             = 302,
		CTFShotgun_HWG                       = 298,
		CTFShotgun_Pyro                      = 299,
		CTFShotgun_Revenge                   = 300,
		CTFShotgun_Soldier                   = 301,
		CTFShovel                            = 303,
		CTFSlap                              = 304,
		CTFSniperRifle                       = 306,
		CTFSniperRifleClassic                = 307,
		CTFSniperRifleDecap                  = 308,
		CTFSodaPopper                        = 309,
		CTFSpellBook                         = 310,
		CTFStickBomb                         = 311,
		CTFStunBall                          = 312,
		CTFSword                             = 313,
		CTFSyringeGun                        = 314,
		CTFTankBoss                          = 315,
		CTFTauntProp                         = 316,
		CTFTeam                              = 317,
		CTFThrowable                         = 318,
		CTFViewModel                         = 319,
		CTFWeaponBase                        = 320,
		CTFWeaponBaseGrenadeProj             = 321,
		CTFWeaponBaseGun                     = 322,
		CTFWeaponBaseMelee                   = 323,
		CTFWeaponBaseMerasmusGrenade         = 324,
		CTFWeaponBuilder                     = 325,
		CTFWeaponFlameBall                   = 326,
		CTFWeaponInvis                       = 327,
		CTFWeaponPDA                         = 328,
		CTFWeaponPDAExpansion_Dispenser      = 332,
		CTFWeaponPDAExpansion_Teleporter     = 333,
		CTFWeaponPDA_Engineer_Build          = 329,
		CTFWeaponPDA_Engineer_Destroy        = 330,
		CTFWeaponPDA_Spy                     = 331,
		CTFWeaponSapper                      = 334,
		CTFWearable                          = 335,
		CTFWearableCampaignItem              = 336,
		CTFWearableDemoShield                = 337,
		CTFWearableItem                      = 338,
		CTFWearableLevelableItem             = 339,
		CTFWearableRazorback                 = 340,
		CTFWearableRobotArm                  = 341,
		CTFWearableVM                        = 342,
		CTFWrench                            = 343,
		CTeam                                = 124,
		CTeamRoundTimer                      = 126,
		CTeamTrainWatcher                    = 127,
		CTeamplayRoundBasedRulesProxy        = 125,
		CTeleportVortex                      = 159,
		CTesla                               = 169,
		CTestTraceline                       = 175,
		CTest_ProxyToggle_Networkable        = 174,
		CVGuiScreen                          = 344,
		CVoteController                      = 345,
		CWaterBullet                         = 346,
		CWaterLODControl                     = 347,
		CWeaponIFMBase                       = 348,
		CWeaponIFMBaseCamera                 = 349,
		CWeaponIFMSteadyCam                  = 350,
		CWeaponMedigun                       = 351,
		CWorld                               = 352,
		CZombie                              = 353,
		DustTrail                            = 354,
		MovieExplosion                       = 355,
		NextBotCombatCharacter               = 356,
		ParticleSmokeGrenade                 = 357,
		RocketTrail                          = 358,
		SmokeTrail                           = 359,
		SporeExplosion                       = 360,
		SporeTrail                           = 361
	};

	enum clientFrameStage
	{
		frame_undefined = -1,
		frame_start,
		frame_net_update_start,
		frame_net_update_postdataupdate_start,
		frame_net_update_postdataupdate_end,
		frame_net_update_end,
		frame_render_start,
		frame_render_end
	};

	enum moveTypes
	{
		movetype_none = 0,
		movetype_isometric,
		movetype_walk,
		movetype_step,
		movetype_fly,
		movetype_flygravity,
		movetype_vphysics,
		movetype_push,
		movetype_noclip,
		movetype_ladder,
		movetype_observer,
		movetype_custom,
		movetype_last = movetype_custom,
		movetype_max_bits = 4
	};

	enum bspFlags
	{
		contents_empty               = 0x0,
		contents_solid               = 0x1,
		contents_window              = 0x2,
		contents_aux                 = 0x4,
		contents_grate               = 0x8,
		contents_slime               = 0x10,
		contents_water               = 0x20,
		contents_blocklos            = 0x40,
		contents_opaque              = 0x80,
		last_visible_contents        = 0x80,
		//all_visible_contents         = (last_visible_contents |= (last_visible_contents - 1)),
		contents_testfogvolume       = 0x100,
		contents_unused              = 0x200,
		contents_unused6             = 0x400,
		contents_team1               = 0x800,
		contents_team2               = 0x1000,
		contents_ignore_nodraw_opaque= 0x2000,
		contents_moveable            = 0x4000,
		contents_areaportal          = 0x8000,
		contents_playerclip          = 0x10000,
		contents_monsterclip         = 0x20000,
		contents_current_0           = 0x40000,
		contents_current_90          = 0x80000,
		contents_current_180         = 0x100000,
		contents_current_270         = 0x200000,
		contents_current_up          = 0x400000,
		contents_current_down        = 0x800000,
		contents_origin              = 0x1000000,
		contents_monster             = 0x2000000,
		contents_debris              = 0x4000000,
		contents_detail              = 0x8000000,
		contents_translucent         = 0x10000000,
		contents_ladder              = 0x20000000,
		contents_hitbox              = 0x40000000,
		surf_light                   = 0x0001,
		surf_sky2d                   = 0x0002,
		surf_sky                     = 0x0004,
		surf_warp                    = 0x0008,
		surf_trans                   = 0x0010,
		surf_noportal                = 0x0020,
		surf_trigger                 = 0x0040,
		surf_nodraw                  = 0x0080,
		surf_hint                    = 0x0100,
		surf_skip                    = 0x0200,
		surf_nolight                 = 0x0400,
		surf_bumplight               = 0x0800,
		surf_noshadows               = 0x1000,
		surf_nodecals                = 0x2000,
		surf_nochop                  = 0x4000,
		surf_hitbox                  = 0x8000,
		mask_all                     = 0xFFFFFFFF,
		mask_solid                   = (contents_solid | contents_moveable | contents_window | contents_monster | contents_grate),
		mask_playersolid             = (contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate),
		mask_npcsolid                = (contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate),
		mask_water                   = (contents_water | contents_moveable | contents_slime),
		mask_opaque                  = (contents_solid | contents_moveable | contents_opaque),
		mask_opaque_and_npcs         = (mask_opaque | contents_monster),
		mask_blocklos                = (contents_solid | contents_moveable | contents_blocklos),
		mask_blocklos_and_npcs       = (mask_blocklos | contents_monster),
		mask_visible                 = (mask_opaque | contents_ignore_nodraw_opaque),
		mask_visible_and_npcs        = (mask_opaque_and_npcs | contents_ignore_nodraw_opaque),
		mask_shot                    = (contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_hitbox),
		mask_shot_hull               = (contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate),
		mask_shot_portal             = (contents_solid | contents_moveable | contents_window | contents_monster),
		mask_solid_brushonly         = (contents_solid | contents_moveable | contents_window | contents_grate),
		mask_playersolid_brushonly   = (contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate),
		mask_npcsolid_brushonly      = (contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate),
		mask_npcworldstatic          = (contents_solid | contents_window | contents_monsterclip | contents_grate),
		mask_splitareaportal         = (contents_water | contents_slime),
		mask_current                 = (contents_current_0 | contents_current_90 | contents_current_180 | contents_current_270 | contents_current_up | contents_current_down),
		mask_deadsolid               = (contents_solid | contents_playerclip | contents_window | contents_grate)
	};

	enum stereoEye
	{
		stereo_eye_mono		= 0,
		stereo_eye_left		= 1,
		stereo_eye_right	= 2,
		stereo_eye_max		= 3
	};

	class viewSetup
	{
	public:
		int			x;
		int			m_nUnscaledX;
		int			y;
		int			m_nUnscaledY;
		int			width;
		int			m_nUnscaledWidth;
		int			height;
		stereoEye m_eStereoEye;
		int			m_nUnscaledHeight;
		bool		m_bOrtho;
		float		m_OrthoLeft;
		float		m_OrthoTop;
		float		m_OrthoRight;
		float		m_OrthoBottom;
		float		fov;
		float		fovViewmodel;
		math::vec3	origin;
		math::vec3	angles;
		float		zNear;
		float		zFar;
		float		zNearViewmodel;
		float		zFarViewmodel;
		bool		m_bRenderToSubrectOfLargerScreen;
		float		m_flAspectRatio;
		bool		m_bOffCenter;
		float		m_flOffCenterTop;
		float		m_flOffCenterBottom;
		float		m_flOffCenterLeft;
		float		m_flOffCenterRight;
		bool		m_bDoBloomAndToneMapping;
		bool		m_bCacheFullSceneState;
		bool        m_bViewToProjectionOverride;
		void		*m_ViewToProjection;
	};

	enum observerModes
	{
		obs_mode_none = 0,		// not in spectator mode
		obs_mode_deathcam,		// special mode for death cam animation
		obs_mode_freezecam,		// zooms to a target, and freeze-frames on them
		obs_mode_fixed,			// view from a fixed camera position
		obs_mode_firstperson,	// follow a player in first person view
		obs_mode_thirdperson,	// follow a player in third person view
		obs_mode_roaming		// free roaming
	};

	enum effectFlags
	{
		ef_bonemerge			= 0x1,
		ef_brightlight			= 0x2,
		ef_dimlight				= 0x4,
		ef_noshadow				= 0x10,
		ef_nodraw				= 0x20,
		ef_bonemerge_fastcull	= 0x80,
		ef_item_blink			= 0x100,
		ef_parent_animates		= 0x200
	};

	struct playerInfo
	{
		char			name[32];
		int				user_id;
		char			guid[33];
		unsigned long	friends_id;
		char			friends_name[32];
		bool			fakeplayer;
		bool			ishltv;
		unsigned long	custom_files[4];
		unsigned char	files_downloaded;
	};

	class clientClass
	{
	private:
		char padding[8];
	public:
		char *name;
		RecvTable *table;
		clientClass *next_class;
		int	class_id;
	};

	class userCmd
	{
	public:
		virtual		~userCmd() {};
		int			command_number;
		int			tick_count;
		math::vec3	viewangles;
		float		forwardmove;
		float		sidemove;
		float		upmove;
		int			buttons;
		byte		impulse;
		int			weaponselect;
		int			weaponsubtype;
		int			random_seed;
		short		mousedx;
		short		mousedy;
		bool		hasbeenpredicted;
	};

	struct studioBbox
	{
		int	bone;
		int	group;
		math::vec3 bbmin;
		math::vec3 bbmax;
		int	hitbox_name_index;
		int	unused[8];
	};

	struct studioHitboxSet
	{
		int					name_index;
		inline char *const	pszName(void) const { return ((char *)this) + name_index; }
		int					num_hitboxes;
		int					hitbox_index;
		studioBbox		*hitbox(int i) const { return (studioBbox *)(((byte *)this) + hitbox_index) + i; };
	};

	struct studioBone
	{
		int					name_index;
		inline char *const name(void) const { return ((char *)this) + name_index; }
		int		 			parent;
		int					bonecontroller[6];
		math::vec3			pos;
		float				quat[4];
		math::vec3			rot;
		math::vec3			posscale;
		math::vec3			rotscale;
		float				pose_to_bone[3][4];
		float				alignment[4];
		int					flags;
		int					proc_type;
		int					proc_index;
		mutable int			physicsbone;
		inline void *pProcedure() const { if (proc_index == 0) return NULL; else return  (void *)(((byte *)this) + proc_index); };
		int					surfacepropidx;
		inline char *const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
		int					contents;
		int					unused[8];

		studioBone() {}
	private:
		// No copy constructors allowed
		studioBone(const studioBone &vOther);
	};

	struct studioHdr
	{
		int id;
		int version;
		int checksum;
		char name[64];
		int length;
		math::vec3 eyeposition;
		math::vec3 illumposition;
		math::vec3 hull_min;
		math::vec3 hull_max;
		math::vec3 view_bbmin;
		math::vec3 view_bbmax;
		int flags;
		int numbones;
		int boneindex;
		inline studioBone *get_bone(int i) const { return (studioBone *)(((byte *)this) + boneindex) + i; };

		int numbonecontrollers;
		int bonecontrollerindex;
		int numhitboxsets;
		int hitboxsetindex;

		studioHitboxSet *get_hitbox_set(int i) const
		{
			return (studioHitboxSet *)(((byte *)this) + hitboxsetindex) + i;
		}

		inline studioBbox *get_hitbox(int i, int set) const
		{
			studioHitboxSet const *s = get_hitbox_set(set);

			if (!s)
				return NULL;

			return s->hitbox(i);
		}

		inline int get_hitbox_count(int set) const
		{
			studioHitboxSet const *s = get_hitbox_set(set);

			if (!s)
				return 0;

			return s->num_hitboxes;
		}

		int numlocalanim;
		int localanimindex;
		int numlocalseq;
		int localseqindex;
		mutable int activitylistversion;
		mutable int eventsindexed;
		int numtextures;
		int textureindex;
		int numcdtextures;
		int cdtextureindex;
		int numskinref;
		int numskinfamilies;
		int skinindex;
		int numbodyparts;
		int bodypartindex;
		int numlocalattachments;
		int localattachmentindex;
		int numlocalnodes;
		int localnodeindex;
		int localnodenameindex;
		int numflexdesc;
		int flexdescindex;
		int numflexcontrollers;
		int flexcontrollerindex;
		int numflexrules;
		int flexruleindex;
		int numikchains;
		int ikchainindex;
		int nummouths;
		int mouthindex;
		int numlocalposeparameters;
		int localposeparamindex;
		int surfacepropindex;
		int keyvalueindex;
		int keyvaluesize;
		int numlocalikautoplaylocks;
		int localikautoplaylockindex;
		float mass;
		int contents;
		int numincludemodels;
		int includemodelindex;
		mutable void *virtualModel;
		int szanimblocknameindex;
		int numanimblocks;
		int animblockindex;
		mutable void *animblockModel;
		int bonetablebynameindex;
		void *pVertexBase;
		void *pIndexBase;
		byte constdirectionallightdot;
		byte rootLOD;
		byte numAllowedRootLODs;
		byte unused[1];
		int unused4;
		int numflexcontrollerui;
		int	flexcontrolleruiindex;
		float flVertAnimFixedPointScale;
		int	unused3[1];
		int	studiohdr2index;
		int	unused2[1];
	};

	class baseEntity;

	class __declspec(align(16))vectorAligned : public math::vec3
	{
	public:
		inline vectorAligned(void)
		{

		};

		inline vectorAligned(float X, float Y, float Z)
		{
			set(X, Y, Z);
		}

		explicit vectorAligned(const math::vec3 &other)
		{
			set(other.x, other.y, other.z);
		}

		vectorAligned &operator=(const math::vec3 &other)
		{
			set(other.x, other.y, other.z);
			return *this;
		}

		float w;
	};

	struct iRay
	{
		vectorAligned start;
		vectorAligned delta;
		vectorAligned start_offset;
		vectorAligned extents;

		bool is_ray;
		bool is_swept;

		void init(math::vec3 vstart, math::vec3 end)
		{
			delta = end - vstart;

			is_swept = (delta.length_sqr() != 0);

			extents.set();
			is_ray = true;

			start_offset.set();
			start = vstart;
		}

		void init(math::vec3 &vstart, math::vec3 &end, math::vec3 &mins, math::vec3 &maxs)
		{
			delta = end - vstart;

			is_swept = (delta.length_sqr() != 0);

			extents = maxs - mins;
			extents *= 0.5f;
			is_ray = (extents.length_sqr() < 1e-6);

			start_offset = mins + maxs;

			start_offset *= 0.5f;
			start = vstart - start_offset;
			start_offset *= -1.0f;
		}
	};

	struct _plane
	{
		math::vec3 normal;
		float dist;
		BYTE type;
		BYTE signbits;
		BYTE pad[2];
	};

	struct _surface
	{
		const char *name;
		short surfaceProps;
		unsigned short flags;
	};

	enum surfaceFlags
	{
		dispsurf_flag_surface	= (1 << 0),
		dispsurf_flag_walkable	= (1 << 1),
		dispsurf_flag_buildable = (1 << 2),
		dispsurf_flag_surfprop1 = (1 << 3),
		dispsurf_flag_surfprop2 = (1 << 4)
	};

	enum traceType
	{
		trace_everything,
		trace_world_only,
		trace_entities_only,
		trace_everything_filter_props
	};

	enum fontFlags
	{
		fontflag_none			= 0x000,
		fontflag_italic			= 0x001,
		fontflag_underline		= 0x002,
		fontflag_strikeout		= 0x004,
		fontflag_symbol			= 0x008,
		fontflag_antialias		= 0x010,
		fontflag_gaussianblur	= 0x020,
		fontflag_rotary			= 0x040,
		fontflag_dropshadow		= 0x080,
		fontflag_additive		= 0x100,
		fontflag_outline		= 0x200,
		fontflag_custom			= 0x400
	};

	class traceFilter
	{
	public:
		virtual bool should_hit_entity(void *entity, int contents_mask) = 0;
		virtual traceType get_trace_type() const = 0;
	};

	class baseTrace
	{
	public:
		bool is_disp_surface(void)				{ return ((dispFlags & dispsurf_flag_surface) != 0);	}
		bool is_disp_surface_walkable(void)		{ return ((dispFlags & dispsurf_flag_walkable) != 0);	}
		bool is_disp_surface_buildable(void)	{ return ((dispFlags & dispsurf_flag_buildable) != 0);	}
		bool is_disp_surface_prop1(void)		{ return ((dispFlags & dispsurf_flag_surfprop1) != 0);	}
		bool is_disp_surface_prop2(void)		{ return ((dispFlags & dispsurf_flag_surfprop2) != 0);	}

	public:
		math::vec3		startpos;
		math::vec3		endpos;
		_plane			plane;
		float			fraction;
		int				contents;
		unsigned short	dispFlags;
		bool			allsolid;
		bool			startsolid;

		baseTrace() { }

	private:
		baseTrace(const baseTrace &other);
	};

	class gameTrace : public baseTrace
	{
	public:
		bool did_hit_world() const;
		bool did_hit_non_world_entity() const;
		int get_entity_index() const;
		bool did_hit() const { return fraction < 1 || allsolid || startsolid; }

	public:
		float			fractionleftsolid;
		_surface		surface;
		int				hitgroup;
		short			physicsbone;
		baseEntity		*ent;
		int				hitbox;

		gameTrace() { }
		gameTrace(const gameTrace &other);
	};

	typedef gameTrace iTrace;

	class moveData
	{
	public:
		bool				first_run_of_functions : 1;
		bool				game_code_moved_player : 1;
		void				*player_handle;
		int					impulse_command;
		math::vec3			view_angles;
		math::vec3			abs_view_angles;
		int					buttons;
		int					old_buttons;
		float				forward_move;
		float				side_move;
		float				up_move;
		float				max_speed;
		float				client_max_speed;
		math::vec3			velocity;
		math::vec3			angles;
		math::vec3			old_angles;
		float				out_step_height;
		math::vec3			out_wish_vel;
		math::vec3			out_jump_vel;
		math::vec3			constraint_center;
		float				constraint_radius;
		float				constraint_width;
		float				constraint_speed_factor;
		void				set_abs_origin(const math::vec3 &vec);
		const math::vec3	&get_abs_origin() const;
		math::vec3			abs_origin;
	};

	class hlClient
	{
	public:
		clientClass *get_all_classes(void)
		{
			typedef clientClass *(__thiscall * OriginalFn)(void *);
			return vfunc::get_vfunc<OriginalFn>(this, 8)(this);
		}

		bool should_draw_entity(baseEntity *entity)
		{
			typedef bool(__thiscall * OriginalFn)(void *, baseEntity *);
			return vfunc::get_vfunc<OriginalFn>(this, 12)(this, entity);
		}
	};

	class engineClient
	{
	public:
		void get_screen_size(int &width_out, int &height_out)
		{
			typedef void(__thiscall * original_fn)(void *, int &, int &);
			return vfunc::get_vfunc<original_fn>(this, 5)(this, width_out, height_out);
		}

		void server_cmd(const char *cmd_string, bool reliable = true)
		{
			typedef void(__thiscall * original_fn)(void *, const char *, bool);
			return vfunc::get_vfunc<original_fn>(this, 6)(this, cmd_string, reliable);
		}

		void client_cmd_unrestricted(const char *cmd_string)
		{
			typedef void(__thiscall * original_fn)(void *, const char *);
			return vfunc::get_vfunc<original_fn>(this, 106)(this, cmd_string);
		}

		bool get_player_info(int entity_index, playerInfo *player_info)
		{
			typedef bool(__thiscall * original_fn)(void *, int, playerInfo *);
			return vfunc::get_vfunc<original_fn>(this, 8)(this, entity_index, player_info);
		}

		bool is_console_visible(void)
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 11)(this);
		}

		int get_local_player(void)
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 12)(this);
		}

		float time(void)
		{
			typedef float(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 14)(this);
		}

		void get_view_angles(math::vec3 &va)
		{
			typedef void(__thiscall * original_fn)(void *, math::vec3 & va);
			return vfunc::get_vfunc<original_fn>(this, 19)(this, va);
		}

		void set_view_angles(math::vec3 &va)
		{
			typedef void(__thiscall * original_fn)(void *, math::vec3 & va);
			return vfunc::get_vfunc<original_fn>(this, 20)(this, va);
		}

		int get_max_clients(void)
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 21)(this);
		}

		bool is_in_game(void)
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 26)(this);
		}

		bool is_connected(void)
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 27)(this);
		}

		bool is_drawing_loading_image(void)
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 28)(this);
		}

		const math::matrix3x4 &world_to_screen_matrix(void)
		{
			typedef const math::matrix3x4 &(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 36)(this);
		}

		bool is_taking_screenshot(void)
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 85)(this);
		}

		DWORD *get_net_channel_info(void)
		{
			typedef DWORD *(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 72)(this);
		}
	};

	class iGlobals
	{
	public:
		float	realtime;
		int		framecount;
		float	absoluteframetime;
		float	curtime;
		float	frametime;
		int		maxclients;
		int		tickcount;
		float	interval_per_tick;
		float	interpolation_amount;
	};

	class modelInfo
	{
	public:
		const char *get_model_name(DWORD *model)
		{
			typedef const char *(__thiscall * original_fn)(void *, DWORD *);
			return vfunc::get_vfunc<original_fn>(this, 3)(this, model);
		}

		void get_model_render_bounds(const DWORD *model, math::vec3 &mins, math::vec3 &maxs)
		{
			typedef void(__thiscall * original_fn)(void *, const DWORD *, math::vec3 &, math::vec3 &);
			return vfunc::get_vfunc<original_fn>(this, 7)(this, model, mins, maxs);
		}

		DWORD *get_studio_model(DWORD *model)
		{
			typedef DWORD *(__thiscall * original_fn)(void *, DWORD *);
			return vfunc::get_vfunc<original_fn>(this, 28)(this, model);
		}
	};

	class entityList
	{
	public:
		baseEntity *get_client_entity(int index)
		{
			typedef baseEntity *(__thiscall * original_fn)(void *, int);
			return vfunc::get_vfunc<original_fn>(this, 3)(this, index);
		}

		baseEntity *get_client_entity_from_handle(int entity)
		{
			typedef baseEntity *(__thiscall * original_fn)(void *, int);
			return vfunc::get_vfunc<original_fn>(this, 4)(this, entity);
		}

		int get_highest_entity_index(void)
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 6)(this);
		}
	};

	constexpr int END_OF_FREE_LIST = -1;
	constexpr int ENTRY_IN_USE = -2;

	struct glowObjectDefinition
	{
		unsigned int entity;
		math::vec3 glow_color;
		float glow_alpha;
		bool render_when_occluded;
		bool render_when_unoccluded;
		int split_screen_slot;
		int next_free_slot;
	};

	class glowObjectManager
	{
	public:
		CUtlVector<glowObjectDefinition> glow_objects;
		int first_free_slot;
	};

	class baseCombatWeapon;

	class baseEntity
	{
	public:
		template <typename T>
		T get(uint32_t off)
		{
			return *(T *)((uint32_t)this + off);
		}

		template <typename T>
		void set(uint32_t off, T val)
		{
			(*(T *)((uint32_t)this + off)) = val;
		}

		math::vec3 get_view_offset()
		{
			DYNVAR_RETURN(math::vec3, this, "DT_BasePlayer", "localdata", "m_vecViewOffset[0]");
		}

		void set_current_cmd(userCmd *cmd)
		{
			DYNVAR_SET(userCmd *, (this - 0x4), cmd, "DT_BasePlayer", "localdata", "m_hConstraintEntity");
		}

		userCmd *get_current_cmd()
		{
			DYNVAR_RETURN(userCmd *, (this - 0x4), "DT_BasePlayer", "localdata", "m_hConstraintEntity");
		}

		math::vec3 get_vec_origin()
		{
			DYNVAR_RETURN(math::vec3, this, "DT_BaseEntity", "m_vecOrigin");
		}

		void set_vec_origin(math::vec3 &origin)
		{
			DYNVAR_SET(math::vec3, this, origin, "DT_BaseEntity", "m_vecOrigin");
		}

		math::vec3 &get_abs_origin()
		{
			typedef math::vec3 &(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 9)(this);
		}

		math::vec3 &get_shoot_pos()
		{
			static auto shoot_pos_fn = reinterpret_cast<float *(__thiscall *)(void *, math::vec3 *)>(
				pattern::find_in_client("55 8B EC 56 8B 75 08 57 8B F9 56 8B 07 FF 90"));

			math::vec3 out;
			shoot_pos_fn(this, &out);

			return out;
		}
		
		const char *get_model_name()
		{
			return (ifaces::model_info->get_model_name(this->get_model()));
		}

		int get_ammo()
		{
			DYNVAR_RETURN(int, (this + 4), "DT_BasePlayer", "localdata", "m_iAmmo");
		}

		bool is_baseCombatWeapon()
		{
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 137)(this);
		}

		int get_hitbox_set()
		{
			DYNVAR_RETURN(int, this, "DT_BaseAnimating", "m_nHitboxSet");
		}

		int get_tick_base()
		{
			DYNVAR_RETURN(int, this, "DT_BasePlayer", "localdata", "m_nTickBase");
		}

		void inc_tick_base()
		{
			static dynamicNetvar<int>n("DT_BasePlayer", "localdata", "m_nTickBase");
			n.set_value(this, n.get_value(this) + 1);
		}

		float get_simulation_time()
		{
			DYNVAR_RETURN(float, this, "DT_BaseEntity", "m_flSimulationTime");
		}

		int get_owner_entity()
		{
			DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_hOwnerEntity");
		}

		moveTypes get_move_type()
		{
			DYNVAR_RETURN(moveTypes, this, "DT_BaseEntity", "movetype");
		}

		math::vec3 &get_abs_angles()
		{
			typedef math::vec3 &(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 10)(this);
		}

		math::vec3 get_world_space_center()
		{
			math::vec3 mins, maxs;

			this->get_render_bounds(mins, maxs);
			math::vec3 vWorldSpaceCenter = this->get_abs_origin();
			vWorldSpaceCenter.z += (mins.z + maxs.z) / 2.0f;

			return vWorldSpaceCenter;
		}

		DWORD *get_model()
		{
			void *renderable = (void *)(this + 0x4);
			typedef DWORD *(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(renderable, 9)(renderable);
		}

		int draw_model(int flags)
		{
			void *renderable = (void *)(this + 0x4);
			typedef int(__thiscall * original_fn)(void *, int);
			return vfunc::get_vfunc<original_fn>(renderable, 10)(renderable, flags);
		}

		void *get_renderable()
		{
			return (void *)(this + 0x4);
		}

		bool setup_bones(math::matrix3x4 *bone_to_world_out, int max_bones, int bone_mask, float cur_time)
		{
			void *renderable = (void *)(this + 0x4);
			typedef bool(__thiscall * original_fn)(void *, math::matrix3x4 *, int, int, float);
			return vfunc::get_vfunc<original_fn>(renderable, 16)(renderable, bone_to_world_out, max_bones, bone_mask, cur_time);
		}

		clientClass *get_client_class()
		{
			void *networkable = (void *)(this + 0x8);
			typedef clientClass *(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(networkable, 2)(networkable);
		}

		bool is_dormant()
		{
			void *networkable = (void *)(this + 0x8);
			typedef bool(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(networkable, 8)(networkable);
		}

		int get_index()
		{
			void *networkable = (void *)(this + 0x8);
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(networkable, 9)(networkable);
		}

		void get_render_bounds(math::vec3 &mins, math::vec3 &maxs)
		{
			void *renderable = (void *)(this + 0x4);
			typedef void(__thiscall * original_fn)(void *, math::vec3 &, math::vec3 &);
			vfunc::get_vfunc<original_fn>(renderable, 20)(renderable, mins, maxs);
		}

		math::matrix3x4 &get_rgfl_coordinate_frame()
		{
			void *renderable = (void *)(this + 0x4);
			typedef math::matrix3x4 &(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(renderable, 34)(renderable);
		}

		math::vec3 get_velocity()
		{
			typedef void(__thiscall *EstimateAbsVelocityFn)(baseEntity *, math::vec3 &);
			static DWORD fn = pattern::find_in_client("E8 ? ? ? ? F3 0F 10 4D ? 8D 85 ? ? ? ? F3 0F 10 45 ? F3 0F 59 C9 56 F3 0F 59 C0 F3 0F 58 C8 0F 2F 0D ? ? ? ? 76 07") + 0x1;
			static DWORD estimate = ((*(PDWORD)(fn)) + fn + 0x4);
			EstimateAbsVelocityFn vel = (EstimateAbsVelocityFn)estimate;
			math::vec3 v;

			vel(this, v);

			return v;
		}

		int get_max_health()
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 107)(this);
		}

		int get_ground_entity()
		{
			DYNVAR_RETURN(int, this, "DT_BasePlayer", "localdata", "m_hGroundEntity");
		}

		int get_health()
		{
			DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iHealth");
		}

		int get_team_num()
		{
			DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_iTeamNum");
		}

		int get_flags()
		{
			DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_fFlags");
		}

		void set_flags(int flags)
		{
			DYNVAR_SET(int, this, flags, "DT_BasePlayer", "m_fFlags");
		}

		BYTE get_life_state()
		{
			DYNVAR_RETURN(BYTE, this, "DT_BasePlayer", "m_lifeState");
		}

		int get_class_id()
		{
			return this->get_client_class()->class_id;
		}

		int get_class_num()
		{
			DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_PlayerClass", "m_iClass");
		}

		const char *get_class_string()
		{
			DYNVAR(_class, int, "DT_TFPlayer", "m_PlayerClass", "m_iClass");

			switch (_class.get_value(this))
			{
				case scout:
					return "scout";

				case soldier:
					return "soldier";

				case pyro:
					return "pyro";

				case demoman:
					return "demoman";

				case heavy:
					return "heavy";

				case engineer:
					return "engineer";

				case medic:
					return "medic";

				case sniper:
					return "sniper";

				case spy:
					return "spy";

				default:
					return "unknown";
			}
		}

		int get_cond()
		{
			DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_Shared", "m_nPlayerCond");
		}

		int get_cond_ex()
		{
			DYNVAR_RETURN(int, this, "DT_TFPlayer", "m_Shared", "m_nPlayerCondEx");
		}

		math::vec3 get_collideable_mins()
		{
			DYNVAR_RETURN(math::vec3, this, "DT_BaseEntity", "m_Collision", "m_vecMins");
		}

		math::vec3 get_collideable_maxs()
		{
			DYNVAR_RETURN(math::vec3, this, "DT_BaseEntity", "m_Collision", "m_vecMaxs");
		}

		math::vec3 get_eye_angles()
		{
			DYNVAR_RETURN(math::vec3, this, "DT_TFPlayer", "tfnonlocaldata", "m_angEyeAngles[0]");
		}

		byte get_water_level()
		{
			DYNVAR(n, byte, "DT_TFPlayer", "m_nWaterLevel");
			return n.get_value(this);
		}

		bool is_on_ground()
		{
			return (this->get_flags() & on_ground);
		}

		bool is_in_water()
		{
			return (this->get_flags() & in_water);
		}

		bool is_swimming()
		{
			return (this->get_water_level() > 1);
		}

		math::vec3 get_hitbox_pos(int hitbox)
		{
			DWORD *model = this->get_model();
			if (!model)
				return math::vec3();
			
			studioHdr *hdr = (studioHdr *)ifaces::model_info->get_studio_model(model);
			if (!hdr)
				return math::vec3();

			math::matrix3x4 bone_matrix[128];
			if (!this->setup_bones(bone_matrix, 128, 0x100, ifaces::globals->curtime))
				return math::vec3();

			studioHitboxSet *set = hdr->get_hitbox_set(this->get_hitbox_set());
			if (!set)
				return math::vec3();

			studioBbox *box = set->hitbox(hitbox);
			if (!box)
				return math::vec3();

			math::vec3 pos = (box->bbmin + box->bbmax) * 0.5f;
			math::vec3 out = math::vec3();

			math::vector_transform(pos, bone_matrix[box->bone], out);

			return out;
		}

		int get_num_of_hitboxes()
		{
			DWORD *model = this->get_model();
			if (!model)
				return 0;

			studioHdr *hdr = (studioHdr*)ifaces::model_info->get_studio_model(model);
			if (!hdr)
				return 0;

			studioHitboxSet *set = hdr->get_hitbox_set(this->get_hitbox_set());
			if (!set)
				return 0;

			return set->num_hitboxes;
		}

		math::vec3 get_bone_pos(int bone)
		{
			math::matrix3x4 matrix[128];

			if (this->setup_bones(matrix, 128, 0x100, GetTickCount64()))
				return math::vec3(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);

			return math::vec3(0.0f, 0.0f, 0.0f);
		}

		baseCombatWeapon *get_active_weapon()
		{
			DYNVAR(pHandle, int, "DT_BaseCombatCharacter", "m_hActiveWeapon");
			return reinterpret_cast<baseCombatWeapon *>(ifaces::entity_list->get_client_entity_from_handle(pHandle.get_value(this)));
		}

		void force_taunt_camera(bool state)
		{
			DYNVAR(n, bool, "DT_TFPlayer", "m_nForceTauntCam");
			return n.set_value(this, state);
		}


		void set_glow_enabled(bool bState)
		{
			DYNVAR(n, bool, "DT_TFPlayer", "m_bGlowEnabled");
			return n.set_value(this, bState);
		}

		bool is_glow_enabled()
		{
			DYNVAR(n, bool, "DT_TFPlayer", "m_bGlowEnabled");
			return n.get_value(this);
		}

		void update_glow_effect() 
		{
			typedef void(__thiscall * original_fn)(void*);
			return vfunc::get_vfunc<original_fn>(this, 226)(this);
		}

		int register_glow_object(color &color, bool render_when_occluded, bool render_when_unoccluded)
		{
			using register_fn		= int(__thiscall*)(glowObjectManager*, baseEntity*, math::vec3&, float, bool, bool, int);
			static DWORD fn			= pattern::find_in_client("55 8B EC 51 53 56 8B F1 57 8B 5E 14");
			static register_fn reg	= (register_fn)fn;
			math::vec3 col			= color.get_vec3();
			float alpha				= color.get_a_fl();

			return reg(ifaces::glow_object, this, col, alpha, render_when_occluded, render_when_unoccluded, -1);
		}

		bool has_glow_effect()
		{
			for (int n = 0; n < ifaces::glow_object->glow_objects.Count(); n++) {
				glowObjectDefinition &object = ifaces::glow_object->glow_objects[n];
				baseEntity *ent = ifaces::entity_list->get_client_entity_from_handle(object.entity);

				if (ent == this)
					return true;
			}

			return false;
		}


		bool is_in_taunt_camera()
		{
			DYNVAR(n, bool, "DT_TFPlayer", "m_nForceTauntCam");
			return n.get_value(this);
		}

		bool is_alive()
		{
			return (this->get_life_state() == alive);
		}

		bool is_vulnerable()
		{
			return !(this->get_cond() & cond_ubercharged || this->get_cond() & cond_bonked);
		}

		bool is_crit_boosted()
		{
			int cond = this->get_cond();
			int cond_ex = this->get_cond_ex();

			return (cond & cond_kritzkrieged
				|| cond_ex & cond_crit_canteen
				|| cond_ex & cond_crit_on_first_blood
				|| cond_ex & cond_crit_on_win
				|| cond_ex & cond_halloween_crit_candy
				|| cond_ex & cond_pyro_crits);
		}

		bool is_player()
		{
			return (this->get_client_class()->class_id == CTFPlayer);
		}

		bool is_building()
		{
			return (this->get_client_class()->class_id == CObjectDispenser
				|| this->get_client_class()->class_id == CObjectSentrygun
				|| this->get_client_class()->class_id == CObjectTeleporter);
		}

		bool is_pickup()
		{
			return (this->get_client_class()->class_id == CBaseAnimating && this->get_model_name()[24] != 'h'
				|| this->get_client_class()->class_id == CTFAmmoPack);
		}

		bool is_scoped()
		{
			return (this->get_cond() & cond_zoomed);
		}

		int get_fov()
		{
			DYNVAR_RETURN(int, this, "DT_BasePlayer", "m_iFOV");
		}

		void set_fov(int fov)
		{
			DYNVAR_SET(int, this, fov, "DT_BasePlayer", "m_iFOV");
		}

		bool is_taunting()
		{
			return (this->get_cond() & cond_taunting);
		}

		bool is_ducking()
		{
			return (this->get_flags() & ducking);
		}

		bool is_ubered()
		{
			return (this->get_cond() & cond_ubercharged);
		}

		bool is_bonked()
		{
			return (this->get_cond() & cond_bonked);
		}

		bool is_cloaked()
		{
			return (this->get_cond() & cond_cloaked);
		}

		int get_observer_target()
		{
			DYNVAR(n, int, "DT_BasePlayer", "m_hObserverTarget");
			return n.get_value(this);
		}

		int get_observer_mode()
		{
			DYNVAR(n, int, "DT_BasePlayer", "m_iObserverMode");
			return n.get_value(this);
		}

		void remove_effect(effectFlags effect)
		{
			*reinterpret_cast<byte *>(this + 0x7C) &= ~effect;

			if (effect == ef_nodraw)
			{
				static auto AddToLeafSystemFn = reinterpret_cast<int(__thiscall *)(void *, int)>(pattern::find_in_client("55 8B EC 56 FF 75 08 8B F1 B8"));

				if (AddToLeafSystemFn)
					AddToLeafSystemFn(this, 1);
			}
		}
	};

	class baseObject : public baseEntity
	{
	public:
		baseObject *to_base_object(baseEntity *pEntity)
		{
			return reinterpret_cast<baseObject *>(pEntity);
		}

		baseEntity *get_owner()
		{
			DYNVAR_RETURN(baseEntity *, this, "DT_BaseObject", "m_hBuilder");
		}

		int get_level()
		{
			DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iUpgradeLevel");
		}

		bool is_sapped()
		{
			DYNVAR_RETURN(bool, this, "DT_BaseObject", "m_bHasSapper");
		}

		bool is_building()
		{
			DYNVAR_RETURN(bool, this, "DT_BaseObject", "m_bBuilding");
		}

		float get_percentage_constructed()
		{
			if (is_building()) {
				DYNVAR_RETURN(float, this, "DT_BaseObject", "m_flPercentageConstructed");
			}

			return 0.0f;
		}

		int get_health()
		{
			DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iHealth");
		}

		int get_max_health()
		{
			DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iMaxHealth");
		}

		int get_state()
		{
			DYNVAR_RETURN(int, this, "DT_ObjectSentrygun", "m_iState");
		}

		int get_upgrade_metal()
		{
			DYNVAR_RETURN(int, this, "DT_BaseObject", "m_iUpgradeMetal");
		}

		int get_team_num()
		{
			DYNVAR_RETURN(int, this, "DT_BaseEntity", "m_iTeamNum");
		}
	};

	class baseCombatWeapon : public baseEntity
	{
	public:
		int get_max_clip_1()
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 318)(this);
		}

		int get_max_clip_2()
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 319)(this);
		}

		int get_slot()
		{
			typedef int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 327)(this);
		}

		char *get_name()
		{
			typedef char *(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 329)(this);
		}

		char *get_print_name()
		{
			typedef char *(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 330)(this);
		}

		float get_charge_time()
		{
			DYNVAR_RETURN(float, this, "DT_WeaponPipebombLauncher", "PipebombLauncherLocalData", "m_flChargeBeginTime");
		}

		float get_charge_damage()
		{
			DYNVAR_RETURN(float, this, "DT_TFSniperRifle", "SniperRifleLocalData", "m_flChargedDamage");
		}

		int get_definition_index()
		{
			DYNVAR_RETURN(int, this, "DT_EconEntity", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
		}

		float get_last_fire_time()
		{
			DYNVAR_RETURN(float, this, "DT_TFWeaponBase", "LocalActiveTFWeaponData", "m_flLastFireTime");
		}

		float get_swing_range(baseEntity *local_entity)
		{
			typedef int(__thiscall * original_fn)(baseEntity *);
			return 4.0f + (float)vfunc::get_vfunc<original_fn>(this, 451)(local_entity) / 10.0f;
		}

		bool do_swing_trace(iTrace &Trace)
		{
			typedef int(__thiscall * original_fn)(iTrace &);
			return vfunc::get_vfunc<original_fn>(this, 453)(Trace);
		}

		bool can_backstab()
		{
			return *reinterpret_cast<bool *>(this + net_vars.get_offset("DT_TFWeaponKnife", "m_bReadyToBackstab"));
		}
	};

	class iTraceFilter : public traceFilter
	{
	public:
		virtual bool should_hit_entity(void *entity_handle, int contents_mask)
		{
			baseEntity *entity = reinterpret_cast<baseEntity *>(entity_handle);

			switch (entity->get_client_class()->class_id) {
				case 55:
				case 64:
				case 117:
				case 225:
					return false;
			}

			return !(entity_handle == skip);
		}

		virtual traceType get_trace_type() const {
			return trace_everything;
		}

		baseEntity *skip;
	};

	class iPanel
	{
	public:
		const char *get_name(unsigned int vgui_panel)
		{
			typedef const char *(__thiscall * original_fn)(void *, unsigned int);
			return vfunc::get_vfunc<original_fn>(this, 36)(this, vgui_panel);
		}

		void set_mouse_input_enabled(unsigned int panel, bool state)
		{
			vfunc::get_vfunc<void(__thiscall *)(void *, int, bool)>(this, 32)(this, panel, state);
		}
	};

	class iSurface
	{
	public:
		void set_draw_color(int r, int g, int b, int a)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int);
			vfunc::get_vfunc<original_fn>(this, 11)(this, r, g, b, a);
		}

		void draw_filled_rect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int);
			vfunc::get_vfunc<original_fn>(this, 12)(this, x0, y0, x1, y1);
		}

		void draw_outlined_rect(int x0, int y0, int x1, int y1)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int);
			vfunc::get_vfunc<original_fn>(this, 14)(this, x0, y0, x1, y1);
		}

		void set_text_font(unsigned long font)
		{
			typedef void(__thiscall * original_fn)(void *, unsigned long);
			vfunc::get_vfunc<original_fn>(this, 17)(this, font);
		}

		void set_text_color(int r, int g, int b, int a)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int);
			vfunc::get_vfunc<original_fn>(this, 19)(this, r, g, b, a);
		}

		void set_text_pos(int x, int y)
		{
			typedef void(__thiscall * original_fn)(void *, int, int);
			vfunc::get_vfunc<original_fn>(this, 20)(this, x, y);
		}

		void print_text(const wchar_t *text, int text_len)
		{
			typedef void(__thiscall * original_fn)(void *, const wchar_t *, int, int);
			return vfunc::get_vfunc<original_fn>(this, 22)(this, text, text_len, 0);
		}

		void draw_line(int x, int y, int x1, int y1)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int);
			return vfunc::get_vfunc<original_fn>(this, 15)(this, x, y, x1, y1);
		}

		unsigned long create_font()
		{
			typedef unsigned int(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 66)(this);
		}

		void set_font_glyph_set(unsigned long &font, const char *windows_font_name, int tall, int weight, int blur, int scanlines, int flags)
		{
			typedef void(__thiscall * original_fn)(void *, unsigned long, const char *, int, int, int, int, int, int, int);
			vfunc::get_vfunc<original_fn>(this, 67)(this, font, windows_font_name, tall, weight, blur, scanlines, flags, 0, 0);
		}

		void get_text_size(unsigned long font, const wchar_t *text, int &wide, int &tall)
		{
			typedef void(__thiscall * original_fn)(void *, unsigned long, const wchar_t *, int &, int &);
			vfunc::get_vfunc<original_fn>(this, 75)(this, font, text, wide, tall);
		}

		void get_cursor_pos(int &x_out, int &y_out)
		{
			typedef void(__thiscall * original_fn)(void *, int &, int &);
			vfunc::get_vfunc<original_fn>(this, 96)(this, x_out, y_out);
		}

		void set_cursor_always_visible(bool b)
		{
			typedef void(__thiscall * original_fn)(void *, bool);
			vfunc::get_vfunc<original_fn>(this, 52)(this, b);
		}

		void draw_filled_rect_fade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool horizontal)
		{
			typedef void(__thiscall * original_fn)(void *, int, int, int, int, unsigned int, unsigned int, bool);
			vfunc::get_vfunc<original_fn>(this, 118)(this, x0, y0, x1, y1, alpha0, alpha1, horizontal);
		}

		void unlock_cursor()
		{
			typedef void(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 61)(this);
		}

		void lock_cursor()
		{
			typedef void(__thiscall * original_fn)(void *);
			return vfunc::get_vfunc<original_fn>(this, 62)(this);
		}
	};

	class clientModeShared
	{
	public:
		bool is_chat_panel_out_of_focus(void)
		{
			typedef void *(__thiscall * original_fn)(void *);
			void *CHudChat = vfunc::get_vfunc<original_fn>(this, 19)(this);

			if (CHudChat)
				return *reinterpret_cast<float *>((reinterpret_cast<DWORD>(CHudChat) + 0xFC)) == 0.0f;

			return false;
		}
	};

	class engineTrace
	{
	public:
		void trace_ray(const iRay &ray, unsigned int mask, iTraceFilter *trace_filter, iTrace *trace)
		{
			typedef void(__thiscall * trace_ray_fn)(void *, const iRay &, unsigned int, iTraceFilter *, iTrace *);
			return vfunc::get_vfunc<trace_ray_fn>(this, 4)(this, ray, mask, trace_filter, trace);
		}
	};

	class moveHelper
	{
	public:
		void set_host(baseEntity *host)
		{
			typedef void(__thiscall * original_fn)(void *, baseEntity *);
			vfunc::get_vfunc<original_fn>(this, 0)(this, host);
		}
	};

	class iPrediction
	{
	public:
		void set_local_view_angles(math::vec3 &angles)
		{
			typedef void(__thiscall * original_fn)(void *, math::vec3 &);
			vfunc::get_vfunc<original_fn>(this, 16)(this, angles);
		}

		void setup_move(baseEntity *entity, userCmd *cmd, moveHelper *move_helper, void *move_data)
		{
			typedef void(__thiscall * original_fn)(void *, baseEntity *, userCmd *, moveHelper *, void *);
			vfunc::get_vfunc<original_fn>(this, 18)(this, entity, cmd, move_helper, move_data);
		}

		void finish_move(baseEntity *entity, userCmd *cmd, void *move_data)
		{
			typedef void(__thiscall * original_fn)(void *, baseEntity *, userCmd *, void *);
			vfunc::get_vfunc<original_fn>(this, 19)(this, entity, cmd, move_data);
		}
	};

	class gameMovement
	{
	public:
		virtual ~gameMovement(void) { }

		virtual void process_movement(baseEntity *player, void *move) = 0;
		virtual void start_track_prediction_errors(baseEntity *player) = 0;
		virtual void finish_track_prediction_errors(baseEntity *player) = 0;
		virtual void diff_print(char const *fmt, ...) = 0;
		virtual math::vec3 get_player_mins(bool ducked) const = 0;
		virtual math::vec3 get_player_maxs(bool ducked) const = 0;
		virtual math::vec3 get_player_view_offset(bool ducked) const = 0;
	};
}

#define get_ent(x)		sdk::ifaces::entity_list->get_client_entity(x)
#define local_ent_idx	sdk::ifaces::engine->get_local_player()
#define ent_list_start	1
#define ent_list_end	sdk::ifaces::entity_list->get_highest_entity_index()
#define max_players		(sdk::ifaces::engine->get_max_clients() + 1)

struct globalInfo
{
	bool sniper_can_headshot = false;
	bool spy_can_headshot = false;
}; extern globalInfo global_info;

struct screenSize
{
	int w = 0, h = 0;

	void update() {
		sdk::ifaces::engine->get_screen_size(w, h);
	}

}; extern screenSize screen_size;

class surfaceWrapper
{
public:
	unsigned long font = 0x0;

	surfaceWrapper() { }

	surfaceWrapper(const char *name, int tall, int weight, int flags)
	{
		if (sdk::ifaces::surface) {
			font = sdk::ifaces::surface->create_font();
			sdk::ifaces::surface->set_font_glyph_set(font, name, tall, weight, 0, 0, flags);
		}
	}

	void string(int x, int y, color &clr, const char *str, ...)
	{
		if (str == 0)
			return;

		va_list va_alist;
		char cbuffer[1024] = { '\0' };
		wchar_t wstr[1024] = { '\0' };

		va_start(va_alist, str);
		vsprintf_s(cbuffer, str, va_alist);
		va_end(va_alist);

		wsprintfW(wstr, L"%S", cbuffer);

		sdk::ifaces::surface->set_text_pos(x, y);
		sdk::ifaces::surface->set_text_font(font);
		sdk::ifaces::surface->set_text_color(clr.get_r(), clr.get_g(), clr.get_b(), clr.get_a());
		sdk::ifaces::surface->print_text(wstr, wcslen(wstr));
	}

	void line(int x, int y, int x1, int y1, color &clr)
	{
		sdk::ifaces::surface->set_draw_color(clr.get_r(), clr.get_g(), clr.get_b(), clr.get_a());
		sdk::ifaces::surface->draw_line(x, y, x1, y1);
	}

	void rect(int x, int y, int w, int h, color &clr)
	{
		sdk::ifaces::surface->set_draw_color(clr.get_r(), clr.get_g(), clr.get_b(), clr.get_a());
		sdk::ifaces::surface->draw_filled_rect(x, y, x + w, y + h);
	}

	void outline_rect(int x, int y, int w, int h, color &clr)
	{
		sdk::ifaces::surface->set_draw_color(clr.get_r(), clr.get_g(), clr.get_b(), clr.get_a());
		sdk::ifaces::surface->draw_outlined_rect(x, y, x + w, y + h);
	}

	void gradient_rect(int x, int y, int x1, int y1, color &top_clr, color &bottom_clr)
	{
		sdk::ifaces::surface->set_draw_color(top_clr.get_r(), top_clr.get_g(), top_clr.get_b(), top_clr.get_a());
		sdk::ifaces::surface->draw_filled_rect_fade(x, y, x + x1, y + y1, 255, 255, false);

		sdk::ifaces::surface->set_draw_color(bottom_clr.get_r(), bottom_clr.get_g(), bottom_clr.get_b(), bottom_clr.get_a());
		sdk::ifaces::surface->draw_filled_rect_fade(x, y, x + x1, y + y1, 0, 255, false);
	}

	void circle(float x, float y, float r, float s, color &clr)
	{
		float step = 3.141 * 2.0 / s;

		for (float a = 0; a < (3.141 * 2.0); a += step) {
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a + step) + x;
			float y2 = r * sin(a + step) + y;
			line(static_cast<int>(x1),
				static_cast<int>(y1),
				static_cast<int>(x2),
				static_cast<int>(y2),
				clr);
		}
	}
};

namespace math
{
	inline bool world_to_screen(math::vec3 &origin, math::vec3 &screen)
	{
		const math::matrix3x4 &w2s = sdk::ifaces::engine->world_to_screen_matrix();

		float w = w2s[3][0] * origin[0] + w2s[3][1] * origin[1] + w2s[3][2] * origin[2] + w2s[3][3];
		screen.z = 0;

		if (w > 0.001) {
			float fl1DBw = 1 / w;
			screen.x = (screen_size.w / 2) + (0.5 * ((w2s[0][0] * origin[0] + w2s[0][1] * origin[1] + w2s[0][2] * origin[2] + w2s[0][3]) * fl1DBw) * screen_size.w + 0.5);
			screen.y = (screen_size.h / 2) - (0.5 * ((w2s[1][0] * origin[0] + w2s[1][1] * origin[1] + w2s[1][2] * origin[2] + w2s[1][3]) * fl1DBw) * screen_size.h + 0.5);
			return true;
		}

		return false;
	}
}

namespace utils
{
	inline color get_team_color(int team_num)
	{
		switch (team_num)
		{
			case 2:		{ return color(251, 82, 79, 255);	}
			case 3:		{ return color(30, 145, 255, 255);	}
			default:	{ return color(255, 255, 255, 255); }
		}
	}

	inline color get_health_color(int hp, int maxhp)
	{
		hp = std::max(0, std::min(hp, maxhp));

		return color(
			std::min((510 * (maxhp - hp)) / maxhp, 255),
			std::min((510 * hp) / maxhp, 255),
			0,
			255);
	}

	inline std::wstring to_wchar(const char *text)
	{
		size_t length = strlen(text) + 1;
		std::wstring wc(length, L'#');
		mbstowcs(&wc[0], text, length);

		return wc;
	}

	inline bool can_sniper_headshot(sdk::baseEntity *local)
	{
		static float timer = 0.0f;
		static bool started = false;

		if (!local->is_scoped()) {
			started = false;
			timer = 0.0f;
		}

		if (!started) {
			started = true;
			timer = sdk::ifaces::globals->curtime;
		}

		if (started)
			if ((sdk::ifaces::globals->curtime - timer) > 0.21f) //0.2, 0.21 to avoid rare but annoying early shots
				return true;

		return false;
	}

	inline bool can_spy_headshot(sdk::baseEntity *local)
	{
		return ((sdk::ifaces::globals->curtime - local->get_active_weapon()->get_last_fire_time()) > 0.930f);
	}

	inline void fix_silent(sdk::userCmd *cmd, math::vec3 &angs)
	{
		math::vec3 smth(cmd->forwardmove, cmd->sidemove, cmd->upmove);
		float speed = math::fsqrt(smth.x * smth.x + smth.y * smth.y);
		math::vec3 move_ang;
		math::vector_angles(smth, move_ang);
		float yaw = DEG2RAD(angs.y - cmd->viewangles.y + move_ang.y);

		cmd->forwardmove = (cosf(yaw) * speed);
		cmd->sidemove = (sinf(yaw) * speed);
		cmd->viewangles = angs;
	}

	inline bool vis_pos(sdk::baseEntity *local, sdk::baseEntity *ent, math::vec3 &ent_pos)
	{
		sdk::iRay ray;
		ray.init(local->get_shoot_pos(), ent_pos);

		sdk::iTraceFilter filter;
		filter.skip = local;

		sdk::iTrace trace;
		sdk::ifaces::engine_trace->trace_ray(ray, (sdk::mask_shot | sdk::contents_grate), &filter, &trace);

		if (trace.ent != nullptr && trace.ent->get_index() == ent->get_index() || trace.fraction > 0.97f)
			return true;

		return false;
	}

	inline bool vis_pos_id_out(sdk::baseEntity *local, sdk::baseEntity *ent, math::vec3 &ent_pos, int &out)
	{
		sdk::iRay ray;
		ray.init(local->get_shoot_pos(), ent_pos);

		sdk::iTraceFilter filter;
		filter.skip = local;

		sdk::iTrace trace;
		sdk::ifaces::engine_trace->trace_ray(ray, (sdk::mask_shot | sdk::contents_grate), &filter, &trace);

		if (trace.ent != nullptr && trace.ent->get_index() == ent->get_index() || trace.fraction > 0.97f) {
			out = trace.hitbox;
			return true;
		}
		
		return false;
	}

	inline bool vis_pos_id(sdk::baseEntity *local, sdk::baseEntity *ent, math::vec3 &ent_pos, int id)
	{
		sdk::iRay ray;
		ray.init(local->get_shoot_pos(), ent_pos);

		sdk::iTraceFilter filter;
		filter.skip = local;

		sdk::iTrace trace;
		sdk::ifaces::engine_trace->trace_ray(ray, (sdk::mask_shot | sdk::contents_grate), &filter, &trace);

		if (trace.ent != nullptr && trace.ent->get_index() == ent->get_index() && trace.hitbox == id || trace.fraction > 0.97f) {
			return true;
		}

		return false;
	}

	inline float get_distance(const math::vec3 &src, const math::vec3 &dst)
	{
		return fmax(1.0f, math::fsqrt((src - dst).length()));
	}
}
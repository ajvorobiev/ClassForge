#include "script_component.hpp"
#include "script_config.hpp"

/**
* @class CfgPatches
* @brief Injection point addon into Arma 3
*/
class CfgPatches
{
	/**
	* @class rhs_c_2s3
	* @brief Injection point of 2S3
	* @ingroup patches
	*/
	class rhs_c_2s3
	{
		units[] = { rhs_2s3_tv }; /**< The unit classes injected by this addon. */
		weapons[] = {};
		requiredVersion = 1.38; /**< The minimum version of the game required. */
		requiredAddons[] = { "rhs_main", "rhs_c_heavyweapons", "rhs_decals", "rhs_optics", "rhs_c_troops" }; /**< The addons required. */
		version = VERSION;
	};
};

class DefaultEventhandlers;
class WeaponFireGun;
class WeaponCloudsGun;
class WeaponFireMGun;
class WeaponCloudsMGun;
class RCWSOptics;

class CfgMovesBasic
{
	class Default;
	class DefaultDie;
	class ManActions
	{
		rhs_2s3_commander = "rhs_2s3_commander";
	};
};

class CfgMovesMaleSdr : CfgMovesBasic
{
	class States
	{
		class Crew;
		class rhs_crew_in : Default
		{
			actions = "CargoActions";
			aiming = "aimingNo";
			aimingBody = "aimingNo";
			legs = "legsNo";
			head = "headNo";
			disableWeapons = 1;
			interpolationRestart = 1;
			soundEdge[] = { 0.45 };
			//seems that bounding Sphere is crucial to hit detection
			boundingSphere = 2.5;
			canPullTrigger = 0;
			leaning = "crewShake";
			rightHandIKCurve[] = { 1 };
			leftHandIKCurve[] = { 1 };
			rightLegIKCurve[] = { 1 };
			leftLegIKCurve[] = { 1 };
			ConnectTo[] = {};
			InterpolateTo[] = { "Unconscious", 0.1 };
		};
		class rhs_2s3_commander : rhs_crew_in
		{
			file = "\rhsafrf\addons\rhs_2s3\anims\2s3_commander.rtm";
			interpolateTo[] = { "kia_rhs_2s3_commander", 1 };
		};
		class kia_rhs_2s3_commander : DefaultDie
		{
			file = "\rhsafrf\addons\rhs_2s3\anims\2s3_commander.rtm";
		};
	};
};

/**
* @class CfgVehicles
* @brief Injection point of vehicles
*/
class CfgVehicles
{
	/**
	* @class LandVehicle
	*/
	class LandVehicle;

	/**
	* @class Tank
	* @private
	* @ingroup private
	*/
	class Tank : LandVehicle
	{
		class NewTurret;
		class Sounds;
		class HitPoints;
	};

	/**
	* @class Tank_F
	* @brief Base Tank_F definition
	* @private
	* @note Internal Arma 3 class.
	* @ingroup private
	*/
	class Tank_F : Tank
	{
		class Turrets
		{
			class MainTurret : NewTurret
			{
				class Turrets
				{
					class CommanderOptics;
				};
			};
		};
		class AnimationSources;
		class ViewPilot;
		class ViewOptics;
		class ViewCargo;
		class HeadLimits;
		class HitPoints : HitPoints
		{
			class HitHull;
			class HitEngine;
			class HitLTrack;
			class HitRTrack;
		};
		class Sounds : Sounds
		{
			class Engine;
			class Movement;
		};
		class EventHandlers;
	};

	/**
	* @class rhs_2s3tank_base
	* @brief 2S3 Base Class
	* @note Private class.
	* @ingroup private
	*/
	class rhs_2s3tank_base : Tank_F
	{
		category = "Armored";
		destrType = DestructDefault;
		availableForSupportTypes[] =
		{
			"Artillery"
		};
		artilleryScanner = 1;
		AGM_FCSEnabled = 0;

		// from tut
		author = "RHS";
		_generalMacro = "rhs_2s3tank_base";

		/// Vehicle class.
		vehicleClass = "rhs_vehclass_artillery";

		/// Display name string reference.
		displayName = "$STR_2S3M1_Name";
		accuracy = 0.3;

		model = "\rhsafrf\addons\rhs_2s3\rhs_2s3";
		picture = "\A3\armor_f_gamma\MBT_01\Data\UI\Slammer_M2A1_Base_ca.paa";
		Icon = "\rhsafrf\addons\rhs_2s3\ico\ico_2s3_ca.paa";

		/// The crew in the vehicle.
		crew = "rhs_msv_crew";
		typicalCargo[] = {};
		side = 0;

		/// The faction.
		faction = "rhs_faction_tv";

		getInAction = "GetInLow";
		getOutAction = "GetOutLow";
		driverAction = "driver_apcwheeled2_out";
		driverInAction = "driver_apcwheeled2_in";
		driverDoor = "hatchD";

#include "physx_config.hpp"
#include "sound_config.hpp"

		tracksSpeed = 1.35;
		wheelCircumference = 2.01;
		attenuationEffectType = "TankAttenuation";

		extCameraPosition[] = { 0, 2, -15 };

		//crewVulnerable = 1;

		cost = 1500000;
		damageResistance = 0.02;
		crewVulnerable = false;

		armor = 300;
		armorStructural = 6;
		driverOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpo170a"; //inside optics

		class HitPoints : HitPoints
		{
			class HitHull : HitHull {
				armor = 0.5;
				material = -1;
				name = "telo";
				visual = "zbytek";
				passThrough = 0;
				minimalHit = 0.14;
				explosionShielding = 0.009;
				radius = 0.25;
			};
			class HitEngine : HitEngine {
				armor = 1;
				material = -1;
				name = "motor";
				passThrough = 0;
				minimalHit = 0.24;
				explosionShielding = 0.009;
				radius = 0.33;
			};
			class HitLTrack : HitLTrack {
				armor = 0.5;
				material = -1;
				name = "pas_L";
				passThrough = 0;
				minimalHit = 0.25;
				explosionShielding = 0.5;
				radius = 0.3;
			};
			class HitRTrack : HitRTrack {
				armor = 0.5;
				material = -1;
				name = "pas_P";
				passThrough = 0;
				minimalHit = 0.25;
				explosionShielding = 0.5;
				radius = 0.3;
			};
		};

		class TransportMagazines
		{
			class _xx_30Rnd_545x39_AK
			{
				magazine = "rhs_30Rnd_545x39_7N10_AK";
				count = "10";
			};
			class _xx_HandGrenade_East
			{
				magazine = "rhs_mag_rgd5";
				count = "10";
			};
			//it should be signal pistol rounds
			class _xx_signal_rounds
			{
				magazine = "rhs_mag_nspn_red";
				count = "10";
			};
		};

		class TransportItems
		{
			class _xx_FirstAidKit
			{
				name = "FirstAidKit";
				count = 4;
			};
		};

		/**
		* @class Turrets
		* @brief 2S3 Turrets
		*/
		class Turrets : Turrets
		{
			/**
			* @class MainTurret
			* @brief Main Turret
			*/
			class MainTurret : MainTurret
			{
				/**
				* @class Turrets
				* @brief Main Turret Turrets
				*/
				class Turrets : Turrets
				{
					/**
					* @class CommanderOptics
					* @brief Commander Turret
					*/
					class CommanderOptics : CommanderOptics
					{
						// Animation class
						body = "obsTurret";
						gun = "obsGun";

						// Animation source
						animationSourceBody = "obsTurret";
						animationSourceGun = "obsGun";

						// Servos
						maxHorizontalRotSpeed = 0.45;
						maxVerticalRotSpeed = 0.07;
						stabilizedInAxes = StabilizedInAxesBoth;
						soundServo[] = { "A3\Sounds_F\vehicles\armor\noises\servo_best", db - 40, 1.0, 50 };
						minElev = -6;
						maxElev = +15;
						initElev = 0;
						minTurn = -171;
						maxTurn = +124;
						initTurn = 0;

						// Weapon and magazines
						memoryPointGun = "usti hlavne3";
						gunBeg = "usti hlavne3";
						gunEnd = "konec hlavne3";

						/// Weapons
						weapons[] = { rhs_weap_pkt_2s3 };	// you may need different weapon class to provide firing effects emit from proper position.

						/// Magazines
						magazines[] = { rhs_mag_762x54mm_250, rhs_mag_762x54mm_250, rhs_mag_762x54mm_250, rhs_mag_762x54mm_250, rhs_mag_762x54mm_250, rhs_mag_762x54mm_250 };

						// FCS
						turretInfoType = "RscWeaponZeroing";
						discreteDistance[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500 };
						discreteDistanceInitIndex = 2;

						// Optics view
						memoryPointGunnerOutOptics = "commanderview";
						memoryPointGunnerOptics = "commanderview";
						gunnerOpticsModel = "\A3\weapons_f\reticle\Optics_Commander_02_F";
						gunnerOutOpticsModel = "";
						gunnerOpticsEffect[] = {};	// post processing effets
						gunnerHasFlares = 1;	// flare visual effect when looking at light source
						class ViewOptics : ViewOptics {
							initAngleX = 0;
							minAngleX = -30;
							maxAngleX = +30;
							initAngleY = 0;
							minAngleY = -100;
							maxAngleY = +100;
							// Field of view values: 1 = 120�
							initFov = 0.155;
							minFov = 0.034;
							maxFov = 0.155;
							visionMode[] = { "Normal", "TI" };
							thermalMode[] = { 0, 1 };
						};

						// Gunner operations
						gunnerAction = mbt2_slot2b_out;
						gunnerInAction = rhs_2s3_commander;
						gunnerGetInAction = GetInHigh;
						gunnerGetOutAction = GetOutHigh;
						gunnerDoor = "hatchC";
						startEngine = 0;	// Turning this turret should not turn engine on.
						viewGunnerInExternal = 1;
						outGunnerMayFire = 0;	//remote controled
						inGunnerMayFire = 1;

						class HitPoints {
							class HitTurret	{
								armor = 0.3;
								material = -1;
								name = "vezVelitele";
								visual = "vezVelitele";
								passThrough = 0;
								minimalHit = 0.03;
								explosionShielding = 0.6;
								radius = 0.25;
							};
							class HitGun	{
								armor = 0.3;
								material = -1;
								name = "zbranVelitele";
								visual = "zbranVelitele";
								passThrough = 0;
								minimalHit = 0.03;
								explosionShielding = 0.6;
								radius = 0.25;
							};
						};
						selectionFireAnim = "zasleh3";
						class OpticsIn
						{
							class day1
							{
								initAngleX = 0;
								minAngleX = -30;
								maxAngleX = 30;
								initAngleY = 0;
								minAngleY = -100;
								maxAngleY = 100;
								initFov = 0.155;
								minFov = 0.155;
								maxFov = 0.155;
								visionMode[] = { "Normal", "NVG" };
								gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tkn3.p3d";
								gunnerOpticsEffect[] = { "TankGunnerOptics1", "OpticsBlur2", "OpticsCHAbera3" };
							};
							class day2
							{
								initAngleX = 0;
								minAngleX = -30;
								maxAngleX = 30;
								initAngleY = 0;
								minAngleY = -100;
								maxAngleY = 100;
								initFov = 0.047;
								minFov = 0.047;
								maxFov = 0.047;
								visionMode[] = { "Normal", "NVG" };
								gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tkn3.p3d";
								gunnerOpticsEffect[] = { "TankGunnerOptics1", "OpticsBlur2", "OpticsCHAbera3" };
							};
							class PZU3
							{
								initAngleX = 0;
								minAngleX = -30;
								maxAngleX = 30;
								initAngleY = 0;
								minAngleY = -100;
								maxAngleY = 100;
								initFov = 0.1;
								minFov = 0.1;
								maxFov = 0.1;
								visionMode[] = { "Normal" };
								gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_pzu3.p3d";
								gunnerOpticsEffect[] = { "TankGunnerOptics1", "OpticsBlur2", "OpticsCHAbera3" };
							};
						};
					};
				};

				// Coaxial gun
				memoryPointGun = "usti hlavne2";
				selectionFireAnim = "zasleh2";

				// Main gun
				gunBeg = "usti hlavne";
				gunEnd = "konec hlavne";

				// Weapons and magazines

				/// Weapons
				weapons[] = { RHS_Weap_2a33 };

				/// Magazines
				magazines[] = { "rhs_mag_HE_2a33", "rhs_mag_WP_2a33", "rhs_mag_LASER_2a33", "rhs_mag_SMOKE_2a33", "rhs_mag_ILLUM_2a33" };

				// Turret servos
				minElev = -5;
				//should be +60 but as I couldn't make arty firing at semi high angle, I use BIS values for SP arty instead
				maxElev = +77;
				initElev = 20;
				elevationMode = 3;
				soundServo[] = { "A3\Sounds_F\vehicles\armor\noises\servo_best", db - 40, 1.0, 50 };
				maxHorizontalRotSpeed = 0.45;	// 1 = 45?/sec
				maxVerticalRotSpeed = 0.07;		// 1 = 45?/sec

				// FCS
				//RscWeaponRangeArtilleryAuto
				turretInfoType = "rhs_gui_optic_2s3_computer";
				//turretInfoType = "RscWeaponRangeArtilleryAuto";
				discreteDistance[] = {
					100
				};
				discreteDistanceInitIndex = 0;	// start at 600 meters

				// Optics view
				memoryPointGunnerOptics = "gunnerview";
				gunnerOutOpticsModel = "";
				gunnerOutOpticsEffect[] = {};
				gunnerOpticsEffect[] = {};
				gunnerForceOptics = 1;

				// Field of view values: 1 = 120�
				class OpticsIn
				{
					class Wide : ViewOptics
					{
						initAngleX = 0;
						minAngleX = -30;
						maxAngleX = +30;
						initAngleY = 0;
						minAngleY = -100;
						maxAngleY = +100;
						initFov = 0.7 / 6;
						minFov = 0.7 / 6;
						maxFov = 0.7 / 6;
						visionMode[] = { "Normal", "NVG" };
						gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_op297.p3d";
						gunnerOpticsEffect[] = {};
					};
				};

				// Gunner operations and animations
				gunnerAction = mbt2_slot2a_out;
				gunnerInAction = mbt2_slot2a_in;
				gunnerDoor = "hatchC";
				forceHideGunner = 1;
				inGunnerMayFire = 1;	// set to 0 to let gunner look around the internal compartment if modeled
				viewGunnerInExternal = 1; // Needed to make gunner possible to be killed with penetrating rounds.

				class HitPoints {
					class HitTurret	{
						armor = 0.5;
						material = -1;
						name = "vez";
						visual = "vez";
						passThrough = 0;
						minimalHit = 0.15;
						explosionShielding = 0.009;
						radius = 0.25;
					};
					class HitGun	{
						armor = 0.5;
						material = -1;
						name = "zbran";
						visual = "";
						passThrough = 0;
						minimalHit = 0.15;
						explosionShielding = 0.001;
						radius = 0.25;
					};
				};
			};
		};

		/// Hidden selections for retexturability
		/// - [0] = camo1 => hull
		/// - [1] = camo2 => turret
		/// - [2] = camo3 => wheels
		/// - [3,4,5] = n1,n2,n3 => numbers
		hiddenSelections[] = { "camo1", "camo2", "camo3", "n1", "n2", "n3" };

		/// Default textures.
		hiddenSelectionsTextures[] =
		{
			"rhsafrf\addons\rhs_2s3\data\rhs_2s3_01_co.paa",
			"rhsafrf\addons\rhs_2s3\data\rhs_2s3_02_co.paa",
			"rhsafrf\addons\rhs_2s3\data\rhs_art_wheels_co.paa",
			"rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa",
			"rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa",
			"rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa"
		};

		class textureSources
		{
			class standard
			{
				displayName = "Standard";
				Author_Macro
					textures[] =
				{
					"rhsafrf\addons\rhs_2s3\data\rhs_2s3_01_co.paa",
					"rhsafrf\addons\rhs_2s3\data\rhs_2s3_02_co.paa",
					"rhsafrf\addons\rhs_2s3\data\rhs_art_wheels_co.paa"
				};
				factions[] =// This source should be available only for these factions
				{
					rhs_faction_tv
				};
			};
		};

		textureList[] =
		{
			"standard", 1
		};

		smokeLauncherGrenadeCount = 8; //Number of smoke shells launched at once
		smokeLauncherVelocity = 14; //Velocity which smoke shells are launched at
		smokeLauncherOnTurret = 1; //0 if smoke launchers are on hull, 1 if on turret
		smokeLauncherAngle = 120; //Angle within which smoke grenades are launched (actual spacing may end up smaller so use slighty higher number)

		class ViewOptics : ViewOptics {
			visionMode[] = { "Normal", "NVG" };
			initFov = 0.7;
			minFov = 0.7;
			maxFov = 0.7;
		};

		class AnimationSources :AnimationSources
		{
			class muzzle_rot_HMG { source = "ammorandom"; weapon = "rhs_weap_pkt_2s3"; };
			class recoil_source { source = "reload"; weapon = "RHS_Weap_2a33"; };
			class muzzle_hide_arty { source = "reload"; weapon = "RHS_Weap_2a33"; };
			class HatchC
			{
				source = "door";
				animPeriod = 0.8;
			};
			class HatchD : HatchC {};
		};

		class Damage {
			tex[] = {};
			mat[] = {

				"rhsafrf\addons\rhs_2s3\data\rhs_2s3_01new.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_dam_2s3_01new.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_destr_2s3.rvmat",

				"rhsafrf\addons\rhs_2s3\data\rhs_2s3_02new.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_dam_2s3_02new.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_destr_2s3.rvmat",

				"rhsafrf\addons\rhs_2s3\data\rhs_art_wheels.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_dam_art_wheels.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_destr_2s3.rvmat",

				"rhsafrf\addons\rhs_2s3\data\rhs_dam_art_tracks.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_dam_art_tracks.rvmat",
				"rhsafrf\addons\rhs_2s3\data\rhs_destr_2s3.rvmat",

				"a3\data_f\default.rvmat",
				"a3\data_f\default.rvmat",
				"a3\data_f\default_destruct.rvmat"
			};
		};

		class Exhausts
		{
			class Exhaust1
			{
				position = "exhaustl";
				direction = "exhaustl_dir";
				effect = "ExhaustEffectTankSide";
			};

			class Exhaust2
			{
				position = "exhaustr";
				direction = "exhaustr_dir";
				effect = "ExhaustEffectTankSide";
			};
		};

		class Reflectors {
			class Left {
				color[] = { 1900, 1300, 950 };
				ambient[] = { 5, 5, 5 };
				position = "l svetlo";
				direction = "konec l svetla";
				hitpoint = "l svetlo";
				selection = "L svetlo";
				size = 1;
				innerAngle = 100;
				outerAngle = 179;
				coneFadeCoef = 10;
				intensity = 1; //17.5
				useFlare = 0;
				dayLight = 0;
				flareSize = 1.0;
				class Attenuation {
					start = 1.0;
					constant = 0;
					linear = 0;
					quadratic = 0.25;
					hardLimitStart = 30;
					hardLimitEnd = 60;
				};
			};

			class Right : Left {
				position = "P svetlo";
				direction = "konec P svetla";
				hitpoint = "P svetlo";
				selection = "P svetlo";
			};

			class Right2 : Right {
				direction = "konec P svetla";
				useFlare = 1;
			};

			class Left2 : Left {
				direction = "konec l svetla";
				useFlare = 1;
			};
		};

		aggregateReflectors[] = { { "Left" }, { "Right" } };

		/**
		* @class EventHandlers
		* @brief Event Handlers
		*
		* Keep in mind when messing with that, that event handler fired is important for arty FX handling - R
		*/
		class EventHandlers : DefaultEventhandlers
		{
			/// Initialization handler
			init = "_this call SLX_XEH_EH_Init;_this call compile preProcessFile '\rhsafrf\addons\rhs_c_2s3\scripts\rhs_2s3_init.sqf'";

			/// HitPart handler
			hitpart = "_this call SLX_XEH_EH_HitPart;_this call rhs_fnc_hitHandler";
		};
	};

	/**
	* @class rhs_2s3_tv
	* @brief TV 2S3
	* @since 0.3.0
	* @ingroup 2s3
	*/
	class rhs_2s3_tv : rhs_2s3tank_base
	{
		Author_Macro
		_generalMacro = "rhs_2s3_tv";
		model = "\rhsafrf\addons\rhs_2s3\rhs_2s3";
		scope = 2;

		/// Display name
		displayName = "$STR_2S3M1_Name";
	};
};
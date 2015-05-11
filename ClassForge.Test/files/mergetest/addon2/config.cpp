
#include "script_component.hpp"
#include "script_config.hpp"

/**
 * @class CfgPatches
 * @brief Injection point addon into Arma 3
 */
class CfgPatches 
{ 
  /**
   * @class rhs_c_sprut
   * @brief Injection point of Sprut and BMD-4
   * @ingroup patches
   */
  class rhs_c_sprut
  { 
    units[] = {rhs_sprut_vdv,rhs_bmd4_vdv,rhs_bmd4m_vdv,rhs_bmd4ma_vdv}; /**< The unit classes injected by this addon. */ 
    weapons[] = {}; 
    requiredVersion = 1.32; /**< The minimum version of the game required. */
    requiredAddons[] = {
      "rhs_main",
      "rhs_c_heavyweapons",
      "rhs_decals",
      "rhs_optics",
      "rhs_c_troops",
      "A3_Armor_F",    
      "A3_Armor_F_Beta",
      "A3_Armor_F_T100K",
      "A3_CargoPoses_F"
    }; /**< The addons required. */
    version = VERSION;
  }; 
};

class DefaultEventhandlers;

class WeaponFireGun;
class WeaponCloudsGun;
class WeaponFireMGun;
class WeaponCloudsMGun;
class RCWSOptics;

#include "cfgFunctions.hpp"

class CfgMovesBasic 
{
  class Default;
  class DefaultDie;
  class ManActions 
  {
    rhs_sprut_commander = "rhs_sprut_commander";
    rhs_sprut_gunner = "rhs_sprut_gunner";
    rhs_bmd4_commander_in = "rhs_bmd4_commander_in";
    rhs_bmd4_gunner_in = "rhs_bmd4_gunner_in";
    rhs_bmd4_cargo_in = "rhs_bmd4_cargo_in";
  };
};
class CfgMovesMaleSdr : CfgMovesBasic 
{
  class States 
  {
    class Crew; 
    class rhs_crew_in: Default
    {
      actions = "CargoActions";
      aiming = "aimingNo";
      aimingBody = "aimingNo";
      legs = "legsNo";
      head = "headNo";
      disableWeapons = 1;
      interpolationRestart = 1;
      soundEdge[] = {0.45};
      //seems that bounding Sphere is crucial to hit detection
      boundingSphere = 2.5;
      canPullTrigger = 0;
      leaning = "crewShake";
      rightHandIKCurve[] = {1};
      leftHandIKCurve[] = {1};
      rightLegIKCurve[] = {1};
      leftLegIKCurve[] = {1};
      ConnectTo[] = {};
      InterpolateTo[] = {"Unconscious",0.1};
    };
    class rhs_sprut_commander : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_sprut_commander.rtm"; 
      interpolateTo[] = {"kia_rhs_sprut_commander",1};
    };
    class kia_rhs_sprut_commander : DefaultDie 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_sprut_commander.rtm"; 
    };
    class rhs_sprut_gunner : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_sprut_gunner.rtm"; 
      interpolateTo[] = {"kia_rhs_sprut_gunner",1};
    };
    class kia_rhs_sprut_gunner : DefaultDie 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_sprut_gunner.rtm"; 
    };

    class rhs_bmd4_commander_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_commander_in.rtm"; 
      interpolateTo[] = {"kia_rhs_bmd4_commander_in",1};
    };
    class kia_rhs_bmd4_commander_in : DefaultDie 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_commander_in.rtm"; 
    };
    class rhs_bmd4_gunner_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_gunner_in.rtm"; 
      interpolateTo[] = {"kia_rhs_bmd4_gunner_in",1};
    };
    class kia_rhs_bmd4_gunner_in : DefaultDie 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_gunner_in.rtm"; 
    };
    class rhs_bmd4_cargo_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_cargo_in.rtm"; 
      interpolateTo[] = {"kia_rhs_bmd4_cargo_in",1};
    };
    class kia_rhs_bmd4_cargo_in : DefaultDie 
    {
      file = "\rhsafrf\addons\rhs_c_sprut\anims\rhs_bmd4_cargo_in.rtm"; 
    };

  };
};

class CfgVehicles
{
  class LandVehicle;
  class Tank: LandVehicle
  {
    class NewTurret;
    class Sounds;
    class HitPoints;
  };
  
  class Tank_F: Tank
  {
    class Turrets
    {
      class MainTurret: NewTurret
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
    class HitPoints: HitPoints
    {
      class HitHull;
      class HitEngine;
      class HitLTrack;
      class HitRTrack;
    };
    class Sounds: Sounds
    {
      class Engine;
      class Movement;
    };
    class EventHandlers;
  };
  
  /**
   * @class rhs_a3spruttank_base
   * @brief Sprut-SD Base Class
   * @note Private class.
   * @ingroup private
   */
  class rhs_a3spruttank_base: Tank_F
  {
    category = "Armored";
    slingLoadCargoMemoryPoints[] = {"SlingLoadCargo1","SlingLoadCargo2","SlingLoadCargo3","SlingLoadCargo4"};
    AGM_FCSEnabled = 0;
    driveOnComponent[]={"Slide"};
    destrType=DestructDefault;
    author = "RHS";
    _generalMacro = "rhs_a3spruttank_base";
    
    /// Vehicle class
    vehicleClass = "rhs_vehclass_tank";
    displayName = "$STR_SPRUT_Name";
    accuracy = 0.3;
    
    model = "\rhsafrf\addons\rhs_sprut\rhs_sprut";
    picture = "\A3\armor_f_gamma\MBT_01\Data\UI\Slammer_M2A1_Base_ca.paa";
    Icon = "\rhsafrf\addons\rhs_sprut\icon\ico_sprutsd_ca.paa";
    mapSize = 11;
    scope = 0;

    weapons[] = {"rhs_weap_smokegen"};
    magazines[] = {"rhs_mag_smokegen"};
    
    /// Crew
    crew = "rhs_vdv_combatcrew";
    typicalCargo[] = {};
    side = 0;
    
    /// Faction
    faction = "rhs_faction_vdv";    

    driverCanSee=2+4+8;
    gunnerCanSee=2+4+8;
    commanderCanSee = 2+4+8;
    unitInfoType = "RHS_RscInfoSprut";
    tf_range_api = 35000; //r173 - range 35-40km with standard 4m metal antenna

    driverDoor="hatchD";
    driverAction = "driver_apcwheeled2_out";
    driverInAction = "driver_apcwheeled2_in";
    driverOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tvn5.p3d";
    
    #include "physx_config_sprut.hpp"
    #include "sound_config.hpp"
    
    tracksSpeed = 1.35;
    wheelCircumference = 2.01;
    attenuationEffectType = "TankAttenuation";
    
    cost = 1500000;
    damageResistance = 0.02;
    crewVulnerable = false;
    
    armor = 200;
    armorStructural=500;
    
    class HitPoints: HitPoints {
      class HitHull: HitHull {
        armor=0.4;
        material=-1;
        name="telo";
        visual="zbytek";
        passThrough=0;
        minimalHit = 0.54;
        explosionShielding=0;
        radius = 0.25;
      };
      class HitEngine: HitEngine {
        armor=0.45;
        material=-1;
        name="motor";
        passThrough=0;
        minimalHit = 0.139;
        explosionShielding=0.009;
        radius = 0.17;
      };
      class HitLTrack: HitLTrack {
        armor=0.15;
        material=-1;
        name="pas_L";
        passThrough=0;
        minimalHit = 0.15;
        explosionShielding=0.15;
        radius = 0.3;
      };
      class HitRTrack: HitRTrack {
        armor=0.15;
        material=-1;
        name="pas_P";
        passThrough=0;
        minimalHit = 0.15;
        explosionShielding=0.15;
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
     * @brief Turrets
     */
    class Turrets: Turrets 
    {
      /**
       * @class MainTurret
       * @brief Main Turret
       */
      class MainTurret: MainTurret 
      {
        /**
         * @class Turrets
         * @brief Main Turret Turrets
         */
        class Turrets: Turrets 
        {
          /**
           * @class CommanderOptics
           * @brief Commander Turret
           */
          class CommanderOptics: CommanderOptics 
          {
            // Animation class
            gunnerDoor="hatchC";
            body = "obsTurret";
            gun = "obsGun";
            
            // Animation source
            animationSourceBody = "obsTurret";
            animationSourceGun = "obsGun";
            
            // Servos
            maxHorizontalRotSpeed = 1.8;  // 1 = 45?/sec
            maxVerticalRotSpeed = 1.8;    // 1 = 45?/sec
            stabilizedInAxes = StabilizedInAxesBoth;
            soundServo[]= {"A3\Sounds_F\vehicles\armor\noises\servo_best", db-40, 1.0,50};
            minElev=-05;
            maxElev=+60;
            initElev=0;
            minTurn=-360;
            maxTurn=+360;
            initTurn=0;
            
            // Weapon and magazines
            memoryPointGun = "usti hlavne3";
            gunBeg = "usti hlavne3";
            gunEnd = "konec hlavne3";
            
            /// Weapons
            weapons[] = { SmokeLauncher};  // you may need different weapon class to provide firing effects emit from proper position.
            
            /// Magazines
            magazines[] = { SmokeLauncherMag};
            
            
            // FCS
            turretInfoType = "RHS_RscWeapon1k13_FCS";
            discreteDistance[] = {};
            discreteDistanceInitIndex = 0;
            
            // Optics view
            memoryPointGunnerOutOptics = "commanderview";
            memoryPointGunnerOptics= "commanderview";
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k13_3s_1x.p3d";
            gunnerOutOpticsModel = "";  
            gunnerOpticsEffect[] = {};  // post processing effets
            gunnerHasFlares = 1;  // flare visual effect when looking at light source
            class ViewOptics: ViewOptics {
              initAngleX=0;
              minAngleX=-30;
              maxAngleX=+30;
              initAngleY=0;
              minAngleY=-100;
              maxAngleY=+100;
              // Field of view values: 1 = 120?
              initFov=0.155;
              minFov=0.034;
              maxFov=0.155;
              visionMode[] = {"Normal","TI"};
              thermalMode[] = {0,1};
            };
            class OpticsIn {
              class DayMain: ViewOptics {
                initAngleX=0;
                minAngleX=-30;
                maxAngleX=+30;
                initAngleY=0;
                minAngleY=-100;
                maxAngleY=+100;
                initFov=0.7/1;
                minFov=0.7/1;
                maxFov=0.7/1;
                visionMode[] = {"Normal"};
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k13_3s_1x.p3d";
                gunnerOpticsEffect[] = {};
              };
              class Day2: DayMain {
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k13_3s_5x.p3d";
                initFov=0.7/5;
                minFov=0.7/5;
                maxFov=0.7/5;
              };
              class Day3: DayMain {
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k13_3s_14x.p3d";
                initFov=0.7/14;
                minFov=0.7/14;
                maxFov=0.7/14;
              };
              class night: daymain
              {
                initFov = 0.7/5;
                minFov = 0.7/5;
                maxFov = 0.7/5;
                visionMode[] = {"NVG"};
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k13_3s_5x_nvg.p3d";
              };
            };
            
            // Gunner operations
            gunnerAction = mbt2_slot2b_out;
            gunnerInAction = rhs_sprut_commander;
            gunnerGetInAction = GetInHigh;
            gunnerGetOutAction = GetOutHigh;
            startEngine = 0;  // Turning this turret should not turn engine on.
            viewGunnerInExternal = 1;
            outGunnerMayFire = 1;  
            inGunnerMayFire = 1;
            
            class HitPoints {
              class HitTurret  {
                armor = 0.7;
                material = -1;
                name = "vezVelitele";
                visual="vezVelitele";
                passThrough = 0;
                minimalHit = 0.13;
                explosionShielding=0.001;
                radius = 0.12;
              };
              class HitGun  {
                armor = 0.7;
                material = -1;
                name = "zbranVelitele";
                visual="zbranVelitele";
                passThrough = 0;
                minimalHit = 0.13;
                explosionShielding=0.001;
                radius = 0.12;
              };
            };
            selectionFireAnim = "zasleh3";
          };
        };
        
        gunnerDoor="hatchG";

        // Coaxial gun
        memoryPointGun = "usti hlavne2";
        selectionFireAnim = "zasleh2";
        
        // Main gun
        gunBeg = "usti hlavne";
        gunEnd = "konec hlavne";
        
        /// Weapons
        weapons[]={rhs_weap_2a75,rhs_weap_pkt_bmd_coax, rhs_weap_PL1,rhs_weap_902a};
        magazines[]=
        {
          rhs_mag_3bm42_10, rhs_mag_9m119rx_6,rhs_mag_3bk29_8,rhs_mag_3of26_6,rhs_mag_3d17_6,
          rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,
          rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,rhs_mag_762x54mm_250,
          rhs_lasermag
        }; //
        
        // Turret servos
        maxHorizontalRotSpeed = 0.53;  
        maxVerticalRotSpeed = 0.12;    
        minElev=-5;
        maxElev=+16;
        initElev=10;
        soundServo[]= {"A3\Sounds_F\vehicles\armor\noises\servo_best", db-40, 1.0,50};
        startEngine=0;

        // FCS
        turretInfoType = "RHS_RscWeaponSprutSD_FCS";
        discreteDistance[] = {};
        discreteDistanceInitIndex = 0;  
        
        // Optics view
        memoryPointGunnerOptics= "gunnerview";
        gunnerOutOpticsModel = "";
        gunnerOutOpticsEffect[] = {};
        gunnerOpticsEffect[] = {"TankGunnerOptics1", "WeaponsOptics", "OpticsCHAbera3"};
        gunnerForceOptics = 1;
        
        // Field of view values: 1 = 120?
        class OpticsIn {
          class DayMain: ViewOptics {
            initAngleX=0;
            minAngleX=-30;
            maxAngleX=+30;
            initAngleY=0;
            minAngleY=-100;
            maxAngleY=+100;
            initFov=0.7/9;
            minFov=0.7/9;
            maxFov=0.7/9;
            visionMode[] = {"Normal"};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_sprut.p3d";
            gunnerOpticsEffect[] = {};
          };
          class Rocket: DayMain {
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1k113.p3d";
            initFov=0.7/8;
            minFov=0.7/8;
            maxFov=0.7/8;
          };
          class Periscope: DayMain {
            initFov = 0.466666; 
            gunnerOpticsModel =  "\rhsafrf\addons\rhs_optics\vehicles\rhs_tvn5.p3d";
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera2"};
          };
          class night: daymain
          {
            initFov = 0.7/7;
            minFov = 0.7/7;
            maxFov = 0.7/7;
            visionMode[] = {"NVG"};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_empty";  
          };
        };
        
        // Gunner operations and animations
        gunnerAction = mbt2_slot2a_out;
        gunnerInAction = rhs_sprut_gunner;
        forceHideGunner = 0;
        inGunnerMayFire = 1;  // set to 0 to let gunner look around the internal compartment if modeled
        viewGunnerInExternal = 1; // Needed to make gunner possible to be killed with penetrating rounds.
        
        class HitPoints {
          class HitTurret  {
            armor = 0.5;
            material = -1;
            name = "vez";
            visual="vez";
            passThrough = 0;
            minimalHit = 0.14;
            explosionShielding=0.001;
            radius = 0.25;
          };
          class HitGun  {
            armor = 0.6;
            material = -1;
            name = "zbran";
            visual="";
            passThrough = 0;
            minimalHit = 0.13;
            explosionShielding=0.001;
            radius = 0.25;
          };
        };

        class Reflectors {
          class Right {
            color[]   = {1900, 1300, 950};
            ambient[]  = {5,5,5};
            position = "R svetlo";
            direction = "konec R svetla";
            hitpoint = "R svetlo";
            selection = "R svetlo";
            size     = 1;
            innerAngle   = 20;
            outerAngle   = 80;
            coneFadeCoef = 8;
            intensity   = 1; 
            useFlare   = 1;
            dayLight   = 0;
            flareSize   = 1.0;
            class Attenuation 
            {
              start     = 1.0;
              constant   = 0;
              linear     = 0;
              quadratic   = 0.25;
              hardLimitStart = 200;
              hardLimitEnd = 300;
            };
          };
          class Right2: Right {
            direction = "konec R svetla";
            useFlare   = 1;
          };
        };
        aggregateReflectors[] = {{"Right","Right2"}};
        armorLights = 0.1;


      };
    };
    
    /// Hidden selections for retexturability
    /// - [0,1,2] = n1,n2,n3 => numbers
    /// - 3 = i1 => insignia
    hiddenSelections[] = {"n1","n2","n3","i1"};
    
    hiddenSelectionsTextures[] = 
    {
      "rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa",
      "rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa",
      "rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa",
      "rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa"
    };
    
    // Damage textures - for sections: zbytek, vez, zbran, vezVelitele, zbranVelitele,
    class Damage {
      tex[] = {};
      mat[] = {

        "rhsafrf\addons\rhs_sprut\data\rhs_sprut_hull.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_sprut_hull.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_sprut_hull.rvmat",

        "rhsafrf\addons\rhs_sprut\data\rhs_sprut_turret.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_sprut_turret.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_sprut_turret.rvmat",

        "rhsafrf\addons\rhs_sprut\data\rhs_bmd34track.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_bmd34track.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_bmd34track.rvmat",

        "rhsafrf\addons\rhs_sprut\data\rhs_bmd34roadwheel.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_bmd34roadwheel.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_bmd34roadwheel.rvmat",

        "a3\data_f\default.rvmat",
        "a3\data_f\default.rvmat",
        "a3\data_f\default_destruct.rvmat"
      };
    };

    smokeLauncherGrenadeCount = 3;
    smokeLauncherVelocity = 17;
    smokeLauncherOnTurret = 1;
    smokeLauncherAngle = 60;


    class ViewOptics: ViewOptics {
      visionMode[] = {"Normal","NVG"};
      initFov         = 0.7;
      minFov          = 0.7;
      maxFov          = 0.7;
    };

    class Exhausts
    {
      class Exhaust1
      {
        position = "exhaustl";
        direction = "exhaustl_dir";
        effect = "ExhaustEffectTankBack";
      };
      
      class Exhaust2
      {
        position = "exhaustr";
        direction = "exhaustr_dir";
        effect = "ExhaustEffectTankBack";
      };
    };

    class Reflectors {
      class Left {
        color[]   = {1900, 1300, 950};
        ambient[]  = {5,5,5};
        position = "l svetlo";
        direction = "konec l svetla";
        hitpoint = "l svetlo";
        selection = "L svetlo";
        size     = 1;
        innerAngle   = 30;
        outerAngle   = 100;
        coneFadeCoef = 10;
        intensity   = 1; //17.5
        useFlare   = 0;
        dayLight   = 0;
        flareSize   = 1.0;
        class Attenuation {
          start     = 1.0;
          constant   = 0;
          linear     = 0;
          quadratic   = 0.25;
          hardLimitStart = 30;
          hardLimitEnd = 60;
        };
      };
      class Left2: Left {
        direction = "konec l svetla";
        useFlare   = 1;
      };
    };
    aggregateReflectors[] = {{"Left"}};
    armorLights = 0.1;
    
    class EventHandlers : DefaultEventhandlers
    {
      init = "_this call SLX_XEH_EH_Init;_this call compile preProcessFile '\rhsafrf\addons\rhs_c_sprut\scripts\rhs_sprut_init.sqf'";
      fired = "_this call SLX_XEH_EH_Fired;_this spawn RHS_fnc_Sprut_autoloader; _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
      hitpart = "_this call SLX_XEH_EH_HitPart;_this call rhs_fnc_hitHandler";
    };
    class AnimationSources
    {
      class muzzle_rot_coax {source = "ammorandom"; weapon = "rhs_weap_pkt_bmd_coax";};
      class recoil_source {source = "reload"; weapon = "rhs_weap_2a75";};
      class muzzle_hide_cannon: recoil_source {};
      class muzzle_rot_cannon: recoil_source
      {
        source="ammorandom";
      };
         class autoloader
         {
              source = "user";
              animPeriod = 1.25; // seconds per mil
              initPhase=0;
         };
      class elev {source="user";animperiod=16;};
      class lead {source="user";animperiod=22;};

        class smokecap_revolving_source
      {
      source = "revolving";
      weapon = "rhs_weap_902a";
      };

      class hatchC
      {
        source="door";
        animPeriod=0.80000001;
      };
      class HatchG: HatchC {};
      class HatchD: HatchC {};
    };
    
    class UserActions
    {
      class LowerSusp
      {
        displayName = $STR_UA_LowerSusp;
        position = ""; 
        radius = 5; 
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this <19000"; 
        //statement = "this setmass [18000*3,7];this setVelocity [0.01,0.01,0.01]"; 
        statement = "this setmass [(getmass this)*5,6];this setVelocity [0.01,0.01,0.01]"; 
        onlyForPlayer = true; 
      };
      class RaiseSusp: LowerSusp
      {
        displayName = $STR_UA_RaiseSusp;
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this >19000"; 
        //statement = "this setmass [18000,7];this setVelocity [0.01,0.01,0.01]"; 
        statement = "this setmass [18000,6];this setVelocity [0.01,0.01,0.01]"; 
      }; 
    };
    class ViewPilot: ViewPilot
    {
      initAngleX = 7;
      minAngleX = -15;
      maxAngleX = 25;
      initAngleY = 0;
      minAngleY = -90;
      maxAngleY = 90;
      initFov = 0.7;
      minFov = 0.7;
      maxFov = 0.7;
    };
  };

  /**
   * @class rhs_sprut_vdv
   * @brief VDV Sprut-SD
   * @ingroup 2s25
   */
  class rhs_sprut_vdv: rhs_a3spruttank_base
  {
    author = "RHS";
    _generalMacro = "rhs_sprut_vdv";
    scope = 2;
    displayName = "$STR_SPRUT_Name";
    
  };
  
  /**
   * @class rhs_bmd4_vdv
   * @brief VDV BMD-4
   * @ingroup bmd
   */
  class rhs_bmd4_vdv: rhs_a3spruttank_base
  {
    author = "RHS";
    _generalMacro = "rhs_bmd4_vdv";
    vehicleClass = "rhs_vehclass_ifv";
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd_34\rhs_bmd_4.p3d"; // path to model
    displayName = $STR_BMD4_Name; // as seen in the editor
    #include "physx_config_BMD4.hpp"
    Icon = "\rhsafrf\addons\rhs_bmd_34\data\icons\bmd4_mapicon_ca.paa";
    mapSize = 6.5;
    transportSoldier=5;
    unloadInCombat = 1;

    weapons[] = {"rhs_weap_smokegen"};
    magazines[] = {"rhs_mag_smokegen"};

    //ai will man those fake turrets yet those cargo places might be still manned using moveincargo
    cargoAction[] ={"YouShallNotSitHere"};
    cargoCompartments[] = {"Compartment3"};
    class SpeechVariants
    {
      class Default
      {
        speechSingular[] = {"veh_vehicle_APC_s"};
        speechPlural[] = {"veh_vehicle_APC_p"};
      };
    };
    textSingular = "BMP";
    textPlural = "BMPs";
    nameSound = "veh_vehicle_APC_s";    

    class Turrets: Turrets 
    {
      class MainTurret: MainTurret 
      {
        class Turrets: Turrets 
        {
          class CommanderOptics: CommanderOptics 
          {
            // Animation class
            body = "obsTurret";
            gun = "obsGun";
            gunnerDoor="hatchC";
            
            // Animation source
            animationSourceBody = "obsTurret";
            animationSourceGun = "obsGun";
            commanding = 5;
            
            // Servos
            maxHorizontalRotSpeed = 1.8;  // 1 = 45?/sec
            maxVerticalRotSpeed = 1.8;    // 1 = 45?/sec
            stabilizedInAxes = StabilizedInAxesBoth;
            soundServo[]= {"A3\Sounds_F\vehicles\armor\noises\servo_best", db-40, 1.0,50};
            minElev=-05;
            maxElev=+60;
            initElev=0;
            minTurn=-360;
            maxTurn=+360;
            initTurn=0;
            
            // Weapon and magazines
            memoryPointGun = "usti hlavne3";
            gunBeg = "usti hlavne3";
            gunEnd = "konec hlavne3";
            weapons[] = {};  // you may need different weapon class to provide firing effects emit from proper position.
            magazines[] = {};
            
            
            // FCS
            turretInfoType = "RHS_RscWeaponESSA_commander_FCS";
            discreteDistance[] = {};
            discreteDistanceInitIndex = 0;
            
            // Optics view
            memoryPointGunnerOutOptics = "commanderview";
            memoryPointGunnerOptics= "commanderview";
            gunnerOpticsModel = "\A3\weapons_f\reticle\Optics_Commander_02_F";
            gunnerOutOpticsModel = "";  
            gunnerOpticsEffect[] = {};  // post processing effets
            gunnerHasFlares = 1;  // flare visual effect when looking at light source
            class ViewOptics: ViewOptics {
              initAngleX=0;
              minAngleX=-30;
              maxAngleX=+30;
              initAngleY=0;
              minAngleY=-100;
              maxAngleY=+100;
              // Field of view values: 1 = 120?
              initFov=0.155;
              minFov=0.034;
              maxFov=0.155;
              visionMode[] = {"Normal","TI"};
              thermalMode[] = {0};
            };

            class OpticsIn {
              class Wide: ViewOptics {
                initAngleX=0;
                minAngleX=-30;
                maxAngleX=+30;
                initAngleY=0;
                minAngleY=-100;
                maxAngleY=+100;
                initFov=0.7/3;
                minFov=0.7/3;
                maxFov=0.7/3;
                visionMode[] = {"Normal","Ti"};
                thermalMode[] = {0}; //WHOT
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalscreen_empty.p3d";
              };
              class Medium: Wide {
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalscreen_empty.p3d";
                initFov=0.7/12;
                minFov=0.7/12;
                maxFov=0.7/12;
              };
              class Narrow: Wide {
                gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalscreen_empty.p3d";
                initFov=0.7/24;
                minFov=0.7/24;
                maxFov=0.7/24;
              };
            };
            
            // Gunner operations
            gunnerAction = mbt2_slot2b_out;
            gunnerInAction = rhs_bmd4_commander_in;
            gunnerGetInAction = GetInHigh;
            gunnerGetOutAction = GetOutHigh;
            startEngine = 0;  // Turning this turret should not turn engine on.
            viewGunnerInExternal = 1;
            outGunnerMayFire = 1;  
            inGunnerMayFire = 1;
            dontCreateAI=1;
            
            class HitPoints {
              class HitTurret  {
                armor = 0.7;
                material = -1;
                name = "vezVelitele";
                visual="vezVelitele";
                passThrough = 0;
                minimalHit = 0.13;
                explosionShielding=0.001;
                radius = 0.12;
              };
              class HitGun  {
                armor = 0.7;
                material = -1;
                name = "zbranVelitele";
                visual="zbranVelitele";
                passThrough = 0;
                minimalHit = 0.13;
                explosionShielding=0.001;
                radius = 0.12;
              };
            };
            selectionFireAnim = "zasleh3";
          };
        };
        
        gunnerDoor="hatchG";

        // Coaxial gun
        memoryPointGun = "usti hlavne2";
        selectionFireAnim = "zasleh2";
        
        // Main gun
        gunBeg = "usti hlavne";
        gunEnd = "konec hlavne";
        
        /// Weapons
        weapons[]={"rhs_weap_2a70", "rhs_weap_2a72", "rhs_weap_pkt_bmd_coax","rhs_weap_902a"};
        
        /// Magazines
        magazines[]={"rhs_mag_3UOF17_22", "rhs_mag_9m117_8", "rhs_mag_3uof8_340","rhs_mag_3ubr6_160","rhs_mag_9m113_4","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_3d17_6"};
        
        // Turret servos
        maxHorizontalRotSpeed = 0.55;  
        maxVerticalRotSpeed = 0.55;    
        minElev=-5;
        maxElev=+20;
        initElev=10;
        soundServo[]= {"A3\Sounds_F\vehicles\armor\noises\servo_best", db-40, 1.0,50};
        startEngine = 0; 

        // FCS
        turretInfoType = "RHS_RscWeaponESSA_FCS";
        discreteDistance[] = {};
        discreteDistanceInitIndex = 0;  // start at 600 meters
        
        // Optics view
        memoryPointGunnerOptics= "gunnerview";
        gunnerOutOpticsModel = "";
        
        gunnerOpticsEffect[] = {};
        gunnerOutOpticsEffect[] = {"TankGunnerOptics1","BWTV"};
        gunnerForceOptics = 1;
        commanding = 3;
        
        // Field of view values: 1 = 120?
        class OpticsIn {
          class Wide: ViewOptics {
            initAngleX=0;
            minAngleX=-30;
            maxAngleX=+30;
            initAngleY=0;
            minAngleY=-100;
            maxAngleY=+100;
            initFov=0.7/3;
            minFov=0.7/3;
            maxFov=0.7/3;
            visionMode[] = {"Normal","Ti"};
            thermalMode[] = {0}; //WHOT
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalscreen_empty.p3d";
          };
          class Medium: Wide {
            initFov=0.7/12;
            minFov=0.7/12;
            maxFov=0.7/12;
          };
          class Narrow: Wide {
            initFov=0.7/24;
            minFov=0.7/24;
            maxFov=0.7/24;
          };
        };
        
        // Gunner operations and animations
        gunnerAction = mbt2_slot2a_out;
        gunnerInAction = rhs_bmd4_gunner_in;
        forceHideGunner = 0;
        inGunnerMayFire = 1;  // set to 0 to let gunner look around the internal compartment if modeled
        viewGunnerInExternal = 1; // Needed to make gunner possible to be killed with penetrating rounds.
        
        class HitPoints {
          class HitTurret  {
            armor = 0.5;
            material = -1;
            name = "vez";
            visual="vez";
            passThrough = 0;
            minimalHit = 0.14;
            explosionShielding=0.001;
            radius = 0.25;
          };
          class HitGun  {
            armor = 0.6;
            material = -1;
            name = "zbran";
            visual="";
            passThrough = 0;
            minimalHit = 0.13;
            explosionShielding=0.001;
            radius = 0.25;
          };
        };
        class Reflectors {};
      };

      class GPMGTurret1 : NewTurret
      {
        proxyType = "CPGunner";
        proxyIndex = 2;
        body = "obsTurret2";
        gun = "obsGun2";
        animationSourceBody = "obsTurret2";
        animationSourceGun = "obsGun2";
        animationSourceHatch = "";
        gunnerDoor="hatchCR";
        selectionFireAnim = "zasleh3";
        gunnerName = $STR_MGFrontRight;
        hasGunner = 1;
        dontCreateAI=1;
        forceHideGunner = 1;
        primaryObserver = 0;
        primaryGunner = 0;
        commanding = 1;
        minElev = -10;
        maxElev = 10;
        minTurn = -10;
        maxTurn = 10;
        weapons[] = {"rhs_weap_pkt_bmd_bow1"};
        magazines[] = {"rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250"};
        ejectDeadGunner = 0;
        class CargoLight {
          ambient[] = {0.6,0,0.15,1};
          brightness = 0.007;
          color[] = {0,0,0,0};
        };
        gunBeg = "muzzle2";
        gunEnd = "end2";
        memoryPointGun = "memoryPointGun2";
        memoryPointGunnerOptics = "gunnerview3";
        memoryPointsGetInGunner = "pos cargo R";
        memoryPointsGetInGunnerDir = "pos cargo R dir";
        gunnerAction = mbt2_slot2a_out;
        gunnerInAction = rhs_bmd4_cargo_in;
        gunnerGetInAction = GetInHigh;
        gunnerGetOutAction = GetOutHigh;
        viewGunnerInExternal = 1;
        startEngine = 0; // Don't start engine when operate with gun
        class Turrets {};
        
        gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpp220a";
        gunnerOpticsColor[] = {1, 1, 1, 1};
        gunnerForceOptics = 1;
        gunnerOpticsEffect[] = {"TankGunnerOptics1", "WeaponsOptics", "OpticsCHAbera3"};
        class ViewOptics
        {
          initAngleX = 0;
          minAngleX = -30;
          maxAngleX = 30;
          initAngleY = 0;
          minAngleY = -100;
          maxAngleY = 100;
          opticsZoomMin = 0.166666;
          opticsZoomMax = 0.166666;
          distanceZoomMin = 200;
          distanceZoomMax = 2000;
          initFov = 0.166666;
          minFov =  0.166666;
          maxFov =  0.166666;
        };
        unloadInCombat = 1;
      };
      class LeftBack : NewTurret
      {
      
        proxyType = "CPGunner";
        body = "LB_Seat_turret";
        gun = "LB_Seat_Gun";
        animationSourceBody = "LB_Seat_Turret";
        animationSourceGun = "LB_Seat_Gun";
        animationSourceHatch = "";
        selectionFireAnim = "";
        gunnerDoor="hatchCL";
        minElev = 0;
        maxElev = 0;
        initTurn = 60;
        minTurn = 60;
        maxTurn = 60;
        maxHorizontalRotSpeed = 0;
        maxVerticalRotSpeed = 0;
        proxyIndex = 4;
        memoryPointsGetInGunner = "pos cargo L";
        memoryPointsGetInGunnerDir = "pos cargo L dir";
        gunnerName = $STR_CargoBackLeft;
        commanding = 2;
        gunBeg = "";
        gunEnd = "";
        memoryPointGun = "";
        memoryPointGunnerOptics = "lseat_view";
        gunnerAction = mbt2_slot2a_out;
        gunnerInAction = rhs_bmd4_cargo_in;
        gunnerGetInAction = GetInHigh;
        gunnerGetOutAction = GetOutHigh;
        weapons[] = {};
        magazines[] = {};
        forceHideGunner = 1;
        hasGunner = 1;
        dontCreateAI=1;
        primaryGunner = 0;
        primaryObserver = 0;
        
        gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpo170a";
        gunnerOpticsColor[] = {1, 1, 1, 1};
        gunnerForceOptics = 1;
        startEngine = 0;
        class ViewOptics 
        {
          initAngleX = 0;
          minAngleX = -110;
          maxAngleX = 110;
          initAngleY = 0;
          minAngleY = -110;
          maxAngleY = 110;
          opticsZoomMin = 0.700000;
          opticsZoomMax = 0.700000;
          distanceZoomMin = 20;
          distanceZoomMax = 2000;
          initFov = 0.700000;
          minFov =  0.700000;
          maxFov =  0.700000;
        };
        unloadInCombat = 1;
        viewGunnerInExternal = 1;
      };
      class RightBack : LeftBack
      {
        body = "RB_Seat_Turret";
        gun = "RB_Seat_gun";
        animationSourceBody = "RB_Seat_Turret";
        animationSourceGun = "RB_Seat_Gun";
        initTurn = -60;
        minTurn = -60;
        maxTurn = -60;
        gunnerName = $STR_CargoBackRight;
        memoryPointGunnerOptics = "rseat_view";
        gunnerDoor="hatchCR";
        commanding = 2;
        proxyIndex = 5;
        memoryPointsGetInGunner = "pos cargo R";
        memoryPointsGetInGunnerDir = "pos cargo R dir";
      };
      class MainFront : LeftBack
      {
        body = "LF_Seat_turret";
        gun = "LF_Seat_gun";
        animationSourceBody = "LF_Seat_Turret";
        animationSourceGun = "LF_Seat_Gun";
        initTurn =0;
        minTurn = 0;
        maxTurn =0;
        gunnerName = Front Cargo;
        memoryPointGunnerOptics = "gunnerView2";
        commanding = 1;
        proxyIndex = 3;
      };

    };
    class AnimationSources
    {
      class recoil_source {source = "reload"; weapon = "rhs_weap_2a70";};
      class recoil_source2 {source = "reload"; weapon = "rhs_weap_2a72";};
      class muzzle_hide_cannon: recoil_source {};
      class muzzle_rot_cannon: recoil_source
      {
        source="ammorandom";
      };


        class smokecap_revolving_source
      {
      source = "revolving";
      weapon = "rhs_weap_902a";
      };

      class muzzle_hide_hmg: recoil_source2 {};
      class muzzle_rot_hmg: recoil_source2
      {
        source="ammorandom";
      };
      class muzzle_rot_mg1: muzzle_rot_hmg { weapon = "rhs_weap_pkt_bmd_coax";};
      class muzzle_rot_mg2: muzzle_rot_hmg { weapon = "rhs_weap_pkt_bmd_bow1";};

         class autoloader
         {
              source = "user";
              animPeriod = 1.25; // seconds per mil
              initPhase=0;
         };
      class elev {source="user";animperiod=16;};
      class lead {source="user";animperiod=22;};

      class hatchCL
      {
        source="door";
        animPeriod=0.80000001;
      };
      class hatchCLB: hatchCL {};
      class hatchCR: hatchCL {};
      class HatchC: hatchCL {};
      class HatchG: HatchC {};
      class HatchD: HatchC {};
    };

    class Damage {
      tex[] = {};
      mat[] = {

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd3_01.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd3_01.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd3_01.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4_02.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4_02.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4_02.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4_03.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4_03.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4_03.rvmat",

        "rhsafrf\addons\rhs_sprut\data\rhs_bmd34track.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_bmd34track.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_bmd34track.rvmat",

        "rhsafrf\addons\rhs_sprut\data\rhs_bmd34roadwheel.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_dam_bmd34roadwheel.rvmat",
        "rhsafrf\addons\rhs_sprut\data\rhs_destr_bmd34roadwheel.rvmat",

        "a3\data_f\default.rvmat",
        "a3\data_f\default.rvmat",
        "a3\data_f\default_destruct.rvmat"
      };
    };

    class UserActions
    {
      class LowerSusp
      {
        displayName = $STR_UA_LowerSusp;
        position = ""; 
        radius = 5; 
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this <15000"; 
        statement = "this setmass [(getmass this)*4,7];this setVelocity [0.01,0.01,0.01]"; 
        onlyForPlayer = true; 
      };
      class RaiseSusp: LowerSusp
      {
        displayName = $STR_UA_RaiseSusp;
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this >15000"; 
        statement = "this setmass [(getmass this)/4,7];this setVelocity [0.01,0.01,0.01]"; 
      }; 
    };

    class TransportMagazines
    {
      class _xx_30Rnd_545x39_AK
      {
        magazine = "rhs_30Rnd_545x39_7N10_AK";
        count = "30*1";
      };
      class _xx_10Rnd_762x54_SVD
      {
        magazine = "rhs_10Rnd_762x54mmR_7N1";
        count = "10*1";
      };
      class _xx_100Rnd_762x54_PK
      {
        magazine = "rhs_100Rnd_762x54mmR";
        count = "3*1";
      };
      class _xx_SmokeShellRed
      {
        magazine = "rhs_mag_rdg2_white";
        count = "2*1";
      };
      class _xx_HandGrenade_East
      {
        magazine = "rhs_mag_rgd5";
        count = "9*1";
      };
      class _xx_1Rnd_HE_GP25
      {
        magazine = "rhs_VOG25";
        count = "20*1";
      };
      class _xx_1Rnd_SMOKE_GP25
      {
        magazine = "rhs_vg40op_white";
        count = "5*1";
      };
      class _xx_FlareWhite_GP25
      {
        magazine = "rhs_GRD40_white";
        count = "5*1";
      };
      class _xx_RPG26
      {
        magazine = "rhs_rpg26_mag";
        count = "2*1";
      };
    };
    class TransportWeapons
    {
      class _xx_AK74M
      {
        weapon = "rhs_weap_ak74m";
        count = 2;
      };
       class _xx_RPG26
      {
        weapon = "rhs_weap_rpg26";
        count = 2;
      };
    };
    class TransportItems
    {
      class _xx_FirstAidKit
      {
        name = "FirstAidKit";
        count = 4;
      };
      class _xx_Medikit
      {
        name = "Medikit";
        count = 1;
      };
    };
    class TransportBackpacks
    {
      class _xx_rhs_sidor
      {
        backpack = "rhs_sidor";
        count = 7;
      };
    };


    class EventHandlers : EventHandlers
    {
      init = "_this call SLX_XEH_EH_Init;_this call compile preProcessFile '\rhsafrf\addons\rhs_c_sprut\scripts\rhs_sprut_init.sqf'";
      fired = "_this call SLX_XEH_EH_Fired;_this spawn RHS_fnc_BMD4_autoloader; _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
    };
        
  };
  
  /**
   * @class rhs_bmd4_vdv
   * @brief VDV BMD-4M
   * @ingroup bmd
   */
  class rhs_bmd4m_vdv: rhs_bmd4_vdv
  {
    author = "RHS";
    _generalMacro = "rhs_bmd4_vdv";
    vehicleClass = "rhs_vehclass_ifv";
    scope = 2;
    #include "physx_config_BMD4M.hpp"
    model = "\rhsafrf\addons\rhs_bmd_34\rhs_bmd_4m.p3d"; // path to model
    displayName = $STR_BMD4M_Name; // as seen in the editor
    
    class Turrets: Turrets 
    {
      class MainTurret: MainTurret 
      {
        class Turrets: Turrets 
        {
          class CommanderOptics: CommanderOptics {};
        };
      };
      class GPMGTurret1 : GPMGTurret1 {};
      class GPMGTurret2 : GPMGTurret1 
      {
        weapons[] = {"rhs_weap_pkt_bmd_bow2"};
        body = "LF_Seat_turret";
        gun = "LF_Seat_gun";
        animationSourceBody = "LF_Seat_Turret";
        animationSourceGun = "LF_Seat_Gun";
        gunnerName = Left Hull Gunner;
        memoryPointGunnerOptics = "gunnerView2";
        commanding = 1;

        gunnerDoor="hatchCL";
        memoryPointsGetInGunner = "pos cargo L";
        memoryPointsGetInGunnerDir = "pos cargo L dir";
        memoryPointGun = "memoryPointGun3";
        gunBeg = "muzzle3";
        gunEnd = "end3";
        selectionFireAnim = "zasleh4";
        proxyIndex = 3;
      };
      class RightBack : RightBack {};
      class LeftBack : LeftBack 
      {
        gunnerDoor="hatchCLB";
        memoryPointsGetInGunner = "pos gunner";
        memoryPointsGetInGunnerDir = "pos gunner dir";
      };
    };
    class Damage {
      tex[] = {};
      mat[] = {

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4_02.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4_02.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4_02.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4_03.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4_03.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4_03.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_01.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_01.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_01.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_01a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_01a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_01a.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_02a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_02a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_02a.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_a.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_a.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_t.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_t.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_t.rvmat",

        "rhsafrf\addons\rhs_bmd_34\data\rhs_bmd4m_w.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_dam_bmd4m_w.rvmat",
        "rhsafrf\addons\rhs_bmd_34\data\rhs_destr_bmd4m_w.rvmat",

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

    class AnimationSources: AnimationSources
    {
      class muzzle_rot_mg3 {source="ammorandom"; weapon = "rhs_weap_pkt_bmd_bow2";};

        class smokecap_revolving_source
      {
      source = "revolving";
      weapon = "rhs_weap_902a";
      };
    };
  };
  
  /**
   * @class rhs_bmd4ma_vdv
   * @brief VDV BMD-4M Armored
   * @ingroup bmd
   */
  class rhs_bmd4ma_vdv: rhs_bmd4m_vdv
  {
    author = "RHS";
    _generalMacro = "rhs_bmd4_vdv";
    vehicleClass = "rhs_vehclass_ifv";
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd_34\rhs_bmd_4ma.p3d"; // path to model
    displayName = $STR_BMD4MA_Name; // as seen in the editor
  };
  

};
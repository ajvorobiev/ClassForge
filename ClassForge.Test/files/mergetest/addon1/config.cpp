
#include "script_component.hpp"
#include "script_config.hpp"

class CfgPatches 
{ 
  class rhs_c_bmd
  { 
    units[] = 
    {
      rhs_bmd1,
      rhs_bmd1k,
      rhs_bmd1p,
      rhs_bmd1pk,
      rhs_bmd1r,
      rhs_bmd2,
      rhs_bmd2k,
      rhs_bmd2m
    }; 
    weapons[] = {}; 
    requiredVersion = 1.32;
    requiredAddons[] = {"rhs_main","rhs_c_heavyweapons","rhs_decals","rhs_optics","rhs_c_troops"};
    version = VERSION;
  }; 
};

/*******************************************************************************
* CfgMovesBasic : spawns the animation classes                                 *
*******************************************************************************/
class CfgMovesBasic 
{
  class Default;
  class DefaultDie;
  class ManActions 
  {
    rhs_bmd_commander = "rhs_bmd_commander";
    rhs_bmd_mggunner = "rhs_bmd_mggunner";
    rhs_bmd_gunner = "rhs_bmd_gunner";
    rhs_bmd_commander_in = "rhs_bmd_commander_in";
    rhs_bmd_gunner_in = "rhs_bmd_gunner_in";
    rhs_bmd_gunner_r_in = "rhs_bmd_gunner_r_in";
    rhs_bmd_cargo_in = "rhs_bmd_cargo_in";

  };
};
/*******************************************************************************
* CfgMovesMaleSdr defines the classes of crew animations                       *
* inherits from CfgMovesBasic                                                  *
*******************************************************************************/
class CfgMovesMaleSdr : CfgMovesBasic 
{
  class States 
  {
    class Crew; //External Inheritance class
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

    class KIA_rhs_bmd_commander: DefaultDie
    {
      actions = "DeadActions";
      file = "\rhsafrf\addons\rhs_bmd\anims\kia_rhs_bmd_commanderout.rtm"; 
      speed = 0.5;
      looped = 0;
      terminal = 1;
      soundEnabled = 0;
      connectTo[]=
      {
        "Unconscious",
        0.1
      };
    };
    class KIA_rhs_bmd_gunner : KIA_rhs_bmd_commander 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\kia_rhs_bmd_gunnerout.rtm"; 
    };

    class rhs_bmd_commander : Crew 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd_commanderout.rtm"; 
      interpolateTo[] = {"KIA_rhs_bmd_commander",1};
    };
    class rhs_bmd_mggunner : Crew 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd_mggunnerout.rtm"; 
      interpolateTo[] = {"KIA_rhs_bmd_gunner",1};
    };
    class rhs_bmd_gunner : Crew 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd_gunnerout.rtm"; 
      interpolateTo[] = {"KIA_rhs_bmd_gunner",1};
    };

    class rhs_bmd_commander_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_commander_in.rtm"; 
      interpolateTo[] = {"rhs_bmd_commander_in",1};
    };
    class rhs_bmd_gunner_r_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_gunner_r_in.rtm"; 
      interpolateTo[] = {"rhs_bmd_gunner_r_in",1};
    };
    class rhs_bmd_gunner_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_gunner_in.rtm"; 
      interpolateTo[] = {"rhs_bmd_gunner_in",1};
    };
    class rhs_bmd_cargo_in : rhs_crew_in 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_cargo_in.rtm"; 
      interpolateTo[] = {"rhs_bmd_cargo_in",1};
    };

    class KIA_rhs_bmd_commander_in : KIA_rhs_bmd_commander 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_commander_in.rtm"; 
    };
    class KIA_rhs_bmd_gunner_r_in : KIA_rhs_bmd_commander 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_gunner_r_in.rtm"; 
    };
    class KIA_rhs_bmd_gunner_in : KIA_rhs_bmd_commander 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_gunner_in.rtm"; 
    };
    class KIA_rhs_bmd_cargo_in : KIA_rhs_bmd_commander 
    {
      file = "\rhsafrf\addons\rhs_bmd\anims\rhs_bmd1_cargo_in.rtm"; 
    };



  };
};

class NewTurret;
class ViewOptics;
//class Sounds;
class Turrets;
class MainTurret;
class Engine;
class Movement;
class Reflectors;
class AnimationSources;
class DefaultEventHandlers;
class HitPoints;

#include "cfgFunctions.hpp"

class CfgVehicles 
{
  /*******************************************************************************
  * External class references to CATracked                  *
  *******************************************************************************/
  
  
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
  class rhs_bmd_base : Tank_F
  {
    category = "Armored";
    slingLoadCargoMemoryPoints[] = {"SlingLoadCargo1","SlingLoadCargo2","SlingLoadCargo3","SlingLoadCargo4"};
    AGM_FCSEnabled = 0;
    driveOnComponent[]={"Slide"};
    destrType=DestructDefault;
    driverDoor="hatchD";
    // Defenition
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd2.p3d"; // path to model
    Author_Macro
    displayName= $STR_BMD2_Name; // as seen in the editor
    vehicleClass = "rhs_vehclass_ifv";
    side = 0; // East, affiliation of the vehicle
    faction = "rhs_faction_vdv"; //faction
    icon = "\rhsafrf\addons\rhs_bmd\rhs_bmd2_icon.paa";
    picture = "\rhsafrf\addons\rhs_bmd\rhs_bmd2_pic_ca.paa";
    scope = 0;
    mapSize = 5.4; // size of editor map icon in meters
    class SpeechVariants
    {
      class Default
      {
        speechSingular[] = {"veh_vehicle_APC_s"};
        speechPlural[] = {"veh_vehicle_APC_p"};
      };
    };
    textSingular = "BMD";
    textPlural = "BMDs";
    nameSound = "veh_vehicle_APC_s";

    
    weapons[] = {"rhs_weap_smokegen"};
    magazines[] = {"rhs_mag_smokegen"};
    
    #include "physx_config_bmd1.hpp"
    #include "sound_config.hpp"

    tf_range_api = 17000; //r123m - range 15-20km with standard metal antenna

    unitInfoType = "RHS_RscUnitInfoEastTank";
    
    tracksSpeed = 1.35;
    wheelCircumference = 2.375;
    
    // Cargo and Crew
    crew = "rhs_vdv_combatcrew"; // crew of the vehicle
    hasCommander = 1;
    hasGunner = 1;
    transportSoldier = 5;
    typicalCargo[] = {}; // cargo of the vehicle, refers to the unit classnames
    ejectDeadCargo = false;
    unloadInCombat = true;
    forceHideDriver = 0;
    viewCargoShadow = true;
    viewCargoShadowDiff = 1;
    
    // Unit animations
    //driverAction = "Abrams_Driverout"; // driver out animation
    //driverInAction = "Abrams_Driver"; // driver in animation
    
    driverAction = "driver_apcwheeled2_out";
    driverInAction = "driver_apcwheeled2_in";
    cargoAction[] = {"YouShallNotSitHere"};
    cargoCompartments[] = {"Compartment33"};

    getInAction = "GetInLow";
    getOutAction = "GetOutLow";
    cargoGetInAction[] = {"GetInLow"};
    cargoGetOutAction[] = {"GetOutLow"};
    
    // Performance
    accuracy = 0.7; //?
    minSpeed = 0.45; // crosscountry
    maxSpeed = 80; // on roads
    acelleration = 9; // acceleration
    brakeDistance = 25;
    preferRoads = false;
    animated = true; //? not sure if it does anything
    
    type = 1; //?
    cost = 3000000; // cost of the vehicle in Warfare
    camouflage = 5; // visibility of the vehicle, the lower the number the less AI spots it
    
    // Hidden selections
    hiddenSelections[] = {"body1","body2","body3","n1","n2","n3","i1","i2"}; // selections for interchangeable textures
    hiddenSelectionsTextures[] = {
      "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_co.paa",
      "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02_co.paa",
      "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_co.paa",
      "rhsafrf\addons\RHS_Decals\Data\Labels\Misc\no_ca.paa"
    };
    class textureSources
    {
      class standard 
      {
        displayName="Standard"; 
        Author_Macro
        textures[]=
        {
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_co.paa"
        };
        factions[]=// This source should be available only for these factions
        {
          rhs_faction_vmf, rhs_faction_vdv,rhs_faction_vdv,rhs_faction_vv
        };
      };
      class Camo: standard
      {
        displayName="Chedaki"; 
        Author_Macro
        textures[]=
        {
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_chdkz_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02_chdkz_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_chdkz_co.paa"
        };
      };
    };
    textureList[]=
    {
      "standard", 1,
      "Camo", 0
    };
    
    // Animation 
    selectionLeftOffset = "pasanimL"; // track left
    selectionRightOffset = "pasanimP"; // track right
    animationSourceHatch = "hatchDriver";

    #define hideMacro(name) class ##name##: r1_source {};
    #define hideMacroAction(name,action) class ##name##: r1_source {displayName=##action##;};

    class AnimationSources : AnimationSources 
    {
      class muzzleMG1
      {
        source="ammorandom";
        weapon = "rhs_weap_pkt_btr";
      };
      class muzzleMG2: muzzleMG1
      {
        weapon = "rhs_weap_pkt_bmd_bow1";
      };
      class muzzleMG3: muzzleMG1
      {
        weapon = "rhs_weap_pkt_bmd_bow2";
      };
      class r1_source
      {
        source = "user";
        mass=1;
        animPeriod = 0.000001; // ditto
        initPhase = 0; // ditto
      };
      hideMacro(r2_source)
      hideMacro(r3_source)
      hideMacro(r4_source)
      hideMacro(r5_source)
      hideMacro(r6_source)
      hideMacro(r7_source)
      hideMacro(r8_source)
      hideMacro(r9_source)
      hideMacro(r10_source)
      hideMacro(r11_source)
      hideMacro(r12_source)
      hideMacro(maljutka_hide_source)
      hideMacro(maljutka_unhide)
      hideMacro(at14_l_hide_source)
      hideMacro(at14_r_hide_source)

      hideMacroAction(crate_l1_unhide,"hide l1 crate")
      hideMacroAction(crate_l2_unhide,"hide l2 crate")
      hideMacroAction(crate_l3_unhide,"hide l3 crate")
      hideMacroAction(crate_r1_unhide,"hide r1 crate")
      hideMacroAction(crate_r2_unhide,"hide r2 crate")
      hideMacroAction(crate_r3_unhide,"hide r3 crate")
      hideMacroAction(wood_1_unhide,"hide wood log 1")
      hideMacroAction(wood_2_unhide,"hide wood log 2")
      class antena2_hide: r1_source
      {
        initPhase = 1; 
        displayName="hide additional antenna";
      };

      class HatchC
      {
        source="door";
        animPeriod=0.8;
      };
      class HatchG: HatchC {};
      class HatchMG: HatchC {};
      class HatchD: HatchC {};
    };
    
    class UserActions
    {
      class LowerSusp
      {
        displayName = $STR_UA_LowerSusp;
        position = ""; 
        radius = 5; 
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this <8400"; 
        statement = "this setmass [7600*1.7,6];this setVelocity [0.01,0.01,0.01]"; 
        onlyForPlayer = true; 
      };
      class RaiseSusp: LowerSusp
      {
        displayName = $STR_UA_RaiseSusp;
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this >12000"; 
        statement = "this setmass [7600,6];this setVelocity [0.01,0.01,0.01]"; 
      }; 
    };
    
    // Transport magazines
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
        count = "10*1";
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
        count = 4;
      };
    };
    
    transportMaxMagazines = 160;
    transportMaxWeapons = 10;
    
    
    class Damage 
    {
      tex[] = {};
      mat[] = {
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01.rvmat", 
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_damage.rvmat", 
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_destruct.rvmat",

        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02.rvmat", 
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02_damage.rvmat", 
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_02_destruct.rvmat",

        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat", 
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_destruct.rvmat",

        "rhsafrf\addons\rhs_bmd\data\sa_mantle.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_mantle.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_mantle_destruct.rvmat"
      };
    };
    
    // Protection and damage
    damageResistance = 0.01796;        
    secondaryExplosion = 1;
    armor = 160; // overall armor
    armorStructural = 400;
    threat[] = {0.5, 0.5, 1}; // ?

    class HitPoints: HitPoints 
    {
      class HitHull: HitHull {
        armor=0.4;
        material=-1;
        name="telo";
        visual="zbytek";
        passThrough=0;
        minimalHit = 0.54;
        explosionShielding=0.5;
        radius = 0.25;
      };
      class HitEngine: HitEngine {
        armor=0.45;
        material=-1;
        name="motor";
        passThrough=0;
        minimalHit = 0.139;
        explosionShielding=0.009;
        radius = 0.27;
      };
      class HitLTrack: HitLTrack {
        armor=0.3;
        material=-1;
        name="pas_L";
        passThrough=0;
        minimalHit = 0.35;
        explosionShielding=0.25;
        radius = 0.3;
      };
      class HitRTrack: HitRTrack {
        armor=0.3;
        material=-1;
        name="pas_P";
        passThrough=0;
        minimalHit = 0.35;
        explosionShielding=0.25;
        radius = 0.3;
      };
      class HitFuel
      {
        armor=1;
        explosionShielding=1;
        material=-1;
        passThrough=1;
        name="palivo";
        visual="";
      };
    };
    
    // Smoke
    smokeLauncherGrenadeCount = 0;
    smokeLauncherVelocity = 14;
    smokeLauncherOnTurret = 0;
    smokeLauncherAngle = 70;
    
    // Memory points
    memoryPointGun = "kulas"; // machinegun
    memoryPointsGetInGunner = "pos gunner"; // get in gunner
    memoryPointsGetInDriver = "pos driver"; // get in driver
    memoryPointsGetInCargo = "pos cargo"; // get in cargo
    memoryPointsGetInGunnerDir = "pos gunner dir"; // direction gunner
    memoryPointsGetInDriverDir = "pos driver dir"; // direction driver
    memoryPointsGetInCargoDir = "pos cargo dir"; // cargo dir
    memoryPointSupply = "doplnovani"; // supply point
    memoryPointTrack1L = "Stopa ll"; // track memory point L1
    memoryPointTrack1R = "Stopa lr"; // track memory point R1
    memoryPointTrack2L = "Stopa rl"; // track memory point L2
    memoryPointTrack2R = "Stopa rr"; // track memory point R2
    memoryPointDriverOptics = "driverview";
    
    
    // Exhaust class
    class Exhausts
    {
      // left exhaust
      class Exhaust1 
      {
        position = "vyfuk start"; // start of exhaust memory point
        direction = "vyfuk konec"; // end of exhaust memory point
        effect = "ExhaustEffectTankSide"; // type of effect
      };
      // right exhaust 
      class Exhaust2 
      {
        position = "vyfuk1 start"; // ditto
        direction = "vyfuk1 konec"; // ditto
        effect = "ExhaustEffectTankSide"; // ditto
      };
    };
    
    // Lights
    class Reflectors {
      class Left {
        color[]   = {1200, 900, 650};
        ambient[]  = {5,5,5};
        position = "l svetlo";
        direction = "konec l svetlo";
        hitpoint = "l svetlo";
        selection = "L svetlo";
        size     = 1;
        innerAngle   = 30;
        outerAngle   = 100;
        coneFadeCoef = 10;
        intensity   = 1; //17.5
        useFlare   = 1;
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
      class Right: Left {
        color[]   = {0.9, 0.3, 0.5};
        ambient[]  = {0.5,0.5,0.5};
        position = "p svetlo";
        direction = "konec p svetlo";
        hitpoint = "p svetlo";
        selection = "P svetlo";
      };
    };
    aggregateReflectors[] = {{"Left"},{"Right"}};
    armorLights = 0.1;
    
    // Sounds
    //insideSoundCoef = 1;
    //soundGear[] = {"", 5.62341e-005, 1};
    
    /**
    * TNPO-170A Configuration
    * Magnification x1 
    * (0.700000 / 1 = 0.700000)
    */
    driverForceOptics = 1; // driver always in optics
    driverOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpo170a"; //inside optics
    driverOpticsColor[] = {1, 1, 1, 1};
    driverOpticsEffect[] = {
      "OpticsCHAbera1" // ?????? ????????????? ????????
    };
    driverOutOpticsEffect[] = {};
    class ViewOptics 
    {
      initFov         = 0.700000;
      minFov          = 0.700000;
      maxFov          = 0.700000;
      initAngleX      = 0;
      minAngleX       = -110;
      maxAngleX       = 110;
      initAngleY      = 0;
      minAngleY       = -110;
      maxAngleY       = 110;
      opticsZoomMin   = 0.700000;
      opticsZoomMax   = 0.700000;
      distanceZoomMin = 20;
      distanceZoomMax = 2000;
    };
    // Library
    class Library
    {
      libTextDesc = $STR_BMD2_LibDesc,; // As seen in the armory @see stringtable
    };
    
    // Turrets
    class Turrets : Turrets
    {
      /*******************************************************************
      * Commander Turret                                                 *
      *******************************************************************/
      class CommanderOptics : NewTurret 
      {
        gunnerDoor="hatchC";
        proxyType = "CPCommander";
        proxyIndex = 1;
        gunnerName = $STR_RHS_Commander;
        dontCreateAI=1;
        primaryGunner = 0;
        primaryObserver = 1;
        stabilizedInAxes = "StabilizedInAxesNone";
        animationSourceBody = "sightCommanderSourceY";
        animationSourceGun = "sightCommanderSourceX";
        animationSourceHatch = "hatchCommander";
        //soundServo[] = {"\ca\sounds\vehicles\servos\turret-1", db-40, 1.0, 10};
        ejectDeadGunner = false;
        commanding = 6;
        outGunnerMayFire = false;
        inGunnerMayFire = false;
        viewGunnerInExternal = true;
        gunnerOutOpticsShowCursor = 0;
        gunnerOpticsShowCursor = true;
        memoryPointGunnerOptics = "gunnerview2";
        memoryPointsGetInGunner = "pos commander";
        memoryPointsGetInGunnerDir = "pos commander dir";
        gunnerGetInAction = "GetInMedium";
        gunnerGetOutAction = "GetOutMedium";
        gunnerAction = "rhs_bmd_commander";
        gunnerInAction = "rhs_bmd_commander_in";
        startEngine = false;
        //body = "sight_cmdr";
        /**
        * ???-3??
        * Magnification x5 (daylight thred)
        * (0.700000 / 5 = 0.140000)
        */
        minElev = -15;
        maxElev = 15;
        initElev = 0;
        minTurn = -50;
        maxTurn = 50;
        initTurn = 0;

        gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_binoc";
        //gunnerOutOpticsModel = "";
        gunnerOpticsEffect[] = {
          "TankGunnerOptics1",
          "WeaponsOptics",
          "OpticsCHAbera3"
        };
        gunnerOutOpticsEffect[] = {};
        gunnerOpticsColor[] = {1, 1, 1, 1};
        gunnerOutForceOptics = 0;
        gunnerForceOptics = 1;
        class ViewOptics 
        {
          initAngleX = 0;
          minAngleX = -110;
          maxAngleX = 110;
          initAngleY = 0;
          minAngleY = -100;
          maxAngleY = 100;
          opticsZoomMin = 0.140000;
          opticsZoomMax = 0.140000;
          distanceZoomMin = 100;
          distanceZoomMax = 2000;
          initFov = 0.140000;
          minFov =  0.140000;
          maxFov =  0.140000;
          visionMode[] = {"Normal","NVG"};
        };
      };
      /*******************************************************************
      * Main Turret                                                      *
      *******************************************************************/
      class MainTurret : MainTurret
      {
        
        gunnerDoor="hatchG";
        viewGunnerInExternal = true;
        proxyType = "CPGunner";
        proxyIndex = 1;
        primaryGunner = 1;
        primaryObserver = 0;
        stabilizedInAxes = 3;

        // Unit animations
        gunnerAction = "rhs_bmd_gunner"; // Out animation
        gunnerInAction = "rhs_bmd_gunner_in";
        ejectDeadGunner = false;

        // Animation sources
        animationSourceHatch = "hatchGunner"; // hatch
        animationSourceBody = "mainTurret"; // turret
        animationSourceGun = "mainGun"; // gun

        // Selections 
        gunBeg = "usti hlavne";  // endpoint of the gun
        gunEnd = "konec hlavne";  // chamber of the gun

        // Memory points
        memoryPointGun = "kulas"; // gun muzzle
        //memoryPointGunnerOptics = "sight_gnr"; // gunner view
        memoryPointGunnerOptics = "gunnerview"; // gunner view

        memoryPointsGetInGunner = "pos gunner"; // get in gunner
        memoryPointsGetInGunnerDir = "pos gunner dir"; // direction gunner

        // Weaponary
        weapons[] = {"rhs_weap_2a42", "rhs_weap_pkt", "rhs_weap_9m111"};
        magazines[] = {"rhs_mag_3uor6_250", "rhs_mag_3ubr6_250", "rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_9m113_3"};

        // Sounds
        //soundServo[] = {"\ca\sounds\vehicles\servos\turret-1", db-40, 1.0, 10}; // turning servo
        selectionFireAnim = "zasleh3";

        // Maneuvering
        minElev = -5; // min x-rotation
        maxElev = 60; // max x-rotation
        initElev = 10; // initial x-rotation
        minTurn = -360; // min y-rotation
        maxTurn = 360; // max y-rotation
        initTurn = 35; // initial y-rotation

        // Properties
        lockWhenDriverOut = 1; // Lock turret when driver turn out
        forceHideGunner = 0; // if 0 gunner can't turn out
        commanding = 5; // Chain of command
        startEngine = false; // Don't start engine when operate with gun
        memoryPointMissile[] = {"Konec rakety"};
        memoryPointMissileDir[] = {"Spice rakety"};

        // Extra turrets
        class Turrets{};

        // Hit Points
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
        /**
        * ???-1-42
        * Magnification x1.5
        * (0.700000 / 5 = 0.140000)
        */
        GunnerForceOptics    = 1; // always optics if 1
        //gunnerOpticsModel    = "\rhsafrf\addons\rhs_bmd\data\sights\sa_BPK142_sight"; // inside optics
        gunnerOpticsColor[]  = {1, 1, 1, 1};
        gunnerOutOpticsModel = "";
        //gunnerOutOpticsModel = ""; // outside optics
        //gunnerOpticsEffect[] = {"TankGunnerOptics1", "WeaponsOptics", "OpticsCHAbera3"};
        class OpticsIn
        {
          class bpk142
          {
            initAngleX      = 0;
            minAngleX       = -110;
            maxAngleX       = +110;
            initAngleY      = 0;
            minAngleY       = -110;
            maxAngleY       = +110;
            opticsZoomMin   = 0.140000;
            opticsZoomMax   = 0.140000;
            distanceZoomMin = 200;
            distanceZoomMax = 2000;
            initFov = 0.7/5.6;
            minFov          = 0.140000;
            maxFov          = 0.140000;
            visionMode[] = {"Normal"};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_empty";  //path to daylight optic model
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic
            
          };
          class bpk142n
          {
            initAngleX      = 0;
            minAngleX       = -110;
            maxAngleX       = +110;
            initAngleY      = 0;
            minAngleY       = -110;
            maxAngleY       = +110;
            opticsZoomMin   = 0.140000;
            opticsZoomMax   = 0.140000;
            distanceZoomMin = 200;
            distanceZoomMax = 2000;
            initFov = 0.7/5;
            minFov          = 0.140000;
            maxFov          = 0.140000;
            visionMode[] = {"NVG"};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_bpk142n";  //path to daylight optic model
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic
            
          };
          class pzu812
          {
            initAngleX      = 0;
            minAngleX       = -110;
            maxAngleX       = +110;
            initAngleY      = 0;
            minAngleY       = -110;
            maxAngleY       = +110;
            opticsZoomMin   = 0.25;
            opticsZoomMax   = 0.25;
            distanceZoomMin = 200;
            distanceZoomMax = 2000;
            initFov         = 0.25;
            minFov          = 0.25;
            maxFov          = 0.25;
            visionMode[] = {"Normal"};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_pzu812";  //path to daylight optic model
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic
            
          };
        };
        class Reflectors 
        {
          class TurretLight 
          {
            color[]   = {1200, 900, 650};
            ambient[]  = {5,5,5};
            position = "G svetlo";
            direction = "konec G svetlo";
            hitpoint = "G svetlo";
            selection = "G svetlo";
            size     = 1;
            innerAngle   = 20;
            outerAngle   = 80;
            coneFadeCoef = 8;
            intensity   = 1; //17.5
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
        };
        aggregateReflectors[] = {{"TurretLight"}};
        armorLights = 0.1;
      };
      /*******************************************************************
      * Hull gunner Turret                                               *
      *******************************************************************/
      class GPMGTurret1 : NewTurret
      {
        gunnerDoor="hatchMG";
        proxyType = "CPGunner";
        proxyIndex = 2;
        body = "obsTurret2";
        gun = "obsGun2";
        animationSourceBody = "obsTurret2";
        animationSourceGun = "obsGun2";
        animationSourceHatch = "hatchMgGunner";
        selectionFireAnim = "zasleh1";
        gunnerName = $STR_MGFrontRight;
        hasGunner = 1;
        dontCreateAI=1;
        soundServo[] = {};
        forceHideGunner = 0;
        primaryObserver = 0;
        primaryGunner = 0;
        commanding = 4;
        minElev = -10;
        maxElev = 10;
        minTurn = -10;
        maxTurn = 10;
        weapons[] = {"rhs_weap_pkt_bmd_bow1"};
        magazines[] = {"rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250"};
        //weapons[] = {};
        //magazines[] = {};
        ejectDeadGunner = false;
        class CargoLight {
          ambient[] = {0.6,0,0.15,1};
          brightness = 0.007;
          color[] = {0,0,0,0};
        };
        gunBeg = "muzzle2";
        gunEnd = "end2";
        memoryPointGun = "memoryPointGun2";
        memoryPointGunnerOptics = "gunnerview3";
        memoryPointsGetInGunner = "pos cargo"; // get in gunner
        memoryPointsGetInGunnerDir = "pos cargo dir"; // direction gunner
        gunnerAction = "rhs_bmd_mggunner";
        gunnerInAction = "rhs_bmd_gunner_r_in";
        viewGunnerInExternal = true;
        startEngine = false; // Don't start engine when operate with gun
        class Turrets {};
        /**
        * TNPP-220A Optical Tube
        * Magnification x1.5
        * (0.250000 / 1.5 = 0.166666)
        */
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
      };
      /*******************************************************************
      * Left Cargo Seat @see NewTurret                                  *
      *******************************************************************/
      class LeftBack : NewTurret 
      {
        body = "lseat_turret";
        gun = "lseat_gun";
        animationSourceBody = "lseat_Turret";
        animationSourceGun = "lseat_Gun";
        animationSourceHatch = "";
        selectionFireAnim = "";
        minElev = 0;
        maxElev = 0;
        initTurn = 60;
        minTurn = 60;
        maxTurn = 60;
        maxHorizontalRotSpeed = 0;
        maxVerticalRotSpeed = 0;
        proxyIndex = 3;
        memoryPointsGetInGunner = "pos cargo";
        memoryPointsGetInGunnerDir = "pos cargo dir";
        gunnerName = $STR_CargoBackLeft;
        commanding = 3;
        gunBeg = "";
        gunEnd = "";
        memoryPointGun = "";
        memoryPointGunnerOptics = "lseat_view";
        gunnerAction = "";
        gunnerInAction = "rhs_bmd_cargo_in";
        weapons[] = {};
        magazines[] = {};
        forceHideGunner = true;
        viewGunnerInExternal = true;
        hasGunner = 1;
        dontCreateAI=1;
        primaryGunner = 0;
        primaryObserver = 0;
        /**
        * TNPO-170A Configuration
        * Magnification x1 
        * (0.700000 / 1 = 0.700000)
        */
        gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpo170a";
        gunnerOpticsColor[] = {1, 1, 1, 1};
        gunnerForceOptics = 1;
        startEngine = false;
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
      };
      /*******************************************************************
      * Right Cargo Seat @see LeftBack                                 *
      *******************************************************************/
      class RightBack : LeftBack
      {
        body = "rseat_turret";
        gun = "rseat_gun";
        animationSourceBody = "rseat_Turret";
        animationSourceGun = "rseat_Gun";
        initTurn = -60;
        minTurn = -60;
        maxTurn = -60;
        gunnerName = $STR_CargoBackRight;
        memoryPointGunnerOptics = "rseat_view";
        commanding = 2;
        proxyIndex = 4;
      };
      /*******************************************************************
      * Back Cargo Seat @see LeftBack                                  *
      *******************************************************************/
      class MainBack : LeftBack
      {
        body = "bseat_turret";
        gun = "bseat_gun";
        animationSourceBody = "bseat_Turret";
        animationSourceGun = "bseat_Gun";
        initTurn = 180;
        minTurn = 180;
        maxTurn = 180;
        gunnerName = $STR_CargoBackCenter;
        memoryPointGunnerOptics = "bseat_view";
        commanding = 1;
        proxyIndex = 5;
      };
    };
    class EventHandlers: EventHandlers
    {
      init = "_this call SLX_XEH_EH_Init;_this call rhs_fnc_bmd_init"; 
      fired = "_this call SLX_XEH_EH_Fired;_this spawn rhs_fnc_9m14_fired;  _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
      hitpart = "_this call SLX_XEH_EH_HitPart;_this call rhs_fnc_hitHandler";
    };

  };
  // Version base
  class rhs_bmd2_base : rhs_bmd_base
  {
    scope = 0;
    #include "physx_config_bmd2.hpp"

    class AnimationSources : AnimationSources 
    {
      class recoil_source 
      {
        source = "reload";
        weapon = "rhs_weap_2a42";
      };

      class muzzle_hide_hmg: recoil_source {};
      class muzzle_rot_hmg: recoil_source 
      {
        source="ammorandom";
      };

    };
    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {

        turretInfoType = "RHS_RscWeaponBPK42_FCS";
        discreteDistance[] = {100};
        discreteDistanceInitIndex = 0;

        maxhorizontalrotspeed = 0.61;
        maxverticalrotspeed = 0.104;
      };
      class CommanderOptics1 : CommanderOptics{};
      class GPMGTurretBMD1 : GPMGTurret1 {};
      class LeftBack1 : LeftBack{};
      class RightBack1 : RightBack{};
      class MainBack1 : MainBack{};
    };
    class UserActions
    {
      class LowerSusp
      {
        displayName = $STR_UA_LowerSusp;
        position = ""; 
        radius = 5; 
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this <8400"; 
        statement = "this setmass [8200*1.7,6];this setVelocity [0.01,0.01,0.01]"; 
        onlyForPlayer = true; 
      };
      class RaiseSusp: LowerSusp
      {
        displayName = $STR_UA_RaiseSusp;
        condition = "(player == driver this) && (2 > speed this) && !(surfaceIsWater getPos this) && getmass this >13000"; 
        statement = "this setmass [8200,6];this setVelocity [0.01,0.01,0.01]"; 
      }; 
    };
    class EventHandlers: EventHandlers
    {
      fired = "_this call SLX_XEH_EH_Fired;_this call rhs_fnc_at14_fired;  _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
    };
  };
  class rhs_bmd1_base : rhs_bmd_base
  {
    scope = 0;
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd1.p3d"; // path to model
    Author_Macro
    displayName= $STR_BMD1_Name; // as seen in the editor
    picture = "\rhsafrf\addons\rhs_bmd\rhs_bmd1_pic_ca.paa";
    icon = "\rhsafrf\addons\rhs_bmd\rhs_bmd1_icon.paa";

    class AnimationSources : AnimationSources 
    {
      class recoil_source_2a28
      {
        source = "reload";
        weapon = "rhs_weap_2a28";
      };
    };
    class Damage 
    {
      tex[] = {};
      mat[] = {
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_damage.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_destruct.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_damage.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_destruct.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_destruct.rvmat"
      };
    };

    hiddenSelectionsTextures[] = {
      "\rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_co.paa",
      "\rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_co.paa",
      "\rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_co.paa",
      "rhsafrf\addons\rhs_decals\Data\Labels\Misc\no_ca.paa"
    };
    class textureSources
    {
      class standard 
      {
        displayName="Standard"; 
        Author_Macro
        textures[]=
        {
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_co.paa"
        };
        factions[]=// This source should be available only for these factions
        {
          rhs_faction_vmf, rhs_faction_vdv,rhs_faction_vdv,rhs_faction_vv
        };
      };
      class Camo: standard
      {
        displayName="Chedaki"; 
        Author_Macro
        textures[]=
        {
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_chdkz_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_co.paa",
          "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_chdkz_co.paa"
        };
      };
    };

    class Turrets :Turrets
    {
        class MainTurret : MainTurret
        {
          stabilizedInAxes = 0;
          weapons[] = {"rhs_weap_2a28", "rhs_weap_pkt","rhs_weap_9k11"}; // weapons
          magazines[] = {"rhs_mag_pg15v_24","rhs_mag_og15v_16","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_9m14m_3"}; //ammo

          //motion range
          minElev = -4;
          maxElev = 33;
          initElev = 0;
          minTurn = -360;
          maxTurn = 360;
          initTurn = 35;
          lockWhenDriverOut = 1;
          maxHorizontalRotSpeed = 0.4;
          maxVerticalRotSpeed = 0.1;

          class OpticsIn
          {
            class pn22m1
            {
              initAngleX      = 0;
              minAngleX       = -110;
              maxAngleX       = +110;
              initAngleY      = 0;
              minAngleY       = -110;
              maxAngleY       = +110;
              opticsZoomMin   = 0.140000;
              opticsZoomMax   = 0.140000;
              distanceZoomMin = 200;
              distanceZoomMax = 2000;
              initFov         = 0.140000;
              minFov          = 0.140000;
              maxFov          = 0.140000;
              visionMode[] = {"Normal"};
              gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1pn22m1";  //path to daylight optic model
              gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic

            };
            class pn22m1n
            {
              initAngleX      = 0;
              minAngleX       = -110;
              maxAngleX       = +110;
              initAngleY      = 0;
              minAngleY       = -110;
              maxAngleY       = +110;
              opticsZoomMin   = 0.140000;
              opticsZoomMax   = 0.140000;
              distanceZoomMin = 200;
              distanceZoomMax = 2000;
              initFov         = 0.140000;
              minFov          = 0.140000;
              maxFov          = 0.140000;
              visionMode[] = {"NVG"};
              gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_1pn22m1n";  //path to daylight optic model
              gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic

            };

          };
        };

        class CommanderOptics1 : CommanderOptics
        {
          proxyType = "CPCommander";
          proxyIndex = 1;
          gunnerName = $STR_RHS_Commander;
          primaryGunner = 0;
          primaryObserver = 1;
          stabilizedInAxes = "StabilizedInAxesNone";
          selectionFireAnim = "zasleh2";
          //animationSourceBody = "sightCommanderSourceY";
          //animationSourceGun = "sightCommanderSourceX";
          animationSourceHatch = "hatchCommander";
          soundServo[] = {};
          ejectDeadGunner = false;
          commanding = 6;
          outGunnerMayFire = false;
          inGunnerMayFire = true;
          viewGunnerInExternal = true;
          gunnerOutOpticsShowCursor = 0;
          gunnerOpticsShowCursor = false;
          memoryPointGunnerOptics = "gunnerview2";
          memoryPointsGetInGunner = "pos commander";
          memoryPointsGetInGunnerDir = "pos commander dir";
          gunnerGetInAction = "GetInMedium";
          gunnerGetOutAction = "GetOutMedium";
          gunnerAction = "rhs_bmd_commander";
          body = "obsTurret";
          gun = "obsGun";
          gunBeg = "muzzle3";
          gunEnd = "end3";
          memoryPointGun = "memoryPointGun";
          animationSourceBody = "sightCommanderSourceY";
          animationSourceGun = "sightCommanderSourceX";

          weapons[] = {"rhs_weap_pkt_bmd_bow2"};
          magazines[] = {"rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250"};

          minElev = -10;
          maxElev = 10;
          initElev = 0;
          minTurn = -10;
          maxTurn = 10;
          initTurn = 0;

          gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_tnpp220a";
          //gunnerOutOpticsModel = "";
          gunnerOpticsEffect[] = {
            "TankGunnerOptics1",
            "WeaponsOptics",
            "OpticsCHAbera3"
          };
          gunnerOutOpticsEffect[] = {};
          gunnerOpticsColor[] = {1, 1, 1, 1};
          gunnerOutForceOptics = 0;
          gunnerForceOptics = 1;

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
        };
        class GPMGTurretBMD1 : GPMGTurret1 {};
        class LeftBack1 : LeftBack{};
        class RightBack1 : RightBack{};
        class MainBack1 : MainBack{};

      };
      class EventHandlers;
  };
  // BMD1 Versions
  // BMD1
  class rhs_bmd1 : rhs_bmd1_base
  {
    scope = 2;
    Author_Macro
  };
  // BMD1K
  class rhs_bmd1k : rhs_bmd1_base
  {
    scope = 2;
    Author_Macro
    displayName= $STR_BMD1K_Name; // as seen in the editor
    class AnimationSources : AnimationSources 
    {
      class antena2_hide: antena2_hide
      {
        initPhase = 0; 
      };
    };
    tf_range_api = 17000; //r123m - range 15-20km with standard metal antenna

    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {
        weapons[] = {"rhs_weap_2a28", "rhs_weap_pkt"}; // weapons
        magazines[] = {"rhs_mag_pg15v_24","rhs_mag_og15v_16","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250"};
      };
      class CommanderOptics1 : CommanderOptics1 {};
      class GPMGTurretBMD1 : GPMGTurret1 {};
      class LeftBack1 : LeftBack{};
      class RightBack1 : RightBack{};
      class MainBack1 : MainBack{};
    };
  };
  // BMD1P
  class rhs_bmd1p : rhs_bmd1_base
  {
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd1p.p3d"; // path to model
    Author_Macro
    displayName= $STR_BMD1P_Name; // as seen in the editor

    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {
        weapons[] = {"rhs_weap_2a28", "rhs_weap_pkt","rhs_weap_9m111"}; // weapons
        magazines[] = {"rhs_mag_pg15v_24","rhs_mag_og15v_16","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_9m113_3"};
      };
      class CommanderOptics1 : CommanderOptics1 {};
      class GPMGTurretBMD1 : GPMGTurret1 {};
      class LeftBack1 : LeftBack{};
      class RightBack1 : RightBack{};
      class MainBack1 : MainBack{};
    };
    class EventHandlers: EventHandlers
    {
      fired = "_this call SLX_XEH_EH_Fired;_this call rhs_fnc_at14_fired;  _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
    };
  };
  
  // BMD1PK
  class rhs_bmd1pk : rhs_bmd1_base
  {
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd1pk.p3d"; // path to model
    picture = "\rhsafrf\addons\rhs_bmd\rhs_bmd1pk_pic_ca.paa";
    Author_Macro
    displayName= $STR_BMD1PK_Name; // as seen in the editor

    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {
        weapons[] = {"rhs_weap_2a28", "rhs_weap_pkt"}; // weapons
        magazines[] = {"rhs_mag_pg15v_24","rhs_mag_og15v_16","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250"};
      };
      class CommanderOptics1 : CommanderOptics1
      {
        proxyType = "CPCommander";
        proxyIndex = 1;
        gunnerName = $STR_RHS_Commander;
        primaryGunner = 0;
        primaryObserver = 1;
        stabilizedInAxes = "StabilizedInAxesNone";
        animationSourceBody = "sightCommanderSourceY";
        animationSourceGun = "sightCommanderSourceX";
        animationSourceHatch = "hatchCommander";
        //soundServo[] = {"\ca\sounds\vehicles\servos\turret-1", db-40, 1.0, 10};
        ejectDeadGunner = false;
        commanding = 6;
        outGunnerMayFire = false;
        inGunnerMayFire = false;
        viewGunnerInExternal = true;
        gunnerOutOpticsShowCursor = 0;
        gunnerOpticsShowCursor = true;
        memoryPointGunnerOptics = "gunnerview2";
        memoryPointsGetInGunner = "pos commander";
        memoryPointsGetInGunnerDir = "pos commander dir";
        gunnerGetInAction = "GetInMedium";
        gunnerGetOutAction = "GetOutMedium";
        gunnerAction = "rhs_bmd_commander";
        body = "";
        gun = "";


        weapons[] = {};
        magazines[] = {};

        minElev = -15;
        maxElev = 15;
        initElev = 0;
        minTurn = -50;
        maxTurn = 50;
        initTurn = 0;

        gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_binoc";
        //gunnerOutOpticsModel = "";
        gunnerOpticsEffect[] = {
          "TankGunnerOptics1",
          "WeaponsOptics",
          "OpticsCHAbera3"
        };
        gunnerOutOpticsEffect[] = {};
        gunnerOpticsColor[] = {1, 1, 1, 1};
        gunnerOutForceOptics = 0;
        gunnerForceOptics = 1;
        class ViewOptics 
        {
          initAngleX = 0;
          minAngleX = -110;
          maxAngleX = 110;
          initAngleY = 0;
          minAngleY = -100;
          maxAngleY = 100;
          opticsZoomMin = 0.140000;
          opticsZoomMax = 0.140000;
          distanceZoomMin = 100;
          distanceZoomMax = 2000;
          initFov = 0.140000;
          minFov =  0.140000;
          maxFov =  0.140000;
          visionMode[] = {"Normal","NVG"};
        };
      };
      class GPMGTurretBMD1 : GPMGTurret1 {};
      class LeftBack1 : LeftBack{};
      class RightBack1 : RightBack{};
      class MainBack1 : MainBack{};
    };

    class AnimationSources : AnimationSources 
    {
      class antena2_hide: antena2_hide
      {
        initPhase = 0; 
      };
    };

    class EventHandlers: EventHandlers
    {
      fired = "_this call SLX_XEH_EH_Fired;_this call rhs_fnc_at14_fired;  _this call (uinamespace getvariable 'RHS_fnc_effectFired')";
    };
  };
  // BMD1R
  class rhs_bmd1r : rhs_bmd1_base
  {
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd1rock.p3d"; // path to model
    picture = "\rhsafrf\addons\rhs_bmd\rhs_bmd1r_pic_ca.paa";
    Author_Macro
    displayName= $STR_BMD1R_Name; // as seen in the editor
    transportSoldier = 0;
    
    class Damage 
    {
      tex[] = {};
      mat[] = {
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_damage.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_01_destruct.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_damage.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_02_destruct.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd2_03_destruct.rvmat",
        "rhsafrf\addons\rhs_bmd\data\sa_bmd1_grom.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_grom_damage.rvmat", "rhsafrf\addons\rhs_bmd\data\sa_bmd1_grom_destruct.rvmat"
      };
    };

    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {
        forcehidegunner = true;
        weapons[] = {"rhs_weap_s8"}; // weapons
        magazines[] = {"rhs_mag_s8_12"}; 
      };
      class CommanderOptics1 : CommanderOptics1 {};
      class GPMGTurretBMD1 : GPMGTurret1 {};
      class LeftBack1 : LeftBack{};
      class RightBack1 : RightBack{};
      class MainBack1 : MainBack{};
    };
    
    class EventHandlers: EventHandlers
    {
      init = "_this call SLX_XEH_EH_Init;_this call compile preProcessFile '\rhsafrf\addons\rhs_c_bmd\scripts\rhs_bmd_init.sqf'"; 
      fired = "_this spawn fRHSBMD1RRocketonfired;  _this call (uinamespace getvariable 'RHS_fnc_effectFired')"; 
    };
  };
  // BMD2 Versions
  // BMD2
  class rhs_bmd2 : rhs_bmd2_base
  {
    scope = 2;
    Author_Macro
  };
  // BMD2M
  class rhs_bmd2m : rhs_bmd2
  {
    scope = 2;
    model = "\rhsafrf\addons\rhs_bmd\rhs_bmd2m.p3d"; // path to model
    Author_Macro
    displayName= $STR_BMD2M_Name; // as seen in the editor
    transportSoldier = 0;
    
    class Turrets : Turrets
    {
      class MainTurret : MainTurret
      {
        weapons[] = {"rhs_weap_2a42", "rhs_weap_pkt", "rhs_weap_9k133"};
        magazines[] = {"rhs_mag_3uor6_250", "rhs_mag_3ubr6_250", "rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_762x54mm_250","rhs_mag_9m133_2"};
        turretInfoType = "rhs_gui_optic_thermalscreen";
        class OpticsIn
        {
          class gunnerSightWide
          {
            initAngleX      = 0;
            minAngleX       = -110;
            maxAngleX       = +110;
            initAngleY      = 0;
            minAngleY       = -110;
            maxAngleY       = +110;
            opticsZoomMin   = 0.140000;
            opticsZoomMax   = 0.140000;
            distanceZoomMin = 200;
            distanceZoomMax = 2000;
            initFov         = 0.140000;
            minFov          = 0.140000;
            maxFov          = 0.140000;
            visionMode[] = {"Normal","Ti"};
            thermalMode[] = {0, 1};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalScreen_wide";  //path to daylight optic model
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic
            
          };
          class gunnerSightNarrow
          {
            initAngleX      = 0;
            minAngleX       = -110;
            maxAngleX       = +110;
            initAngleY      = 0;
            minAngleY       = -110;
            maxAngleY       = +110;
            opticsZoomMin   = 0.047;
            opticsZoomMax   = 0.047;
            distanceZoomMin = 200;
            distanceZoomMax = 2000;
            initFov = 0.047;
            minFov = 0.047;
            maxFov = 0.047;
            visionMode[] = {"Normal","Ti"};
            thermalMode[] = {0, 1};
            gunnerOpticsModel = "\rhsafrf\addons\rhs_optics\vehicles\rhs_thermalScreen_narrow";  //path to daylight optic model
            gunnerOpticsEffect[] = {"TankGunnerOptics1","OpticsBlur2","OpticsCHAbera3"}; // graphic effects on optic
            
          };
          
        };

      };

      class CommanderOptics2 : CommanderOptics1{};
      class GPMGTurretBMD2 : GPMGTurretBMD1 {
        forceHideGunner = 1;
      };
      class LeftBack2 : LeftBack1{};
      class RightBack2 : RightBack1{};
      class MainBack2 : MainBack1{};
    };
  };
  // BMD2K
  class rhs_bmd2k:rhs_bmd2
  {
    Author_Macro
    displayName= $STR_BMD2K_Name;
    class AnimationSources : AnimationSources 
    {
      class antena2_hide: antena2_hide
      {
        initPhase = 0; 
      };
    };
  };
  

};

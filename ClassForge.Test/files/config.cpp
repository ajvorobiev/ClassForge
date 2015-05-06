class rhs_acc_1pn93_2 : rhs_acc_pgo7v
{
	Author_Macro
	scope = 2;

	displayName = $STR_RHS_ACC_1PN932;

	picture = "\rhsafrf\addons\rhs_weapons\gear_acc\rhs_acc_gear_1pn93_ca.paa";

	model = "\rhsafrf\addons\rhs_weapons\acc\scopes\1pn93\rhs_1pn93_2";

	descriptionShort = $STR_RHS_ACC_1PN932_SD;

	class ItemInfo : InventoryOpticsItem_Base_F
	{
		opticType = 2;
		mass = 13.64;
		RMBhint = "Optical Sight";
		optics = 1;


		modelOptics = "\rhsafrf\addons\rhs_weapons\acc\scopes\optics\rhs_1pn932_sniper_scope";

		class OpticsModes
		{
			///! 2.7X MAGNIFICATION -> 0.2492/2.7
			class rhs_pgo7v_scope
			{
				opticsID = 2;
				useModelOptics = 1;
				opticsPPEffects[] = { "OpticsCHAbera1", "OpticsBlur1" };
				discreteDistance[] = { 500 };
				discreteDistanceInitIndex = 0;
				opticsZoomMin = 0.35 / 2.7;
				opticsZoomMax = 0.35 / 2.7;
				opticsZoomInit = 0.35 / 2.7;
				memoryPointCamera = "opticView";
				visionMode[] = { "NVG" };
				opticsFlare = 1;
				opticsDisablePeripherialVision = 1;
				distanceZoomMin = 200;
				distanceZoomMax = 1000;
				cameraDir = "direction";
			};
		};
	};
};

class rhs_acc_1pn93_2 : rhs_acc_pgo7v
{
	Author_Macro
	scope = 2;

	displayName = $STR_RHS_ACC_1PN932;

	picture = "\rhsafrf\addons\rhs_weapons\gear_acc\rhs_acc_gear_1pn93_ca.paa";

	model = "\rhsafrf\addons\rhs_weapons\acc\scopes\1pn93\rhs_1pn93_2";

	descriptionShort = $STR_RHS_ACC_1PN932_SD;

	class ItemInfo : InventoryOpticsItem_Base_F
	{
		opticType = 2;
		mass = 13.64;
		RMBhint = "Optical Sight";
		optics = 1;


		modelOptics = "\rhsafrf\addons\rhs_weapons\acc\scopes\optics\rhs_1pn932_sniper_scope";

		class OpticsModes
		{
			///! 2.7X MAGNIFICATION -> 0.2492/2.7
			class rhs_pgo7v_scope
			{
				opticsID = 2;
				useModelOptics = 1;
				opticsPPEffects[] = { "OpticsCHAbera1", "OpticsBlur1" };
				discreteDistance[] = { 500 };
				discreteDistanceInitIndex = 0;
				opticsZoomMin = 0.35 / 2.7;
				opticsZoomMax = 0.35 / 2.7;
				opticsZoomInit = 0.35 / 2.7;
				memoryPointCamera = "opticView";
				visionMode[] = { "NVG" };
				opticsFlare = 1;
				opticsDisablePeripherialVision = 1;
				distanceZoomMin = 200;
				distanceZoomMax = 1000;
				cameraDir = "direction";
			};
		};
	};
};
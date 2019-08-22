using UnrealBuildTool;

public class MathPlusEditor : ModuleRules
{
	public MathPlusEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
            });

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "DetailCustomizations",
                "EditorStyle",
                "Engine",
                "InputCore",
                "Slate",
				"SlateCore",
                "UnrealEd",

                "MathPlus",
			});
    }
}

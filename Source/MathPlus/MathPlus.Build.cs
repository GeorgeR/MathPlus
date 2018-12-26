using UnrealBuildTool;

public class MathPlus : ModuleRules
{
	public MathPlus(ReadOnlyTargetRules Target) 
		: base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		if (Target.Version.MinorVersion <= 19)
	    {
			PublicIncludePaths.AddRange(
				new string[] {
				});
				
			PrivateIncludePaths.AddRange(
				new string[] {
				});
		}

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
			});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Engine",
				"Slate",
				"SlateCore",
			});
			
	    if (Target.bBuildEditor == true)
	        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "ContentBrowser" });
	}
}
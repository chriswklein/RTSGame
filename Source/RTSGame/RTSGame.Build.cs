using UnrealBuildTool;

public class RTSGame : ModuleRules
{
	public RTSGame(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });
	}
}
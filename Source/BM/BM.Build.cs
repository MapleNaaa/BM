using UnrealBuildTool;

public class BM : ModuleRules
{
	public BM(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore",
			"UMG", "Slate", "SlateCore", "EnhancedInput",
			"AnimGraphRuntime", "NetCore", "Chooser",
			"OnlineSubsystem",
			"OnlineSubsystemUtils",  
			"DeveloperSettings" // 关键
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			"Eigen",
			"AnimationLocomotionLibraryRuntime",
			"OnlineSubsystem",
			"OnlineBlueprintSupport",
			"OnlineSubsystemUtils",   // ← 关键：BM 模块里必须声明
			// 暂时不要启用 Advanced*，先把自带节点编过
			"AdvancedSessions",
			"AdvancedSteamSessions",
		});
	}
}
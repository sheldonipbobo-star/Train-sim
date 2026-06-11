# Unreal Engine Build.cs 配置

using UnrealBuildTool;

public class TrainSimTarget : TargetRules
{
    public TrainSimTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

        ExtraModuleNames.AddRange(new string[] { "TrainSim" });
    }
}

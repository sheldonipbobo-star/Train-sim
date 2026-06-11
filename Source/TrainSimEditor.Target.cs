# Unreal Engine Editor Target

using UnrealBuildTool;

public class TrainSimEditorTarget : TargetRules
{
    public TrainSimEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

        ExtraModuleNames.AddRange(new string[] { "TrainSim" });
    }
}

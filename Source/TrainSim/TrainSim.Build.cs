using UnrealBuildTool;

public class TrainSim : ModuleRules
{
    public TrainSim(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore",
            "EnhancedInput",
            "Slate",
            "SlateCore",
            "Json",
            "JsonUtilities",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}

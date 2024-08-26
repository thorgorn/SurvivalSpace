// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SurvivalSpace : ModuleRules
{
	public SurvivalSpace(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Niagara", "NiagaraCore", "EnhancedInput", "CommonUI", "CommonInput" });
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] { "LevelEditor", "UnrealEd", "CommonUIEditor", "Slate", "SlateCore" });
		}
		else
		{
			PrivateDependencyModuleNames.AddRange(new string[] { });
		}
		
		 
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

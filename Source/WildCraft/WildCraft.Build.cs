// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class WildCraft : ModuleRules
{   
	public WildCraft(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //bLegacyPublicIncludePaths = true;
        bLegacyPublicIncludePaths = false;
        PublicIncludePaths.Add(ModuleDirectory);

        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities", "GameplayTags", "GameplayTasks" });

        PublicDependencyModuleNames.AddRange(new string[] { "AIModule", "UMG" });

        PublicDependencyModuleNames.AddRange(new string[] { "RPGv1" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

    }
}

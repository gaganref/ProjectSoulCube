// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectSoulCube : ModuleRules
{
	public ProjectSoulCube(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PublicDependencyModuleNames.AddRange(new string[] { "UMG", "CommonUI" });
		PublicDependencyModuleNames.AddRange(new string[] { "DebugLibrary", "ProceduralLevelGenerator", "InteractionSystemPlugin" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "GameplayAbilities", "GameplayTags", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}

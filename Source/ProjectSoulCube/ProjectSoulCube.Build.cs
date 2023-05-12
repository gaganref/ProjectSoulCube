// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectSoulCube : ModuleRules
{
	public ProjectSoulCube(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				"CoreUObject", 
				"Engine",
				"UnrealEd",
				"InputCore",
				"DebugLibrary", 
				"ProceduralLevelGenerator", 
				"InteractionSystemPlugin",
				"UMG", 
				"CommonUI", "AITestSuite"
				// ... add other public dependencies that you statically link with here ...
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"EnhancedInput", 
				"GameplayAbilities", 
				"GameplayTags", 
				"GameplayTasks",
				"Slate",
				"SlateCore", "MoviePlayer"
				// ... add private dependencies that you statically link with here ...	
			}
		);
	}
}

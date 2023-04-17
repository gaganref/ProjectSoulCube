// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SoulCubeAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "Misc/SoulCubeGameplayTags.h"
#include "ProjectSoulCube/ProjectSoulCube.h"

void USoulCubeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Init Gameplay abilities system target data to avoid errors
	UAbilitySystemGlobals::Get().InitGlobalData();

	// Initialize native c++ tags to use in the editor
	FSoulCubeGameplayTags::InitializeNativeTags();
}

USoulCubeAssetManager::USoulCubeAssetManager()
{
}

USoulCubeAssetManager& USoulCubeAssetManager::Get()
{
	check(GEngine);

	if(USoulCubeAssetManager* AssetManager = Cast<USoulCubeAssetManager>(GEngine->AssetManager))
	{
		return *AssetManager;
	}

	UE_LOG(LogSoulCubeSystem, Fatal, TEXT("Invalid AssetManagerClassName in DefaultEngine.ini, Make sure you are using \"SoulCubeAssetManager\" class!"));

	// Fatal error above prevents this from being called.
	return *NewObject<USoulCubeAssetManager>();
}

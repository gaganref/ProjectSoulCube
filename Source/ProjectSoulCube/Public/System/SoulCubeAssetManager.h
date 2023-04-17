// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SoulCubeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API USoulCubeAssetManager : public UAssetManager
{
	GENERATED_BODY()

protected:
	/** Starts initial load, gets called from InitializeObjectReferences */
	virtual void StartInitialLoading() override;

public:
	/** Constructor */
	USoulCubeAssetManager();

	// Returns the AssetManager singleton object.
	static USoulCubeAssetManager& Get();	
};

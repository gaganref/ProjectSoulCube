// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CustomPlayerCameraManager.generated.h"

UCLASS()
class PROJECTSOULCUBE_API ACustomPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACustomPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

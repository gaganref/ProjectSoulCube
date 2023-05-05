// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

UCLASS()
class PROJECTSOULCUBE_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainMenuController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

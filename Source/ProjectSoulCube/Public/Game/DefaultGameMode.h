// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FLinearColor CameraFadeInColor = FLinearColor::Red;
	
public:

	virtual void BeginGameWin();
	
	virtual void BeginGameLost();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameWin();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void GameLost();
};

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
	FLinearColor LooseCameraFadeInColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere)
	FLinearColor WinCameraFadeInColor = FLinearColor::Green;
	
private:
	virtual void GameWin_Implementation();
	
	virtual void GameLost_Implementation();
	
public:

	UFUNCTION(BlueprintCallable)
	void BeginGameWin();

	UFUNCTION(BlueprintCallable)
	void BeginGameLost();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameWin();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void GameLost();
};

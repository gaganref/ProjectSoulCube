// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCHUDMainMenu.generated.h"

UCLASS()
class PROJECTSOULCUBE_API ASCHUDMainMenu : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> LevelToOpenOnStart;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScCuwMainMenuHud> HudWidgetClass;
	
	UPROPERTY(BlueprintGetter = GetHudWidget)
	TObjectPtr<class UScCuwMainMenuHud> HudWidget;

	UPROPERTY()
	TObjectPtr<APawn> PlayerPawn;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	
public:
	// Sets default values for this actor's properties
	ASCHUDMainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnInit_Implementation();

	UFUNCTION()
	void HandleStartButtonPressed();
	
	UFUNCTION()
	void HandleQuitButtonPressed();
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();

public:
	UFUNCTION(BlueprintGetter)
	class UScCuwMainMenuHud* GetHudWidget() const;

};

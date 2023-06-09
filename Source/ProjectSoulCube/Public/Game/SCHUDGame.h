// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Interface/InteractableItemHudInterface.h"
#include "SCHUDGame.generated.h"

class IInteractableInterface;
/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API ASCHUDGame : public AHUD, public IInteractableItemHudInterface
{
	GENERATED_BODY()

public:
	ASCHUDGame();
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UScCuwGameHud> HudWidgetClass;

	UPROPERTY(EditAnywhere)
	TArray<FName> LevelsRef;
	
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainMenuLevelRef;
	
	UPROPERTY(BlueprintGetter = GetHudWidget)
	TObjectPtr<class UScCuwGameHud> HudWidget;

	UPROPERTY(BlueprintGetter = GetPlayerPawn)
	TObjectPtr<APawn> PlayerPawn;

	UPROPERTY(BlueprintGetter = GetPlayerController)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintGetter = GetInventoryRef)
	TObjectPtr<class UInventorySystemComponent> InventoryRef;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnInit_Implementation();

	virtual void OnInventoryPressed_Implementation(const bool bShouldOpenInventory);

	virtual void ShowItemInfo_Implementation(AActor* InteractableRef) override;
	
	virtual void HideItemInfo_Implementation(AActor* InteractableRef) override;

	int32 GetLevelIndexByName(const FName& InName);
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInventoryPressed(const bool bShouldOpenInventory);

	UFUNCTION(BlueprintCallable)
	void SetGameObjectiveCurrentData(const int32 NewData);

	UFUNCTION(BlueprintCallable)
	void SetGameObjectiveTargetData(const int32 NewData);
	
	UFUNCTION()
	void HandlePauseGame();
	
	UFUNCTION()
	void HandleResumeGame();
	
	UFUNCTION()
	void HandleRestartGame();
	
	UFUNCTION()
	void HandleReturnToMainMenu();

	UFUNCTION()
	void HandleNextLevel();

public:

	void ShowLooseScreen();

	void ShowWinScreen();
	
public:
	UFUNCTION(BlueprintGetter)
	class UScCuwGameHud* GetHudWidget() const;

	UFUNCTION(BlueprintGetter)
	class APawn* GetPlayerPawn() const;

	UFUNCTION(BlueprintGetter)
	class APlayerController* GetPlayerController() const;

	UFUNCTION(BlueprintGetter)
	class UInventorySystemComponent* GetInventoryRef() const;
};

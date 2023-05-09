// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ScCuwGameHud.generated.h"

class IInteractableInterface;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwGameHud : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintGetter = GetPlayerStats, meta = (BindWidget))
	TObjectPtr<class UScCuwPawnStats> PlayerStats;

	UPROPERTY(BlueprintGetter = GetInventory, meta = (BindWidget))
	TObjectPtr<class UScCuwInventoryWidget> Inventory;

	UPROPERTY(BlueprintGetter = GetInteractableItemHelp, meta = (BindWidget))
	TObjectPtr<class UScCuwInteractableItemHelp> InteractableItemHelp;

	UPROPERTY(BlueprintGetter = GetAlterHelpWidget, meta = (BindWidget))
	TObjectPtr<class UAlterHelpWidget> AlterHelpWidget;
	
	UPROPERTY(BlueprintGetter = GetPauseMenu, meta = (BindWidget))
	TObjectPtr<class UPauseMenuWidget> PauseMenu;

	UPROPERTY(BlueprintGetter = GetLooseMenu, meta = (BindWidget))
	TObjectPtr<class UGameLooseMenu> LooseMenu;

	UPROPERTY(BlueprintGetter = GetWinMenu, meta = (BindWidget))
	TObjectPtr<class UGameWinMenu> WinMenu;

	UPROPERTY(BlueprintGetter = GetDamageDisplay, meta = (BindWidget))
	TObjectPtr<class UImage> DamageDisplay;
	
	UPROPERTY(BlueprintGetter = GetGameObjective, meta = (BindWidget))
	TObjectPtr<class UGameObjectiveWidget> GameObjective;
	
	UPROPERTY(EditAnywhere)
	FKey ToggleInventoryPrimaryKey = EKeys::I;

	UPROPERTY(EditAnywhere)
	FKey ToggleInventorySecondaryKey = EKeys::Escape;

	UPROPERTY()
	bool bIsInventoryOpen = false;

	UPROPERTY()
	bool bIsItemHelpTextOpen = false;

	UPROPERTY()
	bool bIsAlterHelpOpen = false;
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	virtual void ShowItemHelp_Implementation(AActor* Item);

	virtual void HideItemHelp_Implementation(AActor* Item);
	
	virtual void HandleHealthDamage_Implementation();

	virtual void HandleShieldDamage_Implementation();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UFUNCTION()
	void HandleToggleInventory(const bool bShouldOpenInventory);
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowItemHelp(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideItemHelp(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleHealthDamage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleShieldDamage();
	
	UFUNCTION(BlueprintCallable)
	void ShowAlterHelp();

	UFUNCTION(BlueprintCallable)
	void HideAlterHelp();
	
public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCuwPawnStats* GetPlayerStats() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryWidget* GetInventory() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInteractableItemHelp* GetInteractableItemHelp() const;

	UFUNCTION(BlueprintGetter)
	class UAlterHelpWidget* GetAlterHelpWidget() const;
	
	UFUNCTION(BlueprintGetter)
	class UPauseMenuWidget* GetPauseMenu() const;

	UFUNCTION(BlueprintGetter)
	class UGameLooseMenu* GetLooseMenu() const;

	UFUNCTION(BlueprintGetter)
	class UGameWinMenu* GetWinMenu() const;

	UFUNCTION(BlueprintGetter)
	class UImage* GetDamageDisplay() const;

	UFUNCTION(BlueprintGetter)
	class UGameObjectiveWidget* GetGameObjective() const;
	
public:

	void ShowLooseScreen();

	void ShowWinScreen();
	
};

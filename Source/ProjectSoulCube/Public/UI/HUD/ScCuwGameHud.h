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
	
	UPROPERTY(EditAnywhere)
	FKey ToggleInventoryPrimaryKey = EKeys::I;

	UPROPERTY(EditAnywhere)
	FKey ToggleInventorySecondaryKey = EKeys::Escape;
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	virtual void ShowItemHelp_Implementation(AActor* Item);

	virtual void HideItemHelp_Implementation(AActor* Item);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowItemHelp(AActor* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideItemHelp(AActor* Item);
public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCuwPawnStats* GetPlayerStats() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryWidget* GetInventory() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInteractableItemHelp* GetInteractableItemHelp() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ScCuwGameHud.generated.h"

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

	UPROPERTY(EditAnywhere)
	FKey ToggleInventoryPrimaryKey = EKeys::I;

	UPROPERTY(EditAnywhere)
	FKey ToggleInventorySecondaryKey = EKeys::Escape;
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);
	
public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCuwPawnStats* GetPlayerStats() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryWidget* GetInventory() const;
};

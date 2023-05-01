// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInventoryWidget.generated.h"

class UInventorySystemComponent;
class UScCuwInventoryItem;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwInventoryWidget : public UScCommonUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetInventoryItemClass)
	TSubclassOf<UUserWidget> InventoryItemClass;

	UPROPERTY(EditAnywhere, BlueprintGetter = GetInventorySize, BlueprintSetter = SetInventorySize)
	int32 InventorySize = 4;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetMaxInventorySize, BlueprintSetter = SetMaxInventorySize)
	int32 MaxInventorySize = 20;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> InventorySizeText;
	
	UPROPERTY(BlueprintGetter = GetScrollBox, meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox;

	UPROPERTY(BlueprintGetter = GetWrapBox, meta = (BindWidget))
	TObjectPtr<class UWrapBox> WrapBox;

	UPROPERTY(BlueprintGetter = GetInventoryItemStats, meta = (BindWidget))
	TObjectPtr<class UScCuwInventoryItemStats> InventoryItemStats;
	
private:
	UPROPERTY(BlueprintGetter = GetPlayerPawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> PlayerPawn;

	UPROPERTY(BlueprintGetter = GetInventoryRef, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventorySystemComponent> InventoryRef;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<UScCuwInventoryItem>> InventoryItems;
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	void UpdateInventorySizeText();

	UFUNCTION()
	void HandleInventoryItemAdd(const FName RowId, const int32 ItemQuantity);
	
	UFUNCTION()
	void HandleInventoryItemRemove(const FName RowId, const int32 ItemQuantity);

	UFUNCTION()
	void HandleToggleInventory(const bool bShouldOpenInventory);

	UFUNCTION()
	void HandleInventorySizeChanged(const int32 NewSize);

	UFUNCTION()
	void HandleMaxInventorySizeChanged(const int32 NewSize);

	UFUNCTION()
	void HandleInventoryItemButtonClicked(UScCuwInventoryItem* ItemReference);

	UFUNCTION()
	static void SetInventoryItemVisibility(UScCuwInventoryItem* ItemWidget, const int32 ItemQuantity);

	UFUNCTION()
	void HandleItemUseButtonPressed(UScCuwInventoryItem* ItemReference);

	UFUNCTION()
	void HandleItemDropButtonPressed(UScCuwInventoryItem* ItemReference);

	UFUNCTION()
	void HandleItemCancelButtonPressed(UScCuwInventoryItem* ItemReference);
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);

public:
	// Getters

	UFUNCTION(BlueprintGetter)
	int32 GetInventorySize() const;

	UFUNCTION(BlueprintGetter)
	int32 GetMaxInventorySize() const;

	UFUNCTION(BlueprintGetter)
	class UScrollBox* GetScrollBox() const;

	UFUNCTION(BlueprintGetter)
	class UWrapBox* GetWrapBox() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryItemStats* GetInventoryItemStats() const;
	
	UFUNCTION(BlueprintGetter)
	class APawn* GetPlayerPawn() const;

	UFUNCTION(BlueprintGetter)
	class UInventorySystemComponent* GetInventoryRef() const;

	const TMap<FName, TObjectPtr<UScCuwInventoryItem>>& GetInventoryItems() const;

	UFUNCTION(BlueprintGetter)
	TSubclassOf<class UUserWidget> GetInventoryItemClass() const;

public:
	UFUNCTION(BlueprintSetter)
	void SetInventorySize(const int32 NewSize);

	UFUNCTION(BlueprintSetter)
	void SetMaxInventorySize(const int32 NewSize);
};

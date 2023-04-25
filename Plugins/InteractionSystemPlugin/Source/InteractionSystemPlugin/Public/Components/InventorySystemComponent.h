// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddItem, const FName, ItemRowId, const int32, ItemQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoveItem, const FName, ItemRowId, const int32, ItemQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryPressed, const bool, bShouldOpenInventory);

class UDataTable;
struct FInventoryItemInfo;
class IInteractableInterface;
class AInteractable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEMPLUGIN_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY(BlueprintGetter = GetInventorySize, BlueprintSetter = SetInventorySize, meta = (AllowPrivateAccess = "true"))
	int32 InventorySize = 0;
	
	UPROPERTY(BlueprintGetter = GetMaxInventorySize, BlueprintSetter = SetMaxInventorySize, meta = (AllowPrivateAccess = "true"))
	int32 MaxInventorySize = 20;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RequiredAssetDataTags="RowStructure=/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	UDataTable* InventoryInfoTable;
	
	// TMap<FInventoryItemInfo*, int32> Inventory;

	UPROPERTY()
	TMap<FName, int32> Inventory;

	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY()
	bool bIsInventoryOpen = false;

private:
	FOnAddItem AddItemDelegate;
	FOnRemoveItem RemoveItemDelegate;
	FOnInventoryPressed InventoryPressedDelegate;
	
public:
	// Sets default values for this component's properties
	UInventorySystemComponent();

	~UInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Fetch all the inventory data from the datatable
	void FetchInventoryTableDataToInventoryMap();

	// Get item info from data table.
	FInventoryItemInfo* FetchItemDataFromTable(AActor* Actor) const;

	FVector CalculateItemDropLocation() const;
	
public:
	// Add the item into inventory Array.
	UFUNCTION(BlueprintCallable)
	void AddItem(AActor* Actor);

	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void RemoveItem(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemByItemRowName(FName ItemRow);
	
	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void UseInventoryItem(FName ItemRow);

	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void DropInventoryItem(FName ItemRow);

	// Add the item into inventory Array.
	UFUNCTION(BlueprintCallable)
	bool CanAddItem(AActor* Actor);

	// Get item info from data table.
	UFUNCTION(BlueprintCallable)
	bool FetchItemDataReferenceFromTable(AActor* Actor, FInventoryItemInfo& OutItemInfo) const;

	UFUNCTION(BlueprintCallable)
	const TMap<FName, int32>& GetInventory() const;

	FInventoryItemInfo* GetInventoryItemInfo(const FName RowName) const;
	
	TArray<FInventoryItemInfo*> GetInventoryItemsInfo() const;

	UFUNCTION()
	void ToggleInventory();

public:
	FOnAddItem* GetAddItemDelegate() { return &AddItemDelegate; }

	FOnRemoveItem* GetRemoveItemDelegate() { return &RemoveItemDelegate; }
	
	FOnInventoryPressed* GetInventoryPressedDelegate() { return &InventoryPressedDelegate; }

public:

	UFUNCTION(BlueprintGetter)
	int32 GetInventorySize();

	UFUNCTION(BlueprintGetter)
	int32 GetMaxInventorySize();

public:

	UFUNCTION(BlueprintSetter)
	void SetInventorySize(const int32 InSize);

	UFUNCTION(BlueprintSetter)
	void SetMaxInventorySize(const int32 InSize);
	
};

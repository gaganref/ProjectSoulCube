// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAddItem, const FName, ItemRowId, const int32, ItemQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRemoveItem, const FName, ItemRowId, const int32, ItemQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryPressed, const bool, bShouldOpenInventory);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventorySizeChanged, const int32, NewSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxInventorySizeChanged, const int32, NewSize);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRequestOfferItem, const bool, bShouldOpen);

class UDataTable;
struct FInventoryItemInfo;
class IInteractableInterface;
class AInteractable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEMPLUGIN_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintGetter = GetInventorySize, BlueprintSetter = SetInventorySize)
	int32 InventorySize = 0;
	
	UPROPERTY(BlueprintGetter = GetMaxInventorySize, BlueprintSetter = SetMaxInventorySize)
	int32 MaxInventorySize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RequiredAssetDataTags="RowStructure=/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	UDataTable* InventoryInfoTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug = false;

	UPROPERTY()
	TMap<FName, int32> Inventory;

	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY()
	TObjectPtr<AActor> AlterRef;
	
	UPROPERTY()
	bool bIsInventoryOpen = false;

private:
	FOnPickItem PickItemDelegate;
	FOnDropItem DropItemDelegate;
	FOnAddItem AddItemDelegate;
	FOnRemoveItem RemoveItemDelegate;
	FOnInventoryPressed InventoryPressedDelegate;
	FOnInventorySizeChanged InventorySizeChangedDelegate;
	FOnMaxInventorySizeChanged MaxInventorySizeChangedDelegate;
	FOnRequestOfferItem RequestOfferItemDelegate;
	
public:
	// Sets default values for this component's properties
	UInventorySystemComponent();

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

	//	Offers the item to the possible alter and Removes the item from the inventory array.
	UFUNCTION(BlueprintCallable)
	void OfferInventoryItem(FName ItemRow);
	
	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void UseInventoryItem(FName ItemRow);

	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void DropInventoryItem(FName ItemRow);

	// Add the item into inventory Array.
	UFUNCTION(BlueprintCallable)
	bool CanAddItem(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void RequestBeginItemOfferings(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void RequestEndItemOfferings();
	
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
	FOnPickItem* GetPickItemDelegate() { return &PickItemDelegate; }
	
	FOnDropItem* GetDropItemDelegate() { return &DropItemDelegate; }
	
	FOnAddItem* GetAddItemDelegate() { return &AddItemDelegate; }

	FOnRemoveItem* GetRemoveItemDelegate() { return &RemoveItemDelegate; }
	
	FOnInventoryPressed* GetInventoryPressedDelegate() { return &InventoryPressedDelegate; }

	FOnInventorySizeChanged* GetInventorySizeChangedDelegate() { return &InventorySizeChangedDelegate; }
	
	FOnMaxInventorySizeChanged* GetMaxInventorySizeChangedDelegate() { return &MaxInventorySizeChangedDelegate; }

	FOnRequestOfferItem* GetRequestOfferItemDelegate() { return &RequestOfferItemDelegate; }
	
public:

	UFUNCTION(BlueprintGetter)
	int32 GetInventorySize();

	UFUNCTION(BlueprintGetter)
	int32 GetMaxInventorySize();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsInventoryOpen() const;

public:

	UFUNCTION(BlueprintCallable)
	void IncreaseInventorySize(const int32 InSize);

	UFUNCTION(BlueprintCallable)
	void DecreaseInventorySize(const int32 InSize);
	
	UFUNCTION(BlueprintSetter)
	void SetInventorySize(const int32 InSize);

	UFUNCTION(BlueprintSetter)
	void SetMaxInventorySize(const int32 InSize);
	
};

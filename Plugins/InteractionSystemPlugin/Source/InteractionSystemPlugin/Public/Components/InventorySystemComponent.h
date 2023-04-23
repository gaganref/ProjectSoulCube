// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventorySystemComponent.generated.h"

class UDataTable;
struct FInventoryItemInfo;
class IInteractableInterface;
class AInteractable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEMPLUGIN_API UInventorySystemComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 InventorySize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MaxInventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RequiredAssetDataTags="RowStructure=/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	UDataTable* InventoryInfoTable;
	
	UPROPERTY()
	TArray<FInventoryItemInfo> Inventory;

public:
	// Sets default values for this component's properties
	UInventorySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Fetch all the inventory data from the datatable
	UFUNCTION(BlueprintCallable)
	void FetchInventoryTableData();
	
	// Add the item into inventory Array.
	UFUNCTION(BlueprintCallable)
	void AddItem(AActor* Actor);

	// Removes the item from the inventory array using the item.
	UFUNCTION(BlueprintCallable)
	void RemoveItem(AActor* Actor);

	// Add the item into inventory Array.
	UFUNCTION(BlueprintCallable)
	bool CanAddItem(AActor* Actor);

	// Get item info from data table.
	UFUNCTION(BlueprintCallable)
	void FetchItemDataFromTable(AActor* Actor);
};

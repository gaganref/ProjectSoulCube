// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventorySystemComponent.h"

#include "Interface/InteractableInterface.h"
#include "..\..\Public\Misc\InteractionStructs.h"


// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UInventorySystemComponent::~UInventorySystemComponent()
{
	// Inventory.Empty();
}

// Called when the game starts
void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());
	
	// ...
	FetchInventoryTableDataToInventoryMap();
}

// Called every frame
void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	for(auto It : Inventory)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, FString::Printf(TEXT("Item - %s :: Quamtity - %s."), *It.Key.ToString(), *FString::FromInt(It.Value)));
	}
}

void UInventorySystemComponent::AddItem(AActor* Actor)
{
	if(!CanAddItem(Actor) || !OwnerPawn)
	{
		return;
	}
	
	FName RowName = IInteractableInterface::Execute_GetItemId(Actor);
	FInventoryItemInfo* Item = FetchItemDataFromTable(Actor);
	if(!Item)
	{
		return;
	}

	const int NewItemQuantity = Inventory.FindRef(RowName) + 1;
	Inventory.Add(RowName, NewItemQuantity);

	if(AddItemDelegate.IsBound())
	{
		AddItemDelegate.Broadcast(RowName, NewItemQuantity);
	}
	Actor->Destroy();
}

void UInventorySystemComponent::RemoveItem(AActor* Actor)
{
}

bool UInventorySystemComponent::CanAddItem(AActor* Actor)
{
	if(!Actor)
	{
		return false;
	}
	
	if(!Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return false;
	}
	
	FInventoryItemInfo* Item = FetchItemDataFromTable(Actor);
	if(!Item)
	{
		return false;
	}
	
	if(Item->ItemSize + InventorySize > MaxInventorySize)
	{
		return false;
	}
	
	return true;
}

void UInventorySystemComponent::FetchInventoryTableDataToInventoryMap()
{
	if(!InventoryInfoTable)
	{
		return;
	}

	for(auto Item : InventoryInfoTable->GetRowNames())
	{
		Inventory.Add(Item, 0);
	}
}

FInventoryItemInfo* UInventorySystemComponent::FetchItemDataFromTable(AActor* Actor) const
{
	if(!Actor)
	{
		return nullptr;
	}
	
	if(!Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return nullptr;
	}

	if(!InventoryInfoTable)
	{
		return nullptr;
	}
	
	FName RowName = IInteractableInterface::Execute_GetItemId(Actor);
	FInventoryItemInfo* Item = GetInventoryItemInfo(RowName);
	return Item;
}

bool UInventorySystemComponent::FetchItemDataReferenceFromTable(AActor* Actor, FInventoryItemInfo& OutItemInfo) const
{
	FInventoryItemInfo* Item = FetchItemDataFromTable(Actor);
	if(!Item)
	{
		return false;
	}

	OutItemInfo = *Item;
	return true;
}

const TMap<FName, int32>& UInventorySystemComponent::GetInventory() const
{
	return Inventory;
}

FInventoryItemInfo* UInventorySystemComponent::GetInventoryItemInfo(const FName RowName) const
{
	return InventoryInfoTable->FindRow<FInventoryItemInfo>(RowName, TEXT("GetInventoryItemInfo in InventorySt=ystemComponent"));
}

TArray<FInventoryItemInfo*> UInventorySystemComponent::GetInventoryItemsInfo() const
{
	TArray<FInventoryItemInfo*> OutArray;
	InventoryInfoTable->GetAllRows(TEXT("FetchInventoryTableDataToInventoryMap in InventorySt=ystemComponent"), OutArray);

	return OutArray;
}

void UInventorySystemComponent::ToggleInventory()
{
	bIsInventoryOpen = !bIsInventoryOpen;
	if(InventoryPressedDelegate.IsBound())
	{
		InventoryPressedDelegate.Broadcast(bIsInventoryOpen);
	}
}

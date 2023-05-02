// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventorySystemComponent.h"

#include "Interface/InteractableInterface.h"
#include "..\..\Public\Misc\InteractionStructs.h"
#include "Interface/InventoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UInventorySystemComponent::UInventorySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	IncreaseInventorySize(Item->ItemWeight);
	// InventorySize += Item->ItemWeight;
	
	if(AddItemDelegate.IsBound())
	{
		AddItemDelegate.Broadcast(RowName, NewItemQuantity);
	}
	
	Actor->Destroy();
}

void UInventorySystemComponent::RemoveItem(AActor* Actor)
{
	
}

bool UInventorySystemComponent::RemoveItemByItemRowName(FName ItemRow)
{
	FInventoryItemInfo* Item = GetInventoryItemInfo(ItemRow);
	if(!Item)
	{
		return false;
	}
	
	const int NewItemQuantity = Inventory.FindRef(ItemRow) - 1;
	if(NewItemQuantity < 0)
	{
		return false;
	}
	
	Inventory.Add(ItemRow, NewItemQuantity);

	DecreaseInventorySize(Item->ItemWeight);
	// InventorySize -= Item->ItemWeight;
	
	if(RemoveItemDelegate.IsBound())
	{
		RemoveItemDelegate.Broadcast(ItemRow, NewItemQuantity);
	}

	return true;
}

void UInventorySystemComponent::UseInventoryItem(FName ItemRow)
{
	if(!OwnerPawn)
	{
		return;
	}
	
	FInventoryItemInfo* Item = GetInventoryItemInfo(ItemRow);
	if(!Item)
	{
		return;
	}
	if(!Item->ItemClass)
	{
		return;
	}
	
	AActor* ItemActor = Item->ItemClass->GetDefaultObject<AActor>();
	if(!ItemActor)
	{
		return;
	}
	if(!ItemActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return;
	}
	if(!IInteractableInterface::Execute_CanInteract(ItemActor, OwnerPawn))	// Stop use item if we cannot interact with the items
	{
		return;
	}

	IInteractableInterface::Execute_OnInteract(ItemActor, OwnerPawn);
	if(RemoveItemByItemRowName(ItemRow))
	{
		UE_LOG(LogTemp, Warning, TEXT("placeHolder for Use Item"));
	}
}

void UInventorySystemComponent::DropInventoryItem(FName ItemRow)
{
	if(!OwnerPawn || !GetWorld())
	{
		return;
	}

	FInventoryItemInfo* Item = GetInventoryItemInfo(ItemRow);
	if(!Item)
	{
		return;	
	}
	
	if(RemoveItemByItemRowName(ItemRow))
	{
		FRotator ItemSpawnRotation;
		FVector ItemSpawnLocation = CalculateItemDropLocation();
		ItemSpawnLocation = ItemSpawnRotation.RotateVector(ItemSpawnLocation);
		
		FActorSpawnParameters ItemSpawnParams;
		ItemSpawnParams.Instigator = OwnerPawn;
		ItemSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor(Item->ItemClass, &ItemSpawnLocation, &ItemSpawnRotation, ItemSpawnParams);
	}
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
	
	if(GetInventorySize() + Item->ItemWeight > GetMaxInventorySize())
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

FVector UInventorySystemComponent::CalculateItemDropLocation() const
{
	FVector OutLocation;
	if(!OwnerPawn || !GetWorld())
	{
		return OutLocation;
	}

	const FVector PawnLocation = OwnerPawn->GetActorLocation();
	const FVector PawnForwardVector = OwnerPawn->GetActorForwardVector();

	FVector LineTraceStartLocation = FMath::VRandCone(PawnForwardVector, FMath::DegreesToRadians(30.0f));
	LineTraceStartLocation *= 500.0f;
	LineTraceStartLocation += PawnLocation;
	FVector LineTraceEndLocation = LineTraceStartLocation - FVector(0.0f, 0.0f, 500.0f);
	FCollisionQueryParams TraceParams;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, LineTraceStartLocation, LineTraceEndLocation, ECC_Visibility, TraceParams);

	return HitResult.Location;
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
	return InventoryInfoTable->FindRow<FInventoryItemInfo>(RowName, TEXT("GetInventoryItemInfo in InventorySystemComponent"));
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

int32 UInventorySystemComponent::GetInventorySize()
{
	return InventorySize;
}

int32 UInventorySystemComponent::GetMaxInventorySize()
{
	return MaxInventorySize;
}

void UInventorySystemComponent::IncreaseInventorySize(const int32 InSize)
{
	SetInventorySize(InventorySize + InSize);
}

void UInventorySystemComponent::DecreaseInventorySize(const int32 InSize)
{
	SetInventorySize(InventorySize - InSize);
}

void UInventorySystemComponent::SetInventorySize(const int32 InSize)
{
	InventorySize = InSize;
	
	if(InventorySizeChangedDelegate.IsBound())
	{
		InventorySizeChangedDelegate.Broadcast(InventorySize);
	}
}

void UInventorySystemComponent::SetMaxInventorySize(const int32 InSize)
{
	MaxInventorySize = InSize;

	if(MaxInventorySizeChangedDelegate.IsBound())
	{
		MaxInventorySizeChangedDelegate.Broadcast(MaxInventorySize);
	}
}

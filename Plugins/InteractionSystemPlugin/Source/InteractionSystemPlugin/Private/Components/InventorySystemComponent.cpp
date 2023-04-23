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


// Called when the game starts
void UInventorySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventorySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventorySystemComponent::AddItem(AActor* Actor)
{
	if(!Actor)
	{
		return;
	}
	
	if(!Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return;
	}
		
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
	if(InventorySize >= MaxInventorySize)
	{
		return false;
	}

	// for(const auto& Item : Inventory)
	// {
	// 	if
	// }
	
	return false;
}

void UInventorySystemComponent::FetchInventoryTableData()
{
}

void UInventorySystemComponent::FetchItemDataFromTable(AActor* Actor)
{
	if(!Actor)
	{
		return;
	}
	
	if(!Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		return;
	}

	FName RowName = IInteractableInterface::Execute_GetItemId(Actor);
	// auto Test = InventoryInfoTable->GetRowMap().Find(RowName);
	FInventoryItemInfo* Item = InventoryInfoTable->FindRow<FInventoryItemInfo>(RowName, TEXT("FetchItemDataFromTable"));

	FString Output = Item->ItemName.ToString();
	GLog->Log(Output);
}

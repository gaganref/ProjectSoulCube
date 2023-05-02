// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Interactable.h"

#include "Components/WidgetComponent.h"
#include "Misc/InteractionStructs.h"


// Sets default values
AInteractable::AInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable::UpdateItemData()
{
	ItemData = ItemInfo.GetRow<FInventoryItemInfo>(TEXT("BeginPlay in AInteractable"));
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FName AInteractable::GetItemId_Implementation()
{
	return ItemInfo.RowName;
}

FName AInteractable::GetItemDescription_Implementation()
{
	if(!ItemData)
	{
		UpdateItemData();
		if(!ItemData)
		{
			return TEXT("NONE");
		}
	}
	
	return ItemData->ItemDescription;
}

FName AInteractable::GetItemName_Implementation()
{
	if(!ItemData)
	{
		UpdateItemData();
		if(!ItemData)
		{
			return TEXT("NONE");
		}
	}
	
	return ItemData->ItemName;
}

int32 AInteractable::GetItemWeight_Implementation()
{
	if(!ItemData)
	{
		UpdateItemData();
		if(!ItemData)
		{
			return -1;
		}
	}
	
	return ItemData->ItemWeight;
}

void AInteractable::OnInteract_Implementation(AActor* Caller)
{
	IInteractableInterface::OnInteract_Implementation(Caller);
}

void AInteractable::BeginFocus_Implementation(AActor* Caller)
{
	IInteractableInterface::BeginFocus_Implementation(Caller);

	// if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT("%s Debug- Begin Focus."), *GetItemId_Implementation().ToString()));
}

void AInteractable::EndFocus_Implementation(AActor* Caller)
{
	IInteractableInterface::EndFocus_Implementation(Caller);

	// if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString::Printf(TEXT("%s Debug- End Focus."), *GetItemId_Implementation().ToString()));
}

bool AInteractable::CanInteract_Implementation(AActor* Caller)
{
	return true;
}

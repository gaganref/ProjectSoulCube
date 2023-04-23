// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionDetectionComponent.h"

#include "Components/InventorySystemComponent.h"
#include "Interface/InteractableInterface.h"
#include "Interface/InventoryInterface.h"


// Sets default values for this component's properties
UInteractionDetectionComponent::UInteractionDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn)
	{
		OwnerController = OwnerPawn->GetController();

		if(OwnerPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			InventoryRef = IInventoryInterface::Execute_GetInventorySystemComponent(OwnerPawn);
		}
	}
}


// Called every frame
void UInteractionDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bIsInteractingWithFocusedActor)
	{
		LookForInteractable();	
	}
}

void UInteractionDetectionComponent::LookForInteractable()
{
	if(!OwnerController)
	{
		return;
	}

	const TObjectPtr<UWorld> World = GetWorld();
	if(!World)
	{
		return;
	}

	FVector Location;
	FRotator Rotation;
	FHitResult HitResult;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector StartPoint = Location;
	FVector EndPoint = StartPoint + (Rotation.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;
	const bool bHit = World->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);
	
	if(bHit)
	{
		TObjectPtr<AActor> HitActor = HitResult.GetActor();
		if(HitActor)
		{
			if(HitActor != FocusedActor)
			{
				EndFocusOnActor(FocusedActor);
				FocusedActor = BeginFocusOnActor(HitActor);
			}
		}
	}
	
	DrawDebugShape(World, bHit, StartPoint, EndPoint, HitResult);
}

void UInteractionDetectionComponent::DrawDebugShape(const UWorld* World, const bool bHit, const FVector& StartPoint, const FVector& EndPoint, const FHitResult& HitResult)
{
	if(!World)
	{
		return;
	}
	if(!bDebug)
	{
		return;
	}

	FColor DrawColor = FColor::Red;
	FColor HitPointColor = FColor::Yellow;
	constexpr float LifeTime = 1.0f;
		
	if(FocusedActor)
	{
		DrawColor = FColor::Green;
		HitPointColor = FColor::Blue;
	}

	DrawDebugLine(World, StartPoint, EndPoint, DrawColor, false, LifeTime);

	if(bHit)
	{
		DrawDebugSolidBox(World, HitResult.ImpactPoint, FVector(3, 3, 3), HitPointColor, false, LifeTime);
	}
}

AActor* UInteractionDetectionComponent::BeginFocusOnActor(AActor* Actor)
{
	if(Actor)
	{
		if(Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			IInteractableInterface::Execute_BeginFocus(Actor, OwnerPawn);
			return Actor;
		}
	}

	return nullptr;
}

void UInteractionDetectionComponent::EndFocusOnActor(AActor* Actor)
{
	if(Actor)
	{
		if(Actor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
		{
			IInteractableInterface::Execute_EndFocus(Actor, OwnerPawn);
		}
	}
}

void UInteractionDetectionComponent::OnItemUseButtonPressed(const FInputActionValue& ActionValue)
{
	if(bIsInteractingWithFocusedActor)
	{
		return;
	}
	if(!FocusedActor)
	{
		return;
	}
	
	bIsInteractingWithFocusedActor = true;

	// TODO: apply its gameplay effect
	UE_LOG(LogTemp, Warning, TEXT("Item Use Pressed"));
	InventoryRef->FetchItemDataFromTable(FocusedActor);
	bIsInteractingWithFocusedActor = false;
}

void UInteractionDetectionComponent::OnItemPickupButtonPressed(const FInputActionValue& ActionValue)
{
	if(bIsInteractingWithFocusedActor)
	{
		return;
	}
	if(!FocusedActor)
	{
		return;
	}
	
	bIsInteractingWithFocusedActor = true;

	// TODO: Add item to inventory and clean up the object by changing its collision and physics values and visibility
	UE_LOG(LogTemp, Warning, TEXT("Item Pickup Pressed %s"), *FocusedActor->GetClass()->GetName());
	// InventoryRef->AddItem();
	
	bIsInteractingWithFocusedActor = false;
}

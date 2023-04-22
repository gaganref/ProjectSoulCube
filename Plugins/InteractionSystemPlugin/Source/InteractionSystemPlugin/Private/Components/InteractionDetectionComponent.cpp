// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionDetectionComponent.h"

#include "Engine/Private/KismetTraceUtils.h"
#include "Interface/InteractableInterface.h"
#include "Kismet/KismetSystemLibrary.h"


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
	}
}


// Called every frame
void UInteractionDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LookForInteractable();
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
				if(FocusedActor)
				{
					if(FocusedActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
					{
						IInteractableInterface::Execute_EndFocus(FocusedActor, OwnerPawn);
						FocusedActor = nullptr;
					}
				}

				if(HitActor->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
				{
					IInteractableInterface::Execute_BeginFocus(HitActor, OwnerPawn);
					FocusedActor = HitActor;
				}
				else
				{
					FocusedActor = nullptr;
				}
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

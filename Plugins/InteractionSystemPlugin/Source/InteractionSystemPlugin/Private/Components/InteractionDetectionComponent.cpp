// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionDetectionComponent.h"

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

	FVector Location;
	FRotator Rotation;
	FHitResult HitResult;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector StartPoint = Location;
	FVector EndPoint = StartPoint + (Rotation.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

	bool bHitValidActor = false;
	
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
				// FocusedActor = HitActor;
			}
		}
		
	}
	
	if(bDebug)
	{
		FColor DrawColor = FColor::Red;
		FColor HitPointColor = FColor::Yellow;
		
		if(FocusedActor)
		{
			DrawColor = FColor::Green;
			HitPointColor = FColor::Blue;
		}
		
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, DrawColor, false, 1.0f);

		if(bHit)
		{
			DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(3, 3, 3), HitPointColor, false, 1.0f);
		}
	}
}

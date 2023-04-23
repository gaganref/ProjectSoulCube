// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionDetectionComponent.generated.h"


class IInteractableInterface;
struct FInputActionValue;
class UInventorySystemComponent;

UCLASS(ClassGroup=(Custom), Within=Pawn, meta=(BlueprintSpawnableComponent))
class INTERACTIONSYSTEMPLUGIN_API UInteractionDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TObjectPtr<APawn> OwnerPawn;

	UPROPERTY()
	TObjectPtr<AController> OwnerController;

	UPROPERTY()
	TObjectPtr<UInventorySystemComponent> InventoryRef;

	UPROPERTY()
	TObjectPtr<AActor> FocusedActor;

	UPROPERTY()
	bool bIsInteractingWithFocusedActor = false;

	UPROPERTY(Category="Interaction Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug = false;
	
	UPROPERTY(Category="Interaction Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 50.0f;

public:
	// Sets default values for this component's properties
	UInteractionDetectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/*
	 *   Traces from start to end with given params, runs every tick to look for Interactable objects.
	 */
	virtual void LookForInteractable();

	virtual void DrawDebugShape(const UWorld* World, const bool bHit, const FVector& StartPoint, const FVector& EndPoint, const FHitResult& HitResult);

	virtual AActor* BeginFocusOnActor(AActor* Actor);

	virtual void EndFocusOnActor(AActor* Actor);
public:
	UFUNCTION()
	void OnItemUseButtonPressed(const FInputActionValue& ActionValue);
	
	UFUNCTION()
	void OnItemPickupButtonPressed(const FInputActionValue& ActionValue);
};

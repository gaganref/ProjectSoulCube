// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactable.h"
#include "AScCollectableItem.generated.h"

class URotatingMovementComponent;
class UInterpToMovementComponent;
class USCGameplayEffect;

UCLASS()
class PROJECTSOULCUBE_API AAScCollectableItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> InteractableMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInterpToMovementComponent> InterpToMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;
	
protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bAutoSetInteractableLocalOffset = true;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FVector OffsetAdjuster;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USCGameplayEffect> ItemGameplayAffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType="/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemInfo;
	
	FInventoryItemInfo* ItemInfoData;
	
public:
	// Sets default values for this actor's properties
	AAScCollectableItem();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateItemInfoData();
	
	// To make sure that the interactable is above the origin of the actor.
	virtual void AdjustInteractablePosition();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual FName GetItemId_Implementation() override;
	
	virtual FName GetItemDescription_Implementation() override;
	
	virtual FName GetItemName_Implementation() override;
	
	virtual int32 GetItemWeight_Implementation() override;

	virtual void OnInteract_Implementation(AActor* Caller) override;
	
	virtual void BeginFocus_Implementation(AActor* Caller) override;
	
	virtual void EndFocus_Implementation(AActor* Caller) override;

	virtual bool CanInteract_Implementation(AActor* Caller) override;

public:
	FORCEINLINE UStaticMeshComponent* GetInteractableMesh() const { return InteractableMesh; }

};

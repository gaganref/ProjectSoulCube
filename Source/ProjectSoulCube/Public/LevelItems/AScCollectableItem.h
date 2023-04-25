// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactable.h"
#include "AScCollectableItem.generated.h"

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
	TObjectPtr<UWidgetComponent> HelpWidget;
	
protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	bool bAutoSetInteractableLocalOffset = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<USCGameplayEffect> ItemGameplayAffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType="/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemInfo;
	
public:
	// Sets default values for this actor's properties
	AAScCollectableItem();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// To make sure that the interactable is above the origin of the actor.
	virtual void AdjustInteractablePosition();
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual FName GetItemId_Implementation() override;
	
	virtual void OnInteract_Implementation(AActor* Caller) override;

	virtual void BeginFocus_Implementation(AActor* Caller) override;
	
	virtual void EndFocus_Implementation(AActor* Caller) override;

	virtual bool CanInteract_Implementation(AActor* Caller) override;

public:
	UFUNCTION(Category = "Interactables|CollectableItem", BlueprintNativeEvent, BlueprintCallable)
	FName GetItemId();
	
	UFUNCTION(Category = "Interactables|CollectableItem", BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(AActor* Caller);
	
	UFUNCTION(Category = "Interactables|CollectableItem", BlueprintNativeEvent, BlueprintCallable)
	void BeginFocus(AActor* Caller);
	
	UFUNCTION(Category = "Interactables|CollectableItem", BlueprintNativeEvent, BlueprintCallable)
	void EndFocus(AActor* Caller);

	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	bool CanInteract(AActor* Caller);

public:
	FORCEINLINE UStaticMeshComponent* GetInteractableMesh() const { return InteractableMesh; }

	FORCEINLINE UWidgetComponent* GetHelpWidget() const { return HelpWidget; }	
};

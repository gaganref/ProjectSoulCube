// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractableInterface.h"
#include "Interactable.generated.h"

UCLASS()
class INTERACTIONSYSTEMPLUGIN_API AInteractable : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RowType="/Script/InteractionSystemPlugin.InventoryItemInfo", AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemInfo;
	
public:
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual FName GetItemId_Implementation() override;
	
	virtual void OnInteract_Implementation(AActor* Caller) override;
	
	virtual void BeginFocus_Implementation(AActor* Caller) override;
	
	virtual void EndFocus_Implementation(AActor* Caller) override;

public:
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	FName GetItemId();
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(AActor* Caller);
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void BeginFocus(AActor* Caller);
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void EndFocus(AActor* Caller);
	
};

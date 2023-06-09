﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

struct FDataTableRowHandle;
// This class does not need to be modified.
UINTERFACE()
class INTERACTIONSYSTEMPLUGIN_API UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIONSYSTEMPLUGIN_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	FName GetItemId();

	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	FName GetItemName();
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	int32 GetItemWeight();

	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	FName GetItemDescription();
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void OnInteract(AActor* Caller);
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void BeginFocus(AActor* Caller);
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	void EndFocus(AActor* Caller);
	
	UFUNCTION(Category = "InteractionSystem|Interactables", BlueprintNativeEvent, BlueprintCallable)
	bool CanInteract(AActor* Caller);
};

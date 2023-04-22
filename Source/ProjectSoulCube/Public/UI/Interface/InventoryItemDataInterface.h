// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryItemDataInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInventoryItemDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSOULCUBE_API IInventoryItemDataInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Interface to handle movement input 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetItemQuantity();
};

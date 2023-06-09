﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

class UInventorySystemComponent;
// This class does not need to be modified.
UINTERFACE()
class INTERACTIONSYSTEMPLUGIN_API UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INTERACTIONSYSTEMPLUGIN_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventorySystemComponent* GetInventorySystemComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsOwnerAlive();
};

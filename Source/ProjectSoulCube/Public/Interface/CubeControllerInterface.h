// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CubeControllerInterface.generated.h"

struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCubeControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Any pawn or character in a GameMode that uses CubeController must implement this interface. 
 */
class PROJECTSOULCUBE_API ICubeControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Interface to handle movement input 
	UFUNCTION(Category = "CubeControllerInterface|Input", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Move"))
	void HandleInputMove(const FInputActionValue& ActionValue);
	// virtual void HandleInputMove_Implementation(FInputActionValue& ActionValue) = 0;

	// Interface to handle look input
	UFUNCTION(Category = "CubeControllerInterface|Input", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Look"))
	void HandleInputLook(const FInputActionValue& ActionValue);
};

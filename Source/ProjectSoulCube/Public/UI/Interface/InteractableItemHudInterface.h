// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableItemHudInterface.generated.h"

class IInteractableInterface;
class AInteractable;
// This class does not need to be modified.
UINTERFACE()
class UInteractableItemHudInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSOULCUBE_API IInteractableItemHudInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowItemInfo(AActor* InteractableRef);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideItemInfo(AActor* InteractableRef);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubeController.generated.h"

class ICubeControllerInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API ACubeController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this controller properties
	ACubeController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:

#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Debug", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug;
#endif
	
private:
	/** Ref to the current player pawn that implements ICubeControllerInterface */
	UPROPERTY()
	TObjectPtr<APawn> PawnRef;

private:
	/** Input Mapping Context - Ref to a class that can store mappings between Input Actions and Input Keys */
	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Ref to the input action move */
	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionMove;

	/** Ref to the input action look */
	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionLook;

protected:

	// Called to handle movement input
	void HandleMove(const FInputActionValue& ActionValue);

	// Called to handle look input 
	void HandleLook(const FInputActionValue& ActionValue);

protected:
	
	virtual void AcknowledgePossession(APawn* P) override;
};

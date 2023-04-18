// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/CubeController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "DebugLibraryCommon.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Interface/CubeControllerInterface.h"

// Sets default values
ACubeController::ACubeController(const FObjectInitializer& ObjectInitializer)
{
}

// Called when the game starts or when spawned
void ACubeController::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	if(GetPawn()->GetClass()->ImplementsInterface(UCubeControllerInterface::StaticClass()))
	{
		PawnRef = GetPawn();
	}
	else
	{
#if WITH_EDITORONLY_DATA
		if(bDebug)
		{
			DEBUG_PRINT_CUSTOM_TEXT_WITH_INFO(TEXT("PawnRef is not valid. - Check if it implements the required interfaces"));
		}
#endif		
	}
}

// Called to bind functionality to input
void ACubeController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ACubeController::HandleMove);
		EnhancedInputComponent->BindAction(InputActionLook, ETriggerEvent::Triggered, this, &ACubeController::HandleLook);
	}
}

// Called to handle movement input
void ACubeController::HandleMove(const FInputActionValue& ActionValue)
{
	if(PawnRef)
	{
		ICubeControllerInterface::Execute_HandleInputMove(PawnRef, ActionValue);
	}
}

// Called to handle look input
void ACubeController::HandleLook(const FInputActionValue& ActionValue)
{
	if(PawnRef)
	{
		ICubeControllerInterface::Execute_HandleInputLook(PawnRef, ActionValue);
	}
}

void ACubeController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	const TObjectPtr<IAbilitySystemInterface> ASIActor = Cast<IAbilitySystemInterface>(P);

	if(ASIActor)
	{
		ASIActor->GetAbilitySystemComponent()->InitAbilityActorInfo(P, P);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "DebugLibraryCommon.h"
#include "Camera/FollowCameraActor.h"
#include "Controller/CubeController.h"
#include "InputActionValue.h"

FVector APlayerCharacter::SpawnCameraOffset(FVector(-215.0f, 85.0f, 45.0f));

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 77.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera. Except Yaw
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UWorld> World = GetWorld();
	check(World);
	
	Super::BeginPlay();

	PlayerControllerRef = Cast<ACubeController>(GetController());
	
	if(!FollowCameraClass)
	{
		FollowCameraClass = AFollowCameraActor::StaticClass();
	}
	FActorSpawnParameters CameraSpawnParameters;
	CameraSpawnParameters.Instigator = this;
	CameraSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = GetTransform();
	const FVector RotatedSpawnOffset = SpawnTransform.GetRotation().RotateVector(SpawnCameraOffset);
	SpawnTransform.SetLocation(SpawnTransform.GetLocation() + RotatedSpawnOffset);
	FollowCamera = World->SpawnActor<AFollowCameraActor>(FollowCameraClass->GetDefaultObject()->GetClass(), SpawnTransform, CameraSpawnParameters);
	check(FollowCamera);

	if(PlayerControllerRef)
	{
		PlayerControllerRef->SetViewTarget(FollowCamera);
	}
	else
	{
#if WITH_EDITORONLY_DATA
		if(bDebug)
		{
			DEBUG_PRINT_CUSTOM_TEXT_WITH_INFO(TEXT("PlayerControllerRef is not valid."));
		}
#endif
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::HandleInputMove_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputMove_Implementation(ActionValue);

	// input is a Vector2D
	const FVector2D MovementVector = ActionValue.Get<FVector2D>();

	if (PlayerControllerRef != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = PlayerControllerRef->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::HandleInputLook_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputLook_Implementation(ActionValue);

	// input is a Vector2D
	const FVector2D LookAxisVector = ActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
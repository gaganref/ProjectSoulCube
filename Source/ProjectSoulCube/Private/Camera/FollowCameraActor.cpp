// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/FollowCameraActor.h"

#include "DebugLibraryCommon.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFollowCameraActor::AFollowCameraActor(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this camera to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup camera defaults
	GetCameraComponent()->bConstrainAspectRatio = false;

	// Default FollowCameraActor settings.
	CameraLocationOffset = FVector(-215.0f, 85.0f, 45.0f);
	CameraRotationOffset = FRotator(-15.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AFollowCameraActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnInstigator = GetInstigator();
	
	MoveCamera();
}

// Called every frame
void AFollowCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveCamera();
}

void AFollowCameraActor::MoveCamera()
{
	if(SpawnInstigator)
	{
		// const FVector InstigatorForwardVector = SpawnInstigator->GetActorForwardVector();
		// const FVector TargetCameraLocation = SpawnInstigator->GetActorLocation() + InstigatorForwardVector*CameraOffset;
		// FTransform TargetTransform = SpawnInstigator->GetActorTransform();
		// TargetTransform.SetLocation(TargetCameraLocation);
		const FRotator TargetCameraRotation = SpawnInstigator->GetControlRotation() + CameraRotationOffset;
		const FVector TargetCameraLocation = SpawnInstigator->GetActorLocation() + TargetCameraRotation.RotateVector(CameraLocationOffset);
#if WITH_EDITORONLY_DATA
		if(bDebug)
		{
			DEBUG_PRINT_CUSTOM_TEXT(FString::Printf(TEXT("TargetCameraLocation = %s."), *TargetCameraLocation.ToString()));
		}
#endif
		
		// SetActorTransform(TargetTransform);
		SetActorLocation(TargetCameraLocation);
		SetActorRotation(TargetCameraRotation);
	}
	else
	{
#if WITH_EDITORONLY_DATA
		if(bDebug)
		{
			DEBUG_PRINT_CUSTOM_TEXT(FString::Printf(TEXT("SpawnInstigator is naot valid.")));
		}
#endif		
	}
}

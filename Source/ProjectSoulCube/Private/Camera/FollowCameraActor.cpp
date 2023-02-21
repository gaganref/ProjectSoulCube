// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/FollowCameraActor.h"

#include "Camera/CameraComponent.h"

// Sets default values
AFollowCameraActor::AFollowCameraActor(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this camera to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup camera defaults
	GetCameraComponent()->bConstrainAspectRatio = false;
}

// Called when the game starts or when spawned
void AFollowCameraActor::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<APawn> SpawnInstigator = GetInstigator();
	
	if(SpawnInstigator)
	{
		// The Follow Camera should always tick after the following pawn to avoid visual jitter 
		PrimaryActorTick.AddPrerequisite(SpawnInstigator, SpawnInstigator->PrimaryActorTick);
	}
}

// Called every frame
void AFollowCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

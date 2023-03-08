// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"

#include "DebugFunctionLibrary.h"
#include "..\..\..\..\Plugins\DebugLibrary\Source\DebugLibrary\Public\DebugLibraryCommon.h"
#include "Components/ArrowComponent.h"
#include "Camera/FollowCameraActor.h"
#include "Controller/CubeController.h"
#include "InputActionValue.h"

FName APlayerPawn::PawnMeshName(TEXT("PawnMesh"));
FVector APlayerPawn::SpawnCameraOffset(FVector(-120.0f, 0.0f, 15.0f));


// Sets default values
APlayerPawn::APlayerPawn(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// Make the scene component the root component
	RootComponent = SceneComponent;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(PawnMeshName);
	PawnMesh->SetupAttachment(SceneComponent);
	
#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	if(ArrowComponent){
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(PawnMesh);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
#endif

}	

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
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
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APlayerPawn::HandleInputMove_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputMove_Implementation(ActionValue);

	DEBUG_LOG_CUSTOM_TEXT("Move - to be Implemented");
}

void APlayerPawn::HandleInputLook_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputLook_Implementation(ActionValue);
	DEBUG_LOG_CUSTOM_TEXT("Look - to be Implemented");
}

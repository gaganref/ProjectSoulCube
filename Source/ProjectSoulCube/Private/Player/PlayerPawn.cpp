// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPawn.h"

#include "Components/ArrowComponent.h"
#include "Camera/FollowCameraActor.h"

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

	if(!FollowCameraClass)
	{
		FollowCameraClass = AFollowCameraActor::StaticClass();
	}
	FActorSpawnParameters CameraSpawnParameters;
	CameraSpawnParameters.Instigator = this;
	CameraSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = GetTransform();
	SpawnTransform.AddToTranslation(SpawnCameraOffset);
	// SpawnTransform.SetLocation(SpawnTransform.GetLocation() + SpawnCameraOffset);
	FollowCamera = World->SpawnActor<AFollowCameraActor>(FollowCameraClass->GetDefaultObject()->GetClass(), SpawnTransform, CameraSpawnParameters);
	check(FollowCamera);

	const TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		PlayerController->SetViewTarget(FollowCamera);
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


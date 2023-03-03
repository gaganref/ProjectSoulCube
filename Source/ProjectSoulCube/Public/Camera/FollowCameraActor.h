// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FollowCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API AFollowCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFollowCameraActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(Category = Instigator, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TObjectPtr<APawn> SpawnInstigator;

#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = Debug, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug;
#endif
	
private:	
	UPROPERTY(Category = CameraOffset, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	FVector CameraOffset;
};

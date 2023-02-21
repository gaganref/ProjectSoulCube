// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class AFollowCameraActor;
class UArrowComponent;

UCLASS()
class PROJECTSOULCUBE_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category = Debug, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug;
	
public:
	/** Name of the PawnMesh component. */
	static FName PawnMeshName;

	/**
	 * Initial offset value for the camera to spawn at.
	 *  @note It is just used at spawn and is very minimal, the actual offset should be set in the camera class.
	 */
	static FVector SpawnCameraOffset;
	
private:
	
	/** Default root scene component. */
	UPROPERTY(Category = PawnComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> SceneComponent;
	
	/** The main static mesh associated with this pawn. */
	UPROPERTY(Category = PawnComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PawnMesh;

#if WITH_EDITORONLY_DATA	
	/** Component shown in the editor only to indicate the direction character facing */
	UPROPERTY(Category = PawnComponent, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif

public:
	/** Returns PawnMesh. */
	FORCEINLINE TObjectPtr<UStaticMeshComponent> GetPawnMesh() const {return PawnMesh;}

#if WITH_EDITORONLY_DATA
	/** Returns ArrowComponent **/
	FORCEINLINE TObjectPtr<UArrowComponent> GetArrowComponent() const { return ArrowComponent; }
#endif

private:

	/** Class of the player follow camera that should be spawned. */
	UPROPERTY(Category = FollowCamera, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TSubclassOf<AFollowCameraActor> FollowCameraClass;

	/** Reference to the spawned player follow camera. */
	UPROPERTY(Category = FollowCamera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TObjectPtr<AFollowCameraActor> FollowCamera;
	
public:
	/** Returns Follow Camera */
	FORCEINLINE TObjectPtr<AFollowCameraActor> GetFollowCameraActor() const { return FollowCamera;}
};

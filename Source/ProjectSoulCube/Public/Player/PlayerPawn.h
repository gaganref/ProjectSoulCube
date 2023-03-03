// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/CubeControllerInterface.h"
#include "PlayerPawn.generated.h"

class ACubeController;
class AFollowCameraActor;
class UArrowComponent;
class USceneComponent;

UCLASS()
class PROJECTSOULCUBE_API APlayerPawn : public APawn, public ICubeControllerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Debug", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug;
#endif
	
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
	UPROPERTY(Category = "PawnComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;
	
	/** The main static mesh associated with this pawn. */
	UPROPERTY(Category = "PawnComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PawnMesh;

#if WITH_EDITORONLY_DATA	
	/** Component shown in the editor only to indicate the direction character facing */
	UPROPERTY(Category = "PawnComponent", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
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
	UPROPERTY(Category = "FollowCamera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TSubclassOf<AFollowCameraActor> FollowCameraClass;

	/** Reference to the spawned player follow camera. */
	UPROPERTY(Category = "FollowCamera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TObjectPtr<AFollowCameraActor> FollowCamera;

	/** Store a reference for Cube Player Controller at begin play for future use */
	UPROPERTY(Category = "Controller", VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACubeController> PlayerControllerRef;
	
public:
	/** Returns Follow Camera */
	FORCEINLINE TObjectPtr<AFollowCameraActor> GetFollowCameraActor() const { return FollowCamera;}

protected:	
	// Interface to handle movement input 
	UFUNCTION(Category = "CubeControllerInterface", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Move"))
	void HandleInputMove(const FInputActionValue& ActionValue);
	virtual void HandleInputMove_Implementation(const FInputActionValue& ActionValue) override;

protected:
	// Interface to handle look input
	UFUNCTION(Category = "CubeControllerInterface", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Look"))
	void HandleInputLook(const FInputActionValue& ActionValue);
	virtual void HandleInputLook_Implementation(const FInputActionValue& ActionValue) override;
};

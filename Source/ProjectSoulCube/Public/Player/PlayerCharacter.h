// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/CubeControllerInterface.h"
#include "PlayerCharacter.generated.h"

class ACubeController;
class AFollowCameraActor;

UCLASS()
class PROJECTSOULCUBE_API APlayerCharacter : public ACharacter, public ICubeControllerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

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

	/**
	 * Initial offset value for the camera to spawn at.
	 *  @note It is just used at spawn and is very minimal, the actual offset should be set in the camera class.
	 */
	static FVector SpawnCameraOffset;
	
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

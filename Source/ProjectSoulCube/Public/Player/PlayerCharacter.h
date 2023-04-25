// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/CubeControllerInterface.h"
#include "Interface/InventoryInterface.h"
#include "PlayerCharacter.generated.h"

struct FOnAttributeChangeData;
class UInputAction;

UCLASS()
class PROJECTSOULCUBE_API APlayerCharacter : public ACharacter, public ICubeControllerInterface, public IAbilitySystemInterface, public IInventoryInterface
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/**
	 * Initial offset value for the camera to spawn at.
	 *  @note It is just used at spawn and is very minimal, the actual offset should be set in the camera class.
	 */
	static FVector SpawnCameraOffset;
	
	UPROPERTY(Category = "Debug", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDebug;
	
	/** Should we use custom follow camera implementation or a spring arm camera . */
	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;
	
	/** Should we use custom follow camera implementation or a spring arm camera . */
	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;
	
	/** Should we use custom follow camera implementation or a spring arm camera . */
	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bUseCustomFollowCamera = false;

	/** Class of the player follow camera that should be spawned. */
	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AFollowCameraActor> FollowCameraClass;

	/** Reference to the spawned player follow camera. */
	UPROPERTY(Category = "Camera", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", DisplayPriority = -3))
	TObjectPtr<class AFollowCameraActor> FollowCamera;

	/** Store a reference for Cube Player Controller at begin play for future use */
	UPROPERTY(Category = "Controller", VisibleDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACubeController> PlayerControllerRef;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionItemPickUp;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionItemUse;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionInventory;
	

protected:

	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInteractionDetectionComponent> InteractionDetectionComponent;

	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInventorySystemComponent> InventorySystemComponent;
	
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USCAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UScPlayerAttributeSet> PlayerAttributeSet;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class USCGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TArray<TSubclassOf<class USCGameplayEffect>> StartupEffects;

	// Default abilities for this Character. These will be removed on Character death and re-given if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TArray<TSubclassOf<class USCGameplayAbility>> CharacterAbilities;
	
protected:

	FDelegateHandle HealthChangedDelegateHandle;

	
public:
	
	/** Returns Follow Camera */
	FORCEINLINE TObjectPtr<AFollowCameraActor> GetFollowCameraActor() const { return FollowCamera;}

protected:

	virtual void InitializeCustomCamera();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void AddCharacterAbilities();
	
	// Interface to handle movement input 
	UFUNCTION(Category = "CubeControllerInterface", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Move"))
	void HandleInputMove(const FInputActionValue& ActionValue);
	virtual void HandleInputMove_Implementation(const FInputActionValue& ActionValue) override;

	// Interface to handle look input
	UFUNCTION(Category = "CubeControllerInterface", BlueprintNativeEvent, BlueprintCallable, meta = (DisplayName = "Handle Look"))
	void HandleInputLook(const FInputActionValue& ActionValue);
	virtual void HandleInputLook_Implementation(const FInputActionValue& ActionValue) override;

protected:
	
	virtual void PossessedBy(AController* NewController) override;

	// Called to handle input for Item Pickup 
	void HandleItemPickup(const FInputActionValue& ActionValue);

	// Called to handle input for Item Usage 
	void HandleItemUse(const FInputActionValue& ActionValue);

	// Called to handle Inventory
	void HandleInventory(const FInputActionValue& ActionValue);

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	
public:

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UInventorySystemComponent* GetInventorySystemComponent_Implementation() override;
	//~ End IAbilitySystemInterface

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealthRegenRate() const;

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetShield() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetMaxShield() const;
	
public:

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/

	virtual void SetHealth(float Health);
	
	virtual void SetStamina(float Stamina);

	virtual void SetShield(float Shield);
    	
};

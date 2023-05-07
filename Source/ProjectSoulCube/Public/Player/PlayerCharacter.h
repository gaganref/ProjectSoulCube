// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Interface/CubeControllerInterface.h"
#include "Interface/InventoryInterface.h"
#include "Interface/PlayerStatsInterface.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPauseMenuPressed);

enum class ESCAbilityInputID : uint8;
struct FOnAttributeChangeData;
class UInputAction;

UCLASS()
class PROJECTSOULCUBE_API APlayerCharacter : public ACharacter, public ICubeControllerInterface, public IAbilitySystemInterface, public IInventoryInterface, public IPlayerStatsInterface
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> ShieldFx;
	
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

	UPROPERTY(Category = "FX", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bCanShowShieldFx = false;
	
	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionItemPickUp;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionItemUse;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionInventory;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionSprint;

	UPROPERTY(Category = "Input", EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputAction> InputActionPauseMenu;

protected:

	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1", ClampMax = "5"))
	float PlayerSprintSpeedMultiplier = 2.9f;

	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInteractionDetectionComponent> InteractionDetectionComponent;

	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class UInventorySystemComponent> InventorySystemComponent;
	
	/** Ability System Component. Required to use Gameplay Attributes and Gameplay Abilities. */
	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USCAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<class UScPlayerAttributeSet> PlayerAttributeSet;

	UPROPERTY()
	bool AscInputBound = false;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(Category = "Ability System", EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class USCGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TArray<TSubclassOf<class USCGameplayEffect>> StartupEffects;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	TSubclassOf<class USCGameplayAbility> SprintAbilityClass;
	
	// // Default abilities for this Character. These will be removed on Character death and re-given if Character respawns.
	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System")
	// TArray<TSubclassOf<class USCGameplayAbility>> CharacterAbilities;

protected:
	FGameplayTag DeadTag;

	FOnPauseMenuPressed PauseMenuPressedDelegate;
	
protected:

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle ShieldChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxInventorySizeChangedDelegateHandle;

	FPlayerHealthChanged PlayerHealthChangedDelegate;
	FPlayerShieldChanged PlayerShieldChangedDelegate;
	FPlayerStaminaChanged PlayerStaminaChangedDelegate;

	
public:
	
	FOnPauseMenuPressed* GetPauseMenuPressedDelegate() { return &PauseMenuPressedDelegate; }
	
	/** Returns Follow Camera */
	FORCEINLINE TObjectPtr<AFollowCameraActor> GetFollowCameraActor() const { return FollowCamera;}

	virtual FPlayerHealthChanged* GetPlayerHealthChangedDelegate() override;
	virtual FPlayerShieldChanged* GetPlayerShieldChangedDelegate() override;
	virtual FPlayerStaminaChanged* GetPlayerStaminaChangedDelegate() override;

protected:

	virtual void InitializeCustomCamera();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void AddCharacterAbilities();

	virtual void RemoveCharacterAbilities();

	virtual void SendAbilityLocalInput(const FInputActionValue& InActionValue, const TSubclassOf<USCGameplayAbility> InAbilityClass, const ESCAbilityInputID InInputId);
	
	// Interface to handle movement input 
	virtual void HandleInputMove_Implementation(const FInputActionValue& ActionValue) override;

	// Interface to handle look input
	virtual void HandleInputLook_Implementation(const FInputActionValue& ActionValue) override;

protected:

	virtual void BeginDie();
	
	virtual void PossessedBy(AController* NewController) override;

	// Called to handle input for Item Pickup 
	void HandleItemPickup(const FInputActionValue& ActionValue);

	// Called to handle input for Item Usage 
	void HandleItemUse(const FInputActionValue& ActionValue);

	// Called to handle Inventory
	void HandleInventory(const FInputActionValue& ActionValue);

	void HandleSprint(const FInputActionValue& ActionValue);

	void HandlePauseMenu(const FInputActionValue& ActionValue);

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);

	virtual void OnShieldChanged(const FOnAttributeChangeData& Data);

	virtual void OnStaminaChanged(const FOnAttributeChangeData& Data);

	virtual void OnMaxInventorySizeChanged(const FOnAttributeChangeData& Data);
	
	UFUNCTION(BlueprintCallable)
	virtual void StartSprinting();

	UFUNCTION(BlueprintCallable)
	virtual void StopSprinting();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Die();
	
public:

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UInventorySystemComponent* GetInventorySystemComponent_Implementation() override;

	virtual bool IsOwnerAlive_Implementation() override;
	//~ End IAbilitySystemInterface

	virtual float GetHealth() const override;
	
	virtual float GetMaxHealth() const override;
	
	virtual float GetHealthRegenRate() const override;
	
	virtual bool IsAlive() const override;

	virtual int32 GetAbilityLevel(ESCAbilityInputID AbilityID) const;
	
	virtual float GetStamina() const override;
	
	virtual float GetMaxStamina() const override;
	
	virtual float GetShield() const override;
	
	virtual float GetMaxShield() const override;

	virtual float GetMoveSpeed() const override;
	
	virtual float GetMaxInventorySize() const override;

	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/

	virtual void SetHealth(float Health);
	
	virtual void SetStamina(float Stamina);

	virtual void SetShield(float Shield);
    	
};

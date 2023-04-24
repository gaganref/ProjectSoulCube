// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "DebugLibraryCommon.h"
#include "EnhancedInputComponent.h"
#include "Camera/FollowCameraActor.h"
#include "Controller/CubeController.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Components/InteractionDetectionComponent.h"
#include "Components/InventorySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/SCAbilitySystemComponent.h"
#include "GAS/Abilities/SCGameplayAbility.h"
#include "GAS/Abilities/AttributeSets/SCHealthAttributeSet.h"
#include "GAS/GameplayEffects/SCGameplayEffect.h"
#include "Player/SCPlayerState.h"
#include "ProjectSoulCube/ProjectSoulCube.h"

FVector APlayerCharacter::SpawnCameraOffset(FVector(-120.0f, 50.0f, 45.0f));

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->SocketOffset = SpawnCameraOffset;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);

	InteractionDetectionComponent = CreateDefaultSubobject<UInteractionDetectionComponent>(TEXT("Interaction Detection Component"));
	InventorySystemComponent = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory Sysytem Component"));
	
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>(TEXT("Ability System Component"));
	HealthAttributeSet = CreateDefaultSubobject<USCHealthAttributeSet>(TEXT("Health Attribute Set"));
	
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 77.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera. Except Yaw
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCustomCamera();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(InputActionItemPickUp, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleItemPickup);
		EnhancedInputComponent->BindAction(InputActionItemUse, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleItemUse);
		EnhancedInputComponent->BindAction(InputActionInventory, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleInventory);
	}
}

void APlayerCharacter::InitializeCustomCamera()
{
	const TObjectPtr<UWorld> World = GetWorld();
	check(World);
	
	PlayerControllerRef = Cast<ACubeController>(GetController());

	if(bUseCustomFollowCamera)
	{
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
			if(bDebug)
			{
				DEBUG_PRINT_CUSTOM_TEXT_WITH_INFO(TEXT("PlayerControllerRef is not valid."));
			}
		}
	}	
}

void APlayerCharacter::HandleInputMove_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputMove_Implementation(ActionValue);

	// input is a Vector2D
	const FVector2D MovementVector = ActionValue.Get<FVector2D>();

	if (PlayerControllerRef != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = PlayerControllerRef->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::HandleInputLook_Implementation(const FInputActionValue& ActionValue)
{
	ICubeControllerInterface::HandleInputLook_Implementation(ActionValue);

	// input is a Vector2D
	const FVector2D LookAxisVector = ActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::HandleItemPickup(const FInputActionValue& ActionValue)
{
	InteractionDetectionComponent->OnItemPickupButtonPressed(ActionValue);
}

void APlayerCharacter::HandleItemUse(const FInputActionValue& ActionValue)
{
	InteractionDetectionComponent->OnItemUseButtonPressed(ActionValue);
}

void APlayerCharacter::HandleInventory(const FInputActionValue& ActionValue)
{
	InventorySystemComponent->ToggleInventory();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		// Set Health to their max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
		
		InitializeAttributes();

		AddStartupEffects();

		AddCharacterAbilities();
	}
	
	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	SetOwner(NewController);
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogSoulCubeGAS, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1/*GetCharacterLevel()*/, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void APlayerCharacter::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->AreStartupEffectsApplied())
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<USCGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1/*GetCharacterLevel()*/, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->SetStartupEffectsApplied(true);
}

void APlayerCharacter::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->AreStartupEffectsApplied())
	{
		return;
	}

	// for (TSubclassOf<USCGameplayAbility>& StartupAbility : CharacterAbilities)
	// {
	// 	AbilitySystemComponent->GiveAbility(
	// 		FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	// }

	AbilitySystemComponent->SetCharacterAbilitiesGiven(true);
}

float APlayerCharacter::GetHealth() const
{
	if(HealthAttributeSet)
	{
		return HealthAttributeSet->GetHealth();
	}

	return 0.0f;
}

float APlayerCharacter::GetMaxHealth() const
{
	if(HealthAttributeSet)
	{
		return HealthAttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

float APlayerCharacter::GetHealthRegenRate() const
{
	if(HealthAttributeSet)
	{
		return HealthAttributeSet->GetHealthRegenRate();
	}

	return 0.0f;
}

bool APlayerCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void APlayerCharacter::SetHealth(float Health)
{
	if(HealthAttributeSet)
	{
		HealthAttributeSet->SetHealth(Health);
	}
}

UInventorySystemComponent* APlayerCharacter::GetInventorySystemComponent_Implementation()
{
	return InventorySystemComponent;
}

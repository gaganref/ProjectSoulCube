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
#include "Game/DefaultGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/SCAbilitySystemComponent.h"
#include "GAS/Abilities/SCGameplayAbility.h"
#include "GAS/Abilities/AttributeSets/SCHealthAttributeSet.h"
#include "GAS/Abilities/AttributeSets/ScPlayerAttributeSet.h"
#include "GAS/GameplayEffects/SCGameplayEffect.h"
#include "Kismet/GameplayStatics.h"
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

	ShieldFx = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield Fx"));
	ShieldFx->SetupAttachment(GetCapsuleComponent());
	ShieldFx->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ShieldFx->SetVisibility(bCanShowShieldFx);
	
	InteractionDetectionComponent = CreateDefaultSubobject<UInteractionDetectionComponent>(TEXT("Interaction Detection Component"));
	InventorySystemComponent = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("Inventory Sysytem Component"));
	
	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>(TEXT("Ability System Component"));
	PlayerAttributeSet = CreateDefaultSubobject<UScPlayerAttributeSet>(TEXT("Player Attribute Set"));
	
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 77.0f);
	
	// Don't rotate when the controller rotates. Let that just affect the camera. Except Yaw
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeCustomCamera();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetHealthAttribute()).AddUObject(this, &APlayerCharacter::OnHealthChanged);
		ShieldChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetShieldAttribute()).AddUObject(this, &APlayerCharacter::OnShieldChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetStaminaAttribute()).AddUObject(this, &APlayerCharacter::OnStaminaChanged);
		MaxInventorySizeChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetMaxInventorySizeAttribute()).AddUObject(this, &APlayerCharacter::OnMaxInventorySizeChanged);
	}

	if(InventorySystemComponent)
	{
		InventorySystemComponent->GetPickItemDelegate()->AddUniqueDynamic(this, &APlayerCharacter::HandleItemPickAudio);
		InventorySystemComponent->GetDropItemDelegate()->AddUniqueDynamic(this, &APlayerCharacter::HandleItemDropAudio);
	}
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
		if(InputActionItemPickUp && ensure(InputActionItemPickUp->ValueType == EInputActionValueType::Boolean))
		{
			EnhancedInputComponent->BindAction(InputActionItemPickUp, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleItemPickup);
		}
		if(InputActionItemUse && ensure(InputActionItemUse->ValueType == EInputActionValueType::Boolean))
		{
			EnhancedInputComponent->BindAction(InputActionItemUse, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleItemUse);
		}
		if(InputActionInventory && ensure(InputActionInventory->ValueType == EInputActionValueType::Boolean))
		{
			EnhancedInputComponent->BindAction(InputActionInventory, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleInventory);
		}
		if(InputActionSprint && ensure(InputActionSprint->ValueType == EInputActionValueType::Boolean))
		{
			EnhancedInputComponent->BindAction(InputActionSprint, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleSprint);
		}
		if(InputActionPauseMenu && ensure(InputActionPauseMenu->ValueType == EInputActionValueType::Boolean))
		{
			EnhancedInputComponent->BindAction(InputActionPauseMenu, ETriggerEvent::Triggered, this, &APlayerCharacter::HandlePauseMenu);
		}
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
	
	//TODO: Use Different Method
	if(!InventorySystemComponent->GetIsInventoryOpen())
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(ESCAbilityInputID::Sprint));	
	}
}

void APlayerCharacter::HandleSprint(const FInputActionValue& ActionValue)
{
	SendAbilityLocalInput(ActionValue, SprintAbilityClass, ESCAbilityInputID::Sprint);
}

void APlayerCharacter::HandlePauseMenu(const FInputActionValue& ActionValue)
{
	if(PauseMenuPressedDelegate.IsBound())
	{
		PauseMenuPressedDelegate.Broadcast();
	}
}

void APlayerCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if(PlayerHealthChangedDelegate.IsBound())
	{
		PlayerHealthChangedDelegate.Broadcast(Data.NewValue);
	}
	
	// If the player died, handle death
	if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		BeginDie();
	}
}

void APlayerCharacter::OnShieldChanged(const FOnAttributeChangeData& Data)
{
	if(bCanShowShieldFx)
	{
		if(Data.NewValue <= 0.0f)
		{
			if(ShieldFx->GetVisibleFlag())
			{
				ShieldFx->SetVisibility(false);	
			}
		}
		else
		{
			if(!ShieldFx->GetVisibleFlag())
			{
				ShieldFx->SetVisibility(true);	
			}
		}
	}
	
	if(PlayerShieldChangedDelegate.IsBound())
	{
		PlayerShieldChangedDelegate.Broadcast(Data.NewValue);
	}
}

void APlayerCharacter::OnStaminaChanged(const FOnAttributeChangeData& Data)
{
	if(PlayerStaminaChangedDelegate.IsBound())
	{
		PlayerStaminaChangedDelegate.Broadcast(Data.NewValue);
	}
}

void APlayerCharacter::OnMaxInventorySizeChanged(const FOnAttributeChangeData& Data)
{
	if(InventorySystemComponent)
	{
		InventorySystemComponent->SetMaxInventorySize(Data.NewValue);
	}
}

void APlayerCharacter::HandleItemDropAudio()
{
	if(ItemDropSound)
	{
		if(GetWorld())
		{
			UGameplayStatics::PlaySoundAtLocation(this, ItemDropSound, GetActorLocation(), ItemDropVolumeMultiplier, ItemDropPitchMultiplier);	
		}
	}
}

void APlayerCharacter::HandleItemPickAudio()
{
	if(ItemPickSound)
	{
		if(GetWorld())
		{
			UGameplayStatics::PlaySoundAtLocation(this, ItemPickSound, GetActorLocation(), ItemPickVolumeMultiplier, ItemPickPitchMultiplier);	
		}
	}
}

void APlayerCharacter::StartSprinting()
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed() * PlayerSprintSpeedMultiplier;
	}
}

void APlayerCharacter::StopSprinting()
{
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	}
}

void APlayerCharacter::BeginDie()
{
	// TODO: Handle death
	RemoveCharacterAbilities();
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);
	
	// OnCharacterDied.Broadcast(this);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	TObjectPtr<ADefaultGameMode> GameModeRef = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this));
	if(GameModeRef)
	{
		GameModeRef->BeginGameLost();
	}

	Die();
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		
		InitializeAttributes();

		AddStartupEffects();

		AddCharacterAbilities();

		// Set Health to their max. This is only necessary for *Respawn*.
		SetHealth(GetMaxHealth());
		SetShield(GetMaxShield());
		SetStamina(GetMaxStamina());

		if(GetCharacterMovement())
		{
			GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
		}
		if(InventorySystemComponent)
		{
			InventorySystemComponent->SetInventorySize(0);
			InventorySystemComponent->SetMaxInventorySize(GetMaxInventorySize());
		}
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
	if (!AbilitySystemComponent || AbilitySystemComponent->AreCharacterAbilitiesGiven())
	{
		return;
	}

	AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec
			(
				SprintAbilityClass,
				GetAbilityLevel(SprintAbilityClass.GetDefaultObject()->AbilityID),
				static_cast<int32>(SprintAbilityClass.GetDefaultObject()->AbilityInputID),
				this
			)
	);
	
	AbilitySystemComponent->SetCharacterAbilitiesGiven(true);
}

void APlayerCharacter::RemoveCharacterAbilities()
{
	if (!AbilitySystemComponent || !AbilitySystemComponent->AreCharacterAbilitiesGiven())
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;

	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && Spec.Ability->GetClass() == SprintAbilityClass)
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
	
	AbilitySystemComponent->SetCharacterAbilitiesGiven(false);
}

void APlayerCharacter::SendAbilityLocalInput(const FInputActionValue& InActionValue, const TSubclassOf<USCGameplayAbility> InAbilityClass, const ESCAbilityInputID InInputId)
{
	if(!AbilitySystemComponent || !InAbilityClass)
	{
		return;
	}
	if(InActionValue.GetValueType() != EInputActionValueType::Boolean)
	{
		return;
	}

	if(InActionValue.Get<bool>())
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(InInputId));
	}
	else
	{
		AbilitySystemComponent->AbilityLocalInputReleased(static_cast<int32>(InInputId));
	}
}

float APlayerCharacter::GetHealth() const
{
	if(PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetHealth();
	}

	return 0.0f;
}

float APlayerCharacter::GetMaxHealth() const
{
	if(PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

float APlayerCharacter::GetHealthRegenRate() const
{
	if(PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetHealthRegenRate();
	}

	return 0.0f;
}

float APlayerCharacter::GetStamina() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetStamina();
	}

	return 0.0f;
}

float APlayerCharacter::GetMaxStamina() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetMaxStamina();
	}

	return 0.0f;
}

float APlayerCharacter::GetShield() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetShield();
	}

	return 0.0f;
}

float APlayerCharacter::GetMaxShield() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetMaxShield();
	}

	return 0.0f;
}

float APlayerCharacter::GetMoveSpeed() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetMoveSpeed();
	}

	return 0.0f;
}

float APlayerCharacter::GetMaxInventorySize() const
{
	if (IsValid(PlayerAttributeSet))
	{
		return PlayerAttributeSet->GetMaxInventorySize();
	}

	return 0.0f;
}

bool APlayerCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 APlayerCharacter::GetAbilityLevel(ESCAbilityInputID AbilityID) const
{
	return 1;
}

void APlayerCharacter::SetHealth(float Health)
{
	if(PlayerAttributeSet)
	{
		PlayerAttributeSet->SetHealth(Health);
	}
}

void APlayerCharacter::SetStamina(float Stamina)
{
	if (IsValid(PlayerAttributeSet))
	{
		PlayerAttributeSet->SetStamina(Stamina);
	}
}

void APlayerCharacter::SetShield(float Shield)
{
	if (IsValid(PlayerAttributeSet))
	{
		PlayerAttributeSet->SetShield(Shield);
	}
}

UInventorySystemComponent* APlayerCharacter::GetInventorySystemComponent_Implementation()
{
	return InventorySystemComponent;
}

bool APlayerCharacter::IsOwnerAlive_Implementation()
{
	return IsAlive();
}

FPlayerHealthChanged* APlayerCharacter::GetPlayerHealthChangedDelegate()
{
	return &PlayerHealthChangedDelegate;
}

FPlayerShieldChanged* APlayerCharacter::GetPlayerShieldChangedDelegate()
{
	return &PlayerShieldChangedDelegate;
}

FPlayerStaminaChanged* APlayerCharacter::GetPlayerStaminaChangedDelegate()
{
	return &PlayerStaminaChangedDelegate;
}

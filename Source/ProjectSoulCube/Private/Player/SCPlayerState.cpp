// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "Player/SCPlayerState.h"
//
// #include "GAS/SCAbilitySystemComponent.h"
// #include "GAS/Abilities/AttributeSets/SCHealthAttributeSet.h"
//
//
// // Sets default values
// ASCPlayerState::ASCPlayerState()
// {
// 	// Create ability system component, and set it to be explicitly replicated
// 	AbilitySystemComponent = CreateDefaultSubobject<USCAbilitySystemComponent>(TEXT("Ability System Component"));
// 	AbilitySystemComponent->SetIsReplicated(true);
// 	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
// 	
// 	HealthAttributeSet = CreateDefaultSubobject<USCHealthAttributeSet>(TEXT("Health Attributes"));
//
// 	// Set PlayerState's NetUpdateFrequency to the same as the Character.
// 	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
// 	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
// 	NetUpdateFrequency = 100.0f;
// }
//
// // Called when the game starts or when spawned
// void ASCPlayerState::BeginPlay()
// {
// 	Super::BeginPlay();
//
// 	if (AbilitySystemComponent)
// 	{
// 		// Attribute change callbacks
// 		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthAttribute()).AddUObject(this, &ASCPlayerState::HealthChanged);
// 		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ASCPlayerState::MaxHealthChanged);
// 		HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthRegenRateAttribute()).AddUObject(this, &ASCPlayerState::HealthRegenRateChanged);
// 	}
// }
//
// // Called every frame
// void ASCPlayerState::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }
//
// UAbilitySystemComponent* ASCPlayerState::GetAbilitySystemComponent() const
// {
// 	return AbilitySystemComponent;
// }
//
// USCHealthAttributeSet* ASCPlayerState::GetHealthAttributeSet() const
// {
// 	return HealthAttributeSet;
// }
//
// bool ASCPlayerState::IsAlive() const
// {
// 	return GetHealth() > 0.0f;
// }
//
// float ASCPlayerState::GetHealth() const
// {
// 	return HealthAttributeSet->GetHealth();
// }
//
// float ASCPlayerState::GetMaxHealth() const
// {
// 	return HealthAttributeSet->GetMaxHealth();	
// }
//
// float ASCPlayerState::GetHealthRegenRate() const
// {
// 	return HealthAttributeSet->GetHealthRegenRate();	
// }
//
// void ASCPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
// {
// }
//
// void ASCPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
// {
// }
//
// void ASCPlayerState::HealthRegenRateChanged(const FOnAttributeChangeData& Data)
// {
// }

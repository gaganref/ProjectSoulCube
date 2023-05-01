// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ScPlayerAttributeSet.generated.h"

// Referred from https://github.com/tranek/GASDocumentation

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UScPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UScPlayerAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, HealthRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, Stamina)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Stamina")
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, StaminaRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, Shield)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, MaxShield)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData ShieldRegenRate;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, ShieldRegenRate)
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, MoveSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Invnetory Size")
	FGameplayAttributeData MaxInventorySize;
	ATTRIBUTE_ACCESSORS(UScPlayerAttributeSet, MaxInventorySize)
	
public:

	// AttributeSet Overrides
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;
};

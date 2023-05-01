// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Misc/Common.h"
#include "SCGameplayAbility.generated.h"

enum class ESCAbilityInputID : uint8;
/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API USCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	USCGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ESCAbilityInputID AbilityInputID = ESCAbilityInputID::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ESCAbilityInputID AbilityID = ESCAbilityInputID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/AttributeSets/SCHealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

USCHealthAttributeSet::USCHealthAttributeSet()
{
}

void USCHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void USCHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// TODO:
	// FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	// UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	// const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	// FGameplayTagContainer SpecAssetTags;
	// Data.EffectSpec.GetAllAssetTags(SpecAssetTags);
	//
	// // Get the Target actor, which should be our owner
	// AActor* TargetActor = nullptr;
	// AController* TargetController = nullptr;
	// AGDCharacterBase* TargetCharacter = nullptr;
	// if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	// {
	// 	TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	// 	TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	// 	TargetCharacter = Cast<AGDCharacterBase>(TargetActor);
	// }
	//
	// // Get the Source actor
	// AActor* SourceActor = nullptr;
	// AController* SourceController = nullptr;
	// AGDCharacterBase* SourceCharacter = nullptr;
	// if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	// {
	// 	SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
	// 	SourceController = Source->AbilityActorInfo->PlayerController.Get();
	// 	if (SourceController == nullptr && SourceActor != nullptr)
	// 	{
	// 		if (APawn* Pawn = Cast<APawn>(SourceActor))
	// 		{
	// 			SourceController = Pawn->GetController();
	// 		}
	// 	}
	//
	// 	// Use the controller to find the source pawn
	// 	if (SourceController)
	// 	{
	// 		SourceCharacter = Cast<AGDCharacterBase>(SourceController->GetPawn());
	// 	}
	// 	else
	// 	{
	// 		SourceCharacter = Cast<AGDCharacterBase>(SourceActor);
	// 	}
	//
	// 	// Set the causer actor based on context if it's set
	// 	if (Context.GetEffectCauser())
	// 	{
	// 		SourceActor = Context.GetEffectCauser();
	// 	}
	// }

	// Damage
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// TODO:
	}// Health
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes.
		// Health loss should go through Damage.
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}


void USCHealthAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
                                                        const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		const float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}
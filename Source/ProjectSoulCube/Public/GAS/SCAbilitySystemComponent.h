// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SCAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTSOULCUBE_API USCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USCAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	bool bCharacterAbilitiesGiven = false;

	UPROPERTY()
	bool bStartupEffectsApplied = false;


public:

	FORCEINLINE bool AreCharacterAbilitiesGiven() const {return bCharacterAbilitiesGiven;}
	
	FORCEINLINE bool AreStartupEffectsApplied() const {return bStartupEffectsApplied;}

	FORCEINLINE void SetCharacterAbilitiesGiven(const bool InValue) {bCharacterAbilitiesGiven = InValue;}
	
	FORCEINLINE void SetStartupEffectsApplied(const bool InValue) {bStartupEffectsApplied = InValue;}
};

﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerStatsInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerShieldChanged, float, NewShield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerStaminaChanged, float, NewStamina);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerHealthDamaged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerShieldDamaged);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerStatsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTSOULCUBE_API IPlayerStatsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetHealth() const = 0;

	virtual float GetMaxHealth() const = 0;

	virtual float GetHealthRegenRate() const = 0;

	virtual bool IsAlive() const = 0;

	virtual float GetStamina() const = 0;

	virtual float GetMaxStamina() const = 0;

	virtual float GetShield() const = 0;

	virtual float GetMaxShield() const = 0;

	virtual float GetMoveSpeed() const = 0;

	virtual float GetMaxInventorySize() const = 0;

	virtual FPlayerHealthChanged* GetPlayerHealthChangedDelegate() = 0;

	virtual FPlayerShieldChanged* GetPlayerShieldChangedDelegate() = 0;

	virtual FPlayerStaminaChanged* GetPlayerStaminaChangedDelegate() = 0;
	
	virtual FPlayerHealthDamaged* GetPlayerHealthDamagedDelegate() = 0;

	virtual FPlayerShieldDamaged* GetPlayerShieldDamagedDelegate() = 0;
};

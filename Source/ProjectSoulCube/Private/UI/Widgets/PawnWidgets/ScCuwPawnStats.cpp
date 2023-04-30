// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwPawnStats.h"

#include "Interface/PlayerStatsInterface.h"
#include "UI/Widgets/DataWidgets/ScCuwProgressBarWithLabel.h"


void UScCuwPawnStats::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UScCuwPawnStats::OnInit_Implementation(AController* Controller)
{
	if(!Controller)
	{
		return;
	}
	
	if(Controller->GetPawn())
	{
		IPlayerStatsInterface* PlayerStatsInterface = Cast<IPlayerStatsInterface>(Controller->GetPawn());

		if(PlayerStatsInterface)
		{
			PlayerStatsInterface->GetPlayerHealthChangedDelegate()->AddUniqueDynamic(this, &UScCuwPawnStats::HandleHealthChange);
			PlayerStatsInterface->GetPlayerShieldChangedDelegate()->AddUniqueDynamic(this, &UScCuwPawnStats::HandleShieldChange);
			PlayerStatsInterface->GetPlayerStaminaChangedDelegate()->AddUniqueDynamic(this, &UScCuwPawnStats::HandleStaminaChange);

			HealthBar->SetValue(PlayerStatsInterface->GetHealth());
			HealthBar->SetMaxValue(PlayerStatsInterface->GetMaxHealth());
			HealthBar->UpdateFillPercentage();

			ShieldBar->SetValue(PlayerStatsInterface->GetShield());
			ShieldBar->SetMaxValue(PlayerStatsInterface->GetMaxShield());
			ShieldBar->UpdateFillPercentage();

			StaminaBar->SetValue(PlayerStatsInterface->GetShield());
			StaminaBar->SetMaxValue(PlayerStatsInterface->GetMaxStamina());
			StaminaBar->UpdateFillPercentage();
		}
	}
}

void UScCuwPawnStats::HandleHealthChange(float NewHealth)
{
	HealthBar->SetValue(NewHealth);
	HealthBar->UpdateFillPercentage();
}

void UScCuwPawnStats::HandleShieldChange(float NewShield)
{
	ShieldBar->SetValue(NewShield);
	ShieldBar->UpdateFillPercentage();
}

void UScCuwPawnStats::HandleStaminaChange(float NewStamina)
{
	StaminaBar->SetValue(NewStamina);
	StaminaBar->UpdateFillPercentage();
}

UScCuwProgressBarWithLabel* UScCuwPawnStats::GetHealthBar() const
{
	return HealthBar;
}

UScCuwProgressBarWithLabel* UScCuwPawnStats::GetShieldBar() const
{
	return ShieldBar;
}

UScCuwProgressBarWithLabel* UScCuwPawnStats::GetStaminaBar() const
{
	return StaminaBar;
}
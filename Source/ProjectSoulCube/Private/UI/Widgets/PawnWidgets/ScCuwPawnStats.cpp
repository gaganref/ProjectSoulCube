// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwPawnStats.h"


void UScCuwPawnStats::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UScCuwPawnStats::OnInit_Implementation(AController* Controller)
{
}

UScCuwProgressBarWithLabel* UScCuwPawnStats::GetHealthBar() const
{
	return HealthBar;
}

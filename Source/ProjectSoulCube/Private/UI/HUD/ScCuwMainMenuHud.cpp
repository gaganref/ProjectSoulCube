// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ScCuwMainMenuHud.h"

#include "UI/Widgets/Buttons/ScCuwTextButton.h"

void UScCuwMainMenuHud::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UScCuwMainMenuHud::NativeConstruct()
{
	Super::NativeConstruct();

	if(StartButton)
	{
		StartButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwMainMenuHud::HandleStartButtonPressed);
	}
	if(QuitButton)
	{
		QuitButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwMainMenuHud::HandleQuitButtonPressed);
	}
}

void UScCuwMainMenuHud::OnInit_Implementation(AController* Controller)
{
	
}

void UScCuwMainMenuHud::HandleStartButtonPressed()
{
	if(StartButtonPressedDelegate.IsBound())
	{
		StartButtonPressedDelegate.Broadcast();
	}
}

void UScCuwMainMenuHud::HandleQuitButtonPressed()
{
	if(QuitButtonPressedDelegate.IsBound())
	{
		QuitButtonPressedDelegate.Broadcast();
	}
}

UScCuwTextButton* UScCuwMainMenuHud::GetStartButton() const
{
	return StartButton;
}

UScCuwTextButton* UScCuwMainMenuHud::GetQuitButton() const
{
	return QuitButton;
}

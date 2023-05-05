// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/PauseMenuWidget.h"

#include "UI/Widgets/Buttons/ScCuwTextButton.h"

void UPauseMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ResumeButton)
	{
		ResumeButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UPauseMenuWidget::HandleResumeButtonPressed);
	}
	if(MainMenuButton)
	{
		MainMenuButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UPauseMenuWidget::HandleMainMenuButtonPressed);
	}
	if(RestartButton)
	{
		RestartButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UPauseMenuWidget::HandleRestartButtonPressed);
	}
}

void UPauseMenuWidget::HandleResumeButtonPressed()
{
	if(ResumeButtonPressedDelegate.IsBound())
	{
		ResumeButtonPressedDelegate.Broadcast();
	}
}

void UPauseMenuWidget::HandleMainMenuButtonPressed()
{
	if(MainMenuButtonPressedDelegate.IsBound())
	{
		MainMenuButtonPressedDelegate.Broadcast();
	}
}

void UPauseMenuWidget::HandleRestartButtonPressed()
{
	if(RestartButtonPressedDelegate.IsBound())
	{
		RestartButtonPressedDelegate.Broadcast();
	}
}

void UPauseMenuWidget::OnInit_Implementation(AController* Controller)
{
}

UScCuwTextButton* UPauseMenuWidget::GetRestartButton() const
{
	return RestartButton;
}

UScCuwTextButton* UPauseMenuWidget::GetResumeButton() const
{
	return ResumeButton;
}

UScCuwTextButton* UPauseMenuWidget::GetMainMenuButton() const
{
	return MainMenuButton;
}

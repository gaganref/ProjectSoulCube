// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GameWinMenu.h"

void UGameWinMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGameWinMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);
}

void UGameWinMenu::OnInit_Implementation(AController* Controller)
{
}

UScCuwTextButton* UGameWinMenu::GetRetryButton() const
{
	return RetryButton;
}

UScCuwTextButton* UGameWinMenu::GetReturnToMainMenuButton() const
{
	return ReturnToMainMenuButton;
}

UScCuwTextButton* UGameWinMenu::GetNextLevelButton() const
{
	return NextLevelButton;
}

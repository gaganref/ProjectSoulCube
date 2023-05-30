// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GameWinMenu.h"

#include "Components/TextBlock.h"

void UGameWinMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGameWinMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetWinHeaderText(FText::FromString("You Won the Level"));
	SetVisibility(ESlateVisibility::Collapsed);
}

void UGameWinMenu::OnInit_Implementation(AController* Controller)
{
}

void UGameWinMenu::SetWinHeaderText(const FText& InText)
{
	if(WinText)
	{
		WinText->SetText(InText);
	}
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

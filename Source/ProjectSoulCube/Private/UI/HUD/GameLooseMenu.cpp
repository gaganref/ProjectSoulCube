// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/GameLooseMenu.h"

#include "Components/HorizontalBox.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"

void UGameLooseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UGameLooseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Collapsed);
	
}

void UGameLooseMenu::OnInit_Implementation(AController* Controller)
{
}

UScCuwTextButton* UGameLooseMenu::GetRetryButton() const
{
	return RetryButton;
}

UScCuwTextButton* UGameLooseMenu::GetReturnToMainMenuButton() const
{
	return ReturnToMainMenuButton;
}

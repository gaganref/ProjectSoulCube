// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SCHUDMainMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/ScCuwMainMenuHud.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"


// Sets default values
ASCHUDMainMenu::ASCHUDMainMenu()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASCHUDMainMenu::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCHUDMainMenu::OnInit_Implementation()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if(PlayerController && HudWidgetClass)
	{
		HudWidget = CreateWidget<UScCuwMainMenuHud>(PlayerController, HudWidgetClass);
		if(HudWidget)
		{
			HudWidget->OnInit(PlayerController);
			HudWidget->AddToViewport();

			HudWidget->GetStartButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDMainMenu::HandleStartButtonPressed);
			HudWidget->GetQuitButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDMainMenu::HandleQuitButtonPressed);

			PlayerController->SetShowMouseCursor(true);
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, HudWidget->GetStartButton());
		}
	}
}

void ASCHUDMainMenu::HandleStartButtonPressed()
{
	PlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToOpenOnStart, true);
	// UGameplayStatics::LoadStreamLevelBySoftObjectPtr()
}

void ASCHUDMainMenu::HandleQuitButtonPressed()
{
	PlayerController->SetShowMouseCursor(false);
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}

UScCuwMainMenuHud* ASCHUDMainMenu::GetHudWidget() const
{
	return HudWidget;
}

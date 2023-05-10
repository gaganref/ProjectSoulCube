// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SCHUDGame.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/InventorySystemComponent.h"
#include "Game/DefaultGameMode.h"
#include "Interface/InventoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "UI/HUD/GameLooseMenu.h"
#include "UI/HUD/GameWinMenu.h"
#include "UI/HUD/PauseMenuWidget.h"
#include "UI/HUD/ScCuwGameHud.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"
#include "UI/Widgets/DataWidgets/GameObjectiveWidget.h"

ASCHUDGame::ASCHUDGame()
{
}

void ASCHUDGame::BeginPlay()
{
	Super::BeginPlay();
}

void ASCHUDGame::OnInit_Implementation()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if(PlayerController && HudWidgetClass)
	{
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		
		HudWidget = CreateWidget<UScCuwGameHud>(PlayerController, HudWidgetClass);
		if(HudWidget)
		{
			HudWidget->OnInit(PlayerController);
			HudWidget->AddToViewport();

			HudWidget->GetPauseMenu()->GetMainMenuButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleReturnToMainMenu);
			HudWidget->GetPauseMenu()->GetRestartButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleRestartGame);
			HudWidget->GetPauseMenu()->GetResumeButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleResumeGame);

			HudWidget->GetLooseMenu()->GetRetryButton()->GetButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleRestartGame);
			HudWidget->GetLooseMenu()->GetReturnToMainMenuButton()->GetButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleReturnToMainMenu);
			
			HudWidget->GetWinMenu()->GetRetryButton()->GetButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleRestartGame);
			HudWidget->GetWinMenu()->GetReturnToMainMenuButton()->GetButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleReturnToMainMenu);
			HudWidget->GetWinMenu()->GetNextLevelButton()->GetButtonPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandleNextLevel);
		}
	}
	
	if(PlayerPawn)
	{
		if(PlayerPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			InventoryRef = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerPawn);

			if(InventoryRef)
			{
				InventoryRef->GetInventoryPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::OnInventoryPressed);
			}
		}
		
		if(APlayerCharacter* Pc = Cast<APlayerCharacter>(PlayerPawn))
		{
			Pc->GetPauseMenuPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::HandlePauseGame);
		}
	}

	if(TObjectPtr<ADefaultGameMode> Gm = Cast<ADefaultGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		SetGameObjectiveCurrentData(0);
		SetGameObjectiveTargetData(Gm->GetTargetWeightToWin());
	}
}

void ASCHUDGame::OnInventoryPressed_Implementation(const bool bShouldOpenInventory)
{
	if(!PlayerController)
	{
		return;
	}

	if(bShouldOpenInventory)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, HudWidget);
	}
	else
	{
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}
}


void ASCHUDGame::SetGameObjectiveCurrentData(const int32 NewData)
{
	if(HudWidget)
	{
		if(HudWidget->GetGameObjective())
		{
			HudWidget->GetGameObjective()->SetCurrentWeight(NewData);
		}
	}
}

void ASCHUDGame::SetGameObjectiveTargetData(const int32 NewData)
{
	if(HudWidget)
	{
		if(HudWidget->GetGameObjective())
		{
			HudWidget->GetGameObjective()->SetTargetWeight(NewData);
		}
	}
}

void ASCHUDGame::HandlePauseGame()
{
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
	}

	if(HudWidget)
	{
		if(HudWidget->GetPauseMenu())
		{
			HudWidget->GetPauseMenu()->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	UGameplayStatics::SetGamePaused(this, true);
}

void ASCHUDGame::HandleResumeGame()
{
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
	}

	if(HudWidget)
	{
		if(HudWidget->GetPauseMenu())
		{
			HudWidget->GetPauseMenu()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
	UGameplayStatics::SetGamePaused(this, false);
}

void ASCHUDGame::HandleRestartGame()
{
	FName LevelName = *UGameplayStatics::GetCurrentLevelName(this, true);
	UGameplayStatics::OpenLevel(this, LevelName, true);
}

void ASCHUDGame::HandleNextLevel()
{
	// TODO:
	FName LevelName = *UGameplayStatics::GetCurrentLevelName(this, true);
	int32 LevelIndex = GetLevelIndexByName(LevelName);

	if(LevelIndex >= 0 && LevelIndex < LevelsRef.Num()-1)
	{
		UGameplayStatics::OpenLevel(this, LevelsRef[LevelIndex+1], true);
	}
}

void ASCHUDGame::ShowLooseScreen()
{
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
	}
	
	if(HudWidget)
	{
		HudWidget->ShowLooseScreen();
	}
}

void ASCHUDGame::ShowWinScreen()
{
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
	}
	
	if(HudWidget)
	{
		HudWidget->ShowWinScreen();
	}
}

void ASCHUDGame::HandleReturnToMainMenu()
{
	if(PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController);
	}

	if(!MainMenuLevelRef.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevelRef, true);
	}
}

void ASCHUDGame::ShowItemInfo_Implementation(AActor* InteractableRef)
{
	IInteractableItemHudInterface::ShowItemInfo_Implementation(InteractableRef);

	HudWidget->ShowItemHelp(InteractableRef);
}

void ASCHUDGame::HideItemInfo_Implementation(AActor* InteractableRef)
{
	IInteractableItemHudInterface::HideItemInfo_Implementation(InteractableRef);
	
	HudWidget->HideItemHelp(InteractableRef);
}

int32 ASCHUDGame::GetLevelIndexByName(const FName& InName)
{
	for(int Itr = 0; Itr < LevelsRef.Num(); Itr++)
	{
		if(LevelsRef[Itr] == InName)
		{
			return Itr;
		}
	}
	return -1;
}

UScCuwGameHud* ASCHUDGame::GetHudWidget() const
{
	return HudWidget;
}

APawn* ASCHUDGame::GetPlayerPawn() const
{
	return PlayerPawn;
}

APlayerController* ASCHUDGame::GetPlayerController() const
{
	return PlayerController;
}

UInventorySystemComponent* ASCHUDGame::GetInventoryRef() const
{
	return InventoryRef;
}

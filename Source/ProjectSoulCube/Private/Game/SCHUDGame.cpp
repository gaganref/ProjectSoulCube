// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SCHUDGame.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/InventorySystemComponent.h"
#include "Interface/InventoryInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "UI/HUD/PauseMenuWidget.h"
#include "UI/HUD/ScCuwGameHud.h"
#include "UI/Widgets/PawnWidgets/ScCuwInventoryWidget.h"

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

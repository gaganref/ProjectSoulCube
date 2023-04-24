// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/SCHUDGame.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/InventorySystemComponent.h"
#include "Interface/InventoryInterface.h"
#include "Kismet/GameplayStatics.h"
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
		HudWidget = CreateWidget<UScCuwGameHud>(PlayerController, HudWidgetClass);
		if(HudWidget)
		{
			HudWidget->OnInit(PlayerController);
			HudWidget->AddToViewport();
		}
	}

	if(PlayerPawn)
	{
		if(PlayerPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			InventoryRef = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerPawn);

			if(InventoryRef)
			{
				InventoryRef->GetInventoryPressedDelegate()->AddUniqueDynamic(this, &ASCHUDGame::ASCHUDGame::OnInventoryPressed);
			}
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

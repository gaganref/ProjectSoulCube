// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ScCuwGameHud.h"

#include "Components/InventorySystemComponent.h"
#include "Interface/InventoryInterface.h"
#include "Interface/PlayerStatsInterface.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/GameLooseMenu.h"
#include "UI/HUD/GameWinMenu.h"
#include "UI/HUD/PauseMenuWidget.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"
#include "UI/Widgets/DataWidgets/AlterHelpWidget.h"
#include "UI/Widgets/DataWidgets/ScCuwInteractableItemHelp.h"
#include "UI/Widgets/DataWidgets/ScCuwInventoryItemStats.h"
#include "UI/Widgets/PawnWidgets/ScCuwInventoryWidget.h"
#include "UI/Widgets/PawnWidgets/ScCuwPawnStats.h"

void UScCuwGameHud::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = true;
}

void UScCuwGameHud::NativeConstruct()
{
	Super::NativeConstruct();

	InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
	AlterHelpWidget->SetVisibility(ESlateVisibility::Collapsed);
	SetFocus();
}

void UScCuwGameHud::OnInit_Implementation(AController* Controller)
{
	PlayerStats->OnInit(Controller);
	Inventory->OnInit(Controller);

	if(!Controller)
	{
		return;
	}
	
	TObjectPtr<APawn> PlayerPawn = Controller->GetPawn();
	TObjectPtr<UInventorySystemComponent> InventoryRef;
	if(PlayerPawn)
	{
		if(PlayerPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			InventoryRef = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerPawn);
		}

		IPlayerStatsInterface* PlayerStatsInterface = Cast<IPlayerStatsInterface>(PlayerPawn);

		if(PlayerStatsInterface)
		{
			PlayerStatsInterface->GetPlayerHealthDamagedDelegate()->AddUniqueDynamic(this, &UScCuwGameHud::HandleHealthDamage);
			PlayerStatsInterface->GetPlayerShieldDamagedDelegate()->AddUniqueDynamic(this, &UScCuwGameHud::HandleShieldDamage);
		}
	}

	if(InventoryRef)
	{
		InventoryRef->GetInventoryPressedDelegate()->AddUniqueDynamic(this, &UScCuwGameHud::HandleToggleInventory);
	}
}

void UScCuwGameHud::ShowItemHelp_Implementation(AActor* Item)
{
	bIsItemHelpTextOpen = true;
	InteractableItemHelp->SetParentItemRef(Item);
	if(!bIsInventoryOpen)
	{
		InteractableItemHelp->SetVisibility(ESlateVisibility::Visible);
	}
}

void UScCuwGameHud::HandleToggleInventory(const bool bShouldOpenInventory)
{
	if(bShouldOpenInventory)
	{
		Inventory->SetVisibility(ESlateVisibility::Visible);
		bIsInventoryOpen = true;
		InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Inventory->SetVisibility(ESlateVisibility::Collapsed);
		bIsInventoryOpen = false;
		if(bIsItemHelpTextOpen)
		{
			InteractableItemHelp->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	Inventory->GetInventoryItemStats()->SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwGameHud::HideItemHelp_Implementation(AActor* Item)
{
	bIsItemHelpTextOpen = false;
	InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwGameHud::HandleHealthDamage_Implementation()
{
	// Play damage animation in Bp
}

void UScCuwGameHud::HandleShieldDamage_Implementation()
{
	// Play damage animation in Bp
}

void UScCuwGameHud::ShowAlterHelp()
{
	bIsAlterHelpOpen = true;
	AlterHelpWidget->SetVisibility(ESlateVisibility::Visible);
}

void UScCuwGameHud::HideAlterHelp()
{
	bIsAlterHelpOpen = false;
	AlterHelpWidget->SetVisibility(ESlateVisibility::Collapsed);
}

FReply UScCuwGameHud::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey PressedKey = InKeyEvent.GetKey();

	if(PressedKey == ToggleInventoryPrimaryKey || PressedKey == ToggleInventorySecondaryKey)
	{
		if(Inventory)
		{
			if(Inventory->GetInventoryRef())
			{
				Inventory->GetInventoryRef()->ToggleInventory();
				
				return FEventReply(true).NativeReply;
			}
		}
	}
	
	return FEventReply(false).NativeReply;
}

void UScCuwGameHud::ShowLooseScreen()
{
	PlayerStats->SetVisibility(ESlateVisibility::Collapsed);
	Inventory->SetVisibility(ESlateVisibility::Collapsed);
	InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
	PauseMenu->SetVisibility(ESlateVisibility::Collapsed);
	WinMenu->SetVisibility(ESlateVisibility::Collapsed);
	
	LooseMenu->SetVisibility(ESlateVisibility::Visible);
}

void UScCuwGameHud::ShowWinScreen()
{
	PlayerStats->SetVisibility(ESlateVisibility::Collapsed);
	Inventory->SetVisibility(ESlateVisibility::Collapsed);
	InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
	PauseMenu->SetVisibility(ESlateVisibility::Collapsed);
	LooseMenu->SetVisibility(ESlateVisibility::Collapsed);
	
	WinMenu->SetVisibility(ESlateVisibility::Visible);
	if(UGameplayStatics::GetCurrentLevelName(this) == "Game_Level_10")
	{
		WinMenu->SetWinHeaderText(FText::FromString("You Won the Game, Congratulations"));
		WinMenu->GetNextLevelButton()->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		if(WinMenu->GetNextLevelButton()->GetVisibility() == ESlateVisibility::Collapsed)
		{
			WinMenu->SetWinHeaderText(FText::FromString("Level Completed"));
			WinMenu->GetNextLevelButton()->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

UScCuwPawnStats* UScCuwGameHud::GetPlayerStats() const
{
	return PlayerStats;
}

UScCuwInventoryWidget* UScCuwGameHud::GetInventory() const
{
	return Inventory;
}

UScCuwInteractableItemHelp* UScCuwGameHud::GetInteractableItemHelp() const
{
	return InteractableItemHelp;
}

UAlterHelpWidget* UScCuwGameHud::GetAlterHelpWidget() const
{
	return AlterHelpWidget;
}

UPauseMenuWidget* UScCuwGameHud::GetPauseMenu() const
{
	return PauseMenu;
}

UGameLooseMenu* UScCuwGameHud::GetLooseMenu() const
{
	return LooseMenu;
}

UGameWinMenu* UScCuwGameHud::GetWinMenu() const
{
	return WinMenu;
}

UImage* UScCuwGameHud::GetDamageDisplay() const
{
	return DamageDisplay;
}

UGameObjectiveWidget* UScCuwGameHud::GetGameObjective() const
{
	return GameObjective;
}

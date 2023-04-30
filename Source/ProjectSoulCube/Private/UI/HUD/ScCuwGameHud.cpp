// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ScCuwGameHud.h"

#include "Components/InventorySystemComponent.h"
#include "UI/Widgets/DataWidgets/ScCuwInteractableItemHelp.h"
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
	SetFocus();
}

void UScCuwGameHud::OnInit_Implementation(AController* Controller)
{
	PlayerStats->OnInit(Controller);
	Inventory->OnInit(Controller);
}

void UScCuwGameHud::ShowItemHelp_Implementation(AActor* Item)
{
	InteractableItemHelp->SetParentItemRef(Item);
	InteractableItemHelp->SetVisibility(ESlateVisibility::Visible);
}

void UScCuwGameHud::HideItemHelp_Implementation(AActor* Item)
{
	InteractableItemHelp->SetVisibility(ESlateVisibility::Collapsed);
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

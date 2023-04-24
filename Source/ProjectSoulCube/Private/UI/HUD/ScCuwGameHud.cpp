// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ScCuwGameHud.h"

#include "Components/InventorySystemComponent.h"
#include "UI/Widgets/PawnWidgets/ScCuwInventoryWidget.h"

void UScCuwGameHud::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = true;
}

void UScCuwGameHud::NativeConstruct()
{
	Super::NativeConstruct();

	SetFocus();
}

void UScCuwGameHud::OnInit_Implementation(AController* Controller)
{

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

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwInventoryWidget.h"

#include "Components/InventorySystemComponent.h"
#include "Components/WrapBox.h"
#include "Interface/InventoryInterface.h"
#include "Misc/InteractionStructs.h"
#include "UI/Widgets/Buttons/ScCuwImageButton.h"
#include "UI/Widgets/PawnWidgets/ScCuwInventoryItem.h"

void UScCuwInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwInventoryWidget::OnInit_Implementation(AController* Controller)
{
	if(!Controller)
	{
		return;
	}
	
	PlayerPawn = Cast<APawn>(Controller->GetPawn());
	if(PlayerPawn)
	{
		if(PlayerPawn->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
		{
			InventoryRef = IInventoryInterface::Execute_GetInventorySystemComponent(PlayerPawn);
		}
	}

	if(InventoryRef)
	{
		for(auto Item : InventoryRef->GetInventory())
		{
			TObjectPtr<UUserWidget> CreatedWidget = CreateWidget(this, InventoryItemClass, Item.Key);
			TObjectPtr<UScCuwInventoryItem> ItemWidget = Cast<UScCuwInventoryItem>(CreatedWidget);
			FInventoryItemInfo* ItemInfo = InventoryRef->GetInventoryItemInfo(Item.Key);

			if(ItemWidget)
			{
				InventoryItems.Add(Item.Key, ItemWidget);
				
				ItemWidget->SetItemQuantity(Item.Value);
				ItemWidget->GetItemButton()->SetImageTexture(ItemInfo->Thumbnail);
				SetInventoryItemVisibility(ItemWidget, Item.Value);
				
				WrapBox->AddChild(ItemWidget);
			}
		}

		InventoryRef->GetAddItemDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleInventoryItemAdd);
		InventoryRef->GetRemoveItemDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleInventoryItemRemove);
		InventoryRef->GetInventoryPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleToggleInventory);
	}
}

void UScCuwInventoryWidget::HandleInventoryItemAdd(const FName RowId, const int32 ItemQuantity)
{
	TObjectPtr<UScCuwInventoryItem> ItemWidget = InventoryItems.FindRef(RowId);
	ItemWidget->SetItemQuantity(ItemQuantity);
	
	SetInventoryItemVisibility(ItemWidget, ItemQuantity);
}

void UScCuwInventoryWidget::HandleInventoryItemRemove(const FName RowId, const int32 ItemQuantity)
{
	TObjectPtr<UScCuwInventoryItem> ItemWidget = InventoryItems.FindRef(RowId);
	ItemWidget->SetItemQuantity(ItemQuantity);
	
	SetInventoryItemVisibility(ItemWidget, ItemQuantity);
}

void UScCuwInventoryWidget::HandleToggleInventory(const bool bShouldOpenInventory)
{
	if(bShouldOpenInventory)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UScCuwInventoryWidget::SetInventoryItemVisibility(UScCuwInventoryItem* ItemWidget, const int32 ItemQuantity)
{
	if(ItemQuantity > 0)
	{
		ItemWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		ItemWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

UScrollBox* UScCuwInventoryWidget::GetScrollBox() const
{
	return ScrollBox;
}

UWrapBox* UScCuwInventoryWidget::GetWrapBox() const
{
	return WrapBox;
}

TSubclassOf<UUserWidget> UScCuwInventoryWidget::GetInventoryItemClass() const
{
	return InventoryItemClass;
}

APawn* UScCuwInventoryWidget::GetPlayerPawn() const
{
	return PlayerPawn;
}

UInventorySystemComponent* UScCuwInventoryWidget::GetInventoryRef() const
{
	return InventoryRef;
}

const TMap<FName, TObjectPtr<UScCuwInventoryItem>>& UScCuwInventoryWidget::GetInventoryItems() const
{
	return InventoryItems;
}

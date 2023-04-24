// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwInventoryWidget.h"

#include "Components/InventorySystemComponent.h"
#include "Components/WrapBox.h"
#include "Interface/InventoryInterface.h"
#include "Misc/InteractionStructs.h"
#include "UI/Widgets/DataWidgets/ScCuwInventoryItemStats.h"
#include "UI/Widgets/PawnWidgets/ScCuwInventoryItem.h"

void UScCuwInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UScCuwInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
				ItemWidget->SetItemId(Item.Key);
				ItemWidget->SetItemTexture(ItemInfo->Thumbnail);

				ItemWidget->GetInventoryItemClickedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleInventoryItemButtonClicked);
				
				SetInventoryItemVisibility(ItemWidget, Item.Value);
				
				WrapBox->AddChild(ItemWidget);
			}
		}

		InventoryRef->GetAddItemDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleInventoryItemAdd);
		InventoryRef->GetRemoveItemDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleInventoryItemRemove);
		InventoryRef->GetInventoryPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleToggleInventory);
	}

	if(InventoryItemStats)
	{
		InventoryItemStats->GetItemUseButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleItemUseButtonPressed);
		InventoryItemStats->GetItemDropButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleItemDropButtonPressed);
		InventoryItemStats->GetItemCancelButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryWidget::HandleItemCancelButtonPressed);
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

	InventoryItemStats->SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwInventoryWidget::HandleInventoryItemButtonClicked(UScCuwInventoryItem* ItemReference)
{
	if(!InventoryItemStats)
	{
		return;
	}

	if(!InventoryRef)
	{
		return;
	}
	
	FInventoryItemInfo* ItemInfo = InventoryRef->GetInventoryItemInfo(ItemReference->GetItemId());
	if(!ItemInfo)
	{
		return;
	}
	
	InventoryItemStats->SetParentItemRef(ItemReference);
	InventoryItemStats->SetItemName(ItemInfo->ItemName);
	InventoryItemStats->SetItemQuantity(ItemReference->GetItemQuantity());
	
	InventoryItemStats->SetVisibility(ESlateVisibility::Visible);
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

void UScCuwInventoryWidget::HandleItemUseButtonPressed(UScCuwInventoryItem* ItemReference)
{
	if(!InventoryRef)
	{
		return;
	}

	FName RowName = *InventoryItems.FindKey(ItemReference);
	InventoryRef->UseInventoryItem(RowName);
	
	InventoryItemStats->SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwInventoryWidget::HandleItemDropButtonPressed(UScCuwInventoryItem* ItemReference)
{
	if(!InventoryRef)
	{
		return;
	}

	FName RowName = *InventoryItems.FindKey(ItemReference);
	InventoryRef->DropInventoryItem(RowName);
	
	InventoryItemStats->SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwInventoryWidget::HandleItemCancelButtonPressed(UScCuwInventoryItem* ItemReference)
{
	if(!InventoryItemStats)
	{
		return;
	}
	InventoryItemStats->SetVisibility(ESlateVisibility::Collapsed);
}

UScrollBox* UScCuwInventoryWidget::GetScrollBox() const
{
	return ScrollBox;
}

UWrapBox* UScCuwInventoryWidget::GetWrapBox() const
{
	return WrapBox;
}

UScCuwInventoryItemStats* UScCuwInventoryWidget::GetInventoryItemStats() const
{
	return InventoryItemStats;
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

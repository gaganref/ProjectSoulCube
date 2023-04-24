// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwInventoryItemStats.h"

#include "Components/TextBlock.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"

void UScCuwInventoryItemStats::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemName(ItemName);
	SetItemQuantity(ItemQuantity);
}

void UScCuwInventoryItemStats::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemUseButton)
	{
		ItemUseButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryItemStats::HandleItemUseButtonPressed);
	}
	if(ItemDropButton)
	{
		ItemDropButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryItemStats::HandleItemDropButtonPressed);
	}
	if(ItemCancelButton)
	{
		ItemCancelButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryItemStats::HandleItemCancelButtonPressed);
	}

	SetVisibility(ESlateVisibility::Collapsed);
}

void UScCuwInventoryItemStats::HandleItemUseButtonPressed()
{
	if(ItemUseButtonPressedDelegate.IsBound())
	{
		ItemUseButtonPressedDelegate.Broadcast(ParentItemRef);
	}
}

void UScCuwInventoryItemStats::HandleItemDropButtonPressed()
{
	if(ItemDropButtonPressedDelegate.IsBound())
	{
		ItemDropButtonPressedDelegate.Broadcast(ParentItemRef);
	}
}

void UScCuwInventoryItemStats::HandleItemCancelButtonPressed()
{
	if(ItemCancelButtonPressedDelegate.IsBound())
	{
		ItemCancelButtonPressedDelegate.Broadcast(ParentItemRef);
	}
}

FName UScCuwInventoryItemStats::GetItemName() const
{
	return ItemName;
}

int32 UScCuwInventoryItemStats::GetItemQuantity() const
{
	return ItemQuantity;
}

UScCuwInventoryItem* UScCuwInventoryItemStats::GetParentItemRef() const
{
	return ParentItemRef;
}

UScCuwTextButton* UScCuwInventoryItemStats::GetItemUseButton() const
{
	return ItemUseButton;
}

UScCuwTextButton* UScCuwInventoryItemStats::GetItemDropButton() const
{
	return ItemDropButton;
}

UScCuwTextButton* UScCuwInventoryItemStats::GetItemCancelButton() const
{
	return ItemCancelButton;
}

void UScCuwInventoryItemStats::SetItemName(const FName NewName)
{
	if(ItemNameBlock)
	{
		ItemName = NewName;
		ItemNameBlock->SetText(FText::FromString(ItemName.ToString()));
	}
}

void UScCuwInventoryItemStats::SetItemQuantity(const int32 NewQuantity)
{
	if(ItemQuantityBlock)
	{
		ItemQuantity = NewQuantity;
		ItemQuantityBlock->SetText(FText::FromString(FString::FromInt(ItemQuantity)));
	}
}

void UScCuwInventoryItemStats::SetParentItemRef(UScCuwInventoryItem* InItem)
{
	ParentItemRef = InItem;
}

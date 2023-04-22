// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwInventoryItem.h"

#include "CommonNumericTextBlock.h"
#include "UI/Interface/InventoryItemDataInterface.h"

void UScCuwInventoryItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemQuantity(ItemQuantity);
}

int32 UScCuwInventoryItem::GetItemQuantity() const
{
	return ItemQuantity;
}

UScCuwImageButton* UScCuwInventoryItem::GetItemButton() const
{
	return ItemButton;
}

UCommonNumericTextBlock* UScCuwInventoryItem::GetItemQuantityBlock() const
{
	return ItemQuantityBlock;
}

void UScCuwInventoryItem::SetItemQuantity(const int32 NewQuantity)
{
	if(ItemQuantityBlock)
	{
		ItemQuantity = NewQuantity;
		ItemQuantityBlock->SetText(FText::FromString(FString::FromInt(ItemQuantity)));
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PawnWidgets/ScCuwInventoryItem.h"

#include "CommonNumericTextBlock.h"
#include "UI/Widgets/Buttons/ScCuwImageButton.h"

void UScCuwInventoryItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemQuantity(ItemQuantity);
}

void UScCuwInventoryItem::NativeConstruct()
{
	Super::NativeConstruct();

	if(ItemButton)
	{
		if(ItemButton->GetButtonPressedDelegate())
		{
			ItemButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryItem::OnItemButtonPressed);
		}
	}
}

void UScCuwInventoryItem::OnInit_Implementation(AController* Controller)
{
}

void UScCuwInventoryItem::OnItemButtonPressed_Implementation()
{
	if(InventoryItemClickedDelegate.IsBound())
	{
		InventoryItemClickedDelegate.Broadcast(this);
	}
}

int32 UScCuwInventoryItem::GetItemQuantity() const
{
	return ItemQuantity;
}

UScCuwImageButton* UScCuwInventoryItem::GetItemButton() const
{
	return ItemButton;
}

UTextBlock* UScCuwInventoryItem::GetItemQuantityBlock() const
{
	return ItemQuantityBlock;
}

FName UScCuwInventoryItem::GetItemId() const
{
	return ItemId;
}

void UScCuwInventoryItem::SetItemQuantity(const int32 NewQuantity)
{
	if(ItemQuantityBlock)
	{
		ItemQuantity = NewQuantity;
		ItemQuantityBlock->SetText(FText::FromString(FString::FromInt(ItemQuantity)));
	}
}

void UScCuwInventoryItem::SetItemId(const FName NewId)
{
	ItemId = NewId;
}

void UScCuwInventoryItem::SetItemTexture(UTexture* NewTexture) const
{
	if(ItemButton)
	{
		ItemButton->SetImageTexture(NewTexture);
	}
}

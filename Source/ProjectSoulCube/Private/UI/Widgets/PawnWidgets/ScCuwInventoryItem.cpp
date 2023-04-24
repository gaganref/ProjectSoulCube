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
	UE_LOG(LogTemp, Error, TEXT("Item Button Pressed in Inventotry - %s"), *GetNameSafe(this));
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

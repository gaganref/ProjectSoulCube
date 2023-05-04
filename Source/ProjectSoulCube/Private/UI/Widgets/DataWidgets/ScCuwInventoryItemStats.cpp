// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwInventoryItemStats.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UI/Widgets/Buttons/ScCuwTextButton.h"

void UScCuwInventoryItemStats::NativePreConstruct()
{
	Super::NativePreConstruct();

	ToggleItemOfferButton(false);
	SetItemName(TEXT("Default"));
	SetItemQuantity(5);
	SetItemWeight(3);
	SetItemDescription(TEXT("Use this Item to gain 10 health"));
}

void UScCuwInventoryItemStats::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleItemOfferButton(false);
	
	if(ItemOfferButton)
	{
		ItemOfferButton->GetButtonPressedDelegate()->AddUniqueDynamic(this, &UScCuwInventoryItemStats::HandleItemOfferButtonPressed);
	}
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

void UScCuwInventoryItemStats::HandleItemOfferButtonPressed()
{
	if(ItemOfferButtonPressedDelegate.IsBound())
	{
		ItemOfferButtonPressedDelegate.Broadcast(ParentItemRef);
	}
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

void UScCuwInventoryItemStats::ToggleItemOfferButton(const bool bShouldOpen)
{
	if(ItemOfferButton && ItemOfferButtonVerticalBox)
	{
		if(bShouldOpen)
		{
			ItemOfferButton->SetVisibility(ESlateVisibility::Visible);
			ItemOfferButton->SetIsEnabled(true);
			ItemOfferButtonVerticalBox->SetVisibility(ESlateVisibility::Visible);
			ItemOfferButtonVerticalBox->SetIsEnabled(true);
		}
		else
		{
			ItemOfferButton->SetVisibility(ESlateVisibility::Collapsed);
			ItemOfferButton->SetIsEnabled(false);
			ItemOfferButtonVerticalBox->SetVisibility(ESlateVisibility::Collapsed);
			ItemOfferButtonVerticalBox->SetIsEnabled(false);
		}
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

int32 UScCuwInventoryItemStats::GetItemWeight() const
{
	return ItemWeight;
}

FName UScCuwInventoryItemStats::GetItemDescription() const
{
	return ItemDescription;
}

UScCuwInventoryItem* UScCuwInventoryItemStats::GetParentItemRef() const
{
	return ParentItemRef;
}

UScCuwTextButton* UScCuwInventoryItemStats::GetItemOfferButton() const
{
	return ItemOfferButton;
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

void UScCuwInventoryItemStats::SetItemWeight(const int32 NewWeight)
{
	if(ItemWeightBlock)
	{
		ItemWeight = NewWeight;
		ItemWeightBlock->SetText(FText::FromString(FString::FromInt(ItemWeight)));
	}
}

void UScCuwInventoryItemStats::SetItemDescription(const FName NewDescription)
{
	if(ItemDescriptionBlock)
	{
		ItemDescription = NewDescription;
		ItemDescriptionBlock->SetText(FText::FromName(NewDescription));
	}
}

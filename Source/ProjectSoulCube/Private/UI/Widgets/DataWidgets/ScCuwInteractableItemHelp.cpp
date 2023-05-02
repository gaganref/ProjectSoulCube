// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwInteractableItemHelp.h"

#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Interface/InteractableInterface.h"

void UScCuwInteractableItemHelp::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemName(TEXT("Default"));
	SetItemWeight(3);
	SetItemDescription(TEXT("Use this Item to gain 10 health"));
}

FName UScCuwInteractableItemHelp::GetItemName() const
{
	return ItemName;
}

int32 UScCuwInteractableItemHelp::GetItemWeight() const
{
	return ItemWeight;
}

FName UScCuwInteractableItemHelp::GetItemDescription() const
{
	return ItemDescription;
}

AActor* UScCuwInteractableItemHelp::GetParentItemRef() const
{
	return ParentItemRef;
}

void UScCuwInteractableItemHelp::SetItemName(const FName NewName)
{
	if(ItemNameBlock)
	{
		ItemName = NewName;
		ItemNameBlock->SetText(FText::FromString(ItemName.ToString()));
	}
}

void UScCuwInteractableItemHelp::SetItemWeight(const int32 NewWeight)
{
	if(ItemWeightBlock)
	{
		ItemWeight = NewWeight;
		ItemWeightBlock->SetText(FText::FromString(FString::FromInt(ItemWeight)));
	}
}

void UScCuwInteractableItemHelp::SetItemDescription(const FName NewDescription)
{
	if(ItemDescriptionBlock)
	{
		ItemDescription = NewDescription;
		ItemDescriptionBlock->SetText(FText::FromName(NewDescription));
	}
}


void UScCuwInteractableItemHelp::SetParentItemRef(AActor* InItem)
{
	// ParentItemRef = InItem;

	if(!InItem)
	{
		return;
	}

	if(InItem->GetClass()->ImplementsInterface(UInteractableInterface::StaticClass()))
	{
		ParentItemRef = InItem;
		SetItemName(IInteractableInterface::Execute_GetItemName(InItem));
		SetItemWeight(IInteractableInterface::Execute_GetItemWeight(InItem));
		SetItemDescription(IInteractableInterface::Execute_GetItemDescription(InItem));
	}
}

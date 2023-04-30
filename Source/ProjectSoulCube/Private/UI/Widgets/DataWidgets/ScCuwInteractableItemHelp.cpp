// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwInteractableItemHelp.h"

#include "Components/TextBlock.h"

void UScCuwInteractableItemHelp::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetItemName(ItemName);
}

FName UScCuwInteractableItemHelp::GetItemName() const
{
	return ItemName;
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

void UScCuwInteractableItemHelp::SetParentItemRef(AActor* InItem)
{
	ParentItemRef = InItem;
}

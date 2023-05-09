// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/AlterHelpWidget.h"

#include "Components/RichTextBlock.h"

void UAlterHelpWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetHelpText(TEXT("You can offer items to the alter using inventory"));
}

void UAlterHelpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetHelpText(HelpText);
}

FName UAlterHelpWidget::GetHelpText() const
{
	return HelpText;
}

void UAlterHelpWidget::SetHelpText(const FName NewText)
{
	if(HelpTextBlock)
	{
		HelpText = NewText;
		HelpTextBlock->SetText(FText::FromName(NewText));
	}
}

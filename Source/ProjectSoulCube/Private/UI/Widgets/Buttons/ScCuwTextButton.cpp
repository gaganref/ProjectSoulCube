// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\..\Public\UI\Widgets\Buttons\ScCuwTextButton.h"

#include "CommonTextBlock.h"

void UScCuwTextButton::NativeConstruct()
{
	Super::NativeConstruct();

	TextBlock->SetText(Text);
}

FText UScCuwTextButton::GetText() const
{
	return Text;
}

UCommonTextBlock* UScCuwTextButton::GetTextBlock() const
{
	return TextBlock;
}

void UScCuwTextButton::SetText(const FText& NewText)
{
	Text = NewText;
}

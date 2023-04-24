// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwProgressBarWithLabel.h"

#include "CommonTextBlock.h"

void UScCuwProgressBarWithLabel::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetText(Text);
}

FText UScCuwProgressBarWithLabel::GetText() const
{
	return Text;
}

UProgressBar* UScCuwProgressBarWithLabel::GetProgressBar() const
{
	return ProgressBar;
}

UTextBlock* UScCuwProgressBarWithLabel::GetTextBlock() const
{
	return TextBlock;
}

void UScCuwProgressBarWithLabel::SetText(const FText& NewText)
{
	if(TextBlock)
	{
		Text = NewText;
		TextBlock->SetText(Text);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwProgressBarWithLabel.h"

#include "CommonTextBlock.h"
#include "Components/ProgressBar.h"

void UScCuwProgressBarWithLabel::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetText(Text);

	if(ProgressBar)
	{
		ProgressBar->SetFillColorAndOpacity(ProgressBarColor);
	}

	UpdateFillPercentage();
}

void UScCuwProgressBarWithLabel::UpdateFillPercentage() const
{
	if(ProgressBar)
	{
		const float FillPercent = Value/MaxValue;
		ProgressBar->SetPercent(FillPercent);
	}
}

FText UScCuwProgressBarWithLabel::GetText() const
{
	return Text;
}

UProgressBar* UScCuwProgressBarWithLabel::GetProgressBar() const
{
	return ProgressBar;
}

float UScCuwProgressBarWithLabel::GetValue() const
{
	return Value;
}

float UScCuwProgressBarWithLabel::GetMaxValue() const
{
	return MaxValue;
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

void UScCuwProgressBarWithLabel::SetValue(const float NewValue)
{
	Value = NewValue;
}

void UScCuwProgressBarWithLabel::SetMaxValue(const float NewValue)
{
	MaxValue = NewValue;
}

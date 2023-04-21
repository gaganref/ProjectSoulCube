// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/ScCuwProgressBarWithLabel.h"

#include "CommonTextBlock.h"
#include "Components/SizeBox.h"

void UScCuwProgressBarWithLabel::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	SizeBox->SetWidthOverride(Width);
	SizeBox->SetHeightOverride(Height);

	TextBlock->SetText(Text);
}

float UScCuwProgressBarWithLabel::GetWidth() const
{
	return Width;
}

float UScCuwProgressBarWithLabel::GetHeight() const
{
	return Height;
}

FText UScCuwProgressBarWithLabel::GetText() const
{
	return Text;
}

UProgressBar* UScCuwProgressBarWithLabel::GetProgressBar() const
{
	return ProgressBar;
}

UCommonTextBlock* UScCuwProgressBarWithLabel::GetTextBlock() const
{
	return TextBlock;
}

void UScCuwProgressBarWithLabel::SetWidth(const float NewWidth)
{
	Width = NewWidth;
}

void UScCuwProgressBarWithLabel::SetHeight(const float NewHeight)
{
	Height = NewHeight;
}

void UScCuwProgressBarWithLabel::SetText(const FText& NewText)
{
	Text = NewText;
}

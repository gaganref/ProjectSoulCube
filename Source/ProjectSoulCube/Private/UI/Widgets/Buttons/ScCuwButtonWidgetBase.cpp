// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Buttons/ScCuwButtonWidgetBase.h"

#include "Components/SizeBox.h"

void UScCuwButtonWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	SizeBox->SetWidthOverride(Width);
	SizeBox->SetHeightOverride(Height);
}

float UScCuwButtonWidgetBase::GetWidth() const
{
	return Width;
}

float UScCuwButtonWidgetBase::GetHeight() const
{
	return Height;
}

UScCbbButton* UScCuwButtonWidgetBase::GetButton() const
{
	return Button;
}

void UScCuwButtonWidgetBase::SetWidth(const float NewWidth)
{
	Width = NewWidth;
}

void UScCuwButtonWidgetBase::SetHeight(const float NewHeight)
{
	Height = NewHeight;
}

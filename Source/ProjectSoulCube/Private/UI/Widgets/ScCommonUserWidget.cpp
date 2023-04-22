// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/ScCommonUserWidget.h"

#include "Components/SizeBox.h"

void UScCommonUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetWidth(Width);
	SetHeight(Height);
}

float UScCommonUserWidget::GetWidth() const
{
	return Width;
}

float UScCommonUserWidget::GetHeight() const
{
	return Height;
}

void UScCommonUserWidget::SetWidth(const float NewWidth)
{
	if(SizeBox)
	{
		Width = NewWidth;
		SizeBox->SetWidthOverride(Width);
	}
}

void UScCommonUserWidget::SetHeight(const float NewHeight)
{
	if(SizeBox)
	{
		Height = NewHeight;
		SizeBox->SetHeightOverride(Height);
	}
}
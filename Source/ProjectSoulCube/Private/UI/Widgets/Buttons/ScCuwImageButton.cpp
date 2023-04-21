// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../../Public/UI/Widgets/Buttons/ScCuwImageButton.h"

void UScCuwImageButton::NativePreConstruct()
{
	Super::NativePreConstruct();
}

UImage* UScCuwImageButton::GetImage() const
{
	return Image;
}

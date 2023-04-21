// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../../Public/UI/Widgets/Buttons/ScCuwImageButton.h"

void UScCuwImageButton::NativeConstruct()
{
	Super::NativeConstruct();
}

UImage* UScCuwImageButton::GetImage() const
{
	return Image;
}

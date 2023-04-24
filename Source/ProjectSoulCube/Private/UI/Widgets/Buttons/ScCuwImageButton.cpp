// Fill out your copyright notice in the Description page of Project Settings.


#include "../../../../Public/UI/Widgets/Buttons/ScCuwImageButton.h"

#include "Components/Image.h"

void UScCuwImageButton::NativePreConstruct()
{
	Super::NativePreConstruct();
}

UImage* UScCuwImageButton::GetImage() const
{
	return Image;
}

void UScCuwImageButton::SetImageTexture(UTexture* InTexture) const
{
	if(InTexture)
	{
		Image->Brush.SetResourceObject(InTexture);	
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Buttons/ScCuwButtonWidgetBase.h"


void UScCuwButtonWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

UScCbbButton* UScCuwButtonWidgetBase::GetButton() const
{
	return Button;
}
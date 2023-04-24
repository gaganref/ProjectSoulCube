// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Buttons/ScCuwButtonWidgetBase.h"

#include "Input/CommonBoundActionButton.h"
#include "UI/Widgets/Buttons/ScCbbButton.h"


void UScCuwButtonWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UScCuwButtonWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	Button->OnClicked.AddUniqueDynamic(this, &UScCuwButtonWidgetBase::OnButtonPressed);
}

void UScCuwButtonWidgetBase::OnButtonPressed_Implementation()
{
	if(ButtonPressedDelegate.IsBound())
	{
		ButtonPressedDelegate.Broadcast();
	}
}

void UScCuwButtonWidgetBase::OnButtonHovered_Implementation()
{
}

void UScCuwButtonWidgetBase::OnButtonUnHovered_Implementation()
{
}

UButton* UScCuwButtonWidgetBase::GetButton() const
{
	return Button;
}

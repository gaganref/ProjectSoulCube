// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Buttons/ScCuwButtonWidgetBase.h"

#include "Input/CommonBoundActionButton.h"
#include "UI/Widgets/Buttons/ScCbbButton.h"


void UScCuwButtonWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	Button->OnClicked().AddUObject(this, &UScCuwButtonWidgetBase::OnButtonPressed);
}

void UScCuwButtonWidgetBase::OnButtonPressed_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Reaches - %s"), *GetNameSafe(this));
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

UScCbbButton* UScCuwButtonWidgetBase::GetButton() const
{
	return Button;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/DataWidgets/GameObjectiveWidget.h"

#include "Components/TextBlock.h"

#define LOCTEXT_NAMESPACE "MassExtractor"

void UGameObjectiveWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateObjectiveData();
}

void UGameObjectiveWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UpdateObjectiveData();
}

void UGameObjectiveWidget::UpdateObjectiveData() const
{
	if(ObjectiveData)
	{
		ObjectiveData->SetText(FText::Format(LOCTEXT("SnippetHeader", "{0}/{1}"), CurrentWeight, TargetWeight));
	}
}

int32 UGameObjectiveWidget::GetCurrentWeight() const
{
	return CurrentWeight;
}

int32 UGameObjectiveWidget::GetTargetWeight() const
{
	return TargetWeight;
}

void UGameObjectiveWidget::SetCurrentWeight(const int32 NewWeight)
{
	CurrentWeight = NewWeight;
	UpdateObjectiveData();
}

void UGameObjectiveWidget::SetTargetWeight(const int32 NewWeight)
{
	TargetWeight = NewWeight;
	UpdateObjectiveData();
}

#undef LOCTEXT_NAMESPACE

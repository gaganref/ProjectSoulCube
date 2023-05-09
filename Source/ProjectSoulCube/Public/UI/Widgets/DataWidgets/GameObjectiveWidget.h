// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "GameObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UGameObjectiveWidget : public UScCommonUserWidget
{
	GENERATED_BODY()

private:	
	UPROPERTY(BlueprintGetter = GetCurrentWeight, BlueprintSetter = SetCurrentWeight)
	int32 CurrentWeight = 12;
	
	UPROPERTY(BlueprintGetter = GetTargetWeight, BlueprintSetter = SetTargetWeight)
	int32 TargetWeight = 25;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ObjectiveHeader;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ObjectiveData;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateObjectiveData() const;

public:
	
	UFUNCTION(BlueprintGetter)
	int32 GetCurrentWeight() const;

	UFUNCTION(BlueprintGetter)
	int32 GetTargetWeight() const;
	
public:
	UFUNCTION(BlueprintSetter)
	void SetCurrentWeight(const int32 NewWeight);

	UFUNCTION(BlueprintSetter)
	void SetTargetWeight(const int32 NewWeight);
};

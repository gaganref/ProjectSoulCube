// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwPawnStats.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwPawnStats : public UScCommonUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintGetter = GetHealthBar, meta = (BindWidget))
	TObjectPtr<class UScCuwProgressBarWithLabel> HealthBar;
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);
	
public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCuwProgressBarWithLabel* GetHealthBar() const;

};

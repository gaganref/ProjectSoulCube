// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwProgressBarWithLabel.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwProgressBarWithLabel : public UScCommonUserWidget
{
	GENERATED_BODY()

	
private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetText, BlueprintSetter = SetText)
	FText Text;

	UPROPERTY(EditAnywhere)
	FLinearColor ProgressBarColor;

	UPROPERTY(BlueprintGetter = GetValue, BlueprintSetter = SetValue)
	float Value = 75.0f;

	UPROPERTY(BlueprintGetter = GetValue, BlueprintSetter = SetValue)
	float MaxValue = 100.0f;
	
private:
	UPROPERTY(BlueprintGetter = GetProgressBar, meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;

	UPROPERTY(BlueprintGetter = GetTextBlock, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

protected:
	virtual void NativePreConstruct() override;

public:
	// Getters

	UFUNCTION(BlueprintGetter)
	FText GetText() const;

	UFUNCTION(BlueprintGetter)
	float GetValue() const;
	
	UFUNCTION(BlueprintGetter)
	float GetMaxValue() const;
	
	UFUNCTION(BlueprintGetter)
	class UProgressBar* GetProgressBar() const;

	UFUNCTION(BlueprintGetter)
	class UTextBlock* GetTextBlock() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetText(const FText& NewText);

	UFUNCTION(BlueprintSetter)
	void SetValue(const float NewValue);
	
	UFUNCTION(BlueprintSetter)
	void SetMaxValue(const float NewValue);

public:
	UFUNCTION(BlueprintCallable)
	void UpdateFillPercentage() const;
};

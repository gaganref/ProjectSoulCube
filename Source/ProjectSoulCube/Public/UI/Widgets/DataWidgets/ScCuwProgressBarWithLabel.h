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
	class UProgressBar* GetProgressBar() const;

	UFUNCTION(BlueprintGetter)
	class UTextBlock* GetTextBlock() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetText(const FText& NewText);
};

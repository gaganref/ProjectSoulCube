// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ScCuwProgressBarWithLabel.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwProgressBarWithLabel : public UCommonUserWidget
{
	GENERATED_BODY()

	
private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetWidth, BlueprintSetter = SetWidth)
	float Width;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetHeight, BlueprintSetter = SetHeight)
	float Height;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetText, BlueprintSetter = SetText)
	FText Text;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintGetter = GetProgressBar, meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar;

	UPROPERTY(BlueprintGetter = GetTextBlock, meta = (BindWidget))
	TObjectPtr<class UCommonTextBlock> TextBlock;

protected:
	virtual void NativePreConstruct() override;

public:
	// Getters

	UFUNCTION(BlueprintGetter)
	float GetWidth() const;

	UFUNCTION(BlueprintGetter)
	float GetHeight() const;

	UFUNCTION(BlueprintGetter)
	FText GetText() const;
	
	UFUNCTION(BlueprintGetter)
	class UProgressBar* GetProgressBar() const;

	UFUNCTION(BlueprintGetter)
	class UCommonTextBlock* GetTextBlock() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetWidth(const float NewWidth);

	UFUNCTION(BlueprintSetter)
	void SetHeight(const float NewHeight);

	UFUNCTION(BlueprintSetter)
	void SetText(const FText& NewText);
};

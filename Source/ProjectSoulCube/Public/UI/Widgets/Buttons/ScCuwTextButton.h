// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScCuwButtonWidgetBase.h"
#include "ScCuwTextButton.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwTextButton : public UScCuwButtonWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetText, BlueprintSetter = SetText)
	FText Text;

private:	
	UPROPERTY(BlueprintGetter = GetTextBlock, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;
	
protected:
	virtual void NativePreConstruct() override;

public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	FText GetText() const;

	UFUNCTION(BlueprintGetter)
	class UTextBlock* GetTextBlock() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetText(const FText& NewText);
	
};

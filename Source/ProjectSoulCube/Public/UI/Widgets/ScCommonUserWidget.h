// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ScCommonUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UScCommonUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetWidth, BlueprintSetter = SetWidth)
	float Width;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetHeight, BlueprintSetter = SetHeight)
	float Height;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
protected:
	virtual void NativePreConstruct() override;

public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	float GetWidth() const;

	UFUNCTION(BlueprintGetter)
	float GetHeight() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetWidth(const float NewWidth);

	UFUNCTION(BlueprintSetter)
	void SetHeight(const float NewHeight);	
};

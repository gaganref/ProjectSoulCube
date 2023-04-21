// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "ScCuwButtonWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwButtonWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

	
private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetWidth, BlueprintSetter = SetWidth, meta = (AllowPrivateAccess = "true"))
	float Width;
	
	UPROPERTY(EditAnywhere, BlueprintGetter = GetHeight, BlueprintSetter = SetHeight, meta = (AllowPrivateAccess = "true"))
	float Height;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBox;
	
	UPROPERTY(BlueprintGetter = GetButton, meta = (BindWidget))
	TObjectPtr<class UScCbbButton> Button;

protected:
	virtual void NativeConstruct() override;

public:
	// Getters

	UFUNCTION(BlueprintGetter)
	float GetWidth() const;

	UFUNCTION(BlueprintGetter)
	float GetHeight() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCbbButton* GetButton() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetWidth(const float NewWidth);

	UFUNCTION(BlueprintSetter)
	void SetHeight(const float NewHeight);
	
};

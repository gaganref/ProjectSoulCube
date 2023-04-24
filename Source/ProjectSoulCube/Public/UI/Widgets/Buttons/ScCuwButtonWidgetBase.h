// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwButtonWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnHovered);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwButtonWidgetBase : public UScCommonUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintGetter = GetButton, meta = (BindWidget))
	TObjectPtr<class UScCbbButton> Button;

	FOnButtonPressed ButtonPressedDelegate;

protected:
	virtual void NativePreConstruct() override;

	virtual void OnButtonPressed_Implementation();

	virtual void OnButtonHovered_Implementation();

	virtual void OnButtonUnHovered_Implementation();

public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCbbButton* GetButton() const;

	UFUNCTION(BlueprintNativeEvent)
	void OnButtonPressed();

	UFUNCTION(BlueprintNativeEvent)
	void OnButtonHovered();

	UFUNCTION(BlueprintNativeEvent)
	void OnButtonUnHovered();

	FOnButtonPressed* GetButtonPressedDelegate() { return &ButtonPressedDelegate; }
};

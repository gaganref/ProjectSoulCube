// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwButtonWidgetBase.generated.h"

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

protected:
	virtual void NativePreConstruct() override;

public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UScCbbButton* GetButton() const;
	
};

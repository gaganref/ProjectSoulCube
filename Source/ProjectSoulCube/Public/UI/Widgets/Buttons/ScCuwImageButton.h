// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScCuwButtonWidgetBase.h"
#include "ScCuwImageButton.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwImageButton : public UScCuwButtonWidgetBase
{
	GENERATED_BODY()

private:	
	UPROPERTY(BlueprintGetter = GetImage, meta = (BindWidget))
	TObjectPtr<class UImage> Image;
	
protected:
	virtual void NativeConstruct() override;

public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	class UImage* GetImage() const;
	
};

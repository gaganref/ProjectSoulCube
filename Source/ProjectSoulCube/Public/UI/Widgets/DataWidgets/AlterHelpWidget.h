// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "AlterHelpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UAlterHelpWidget : public UScCommonUserWidget
{
	GENERATED_BODY()

private:	
	
	UPROPERTY(BlueprintGetter = GetHelpText, BlueprintSetter = SetHelpText)
	FName HelpText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class URichTextBlock> HelpTextBlock;

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintGetter)
	FName GetHelpText() const;
	
public:
	UFUNCTION(BlueprintSetter)
	void SetHelpText(const FName NewText);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "GameLooseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UGameLooseMenu : public UScCommonUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> LooseText;
	
	UPROPERTY(BlueprintGetter = GetRetryButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> RetryButton;
	
	UPROPERTY(BlueprintGetter = GetReturnToMainMenuButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ReturnToMainMenuButton;

protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void OnInit_Implementation(AController* Controller);
	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);
	
public:

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetRetryButton() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetReturnToMainMenuButton() const;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScCuwMainMenuHud.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitButtonPressed);

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UScCuwMainMenuHud : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintGetter = GetStartButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> StartButton;
	
	UPROPERTY(BlueprintGetter = GetQuitButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> QuitButton;

	FOnStartButtonPressed StartButtonPressedDelegate;
	FOnQuitButtonPressed QuitButtonPressedDelegate;
	
protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void OnInit_Implementation(AController* Controller);
	
protected:
	
	UFUNCTION()
	void HandleStartButtonPressed();
	
	UFUNCTION()
	void HandleQuitButtonPressed();

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);
	
public:

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetStartButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetQuitButton() const;

	FOnStartButtonPressed* GetStartButtonPressedDelegate() { return &StartButtonPressedDelegate; }
	
	FOnQuitButtonPressed* GetQuitButtonPressedDelegate() { return &QuitButtonPressedDelegate; }
};

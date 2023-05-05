// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "PauseMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestartButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResumeButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMainMenuButtonPressed);

/**
 * 
 */
UCLASS()
class PROJECTSOULCUBE_API UPauseMenuWidget : public UScCommonUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(BlueprintGetter = GetRestartButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> RestartButton;
	
	UPROPERTY(BlueprintGetter = GetResumeButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ResumeButton;
	
	UPROPERTY(BlueprintGetter = GetMainMenuButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> MainMenuButton;

	FOnRestartButtonPressed RestartButtonPressedDelegate;
	FOnResumeButtonPressed ResumeButtonPressedDelegate;
	FOnMainMenuButtonPressed MainMenuButtonPressedDelegate;
	
protected:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void OnInit_Implementation(AController* Controller);
	
protected:

	UFUNCTION()
	void HandleRestartButtonPressed();
	
	UFUNCTION()
	void HandleResumeButtonPressed();
	
	UFUNCTION()
	void HandleMainMenuButtonPressed();

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);
	
public:

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetRestartButton() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetResumeButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetMainMenuButton() const;

	FOnRestartButtonPressed* GetRestartButtonPressedDelegate() { return &RestartButtonPressedDelegate; }
	
	FOnResumeButtonPressed* GetResumeButtonPressedDelegate() { return &ResumeButtonPressedDelegate; }
	
	FOnMainMenuButtonPressed* GetMainMenuButtonPressedDelegate() { return &MainMenuButtonPressedDelegate; }
};

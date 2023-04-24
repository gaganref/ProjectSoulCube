// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInventoryItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwInventoryItem : public UScCommonUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetItemQuantity, BlueprintSetter = SetItemQuantity)
	int32 ItemQuantity;	

private:
	UPROPERTY(BlueprintGetter = GetItemButton, meta = (BindWidget))
	TObjectPtr<class UScCuwImageButton> ItemButton;

	UPROPERTY(BlueprintGetter = GetItemQuantityBlock, meta = (BindWidget))
	TObjectPtr<class UCommonNumericTextBlock> ItemQuantityBlock;

protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	virtual void OnItemButtonPressed_Implementation();
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnItemButtonPressed();
	
public:
	// Getters
	
	UFUNCTION(BlueprintGetter)
	int32 GetItemQuantity() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCuwImageButton* GetItemButton() const;

	UFUNCTION(BlueprintGetter)
	class UCommonNumericTextBlock* GetItemQuantityBlock() const;

public:
	// Setters

	UFUNCTION(BlueprintSetter)
	void SetItemQuantity(const int32 NewQuantity);
};

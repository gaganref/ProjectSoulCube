// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInventoryItemStats.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemOfferButtonPressed, UScCuwInventoryItem*, ItemReference);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUseButtonPressed, UScCuwInventoryItem*, ItemReference);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemDropButtonPressed, UScCuwInventoryItem*, ItemReference);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemCancelButtonPressed, UScCuwInventoryItem*, ItemReference);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwInventoryItemStats : public UScCommonUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintGetter = GetItemName, BlueprintSetter = SetItemName)
	FName ItemName;

	UPROPERTY(BlueprintGetter = GetItemQuantity, BlueprintSetter = SetItemQuantity)
	int32 ItemQuantity;
	
	UPROPERTY(BlueprintGetter = GetItemWeight, BlueprintSetter = SetItemWeight)
	int32 ItemWeight;

	UPROPERTY(BlueprintGetter = GetItemDescription, BlueprintSetter = SetItemDescription)
	FName ItemDescription;
	
	UPROPERTY(BlueprintGetter = GetParentItemRef, BlueprintSetter = SetParentItemRef)
	TObjectPtr<class UScCuwInventoryItem> ParentItemRef;

private:	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemQuantityBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemWeightBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class URichTextBlock> ItemDescriptionBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UVerticalBox> ItemOfferButtonVerticalBox;
	
	UPROPERTY(BlueprintGetter = GetItemOfferButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemOfferButton;
	
	UPROPERTY(BlueprintGetter = GetItemUseButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemUseButton;

	UPROPERTY(BlueprintGetter = GetItemDropButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemDropButton;
	
	UPROPERTY(BlueprintGetter = GetItemCancelButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemCancelButton;

	FOnItemOfferButtonPressed ItemOfferButtonPressedDelegate;
	FOnItemUseButtonPressed ItemUseButtonPressedDelegate;
	FOnItemDropButtonPressed ItemDropButtonPressedDelegate;
	FOnItemCancelButtonPressed ItemCancelButtonPressedDelegate;
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleItemOfferButtonPressed();
	
	UFUNCTION()
	void HandleItemUseButtonPressed();

	UFUNCTION()
	void HandleItemDropButtonPressed();

	UFUNCTION()
	void HandleItemCancelButtonPressed();

public:
	UFUNCTION(BlueprintCallable)
	void ToggleItemOfferButton(const bool bShouldOpen);
	
public:
	UFUNCTION(BlueprintGetter)
	FName GetItemName() const;

	UFUNCTION(BlueprintGetter)
	int32 GetItemQuantity() const;

	UFUNCTION(BlueprintGetter)
	int32 GetItemWeight() const;

	UFUNCTION(BlueprintGetter)
	FName GetItemDescription() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryItem* GetParentItemRef() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemOfferButton() const;
	
	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemUseButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemDropButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemCancelButton() const;

	FOnItemOfferButtonPressed* GetItemOfferButtonPressedDelegate() { return &ItemOfferButtonPressedDelegate; }
	
	FOnItemUseButtonPressed* GetItemUseButtonPressedDelegate() { return &ItemUseButtonPressedDelegate; }
	
	FOnItemDropButtonPressed* GetItemDropButtonPressedDelegate() { return &ItemDropButtonPressedDelegate; }
	
	FOnItemCancelButtonPressed* GetItemCancelButtonPressedDelegate() { return &ItemCancelButtonPressedDelegate; }
	
public:
	UFUNCTION(BlueprintSetter)
	void SetItemName(const FName NewName);
	
	UFUNCTION(BlueprintSetter)
	void SetItemQuantity(const int32 NewQuantity);

	UFUNCTION(BlueprintSetter)
	void SetParentItemRef(class UScCuwInventoryItem* InItem);

	UFUNCTION(BlueprintSetter)
	void SetItemWeight(const int32 NewWeight);

	UFUNCTION(BlueprintSetter)
	void SetItemDescription(const FName NewDescription);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInventoryItemStats.generated.h"

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
	UPROPERTY(BlueprintGetter = GetItemName, BlueprintSetter = SetItemName, meta = (BindWidget))
	FName ItemName;

	UPROPERTY(BlueprintGetter = GetItemQuantity, BlueprintSetter = SetItemQuantity)
	int32 ItemQuantity;

	UPROPERTY(BlueprintGetter = GetParentItemRef, BlueprintSetter = SetParentItemRef)
	TObjectPtr<class UScCuwInventoryItem> ParentItemRef;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemQuantityBlock;

	UPROPERTY(BlueprintGetter = GetItemUseButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemUseButton;

	UPROPERTY(BlueprintGetter = GetItemDropButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemDropButton;
	
	UPROPERTY(BlueprintGetter = GetItemCancelButton, meta = (BindWidget))
	TObjectPtr<class UScCuwTextButton> ItemCancelButton;

	FOnItemUseButtonPressed ItemUseButtonPressedDelegate;
	FOnItemDropButtonPressed ItemDropButtonPressedDelegate;
	FOnItemCancelButtonPressed ItemCancelButtonPressedDelegate;
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleItemUseButtonPressed();

	UFUNCTION()
	void HandleItemDropButtonPressed();

	UFUNCTION()
	void HandleItemCancelButtonPressed();
	
public:
	UFUNCTION(BlueprintGetter)
	FName GetItemName() const;

	UFUNCTION(BlueprintGetter)
	int32 GetItemQuantity() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwInventoryItem* GetParentItemRef() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemUseButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemDropButton() const;

	UFUNCTION(BlueprintGetter)
	class UScCuwTextButton* GetItemCancelButton() const;

	FOnItemUseButtonPressed* GetItemUseButtonPressedDelegate() { return &ItemUseButtonPressedDelegate; }
	
	FOnItemDropButtonPressed* GetItemDropButtonPressedDelegate() { return &ItemDropButtonPressedDelegate; }
	
	FOnItemCancelButtonPressed* GetItemCancelButtonPressedDelegate() { return &ItemCancelButtonPressedDelegate; }
	
public:
	UFUNCTION(BlueprintSetter)
	void SetItemName(const FName NewName);
	
	UFUNCTION(BlueprintSetter)
	void SetItemQuantity(const int32 NewQuantity);

	UFUNCTION(BlueprintSetter)
	void SetParentItemRef(UScCuwInventoryItem* InItem);
	
};

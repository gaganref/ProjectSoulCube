// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInteractableItemHelp.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwInteractableItemHelp : public UScCommonUserWidget
{
	GENERATED_BODY()

private:	
	UPROPERTY(BlueprintGetter = GetItemName, BlueprintSetter = SetItemName, meta = (BindWidget))
	FName ItemName;

	UPROPERTY(BlueprintGetter = GetItemWeight, BlueprintSetter = SetItemWeight)
	int32 ItemWeight;

	UPROPERTY(BlueprintGetter = GetItemDescription, BlueprintSetter = SetItemDescription)
	FName ItemDescription;
	
	UPROPERTY(BlueprintGetter = GetParentItemRef, BlueprintSetter = SetParentItemRef)
	TObjectPtr<class AActor> ParentItemRef;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemWeightBlock;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class URichTextBlock> ItemDescriptionBlock;

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintGetter)
	FName GetItemName() const;

	UFUNCTION(BlueprintGetter)
	int32 GetItemWeight() const;

	UFUNCTION(BlueprintGetter)
	FName GetItemDescription() const;
	
	UFUNCTION(BlueprintGetter)
	class AActor* GetParentItemRef() const;

	
public:
	UFUNCTION(BlueprintSetter)
	void SetItemName(const FName NewName);

	UFUNCTION(BlueprintSetter)
	void SetItemWeight(const int32 NewWeight);

	UFUNCTION(BlueprintSetter)
	void SetItemDescription(const FName NewDescription);
	
	UFUNCTION(BlueprintSetter)
	void SetParentItemRef(AActor* InItem);
	
};

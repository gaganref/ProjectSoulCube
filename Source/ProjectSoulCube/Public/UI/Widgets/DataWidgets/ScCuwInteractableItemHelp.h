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

	UPROPERTY(BlueprintGetter = GetParentItemRef, BlueprintSetter = SetParentItemRef)
	TObjectPtr<class AActor> ParentItemRef;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemNameBlock;

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintGetter)
	FName GetItemName() const;

	UFUNCTION(BlueprintGetter)
	class AActor* GetParentItemRef() const;

	
public:
	UFUNCTION(BlueprintSetter)
	void SetItemName(const FName NewName);
	
	UFUNCTION(BlueprintSetter)
	void SetParentItemRef(AActor* InItem);
	
};

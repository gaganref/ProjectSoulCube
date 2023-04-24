// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/ScCommonUserWidget.h"
#include "ScCuwInventoryWidget.generated.h"

class UInventorySystemComponent;
class UScCuwInventoryItem;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJECTSOULCUBE_API UScCuwInventoryWidget : public UScCommonUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetInventoryItemClass)
	TSubclassOf<UUserWidget> InventoryItemClass;
	
private:
	UPROPERTY(BlueprintGetter = GetScrollBox, meta = (BindWidget))
	TObjectPtr<class UScrollBox> ScrollBox;

	UPROPERTY(BlueprintGetter = GetWrapBox, meta = (BindWidget))
	TObjectPtr<class UWrapBox> WrapBox;

private:
	UPROPERTY(BlueprintGetter = GetPlayerPawn, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> PlayerPawn;

	UPROPERTY(BlueprintGetter = GetInventoryRef, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventorySystemComponent> InventoryRef;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TMap<FName, TObjectPtr<UScCuwInventoryItem>> InventoryItems;
	
protected:
	virtual void NativePreConstruct() override;
	
	virtual void OnInit_Implementation(AController* Controller);

	UFUNCTION()
	void HandleInventoryItemAdd(const FName RowId, const int32 ItemQuantity);
	
	UFUNCTION()
	void HandleInventoryItemRemove(const FName RowId, const int32 ItemQuantity);

	UFUNCTION()
	void HandleToggleInventory(const bool bShouldOpenInventory);

	UFUNCTION()
	static void SetInventoryItemVisibility(UScCuwInventoryItem* ItemWidget, const int32 ItemQuantity);
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit(AController* Controller);

public:
	// Getters

	UFUNCTION(BlueprintGetter)
	class UScrollBox* GetScrollBox() const;

	UFUNCTION(BlueprintGetter)
	class UWrapBox* GetWrapBox() const;

	UFUNCTION(BlueprintGetter)
	class APawn* GetPlayerPawn() const;

	UFUNCTION(BlueprintGetter)
	class UInventorySystemComponent* GetInventoryRef() const;

	const TMap<FName, TObjectPtr<UScCuwInventoryItem>>& GetInventoryItems() const;

	UFUNCTION(BlueprintGetter)
	TSubclassOf<class UUserWidget> GetInventoryItemClass() const;
};

﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InteractionStructs.Generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture> Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = "/Script/InteractionSystemPlugin.InteractableInterface"))
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemSize;
	
	UPROPERTY(BlueprintReadWrite)
	int32 ItemQuantity;

	FInventoryItemInfo() : ItemName("Default"), Thumbnail(nullptr), ItemClass(nullptr), ItemSize(0), ItemQuantity(0)
	{
	}
};
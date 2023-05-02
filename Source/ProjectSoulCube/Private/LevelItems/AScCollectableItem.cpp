// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelItems/AScCollectableItem.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "DebugLibraryCommon.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/HUD.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "GAS/GameplayEffects/SCGameplayEffect.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/InteractionStructs.h"
#include "UI/Interface/InteractableItemHudInterface.h"


// Sets default values
AAScCollectableItem::AAScCollectableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;
	
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable Mesh"));
	InteractableMesh->SetupAttachment(RootComponent);

	// For simple mesh animation
	InterpToMovementComponent = CreateDefaultSubobject<UInterpToMovementComponent>(TEXT("Interep To Movement"));
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
}

void AAScCollectableItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	AdjustInteractablePosition();
}

// Called when the game starts or when spawned
void AAScCollectableItem::BeginPlay()
{
	Super::BeginPlay();

	UpdateItemInfoData();
}

void AAScCollectableItem::UpdateItemInfoData()
{
	ItemInfoData = ItemInfo.GetRow<FInventoryItemInfo>(TEXT("BeginPlay in AInteractable"));
}

void AAScCollectableItem::AdjustInteractablePosition()
{
	if(bAutoSetInteractableLocalOffset)
	{
		if(InteractableMesh->GetStaticMesh())
		{
			const FVector UpVector = GetActorUpVector();
			const FVector BoxExtent = InteractableMesh->GetStaticMesh()->GetBounds().BoxExtent;
			const FVector TargetLocation = (BoxExtent * UpVector) / 2.0f;
			InteractableMesh->SetRelativeLocation(TargetLocation + OffsetAdjuster);
	
			const FVector TargetWidgetLocation = BoxExtent * (UpVector * -1.0f);
		}
	}
}

// Called every frame
void AAScCollectableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FName AAScCollectableItem::GetItemId_Implementation()
{
	return ItemInfo.RowName;
}

FName AAScCollectableItem::GetItemDescription_Implementation()
{
	if(!ItemInfoData)
	{
		return TEXT("NONE");
	}
	
	return ItemInfoData->ItemDescription;
}

FName AAScCollectableItem::GetItemName_Implementation()
{
	if(!ItemInfoData)
	{
		return TEXT("NONE");
	}
	
	return ItemInfoData->ItemName;
}

int32 AAScCollectableItem::GetItemWeight_Implementation()
{
	if(!ItemInfoData)
	{
		return -1;
	}
	
	return ItemInfoData->ItemWeight;
}

void AAScCollectableItem::OnInteract_Implementation(AActor* Caller)
{
	IInteractableInterface::OnInteract_Implementation(Caller);

	// Make sure to end the focus
	// EndFocus(Caller);
	
	// TODO: apply its gameplay effect
	if(!Caller || !ItemGameplayAffectClass)
	{
		return;
	}
	
	const IAbilitySystemInterface* AscCaller = Cast<IAbilitySystemInterface>(Caller);
	if(!AscCaller)
	{
		return;
	}
	
	const TObjectPtr<UAbilitySystemComponent> AscRef = AscCaller->GetAbilitySystemComponent();
	if(!AscRef)
	{
		return;
	}

	UGameplayEffect* ItemGameplayAffect = ItemGameplayAffectClass->GetDefaultObject<UGameplayEffect>();
	
	const FGameplayEffectContextHandle GameplayEffectContextHandle;
	AscRef->ApplyGameplayEffectToSelf(ItemGameplayAffect, 0.0f, GameplayEffectContextHandle);
	
	// Only Destroy the actor if it is placed in the level
	if(GetWorld() != NULL)
	{
		Destroy();
	}
}

void AAScCollectableItem::BeginFocus_Implementation(AActor* Caller)
{
	IInteractableInterface::BeginFocus_Implementation(Caller);

	TObjectPtr<APlayerController> ControllerRef=  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<AHUD> HudRef= ControllerRef->GetHUD();

	if(HudRef)
	{
		if(HudRef->GetClass()->ImplementsInterface(UInteractableItemHudInterface::StaticClass()))
		{
			IInteractableItemHudInterface::Execute_ShowItemInfo(HudRef, this);
		}
	}
}

void AAScCollectableItem::EndFocus_Implementation(AActor* Caller)
{
	IInteractableInterface::EndFocus_Implementation(Caller);

	TObjectPtr<APlayerController> ControllerRef=  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<AHUD> HudRef= ControllerRef->GetHUD();

	if(HudRef)
	{
		if(HudRef->GetClass()->ImplementsInterface(UInteractableItemHudInterface::StaticClass()))
		{
			IInteractableItemHudInterface::Execute_HideItemInfo(HudRef, this);
		}
	}
}

bool AAScCollectableItem::CanInteract_Implementation(AActor* Caller)
{
	return true;
}

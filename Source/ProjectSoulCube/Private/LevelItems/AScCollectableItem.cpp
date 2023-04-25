// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelItems/AScCollectableItem.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/WidgetComponent.h"
#include "GAS/GameplayEffects/SCGameplayEffect.h"


// Sets default values
AAScCollectableItem::AAScCollectableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = SceneComponent;
	
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable Mesh"));
	InteractableMesh->SetupAttachment(RootComponent);

	HelpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("hep Widget"));
	HelpWidget->SetupAttachment(InteractableMesh);
	HelpWidget->SetVisibility(false);
	HelpWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HelpWidget->SetDrawSize(FVector2D(250.0f, 250.0f));
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
	
}

void AAScCollectableItem::AdjustInteractablePosition()
{
	if(!bAutoSetInteractableLocalOffset)
	{
		return;
	}
	if(!InteractableMesh->GetStaticMesh())
	{
		return;
	}
	
	const FVector UpVector = GetActorUpVector();
	const FVector BoxExtent = InteractableMesh->GetStaticMesh()->GetBounds().BoxExtent;
	const FVector TargetLocation = (BoxExtent * UpVector) / 2.0f;
	InteractableMesh->SetRelativeLocation(TargetLocation);
	
	const FVector TargetWidgetLocation = BoxExtent * (UpVector * -1.0f);
	HelpWidget->SetRelativeLocation(TargetWidgetLocation);
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

void AAScCollectableItem::OnInteract_Implementation(AActor* Caller)
{
	IInteractableInterface::OnInteract_Implementation(Caller);

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

	HelpWidget->SetVisibility(true);
}

void AAScCollectableItem::EndFocus_Implementation(AActor* Caller)
{
	IInteractableInterface::EndFocus_Implementation(Caller);

	HelpWidget->SetVisibility(false);
}

bool AAScCollectableItem::CanInteract_Implementation(AActor* Caller)
{
	return true;
}

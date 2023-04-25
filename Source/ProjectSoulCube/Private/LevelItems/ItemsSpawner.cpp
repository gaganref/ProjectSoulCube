// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelItems/ItemsSpawner.h"


// Sets default values
AItemsSpawner::AItemsSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemsSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


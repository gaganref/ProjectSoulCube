﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LevelManager.h"

#include "Generator/LevelGenerator.h"
#include "Grid/GridDataGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CustomProceduralMeshComponent.h"


// Sets default values
ALevelManager::ALevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MainMenuController.h"


// Sets default values
AMainMenuController::AMainMenuController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMenuController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


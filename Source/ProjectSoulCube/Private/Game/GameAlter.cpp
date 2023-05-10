// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameAlter.h"


// Sets default values
AGameAlter::AGameAlter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameAlter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameAlter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


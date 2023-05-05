// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ScDefaultGameInstance.h"

#include "MoviePlayer.h"
#include "MoviePlayer.h"
#include "Game/ScDefaultGameViewportClient.h"

// Ref: https://unrealcommunity.wiki/loading-screen-243mzpq1

void UScDefaultGameInstance::Init()
{
	Super::Init();
	
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UScDefaultGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UScDefaultGameInstance::EndLoadingScreen);
}

void UScDefaultGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
 
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
}

void UScDefaultGameInstance::EndLoadingScreen(UWorld* InLoadedWorld)
{
	const UWorld* World = GetWorld();
	if (World)
	{
		UScDefaultGameViewportClient* GameViewportClient = Cast<UScDefaultGameViewportClient>(World->GetGameViewport());
		if (GameViewportClient)
		{
			GameViewportClient->Fade(3.0f, false);
		}
	}
}

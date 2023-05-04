// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DefaultGameMode.h"

#include "Game/SCHUDGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "UI/HUD/ScCuwGameHud.h"

void ADefaultGameMode::BeginGameWin()
{
	GameWin();
}

void ADefaultGameMode::BeginGameLost()
{
	TObjectPtr<ACharacter> PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(this, 0);
	TObjectPtr<APlayerController> PlayerControllerRef =  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<APlayerCameraManager> PlayerCameraManagerRef =  UGameplayStatics::GetPlayerCameraManager(this, 0);
	
	if(PlayerCharacterRef)
	{
		PlayerControllerRef->DisableInput(PlayerControllerRef);
		PlayerCharacterRef->DisableInput(PlayerControllerRef);
	}
	
	if(PlayerControllerRef)
	{
		TObjectPtr<ASCHUDGame> HudRef = Cast<ASCHUDGame>(PlayerControllerRef->GetHUD());
		if(HudRef)
		{
			TObjectPtr<UScCuwGameHud> HudWidgetRef = HudRef->GetHudWidget();
			if(HudWidgetRef)
			{
				HudWidgetRef->RemoveFromParent();
			}
		}
	}

	if(PlayerCameraManagerRef)
	{
		PlayerCameraManagerRef->StartCameraFade(0.0f, 0.75f, 3.0f, CameraFadeInColor, false, true);
	}
	
	GameLost();		
}

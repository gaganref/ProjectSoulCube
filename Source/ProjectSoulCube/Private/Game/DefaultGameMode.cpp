// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/DefaultGameMode.h"

#include "Game/SCHUDGame.h"
#include "Interface/PlayerAnimInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

void ADefaultGameMode::BeginGameWin()
{
	TObjectPtr<ACharacter> PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(this, 0);
	TObjectPtr<APlayerController> PlayerControllerRef =  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<APlayerCameraManager> PlayerCameraManagerRef =  UGameplayStatics::GetPlayerCameraManager(this, 0);
	
	if(PlayerCharacterRef)
	{
		PlayerCharacterRef->DisableInput(PlayerControllerRef);

		if(PlayerCharacterRef->GetMesh())
		{
			if(UAnimInstance* Ai = PlayerCharacterRef->GetMesh()->GetAnimInstance())
			{
				if(Ai->GetClass()->ImplementsInterface(UPlayerAnimInterface::StaticClass()))
				{
					IPlayerAnimInterface::Execute_PlayWinAnimation(Ai);
				}
			}
		}
	}
	
	if(PlayerControllerRef)
	{
		PlayerControllerRef->DisableInput(PlayerControllerRef);
	}

	if(PlayerCameraManagerRef)
	{
		PlayerCameraManagerRef->StartCameraFade(0.0f, 0.5f, 3.0f, WinCameraFadeInColor, false, true);
	}
	
	GameWin();
}

void ADefaultGameMode::BeginGameLost()
{
	TObjectPtr<ACharacter> PlayerCharacterRef = UGameplayStatics::GetPlayerCharacter(this, 0);
	TObjectPtr<APlayerController> PlayerControllerRef =  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<APlayerCameraManager> PlayerCameraManagerRef =  UGameplayStatics::GetPlayerCameraManager(this, 0);
	
	if(PlayerCharacterRef)
	{
		PlayerCharacterRef->DisableInput(PlayerControllerRef);
	}
	
	if(PlayerControllerRef)
	{
		PlayerControllerRef->DisableInput(PlayerControllerRef);
	}

	if(PlayerCameraManagerRef)
	{
		PlayerCameraManagerRef->StartCameraFade(0.0f, 0.5f, 3.0f, LooseCameraFadeInColor, false, true);
	}
	
	GameLost();		
}

void ADefaultGameMode::GameWin_Implementation()
{
	TObjectPtr<APlayerController> PlayerControllerRef =  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<ASCHUDGame> HudRef = Cast<ASCHUDGame>(PlayerControllerRef->GetHUD());
	if(HudRef)
	{
		if(HudRef)
		{
			HudRef->ShowWinScreen();
		}
	}
}

void ADefaultGameMode::GameLost_Implementation()
{
	TObjectPtr<APlayerController> PlayerControllerRef =  UGameplayStatics::GetPlayerController(this, 0);
	TObjectPtr<ASCHUDGame> HudRef = Cast<ASCHUDGame>(PlayerControllerRef->GetHUD());
	if(HudRef)
	{
		if(HudRef)
		{
			HudRef->ShowLooseScreen();
		}
	}
}

int32 ADefaultGameMode::GetTargetWeightToWin() const
{
	return TargetWeightToWin;
}

void ADefaultGameMode::SetTargetWeightToWin(const int32 NewWeight)
{
	TargetWeightToWin = NewWeight;
}

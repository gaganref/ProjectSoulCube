// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ScDefaultGameViewportClient.h"

#include "Engine/Canvas.h"

void UScDefaultGameViewportClient::PostRender(UCanvas* Canvas)
{
	Super::PostRender(Canvas);

	// Fade if requested, you could use the same DrawScreenFade method from any canvas such as the HUD
	if (bFading)
	{
		DrawScreenFade(Canvas);
	}
}

void UScDefaultGameViewportClient::ClearFade()
{
	bFading = false;
}

void UScDefaultGameViewportClient::Fade(const float InDuration, const bool InbToBlack)
{
	if (World)
	{
		bFading = true;
		bToBlack = InbToBlack;
		FadeDuration = InDuration;
		FadeStartTime = World->GetTimeSeconds();
	}
}

void UScDefaultGameViewportClient::DrawScreenFade(UCanvas* Canvas)
{
	if (bFading)
	{
		if (World)
		{
			const float Time = World->GetTimeSeconds();
			const float Alpha = FMath::Clamp((Time - FadeStartTime) / FadeDuration, 0.f, 1.f);

			// Make sure that we stay black in a fade to black
			if (Alpha == 1.f && !bToBlack)
			{
				bFading = false;
			}
			else
			{
				FColor OldColor = Canvas->DrawColor;
				FLinearColor FadeColor = FLinearColor::Black;
				FadeColor.A = bToBlack ? Alpha : 1 - Alpha;
				Canvas->DrawColor = FadeColor.ToFColor(true);
				Canvas->DrawTile(Canvas->DefaultTexture, 0, 0, Canvas->ClipX, Canvas->ClipY, 0, 0,
				                 Canvas->DefaultTexture->GetSizeX(), Canvas->DefaultTexture->GetSizeY());
				Canvas->DrawColor = OldColor;
			}
		}
	}
}

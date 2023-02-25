// Copyright Epic Games, Inc. All Rights Reserved.

#include "DebugFunctionLibrary.h"
#include "DebugLibrary.h"
#include "DebugLibraryCommon.h"

UDebugFunctionLibrary::UDebugFunctionLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UDebugFunctionLibrary::DebugLibrarySampleFunction(float Param)
{
	return -1;
}

/** Print a quick test message on screen and log it. */
void UDebugFunctionLibrary::DebugPrint(UObject* CallingObject)
{
	DebugLog(CallingObject);
	DebugScreenLog(CallingObject);
}

/** Log a quick test message. */
void UDebugFunctionLibrary::DebugLog(UObject* CallingObject)
{
	UE_LOG(LogDebugFunctionLibrary, Error, TEXT("%s:: Debug test print."), *GetNameSafe(CallingObject));
}

/** Print a quick test message on screen. */
void UDebugFunctionLibrary::DebugScreenLog(UObject* CallingObject)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
			FString::Printf(TEXT("%s:: Debug test print."), *GetNameSafe(CallingObject)));
	}
}

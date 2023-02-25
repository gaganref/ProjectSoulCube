// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DebugFunctionLibrary.generated.h"


/*
 * Library of debugging functions to simplify logging, printing and debugging.
*/
UCLASS(meta=(ScriptName="DebugFunctionLibrary"))
class DEBUGLIBRARY_API UDebugFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Sample template reference function */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "DebugLibrary sample test testing"), Category = "DebugLibraryTesting")
	static float DebugLibrarySampleFunction(float Param);

	/** Print a quick test message on screen and log it. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Debug Print", Keywords = "Debug Quick Print Simple", DefaultToSelf = "CallingObject"), Category = "Debugging")
	static void DebugPrint(UObject* CallingObject);

	/** Log a quick test message. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Debug Log", Keywords = "Debug Quick Log Simple", DefaultToSelf = "CallingObject"), Category = "Debugging")
	static void DebugLog(UObject* CallingObject);

	/** Print a quick test message on screen. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Debug Screen Log", Keywords = "Debug Quick Screen Log Simple", DefaultToSelf = "CallingObject"), Category = "Debugging")
	static void DebugScreenLog(UObject* CallingObject);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Log Categories
DEBUGLIBRARY_API DECLARE_LOG_CATEGORY_EXTERN(LogDebugFunctionLibrary, Log, All);


// Debug macros

/**
 * @ref https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-class-name-function-name-line-number-of-your-calling-code.html
 */

#define DEBUG_GET_CURR_CLASS_FUNC (FString(__FUNCTION__))
#define DEBUG_GET_CURR_LINE (FString::FromInt(__LINE__))

#define DEBUG_LOG_SIMPLE UE_LOG(LogDebugFunctionLibrary, Error, TEXT("Debug- Simple log."))
#define DEBUG_MESSAGE_SIMPLE if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Debug- Simple message.")))
#define DEBUG_PRINT_SIMPLE DEBUG_LOG_SIMPLE DEBUG_MESSAGE_SIMPLE

#define DEBUG_LOG_SIMPLE_WITH_INFO UE_LOG(LogDebugFunctionLibrary, Error, TEXT("Debug- Simple log with info. || Called at- %s::%s."), *DEBUG_GET_CURR_CLASS_FUNC, *DEBUG_GET_CURR_LINE)
#define DEBUG_MESSAGE_SIMPLE_WITH_INFO if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Debug- Simple message with info. || Called at- %s::%s."), *DEBUG_GET_CURR_CLASS_FUNC, *DEBUG_GET_CURR_LINE))
#define DEBUG_PRINT_SIMPLE_WITH_INFO DEBUG_LOG_SIMPLE_WITH_INFO DEBUG_MESSAGE_SIMPLE_WITH_INFO

#define DEBUG_LOG_CUSTOM_TEXT(text) UE_LOG(LogDebugFunctionLibrary, Error, TEXT("Debug- %s"), *FString(text))
#define DEBUG_MESSAGE_CUSTOM_TEXT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Debug - %s"), *FString(text)))
#define DEBUG_PRINT_CUSTOM_TEXT(text) DEBUG_LOG_CUSTOM_TEXT(text) DEBUG_MESSAGE_CUSTOM_TEXT(text)

#define DEBUG_LOG_CUSTOM_TEXT_WITH_INFO(text) UE_LOG(LogDebugFunctionLibrary, Error, TEXT("Debug- %s || Called at- %s::%s."), *FString(text), *DEBUG_GET_CURR_CLASS_FUNC, *DEBUG_GET_CURR_LINE)
#define DEBUG_MESSAGE_CUSTOM_TEXT_WITH_INFO(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("Debug - %s || Called at- %s::%s."), *FString(text), *DEBUG_GET_CURR_CLASS_FUNC, *DEBUG_GET_CURR_LINE))
#define DEBUG_PRINT_CUSTOM_TEXT_WITH_INFO(text) DEBUG_LOG_CUSTOM_TEXT_WITH_INFO(text) DEBUG_MESSAGE_CUSTOM_TEXT_WITH_INFO(text)


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 * FSoulCubeGameplayTags
 *
 *	Singleton containing native gameplay tags.
 *	Initialize Game play tags in this struct so that they can be easily accessed in native c++ and in engine.
 */
struct FSoulCubeGameplayTags
{
	
private:

	static FSoulCubeGameplayTags GameplayTags;

protected:
	
	/** Function to add a tag and its details
	 *
	 * @param OutTag		The GameplayTag (variable) that to be initialized.
	 * @param TagName		The name of the tag (Ex:- Input.move), the dot operator helps with hierarchy.
	 * @param TagComment	Description of the tag.
	 */
	static void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);
	
	/** Function to add all the initialized variables as tags with its info */
	void AddAllTags(UGameplayTagsManager& Manager);

public:
	
	/** Returns the FSoulCubeGameplayTags singleton object. */
	static FSoulCubeGameplayTags& Get() { return GameplayTags; }

	/** Initialize all the tags to make them available in the game (Should be called before the start of the engine) */
	static void InitializeNativeTags();
	
	/** Helps to find a tag by its name passed as string */
	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);

public:
	
	/** Gameplay Tags Start */

	// Default tag for implementation reference
	FGameplayTag DefaultTag;
	
	/** Gameplay Tags End */
};
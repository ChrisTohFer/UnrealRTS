// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

/**
 * 
 */
class UNREALRTS_API StaticMethods
{
public:

	//Returns the height of the ground at specified position
	//ResultValid = false if there is no ground at the position, or ground was not found
	static float GroundHeightAtPosition(const UWorld* World, FVector Position, bool& ResultValid);

	//Returns the position of the ground at specified position
	//ResultValid = false if there is no ground at the position, or ground was not found
	static FVector GroundLocationAtPosition(const UWorld* World, FVector Position, bool& ResultValid);

};

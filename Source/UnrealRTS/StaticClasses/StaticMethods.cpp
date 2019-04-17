// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticMethods.h"

float StaticMethods::GroundHeightAtPosition(const UWorld * World, FVector Position, bool& ResultValid)
{
	if (World != nullptr)
	{
		//Prepare ray trace to determine ground height
		FHitResult HitResult;
		FVector StartPosition, EndPosition;
		StartPosition = EndPosition = Position;
		StartPosition.Z = -10000.f;
		EndPosition.Z = 10000.f;

		//Create output based on trace result
		if (World->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_WorldStatic))
		{
			ResultValid = true;
			return HitResult.Distance - 10000.f;
		}
	}
	
	ResultValid = false;
	return 0.f;
}

FVector StaticMethods::GroundLocationAtPosition(const UWorld * World, FVector Position, bool & ResultValid)
{
	if (World != nullptr)
	{
		//Prepare ray trace to determine ground height
		FHitResult HitResult;
		FVector StartPosition, EndPosition;
		StartPosition = EndPosition = Position;
		StartPosition.Z = -10000.f;
		EndPosition.Z = 10000.f;

		//Create output based on trace result
		if (World->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_WorldStatic))
		{
			ResultValid = true;
			return HitResult.Location;
		}
	}

	ResultValid = false;
	return FVector::ZeroVector;
}

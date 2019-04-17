// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Squad.h"

/**
 * 
 */
class UnitSelection : public TArray<ASquad*>
{
public:
	UnitSelection();
	~UnitSelection();

	//Find and remove null pointers from the array
	void RemoveNullPointers();
	//Returns the mean position of all selected squads
	FVector GetAveragePosition() const;
	//Order selected units to move to destination and form a line
	void AssignMoveOrder(FVector Destination);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitSelection.h"

UnitSelection::UnitSelection()
{
}

UnitSelection::~UnitSelection()
{
}
//Find and remove null pointers from the array
void UnitSelection::RemoveNullPointers()
{
	int N = Num();
	for (int i = N - 1; i >= 0; --i)
	{
		if (operator[](i) == nullptr)
		{
			RemoveAt(i);
		}
	}
}
//Returns the mean position of all selected squads
FVector UnitSelection::GetAveragePosition() const
{
	int N = Num();
	int NSquads = 0;
	FVector AddedPositions = FVector::ZeroVector;

	//Loop through squads and add positions together
	for (int i = 0; i < N; ++i)
	{
		ASquad* SquadPointer = operator[](i);
		if (SquadPointer != nullptr)
		{
			AddedPositions += SquadPointer->GetActorLocation();
			++NSquads;
		}
	}

	return AddedPositions / static_cast<float>(NSquads);
}


//Class to assist in sorting squads prior to move
class SquadMoveSort
{
public:
	ASquad* Pointer;
	float PerpendicularDistance = 0.f;
};
bool operator<(const SquadMoveSort& A, const SquadMoveSort& B)
{
	return A.PerpendicularDistance < B.PerpendicularDistance;
}

//Order selected units to move to destination and form a line
void UnitSelection::AssignMoveOrder(FVector Destination)
{
	FVector AveragePosition = GetAveragePosition();

	//Get length and angle of move
	FVector Direction; float Distance;
	(Destination - AveragePosition).ToDirectionAndLength(Direction, Distance);

	//Define spread of selected squads
	FVector SpreadVector; float SpreadDistance = 100.f;
	if (Num() > 0 && operator[](0) != nullptr)
	{
		SpreadDistance = operator[](0)->TotalSize().Y + 50.f;
	}
	SpreadVector = Direction * SpreadDistance;
	SpreadVector = SpreadVector.RotateAngleAxis(90.f, FVector::UpVector);
	
	//Create and sort array based on relative positions of squads
	//This sort reduces collisions between the squads when travelling to destination
	TArray<SquadMoveSort> MoveArray = TArray<SquadMoveSort>();
	int N = Num();
	int NSquads = 0;
	for (int i = 0; i < N; ++i)
	{
		ASquad* SquadPointer = operator[](i);
		if (SquadPointer != nullptr)
		{
			MoveArray.Add(SquadMoveSort());
			MoveArray[NSquads].Pointer = SquadPointer;

			FVector SquadDistance = SquadPointer->GetActorLocation() - Destination;
			MoveArray[NSquads].PerpendicularDistance = FVector::DotProduct(SpreadVector, SquadDistance);

			++NSquads;
		}
	}
	MoveArray.Sort();

	//Set destination of each squad
	
	for (int i = 0; i < NSquads; ++i)
	{
		MoveArray[i].Pointer->Destination = Destination + SpreadVector * (i - static_cast<float>(N) / 2.f);
	}
}

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
	RemoveNullPointers();
	if (Num() == 0)
	{
		return;
	}

	FVector AveragePosition = GetAveragePosition();

	//Get length and angle of move
	FVector Direction; float Distance;
	(Destination - AveragePosition).ToDirectionAndLength(Direction, Distance);

	//Define spread of selected squads
	FVector SpreadVector = Direction.RotateAngleAxis(90.f, FVector::UpVector);
	float SelectionWidth = GetSelectionWidth();
	
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
	float RelativeSquadDestination = -SelectionWidth / 2.f + MoveArray[0].Pointer->TotalSize().Y / 2.f;
	for (int i = 0; i < NSquads; ++i)
	{
		MoveArray[i].Pointer->SetDestination(Destination + SpreadVector * RelativeSquadDestination);

		if (i < NSquads - 1)
		{
			RelativeSquadDestination += (MoveArray[i].Pointer->TotalSize().Y + MoveArray[i + 1].Pointer->TotalSize().Y) / 2.f + 50.f;
		}
	}
}

//Get width of all squads lined up`
float UnitSelection::GetSelectionWidth()
{
	float TotalWidth = 0.f;

	for (int i = 0; i < Num(); ++i)
	{
		ASquad* Squad = operator[](i);
		if (Squad != nullptr)
		{
			TotalWidth += Squad->TotalSize().Y + 50.f;
		}
	}

	if (TotalWidth > 0.f)
	{
		TotalWidth -= 50.f;
	}

	return TotalWidth;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Squad.h"
#include "Engine/Blueprint.h"
#include "Infantry.h"
#include "ActorComponents/MovementSquad.h"
#include "StaticClasses/StaticMethods.h"
#include "Engine/World.h"

// Sets default values
ASquad::ASquad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Movement = CreateDefaultSubobject<UMovementSquad>("DestinationMovement");
}

// Called when the game starts or when spawned
void ASquad::BeginPlay()
{
	Super::BeginPlay();

	Destination = GetActorLocation();
	SpawnSquadUnits();
}

//Spawn units to occupy squad and set their relative positions
void ASquad::SpawnSquadUnits()
{
	for (int i = 0; i < Length; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			FVector RelativePosition = SquadMemberRelativePosition(i, j);

			AInfantry* Infantry = GetWorld()->SpawnActor<AInfantry>(UnitBlueprint, GetActorLocation() + GetActorRotation().RotateVector(RelativePosition), FRotator::ZeroRotator);
			Infantry->Squad = this;
			Infantry->SquadRelativePosition = RelativePosition;

			SquadMembers.Add(Infantry);
		}
	}
}

// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	bool ValidCheck;
	FVector GroundLocation = StaticMethods::GroundLocationAtPosition(GetWorld(), GetActorLocation(), ValidCheck);
	if (ValidCheck)
	{
		SetActorLocation(GroundLocation + FVector(0.f, 0.f, SquadHeightAboveGround));
	}
}

//Calculate the position of a squad member from x and y coordinates
FVector ASquad::SquadMemberRelativePosition(int x, int y)
{
	FVector RelativePosition;
	RelativePosition.X = (static_cast<float>(x) - static_cast<float>(Length - 1) / 2.f) * LongitudinalSpacing;
	RelativePosition.Y = (static_cast<float>(y) - static_cast<float>(Width - 1) / 2.f)* HorizontalSpacing;
	RelativePosition.Z = 0.f;

	return RelativePosition;
}

//Return the size of the squad
FVector2D ASquad::TotalSize()
{
	return FVector2D((Length + 1) * LongitudinalSpacing, (Width + 1) * HorizontalSpacing);
}
//Method to set the destination
void ASquad::SetDestination(FVector Value)
{
	Destination = Value;

	SortMemberPositions();
	Movement->SetDestination(Destination);
}


//Class for sorting squad members by position
class SortableInfantry
{
public:
	AInfantry* Infantry;
	float Offset;
};
bool operator<(const SortableInfantry& First, const SortableInfantry Second)
{
	return First.Offset < Second.Offset;
}

//Sort the squad members and assign positions
void ASquad::SortMemberPositions()
{
	//Get travel and perpendicular vectors
	FVector TravelVector = Destination - GetActorLocation();
	TravelVector.Z = 0.f;
	FVector PerpendicularDirection = TravelVector.RotateAngleAxis(90.f, FVector::UpVector);

	//Create array to sort infantry in
	TArray<SortableInfantry> SortableArray;
	
	//Go through squad members, calculate dot product of their position and perpendicular direction and add to array
	for (int i = 0; i < SquadMembers.Num(); ++i)
	{
		SortableInfantry NextInfantry;
		NextInfantry.Infantry = SquadMembers[i];
		
		if (NextInfantry.Infantry != nullptr)
		{
			FVector ActorLocation2D = NextInfantry.Infantry->GetActorLocation();
			ActorLocation2D.Z = 0.f;
			NextInfantry.Offset = FVector::DotProduct(PerpendicularDirection, ActorLocation2D);
			SortableArray.Add(NextInfantry);
		}
	}
	SortableArray.Sort();

	//Assign new positions to the sorted members
	for (int i = 0; i < SortableArray.Num(); i += Length)
	{
		//Create sub array for each column and sort it
		int SubgroupN = FMath::Min(i + Length, SortableArray.Num());
		TArray<SortableInfantry> SubArray;
		for (int j = i; j < SubgroupN; ++j)
		{
			FVector ActorLocation2D = SortableArray[j].Infantry->GetActorLocation();
			ActorLocation2D.Z = 0.f;
			SortableArray[j].Offset = FVector::DotProduct(TravelVector, ActorLocation2D);
			SubArray.Add(SortableArray[j]);
		}
		SubArray.Sort();

		//Assign positions to column members
		int y = i / Length;
		for (int j = 0; j < Length; ++j)
		{
			SubArray[j].Infantry->SquadRelativePosition = SquadMemberRelativePosition(j, y);
		}
	}

}


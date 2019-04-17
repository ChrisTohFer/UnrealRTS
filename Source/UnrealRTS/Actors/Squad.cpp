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
		}
	}
}

// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movement->SetDestination(Destination);
	
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


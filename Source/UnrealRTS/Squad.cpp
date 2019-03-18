// Fill out your copyright notice in the Description page of Project Settings.

#include "Squad.h"
#include "Engine/Blueprint.h"
#include "Infantry.h"
#include "ActorComponents/MovementSquad.h"
#include "StaticClasses/StaticWorldActor.h"
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
	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Length; ++j)
		{
			FVector RelativePosition = SquadMemberRelativePosition(j, i);

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
	
	TPair<bool, FVector> GroundLocation = AStaticWorldActor::GroundLocationAtPosition(GetActorLocation());
	if (GroundLocation.Key)
	{
		SetActorLocation(GroundLocation.Value + FVector(0.f, 0.f, SquadHeightAboveGround));
	}
}

FVector ASquad::SquadMemberRelativePosition(int x, int y)
{
	FVector RelativePosition;
	RelativePosition.X = ((float)x - (float)Width / 2.f)* HorizontalSpacing;
	RelativePosition.Y = ((float)y - (float)Length / 2.f) * LongitudinalSpacing;
	RelativePosition.Z = 0.f;

	return RelativePosition;
}

//Return the size of the squad
FVector2D ASquad::TotalSize()
{
	return FVector2D((Width + 1) * HorizontalSpacing, (Length + 1) * HorizontalSpacing);
}


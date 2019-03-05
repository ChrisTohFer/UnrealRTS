// Fill out your copyright notice in the Description page of Project Settings.

#include "Squad.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"
#include "Infantry.h"
#include "ActorComponents/MovementSquad.h"

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
}

FVector ASquad::SquadMemberRelativePosition(int x, int y)
{
	FVector RelativePosition;
	RelativePosition.X = x * HorizontalSpacing;
	RelativePosition.Y = y * LongitudinalSpacing;
	RelativePosition.Z = 0.f;

	return RelativePosition;
}


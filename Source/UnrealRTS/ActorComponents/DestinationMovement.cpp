// Fill out your copyright notice in the Description page of Project Settings.

#include "DestinationMovement.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDestinationMovement::UDestinationMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDestinationMovement::BeginPlay()
{
	Super::BeginPlay();

	ParentActor = GetOwner();
	SetDestinationToCurrentLocation();
}


// Called every frame
void UDestinationMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If far from destination, move towards it
	FVector Direction = VectorToDestination();
	if (Direction.Size() > DestinationCutoffDistance)
	{
		MoveToDestination(Direction, DeltaTime);
	}
}

void UDestinationMovement::MoveToDestination(FVector Direction, float DeltaTime)
{
	//Implement in derived classes
}

FVector UDestinationMovement::VectorToDestination()
{
	FVector ToDestination = Destination - ParentActor->GetActorLocation();
	ToDestination.Z = 0.f;
	return ToDestination;
}

void UDestinationMovement::SetDestination(FVector NewDestination)
{
	Destination = NewDestination;
	Destination.Z = 0.f;
}

void UDestinationMovement::SetDestinationToCurrentLocation()
{
	SetDestination(ParentActor->GetActorLocation());
}


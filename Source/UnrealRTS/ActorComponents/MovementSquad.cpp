// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementSquad.h"
#include "GameFramework/Actor.h"
#include "math.h"


// Sets default values for this component's properties
UMovementSquad::UMovementSquad()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMovementSquad::MoveToDestination(FVector Direction, float DeltaTime)
{
	//Move actor in direction
	FVector Location = ParentActor->GetActorLocation();
	Location += Direction * (DeltaTime * Velocity / Direction.Size());
	ParentActor->SetActorLocation(Location);

	//Rotate to face direction
	FRotator Rotation = ParentActor->GetActorRotation();
	float Angle = Direction.Rotation().Yaw - Rotation.Yaw;
	float AbsAngle = abs(Angle);
	float AngleChange = DeltaTime * AngularVelocityDegrees;

	if (AbsAngle < AngleChange)
	{
		Angle = 0.f;
	}
	else if (AbsAngle <= 90.f)
	{
		//((Angle > 0.f) - (Angle < 0.f)) is sign function 
		Angle -= ((Angle > 0.f) - (Angle < 0.f)) * AngleChange;
	}
	else if (AbsAngle > 180.f - AngleChange)
	{
		Angle = 180.f;
	}
	else
	{
		Angle += ((Angle > 0.f) - (Angle < 0.f)) * AngleChange;
	}

	Rotation.Yaw = Direction.Rotation().Yaw - Angle;
	ParentActor->SetActorRotation(Rotation);
}

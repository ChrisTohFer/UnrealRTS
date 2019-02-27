// Fill out your copyright notice in the Description page of Project Settings.

#include "Infantry.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Squad.h"


// Sets default values
AInfantry::AInfantry()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set character movement
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = DefaultMaxSpeed;
	Movement->MaxAcceleration = DefaultAcceleration;
	Movement->BrakingDecelerationWalking = DefaultAcceleration;
	
}

// Called when the game starts or when spawned
void AInfantry::BeginPlay()
{
	Super::BeginPlay();
	
	//Set destination to current location
	Destination = GetActorLocation();
}

// Called every frame
void AInfantry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Squad != nullptr)
	{
		Destination = Squad->GetActorLocation() + Squad->GetActorRotation().RotateVector(SquadRelativePosition);
	}
	

	FVector DestinationRelativeVector = GetDestinationRelativeVector();
	if (DestinationRelativeVector.Size2D() > StopRadius)
	{
		MoveTowardsDestination(DestinationRelativeVector);
	}

}

FVector AInfantry::GetDestinationRelativeVector()
{
	FVector RelativeVector = Destination - GetActorLocation();
	RelativeVector.Z = 0.f;

	return RelativeVector;
}

void AInfantry::MoveTowardsDestination(FVector Direction)
{
	SetActorRotation(Direction.ToOrientationQuat());

	AddMovementInput(Direction);
}









/*void AInfantry::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AInfantry::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}*/




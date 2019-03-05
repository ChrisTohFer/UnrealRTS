// Fill out your copyright notice in the Description page of Project Settings.

#include "Infantry.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Squad.h"
#include "ActorComponents/MovementInfantry.h"


// Sets default values
AInfantry::AInfantry()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set character movement
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = DefaultMaxSpeed;
	CharacterMovement->MaxAcceleration = DefaultAcceleration;
	CharacterMovement->BrakingDecelerationWalking = DefaultAcceleration;
	
	Movement = CreateDefaultSubobject<UMovementInfantry>("DestinationMovement");
}

// Called when the game starts or when spawned
void AInfantry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInfantry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set destination of movement component based on squad location and rotation
	if (Squad != nullptr)
	{
		Movement->SetDestination(Squad->GetActorLocation() + Squad->GetActorRotation().RotateVector(SquadRelativePosition));
	}
	
}
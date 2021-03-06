// Fill out your copyright notice in the Description page of Project Settings.

#include "MovementInfantry.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UMovementInfantry::UMovementInfantry()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMovementInfantry::BeginPlay()
{
	Super::BeginPlay();

	ParentCharacter = dynamic_cast<ACharacter*>(ParentActor);
	MoveComponent = ParentCharacter->GetCharacterMovement();
}

void UMovementInfantry::MoveToDestination(FVector Direction, float DeltaTime)
{
	if (ParentCharacter != nullptr)
	{
		ParentCharacter->SetActorRotation(Direction.ToOrientationQuat());
		ParentCharacter->AddMovementInput(Direction);// , Direction.Size() / MoveComponent->MaxWalkSpeed);
	}
}

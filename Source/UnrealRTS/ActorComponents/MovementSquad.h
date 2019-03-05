// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestinationMovement.h"
#include "MovementSquad.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALRTS_API UMovementSquad : public UDestinationMovement
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovementSquad();

protected:
	//The rate at which the squad can turn around in degrees/second
	UPROPERTY(EditAnywhere)
	float AngularVelocityDegrees = 90.f;
	
	//The movement speed of the squad
	UPROPERTY(EditAnywhere)
	float Velocity = 400.f;

	virtual void MoveToDestination(FVector Direction, float DeltaTime) override;
};

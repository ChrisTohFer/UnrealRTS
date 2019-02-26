// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Infantry.generated.h"

UCLASS()
class UNREALRTS_API AInfantry : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInfantry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//Movement

	//Current destination of the unit
	UPROPERTY(EditAnywhere)
	FVector Destination;

protected:
	
	//Return FVector pointing towards destination (excluding z component);
	FVector GetDestinationRelativeVector();

	//Move the unit towards the destination
	void MoveTowardsDestination(FVector Direction);

	//Default movement variables
	float DefaultMaxSpeed = 500.f;
	float DefaultAcceleration = 1000.f;
	
	//How close to destination must unit be before it will stop moving
	UPROPERTY(EditAnywhere)
	float StopRadius = 100.f;


	//

};

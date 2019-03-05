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


	//Reference to parent squad
	UPROPERTY(VisibleAnywhere)
	class ASquad* Squad;
	//Relative position in the squad
	UPROPERTY(VisibleAnywhere)
	FVector SquadRelativePosition;


protected:
	
	//Default movement variables
	float DefaultMaxSpeed = 500.f;
	float DefaultAcceleration = 1000.f;

	UPROPERTY(EditAnywhere)
	class UDestinationMovement* Movement;

};

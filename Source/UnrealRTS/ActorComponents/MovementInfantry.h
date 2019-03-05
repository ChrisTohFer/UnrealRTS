// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DestinationMovement.h"
#include "MovementInfantry.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UNREALRTS_API UMovementInfantry : public UDestinationMovement
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMovementInfantry();

	//
	virtual void BeginPlay() override;

protected:
	//
	ACharacter* ParentCharacter;
	//
	virtual void MoveToDestination(FVector Direction) override;
	
};

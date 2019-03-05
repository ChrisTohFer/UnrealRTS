// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestinationMovement.generated.h"


UCLASS( ClassGroup=(Custom), abstract )
class UNREALRTS_API UDestinationMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestinationMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	//Destination that the actor will attempt to move towards
	UPROPERTY(VisibleInstanceOnly)
	FVector Destination;
	
	//The distance at which the actor will stop approaching
	UPROPERTY(EditAnywhere)
	float DestinationCutoffDistance = 50.f;
	
	//Pointer to actor which this component is attached to
	AActor* ParentActor;

	//Method to move actor towards the destination
	virtual void MoveToDestination(FVector Direction, float DeltaTime);
	//Method to return vector giving difference between actor location and destination
	FVector VectorToDestination();

public:
	//Set a new destination for actor to move towards
	void SetDestination(FVector NewDestination);
	//Set destination to current location
	void SetDestinationToCurrentLocation();

};

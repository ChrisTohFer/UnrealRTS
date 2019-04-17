// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Squad.generated.h"


UCLASS()
class UNREALRTS_API ASquad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASquad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Spawn units to occupy squad and set their relative positions
	void SpawnSquadUnits();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AInfantry> UnitBlueprint;

	//Squad layout
	UPROPERTY(EditAnywhere)
	int Width = 4;
	UPROPERTY(EditAnywhere)
	int Length = 3;
	UPROPERTY(EditAnywhere)
	float HorizontalSpacing = 100.f;
	UPROPERTY(EditAnywhere)
	float LongitudinalSpacing = 100.f;
	UPROPERTY(EditAnywhere)
	float SquadHeightAboveGround = 500.f;
	
	//Calculate the position of a squad member from x and y coordinates
	FVector SquadMemberRelativePosition(int x, int y);

	//Return the size of the squad
	FVector2D TotalSize();

	//Method to set the destination
	UFUNCTION()
	void SetDestination(FVector Value);

protected:
	//Pointer to DestinationMovement component
	UPROPERTY(EditAnywhere)
	class UDestinationMovement* Movement;

	//Destination to move to
	UPROPERTY(EditAnywhere)
	FVector Destination;

	//Array of squad members
	UPROPERTY()
	TArray<AInfantry*> SquadMembers;

	//Sort the squad members and assign positions
	UFUNCTION()
	void SortMemberPositions();

};

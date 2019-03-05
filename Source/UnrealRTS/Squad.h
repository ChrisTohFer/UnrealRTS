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

	
	//Function to determine position of squad member
	FVector SquadMemberRelativePosition(int x, int y);

	UPROPERTY(EditAnywhere)
	class UDestinationMovement* Movement;



	UPROPERTY(EditAnywhere)
	FVector Destination;



};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StaticWorldActor.generated.h"

UCLASS()
class UNREALRTS_API AStaticWorldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaticWorldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Reference to the actor to enable use of inherited AActor methods
	static AStaticWorldActor* WorldActorSingleton;
	
public:
	//Return <true, groundheight> if valid position, else return <false, float>
	static TPair<bool, float> GroundHeightAtPosition(FVector Position);
	//Return <true, groundlocation> if valid position, else return <false, FVector>
	static TPair<bool, FVector> GroundLocationAtPosition(FVector Position);

};

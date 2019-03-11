// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticWorldActor.h"
#include "Engine/World.h"

AStaticWorldActor* AStaticWorldActor::WorldActorSingleton = nullptr;

// Sets default values
AStaticWorldActor::AStaticWorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStaticWorldActor::BeginPlay()
{
	Super::BeginPlay();
	
	WorldActorSingleton = this;
}

//Return <true, groundheight> if valid position, else return <false, float>
TPair<bool, float> AStaticWorldActor::GroundHeightAtPosition(FVector Position)
{
	//Prepare ray trace to determine ground height
	FHitResult HitResult;
	FVector StartPosition, EndPosition;
	StartPosition = EndPosition = Position;
	StartPosition.Z = -10000.f;
	EndPosition.Z = 10000.f;

	//Create output based on trace result
	TPair<bool, float> OutPair;
	if (WorldActorSingleton->GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_WorldStatic))
	{
		OutPair.Key = true;
		OutPair.Value = HitResult.Location.Z;
	}
	else
	{
		OutPair.Key = false;
	}

	return OutPair;
}

//Return <true, groundlocation> if valid position, else return <false, FVector>
TPair<bool, FVector> AStaticWorldActor::GroundLocationAtPosition(FVector Position)
{
	//Prepare ray trace to determine ground height
	FHitResult HitResult;
	FVector StartPosition, EndPosition;
	StartPosition = EndPosition = Position;
	StartPosition.Z = -10000.f;
	EndPosition.Z = 10000.f;

	//Create output based on trace result
	TPair<bool, FVector> OutPair;
	if (WorldActorSingleton->GetWorld()->LineTraceSingleByChannel(HitResult, StartPosition, EndPosition, ECC_WorldStatic))
	{
		OutPair.Key = true;
		OutPair.Value = HitResult.Location;
	}
	else
	{
		OutPair.Key = false;
	}

	return OutPair;
}


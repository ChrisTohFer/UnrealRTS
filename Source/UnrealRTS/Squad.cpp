// Fill out your copyright notice in the Description page of Project Settings.

#include "Squad.h"
#include "Engine/World.h"
#include "Engine/Blueprint.h"
#include "Infantry.h"

// Sets default values
ASquad::ASquad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASquad::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Parameters;
	AInfantry* Infantry = GetWorld()->SpawnActor<AInfantry>(UnitBlueprint, GetActorLocation(), FRotator::ZeroRotator);
	//Parameters.te = UnitBlueprint;
	//GetWorld()->SpawnActor()

}

// Called every frame
void ASquad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


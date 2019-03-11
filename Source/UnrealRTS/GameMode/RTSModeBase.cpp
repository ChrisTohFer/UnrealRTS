// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSModeBase.h"
#include "PlayerControllers/RTSPlayerController.h"
#include "HUDs/RTS_HUD.h"
#include "StaticClasses/StaticWorldActor.h"

//Constructor to set defaults
ARTSModeBase::ARTSModeBase()
{
	
	//
	//DefaultPawnClass = ACameraPawn::StaticClass();

	//
	PlayerControllerClass = ARTSPlayerController::StaticClass();

	//
	HUDClass = ARTS_HUD::StaticClass();

}

void ARTSModeBase::BeginPlay()
{
	//
	GetWorld()->SpawnActor<AStaticWorldActor>();
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "RtsGameMode.h"
#include "PlayerControllers/RTSPlayerController.h"
#include "HUDs/RTS_HUD.h"

ARtsGameMode::ARtsGameMode()
{
	//
	PlayerControllerClass = ARTSPlayerController::StaticClass();

	//
	HUDClass = ARTS_HUD::StaticClass();
}



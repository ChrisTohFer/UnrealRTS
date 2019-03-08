// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSPlayerController.h"
#include "Engine.h"
#include "HUDs/RTS_HUD.h"

//Show cursor
ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
}

//Bind mouse actions
void ARTSPlayerController::BeginPlay()
{
	Hud = Cast<ARTS_HUD>(GetHUD());
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonDown);
	InputComponent->BindAction("LeftMouse", IE_Released, this, &ARTSPlayerController::LeftMouseButtonUp);

	InputComponent->BindAction("RightMouse", IE_Pressed, this, &ARTSPlayerController::RightMouseButtonDown);
	InputComponent->BindAction("RightMouse", IE_Released, this, &ARTSPlayerController::RightMouseButtonUp);
}


void ARTSPlayerController::LeftMouseButtonDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Left down");
	Hud->BoxInitialPosition = Hud->GetCurrentMousePosition();
	Hud->bBoxVisible = true;
}

void ARTSPlayerController::LeftMouseButtonUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Left up");
	Hud->bBoxVisible = false;
}

void ARTSPlayerController::RightMouseButtonDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Right down");
}

void ARTSPlayerController::RightMouseButtonUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Right up");
}

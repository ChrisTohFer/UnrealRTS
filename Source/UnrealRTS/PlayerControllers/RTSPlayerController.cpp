// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSPlayerController.h"
#include "Engine.h"
#include "HUDs/RTS_HUD.h"
#include "Actors/Squad.h"

//Show cursor
ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
}

//Get Hud reference
void ARTSPlayerController::BeginPlay()
{
	Hud = Cast<ARTS_HUD>(GetHUD());
}
//Bind mouse actions
void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &ARTSPlayerController::LeftMouseButtonDown);
	InputComponent->BindAction("LeftMouse", IE_Released, this, &ARTSPlayerController::LeftMouseButtonUp);

	InputComponent->BindAction("RightMouse", IE_Pressed, this, &ARTSPlayerController::RightMouseButtonDown);
	InputComponent->BindAction("RightMouse", IE_Released, this, &ARTSPlayerController::RightMouseButtonUp);
}

//Unit selection begin
void ARTSPlayerController::LeftMouseButtonDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Left down");
	Hud->BoxInitialPosition = Hud->GetCurrentMousePosition();
	Hud->bBoxVisible = true;
}
//Unit selection end
void ARTSPlayerController::LeftMouseButtonUp()
{
	TArray<ASquad*>& SelectedArray = Hud->GetSelectedArray();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Left up, Selected " + FString::FromInt(SelectedArray.Num()));
	Hud->bBoxVisible = false;
}
//
void ARTSPlayerController::RightMouseButtonDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Right down");
}


//Class to describe order
class OrderAction
{
public:
	ASquad* Target;
	FVector Location;
};

//Assign orders to selection
void ARTSPlayerController::RightMouseButtonUp()
{
	//Create order based on context of right click
	FVector MoveDestination;
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	
	OrderAction Order;
	Order.Target = Cast<ASquad>(HitResult.Actor);
	Order.Location = HitResult.Location;

	if (Order.Target != nullptr)
	{
		//Code for attacking/following
	}
	else
	{
		UnitSelection& Selection = Hud->GetSelectedArray();
		Selection.RemoveNullPointers();
		Selection.AssignMoveOrder(Order.Location);
	}
}

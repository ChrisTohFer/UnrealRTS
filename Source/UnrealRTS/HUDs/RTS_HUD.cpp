// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_HUD.h"
#include "GameFramework/PlayerController.h"
#include "Actors/Squad.h"

void ARTS_HUD::DrawHUD()
{
	if (bBoxVisible)
	{
		//Update current position
		BoxCurrentPosition = GetCurrentMousePosition();

		//Set colour of box
		FLinearColor TransparentRed(0.f, 0.f, 1.f, 0.15f);

		//Determine size
		float Width = BoxCurrentPosition.X - BoxInitialPosition.X;
		float Height = BoxCurrentPosition.Y - BoxInitialPosition.Y;

		//Draw box
		DrawRect(TransparentRed, BoxInitialPosition.X, BoxInitialPosition.Y, Width, Height);

		//Fill selected array with squads
		SelectedArray.Empty();
		GetActorsInSelectionRectangle<ASquad>(BoxInitialPosition, BoxCurrentPosition, SelectedArray, true);
	}
}

//Return the current mouse position
FVector2D ARTS_HUD::GetCurrentMousePosition()
{
	float MousePosX, MousePosY;
	GetOwningPlayerController()->GetMousePosition(MousePosX, MousePosY);
	return FVector2D(MousePosX, MousePosY);
}

//Return a reference to selected units array
UnitSelection& ARTS_HUD::GetSelectedArray()
{
	return SelectedArray;
}

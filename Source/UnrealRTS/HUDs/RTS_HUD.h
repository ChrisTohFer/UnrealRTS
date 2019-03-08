// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRTS_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()
	
public:

	virtual void DrawHUD() override;

	//Mouse position at which left mouse is pressed
	FVector2D BoxInitialPosition;
	//Current mouse position (only when left mouse held)
	FVector2D BoxCurrentPosition;
	//Whether box is currently drawn
	bool bBoxVisible = false;

	//Return the current mouse position
	FVector2D GetCurrentMousePosition();

	//
	TArray<class ASquad*>& GetSelectedArray();

protected:

	//
	TArray<class ASquad*> SelectedArray;

	
	
};

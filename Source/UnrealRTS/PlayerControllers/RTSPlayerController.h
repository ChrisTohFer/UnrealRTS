// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRTS_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Show mouse cursor
	ARTSPlayerController();
	
	//Get Hud reference
	virtual void BeginPlay() override;
	//Bind mouse actions
	virtual void SetupInputComponent() override;

	
protected:
	//Reference to the hud
	class ARTS_HUD* Hud;


	//Unit selection begin
	void LeftMouseButtonDown();
	//Unit selection end
	void LeftMouseButtonUp();
	//
	void RightMouseButtonDown();
	//
	void RightMouseButtonUp();

	
};

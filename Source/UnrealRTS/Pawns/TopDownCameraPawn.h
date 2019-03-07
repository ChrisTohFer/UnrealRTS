// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownCameraPawn.generated.h"

UCLASS()
class UNREALRTS_API ATopDownCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATopDownCameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
protected:
	//Billboard as root component
	UPROPERTY(EditAnywhere)
	class UBillboardComponent* BillBoard;
	//Camera component
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	//Movement component
	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	//Camera boom properties
	UPROPERTY(EditAnywhere)
	float BoomLength = 2000.f;
	UPROPERTY(EditAnywhere)
	float BoomLengthMin = 1000.f;
	UPROPERTY(EditAnywhere)
	float BoomLengthMax = 5000.f;
	UPROPERTY(EditAnywhere)
	float BoomAngle = 45.f;
	
	//Camera movement speed
	UPROPERTY(EditAnywhere)
	float ScrollRate = 1000.f;
	UPROPERTY(EditAnywhere)
	float ZoomRateExponential = 1.1f;
	UPROPERTY(EditAnywhere)
	float CameraZoomSpeedModifier = 3.f;
	UPROPERTY(EditAnywhere)
	float CameraZoomSpeedBase = 300.f;

	//Camera moves towards position gradually
	FVector CameraTargetPosition;

	//Sets the height of the actor to the height of the terrain
	void SetActorToTerrainHeight();
	//Sets CameraTargetPosition based on boom length and angle
	void UpdateTargetPosition();
	//Moves the camera towards the target position if not in place
	void UpdateCameraRelativePosition(float DeltaTime);

	//Apply forwards/backwards movement
	void MoveForward(float Value);
	//Apply left/right movement
	void MoveRight(float Value);
	//Apply zoom
	void ZoomIn(float Value);

};

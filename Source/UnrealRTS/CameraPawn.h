// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class UNREALRTS_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//Move forward/back
	void MoveForward(float Value);
	//Move left/right
	void MoveRight(float Value);
	//Move up/down
	void MoveDown(float Value);

	//Camera reference
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
	//Movement reference
	UPROPERTY(EditAnywhere)
	class UFloatingPawnMovement* Movement;

	//Actor height control
	UPROPERTY(EditAnywhere)
	float ActorHeight = 500.f;

	//Camera height control
	UPROPERTY(EditAnywhere)
	float CameraXOffset = -1000.f;
	UPROPERTY(EditAnywhere)
	float CameraHeight = 1000.f;
	UPROPERTY(EditAnywhere)
	float CameraMinHeight = 500.f;
	UPROPERTY(EditAnywhere)
	float CameraMaxHeight = 5000.f;

private:
	//Maintain actor height above terrain
	void MaintainActorHeight();
	//Apply a new CameraHeight value
	void ApplyCameraHeightAndRotation();
};

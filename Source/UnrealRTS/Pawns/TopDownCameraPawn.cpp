// Fill out your copyright notice in the Description page of Project Settings.

#include "TopDownCameraPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/InputComponent.h"
#include "Components/BillboardComponent.h"
#include "Camera/CameraComponent.h"
#include "StaticClasses/StaticWorldActor.h"

// Sets default values
ATopDownCameraPawn::ATopDownCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create billboard
	BillBoard = CreateDefaultSubobject<UBillboardComponent>("RootBillBoard");

	//Create Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	//Create movement component
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingMovement");

}

// Called when the game starts or when spawned
void ATopDownCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//Rotate camera according to boom angle
	Camera->SetRelativeRotation(FRotator::MakeFromEuler(FVector(0.f, -90.f + BoomAngle, 0.f)));
	//Move camera to starting location
	UpdateTargetPosition();
	Camera->SetRelativeLocation(CameraTargetPosition);
}

// Called every frame
void ATopDownCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Maintain height above terrain
	SetActorToTerrainHeight();
	//Scroll camera towards target relative position
	UpdateCameraRelativePosition(DeltaTime);
}

// Called to bind functionality to input
void ATopDownCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATopDownCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATopDownCameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ATopDownCameraPawn::ZoomIn);

}

//Sets the height of the actor to the height of the terrain
void ATopDownCameraPawn::SetActorToTerrainHeight()
{
	TPair<bool, FVector> GroundHeight = AStaticWorldActor::GroundLocationAtPosition(GetActorLocation());
	
	if (GroundHeight.Key)
	{
		SetActorLocation(GroundHeight.Value);
	}
}

void ATopDownCameraPawn::UpdateTargetPosition()
{
	FVector TargetPosition = FVector::UpVector;
	TargetPosition *= BoomLength;
	TargetPosition = TargetPosition.RotateAngleAxis(-BoomAngle, FVector::RightVector);

	CameraTargetPosition = TargetPosition;
}

void ATopDownCameraPawn::UpdateCameraRelativePosition(float DeltaTime)
{
	//Get the distance and direction to the target position
	FVector OffsetDirection;
	float OffsetSize;
	(CameraTargetPosition - Camera->RelativeLocation).ToDirectionAndLength(OffsetDirection, OffsetSize);
	
	//Calculate speed and apply movement to camera
	float CameraSpeed = (CameraZoomSpeedBase + CameraZoomSpeedModifier * OffsetSize) * DeltaTime;
	if (OffsetSize < CameraSpeed)
	{
		Camera->SetRelativeLocation(CameraTargetPosition);
	}
	else
	{
		Camera->SetRelativeLocation(Camera->RelativeLocation + OffsetDirection * CameraSpeed);
	}
}

void ATopDownCameraPawn::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

void ATopDownCameraPawn::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

void ATopDownCameraPawn::ZoomIn(float Value)
{
	BoomLength *= pow(ZoomRateExponential, -Value);
	if (BoomLength < BoomLengthMin)
	{
		BoomLength = BoomLengthMin;
	}
	else if (BoomLength > BoomLengthMax)
	{
		BoomLength = BoomLengthMax;
	}

	UpdateTargetPosition();
}


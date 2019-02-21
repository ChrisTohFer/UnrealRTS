// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "Components/BillboardComponent.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create Billboard to serve as parent
	UBillboardComponent* Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");

	//Create movement component
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	Movement->MaxSpeed = 5000.f;
	Movement->Acceleration = 10000.f;
	Movement->Deceleration = 10000.f;

	//Create and set up camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	ApplyCameraHeightAndRotation();
	/*FVector Facing = {
		1.f,
		0.f,
		-1.f
	};
	FQuat Quaternion = Facing.ToOrientationQuat();
	Camera->SetRelativeRotation(Quaternion);*/

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Maintain the height of the actor above the terrain via raycast
	MaintainActorHeight();
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACameraPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraPawn::MoveRight);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ACameraPawn::MoveDown);
}


//Move forward/back
void ACameraPawn::MoveForward(float Value)
{
	AddMovementInput(FVector::ForwardVector, Value);
}

//Move left/right
void ACameraPawn::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector, Value);
}

//Move Up/down
void ACameraPawn::MoveDown(float Value)
{
	CameraHeight *= powf(1.1f, -Value);
	if (CameraHeight > CameraMaxHeight) {
		CameraHeight = CameraMaxHeight;
	}
	else if (CameraHeight < CameraMinHeight) {
		CameraHeight = CameraMinHeight;
	}

	ApplyCameraHeightAndRotation();
}

//Maintain the height of the actor above the terrain via raycast
void ACameraPawn::MaintainActorHeight()
{
	FHitResult* HitResult = new FHitResult();
	FVector StartTrace = GetActorLocation();
	FVector EndTrace = (-FVector::UpVector * 10000.f) + StartTrace;
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, TraceParams))
	{
		float HeightOffset = HitResult->Distance - ActorHeight;
		SetActorLocation(GetActorLocation() - FVector::UpVector * HeightOffset);
	}
}


void ACameraPawn::ApplyCameraHeightAndRotation()
{
	Camera->SetRelativeLocation(FVector(CameraXOffset, 0.f, CameraHeight - ActorHeight));

	FVector FacingDirection = -Camera->RelativeLocation;
	Camera->SetRelativeRotation(FacingDirection.ToOrientationQuat());
}
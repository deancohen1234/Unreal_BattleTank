// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshairs();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshairs() 
{
	if (!GetControlledTank()) { return; }
	
	FVector hitLocation; //Out parameters

	if (GetSightRayHitLocation(hitLocation)) 
	{		
		GetControlledTank()->AimAt(hitLocation);
	}
}

//get world location through crosshair, true if hit landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find the crosshair position
	int32 viewportSizeX, viewPortSizeY;
	GetViewportSize(viewportSizeX, viewPortSizeY);

	FVector2D ScreenLocation = FVector2D(CrossHairXLocation * viewportSizeX, CrossHairYLocation * viewPortSizeY);
	OutHitLocation = FVector(3.f, 3.f, 3.f);

	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector Direction, FVector & HitLocation) const
{
	FHitResult hitResult;

	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (Direction * AimingRange);

	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		startLocation,
		endLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = hitResult.Location;
		return true;
	}

	HitLocation = FVector(0, 0, 0);
	return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector worldLocation; //for discarding

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, worldLocation, LookDirection);
}
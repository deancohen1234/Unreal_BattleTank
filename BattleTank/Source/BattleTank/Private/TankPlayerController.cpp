// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* tank = GetControlledTank();

	if (tank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is not possessing any Pawn"));
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing %s"), *tank->GetName());
	}
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

		//tell controlled tank to aim at this point
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
		UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *LookDirection.ToString());
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector worldLocation; //for discarding

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, worldLocation, LookDirection);
}
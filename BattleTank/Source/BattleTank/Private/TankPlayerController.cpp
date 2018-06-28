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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
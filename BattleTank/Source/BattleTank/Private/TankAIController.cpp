// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Starting"));

	ATank* tank = GetPossessedTank();

	if (tank == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller is not possessing any pawn"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller is possessing %s"), *tank->GetName());
	}
}

ATank* ATankAIController::GetPossessedTank() const
{
	return Cast<ATank>(GetPawn());
}

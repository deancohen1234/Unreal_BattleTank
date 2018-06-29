// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* tank = GetPossessedTank();

	if (tank == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller is not possessing any pawn"));
		return;
	}

	ATank* playerControlledTank = GetPlayerTank();

	if (playerControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is targeting %s"), *tank->GetName(), *playerControlledTank->GetName());
	}

	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Player Controller not found"));
	}
}

ATank* ATankAIController::GetPossessedTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

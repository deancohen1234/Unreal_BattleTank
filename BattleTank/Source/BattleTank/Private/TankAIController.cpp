// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();

	ATank* tank = GetControlledTank();

	if (tank == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller is not possessing any pawn"));
		return;
	}

	TargetedTank = GetPlayerTank();

	if (TargetedTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is targeting %s"), *tank->GetName(), *TargetedTank->GetName());
	}

	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Player Controller not found"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	if (!TargetedTank) { return; }
	if (!GetControlledTank()) { return; }

	GetControlledTank()->AimAt(TargetedTank->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

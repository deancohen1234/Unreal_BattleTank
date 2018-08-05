// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank) { return; }
	if (!ControlledTank) { return; }

	//Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in centers

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}

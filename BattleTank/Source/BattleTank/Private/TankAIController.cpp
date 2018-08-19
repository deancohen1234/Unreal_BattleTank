// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

//Depends on movement component via pathfinding system

void ATankAIController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank)) { return; }
	if (!ensure(AimingComponent)) {return;}
	if (!ensure(ControlledTank)) { return; }

	//Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in centers

	AimingComponent->SetAimingLocation(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}

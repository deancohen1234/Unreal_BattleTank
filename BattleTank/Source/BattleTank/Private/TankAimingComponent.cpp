// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetAimingLocation(FVector location, float speed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		location,
		speed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	//calculate the outlaunchvelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//turn aim direction into a rotation for the barrel
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();

	auto DeltaRotator = AimDirectionRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("Aim Direction Rotation is %s"), *AimDirectionRotator.ToString());
	//apply rotation and move the barrel over time
}


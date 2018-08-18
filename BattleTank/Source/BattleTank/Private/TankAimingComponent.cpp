// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* _Barrel, UTankTurret* _Turret) 
{
	Barrel = _Barrel;
	Turret = _Turret;
}

void UTankAimingComponent::SetAimingLocation(FVector location)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		location,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	//calculate the outlaunchvelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveGunTowards(AimDirection);
	}
	else 
	{
		//no solution currently
	}
}

void UTankAimingComponent::MoveGunTowards(FVector AimDirection)
{
	if (!ensure(Barrel || Turret)) { return; }

	//turn aim direction into a rotation for the barrel
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimDirectionRotator = AimDirection.Rotation();

	auto DeltaRotator = AimDirectionRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Yaw(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime >= ReloadTimeInSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("Firing"));

	if (!ensure(Barrel || ProjectileBlueprint)) { return; }

	if (isReloaded) 
	{
		FVector location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator rotation = Barrel->GetSocketRotation(FName("Projectile"));

		//spawn projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, location, rotation);

		projectile->Launch(LaunchSpeed); //TODO Get rid of the magic number and firing functionality in the tank altogether;
		LastFireTime = FPlatformTime::Seconds();
	}
}


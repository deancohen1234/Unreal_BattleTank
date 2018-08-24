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

void UTankAimingComponent::BeginPlay() 
{
	//so that first fire is after initial reload
	LastFireTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

}

void UTankAimingComponent::Initialize(UTankBarrel* _Barrel, UTankTurret* _Turret)
{
	Barrel = _Barrel;
	Turret = _Turret;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) 
{
	float time = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	if (AmmoCount <= 0) 
	{
		FiringState = EFiringStatus::NoAmmo;
	}
	else if ((time - LastFireTime) < ReloadTimeInSeconds) 
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) 
	{
		FiringState = EFiringStatus::Aiming;
	}
	else 
	{
		FiringState = EFiringStatus::Locked;
	}

}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmoCount() const 
{
	return AmmoCount;
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if (!ensure(Barrel)) { return false; }

	bool BarrelIsMoving = false;

	BarrelIsMoving = Barrel->GetForwardVector().Equals(AimDirection, 0.01f);

	return !BarrelIsMoving;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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

	if (DeltaRotator.Yaw >= 180.0f) 
	{
		DeltaRotator.Yaw = -360 + DeltaRotator.Yaw;
	}
	else if (DeltaRotator.Yaw <= -180.0f) 
	{
		DeltaRotator.Yaw = 360.0f + DeltaRotator.Yaw;
	}

	Turret->Yaw(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{

	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		FVector location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator rotation = Barrel->GetSocketRotation(FName("Projectile"));

		//spawn projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, location, rotation);

		projectile->Launch(LaunchSpeed); //TODO Get rid of the magic number and firing functionality in the tank altogether;
		LastFireTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());

		AmmoCount--;
	}
}


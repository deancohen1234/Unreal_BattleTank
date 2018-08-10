// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank Construction C++"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP beginplay to run
	
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank Begin Play C++"));
}

void ATank::AimAt(FVector hitLocation) 
{
	if (!TankAimingComponent) { return;	}
	TankAimingComponent->SetAimingLocation(hitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime >= ReloadTimeInSeconds);

	if (Barrel && isReloaded) 
	{
		FVector location = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator rotation = Barrel->GetSocketRotation(FName("Projectile"));

		//spawn projectile
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, location, rotation);

		projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}


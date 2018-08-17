// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP beginplay to run
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

		projectile->Launch(3000); //TODO Get rid of the magic number and firing functionality in the tank altogether;
		LastFireTime = FPlatformTime::Seconds();
	}
}


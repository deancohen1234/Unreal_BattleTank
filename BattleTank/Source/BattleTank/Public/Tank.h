// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();
	
private:
	// Sets default values for this pawn's properties

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	//local reference to barrel for spawning projectile
	UTankBarrel* Barrel = nullptr;
	double LastFireTime = 0;


	ATank();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

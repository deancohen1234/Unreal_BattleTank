// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

/**
*
*/
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//start the tank moving the barrel so that  a shot would hit where
	// the crosshairs interects the world
	ATank * GetControlledTank() const;
	void AimTowardsCrosshairs();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
};

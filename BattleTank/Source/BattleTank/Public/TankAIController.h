// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	//in seconds
	UPROPERTY(EditAnywhere)
	float FireRate = 3.0f;
	
private:

	ATank * TargetedTank = nullptr;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

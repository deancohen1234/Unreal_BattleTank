// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Yaw(float Speed) 
{
	Speed = FMath::Clamp(Speed, -1.0f, 1.0f);
	float YawAmount = RelativeRotation.Yaw + (TurretSpinSpeed * Speed * GetWorld()->GetDeltaSeconds());

	FRotator NewRotation = FRotator(0, YawAmount, 0);
	SetRelativeRotation(NewRotation);
}



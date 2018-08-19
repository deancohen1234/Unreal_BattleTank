// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle) 
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

void UTankTrack::BeginPlay() 
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//Calculate slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CounterForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // /2 because 2 tracks
	TankRoot->AddForce(CounterForce);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) 
{
	UE_LOG(LogTemp, Warning, TEXT("Tracks Hitting"));
}


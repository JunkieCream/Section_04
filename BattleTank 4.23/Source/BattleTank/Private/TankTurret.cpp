// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::TurretRotate(float RelativeSpeed)
{
	if (FMath::Abs(RelativeSpeed) > 180)
	{
		RelativeSpeed = -RelativeSpeed;
	}
	RelativeSpeed = FMath::Clamp<float>((RelativeSpeed), -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}
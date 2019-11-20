// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	GetSightHitLocation(HitLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
}

bool ATankPlayerController::GetSightHitLocation(FVector& out_HitLocation)
{
	FVector PlayerTargetDirection;
	FVector PlayerCameraLocation;
	
	GetLookDirection(PlayerCameraLocation, PlayerTargetDirection);

	if (GetLookVectorHitLocation(out_HitLocation, PlayerCameraLocation, PlayerTargetDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Aim Direction: %s"), *out_HitLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Not hitting anything"));
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector &out_PlayerCameraLocation, FVector& out_PlayerTargetDirection)
{
	//Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//Deprojecting crosshair to the world
	FVector PlayerCameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, PlayerCameraLocation, out_PlayerTargetDirection);

	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector &out_HitLocation, FVector PlayerCameraLocation, FVector PlayerTargetDirection)
{
	FHitResult OutHit;

	out_HitLocation = PlayerCameraLocation + PlayerTargetDirection * LineTraceRange;

	DrawDebugLine(GetWorld(), PlayerCameraLocation, out_HitLocation, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	if (GetWorld()->LineTraceSingleByChannel(OutHit, PlayerCameraLocation, out_HitLocation, ECC_Visibility))
	{
		if (OutHit.bBlockingHit)
		{
			out_HitLocation = OutHit.Location;
			return true;
		}
		//else {return false;}
	}
	
	return false;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("You don't posses a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("You posses: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}


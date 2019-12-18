// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Parameter
	FVector PlayerTargetDirection; // Out Parameter
	FVector PlayerCameraLocation;// Out Parameter

	GetLookDirection(PlayerCameraLocation, PlayerTargetDirection);

	if (GetLookVectorHitLocation(HitLocation, PlayerCameraLocation, PlayerTargetDirection))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetLookDirection(FVector &out_PlayerCameraLocation, FVector& out_PlayerTargetDirection)
{
	//Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//Deprojecting crosshair to the world
	//FVector PlayerCameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, out_PlayerCameraLocation, out_PlayerTargetDirection);

	return true;
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector &out_HitLocation, FVector PlayerCameraLocation, FVector PlayerTargetDirection)
{
	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	//Line tracing end
	out_HitLocation = PlayerCameraLocation + PlayerTargetDirection * LineTraceRange;

	//Check if line hit anything
	if (GetWorld()->LineTraceSingleByChannel(OutHit, PlayerCameraLocation, out_HitLocation, ECC_Visibility))
	{
		if (OutHit.bBlockingHit)
		{
			out_HitLocation = OutHit.Location;
			return true;
		}
	}
	
	return false;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::FoundAimingComponent(UTankAimingComponent* AimCompRef) const
{
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}


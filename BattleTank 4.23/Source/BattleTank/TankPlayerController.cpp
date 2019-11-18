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
	//Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY* CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *ScreenLocation.ToString());

	/*FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewLocation,
		OUT PlayerViewRotation
	);

	out_HitLocation = PlayerViewLocation + PlayerViewRotation.Vector()*1000.f;
	
	if (GetWorld()->LineTraceSingleByChannel(OutHit, PlayerViewLocation, out_HitLocation, ECC_Visibility, CollisionParams))
	{
		return true;
	}
	else 
	{ 
		return false; 
	}*/

	return true;
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


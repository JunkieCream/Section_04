// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAiming = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(TankAiming)){ FoundAimingComponent(TankAiming);}
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto ControlledTank = Cast<ATank>(GetPawn());
		if (!ensure(ControlledTank)) { return; }

		// Subscribe our local method to the tank's death event
		ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossedTankDeath);
	}
}


void ATankPlayerController::OnPossedTankDeath()
{
	//auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("My Tank is dead"));
	StartSpectatingOnly();
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!ensure(TankAiming)) { return; }

	FVector HitLocation; // Out Parameter
	FVector PlayerTargetDirection; // Out Parameter
	FVector PlayerCameraLocation;// Out Parameter

	GetLookDirection(PlayerCameraLocation, PlayerTargetDirection);

	if (GetLookVectorHitLocation(HitLocation, PlayerCameraLocation, PlayerTargetDirection))
	{
		TankAiming->Aiming(HitLocation);
	}
}

bool ATankPlayerController::GetLookDirection(FVector &out_PlayerCameraLocation, FVector& out_PlayerTargetDirection)
{
	//Find crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	//Deprojecting crosshair to the world
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
	if (GetWorld()->LineTraceSingleByChannel(OutHit, PlayerCameraLocation, out_HitLocation, ECC_Camera))
	{
		if (OutHit.bBlockingHit)
		{
			out_HitLocation = OutHit.Location;
			return true;
		}
	}
	else
	{
		out_HitLocation = FVector(0, 0, 0);
		return true;
	}
	
	return false;
}

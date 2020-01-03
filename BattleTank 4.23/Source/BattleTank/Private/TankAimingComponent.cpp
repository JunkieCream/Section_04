// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "..\Public\TankAimingComponent.h"
#include "Projectile.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet || TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	LastFireTime = FPlatformTime::Seconds() - ReloadTimeInSeconds;
}

void UTankAimingComponent::Aiming(FVector HitLocation)
{
	if (!ensure(Barrel)) {return;}
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName ("Projectile"));

	
	if (HitLocation != FVector(0,0,0))
	{
		
		if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
		{
			//Calculate launch velocity
			auto AimDirection = LaunchVelocity.GetSafeNormal();
			MoveTurret(LaunchVelocity);
		}
		else
		{
			auto Time = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution"), Time);
		}
	}

	CheckFiringState(LaunchVelocity, HitLocation);
	
}

//Receive aim direction and rotate barrel with FRotator to that direction
void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	//Difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->TurretRotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (FiringState != EFiringState::Reloading)
	{
		//Spawn projectile at the socket location of barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::CheckFiringState(FVector AimDirection, FVector HitLocation)
{
	auto SquareSum = (AimDirection.X * AimDirection.X) + (AimDirection.Y * AimDirection.Y) + (AimDirection.Z * AimDirection.Z);
	float Scale = 1 / sqrt(SquareSum);
	AimDirection = FVector(AimDirection.X * Scale, AimDirection.Y * Scale, AimDirection.Z * Scale);
	
	if (HitLocation != FVector(0, 0, 0))
	{
		if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
		{
			if (Barrel->GetForwardVector().Equals(AimDirection, 0.01))
			{
				FiringState = EFiringState::Aiming;
			}
			else
			{
				FiringState = EFiringState::Moving;
			}

		}
		else
		{
			FiringState = EFiringState::Reloading;
		}
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	
	return;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declacration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Sets default values for this component's properties
	UTankAimingComponent();

	//Called from Tank itself
	void Aiming(FVector HitLocation);

	//Rotate turret and barrel on axises
	void MoveTurret(FVector AimDirection);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)	
	EFiringState FiringState = EFiringState::Aiming;

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	/// Fire properties
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

};

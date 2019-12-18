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
	void Aiming(FVector HitLocation, float LaunchSpeed);

	//Rotate turret and barrel on axises
	void MoveTurret(FVector AimDirection);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)	
	EFiringState FiringState = EFiringState::Reloading;

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};

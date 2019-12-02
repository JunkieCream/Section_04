// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward declacration
class UTankTurret; //Forward declacration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Finding tank's barrel
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//Finding tank's turret
	void SetTurretReference(UTankTurret* TurretToSet);

	//Called from Tank itself
	void Aiming(FVector HitLocation, float LaunchSpeed);

	//Rotate turret and barrel on axises
	void MoveTurret(FVector AimDirection);

protected:

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};

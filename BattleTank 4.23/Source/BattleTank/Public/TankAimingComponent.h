// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; //Forward declacration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Finding tank's barrel
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//Called from Tank itself
	void Aiming(FVector HitLocation, float LaunchSpeed);

	//Rotate barrel on axises
	void MoveBarrel(FVector AimDirection);

protected:

private:	
	UTankBarrel* Barrel = nullptr;
};

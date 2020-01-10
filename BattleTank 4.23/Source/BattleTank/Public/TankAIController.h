// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPlayerController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

private:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossedTankDeath();

	//how close AI tank can get to the player
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 5000.f;

	UTankAimingComponent* TankAiming = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	void BeginPlay() override;
	
	ATank* GetControlledTank() const;

	// Aim barrel of tank to crosshair
	void AimTowardCrosshair();

	bool GetLookVectorHitLocation(FVector& out_HitLocation, FVector PlayerCameraLocation, FVector PlayerTargetDirection);

	bool GetLookDirection(FVector& out_PlayerCameraLocation, FVector& PlayerTargetDirection);

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
};

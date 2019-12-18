// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	//BlueprintImplementableEvent
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef) const;

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Aim barrel of tank to crosshair
	void AimTowardCrosshair();

	bool GetLookVectorHitLocation(FVector& out_HitLocation, FVector PlayerCameraLocation, FVector PlayerTargetDirection);

	bool GetLookDirection(FVector& out_PlayerCameraLocation, FVector& PlayerTargetDirection);

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "..\Public\TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAiming = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAiming)){ UE_LOG(LogTemp, Warning, TEXT("No tank aiming component"));}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	if (PlayerTank)
	{
		TankAiming->Aiming(PlayerTank->GetActorLocation());
		TankAiming->Fire();
	}
}
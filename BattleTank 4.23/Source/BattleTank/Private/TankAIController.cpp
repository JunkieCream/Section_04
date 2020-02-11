// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "..\Public\TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAiming = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAiming)){ UE_LOG(LogTemp, Warning, TEXT("No tank aiming component"));}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank) { return; }

	// Subscribe our local method to the tank's death event
	ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	if (PlayerTank)
	{
		TankAiming->Aiming(PlayerTank->GetActorLocation());
		if (TankAiming->GetFiringState() == EFiringState::Aiming)
		{
			TankAiming->Fire();
		}
	}
}

void ATankAIController::OnPossedTankDeath()
{
	//auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("My Tank is dead"));
	if (!GetPawn()) {
		UE_LOG(LogTemp, Warning, TEXT("No tank to die"))
		return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

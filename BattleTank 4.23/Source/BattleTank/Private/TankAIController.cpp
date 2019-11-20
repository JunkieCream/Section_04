// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "..\Public\TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI don't posses a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI posses: %s"), *ControlledTank->GetName());
	}

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI don't aim at player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI aimed at %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}



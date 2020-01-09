// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int32 DamageToApply = FPlatformMath::RoundToInt(DamageAmount);
	DamageToApply = FMath::Clamp<int32>(DamageToApply, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health is: %i"), CurrentHealth);

	return 0.0f;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "TankProjectileMoving.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMoving = CreateDefaultSubobject<UTankProjectileMoving>(FName("Projectile Moving"));
	ProjectileMoving->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile fired"));
	ProjectileMoving->SetVelocityInLocalSpace(FVector::ForwardVector* LaunchSpeed);
	ProjectileMoving->Activate();
}
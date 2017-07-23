// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
			)
		)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::RotateTurretTowards(FVector RotateDirection)
{
	FRotator TurretRotator = Barrel->GetForwardVector().Rotation();
	FRotator RotateAsRotator = RotateDirection.Rotation();
	FRotator DeltaRotator = RotateAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);
}


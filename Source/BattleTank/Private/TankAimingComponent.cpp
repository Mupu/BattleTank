// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
	if (!Turret) { return; }
	HitLocation = HitLocation + 0.01f; // Negates the floating point error when HitLocation.Z = 0
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
		MoveTurretAndBarrelTowards(OutLaunchVelocity);
		// TODO turn turret no matter raycast hits something or not
		//UE_LOG(LogTemp, Warning, TEXT(""));
	}
	else
	{
		// TODO turn barrel to natural position
	}
}

void UTankAimingComponent::MoveTurretAndBarrelTowards(FVector LaunchVelocity)
{
	LaunchVelocity = LaunchVelocity.GetSafeNormal();

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = LaunchVelocity.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);
	Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
}


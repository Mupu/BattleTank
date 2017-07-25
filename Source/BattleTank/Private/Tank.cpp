#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::Initialise(UTankBarrel* BarrelToSet, UTankAimingComponent* TankAimingComponentToSet, UTankMovementComponent* TankMovementComponentToSet)
{
	if (!BarrelToSet || !TankAimingComponentToSet || !TankMovementComponentToSet) { return; }
	Barrel = BarrelToSet;
	TankAimingComponent = TankAimingComponentToSet;
	TankMovementComponent = TankMovementComponentToSet;
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && bIsReloaded) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


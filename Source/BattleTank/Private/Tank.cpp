#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	CreateDefaultSubobject<UTankMovementComponent>(FName("Tank Movement Component"));
}

void ATank::SetTankAimingComponentReference(UTankAimingComponent * TankAimingComponentToSet)
{
	if (!TankAimingComponentToSet) { return; }
	TankAimingComponent = TankAimingComponentToSet;
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	if (TankAimingComponent)
	{
		TankAimingComponent->SetBarrelReference(BarrelToSet);
	}
	Barrel = BarrelToSet;
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


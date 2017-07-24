#include "Public/Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

void ATank::Fire()
{
	if (!Barrel) { return; }

	GetWorld()->SpawnActor<AProjectile>(
		ProjectileBP,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	if (!TankAimingComponent) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	if (!TankAimingComponent)
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s: NoTankAimingComponentFound"), *GetName());
		return; 
	}
	TankAimingComponent->SetTurretReference(TurretToSet);
}

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


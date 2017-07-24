#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s in %s:Unable to set Barrel!"), *GetName(), *GetOwner()->GetName());
		return; 
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("%s in %s:Unable to set Barrel!"), *GetName(), *GetOwner()->GetName());
		return;
	}
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	HitLocation = HitLocation + 0.01f; // Negates the floating point error when HitLocation.Z = 0
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Find all actor instances to ignore and ignore them
	TArray<AActor*> FoundActorsToIgnore;
	for (TSubclassOf<AActor> Actor : ActorsToIgnoreForTrace)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Actor, FoundActorsToIgnore);
	}
	
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::TraceFullPath,
		FCollisionResponseParams(ECollisionResponse::ECR_Block),
		FoundActorsToIgnore,
		false
		)
	)
	{
		OutLaunchVelocity = OutLaunchVelocity.GetSafeNormal();
		FRotator Rotator = Barrel->GetForwardVector().Rotation(); 
		FRotator AimAsRotator = OutLaunchVelocity.Rotation();
		FRotator DeltaRotator = AimAsRotator - Rotator;
		Barrel->Elevate(DeltaRotator.GetNormalized().Pitch);
		Turret->Rotate(DeltaRotator.GetNormalized().Yaw);
	}
	else
	{
		// Player Controlled Tank
		ATank* TankTheComponentSitsIn = Cast<ATank>(GetOwner());
		if (TankTheComponentSitsIn->IsPlayerControlled())
		{
			// Move the barrel down to it's natural position when no target
			Barrel->Elevate(-1);

			// Get PlayerViewPointRotation
			APlayerController* PlayerController = Cast<APlayerController>(TankTheComponentSitsIn->Controller);
			FVector PlayerViewPointLocation; // To discard
			FRotator PlayerViewPointRotation;
			PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
			FRotator DeltaRotation = PlayerViewPointRotation - Turret->GetForwardVector().Rotation();

			// Move the barrel to the PlayerViewPortsRotation when no target
			Turret->Rotate(DeltaRotation.GetNormalized().Yaw);
		}
		else
		{
			// AI Controlled Tank
			// Move the barrel down to it's natural position when no target
			Barrel->Elevate(-1);
		}
	}
}


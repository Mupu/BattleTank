#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = Setup) TSubclassOf<AProjectile> ProjectileBP;

	UFUNCTION(BlueprintCallable) void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable) void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable) void Fire();

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Firing) float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing) float ReloadTimeInSeconds = 1;

	double LastFireTime = 0;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UTankBarrel* Barrel = nullptr;
};

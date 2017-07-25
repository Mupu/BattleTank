#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable) void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable) void SetTankAimingComponentReference(UTankAimingComponent* TankAimingComponentToSet);

	UFUNCTION(BlueprintCallable) void Fire();

protected:
	UPROPERTY(BlueprintReadOnly) UTankMovementComponent* TankMovementComponent = nullptr;

private:
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Setup) TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Firing) float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing) float ReloadTimeInSeconds = 1;

	double LastFireTime = 0;

	UTankAimingComponent* TankAimingComponent = nullptr;

	UTankBarrel* Barrel = nullptr;
};

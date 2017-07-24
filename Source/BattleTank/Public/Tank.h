#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable) void Fire();

	UFUNCTION(BlueprintCallable) void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable) void SetTurretReference(UTankTurret* TurretToSet);

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	ATank();

	UPROPERTY(EditAnywhere, Category = Firing) float LaunchSpeed = 4000;
};

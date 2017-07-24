#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation, float LaunchSpeed);

private:
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = Setup) TArray<TSubclassOf<AActor>> ActorsToIgnoreForTrace;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
};

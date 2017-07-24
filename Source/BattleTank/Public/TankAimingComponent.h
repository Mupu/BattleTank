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
	void AimAt(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable) void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable) void SetTurretReference(UTankTurret* TurretToSet);

private:
	UTankAimingComponent();

	UPROPERTY(EditDefaultsOnly, Category = Setup) TArray<TSubclassOf<AActor>> ActorsToIgnoreForTrace;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;
};

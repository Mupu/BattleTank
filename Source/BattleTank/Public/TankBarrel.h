#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UTankBarrel();

	UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxDegreesPerSecond = 5;

	UPROPERTY(EditDefaultsOnly, Category = Setup) float MaxElevationDegrees = 35;

	UPROPERTY(EditDefaultsOnly, Category = Setup) float MinElevationDegrees = 0;
};

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
	UPROPERTY(EditAnywhere) float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere) float MaxElevationDegrees = 35;

	UPROPERTY(EditAnywhere) float MinElevationDegrees = 0;

	UTankBarrel();
};

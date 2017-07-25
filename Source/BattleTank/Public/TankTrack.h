#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION (BlueprintCallable, Category = Input) void SetThrottle(float Throttle);

private:
	// Max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup) float TrackMaxDrivingForce = 500000;
};

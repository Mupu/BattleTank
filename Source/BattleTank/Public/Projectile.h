#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	void LaunchProjectile(float Speed);

private:	
	AProjectile();

	//virtual void BeginPlay() override;
	
	//virtual void Tick(float DeltaTime) override;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

public:	
	AProjectile();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};

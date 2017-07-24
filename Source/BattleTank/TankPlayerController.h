// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup) float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Setup) float CrossHairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly, Category = Setup) int LineTraceRange = 1000000;

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetScreenPointRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;
};

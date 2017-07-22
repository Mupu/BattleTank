// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogActor, Error, TEXT("Player not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("Player possessing tank: %s"), *GetControlledTank()->GetName());
	}
}

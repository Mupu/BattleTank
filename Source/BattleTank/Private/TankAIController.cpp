// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogActor, Error, TEXT("AI not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("AI possessing tank: %s"), *GetControlledTank()->GetName());
	}
}

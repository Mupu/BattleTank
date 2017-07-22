// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerPawn)
	{
		return Cast<ATank>(PlayerPawn);
	}
	return nullptr;
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

	if (!GetPlayerTank())
	{
		UE_LOG(LogActor, Error, TEXT("No PlayerTank found!"));
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("Found PlayerTank: %s"), *GetPlayerTank()->GetName());
	}
}

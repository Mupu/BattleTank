// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "DrawDebugHelpers.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogActor, Error, TEXT("Player not possessing a tank!"));
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation( ViewPortSizeX * CrossHairXLocation,  ViewPortSizeY * CrossHairYLocation );

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return (GetLookVectorHitLocation(LookDirection, OutHitLocation));
	}
	else
	{
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return	DeprojectScreenPositionToWorld(ScreenLocation.X, 
		ScreenLocation.Y, 
		OUT CameraWorldLocation, 
		OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 1.f, 0.f, 0.5f);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}

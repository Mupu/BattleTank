// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
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
	// Default set to aimpoint where it definitely cant reach
	FVector HitLocation{ NAN, NAN, NAN };
	// Set HitLocation of point you looking at, if posible
	GetScreenPointRayHitLocation(HitLocation);
	GetControlledTank()->AimAt(HitLocation);
	
}

bool ATankPlayerController::GetScreenPointRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation( ViewPortSizeX * CrossHairXLocation,  ViewPortSizeY * CrossHairYLocation );
	FVector OutLookDirection;
	FVector CameraWorldLocation; // To be discarded
	// Calculate direction we are looking at through the point of the screen
	if (DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraWorldLocation,
		OutLookDirection))
	{
		return (GetLookVectorHitLocation(OutLookDirection, OutHitLocation));
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FCollisionQueryParams IgnoredActors;
	IgnoredActors.AddIgnoredActor(GetPawn()); //TODO ignore projectile

	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	// RayCast return first HitResult Location with IgnoreSelf on true
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		IgnoredActors
		)
		)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%s"), *HitResult.GetActor()->GetName()));
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}

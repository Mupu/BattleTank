#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Camera/PlayerCameraManager.h"

void ATankPlayerController::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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

// Calculate the direction you are looking at through a point of the screen
bool ATankPlayerController::GetScreenPointRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation( ViewPortSizeX * CrossHairXLocation,  ViewPortSizeY * CrossHairYLocation );
	FVector OutLookDirection;
	FVector CameraWorldLocation; // To be discarded
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

	// Find all actor instances to ignore and ignore them
	TArray<AActor*> FoundActorsToIgnore;
	for (TSubclassOf<AActor> Actor : ActorsToIgnoreForTrace)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Actor, FoundActorsToIgnore);
	}
	IgnoredActors.AddIgnoredActors(FoundActorsToIgnore);
	// Ignore self
	IgnoredActors.AddIgnoredActor(GetPawn());

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
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}

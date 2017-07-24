#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Aim and fire at the player
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	APawn* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank && ControlledTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}

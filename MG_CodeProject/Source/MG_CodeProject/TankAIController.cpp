// Copyright Marett Creative Labs

#include "MG_CodeProject.h"
#include "Tank.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank))
	{
		// TODO Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);


		// Aim at Player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		ControlledTank->Fire();
	}

}



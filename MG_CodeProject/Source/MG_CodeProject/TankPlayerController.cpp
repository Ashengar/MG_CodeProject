// Fill out your copyright notice in the Description page of Project Settings.

#include "MG_CodeProject.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possessing"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessed: %s"), *(ControlledTank->GetName()));
	}
	
}

void  ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get world location through linetrace
	// If hits landscape
	// Tank to aim at this point
}
// Copyright Marett Creative Labs

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class MG_CODEPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	float AcceptanceRadius = 3000;

};

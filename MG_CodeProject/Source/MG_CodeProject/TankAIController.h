// Copyright Marett Creative Labs

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"


/**
 * 
 */
UCLASS()
class MG_CODEPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close AI tank can get to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;
	
private:	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	
};

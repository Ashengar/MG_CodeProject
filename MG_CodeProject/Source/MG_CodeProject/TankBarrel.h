// Copyright Marett Creative Labs

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MG_CODEPROJECT_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 20;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = -3;
};

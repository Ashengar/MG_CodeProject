#pragma once
#include "Vehicles/WheeledVehicleMovementComponent4W.h"
#include "Engine.h"
#include "WheeledVehicleMovementComponent16W.generated.h"

UCLASS()
class VEHICLESPLUGIN_API UWheeledVehicleMovementComponent16W : public UWheeledVehicleMovementComponent4W
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR
		virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyCangedEvent) override;
#endif

protected:

#if WITH_VEHICLE
	//Setup All vehicle Components.
	virtual void SetupVehicle() override;

	//Tick Vehicle Physics.
	virtual void UpdateSimulation(float DeltaTime) override;

#endif
	//Setup engine properties on spawn.
	void UpdateEngineSetup(const FVehicleEngineData& NewEngineSetup);
	//Setup transmission propersties on spawn.
	void UpdateTransmissionSetup(const FVehicleTransmissionData& NewGearSetup);

};
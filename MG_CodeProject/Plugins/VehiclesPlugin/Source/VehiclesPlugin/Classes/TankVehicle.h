/*
	Required for Tank Vehicle Blueprint Setup.
	Only overrides movement component.
*/
#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponentTank.h"
#include "TankVehicle.generated.h"
class UWheeledVehicleMovementComponentTank;

UCLASS()
class VEHICLESPLUGIN_API ATankVehicle : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()

};

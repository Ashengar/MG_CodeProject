/*
	Required for Vehicle 10W Blueprint Setup.
	Only overrides movement component.
*/
#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent10W.h"
#include "WheeledVehicle10W.generated.h"
class UWheeledVehicleMovementComponent10W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle10W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
};
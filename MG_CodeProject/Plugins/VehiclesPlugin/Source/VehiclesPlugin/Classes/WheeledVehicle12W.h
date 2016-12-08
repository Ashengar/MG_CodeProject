/*
	Required for Vehicle 12W Blueprint Setup.
	Only overrides movement component.
*/
#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent12W.h"
#include "WheeledVehicle12W.generated.h"
class UWheeledVehicleMovementComponent12W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle12W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
};
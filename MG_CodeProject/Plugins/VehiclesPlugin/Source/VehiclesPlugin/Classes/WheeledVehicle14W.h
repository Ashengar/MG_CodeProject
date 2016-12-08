/*
	Required for Vehicle 14W Blueprint Setup.
	Only overrides movement component.
*/
#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent14W.h"
#include "WheeledVehicle14W.generated.h"
class UWheeledVehicleMovementComponent14W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle14W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
};
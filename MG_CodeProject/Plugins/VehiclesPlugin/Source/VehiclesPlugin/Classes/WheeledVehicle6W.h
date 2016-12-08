/*
	Required for Vehicle 6W Blueprint Setup.
	Only overrides movement component.
*/

#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent6W.h"
#include "WheeledVehicle6W.generated.h"
class UWheeledVehicleMovementComponent6W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle6W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
};
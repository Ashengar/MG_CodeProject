/*
	Required for Vehicle 8W Blueprint Setup.
	Only overrides movement component.
*/

#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent8W.h"
#include "WheeledVehicle8W.generated.h"
class UWheeledVehicleMovementComponent8W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle8W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
}; 

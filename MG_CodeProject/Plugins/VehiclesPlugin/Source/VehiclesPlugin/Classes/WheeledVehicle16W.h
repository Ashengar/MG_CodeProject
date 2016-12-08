/*
Required for Vehicle 16W Blueprint Setup.
Only overrides movement component.
*/
#pragma once

#include "GameFramework/WheeledVehicle.h"
#include "WheeledVehicleMovementComponent16W.h"
#include "WheeledVehicle16W.generated.h"
class UWheeledVehicleMovementComponent16W;

UCLASS()
class VEHICLESPLUGIN_API AWheeledVehicle16W : public AWheeledVehicle
{
	GENERATED_UCLASS_BODY()
};
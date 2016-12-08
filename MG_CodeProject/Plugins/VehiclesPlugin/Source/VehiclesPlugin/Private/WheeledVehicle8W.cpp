#include "VehiclesPluginPrivatePCH.h"
AWheeledVehicle8W::AWheeledVehicle8W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponent8W>(AWheeledVehicle::VehicleMovementComponentName))
{

}
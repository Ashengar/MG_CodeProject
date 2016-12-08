#include "VehiclesPluginPrivatePCH.h"
AWheeledVehicle12W::AWheeledVehicle12W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponent12W>(AWheeledVehicle::VehicleMovementComponentName))
{

}
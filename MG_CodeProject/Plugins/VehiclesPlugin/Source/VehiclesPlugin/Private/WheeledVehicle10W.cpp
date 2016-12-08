#include "VehiclesPluginPrivatePCH.h"
AWheeledVehicle10W::AWheeledVehicle10W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponent10W>(AWheeledVehicle::VehicleMovementComponentName))
{

}
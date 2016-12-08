#include "VehiclesPluginPrivatePCH.h"
AWheeledVehicle6W::AWheeledVehicle6W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponent6W>(AWheeledVehicle::VehicleMovementComponentName))
{

}
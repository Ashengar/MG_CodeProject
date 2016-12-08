#include "VehiclesPluginPrivatePCH.h"
AWheeledVehicle16W::AWheeledVehicle16W(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponent16W>(AWheeledVehicle::VehicleMovementComponentName))
{

}
#include "VehiclesPluginPrivatePCH.h"
ATankVehicle::ATankVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWheeledVehicleMovementComponentTank>(AWheeledVehicle::VehicleMovementComponentName))
{

}
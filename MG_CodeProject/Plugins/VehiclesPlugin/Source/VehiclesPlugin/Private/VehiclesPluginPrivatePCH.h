// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.


#if PLATFORM_ANDROID || PLATFORM_HTML5_BROWSER || PLATFORM_IOS || PLATFORM_MAC
#ifdef WITH_APEX
#undef WITH_APEX
#endif
#define WITH_APEX 0
#endif //APEX EXCLUSIONS

#include "CoreUObject.h"
// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.
#include "IVehiclesPlugin.h"
#include "Vehicles/WheeledVehicleMovementComponent4W.h"
#include "WheeledVehicleMovementComponent6W.h"
#include "WheeledVehicleMovementComponent8W.h"
#include "WheeledVehicleMovementComponent10W.h"
#include "WheeledVehicleMovementComponent12W.h"
#include "WheeledVehicleMovementComponent14W.h"
#include "WheeledVehicleMovementComponent16W.h"
#include "WheeledVehicleMovementComponentTank.h"
#include "WheeledVehicle6W.h"
#include "WheeledVehicle8W.h"
#include "WheeledVehicle10W.h"
#include "WheeledVehicle12W.h"
#include "WheeledVehicle14W.h"
#include "WheeledVehicle16W.h"
#include "TankVehicle.h"
#include "PhysXIncludes.h"
#include "PhysicsPublic.h"  
#include "PhysXPublic.h"    
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"

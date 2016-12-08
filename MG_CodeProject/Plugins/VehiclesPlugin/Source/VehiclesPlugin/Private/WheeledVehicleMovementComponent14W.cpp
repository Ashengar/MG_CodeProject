#include "VehiclesPluginPrivatePCH.h"
UWheeledVehicleMovementComponent14W::UWheeledVehicleMovementComponent14W(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// grab default values from physx
	PxVehicleDifferentialNWData DefDifferentialSetup;

	PxVehicleEngineData DefEngineData;
	EngineSetup.MOI = DefEngineData.mMOI;
	EngineSetup.MaxRPM = OmegaToRPM(DefEngineData.mMaxOmega);
	EngineSetup.DampingRateFullThrottle = DefEngineData.mDampingRateFullThrottle;
	EngineSetup.DampingRateZeroThrottleClutchEngaged = DefEngineData.mDampingRateZeroThrottleClutchEngaged;
	EngineSetup.DampingRateZeroThrottleClutchDisengaged = DefEngineData.mDampingRateZeroThrottleClutchDisengaged;

	// Convert from PhysX curve to Unreal Engine's
	FRichCurve* TorqueCurveData = EngineSetup.TorqueCurve.GetRichCurve();
	for (PxU32 KeyIdx = 0; KeyIdx<DefEngineData.mTorqueCurve.getNbDataPairs(); KeyIdx++)
	{
		float Input = DefEngineData.mTorqueCurve.getX(KeyIdx) * EngineSetup.MaxRPM;
		float Output = DefEngineData.mTorqueCurve.getY(KeyIdx) * DefEngineData.mPeakTorque;
		TorqueCurveData->AddKey(Input, Output);
	}

	PxVehicleClutchData DefClutchData;
	TransmissionSetup.ClutchStrength = DefClutchData.mStrength;

	PxVehicleAckermannGeometryData DefAckermannSetup;
	AckermannAccuracy = DefAckermannSetup.mAccuracy;

	PxVehicleGearsData DefGearSetup;
	TransmissionSetup.GearSwitchTime = DefGearSetup.mSwitchTime;
	TransmissionSetup.ReverseGearRatio = DefGearSetup.mRatios[PxVehicleGearsData::eREVERSE];
	TransmissionSetup.FinalRatio = DefGearSetup.mFinalRatio;

	PxVehicleAutoBoxData DefAutoBoxSetup;
	TransmissionSetup.NeutralGearUpRatio = DefAutoBoxSetup.mUpRatios[PxVehicleGearsData::eNEUTRAL];
	TransmissionSetup.GearAutoBoxLatency = DefAutoBoxSetup.getLatency();
	TransmissionSetup.bUseGearAutoBox = true;

	for (uint32 i = PxVehicleGearsData::eFIRST; i < DefGearSetup.mNbRatios; i++)
	{
		FVehicleGearData GearData;
		GearData.DownRatio = DefAutoBoxSetup.mDownRatios[i];
		GearData.UpRatio = DefAutoBoxSetup.mUpRatios[i];
		GearData.Ratio = DefGearSetup.mRatios[i];
		TransmissionSetup.ForwardGears.Add(GearData);
	}

	// Init steering speed curve
	FRichCurve* SteeringCurveData = SteeringCurve.GetRichCurve();
	SteeringCurveData->AddKey(0.f, 1.f);
	SteeringCurveData->AddKey(20.f, 0.9f);
	SteeringCurveData->AddKey(60.f, 0.8f);
	SteeringCurveData->AddKey(120.f, 0.7f);

	// Initialize WheelSetups array with 14 wheels
	WheelSetups.SetNum(14);
}

#if WITH_EDITOR
void UWheeledVehicleMovementComponent14W::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == TEXT("DownRatio"))
	{
		for (int32 GearIdx = 0; GearIdx < TransmissionSetup.ForwardGears.Num(); ++GearIdx)
		{
			FVehicleGearData & GearData = TransmissionSetup.ForwardGears[GearIdx];
			GearData.DownRatio = FMath::Min(GearData.DownRatio, GearData.UpRatio);
		}
	}
	else if (PropertyName == TEXT("UpRatio"))
	{
		for (int32 GearIdx = 0; GearIdx < TransmissionSetup.ForwardGears.Num(); ++GearIdx)
		{
			FVehicleGearData & GearData = TransmissionSetup.ForwardGears[GearIdx];
			GearData.UpRatio = FMath::Max(GearData.DownRatio, GearData.UpRatio);
		}
	}
	else if (PropertyName == TEXT("SteeringCurve"))
	{
		//make sure values are capped between 0 and 1
		TArray<FRichCurveKey> SteerKeys = SteeringCurve.GetRichCurve()->GetCopyOfKeys();
		for (int32 KeyIdx = 0; KeyIdx < SteerKeys.Num(); ++KeyIdx)
		{
			float NewValue = FMath::Clamp(SteerKeys[KeyIdx].Value, 0.f, 1.f);
			SteeringCurve.GetRichCurve()->UpdateOrAddKey(SteerKeys[KeyIdx].Time, NewValue);
		}
	}
}

#endif

#if WITH_VEHICLE

static void GetVehicle14WEngineSetup(const FVehicleEngineData& Setup, PxVehicleEngineData& PxSetup)
{
	PxSetup.mMOI = M2ToCm2(Setup.MOI);
	PxSetup.mMOI = M2ToCm2(Setup.MOI);
	PxSetup.mMaxOmega = RPMToOmega(Setup.MaxRPM);
	PxSetup.mDampingRateFullThrottle = M2ToCm2(Setup.DampingRateFullThrottle);
	PxSetup.mDampingRateZeroThrottleClutchEngaged = M2ToCm2(Setup.DampingRateZeroThrottleClutchEngaged);
	PxSetup.mDampingRateZeroThrottleClutchDisengaged = M2ToCm2(Setup.DampingRateZeroThrottleClutchDisengaged);
	// Find max torque in Nm
	float PeakTorque = 0.f;
	TArray<FRichCurveKey> TorqueKeys = Setup.TorqueCurve.GetRichCurveConst()->GetCopyOfKeys();
	for (int32 KeyIdx = 0; KeyIdx < TorqueKeys.Num(); KeyIdx++)
	{
		FRichCurveKey& Key = TorqueKeys[KeyIdx];
		PeakTorque = FMath::Max(PeakTorque, Key.Value);
	}

	PxSetup.mPeakTorque = M2ToCm2(PeakTorque); // convert Nm to (kg cm^2/s^2)

	PxSetup.mTorqueCurve.clear();
	int32 NumTorqueCurveKeys = FMath::Min<int32>(TorqueKeys.Num(), PxVehicleEngineData::eMAX_NB_ENGINE_TORQUE_CURVE_ENTRIES);
	for (int32 KeyIdx = 0; KeyIdx < NumTorqueCurveKeys; KeyIdx++)
	{
		FRichCurveKey& Key = TorqueKeys[KeyIdx];
		PxSetup.mTorqueCurve.addPair(FMath::Clamp(Key.Time / Setup.MaxRPM, 0.f, 1.f), Key.Value / PeakTorque);
	}
}

static void GetVehicle14WGearSetup(const FVehicleTransmissionData& Setup, PxVehicleGearsData& PxSetup)
{
	PxSetup.mSwitchTime = Setup.GearSwitchTime;
	PxSetup.mRatios[PxVehicleGearsData::eREVERSE] = Setup.ReverseGearRatio;
	for (int32 i = 0; i < Setup.ForwardGears.Num(); i++)
	{
		PxSetup.mRatios[i + PxVehicleGearsData::eFIRST] = Setup.ForwardGears[i].Ratio;
	}
	PxSetup.mFinalRatio = Setup.FinalRatio;
	PxSetup.mNbRatios = Setup.ForwardGears.Num() + PxVehicleGearsData::eFIRST;
}

static void GetVehicle14WAutoBoxSetup(const FVehicleTransmissionData& Setup, PxVehicleAutoBoxData& PxSetup)
{
	for (int32 i = 0; i < Setup.ForwardGears.Num(); i++)
	{
		const FVehicleGearData& GearData = Setup.ForwardGears[i];
		PxSetup.mUpRatios[i] = GearData.UpRatio;
		PxSetup.mDownRatios[i] = GearData.DownRatio;
	}
	PxSetup.mUpRatios[PxVehicleGearsData::eNEUTRAL] = Setup.NeutralGearUpRatio;
	PxSetup.setLatency(Setup.GearAutoBoxLatency);
}
void SetupDriveHelper(const UWheeledVehicleMovementComponent14W* VehicleData, const PxVehicleWheelsSimData* PWheelsSimData, PxVehicleDriveSimDataNW& DriveData)
{

	PxVehicleEngineData EngineSetup;
	GetVehicle14WEngineSetup(VehicleData->EngineSetup, EngineSetup);
	DriveData.setEngineData(EngineSetup);

	PxVehicleClutchData ClutchSetup;
	ClutchSetup.mStrength = M2ToCm2(VehicleData->TransmissionSetup.ClutchStrength);
	DriveData.setClutchData(ClutchSetup);

	PxVehicleGearsData GearSetup;
	GetVehicle14WGearSetup(VehicleData->TransmissionSetup, GearSetup);
	DriveData.setGearsData(GearSetup);

	PxVehicleAutoBoxData AutoBoxSetup;
	GetVehicle14WAutoBoxSetup(VehicleData->TransmissionSetup, AutoBoxSetup);
	DriveData.setAutoBoxData(AutoBoxSetup);

}

static void CreateVehicleSimulation14W(PxVehicleWheelsSimData& Veh14WSimData, int32 NumWheels, PxVehicleDriveSimDataNW& DriveSimData14W)
{
	PxVehicleWheelsSimData* PWheelsSimData = PxVehicleWheelsSimData::allocate(4);
	Veh14WSimData.copy(*PWheelsSimData, 0, 0);
	Veh14WSimData.copy(*PWheelsSimData, 1, 1);
	Veh14WSimData.copy(*PWheelsSimData, 2, 2);
	Veh14WSimData.copy(*PWheelsSimData, 3, 3);
	Veh14WSimData.copy(*PWheelsSimData, 0, 4);

	//Copy front wheels bones to apply throttle and make rest of the wheels physical
	Veh14WSimData.copy(*PWheelsSimData, 1, 5);
	Veh14WSimData.copy(*PWheelsSimData, 0, 6);
	Veh14WSimData.copy(*PWheelsSimData, 1, 7);
	Veh14WSimData.copy(*PWheelsSimData, 0, 8);
	Veh14WSimData.copy(*PWheelsSimData, 1, 9);
	Veh14WSimData.copy(*PWheelsSimData, 0, 10);
	Veh14WSimData.copy(*PWheelsSimData, 1, 11);
	Veh14WSimData.copy(*PWheelsSimData, 0, 12);
	Veh14WSimData.copy(*PWheelsSimData, 1, 13);
	Veh14WSimData.setTireLoadFilterData(PWheelsSimData->getTireLoadFilterData());

	PxVehicleDifferentialNWData DifData;

	// Add wheels to diferretial
	DifData.setDrivenWheel(0, true);
	DifData.setDrivenWheel(1, true);
	DifData.setDrivenWheel(2, true);
	DifData.setDrivenWheel(3, true);
	DifData.setDrivenWheel(4, true);
	DifData.setDrivenWheel(5, true);
	DifData.setDrivenWheel(6, true);
	DifData.setDrivenWheel(7, true);
	DifData.setDrivenWheel(8, true);
	DifData.setDrivenWheel(9, true);
	DifData.setDrivenWheel(10, true);
	DifData.setDrivenWheel(11, true);
	DifData.setDrivenWheel(12, true);
	DifData.setDrivenWheel(13, true);
	DriveSimData14W.setDiffData(DifData);
}

void UWheeledVehicleMovementComponent14W::SetupVehicle()
{
	for (int32 WheelIdx = 0; WheelIdx < WheelSetups.Num(); ++WheelIdx)
	{
		const FWheelSetup& WheelSetup = WheelSetups[WheelIdx];
		if (WheelSetup.BoneName == NAME_None)
		{
			return;
		}
	}
	// Setup the chassis and wheel shapes
	SetupVehicleShapes();

	// Setup mass properties
	SetupVehicleMass();

	// Setup the wheels
	PxVehicleWheelsSimData* PWheelsSimData = PxVehicleWheelsSimData::allocate(14);

	// Setup drive data
	PxVehicleDriveSimDataNW DriveData;
	CreateVehicleSimulation14W(*PWheelsSimData, 14, DriveData);

	SetupWheels(PWheelsSimData);
	SetupDriveHelper(this, PWheelsSimData, DriveData);

	PxVehicleDriveNW* PVehicleDriveNW = PxVehicleDriveNW::allocate(14);
	check(PVehicleDriveNW);


	PVehicleDriveNW->setup(GPhysXSDK, UpdatedPrimitive->GetBodyInstance()->GetPxRigidDynamic_AssumesLocked(), *PWheelsSimData, DriveData, 0);
	PVehicleDriveNW->setToRestState();
	// cleanup
	PWheelsSimData->free();
	PWheelsSimData = NULL;
	// cache values
	PVehicle = PVehicleDriveNW;
	PVehicleDrive = PVehicleDriveNW;

	SetUseAutoGears(TransmissionSetup.bUseGearAutoBox);
}

void UWheeledVehicleMovementComponent14W::UpdateSimulation(float DeltaTime)
{
	if (PVehicleDrive == NULL)
		return;

	PxVehicleDriveNWRawInputData RawInputData;
	RawInputData.setAnalogAccel(ThrottleInput);
	RawInputData.setAnalogSteer(SteeringInput);
	RawInputData.setAnalogBrake(BrakeInput);
	RawInputData.setAnalogHandbrake(HandbrakeInput);

	if (!PVehicleDrive->mDriveDynData.getUseAutoGears())
	{
		RawInputData.setGearUp(bRawGearUpInput);
		RawInputData.setGearDown(bRawGearDownInput);
	}
	// Convert from our curve to PxFixedSizeLookupTable
	PxFixedSizeLookupTable<8> SpeedSteerLookup;
	TArray<FRichCurveKey> SteerKeys = SteeringCurve.GetRichCurve()->GetCopyOfKeys();
	const int32 MaxSteeringSamples = FMath::Min(14, SteerKeys.Num());
	for (int32 KeyIdx = 0; KeyIdx < MaxSteeringSamples; KeyIdx++)
	{
		FRichCurveKey& Key = SteerKeys[KeyIdx];
		SpeedSteerLookup.addPair(KmHToCmS(Key.Time), FMath::Clamp(Key.Value, 0.f, 1.0f));
	}

	PxVehiclePadSmoothingData SmoothData = {
		{ ThrottleInputRate.RiseRate, BrakeInputRate.RiseRate, HandbrakeInputRate.RiseRate, SteeringInputRate.RiseRate, SteeringInputRate.RiseRate },
		{ ThrottleInputRate.FallRate, BrakeInputRate.FallRate, HandbrakeInputRate.FallRate, SteeringInputRate.FallRate, SteeringInputRate.FallRate }
	};

	PxVehicleDriveNW* PVehicleDriveNW = (PxVehicleDriveNW*)PVehicleDrive;
	PxVehicleDriveNWSmoothAnalogRawInputsAndSetAnalogInputs(SmoothData, SpeedSteerLookup, RawInputData, DeltaTime, false, *PVehicleDriveNW);
}
#endif

// Updates engine setup on spawn.
void UWheeledVehicleMovementComponent14W::UpdateEngineSetup(const FVehicleEngineData& NewEngineSetup)
{
#if WITH_VEHICLE
	if (PVehicleDrive)
	{
		PxVehicleEngineData EngineData;
		GetVehicle14WEngineSetup(NewEngineSetup, EngineData);

		PxVehicleDriveNW* PVehicleDriveNW = (PxVehicleDriveNW*)PVehicleDrive;
		PVehicleDriveNW->mDriveSimData.setEngineData(EngineData);
	}
#endif
}

// Updates transmisson setup on spawn.
void UWheeledVehicleMovementComponent14W::UpdateTransmissionSetup(const FVehicleTransmissionData& NewTransmissionSetup)
{
#if WITH_VEHICLE
	if (PVehicleDrive)
	{
		PxVehicleGearsData GearData;
		GetVehicle14WGearSetup(NewTransmissionSetup, GearData);

		PxVehicleAutoBoxData AutoBoxData;
		GetVehicle14WAutoBoxSetup(NewTransmissionSetup, AutoBoxData);

		PxVehicleDriveNW* PVehicleDriveNW = (PxVehicleDriveNW*)PVehicleDrive;
		PVehicleDriveNW->mDriveSimData.setGearsData(GearData);
		PVehicleDriveNW->mDriveSimData.setAutoBoxData(AutoBoxData);
	}
#endif
}


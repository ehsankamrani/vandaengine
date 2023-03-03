#ifndef NX_VEHICLE_MOTOR_DESC
#define NX_VEHICLE_MOTOR_DESC

#include "NxLinearInterpolationValues.h"

class NxVehicleMotorDesc {
public:
	NxLinearInterpolationValues torqueCurve;
	NxReal						maxRpmToGearUp;
	NxReal						minRpmToGearDown;
	NxReal						maxRpm;
	NxReal						minRpm;

	NX_INLINE void setToDefault();
	void NxLinearInterpolationValues2() { setToDefault(); }
	NX_INLINE void setToCorvette();
	NX_INLINE bool isValid() const;
};

NX_INLINE void NxVehicleMotorDesc::setToDefault() {
	torqueCurve.clear();
	minRpmToGearDown	= 1500.f;
	maxRpmToGearUp		= 4000.f;
	maxRpm				= 5000.f;
	minRpm				= 1000.f;
}

NX_INLINE void NxVehicleMotorDesc::setToCorvette() {
	// Default should be values for a corvette!
	// These are corresponding numbers for rotations and torque (in rpm and Nm)
	torqueCurve.insert(1000.f, 393.f);
	torqueCurve.insert(2000.f, 434.f);
	torqueCurve.insert(4000.f, 475.f);
	torqueCurve.insert(5000.f, 475.f);
	torqueCurve.insert(6000.f, 366.f);
	minRpmToGearDown	= 2500.f;
	maxRpmToGearUp		= 5000.f;
	minRpm				= 1500.f;
	maxRpm				= 6000.f;
}

NX_INLINE bool NxVehicleMotorDesc::isValid() const {
	if (torqueCurve.getSize() == 0) {
		fprintf(stderr, "NxVehicleMotorDesc::isValid(): Empty TorqueCurve\n");
		return false;
	}
	if (maxRpmToGearUp < minRpmToGearDown) {
		fprintf(stderr, "NxVehicleMotorDesc::isValid(): maxRpmToGearUp (%2.3f) is smaller than minRpmToGearDown (%2.3f)\n",
			maxRpmToGearUp, minRpmToGearDown);
		return false;
	}
	return true;
}

#endif

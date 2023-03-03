#ifndef NX_VEHICLE_GEAR_DESC
#define NX_VEHICLE_GEAR_DESC

#include "NxLinearInterpolationValues.h"
//#include "NxLinearInterpolate3Values.h"
#include <NxArray.h>

#define NX_VEHICLE_MAX_NB_GEARS 32

class NxVehicleGearDesc {
public:
	NxVehicleGearDesc() { setToDefault(); }
	void setToDefault();
	void setToCorvette();
	bool isValid() const;
	NxU32									getMaxNumOfGears() const { return NX_VEHICLE_MAX_NB_GEARS; }


	//NxArray<NxLinearInterpolationValues>	forwardGears;
	//NxArray<NxF32>							forwardGearRatios;
	NxU32									nbForwardGears;
	//NxLinearInterpolationValues				forwardGears[NX_VEHICLE_MAX_NB_GEARS];
	NxF32									forwardGearRatios[NX_VEHICLE_MAX_NB_GEARS];

	//NxLinearInterpolationValues				backwardGear;
	NxF32									backwardGearRatio;
};

NX_INLINE void NxVehicleGearDesc::setToDefault() {
	//forwardGears.clear();
}

NX_INLINE void NxVehicleGearDesc::setToCorvette() {
	forwardGearRatios[0] = 2.66f;
	forwardGearRatios[1] = 1.78f;
	forwardGearRatios[2] = 1.30f;
	forwardGearRatios[3] = 1;
	forwardGearRatios[4] = 0.74f;
	forwardGearRatios[5] = 0.50f;
	nbForwardGears = 6;

	backwardGearRatio = -2.90f;

}

NX_INLINE bool NxVehicleGearDesc::isValid() const {
	if (nbForwardGears > getMaxNumOfGears()) {
		fprintf(stderr, "NxVehicleGearDesc::isValid(): nbForwardGears(%d) is bigger than max (%d)\n",
			nbForwardGears, getMaxNumOfGears());
		return false;
	}
	if (nbForwardGears <= 0) {
		fprintf(stderr, "NxVehicleGearDesc::isValid(): nbForwardGears(%d) smaller or equal 0\n", nbForwardGears);
		return false;
	}
	if (backwardGearRatio > 0) {
		fprintf(stderr, "NxVehilceGearDesc::isValid(): backwardGearRatio(%2.3f) is bigger than 0, make it negative\n", backwardGearRatio);
		return false;
	}
	for (NxU32 i = 0; i < nbForwardGears; i++) {
		if (forwardGearRatios[i] < 0) {
			fprintf(stderr, "NxVehilceGearDesc::isValid(): forwardGearRatios[%d] (%2.3f) has value smaller 0\n", i, forwardGearRatios[i]);
			return false;
		}
		/*if (forwardGears[i].getSize() == 0) {
			fprintf(stderr, "NxVehilceGearDesc::isValid(): forwardGears[%d] has size 0\n", i);
			return false;
		}*/
	}
	return true;
}

#endif

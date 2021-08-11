#ifndef NX_VEHICLE_GEARS
#define NX_VEHICLE_GEARS

#include "NxVehicleGearDesc.h"
#include <NxArray.h>


class NxVehicleGears {
	//NxArray<NxLinearInterpolationValues>	_forwardGears;
	//NxArray<NxF32>							_forwardGearRatios;
	NxU32									_nbForwardGears;
	//NxLinearInterpolationValues				_forwardGears[NX_VEHICLE_MAX_NB_GEARS];
	NxF32									_forwardGearRatios[NX_VEHICLE_MAX_NB_GEARS];

	//NxLinearInterpolationValues				_backwardGear;
	NxF32									_backwardGearRatio;

	NxI32									_curGear;


public:
	NxVehicleGears(): _curGear(1) { }

	static NxVehicleGears* createVehicleGears(const NxVehicleGearDesc& gearDesc);
	
	NxF32					getCurrentRatio() const;
	NxF32					getRatio(NxI32 gear) const;
	NxI32					getGear() const { return _curGear; }
	NxI32					getMaxGear() const { return _nbForwardGears; }
	void					gearUp() { _curGear = NxMath::min(_curGear+1, (NxI32)_nbForwardGears); }
	void					gearDown() { _curGear = NxMath::max(_curGear-1, -1); }
};

NX_INLINE NxVehicleGears* NxVehicleGears::createVehicleGears(const NxVehicleGearDesc& gearDesc) {
	if (!gearDesc.isValid())
		return NULL;
	NxVehicleGears *gears = new NxVehicleGears();
	NxI32 nbForwardGears = gears->_nbForwardGears = gearDesc.nbForwardGears;
	memcpy(gears->_forwardGearRatios, gearDesc.forwardGearRatios, sizeof(NxF32) * nbForwardGears);
	//memcpy(gears->_forwardGears, gearDesc.forwardGears, sizeof(NxLinearInterpolationValues) * nbForwardGears);
	gears->_curGear = 1;

	//gears->_backwardGear = gearDesc.backwardGear;
	gears->_backwardGearRatio = gearDesc.backwardGearRatio;

	return gears;
}

NX_INLINE NxF32 NxVehicleGears::getCurrentRatio() const {
	return getRatio(_curGear);
}

NX_INLINE NxF32 NxVehicleGears::getRatio(NxI32 gear) const {
	if (gear > 0)
		return _forwardGearRatios[gear-1];
	if (gear == -1)
		return _backwardGearRatio;
	return 0;
}

#endif

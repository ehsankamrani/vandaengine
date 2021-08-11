#ifndef NX_VEHICLE_MOTOR
#define NX_VEHICLE_MOTOR

#include "NxVehicleMotorDesc.h"
#include "NxVehicleGears.h"

class NxVehicleMotor {
	NxLinearInterpolationValues _torqueCurve;
	NxReal						_rpm;
	NxReal						_maxTorque;
	NxReal						_maxTorquePos;
	NxReal						_maxRpmToGearUp;
	NxReal						_minRpmToGearDown;
	NxReal						_maxRpm;
	NxReal						_minRpm;
public:
	NxVehicleMotor() : _rpm(0) { }
	static NxVehicleMotor* createMotor(const NxVehicleMotorDesc& motorDesc);

	void		setRpm(NxReal rpm) { _rpm = rpm; }
	NxReal		getRpm() const { return _rpm; }

	NxReal		getMinRpm() const { return _minRpm; }
	NxReal		getMaxRpm() const { return _maxRpm; }
	NxI32		changeGears(const NxVehicleGears* gears, NxReal threshold) const;

	NxReal		getTorque() const { return _torqueCurve.getValue(_rpm); }
};

NX_INLINE NxVehicleMotor* NxVehicleMotor::createMotor(const NxVehicleMotorDesc& motorDesc) {
	if (!motorDesc.isValid())
		return NULL;
	NxVehicleMotor* motor = new NxVehicleMotor();
	motor->_torqueCurve = motorDesc.torqueCurve;
	NxReal maxTorque = 0;
	NxI32 maxTorquePos = -1;
	for (NxU32 i = 0; i < motor->_torqueCurve.getSize(); i++) {
		NxReal v = motor->_torqueCurve.getValueAtIndex(i);
		if (v > maxTorque) {
			maxTorque = v;
			maxTorquePos = i;
		}
	}
	motor->_maxTorque			= maxTorque;
	motor->_maxTorquePos		= (NxReal)maxTorquePos;
	motor->_maxRpmToGearUp		= motorDesc.maxRpmToGearUp;
	motor->_minRpmToGearDown	= motorDesc.minRpmToGearDown;
	motor->_maxRpm				= motorDesc.maxRpm;
	motor->_minRpm				= motorDesc.minRpm;
	return motor;
}

NX_INLINE NxI32 NxVehicleMotor::changeGears(const NxVehicleGears* gears, NxReal threshold) const {
	NxI32 gear = gears->getGear();
	if (_rpm > _maxRpmToGearUp && gear < gears->getMaxGear())
		return 1;
	else if (_rpm < _minRpmToGearDown && gear > 1)
		return -1;
	/*
	NxReal normalTorque = _torqueCurve.getValue(_rpm);

	NxReal lowerGearRatio = gears->getRatio(gear-1);
	NxReal normalGearRatio = gears->getCurrentRatio();
	NxReal upperGearRatio = gears->getRatio(gear+1);
	NxReal lowerGearRpm = _rpm / normalGearRatio * lowerGearRatio;
	NxReal upperGearRpm = _rpm / normalGearRatio * upperGearRatio;
	NxReal lowerTorque = _torqueCurve.getValue(lowerGearRpm);
	NxReal upperTorque = _torqueCurve.getValue(upperGearRpm);
	NxReal lowerWheelTorque = lowerTorque * lowerGearRatio;
	NxReal normalWheelTorque = normalTorque * normalGearRatio;
	NxReal upperWheelTorque = upperTorque * upperGearRatio;
	//printf("%2.3f %2.3f %2.3f\n", lowerWheelTorque, normalWheelTorque, upperWheelTorque);
	*/

	return 0;
}

#endif

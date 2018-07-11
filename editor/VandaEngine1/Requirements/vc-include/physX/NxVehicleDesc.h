#ifndef NX_VEHICLE_DESC
#define NX_VEHICLE_DESC

#include "NxWheelDesc.h"
#include "NxVehicleMotorDesc.h"
#include "NxVehicleGearDesc.h"
#include <NxArray.h>
#include <NxShapeDesc.h>

class NxVehicleDesc
{
public:
	NxArray<NxShapeDesc*>	carShapes;
	NxArray<NxWheelDesc*>	carWheels;

	NxArray<NxVehicleDesc*> children;

	NxVehicleMotorDesc*		motorDesc;
	NxVehicleGearDesc*		gearDesc;

	NxVec3					position;
	NxReal					mass;
	NxReal					motorForce;
	NxReal					transmissionEfficiency;
	NxReal					differentialRatio;

	NxVec3					steeringTurnPoint;
	NxVec3					steeringSteerPoint;
	NxReal					steeringMaxAngle;

	NxVec3					centerOfMass;

	NxReal					digitalSteeringDelta;

	NxReal					maxVelocity;
	NxReal					cameraDistance;
	//NxReal					digitalSteeringDeltaVelocityModifier;

	void*					userData;

	NX_INLINE NxVehicleDesc();
	NX_INLINE void setToDefault();
	NX_INLINE bool isValid() const;
};

NX_INLINE NxVehicleDesc::NxVehicleDesc()	//constructor sets to default
{
	setToDefault();
}

NX_INLINE void NxVehicleDesc::setToDefault()
{
	userData = NULL;
	motorDesc = NULL;
	gearDesc = NULL;
	transmissionEfficiency = 1.0f;
	differentialRatio = 1.0f;
	maxVelocity = 80;
	cameraDistance = 15.f;
	children.clear();
	carWheels.clear();
}

NX_INLINE bool NxVehicleDesc::isValid() const
{
	for (NxU32 i = 0; i < carWheels.size(); i++) {
		if (!carWheels[i]->isValid())
			return false;
	}

	if (mass < 0)
		return false;

	return true;
}


#endif

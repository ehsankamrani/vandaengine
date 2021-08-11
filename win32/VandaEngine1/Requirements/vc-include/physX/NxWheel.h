#ifndef NX_WHEEL
#define NX_WHEEL

#include <cstdio>

#include "NxWheelDesc.h"
#include <NxPhysics.h>

class NxVehicle;

struct ContactInfo 
	{
	ContactInfo() { reset(); }
	void reset() { otherActor = NULL; relativeVelocity = 0; }
	bool isTouching() const { return otherActor != NULL; }
	NxActor*				otherActor;
	NxVec3					contactPosition;
	NxVec3					contactPositionLocal;
	NxVec3					contactNormal;
	NxReal					relativeVelocity;
	NxReal					relativeVelocitySide;
	};


class NxWheel 
	{
	public:
	static NxWheel* createWheel(NxActor* actor, NxWheelDesc* wheelDesc);

	virtual					~NxWheel() {}
	virtual void			tick(bool handbrake, NxReal motorTorque, NxReal brakeTorque, NxReal dt) = 0;
	virtual NxActor *		getTouchedActor() const = 0;
	virtual NxVec3			getWheelPos() const = 0;
	virtual void			setAngle(NxReal angle) = 0;
	virtual void			drawWheel(NxReal approx, bool debug = false) const = 0;
	virtual NxReal			getRpm() const = 0;
	virtual NxVec3			getGroundContactPos() const = 0;
	virtual float			getRadius() const = 0;

	NX_INLINE bool			hasGroundContact() const { return getTouchedActor() != NULL; }
	NX_INLINE bool			getWheelFlag(NxWheelFlags flag) const { return (wheelFlags & flag) != 0; }

	void*					userData;
	protected:
	NxU32					wheelFlags;
	};



class NxWheel1 : public NxWheel
	{
public:
	friend class NxWheel;

	NxWheel1(NxScene * s);
	~NxWheel1();

	//NxWheel interface:

	virtual void			tick(bool handbrake, NxReal motorTorque, NxReal brakeTorque, NxReal dt);
	virtual NxActor *		getTouchedActor() const		{ return contactInfo.otherActor; }
	virtual NxVec3			getWheelPos() const { return wheelCapsule->getLocalPosition(); }
	virtual void			setAngle(NxReal angle);
	virtual void			drawWheel(NxReal approx, bool debug = false) const;
	virtual NxReal			getRpm() const { return NxMath::abs(_turnVelocity * 60.f); }
	virtual NxVec3			getGroundContactPos() const { return getWheelPos(); }
	virtual float			getRadius() const { return _radius; }

	ContactInfo				contactInfo;
private:

	void					getSteeringDirection(NxVec3& dir);
	void					updateContactPosition();
	void					updateAngularVelocity(NxReal lastTimeStepSize, bool handbrake);
	void					setWheelOrientation(const NxMat33& m) { wheelCapsule->setLocalOrientation(m); if (wheelConvex != NULL) wheelConvex->setLocalOrientation(m); }

	NxCapsuleShape*			wheelCapsule;
	NxConvexShape*			wheelConvex;
	NxScene *				scene;

	NxMaterial*				material;
	NxReal					_frictionToSide;
	NxReal					_frictionToFront;
	
	NxReal					_turnAngle;
	NxReal					_turnVelocity;
	NxReal					_radius;
	NxReal					_perimeter;

	NxReal					_angle;
	NxReal					_wheelWidth;
	NxReal					_maxSuspension;
	//NxReal					_rpm;
	NxVec3					_maxPosition;

};


class NxWheel2 : public NxWheel
	{
	public:
	NxWheel2(NxActor* actor, NxWheelDesc* wheelDesc);
	virtual					~NxWheel2();

	virtual void			tick(bool handbrake, NxReal motorTorque, NxReal brakeTorque, NxReal dt);
	virtual NxActor *		getTouchedActor() const;
	virtual NxVec3			getWheelPos() const;
	virtual void			setAngle(NxReal angle);
	virtual void			drawWheel(NxReal approx, bool debug = false) const;
	virtual NxReal			getRpm() const;
	virtual NxVec3			getGroundContactPos() const { return getWheelPos()+NxVec3(0, -wheelShape->getRadius(), 0); }
	virtual float			getRadius() const { return wheelShape->getRadius(); }

	private:
	NxActor* actor;
	NxWheelShape * wheelShape;

	};
#endif

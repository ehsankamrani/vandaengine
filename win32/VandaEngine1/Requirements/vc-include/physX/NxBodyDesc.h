#ifndef NX_PHYSICS_NXBODYDESC
#define NX_PHYSICS_NXBODYDESC
/*----------------------------------------------------------------------------*\
|
|					Public Interface to NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/
/** \addtogroup physics
  @{
*/

#include "Nxp.h"

/**
\brief Descriptor for the optional rigid body dynamic state of #NxActor.

@see NxActor NxActorDesc NxScene.createActor()
*/
class NxBodyDesc
	{
	public:
	
	/**
	\brief position and orientation of the center of mass

	<b>Range:</b> rigid body transform<br>
	<b>Default:</b> Identity Matrix

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setCMassOffsetLocalPose() NxActor.getCMassLocalPose() massSpaceInertia mass
	*/
	NxMat34		massLocalPose;
	
	/**
	\brief Diagonal mass space inertia tensor in bodies mass frame.
	
	Set to all zeros to let the SDK compute it.

	<b>Range:</b> inertia vector<br>
	<b>Default:</b> Zero Matrix

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setMassSpaceInertiaTensor() NxActor.getMassSpaceInertiaTensor() mass massLocalPose
	*/
	NxVec3		massSpaceInertia;
	
	/**
	\brief Mass of body

	Should not be zero, to create a static actor set the body member of #NxActorDesc to NULL.

	<b>Range:</b> (0,inf)<br>
	<b>Default:</b> 0.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setMass() NxActor.getMass() massSpaceInertia
	*/
	NxReal		mass;
	
	/**
	\brief Linear Velocity of the body

	<b>Range:</b> velocity vector<br>
	<b>Default:</b> Zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setLinearVelocity() NxActor.getLinearVelocity() angularVelocity
	*/
	NxVec3		linearVelocity;
	
	/**
	\brief Angular velocity of the body

	<b>Range:</b> angular velocity vector<br>
	<b>Default:</b> Zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setAngularVelocity() NxActor.getAngularVelocity() linearVelocity
	*/
	NxVec3		angularVelocity;
	
	/**
	\brief The body's initial wake up counter.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 20.0f*0.02f

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.wakeUp() NxActor.putToSleep()
	*/
	NxReal		wakeUpCounter;
	
	/**
	\brief Linear damping applied to the body

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 0.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.getLinearDamping() NxActor.setLinearDamping() angularDamping
	*/
	NxReal		linearDamping;
	
	/**
	\brief Angular damping applied to the body

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 0.05

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setAngularDamping() NxActor.getAngularDamping() linearDamping
	*/
	NxReal		angularDamping;
	
	/**
	\brief Maximum allowed angular velocity 

	Use a negative value to use the default, specified using the #NX_MAX_ANGULAR_VELOCITY SDK parameter.

	<b>Range:</b> (0,inf)<br>
	<b>Default:</b> -1.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	Note: The angular velocity is clamped to the set value <i>before</i> the solver, which means that
	the limit may still be momentarily exceeded.

	@see NxActor.setMaxAngularVelocity() NxActor.getMaxAngularVelocity() NxPhysicsSDK.setParameter()
	*/
	NxReal		maxAngularVelocity;
	
	/**
	\brief When CCD is globally enabled, it is still not performed if the motion distance of all points on the body
	is below this threshold.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 0.0 (CCD enabled for any velocity)

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setCCDMotionThreshold() NxActor.getCCDMotionThreshold() NxShape.setCCDSkeleton() NxPhysicsSDK.setParameter()
	*/
	NxReal		CCDMotionThreshold;
	
	/**
	\brief Combination of ::NxBodyFlag flags

	<b>Default:</b> NX_BF_VISUALIZATION | NX_BF_ENERGY_SLEEP_TEST

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxBodyFlag NxActor.raiseBodyFlag() NxActor.clearBodyFlag()
	*/
	NxU32		flags;

	
	/**
	\brief Maximum linear velocity at which body can go to sleep.
	
	If negative, the global default will be used.

	Setting the sleep angular/linear velocity only makes sense when the NX_BF_ENERGY_SLEEP_TEST is not set. In
	version 2.5 and later a new method is used by default which uses the kinetic energy of the body to control
	sleeping.


	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> -1.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setSleepLinearVelocity() NxActor.getSleepLinearVelocity() sleepAngularVelocity
	*/
	NxReal		sleepLinearVelocity;
	
	/**
	\brief Maximum angular velocity at which body can go to sleep.
	
	If negative, the global default will be used.

	Setting the sleep angular/linear velocity only makes sense when the NX_BF_ENERGY_SLEEP_TEST is not set. In
	version 2.5 and later a new method is used by default which uses the kinetic energy of the body to control
	sleeping.

	<b>Range:</b>  [0,inf)<br>
	<b>Default:</b> -1.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setSleepAngularVelocity() NxActor.getSleepAngularVelocity() sleepLinearVelocity
	*/
	NxReal		sleepAngularVelocity;

	
	/**
	\brief Number of solver iterations performed when processing joint/contacts connected to this body.
	
	<b>Range:</b> [1,255]<br>
	<b>Default:</b> 4

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setSolverIterationCount() NxActor.getSolverIterationCount()
	*/
	NxU32		solverIterationCount;
	
	/**
	\brief Threshold for the energy-based sleeping algorithm. Only used when the NX_BF_ENERGY_SLEEP_TEST flag is set.

	<b>Range:</b> [0, inf)<br>
	<b>Default:</b> 0.005

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxReal		sleepEnergyThreshold;

	/**
	\brief Damping factor for bodies that are about to sleep.

	<b>Range:</b> [0, inf)<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxReal		sleepDamping;

	/**
	\brief The impulse threshold for contact reports.

	<b>Range:</b> (0,inf)<br>
	<b>Default:</b> NX_MAX_REAL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxActor.setContactReportThreshold() NxActor.getContactReportThreshold()
	*/
	NxReal		contactReportThreshold;

	/**
	\brief Constructor sets to default, mass == 0 (an immediate call to isValid() will return false). 
	*/
	NX_INLINE NxBodyDesc();	
	/**
	\brief (re)sets the structure to the default, mass == 0 (an immediate call to isValid() will return false). 	
	*/
	NX_INLINE void setToDefault();
	/**
	\brief Returns true if the descriptor is valid.

	\return True if the current settings are valid
	*/
	NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxBodyDesc::NxBodyDesc()	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxBodyDesc::setToDefault()
	{
	massLocalPose			.id();
	massSpaceInertia		.zero();
	linearVelocity			.zero();	//setNotUsed();	//when doing a loadFromDesc, the user expects to set the complete state, so this is not OK.
	angularVelocity			.zero();	//setNotUsed();
	wakeUpCounter			= 20.0f*0.02f;
	mass					= 0.0f;
	linearDamping			= 0.0f;
	angularDamping			= 0.05f;
	maxAngularVelocity		= -1.0f;
	flags					= NX_BF_VISUALIZATION;
	sleepLinearVelocity		= -1.0f;
	sleepAngularVelocity	= -1.0f;
	CCDMotionThreshold		= 0.0f;
	solverIterationCount    = 4;
	flags					|= NX_BF_ENERGY_SLEEP_TEST;
	sleepEnergyThreshold	= -1.0f;
	sleepDamping			= 0.0f;
	contactReportThreshold  = NX_MAX_REAL;
	}

NX_INLINE NxU32 NxBodyDesc::checkValid() const
	{
	if(mass<0.0f)		//no negative masses plz.
		return 1;
	if (wakeUpCounter < 0.0f) //must be nonnegative
		return 2;
	if (linearDamping < 0.0f) //must be nonnegative
		return 3;
	if (angularDamping < 0.0f) //must be nonnegative
		return 4;
	if (CCDMotionThreshold < 0.0f) //must be nonnegative
		return 5;
	if (solverIterationCount < 1) //must be positive
		return 6;
	if (solverIterationCount > 255) 
		return 7;
	if (contactReportThreshold < 0.0f) //must be nonnegative
		return 8;
	if(!massLocalPose.isFinite())
		return 8;
	return 0;
	}

/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

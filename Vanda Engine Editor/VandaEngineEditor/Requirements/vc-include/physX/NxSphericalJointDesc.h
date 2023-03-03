#ifndef NX_PHYSICS_NXSPHEREJOINTDESC
#define NX_PHYSICS_NXSPHEREJOINTDESC
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
#include "NxJointLimitPairDesc.h"
#include "NxSpringDesc.h"
#include "NxJointDesc.h"

class NxActor;


/**
\brief Desc class for an #NxSphericalJoint.

@see NxSphericalJoint NxScene.createJoint()
*/
class NxSphericalJointDesc : public NxJointDesc
	{
	public:
	/**
	\brief swing limit axis defined in the joint space of actor 0.
	
	([localNormal[0], localAxis[0]^localNormal[0],localAxis[0]])

	<b>Range:</b> direction vector<br>
	<b>Default:</b> 0.0, 0.0, 1.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3 swingAxis;

	
	/**
	\brief Distance above which to project joint.

	If flags.projectionMode is 1, the joint gets artificially projected together when it drifts more than this distance.
	
	Sometimes it is not possible to project (for example when the joints form a cycle).

	Should be nonnegative.
	
	However, it may be a bad idea to always project to a very small or zero distance because the solver *needs* some error in order to produce correct motion.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 1.0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see projectionMode NxJointProjectionMode
	*/
	NxReal projectionDistance;	


//limits:

	/**
	\brief limits rotation around twist axis

	<b>Range:</b> See #NxJointLimitPairDesc<br>
	<b>Default:</b> See #NxJointLimitPairDesc

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxJointLimitPairDesc swingLimit
	*/
	NxJointLimitPairDesc twistLimit;

	/**
	\brief limits swing of twist axis

	<b>Range:</b> See #NxJointLimitDesc<br>
	<b>Default:</b> See #NxJointLimitDesc

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxJointLimitDesc twistLimit
	*/
	NxJointLimitDesc swingLimit;
	
	
//spring + damper:

	/**
	\brief spring that works against twisting

    <b>Range:</b> See #NxSpringDesc<br>
	<b>Default:</b> See #NxSpringDesc

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSpringDesc
	*/
	NxSpringDesc	 twistSpring;

	/**
	\brief spring that works against swinging

    <b>Range:</b> See #NxSpringDesc<br>
	<b>Default:</b> See #NxSpringDesc

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSpringDesc
	*/
	NxSpringDesc	 swingSpring;

	/**
	\brief spring that lets the joint get pulled apart

    <b>Range:</b> See #NxSpringDesc<br>
	<b>Default:</b> See #NxSpringDesc

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSpringDesc
	*/
	NxSpringDesc	 jointSpring;

	/**
	\brief This is a combination of the bits defined by ::NxSphericalJointFlag . 

	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSphericalJointFlag
	*/
	NxU32 flags;							

	/**
	\brief use this to enable joint projection

	<b>Default:</b> NX_JPM_NONE

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see projectionDistance NxJointProjectionMode
	*/
	NxJointProjectionMode projectionMode;

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE NxSphericalJointDesc();	
	/**
	\brief (re)sets the structure to the default.	
	*/
	NX_INLINE void setToDefault();
	/**
	\brief Returns true if the descriptor is valid.

	\return true if the current settings are valid
	*/
	NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxSphericalJointDesc::NxSphericalJointDesc() : NxJointDesc(NX_JOINT_SPHERICAL)	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxSphericalJointDesc::setToDefault()
	{
	NxJointDesc::setToDefault();

	swingAxis.set(0,0,1);

	twistLimit.setToDefault();
	swingLimit.setToDefault();
	twistSpring.setToDefault();
	swingSpring.setToDefault();
	jointSpring.setToDefault();

	projectionDistance = 1.0f;

	flags = 0;
	projectionMode = NX_JPM_NONE;
	}

NX_INLINE NxU32 NxSphericalJointDesc::checkValid() const
	{
	//check unit vectors
	if (swingAxis.magnitudeSquared() < 0.9f) return 1;
	if (projectionDistance < 0.0f) return 2;

	NxU32 check;
	check = twistLimit.checkValid(); if(check) return 0x100 + check;
	check = swingLimit.checkValid(); if(check) return 0x100 + check;
	check = swingSpring.checkValid(); if(check) return 0x100 + check;
	check = twistSpring.checkValid(); if(check) return 0x100 + check;
	check = jointSpring.checkValid(); if(check) return 0x100 + check;

	return 3*NxJointDesc::checkValid();
	}

/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

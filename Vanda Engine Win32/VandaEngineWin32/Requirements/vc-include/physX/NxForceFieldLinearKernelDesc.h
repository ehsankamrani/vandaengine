#ifndef NX_PHYSICS_NXFORCEFIELDLINEARKERNELDESC
#define NX_PHYSICS_NXFORCEFIELDLINEARKERNELDESC
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
#include "NxForceFieldDesc.h"

/**
 \brief Descriptor class for  NxForceFieldLinearKernel class.

<b>Platform:</b>
\li PC SW: Yes
\li GPU  : Yes [SW]
\li PS3  : Yes
\li XB360: Yes
\li WII	 : Yes

 @see  NxForceFieldLinearKernel
*/

class NxForceFieldLinearKernelDesc
{
	public:
	
	/**
	\brief Constant part of force field function

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					constant;
	
	/**
	\brief Coefficient of force field function position term

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxMat33					positionMultiplier;
	
	/**
	\brief Force field position target.

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					positionTarget;
	
	/**
	\brief Coefficient of force field function velocity term

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxMat33					velocityMultiplier;
	
	/**
	\brief  Force field velocity target

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					velocityTarget;
	
	/**
	\brief Radius for NX_FFC_TOROIDAL type coordinates.

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxReal					torusRadius;

	/**
	\brief Linear term in magnitude falloff factor. Range (each component): [0, inf)

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					falloffLinear;
	
	/**
	\brief Quadratic term in magnitude falloff factor. Range (each component): [0, inf)

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					falloffQuadratic;

	/**
	\brief Noise scaling

	<b>Default</b> zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxVec3					noise;

	/**
	\brief Possible debug name. The string is not copied by the SDK, only the pointer is stored.

	<b>Default</b> NULL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	const char* name;

	/**
	\brief Will be copied to NxForceField::userData

	<b>Default:</b> NULL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxForceField.userData
	*/
	void*					userData; 

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE NxForceFieldLinearKernelDesc();

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

NX_INLINE NxForceFieldLinearKernelDesc::NxForceFieldLinearKernelDesc()
	{
	setToDefault();
	}

NX_INLINE void NxForceFieldLinearKernelDesc::setToDefault()
	{
	constant			.zero(); 
	positionMultiplier	.zero();
	positionTarget		.zero();
	velocityMultiplier	.zero();
	velocityTarget		.zero();
	falloffLinear		.zero();
	falloffQuadratic	.zero();
	noise				.zero();
	torusRadius			= 1.0f;
	name				= NULL;
	}

NX_INLINE NxU32 NxForceFieldLinearKernelDesc::checkValid() const
	{
	if(torusRadius<0.0f)
		return 1;
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

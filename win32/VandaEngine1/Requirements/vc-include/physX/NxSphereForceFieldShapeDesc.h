#ifndef NX_PHYSICS_NXSPHEREFORCEFIELDSHAPEDESC
#define NX_PHYSICS_NXSPHEREFORCEFIELDSHAPEDESC
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
#include "NxForceFieldShapeDesc.h"
/**
 \brief A descriptor for NxSphereForceFieldShape
 

<b>Platform:</b>
\li PC SW: Yes
\li GPU  : Yes [SW]
\li PS3  : Yes
\li XB360: Yes
\li WII	 : Yes

 @see NxForceFieldShapeDesc, NxForceFieldShape, NxForceField
*/
class NxSphereForceFieldShapeDesc : public NxForceFieldShapeDesc
	{
	public:
	NxReal radius;		//!< radius of the sphere.

	/**
	\brief constructor sets to default.
	*/
	NX_INLINE NxSphereForceFieldShapeDesc ();

	/**
	\brief (re)sets the structure to the default.	
	*/
	virtual NX_INLINE void setToDefault();

	/**
	\brief Returns true if the descriptor is valid.

	\return True if the current settings are valid
	*/
	virtual NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxSphereForceFieldShapeDesc::NxSphereForceFieldShapeDesc () : NxForceFieldShapeDesc(NX_SHAPE_SPHERE)
	{
	setToDefault();
	}

NX_INLINE void NxSphereForceFieldShapeDesc::setToDefault()
	{
	NxForceFieldShapeDesc::setToDefault();
	radius = 1.0f;
	}
NX_INLINE NxU32 NxSphereForceFieldShapeDesc::checkValid() const
	{
	if(!NxMath::isFinite(radius))	return 1;
	if(radius<=0.0f)				return 2;

	return 3*NxForceFieldShapeDesc::checkValid();
	}

/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

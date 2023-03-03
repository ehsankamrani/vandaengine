#ifndef NX_PHYSICS_NXBOXFORCEFIELDSHAPEDESC
#define NX_PHYSICS_NXBOXFORCEFIELDSHAPEDESC
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
 \brief A descriptor for NxBoxForceFieldShape
 

<b>Platform:</b>
\li PC SW: Yes
\li GPU  : Yes [SW]
\li PS3  : Yes
\li XB360: Yes
\li WII	 : Yes

 @see NxBoxForceFieldShape NxForceFieldShapeDesc NxBoxForceField
*/
class NxBoxForceFieldShapeDesc : public NxForceFieldShapeDesc
	{
	public:
	/** 
	\brief Dimensions of the box.
	
	The dimensions are the 'radii' of the box, meaning 1/2 extents in x dimension, 
	1/2 extents in y dimension, 1/2 extents in z dimension. All three must be positive.

	<b>Range:</b> .x (0,inf)
	<b>Range:</b> .y (0,inf)
	<b>Range:</b> .z (0,inf)
	<b>Default:</b> Zero

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxBoxForceFieldShape.setDimensions() NxBoxForceFieldShape.getDimensions()
	*/
	NxVec3 dimensions;

	/**
	\brief constructor sets to default.
	*/
	NX_INLINE NxBoxForceFieldShapeDesc();

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

NX_INLINE NxBoxForceFieldShapeDesc::NxBoxForceFieldShapeDesc() : NxForceFieldShapeDesc(NX_SHAPE_BOX)
	{
	setToDefault();
	}

NX_INLINE void NxBoxForceFieldShapeDesc::setToDefault()
	{
	NxForceFieldShapeDesc::setToDefault();
	dimensions.set(1.0f, 1.0f, 1.0f);	//note: NxBoxShape defaults to x0x0x but this is inconsistent with other shapes that are unity-sized by default.
	}

NX_INLINE NxU32 NxBoxForceFieldShapeDesc::checkValid() const
	{
	if(!dimensions.isFinite())			return 1;
	if(dimensions.x<0.0f)				return 2;
	if(dimensions.y<0.0f)				return 3;
	if(dimensions.z<0.0f)				return 4;
	return 5*NxForceFieldShapeDesc::checkValid();
	}

/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

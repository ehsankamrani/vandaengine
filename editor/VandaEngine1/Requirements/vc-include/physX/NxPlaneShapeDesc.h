#ifndef NX_COLLISION_NXPLANESHAPEDESC
#define NX_COLLISION_NXPLANESHAPEDESC
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

#include "NxShapeDesc.h"

/**
\brief Descriptor class for #NxPlaneShape.

See also the #NxPlane.

<b>Platform:</b>
\li PC SW: Yes
\li GPU  : Yes [SW]
\li PS3  : Yes
\li XB360: Yes
\li WII	 : Yes

@see NxPlane NxPlaneShape NxShapeDesc NxActor.createShape()
*/
class NxPlaneShapeDesc : public NxShapeDesc
	{
	public:
	
	/**
	\brief Plane normal. (unit length!)

	The plane equation takes the form: normal.x * X + normal.y * Y + normal.z * Z  = d
	
	Note: The plane equation defines the plane in world space. Any other transformations, 
	like actor global pose and shape local pose are ignored by the plane shape.

	<b>Range:</b> direction vector<br>
	<b>Default:</b> 0.0, 1.0, 0.0

	@see NxPlaneShape
	*/
	NxVec3		normal;

	/**
	\brief The distance from the origin.

	The plane equation takes the form: normal.x * X + normal.y * Y + normal.z * Z  = d

	<b>Range:</b> (-inf,inf)<br>
	<b>Default:</b> 0.0

	@see NxPlaneShape
	*/
	NxReal		d;

	/**
	\brief constructor sets to default.
	*/
	NX_INLINE					NxPlaneShapeDesc();	
	/**
	\brief (re)sets the structure to the default.	
	*/
	NX_INLINE virtual	void	setToDefault();
	/**
	\brief Returns true if the descriptor is valid.

	\return return true if the current settings are valid
	*/
	NX_INLINE virtual	bool	isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxPlaneShapeDesc::NxPlaneShapeDesc() : NxShapeDesc(NX_SHAPE_PLANE)	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxPlaneShapeDesc::setToDefault()
	{
	NxShapeDesc::setToDefault();
	// default ground plane
	normal.set(NxReal(0.0),NxReal(1.0),NxReal(0.0));
	d=NxReal(0.0);
	}

NX_INLINE NxU32 NxPlaneShapeDesc::checkValid() const
	{
	if(!normal.isFinite())		return 1;
	if(!NxMath::isFinite(d))	return 2;
	return 3*NxShapeDesc::checkValid();
	}

/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

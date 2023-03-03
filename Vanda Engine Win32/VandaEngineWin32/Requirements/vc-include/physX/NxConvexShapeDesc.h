#ifndef NX_COLLISION_NXCONVEXSHAPEDESC
#define NX_COLLISION_NXCONVEXSHAPEDESC
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
#include "NxConvexShape.h"

class NxConvexMesh;

/**
\brief Descriptor class for #NxConvexShape.

@see NxConvexShape NxShapeDesc NxActor.createShape() NxConvexMesh NxPhysicsSDK.createConvexMesh()
*/
class NxConvexShapeDesc : public NxShapeDesc
	{
	public:

	/**
	\brief References the triangle mesh that we want to instance.

	<b>Default:</b> NULL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxConvexMesh NxConvexMeshDesc NxPhysicsSDK.createConvexMesh()
	*/
	NxConvexMesh*	meshData;

	/**
	\brief Combination of ::NxMeshShapeFlag

	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxMeshShapeFlag
	*/
	NxU32			meshFlags;

#ifdef NX_SUPPORT_CONVEX_SCALE
	NxReal			scale;
#endif
	
	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE					NxConvexShapeDesc();	
	/**
	\brief (re)sets the structure to the default.	
	*/
	NX_INLINE virtual	void	setToDefault();
	/**
	\brief Returns true if the descriptor is valid.

	\return returns true if the current settings are valid
	*/
	NX_INLINE virtual	bool	isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxConvexShapeDesc::NxConvexShapeDesc() : NxShapeDesc(NX_SHAPE_CONVEX)	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxConvexShapeDesc::setToDefault()
	{
	NxShapeDesc::setToDefault();
	meshData	= NULL;
	meshFlags	= 0;
#ifdef NX_SUPPORT_CONVEX_SCALE
	scale		= 1.0f;
#endif
	}

NX_INLINE NxU32 NxConvexShapeDesc::checkValid() const
	{
	if(!meshData)	return 1;
#ifdef NX_SUPPORT_CONVEX_SCALE
	if(scale<=0.0f)	return 2;
#endif
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

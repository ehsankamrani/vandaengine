#ifndef NX_COLLISION_NXTRIANGLEMESHSHAPEDESC
#define NX_COLLISION_NXTRIANGLEMESHSHAPEDESC
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
#include "NxTriangleMeshShape.h"

/**
\brief Descriptor class for #NxTriangleMeshShape.

@see NxTriangleMeshShape
*/
class NxTriangleMeshShapeDesc : public NxShapeDesc
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

	@see NxTriangleMesh
	*/
	NxTriangleMesh*	meshData;	

	/**
	\brief Combination of ::NxMeshShapeFlag.

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

	/**
	\brief Mesh paging scheme.

	<b>Default:</b> NX_MESH_PAGING_MANUAL

	<b>Platform:</b>
	\li PC SW: No
	\li GPU  : Yes [SW]
	\li PS3  : No
	\li XB360: No

	@see NxMeshPagingMode
	*/
	NxMeshPagingMode meshPagingMode;

#ifdef NX_SUPPORT_MESH_SCALE
	NxReal			scale;
#endif
	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE					NxTriangleMeshShapeDesc();	
	/**
	\brief (re)sets the structure to the default.	
	*/
	NX_INLINE virtual	void	setToDefault();
	/**
	\brief Returns true if the descriptor is valid.

	\return true if the current settings are valid
	*/
	NX_INLINE virtual	bool	isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxTriangleMeshShapeDesc::NxTriangleMeshShapeDesc() : NxShapeDesc(NX_SHAPE_MESH)	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxTriangleMeshShapeDesc::setToDefault()
	{
	NxShapeDesc::setToDefault();
	meshData		= NULL;
	meshFlags		= 0;
	meshPagingMode	= NX_MESH_PAGING_MANUAL;
#ifdef NX_SUPPORT_MESH_SCALE
	scale		= 1.0f;
#endif
	}

NX_INLINE NxU32 NxTriangleMeshShapeDesc::checkValid() const
	{
	if(!meshData)	return 1;
#ifdef NX_SUPPORT_MESH_SCALE
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

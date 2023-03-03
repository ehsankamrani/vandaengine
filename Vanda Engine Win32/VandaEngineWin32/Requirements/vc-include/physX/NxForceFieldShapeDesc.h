#ifndef NX_PHYSICS_NXFORCEFIELDSHAPEDESC
#define NX_PHYSICS_NXFORCEFIELDSHAPEDESC
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
 \brief Descriptor class for NxForceFieldShape
 

<b>Platform:</b>
\li PC SW: Yes
\li GPU  : Yes [SW]
\li PS3  : Yes
\li XB360: Yes
\li WII	 : Yes

 @see NxForceFieldShape, NxForceField
*/
class NxForceFieldShapeDesc
	{
	protected:
	/**
	\brief The type of shape. This is set by the c'tor of the derived class.
	*/
	NxShapeType type;

	public:
	
	/**
	\brief shape's pose

	<b>Default:</b> Identity

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxMat34  pose;

	
	/**
	\brief Will be copied to NxForceFieldShape::userData.

	<b>Default:</b> NULL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	void* userData;

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
	\brief Constructor sets to default.
	*/
	virtual NX_INLINE ~NxForceFieldShapeDesc();
	
	/**
	\brief (re)sets the structure to the default.	
	*/
	virtual NX_INLINE void setToDefault();
	
	/**
	\brief Returns true if the descriptor is valid.

	\return true if the current settings are valid
	*/
	virtual NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;

	/**
	\brief Retrieves the shape type.

	\return The type of shape this descriptor describes. 

	@see NxShapeType
	*/
	NX_INLINE NxShapeType   getType() const;

	protected:
	/**
	\brief Constructor sets to default.

	\param type shape type
	*/
	NX_INLINE NxForceFieldShapeDesc(NxShapeType type);
	};

NX_INLINE NxForceFieldShapeDesc::NxForceFieldShapeDesc(NxShapeType t) : type(t)
	{
	setToDefault();
	}

NX_INLINE NxForceFieldShapeDesc::~NxForceFieldShapeDesc()
	{
	}

NX_INLINE void NxForceFieldShapeDesc::setToDefault()
	{
	pose.id();

	name = NULL;
	userData = NULL;
	}

NX_INLINE NxU32 NxForceFieldShapeDesc::checkValid() const
	{
	return 0;
	}

NX_INLINE NxShapeType   NxForceFieldShapeDesc::getType() const
	{
	return type;
	}




/** @} */
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

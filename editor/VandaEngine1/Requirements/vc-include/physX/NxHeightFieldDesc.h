#ifndef NX_COLLISION_NXHEIGHTFIELDDESC
#define NX_COLLISION_NXHEIGHTFIELDDESC
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
\brief Descriptor class for #NxHeightField.

The heightfield data is *copied* when a NxHeightField object is created from this descriptor. After the call the
user may discard the height data.

@see NxHeightField NxHeightFieldShape NxPhysicsSDK.createHeightField()
*/
class NxHeightFieldDesc
	{
    public:

	/**
	\brief Number of sample rows in the height field samples array.

	<b>Range:</b> &gt;1<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxU32							nbRows;

	/**
	\brief Number of sample columns in the height field samples array.

	<b>Range:</b> &gt;1<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxU32							nbColumns;

	/**
	\brief Format of the sample data.
	
	Currently the only supported format is NX_HF_S16_TM:

	<b>Default:</b> NX_HF_S16_TM

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	
	@see NxHeightFormat NxHeightFieldDesc.samples
	*/
	NxHeightFieldFormat				format;

	/**
	\brief The offset in bytes between consecutive samples in the samples array.
	
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxU32							sampleStride;

	/**
	\brief The samples array.
	
	It is copied to the SDK's storage at creation time.
	
	There are nbRows * nbColumn samples in the array,
	which define nbRows * nbColumn vertices and cells,
	of which (nbRows - 1) * (nbColumns - 1) cells are actually used.

	The array index of sample(row, column) = row * nbColumns + column.
	The byte offset of sample(row, column) = sampleStride * (row * nbColumns + column).
	The sample data follows at the offset and spans the number of bytes defined by the format.
	Then there are zero or more unused bytes depending on sampleStride before the next sample.
	
	<b>Default:</b> NULL

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxHeightFormat
	*/
	void *							samples;						

	/**
	\brief Deprecated: Sets how far 'below ground' the height volume extends.

	In this way even objects which are under the surface of the height field but above
	this cutoff are treated as colliding with the height field. To create a height field with the up axis being
	the Y axis, you need to set the verticalAxis to Y and the verticalExtent to a large negative number. 

	The verticalExtent has to be outside of the range of the scaled height values along the verticalAxis.

	You may set this to a positive value, in which case the extent will be cast along the opposite side of the height field.

	You may use a smaller finite value for the extent if you want to put some space under the height field, such as a cave.

	<b>Range:</b> (-inf,inf)<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Deprecated
	\li GPU  : Deprecated
	\li PS3  : Deprecated
	\li XB360: Deprecated
	*/
	NxReal					verticalExtent;

	/**
	\brief Sets how thick the heightfield surface is.

	In this way even objects which are under the surface of the height field but above
	this cutoff are treated as colliding with the height field. 

	The difference between thickness and (the deprecated) verticalExtent is that thickness
	is measured relative to the surface at the given point, while vertical extent was an absolute limit.

	You may set this to a positive value, in which case the extent will be cast along the opposite side of the height field.

	You may use a smaller finite value for the extent if you want to put some space under the height field, such as a cave.

	<b>Range:</b> (-inf,inf)<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxReal					thickness;

	/**
	This threshold is used by the collision detection to determine if a height field edge is convex 
	and can generate contact points. 
	Usually the convexity of an edge is determined from the angle (or cosine of the angle) between 
	the normals of the faces sharing that edge. 
	The height field allows a more efficient approach by comparing height values of neighbouring vertices. 
	This parameter offsets the comparison. Smaller changes than 0.5 will not alter the set of convex edges.
	The rule of thumb is that larger values will result in fewer edge contacts.
	
	This parameter is ignored in contact generation with sphere and capsule primitives.

	<b>Range:</b> (0,inf)<br>
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NxReal					convexEdgeThreshold;

	/**
	\brief Flags bits, combined from values of the enum ::NxHeightFieldFlags
	
	<b>Default:</b> 0

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes [SW]
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxHeightFieldFlags
	*/
	NxU32					flags;

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE				NxHeightFieldDesc();	
	
	/**
	\brief (re)sets the structure to the default.	
	*/
	NX_INLINE		void	setToDefault();
	
	/**
	\brief Returns true if the descriptor is valid.
	\return true if the current settings are valid
	*/
	NX_INLINE		bool	isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
	};

NX_INLINE NxHeightFieldDesc::NxHeightFieldDesc()	//constructor sets to default
	{
	setToDefault();
	}

NX_INLINE void NxHeightFieldDesc::setToDefault()
	{
	nbColumns					= 0;
	nbRows						= 0;
	format						= NX_HF_S16_TM;
	sampleStride				= 0;
	samples						= 0;
	verticalExtent				= 0;
	thickness					= 0;
	convexEdgeThreshold			= 0.0f;
	flags						= 0;
	}

NX_INLINE NxU32 NxHeightFieldDesc::checkValid() const
	{
	if (nbColumns < 2) return 1;
	if (nbRows < 2) return 2;
	switch (format) 
		{
		case NX_HF_S16_TM:
			if (sampleStride < 4) return 3;
			break;
		default:
			return 4;
		}
	if (convexEdgeThreshold < 0) return 5;
	if ((flags & NX_HF_NO_BOUNDARY_EDGES) != flags) return 6;
	if (verticalExtent != 0 && thickness != 0) return 7;
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

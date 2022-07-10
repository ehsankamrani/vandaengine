#ifndef NX_FLUIDS_NXPARTICLEIDDATA
#define NX_FLUIDS_NXPARTICLEIDDATA
/** \addtogroup fluids
  @{
*/

/*----------------------------------------------------------------------------*\
|
|					Public Interface to NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

/**
\brief Descriptor-like user-side class describing a set of fluid particle IDs.

NxParticleIdData is used to retrieve information about a selection of particles in the simulation. 

Each particle is created with an ID. This ID is unique within the current set of particles. Also, each ID
is guaranteed to be in the interval [0,NxFluidDesc::maxParticles). The user can use the particle IDs to
manage per particle user data.

*/
class NxParticleIdData
	{
	public:

	/**
	\brief Points to the user-allocated memory holding the number of IDs stored in the buffer. 
	
	If the SDK writes to a given ID buffer, it also sets the numbers of IDs written. If 
	this is set to NULL, the SDK can't write to the ID buffer.
	*/
	NxU32*					numIdsPtr;

	/**
	\brief The pointer to the user-allocated buffer for particle IDs.

	A particle ID is represented with a 32-bit unsigned integer. If set to NULL, IDs are not written to.
	*/
	NxU32*					bufferId;
	
	/**
	\brief The separation (in bytes) between consecutive particle IDs.

	The ID of the first particle is found at location <tt>bufferId</tt>;
	the second is at <tt>bufferId + bufferIdByteStride</tt>;
	and so on.
	*/
	NxU32					bufferIdByteStride;

	const char*				name;			//!< Possible debug name. The string is not copied by the SDK, only the pointer is stored.

	NX_INLINE ~NxParticleIdData();
	/**
	\brief (Re)sets the structure to the default.	
	*/
	NX_INLINE void setToDefault();
	/**
	\brief Returns true if the current settings are valid
	*/
	NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE	NxParticleIdData();
	};

NX_INLINE NxParticleIdData::NxParticleIdData()
	{
	setToDefault();
	}

NX_INLINE NxParticleIdData::~NxParticleIdData()
	{
	}

NX_INLINE void NxParticleIdData::setToDefault()
	{
	numIdsPtr				= NULL;
	bufferId				= NULL;
	bufferIdByteStride		= 0;
	name					= NULL;
	}

NX_INLINE NxU32 NxParticleIdData::checkValid() const
	{
	if (numIdsPtr && !(bufferId)) return 1;
	if (bufferId && !numIdsPtr) return 2;
	if (bufferId && !bufferIdByteStride) return 3;
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


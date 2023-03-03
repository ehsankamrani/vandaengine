#ifndef NX_FLUIDS_NXFLUIDPACKETDATA
#define NX_FLUIDS_NXFLUIDPACKETDATA
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

#include "Nxp.h"


/**
\brief Data structure to represent a bounding box and its associated particle data of a fluid packet.
*/
struct NxFluidPacket
	{
	/**
	\brief AABB of all particles which are inside the same packet.
	*/
	NxBounds3	aabb; 

	/**
	\brief Index of first particle for a given packet.  This index can be used to index into each of the buffers in NxParticleData.

	@see NxParticleData
	*/
	NxU32		firstParticleIndex;

	/**
	\brief Number of particles inside the packet.
	*/
	NxU32		numParticles;

	/**
	\brief The packet's Identifier.
	*/
	NxU32		packetID;
	};

/**
\brief Data structure to receive AABBs per fluid packet.

Important: The array lengths need to be equivalent to the maxPacket parameter of the NxFluid 
this is applied to.

*/
class NxFluidPacketData
	{
	public:

	/**
	\brief The pointer to the user-allocated buffer for fluid packets.
	*/
	NxFluidPacket*			bufferFluidPackets;

	/**
	\brief Points to the user-allocated memory holding the number of packets stored in the buffers.
	*/
	NxU32*					numFluidPacketsPtr;

	NX_INLINE ~NxFluidPacketData();
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
	NX_INLINE	NxFluidPacketData();
	};

NX_INLINE NxFluidPacketData::NxFluidPacketData()
	{
	setToDefault();
	}

NX_INLINE NxFluidPacketData::~NxFluidPacketData()
	{
	}

NX_INLINE void NxFluidPacketData::setToDefault()
	{
	bufferFluidPackets		= NULL;
	numFluidPacketsPtr		= NULL;
	}

NX_INLINE NxU32 NxFluidPacketData::checkValid() const
	{
	if (numFluidPacketsPtr && !bufferFluidPackets) return 1;
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


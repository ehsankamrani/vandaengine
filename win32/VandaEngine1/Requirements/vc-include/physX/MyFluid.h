// ===============================================================================
//						  NVIDIA PhysX SDK Sample ProgramS
//					        PARTICLE FLUID
//
//		            Written by Simon Schirm 01-12-06
// ===============================================================================

#ifndef MYFLUID_H
#define MYFLUID_H

#include "NxPhysics.h"

/**
Stores elements which can be received from the SDK.
Note, not all data here is used in all samples, some just make use of the position.
*/
struct ParticleSDK
{
	NxVec3	position;
	NxVec3  velocity;
	NxReal	density;
	NxReal  lifetime;
	NxU32	id;
	NxVec3	collisionNormal;
};

/**
Stores user specific data.
Note, not all samples make use of user specific data.
*/
struct MyParticle
{
	float rgba[4];
};

class MyFluid 
{
public:

	MyFluid(NxScene* scene, NxFluidDesc &desc, bool trackUserData, bool provideCollisionNormals, const NxVec3& color,  NxReal particleSize);
	~MyFluid();

	NxFluid*				getNxFluid() { return mFluid; }
	
	const ParticleSDK*		getParticles() { return mParticleBuffer; }
	unsigned				getParticlesNum() { return mParticleBufferNum; }

	MyParticle*				getMyParticles() { return mMyParticleBuffer; }

	const unsigned*			getCreatedIds() { return mCreatedParticleIds; }
	unsigned				getCreatedIdsNum() { return mCreatedParticleIdsNum; }

	const unsigned*			getDeletedIds() { return mDeletedParticleIds; }
	unsigned				getDeletedIdsNum() { return mDeletedParticleIdsNum; }

	void					setParticleSize(NxReal size) { mParticleSize = size; }
	NxReal					getParticleSize() { return mParticleSize; }

    const NxVec3&           getColor() { return mParticleColor; }

	void draw();

private:
    void drawBillboards();   // old style rendering

	unsigned			mParticleBufferNum;
	ParticleSDK*		mParticleBuffer;

	NxFluid*			mFluid;
	NxVec3				mParticleColor;
	NxReal				mParticleSize;
	NxU32				mMaxParticles;

	/**
	These fields are only relevant for tracking user partilce data (MyParticle)
	*/
	bool				mTrackUserData;
	MyParticle*			mMyParticleBuffer;
	NxU32				mCreatedParticleIdsNum;
	NxU32*				mCreatedParticleIds;
	NxU32				mDeletedParticleIdsNum;
	NxU32*				mDeletedParticleIds;

	//rendering
	float*				mRenderBuffer;
	float*				mRenderBufferUserData;
};

#endif

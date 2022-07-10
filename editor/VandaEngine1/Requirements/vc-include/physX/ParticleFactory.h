// ===============================================================================
//						  NVIDIA PhysX SDK Sample ProgramS
//					        PARTICLE FLUID
//
//		            Written by Simon Schirm 09-12-06
// ===============================================================================

#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "NxPhysics.h"

void CreateParticleAABB(NxParticleData& pd, unsigned maxParticlesTotal, unsigned maxParticles, bool append, NxBounds3& aabb, const NxVec3 vel, float lifetime, float distance);
void CreateParticleSphere(NxParticleData& pd, unsigned maxParticles, bool append, const NxVec3& pos, const NxVec3 vel, float lifetime, float distance, unsigned sideNum);


#endif


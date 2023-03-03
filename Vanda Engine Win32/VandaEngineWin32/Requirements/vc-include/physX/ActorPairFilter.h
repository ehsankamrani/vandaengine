// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//							    USER ACTORPAIRFILTERING
//
//						    Written by Yang Liu, 7-21-2008
// ===============================================================================

#ifndef USERACTORPAIRFILTERING_H
#define USERACTORPAIRFILTERING_H

extern NxActor* groundPlane;

class UserActorPairFiltering : public NxUserActorPairFiltering
{
public:
	UserActorPairFiltering() : bNoCollision(false) {}

	virtual void  onActorPairs(NxActorPairFilter *filterArray, NxU32 arraySize)
	{
		for (NxU32 i = 0; i < arraySize; ++i)
		{
			NxActor* pActor0 = filterArray[i].actor[0];
			NxActor* pActor1 = filterArray[i].actor[1];
			if (groundPlane == pActor0)
			{
				filterArray[i].filtered = false;
				continue;
			}
			if (groundPlane == pActor1)
			{
				filterArray[i].filtered = false;
				continue;
			}

			filterArray[i].filtered = bNoCollision;
		}
	}

public:
	bool bNoCollision;
};

#endif

// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//			                          USER DATA
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#ifndef USERDATA_H
#define USERDATA_H

#include "NxPhysics.h"

enum UserDataFlag
{
	UD_IS_HW_ACTOR					= (1<<0),
	UD_IS_TRIGGER			        = (1<<1),
    UD_IS_INSIDE_TRIGGER            = (1<<2),
    UD_PASSES_INTERSECTION_TEST     = (1<<3),
    UD_HIT_BY_RAYCAST               = (1<<4),
    UD_NO_RENDER                    = (1<<5),
    UD_IS_DRAIN                     = (1<<6),
	UD_IS_ASLEEP				    = (1<<7),
	UD_RENDER_USING_LIGHT1			= (1<<8),
};


void AddUserDataToActors(NxScene* scene);
void AddUserDataToShapes(NxActor* actor);

void ReleaseUserDataFromActors(NxScene* scene);
void ReleaseUserDataFromShapes(NxActor* actor);

class ActorUserData
{
public:
	NxU32 id;
	NxU32 contactEvents;
	NxU32 flags;

	ActorUserData()
	{
		id = 0;
		contactEvents = 0;
		flags = 0;
	}
};

class ShapeUserData
{
public:
	NxU32 id;
	void* mesh;
    void* model;

	NxReal wheelShapeRollAngle;
	NxMat34 wheelShapePose;

	ShapeUserData()
	{
		id = 0;
		mesh = NULL;
        model = NULL;
		wheelShapeRollAngle = 0;
//		wheelShapePose = 0;
	}
};

#endif  // USERDATA_H


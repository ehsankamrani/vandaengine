// ===============================================================================
//						     PHYSX SDK TRAINING PROGRAMS
//			                        ENTITY REPORT
//
//						   Written by Bob Schade, 12-15-05
// ===============================================================================

#ifndef ENTITYREPORT_H
#define ENTITYREPORT_H

class ShapeReport : public NxUserEntityReport<NxShape*>
{
public:
	virtual bool onEvent(NxU32 nbShapes, NxShape** shapes)
	{
		while (nbShapes--)
		{
			NxActor* actor = &shapes[nbShapes]->getActor();
			((ActorUserData *)(actor->userData))->flags |= UD_PASSES_INTERSECTION_TEST;
		}
		return true;
	}

} gShapeReport;

#endif  // ENTITYREPORT_H


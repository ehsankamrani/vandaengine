// ===============================================================================
//						     PHYSX SDK TRAINING PROGRAMS
//			                       TRIGGER REPORT
//
//						   Written by Bob Schade, 12-15-05
// ===============================================================================

#define TRIGGER_REPORT_H
#ifdef TRIGGER_REPORT_H

#include "UserData.h"

extern NxI32 gNbTouchedBodies;

class TriggerReport : public NxUserTriggerReport
{
public:
	virtual void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
	{
		if (status & NX_TRIGGER_ON_ENTER)
		{
			// A body just entered the trigger area
			gNbTouchedBodies++;
		}
		if (status & NX_TRIGGER_ON_LEAVE)
		{
			// A body just left the trigger area
			gNbTouchedBodies--;
		}
		NX_ASSERT(gNbTouchedBodies>=0);

		// Mark actors in the trigger area to apply forcefield forces to them
		NxActor* triggerActor = &triggerShape.getActor();
		if (((ActorUserData*)(triggerActor->userData))->flags & UD_IS_TRIGGER)
		{
            if (status & NX_TRIGGER_ON_STAY)
            {
                NxActor* otherActor = &otherShape.getActor();
                ((ActorUserData*)(otherActor->userData))->flags |= UD_IS_INSIDE_TRIGGER;
            }
		}
	}
} gTriggerReport;

#endif  // TRIGGER_REPORT_H


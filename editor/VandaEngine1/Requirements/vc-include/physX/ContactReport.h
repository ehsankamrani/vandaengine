// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//			                       CONTACT REPORT
//
//						    Written by Bob Schade, 5-1-05
// ===============================================================================

#ifndef CONTACTREPORT_H
#define CONTACTREPORT_H

#include "UserData.h"

class ContactPoint
{
public:
	ContactPoint(const NxVec3& _p, const NxVec3& _color)
	{
		p = _p;
		color = _color;
	}

	NxVec3	p;
	NxVec3	color;
};

class ContactLine
{
public:
	ContactLine(const NxVec3& _p0, const NxVec3& _p1, const NxVec3& _color)
	{
		p0 = _p0;
		p1 = _p1;
		color = _color;
	}

	NxVec3	p0;
	NxVec3	p1;
	NxVec3	color;
};

class ContactTriangle
{
public:
	ContactTriangle(const NxVec3& _p0, const NxVec3& _p1, const NxVec3& _p2, const NxVec3& _color)
	{
		p0 = _p0;
		p1 = _p1;
		p2 = _p2;
		color = _color;
	}

	NxVec3	p0;
	NxVec3	p1;
	NxVec3	p2;
	NxVec3	color;
};

typedef NxArray<ContactPoint> ContactPointsArray;
typedef NxArray<ContactLine> ContactLinesArray;
typedef NxArray<ContactTriangle> ContactTrisArray;

ContactPointsArray cpArray;
ContactLinesArray clArray;
ContactTrisArray ctArray;

class ContactReport : public NxUserContactReport
{
public:
    virtual void onContactNotify(NxContactPair& pair, NxU32 events)
	{
		if (pair.actors[0])
		{
			ActorUserData* ud = (ActorUserData*)pair.actors[0]->userData;
			if (ud)  ud->contactEvents = events;
		}

		if (pair.actors[1])
		{
			ActorUserData* ud = (ActorUserData*)pair.actors[1]->userData;
			if (ud)  ud->contactEvents = events;
		}

//		if(events & NX_NOTIFY_ON_START_TOUCH)	printf("Start touch\n");
//		if(events & NX_NOTIFY_ON_END_TOUCH)		printf("End touch\n");

		// Iterate through contact points
		NxContactStreamIterator i(pair.stream);
		//user can call getNumPairs() here
		while(i.goNextPair())
		{
			//user can also call getShape() and getNumPatches() here
			while(i.goNextPatch())
			{
				//user can also call getPatchNormal() and getNumPoints() here
				const NxVec3& contactNormal = i.getPatchNormal();
				while(i.goNextPoint())
				{
					//user can also call getShape() and getNumPatches() here
					const NxVec3& contactPoint = i.getPoint();

					NxVec3 normalForceVec = NxVec3(0,0,0);
					NxVec3 frictionForceVec = NxVec3(0,0,0);
					NxVec3 penetrationVec = NxVec3(0,0,0);
					NxVec3 contactArrowForceTip = NxVec3(0,0,0);
					NxVec3 contactArrowFrictionTip = NxVec3(0,0,0);
					NxVec3 contactArrowPenetrationTip = NxVec3(0,0,0);

					ContactPoint cp(contactPoint, NxVec3(1,0,0));
					cpArray.pushBack(cp);

					// Get the normal force vector
					normalForceVec = pair.sumNormalForce;
//					normalForceVec = pair.sumNormalForce * 0.05;
					if (normalForceVec.magnitude() > 0.01)
					{
						normalForceVec.normalize();
						NxVec3 contactArrowForceTip = contactPoint + normalForceVec*3;
						ContactLine cl(contactPoint, contactArrowForceTip, NxVec3(0,0,1));
						clArray.pushBack(cl);
					}

					// Get the friction force vector
					frictionForceVec = pair.sumFrictionForce;
//					frictionForceVec = pair.sumFrictionForce* 0.05;
					if (frictionForceVec.magnitude() > 0.01)
					{
						frictionForceVec.normalize();
					    contactArrowFrictionTip = contactPoint + frictionForceVec*3;
					}

					// Get the penetration vector
					penetrationVec = - contactNormal * i.getSeparation();
//					penetrationVec = - contactNormal * i.getSeparation() * 20.0;
					if (penetrationVec.magnitude() > 0.01)
					{
						penetrationVec.normalize();
					    contactArrowPenetrationTip = contactPoint + penetrationVec*3;
					}
				}
			}
		}
	}

} gContactReport;

#endif  // CONTACTREPORT_H


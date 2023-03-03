#include "NxPhysics.h"

class Rope
{
public:
	Rope(NxScene& nxScene,
		 NxVec3& startPosition = NxVec3(0,0,0),
		 int numSegments =100, 
		 float segLength = 0.5f, 
		 float segMass = 0.05f,
		 float segCollisionRadius = 0.35f,	
		 float projectionRatio = 0.1f		
		 );
	~Rope();	

	NxActor*	getFirstSegment();
	NxActor*    getLastSegment();
	int			getNumSegments();
	NxActor*	getSegment(int segIndex);	
	void		setUniformVelocity(NxVec3& vel);
	float		getSegmentLength() { return segmentLength;}
	NxJoint*		pinFirstSegmentInPlace();	
	NxJoint*		pinLastSegmentInPlace();
	NxJoint*		pinSegmentToPosition(int segIndex, NxVec3& pos);
	

private:
	NxScene* scene;
	NxActor **ropeSegments;	
	NxJoint *topJoint, *bottomJoint;

	int	  numSegs;// = 100;
	float segmentLength;// = 0.5f;
	float segmentCollisionRadius;// = 0.35f;
	float baseMassOfRopeSegment;// = 0.05f;   // w/segmentLength of 0.5m, this is 0.05kg/0.5m = 0.1kg/1m = 100g/m, about 4oz
	float randomMassCoefficient;// = 0.003;   // I find that having slight nonuniformity of mass per unit length improves the dynamic character
	float baseProjectionDistance;// = 0.1f;   // 
	float projectionDistanceRampRate;// = 0.0005f;
	float internalSpringDamping;
	float segmentLinearDamping;// = 0.1f;
	float segmentAngularDamping;// = 0.1f;
	float momentOfInertiaConstant; // = 1.0f;
	NxVec3 startingPos;
	
	

};
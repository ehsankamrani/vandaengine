// An NVIDIA PhysX demo application, using debug visualization and joints
// by Simon Schirm

#include <stdio.h>

static void renderBox(const NxMat34 & pose, const NxVec3  & halfWidths)
	{
	//transform our unit cube:
	float glmat[16];
	glPushMatrix();
	pose.getColumnMajor44(glmat);
	glMultMatrixf(glmat);
	glScalef(halfWidths.x, halfWidths.y, halfWidths.z);	
	glutSolidCube(2.0);
	glPopMatrix();
	}


static void renderSphere(const NxMat34 & pose, float rad)
	{
	//transform our unit cube:
	float glmat[16];
	glPushMatrix();
	pose.getColumnMajor44(glmat);
	glMultMatrixf(glmat);
	glutSolidSphere(rad,10,10);
	glPopMatrix();
	}

class Truck
{
public:


	Truck(): force(0.0), steerAngle(0) {}

	struct Wheel
	{
		void render()
		{
			NxMat34 pose = 	wheel->getGlobalPose();
			NxSphereShape * sphere = static_cast<NxSphereShape*>(wheel->getShapes()[0]);
			if (sphere) renderSphere(pose, sphere->getRadius());
		}

		void create( NxScene& scene, const NxVec3& pos, float rad, NxActor * holder)
		{
			NxActorDesc actorDesc;
			NxBodyDesc bodyDesc;
			NxSphereShapeDesc sphereDesc;
			
			bodyDesc.solverIterationCount = 20;
			// wheel
			sphereDesc.radius = rad;
			sphereDesc.materialIndex = wheelMaterial;
			actorDesc.shapes.pushBack(&sphereDesc);
			bodyDesc.mass = 400.0;
			actorDesc.body		   = &bodyDesc;
			actorDesc.globalPose.t = pos;
			wheel = scene.createActor(actorDesc);

			// roll axis
			bodyDesc.mass = 500.0;
			bodyDesc.massSpaceInertia = NxVec3(10,10,10);
			actorDesc.body			= &bodyDesc;
			actorDesc.shapes.clear();
			actorDesc.globalPose.t  = pos;
			rollAxis = scene.createActor(actorDesc);
			
			// revolution joint connecting wheel with rollAxis
			NxRevoluteJointDesc revJointDesc;
			revJointDesc.projectionMode = NX_JPM_POINT_MINDIST;
			revJointDesc.actor[0] = wheel;
			revJointDesc.actor[1] = rollAxis;
			revJointDesc.setGlobalAnchor(pos);
			revJointDesc.setGlobalAxis(NxVec3(0,0,1));
			NxJoint * joint = scene.createJoint(revJointDesc);
			rollJoint = static_cast<NxRevoluteJoint*>(joint);

			// prismatic joint connecting rollAxis with holder
			NxPrismaticJointDesc prisJointDesc;
			prisJointDesc.actor[0] = rollAxis;
			prisJointDesc.actor[1] = holder;
			prisJointDesc.setGlobalAnchor(pos);
			prisJointDesc.setGlobalAxis(NxVec3(0,1,0));
			scene.createJoint(prisJointDesc);

			//add springs and dampers to the suspension (i.e. the related actors)
			float springLength = 0.2f;
			NxSpringAndDamperEffector * springNdamp = scene.createSpringAndDamperEffector(NxSpringAndDamperEffectorDesc());

			springNdamp->setBodies(rollAxis, pos, holder, pos + NxVec3(0,springLength,0));
			springNdamp->setLinearSpring(0, springLength, 2*springLength, 100000, 100000);
			springNdamp->setLinearDamper(-1,1, 1e5, 1e5);

			//disable collision detection 
			scene.setActorPairFlags(*wheel, *holder, NX_IGNORE_PAIR);
		}

		NxActor * wheel;
		NxActor * rollAxis;
		NxRevoluteJoint * rollJoint;
	};


	struct SteerWheel
	{
		void render()
		{
			wheel.render();
		}

		void create( NxScene& scene, const NxVec3& pos, float rad, NxActor * holder)
		{
			NxActorDesc actorDesc;
			NxBodyDesc bodyDesc;

			bodyDesc.solverIterationCount = 20;

			// steer axis
			bodyDesc.mass = 500.0;
			bodyDesc.massSpaceInertia = NxVec3(10,10,10);
			actorDesc.body			= &bodyDesc;
			actorDesc.shapes.clear();

			actorDesc.globalPose.t  = pos;
			steerAxis = scene.createActor(actorDesc);
			wheel.create( scene, pos, rad, steerAxis); //

			// revolution joint connecting steerAxis with the holder
			NxRevoluteJointDesc revJointDesc;
			revJointDesc.projectionMode = NX_JPM_POINT_MINDIST;
			revJointDesc.actor[0] = steerAxis;
			revJointDesc.actor[1] = holder;
			revJointDesc.setGlobalAnchor(pos);
			revJointDesc.setGlobalAxis(NxVec3(0,1,0));
			NxJoint * joint = scene.createJoint(revJointDesc);
			steerJoint = static_cast<NxRevoluteJoint*>(joint);

			// disable collision detection 
			scene.setActorPairFlags(*wheel.wheel, *holder, NX_IGNORE_PAIR);
		}
		
		Wheel wheel;	
		NxActor * steerAxis;
		NxRevoluteJoint * steerJoint;
	};


	void renderTruckShape(NxShape * shape)
	{
		NxBoxShape * box = static_cast<NxBoxShape*>(shape);
		if (!box) return;
		NxMat34 pose = shape->getGlobalPose();
		renderBox(pose, box->getDimensions());			
	}

	void render()
	{
		glEnable(GL_LIGHTING);

		glColor4f(0.5f, 1.0f, 0.8f, 1.0f);
		renderTruckShape(tractor->getShapes()[0]);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		renderTruckShape(trailer->getShapes()[0]);

		glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
		renderTruckShape(tractor->getShapes()[1]);
		renderTruckShape(trailer->getShapes()[1]);

		steerWheels[0].render();
		steerWheels[1].render();

		unsigned i;
		for (i=0; i<4; i++) frontWheels[i].render();
		for (i=0; i<4; i++) backWheels[i].render();
	}

	void create(NxScene& scene, NxActor& ground)
	{

		NxBodyDesc bodyDesc;	
		NxBoxShapeDesc boxDesc0;
		NxBoxShapeDesc boxDesc1;

		bodyDesc.solverIterationCount = 20;
		
		// tractor actor (two shapes)
		NxActorDesc tractoractorDesc;
		bodyDesc.mass = 3000;
		tractoractorDesc.body			= &bodyDesc;
		tractoractorDesc.globalPose.t   = NxVec3(0,0,0);

		boxDesc0.dimensions = NxVec3(3.5,3,4);
		boxDesc0.localPose.t = NxVec3(3.5,4,0);
		tractoractorDesc.shapes.pushBack(&boxDesc0);
		
		boxDesc1.dimensions = NxVec3(8.5,0.7,3);
		boxDesc1.localPose.t = NxVec3(8.7,1.3,0);
		tractoractorDesc.shapes.pushBack(&boxDesc1);

		tractor = scene.createActor(tractoractorDesc);

		// trailer actor (also two shapes)
		NxActorDesc traileractorDesc;
		bodyDesc.mass = 6000;
		traileractorDesc.body			= &bodyDesc;
		traileractorDesc.globalPose.t   = NxVec3(0,0,0);
		
		boxDesc0.dimensions = NxVec3(14.5,4.3,4);
		boxDesc0.localPose.t = NxVec3(24.0,7.6,0);
		traileractorDesc.shapes.pushBack(&boxDesc0);
		
		boxDesc1.dimensions = NxVec3(5.5,0.7,3);
		boxDesc1.localPose.t = NxVec3(31,2.0,0);
		traileractorDesc.shapes.pushBack(&boxDesc1);

		trailer = scene.createActor(traileractorDesc);

		// remove collision between lower truck parts and ground
		scene.setShapePairFlags(*tractor->getShapes()[1], *ground.getShapes()[0], NX_IGNORE_PAIR);
		scene.setShapePairFlags(*trailer->getShapes()[1], *ground.getShapes()[0], NX_IGNORE_PAIR);

		// wheels
		float staticFriction  = 1.2f;
		float dynamicFriction = 1.0f;

		steerWheels[0].create( scene, NxVec3( 3.5,1.5, 4), 1.5f, tractor);
		steerWheels[1].create( scene, NxVec3( 3.5,1.5,-4), 1.5f, tractor);
		frontWheels[0].create( scene, NxVec3(16.0,1.5, 4), 1.5f, tractor);
		frontWheels[1].create( scene, NxVec3(16.0,1.5,-4), 1.5f, tractor);

		//additionally remove collision between front wheels and the trailer
		scene.setActorPairFlags(*frontWheels[0].wheel,*trailer, NX_IGNORE_PAIR);
		scene.setActorPairFlags(*frontWheels[1].wheel,*trailer, NX_IGNORE_PAIR);

		backWheels[0].create( scene, NxVec3(30.5,1.5, 4), 1.5f, trailer);
		backWheels[1].create( scene, NxVec3(30.5,1.5,-4), 1.5f, trailer);
		backWheels[2].create( scene, NxVec3(33.6,1.5, 4), 1.5f, trailer);
		backWheels[3].create( scene, NxVec3(33.6,1.5,-4), 1.5f, trailer);

		// create rotation joint for the tractor trailer connection
		NxSphericalJointDesc sphJointDesc;
		sphJointDesc.actor[0] = tractor;
		sphJointDesc.actor[1] = trailer;
		sphJointDesc.setGlobalAnchor(NxVec3(10,2.5,0));
		
		
		sphJointDesc.setGlobalAxis(NxVec3(0,1,0));
		sphJointDesc.swingAxis.set(0,0,1);

		sphJointDesc.twistLimit.low.value = NxMath::degToRad( -46.0f);
		sphJointDesc.twistLimit.high.value = NxMath::degToRad( 46.0f);
		sphJointDesc.swingLimit.value = NxMath::degToRad( 10.0f);

		sphJointDesc.flags |= NX_SJF_TWIST_LIMIT_ENABLED;
		sphJointDesc.flags |= NX_SJF_SWING_LIMIT_ENABLED;

		// NxJointLimitDesc swingLimit;
		scene.createJoint(sphJointDesc);
	}

	void control( bool keyLeft, bool keyRight, bool keyUp, bool keyDown, float dt)
	{
		const NxReal maxSteerAngle = 30.0f;
		NxReal sangle; 

		if (keyLeft ) steerAngle += 1.0f;
		if (keyRight) steerAngle -= 1.0f;
		if (!keyLeft && !keyRight) {
			if (steerAngle < 0.0) {
				steerAngle = NxMath::min(steerAngle + 1.0, 0.0);
			} else if (steerAngle > 0.0) {
				steerAngle = NxMath::max(steerAngle - 1.0, 0.0);
			}
		}
		
		if (steerAngle > 0.0) sangle = NxMath::min(steerAngle,  maxSteerAngle);
		else				   sangle = NxMath::max(steerAngle, -maxSteerAngle);	
		steerAngle = sangle;

		steerWheels[0].steerJoint->setSpring(NxSpringDesc(5e4, 100, NxMath::degToRad(sangle)));
		steerWheels[1].steerJoint->setSpring(NxSpringDesc(5e4, 100, NxMath::degToRad(sangle)));
		
		float gdvAcc = dt * 30.0f;
		float gdvBrk = dt * 10.0f;

		if      ( keyUp && !keyDown) force += gdvAcc;
		else if (!keyUp &&  keyDown) force -= gdvBrk;				
		else	force = 0.0f;

		unsigned i;
		float maxvel = NxMath::sign(force) * 1e5f;
		for (i=0; i<2; i++)
			frontWheels[i].rollJoint->setMotor(NxMotorDesc(maxvel, 1.0f * NxMath::abs(force), false));
		for (i=0; i<2; i++)
			steerWheels[i].wheel.rollJoint->setMotor(NxMotorDesc(maxvel, 1.0f * NxMath::abs(force), false));
	}


	NxActor *  tractor;
	NxActor *  trailer;
	SteerWheel steerWheels[2];
	Wheel      frontWheels[2];
	Wheel	   backWheels[4];

	float force;
	float steerAngle;

};

//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Nx.h"
#include "../VandaEngineEditorDlg.h"
#include "../graphicsEngine/scene.h"
NxPhysicsSDK*     gPhysicsSDK;
NxScene*          gPhysXscene;
std::map< CUInt, NxMaterial* > g_physXMaterial;
CNovodex::CNovodex()
{
	m_groundBox = NULL;
	m_currentMoveDirection = m_previousMoveDirection = IDLE;
}

CNovodex::~CNovodex()
{
	g_physXMaterial.clear();
	m_nxActorNames.clear();
	m_nxActorTypes.clear();
}

CBool CNovodex::initNx(CFloat XCharacterPos, CFloat YCharacterPos, CFloat ZCharacterPos, CFloat crtlRadius, CFloat crtlHeight, CFloat crtSlopeLimit, CFloat crtSkinWidth, CFloat crtStepOffset, CBool createScene)
{
	if( createScene )
	{
		gPhysXscene = NULL;
		gPhysicsSDK = NULL;
	}

	
	//Default gravity
	m_defaultGravity.x = g_physXProperties.m_fGravityX;
	m_defaultGravity.y = g_physXProperties.m_fGravityY;
	m_defaultGravity.z = g_physXProperties.m_fGravityZ;
	wireFrame = false;
	zero = NxVec3(0,0,0);

	gJump = false;
	gControllers = NULL;

	gTimestepMultiplier = 1;
	bPushCharacter = false;
	gCharacterVec = NxVec3(1,0,0);
	gCharacterWalkSpeed = g_physXProperties.m_fCharacterWalkSpeed;
	gCharacterRunSpeed = g_physXProperties.m_fCharacterRunSpeed;
	bFixedStep = CTrue; 
	gDesiredDistance = 3.0f;
	m_pushCharacter = CFalse;

	gTriggerReport.hitName = NULL;

	if( createScene )
	{
		gAllocator = NULL;
		gAllocator = new UserAllocator;
		NxPhysicsSDKDesc desc;
		gPhysicsSDK = NxCreatePhysicsSDK( NX_PHYSICS_SDK_VERSION, gAllocator, NULL, desc );
		if( !gPhysicsSDK )
		{
			MessageBox( NULL, "Couldn't initialize physX", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION );
			return false;
		}
		gPhysicsSDK->setParameter( NX_SKIN_WIDTH, g_physXProperties.m_fDefaultSkinWidth );

		NxSceneDesc sceneDesc;
		sceneDesc.gravity = m_defaultGravity;
		sceneDesc.simType = NX_SIMULATION_HW;

		gPhysXscene = gPhysicsSDK->createScene( sceneDesc );
		if( !gPhysXscene )
		{
			sceneDesc.simType = NX_SIMULATION_SW;
			gPhysXscene = gPhysicsSDK->createScene(sceneDesc);
		}
	}
	gPhysXscene->setGroupCollisionFlag( GROUP_COLLIDABLE_NON_PUSHABLE, GROUP_COLLIDABLE_PUSHABLE, CTrue );
	gPhysXscene->setGroupCollisionFlag( GROUP_COLLIDABLE_PUSHABLE, GROUP_COLLIDABLE_PUSHABLE, CTrue );
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_COLLIDABLE_PUSHABLE, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_COLLIDABLE_NON_PUSHABLE, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_COLLIDABLE_NON_PUSHABLE_NO_CAMERA_HIT, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_DUMMY, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_STATIC, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_TRIGGER, CFalse);
	gPhysXscene->setGroupCollisionFlag(GROUP_DUMMY, GROUP_GROUND, CFalse);

	gPhysXscene->setGroupCollisionFlag(GROUP_TRIGGER, GROUP_GROUND, CFalse);

	gPhysXscene->setUserTriggerReport(&gTriggerReport);

	debugMode = true;

	if( debugMode )
	{
        // Set the debug visualization parameters
        gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1.0);
        gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
        gPhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);
		gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1);
		gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
		gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_FORCE, 1);
		gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_STATIC, 1);
		gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_DYNAMIC, 1);
	}

	// Create the default material
	if( createScene )
	{
		NxMaterial* defaultMaterial = gPhysXscene->getMaterialFromIndex(0); 
		defaultMaterial->setRestitution(g_physXProperties.m_fDefaultRestitution);
		defaultMaterial->setStaticFriction(g_physXProperties.m_fDefaultStaticFriction);
		defaultMaterial->setDynamicFriction(g_physXProperties.m_fDefaultDynamicFriction);
	}


	InitCharacterControllers(XCharacterPos, YCharacterPos, ZCharacterPos, crtlRadius, crtlHeight, crtSkinWidth, crtSlopeLimit, crtStepOffset);
	CFloat TimeStep = 1.0f / 60.0f;
	if (bFixedStep)
		gPhysXscene->setTiming(TimeStep, 8, NX_TIMESTEP_FIXED);
	else
		gPhysXscene->setTiming(TimeStep, 8, NX_TIMESTEP_VARIABLE);


	gCharacterPos.x = XCharacterPos;
	gCharacterPos.y = YCharacterPos;
	gCharacterPos.z = ZCharacterPos;

	CreateGroundPlane(g_physXProperties.m_fGroundHeight);
	
	return true;
}

CVoid CNovodex::runPhysics( NxVec3 forceDirection, CFloat forceSpeed, CInt moveDirection, CFloat elapsedTime )
{
	if( gPhysXscene )
	{
		// Update the box character's position according to by testing its
		// axis-aligned bounding box against a copy of the current scene.
		UpdateCharacter(forceDirection, forceSpeed, elapsedTime, moveDirection);

		gPhysXscene->simulate(elapsedTime);
		gPhysXscene->flushStream();
		gPhysXscene->fetchResults(NX_ALL_FINISHED, true);

		// Update the box character's position according to results
		// gathered from the updated scene
		PostUpdateCharacter();
	}
}

CVoid CNovodex::releaseNx()
{

	gTriggerReport.hitName = NULL;
	ReleaseCharacterControllers();

	if( gPhysXscene)
	{
		gPhysicsSDK->releaseScene( *gPhysXscene );
		gPhysXscene = NULL;
	}
	if( gPhysicsSDK )
	{
		gPhysicsSDK->release();
		gPhysicsSDK = NULL;
	}
	if( gAllocator )
	{
        CDelete(gAllocator);
		gAllocator = NULL;
	}
}

CVoid CNovodex::UpdateCharacter( NxVec3 forceDirection, CFloat forceSpeed, CFloat deltaTime, CInt moveDirection )
{
	m_previousMoveDirection = m_currentMoveDirection;
	m_currentMoveDirection = moveDirection;
	deltaTime *= (CFloat)gTimestepMultiplier;

	NxVec3 gravity;
	gPhysXscene->getGravity(gravity);
	NxVec3 disp = gravity;
	CFloat vdisp = 0.0f;
	gCharacterPos = GetRawCharacterPos();
    
	NxVec3 horizontalDisp;
	CFloat verticalDisp = 0.0f;
	horizontalDisp.x = horizontalDisp.y = horizontalDisp.z = 0;

	CBool pushCharacter = false;
	switch( moveDirection )
	{
	case IDLE:
		break;
	case MOVE_FRONT:
	pushCharacter = true;
	horizontalDisp = -gDir;
	break;
	case MOVE_BACK:
	pushCharacter = true;
	horizontalDisp = gDir;
	break;
	case MOVE_LEFT:
	pushCharacter = true;
	horizontalDisp = gRightDir;
	break;
	case MOVE_RIGHT:
	pushCharacter = true;
	horizontalDisp = -gRightDir;
	break;
	case MOVE_FRONT_RIGHT:
	pushCharacter = true;
	horizontalDisp = -gRightDir - gDir ;
	break;
	case MOVE_FRONT_LEFT:
	pushCharacter = true;
	horizontalDisp = gRightDir - gDir ;
	break;
	case MOVE_BACK_RIGHT:
	pushCharacter = true;
	horizontalDisp = gDir - gRightDir ;
	break;
	case MOVE_BACK_LEFT:
	pushCharacter = true;
	horizontalDisp = gDir + gRightDir ;
	break;
	case MOVE_UP:
	pushCharacter = true;
	verticalDisp = 1;
	break;
	case MOVE_DOWN:
	pushCharacter = true;
	verticalDisp = -1;
	break;

	default:
		break;
	}
	if( pushCharacter || bPushCharacter ) //bPushCharater is specifed inside ApplyForce function
	{
		//horizontalDisp.y = 0.0f;
		horizontalDisp.normalize();
		forceDirection.normalize();

		if (g_multipleView->m_inputSystem->KeyDown(DIK_LSHIFT))
			disp += horizontalDisp * gCharacterRunSpeed;
		else
			disp += horizontalDisp * gCharacterWalkSpeed;
		disp += forceDirection * forceSpeed;

		if (g_multipleView->m_inputSystem->KeyDown(DIK_LSHIFT))
			vdisp += verticalDisp * gCharacterRunSpeed * deltaTime;
		else
			vdisp += verticalDisp * gCharacterWalkSpeed * deltaTime;
		m_pushCharacter = CTrue;
	}
	else
		m_pushCharacter = CFalse;
	m_horizontalDisp.x = horizontalDisp.x;
	m_horizontalDisp.y = horizontalDisp.y;
	m_horizontalDisp.z = horizontalDisp.z;

	NxU32 collisionFlags = MoveCharacter(disp, deltaTime, COLLIDABLE_MASK, GetHeight(deltaTime) + vdisp );
	if (collisionFlags & NXCC_COLLISION_DOWN)  StopJump();
}


NxF32 CNovodex::cameraHit()
{
	if( gPhysXscene )
	{
		NxShape* characterShape = GetCharacterActor()->getShapes()[0];

		NxExtendedVec3 cpos = GetRawCharacterPos();	// First character = player

		NxRay worldRay;
		worldRay.orig.x	= (NxReal)cpos.x;
		worldRay.orig.y	= (NxReal)cpos.y;
		worldRay.orig.z	= (NxReal)cpos.z;
		worldRay.dir	=  gDir;
		NxRaycastHit hit;
		characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, true);
		NxShape* shape = gPhysXscene->raycastClosestShape(worldRay, NX_ALL_SHAPES, hit);
		characterShape->setFlag(NX_SF_DISABLE_RAYCASTING, false);

		gWorldRay = worldRay;
		if( shape )
		{
			if (shape->getGroup() == GROUP_TRIGGER || shape->getGroup() == GROUP_COLLIDABLE_NON_PUSHABLE_NO_CAMERA_HIT || shape->getGroup() == GROUP_DUMMY)
				return gDesiredDistance;
			else
			{
				return hit.distance;
			}
		}
		else 
			return NX_MAX_F32;
	}
	return 0.0f;
	//return shape ? hit.distance : NX_MAX_F32;
}

CVoid CNovodex::GetCameraAndCharacterPositions( const CFloat pitch, const CFloat yaw, NxVec3& cameraPos, NxVec3& characterPos, NxVec3& cameraDirection )
{
    // Setup the view matrix
	NxMat33 RotX;	RotX.rotX(pitch);
	NxMat33 RotY;	RotY.rotY(yaw+NxPiF32);
	NxMat33 ViewMat = RotY*RotX;
	gDir = -ViewMat.getColumn(2); 
	gRightDir = ViewMat.getColumn(0);
    
	cameraDirection = gDir;
    dist = cameraHit();
	if(dist>gDesiredDistance)	dist = gDesiredDistance;

	NxExtendedVec3 cpos = GetRawCharacterPos();

	NxVec3 cameraGoal((NxReal)cpos.x, (NxReal)cpos.y, (NxReal)cpos.z);

	characterPos = cameraGoal;
	if ((g_currentCameraType == eCAMERA_PHYSX && !g_mainCharacter) || (g_mainCharacter && g_mainCharacter->GetCameraType() == ePHYSX_CAMERA_FIRST_PERSON))
	{
		characterPos += -gDir*3.0f;
		cameraGoal += gDir*0.1f;
	}
	else
	{
		cameraGoal += gDir*dist;
	}

	cameraPos = cameraGoal;

	cameraPos.y += g_physXProperties.m_fCapsuleHeight;
}

NxReal CNovodex::updateTime()
{
    NxReal deltaTime;
    static __int64 gTime,gLastTime;
    __int64 freq;
    QueryPerformanceCounter((LARGE_INTEGER *)&gTime);  // Get current count
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq); // Get processor freq
    deltaTime = (CFloat)(gTime - gLastTime)/(CFloat)freq;
    gLastTime = gTime;

	return deltaTime;
}

NxF32 CNovodex::GetHeight(NxF32 elapsedTime)
{
	NxVec3 gravity;
	gPhysXscene->getGravity(gravity);
	if (!gJump)  return 0.0f;
	jumpTime += elapsedTime;
	NxF32 h = gravity.y *jumpTime*jumpTime + m_V0*jumpTime;
	return (h - gravity.y)*elapsedTime;
}


CVoid CNovodex::StartJump(NxF32 v0)
{
	if (gJump)  return;
	jumpTime = 0.0f;
	m_V0	= v0;
	gJump = true;
}

CVoid CNovodex::StopJump()
{
	if (!gJump)  return;
	gJump = false;
}

CVoid CNovodex::SetActorCollisionGroup(NxActor* actor, NxCollisionGroup group)
{
	actor->setGroup(group);
    NxShape*const* shapes = actor->getShapes();
    NxU32 nShapes = actor->getNbShapes();
    while (nShapes--)
    {
		//do not set dummy shapes of triggers
		if (group == GROUP_TRIGGER && shapes[nShapes]->getName() && Cmp(shapes[nShapes]->getName(), "dummy"))
			shapes[nShapes]->setGroup(GROUP_DUMMY);
		else
			shapes[nShapes]->setGroup(group);
	}
}

CVoid CNovodex::PostUpdateCharacter()
{
	NxReal maxTimestep;
	NxTimeStepMethod method;
	NxU32 maxIter;
	NxU32 numSubSteps;

	gPhysXscene->getTiming(maxTimestep, maxIter, method, &numSubSteps);
	if (numSubSteps)  UpdateControllers();
}


NxActor* CNovodex::CreateCapsule(const NxVec3& pos, const NxReal height, const NxReal radius, const NxReal density, NxMat33 rotation, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;
	bodyDesc.setToDefault();
	if (isKinematic)
		bodyDesc.flags = NX_BF_KINEMATIC;
	// The actor has one shape, a capsule
	NxCapsuleShapeDesc capsuleDesc;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		capsuleDesc.materialIndex = newMaterial->getMaterialIndex();
		capsuleDesc.skinWidth = physicsMaterial.SkinWidth;
	}

	if (isTrigger && isKinematic)
	{
		NxCapsuleShapeDesc dummyShape;
		dummyShape.name = "dummy";
		NxF32 sizeinc = 1.01f;
		dummyShape.height = height * sizeinc;
		dummyShape.radius = radius * sizeinc;
		dummyShape.group = GROUP_DUMMY;
		actorDesc.shapes.pushBack(&dummyShape);
	}

	if (isTrigger && density == 0)
		capsuleDesc.shapeFlags |= NX_TRIGGER_ENABLE;

	capsuleDesc.height = height;
	capsuleDesc.radius = radius;
	if (!isKinematic)
	{
		capsuleDesc.localPose.t = pos/*NxVec3(0.0f, radius + 0.5f * height, 0.0f )*/;
		capsuleDesc.localPose.M = rotation;
	}
	actorDesc.shapes.pushBack(&capsuleDesc);
	if (isKinematic)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = 10.0f; //none-zero density
	}
	else if (density)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = density;
	}
	else
	{
		actorDesc.body = NULL;
	}
	if (isKinematic)
	{
		actorDesc.globalPose.t = pos;
		actorDesc.globalPose.M = rotation;
	}
	actorDesc.name = name;
	NxActor* actor = gPhysXscene->createActor(actorDesc);

	if (actor && isTrigger)
	{
		SetActorCollisionGroup(actor, GROUP_TRIGGER);
	}
	else if (actor && actor->isDynamic())
	{
		if (!isKinematic)
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_PUSHABLE);
		else
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_NON_PUSHABLE);
	}
	else if (actor) //static actor
	{
		SetActorCollisionGroup(actor, GROUP_STATIC);
	}

	return actor;
}

NxActor* CNovodex::CreateSphere(const NxVec3& pos, const NxReal radius, const NxReal density, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;
	if( isKinematic )
		bodyDesc.flags = NX_BF_KINEMATIC;
	// The actor has one shape, a sphere
	NxSphereShapeDesc sphereDesc;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		sphereDesc.materialIndex = newMaterial->getMaterialIndex();
		sphereDesc.skinWidth = physicsMaterial.SkinWidth;
	}

	if (isTrigger && isKinematic)
	{
		NxSphereShapeDesc dummyShape;
		dummyShape.name = "dummy";
		NxF32 sizeinc = 1.01f;
		dummyShape.radius = radius * sizeinc;
		dummyShape.group = GROUP_DUMMY;
		actorDesc.shapes.pushBack(&dummyShape);
	}

	if( isTrigger && density == 0 )
		sphereDesc.shapeFlags |= NX_TRIGGER_ENABLE;

	sphereDesc.radius = radius;
	if( !isKinematic )
		sphereDesc.localPose.t = pos;
	actorDesc.shapes.pushBack(&sphereDesc);

	if( isKinematic )
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = 10.0f; //none-zero density
	}
	else if (density )
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = density;
	}
	else
	{
		actorDesc.body = NULL;
	}
	if( isKinematic )
		actorDesc.globalPose.t = pos;
	//actorDesc.globalPose.t = pos;
	actorDesc.name = name;
	NxActor* actor = gPhysXscene->createActor(actorDesc);

	if (actor && isTrigger)
	{
		SetActorCollisionGroup(actor, GROUP_TRIGGER);
	}
	else if( actor && actor->isDynamic() )
	{
		if( !isKinematic )
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_PUSHABLE );
		else
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_NON_PUSHABLE );
	}
	else if (actor) //static actor
	{
		SetActorCollisionGroup(actor, GROUP_STATIC);
	}

	return actor;	
}
   
NxActor* CNovodex::CreateBox(const NxVec3& pos, const NxVec3& boxDim, const NxReal density, NxMat33 rotation, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;
	if (isKinematic)
		bodyDesc.flags = NX_BF_KINEMATIC;
	// The actor has one shape, a box
	NxBoxShapeDesc boxDesc;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		boxDesc.materialIndex = newMaterial->getMaterialIndex();
		boxDesc.skinWidth = physicsMaterial.SkinWidth;
	}

	boxDesc.dimensions.set(boxDim.x, boxDim.y, boxDim.z);

	if (isTrigger && density == 0)
	{
		boxDesc.shapeFlags |= NX_TRIGGER_ENABLE;
	}

	if (!isKinematic)
	{
		boxDesc.localPose.t = pos;
		boxDesc.localPose.M = rotation;
	}

	if (isTrigger && isKinematic)
	{
		NxBoxShapeDesc dummyShape;
		dummyShape.name = "dummy";
		NxF32 sizeinc = 1.01f;
		dummyShape.dimensions.set(boxDim.x * sizeinc, boxDim.y * sizeinc, boxDim.z * sizeinc);
		dummyShape.group = GROUP_DUMMY;
		actorDesc.shapes.pushBack(&dummyShape);
	}

	actorDesc.shapes.pushBack(&boxDesc);

	if (isKinematic)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = 10.0f; //none-zero density
	}
	else if (density)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = density;
	}
	else
	{
		actorDesc.body = NULL;
	}
	if (isKinematic)
	{
		actorDesc.globalPose.t = pos;
		actorDesc.globalPose.M = rotation;
	}

	actorDesc.name = name;

	NxActor* actor = gPhysXscene->createActor(actorDesc);

	if (actor && isTrigger)
	{
		SetActorCollisionGroup(actor, GROUP_TRIGGER);
	}
	else if (actor && actor->isDynamic())
	{
		if (!isKinematic)
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_PUSHABLE);
		else
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_NON_PUSHABLE);
	}
	else if (actor) //static actor
	{
		SetActorCollisionGroup(actor, GROUP_STATIC);
	}

	return actor;
}

NxActor* CNovodex::CreateTriggerBox(const NxVec3& pos, const NxVec3& boxDim, NxMat33 rotation, const CChar* name, CBool isKinematic, CPhysXMaterial physicsMaterial)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	if (isKinematic)
		bodyDesc.flags = NX_BF_KINEMATIC;

	NxBoxShapeDesc boxDesc;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		boxDesc.materialIndex = newMaterial->getMaterialIndex();
		boxDesc.skinWidth = physicsMaterial.SkinWidth;
	}

	if (isKinematic)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = 10.0f; //none-zero density
	}
	else
	{
		actorDesc.body = NULL;
	}

	if (isKinematic)
	{
		NxBoxShapeDesc dummyShape;
		dummyShape.name = "dummy";
		NxF32 sizeinc = 1.01f;
		dummyShape.dimensions.set(boxDim.x * sizeinc, boxDim.y * sizeinc, boxDim.z * sizeinc);
		dummyShape.group = GROUP_DUMMY;
		actorDesc.shapes.pushBack(&dummyShape);
	}

	boxDesc.dimensions = boxDim;
	boxDesc.shapeFlags |= NX_TRIGGER_ENABLE;

	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.globalPose.t = pos;
	actorDesc.globalPose.M = rotation;
	actorDesc.name = name;
	NxActor* actor = gPhysXscene->createActor(actorDesc); 
	SetActorCollisionGroup( actor , GROUP_TRIGGER );
	return actor;
}

NxActor* CNovodex::CreateConvexMesh(CInt vertexCount, CFloat* meshVertices, const NxVec3& pos, NxMat33 rotation, const NxReal density, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial)
{
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;
	if( isKinematic )
		bodyDesc.flags = NX_BF_KINEMATIC;

	// Create descriptor for triangle mesh
	NxConvexMeshDesc convexDesc;

	//NxMaterialDesc materialDesc;
	//materialDesc.restitution = 0.0f;
	//NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);

	convexDesc.numVertices			= vertexCount;
	convexDesc.pointStrideBytes		=  3 * sizeof(CFloat);
	convexDesc.points				= meshVertices;
	convexDesc.flags				= NX_CF_COMPUTE_CONVEX;

	NxConvexMeshDesc convexDesc2;

	convexDesc2.numVertices			= vertexCount;
	convexDesc2.pointStrideBytes		=  3 * sizeof(CFloat);
	convexDesc2.points				= meshVertices;
	convexDesc2.flags				= NX_CF_COMPUTE_CONVEX | NX_CF_INFLATE_CONVEX;


	// The actor has one shape, a convex mesh
	NxConvexShapeDesc convexShapeDesc;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		convexShapeDesc.materialIndex = newMaterial->getMaterialIndex();
		convexShapeDesc.skinWidth = physicsMaterial.SkinWidth;
	}

	NxConvexShapeDesc convexShapeDesc2;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		convexShapeDesc2.materialIndex = newMaterial->getMaterialIndex();
		convexShapeDesc2.skinWidth = physicsMaterial.SkinWidth;
	}

	if( isTrigger && density == 0 )
		convexShapeDesc.shapeFlags |= NX_TRIGGER_ENABLE;
	if( isTrigger && density == 0 )
		convexShapeDesc2.shapeFlags |= NX_TRIGGER_ENABLE;

	//	convexShapeDesc.meshData = gPhysicsSDK->createConvexMesh(convexDesc);
	NxInitCooking();
	//UserStream upstream = UserStream("c:\\tmp.bin", false);
	//UserStream downstream = UserStream("c:\\tmp.bin", true);
	MemoryWriteBuffer buf;

	bool status = NxCookConvexMesh(convexDesc, buf/*upstream*/);
	if( status )
	{
		convexShapeDesc.meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data)/*downstream*/);
		NxCloseCooking();

		if( !isKinematic )
		{
			convexShapeDesc.localPose.t = pos;
			convexShapeDesc.localPose.M = rotation;
		}

		actorDesc.shapes.pushBack(&convexShapeDesc);
	}
	else
	{
		convexShapeDesc.meshData = NULL;
		NxCloseCooking();

		NxInitCooking();

		status = NxCookConvexMesh(convexDesc2, buf/*upstream*/);
		if( status )
		{
			convexShapeDesc2.meshData = gPhysicsSDK->createConvexMesh(MemoryReadBuffer(buf.data)/*downstream*/);

			if( !isKinematic )
			{
				convexShapeDesc2.localPose.t = pos;
				convexShapeDesc2.localPose.M = rotation;
			}

			actorDesc.shapes.pushBack(&convexShapeDesc2);
			NxCloseCooking();
		}
		else
		{
			NxCloseCooking();
			convexShapeDesc2.meshData = NULL;
			return NULL;
		}
	}

	if( isKinematic )
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = 10.0f;
	}
	else if (density)
	{
		actorDesc.body = &bodyDesc;
		actorDesc.density = density;
	}
	else
	{
		actorDesc.body = NULL;
	}
	if( isKinematic )
	{
		actorDesc.globalPose.t = pos;
		actorDesc.globalPose.M = rotation;
	}

	if (isTrigger && isKinematic)
	{
		NxBoxShapeDesc dummyShape;
		dummyShape.name = "dummy";
		dummyShape.dimensions.set(0.01f, 0.01f, 0.01f);
		dummyShape.group = GROUP_DUMMY;
		actorDesc.shapes.pushBack(&dummyShape);
	}

	actorDesc.name = name;
	
	NxActor *actor = gPhysXscene->createActor(actorDesc);

	if (actor && isTrigger)
	{
		SetActorCollisionGroup(actor, GROUP_TRIGGER);
	}
	else if( actor && actor->isDynamic() )
	{
		if( !isKinematic )
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_PUSHABLE );
		else
			SetActorCollisionGroup(actor, GROUP_COLLIDABLE_NON_PUSHABLE );
	}
	else if (actor) //static actor
	{
		SetActorCollisionGroup(actor, GROUP_STATIC);
	}

	return actor;
}

CBool CNovodex::CookTriangleMesh(CInt vertexCount, CInt faceCount, CFloat* meshVertices, CInt* meshFaces, const CChar* path, const CChar* name)
{
	// Create descriptor for triangle mesh
	NxTriangleMeshDesc triangleMeshDesc;

	triangleMeshDesc.numVertices = vertexCount;
	triangleMeshDesc.pointStrideBytes = 3 * sizeof(CFloat);
	triangleMeshDesc.points = meshVertices;
	triangleMeshDesc.numTriangles = faceCount;
	triangleMeshDesc.flags = 0;
	triangleMeshDesc.triangles = meshFaces;
	triangleMeshDesc.triangleStrideBytes = 3 * sizeof(CInt);
	CChar temp[MAX_NAME_SIZE];
	sprintf(temp, "%s/%s.phx", path, name);

	NxInitCooking();
	CBool status = NxCookTriangleMesh(triangleMeshDesc, UserStream(temp, false));
	NxCloseCooking();

	if (status)
	{
		return true;
	}
	else
	{
		return false;
	}
}

NxActor* CNovodex::CreateCookedTriangleMesh(CBool isTrigger, const CChar* path, const CChar* name, CPhysXMaterial physicsMaterial)
{
	CChar temp[MAX_NAME_SIZE];
	sprintf(temp, "%s%s.phx", path, name);

	NxTriangleMesh* pMesh = NULL;
	pMesh = gPhysicsSDK->createTriangleMesh(UserStream(temp, true));
	// Create TriangleMesh above code segment.

	if (!pMesh)
		return NULL;

	NxTriangleMeshShapeDesc tmsd;

	tmsd.name = name;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		tmsd.materialIndex = newMaterial->getMaterialIndex();
		tmsd.skinWidth = physicsMaterial.SkinWidth;
	}

	if (isTrigger)
		tmsd.shapeFlags |= NX_TRIGGER_ENABLE;

	tmsd.meshData = pMesh;
	tmsd.localPose.t = NxVec3(0.f, 0.0f, 0.f);
	tmsd.meshPagingMode = NX_MESH_PAGING_MANUAL;

	NxActorDesc actorDesc;
	NxBodyDesc  bodyDesc;

	actorDesc.shapes.pushBack(&tmsd);
	//Dynamic triangle mesh don't be supported anymore. So body = NULL
	actorDesc.body = NULL;
	actorDesc.globalPose.t = NxVec3(0.0f, 0.0f, 0.0f);
	actorDesc.name = name;

	NxActor *actor = gPhysXscene->createActor(actorDesc);

	if (isTrigger)
	{
		SetActorCollisionGroup(actor, GROUP_TRIGGER);
	}
	else //static actor
	{
		SetActorCollisionGroup(actor, GROUP_STATIC);
	}
	return actor;
}

NxActor* CNovodex::CreateTriangleMesh(CInt vertexCount, CInt faceCount, CFloat* meshVertices, CInt* meshFaces, CBool isTrigger, const CChar* name, CPhysXMaterial physicsMaterial)
{
	// Create descriptor for triangle mesh
	NxTriangleMeshDesc triangleMeshDesc;

	triangleMeshDesc.numVertices			= vertexCount;
	triangleMeshDesc.pointStrideBytes		= 3 * sizeof(CFloat);
	triangleMeshDesc.points				= meshVertices;
	triangleMeshDesc.numTriangles			= faceCount;
	triangleMeshDesc.flags					= 0;
	triangleMeshDesc.triangles				= meshFaces;
	triangleMeshDesc.triangleStrideBytes	= 3 * sizeof(CInt);
	
	//Alternative:	see NxMeshFlags
	//triangleMeshDesc->flags				= NX_MF_16_BIT_INDICES
	//triangleMeshDesc->triangles			= indices16;
	//triangleMeshDesc->triangleStrideBytes	= 3 * sizeof(NxU16);

	// The actor has one shape, a triangle mesh
	NxInitCooking();
	MemoryWriteBuffer buf;

	//sprintf(temp, "c:\\terrain/%s.phx", name);
	CBool status = NxCookTriangleMesh(triangleMeshDesc,/* UserStream(temp, false)*/buf);
	NxTriangleMesh* pMesh;
	if (status)
	{
		pMesh = gPhysicsSDK->createTriangleMesh(/*UserStream(temp, true)*/MemoryReadBuffer(buf.data));
	}
	else
	{
		assert(false);
		pMesh = NULL;
	}
	// Create TriangleMesh above code segment.

	NxTriangleMeshShapeDesc tmsd;

	if (physicsMaterial.HasMaterial)
	{
		NxMaterialDesc materialDesc;
		materialDesc.restitution = physicsMaterial.Restitution;
		materialDesc.staticFriction = physicsMaterial.StaticFriction;
		materialDesc.dynamicFriction = physicsMaterial.DynamicFriction;
		NxMaterial *newMaterial = gPhysXscene->createMaterial(materialDesc);
		tmsd.materialIndex = newMaterial->getMaterialIndex();
		tmsd.skinWidth = physicsMaterial.SkinWidth;
	}


	if( isTrigger )
		tmsd.shapeFlags |= NX_TRIGGER_ENABLE;

	tmsd.meshData		= pMesh;
	tmsd.userData		= &triangleMeshDesc;
	tmsd.localPose.t	= NxVec3(0.f, 0.0f, 0.f);
	tmsd.meshPagingMode = NX_MESH_PAGING_MANUAL;
	
	NxActorDesc actorDesc;
	NxBodyDesc  bodyDesc;
	
	assert(tmsd.isValid());
	actorDesc.shapes.pushBack(&tmsd);
	//Dynamic triangle mesh don't be supported anymore. So body = NULL
	actorDesc.body			= NULL;		
	actorDesc.globalPose.t	= NxVec3(0.0f, 0.0f, 0.0f);
	actorDesc.name = name;

	if (pMesh)
	{
		// Save mesh in userData for drawing
		pMesh->saveToDesc(triangleMeshDesc);
		//
		assert(actorDesc.isValid());
		NxActor *actor = gPhysXscene->createActor(actorDesc);
		assert(actor);
		if( isTrigger )
		{
			SetActorCollisionGroup(actor, GROUP_TRIGGER );
		}
		else
		{
			SetActorCollisionGroup(actor, GROUP_STATIC);
		}

		NxCloseCooking();
		return actor;
	}
	NxCloseCooking();

	return NULL;
}

NxActor* CNovodex::CreateGroundPlane(CFloat groundHeight)
{
    // Create a plane with default descriptor
    NxPlaneShapeDesc planeDesc;
	planeDesc.normal = NxVec3(0.0f, 1.0f, 0.0f);
	planeDesc.d = groundHeight;
    NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	m_planeGroundActor = gPhysXscene->createActor(actorDesc);
	m_planeGroundActor->setName("physx_ground_plane");
	SetActorCollisionGroup(m_planeGroundActor, GROUP_GROUND);
	return m_planeGroundActor;
}


CVoid CNovodex::ReleaseGroundPlane()
{
	if (m_planeGroundActor != NULL)
		gPhysXscene->releaseActor(*m_planeGroundActor);
	m_planeGroundActor = NULL;

	if (m_groundBox != NULL)
		gPhysXscene->releaseActor(*m_groundBox);
	m_groundBox = NULL;
}

CVoid CNovodex::rotateX( NxActor* actor,NxReal angle  )
{
	NxMat33 M = actor->getGlobalOrientation();
	M.rotX( NxMath::degToRad(angle) );
	actor->setGlobalOrientation( M );
}

CVoid CNovodex::rotateY( NxActor* actor,NxReal angle  )
{
	NxMat33 M = actor->getGlobalOrientation();
	M.rotY( NxMath::degToRad(angle) );
	actor->setGlobalOrientation( M );
}

CVoid CNovodex::rotateZ( NxActor* actor,NxReal angle  )
{
	NxMat33 M = actor->getGlobalOrientation();
	M.rotZ( angle );
	actor->setGlobalOrientation( M );
}

CVoid CNovodex::rotate( NxActor* actor, NxReal xRot, NxReal yRot, NxReal zRot )
{
	NxMat33 tempMatrix;
	NxMat33 globalOrientation;
	globalOrientation = actor->getGlobalOrientation();
	NxMat33 Mx = globalOrientation;
	Mx.rotX( NxMath::degToRad(xRot) );
	tempMatrix = Mx;
	NxMat33 My = globalOrientation;
	My.rotY( NxMath::degToRad(yRot) );
	tempMatrix = My * tempMatrix;
	NxMat33 Mz = globalOrientation;
	Mz.rotZ( NxMath::degToRad(zRot) );
	tempMatrix = Mz * tempMatrix;
	actor->setGlobalOrientation( tempMatrix );
}



CVoid CNovodex::debugRenderer()
{
	if( gPhysXscene )
	{
		//glUseProgram(0);
		gDebugRenderer.renderData(*gPhysXscene->getDebugRenderable());
	}
}

CVoid CNovodex::processInputs()
{
}

NxVec3 CNovodex::ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength)
{
	NxVec3 forceVec = forceStrength*forceDir;

	actor->addForce(forceVec, NX_IMPULSE, CTrue);

	return forceVec;
}

NxVec3 CNovodex::ApplyTorqueToActor(NxActor* actor, const NxVec3& torqueDir, const NxReal torqueStrength)
{
	NxVec3 torqueVec = torqueStrength*torqueDir;

	actor->addTorque(torqueVec, NX_IMPULSE, CTrue);

	return torqueVec;
}

NxVec3 CNovodex::ApplyForceToActorAtShape(NxActor* actor, NxShape* shape, const NxVec3& forceDir, const NxReal forceStrength, CBool forceMode, CBool shapeSelectMode)
{
	NxVec3 forceVec = forceStrength*forceDir;

	if (forceMode) 
	{
		if (shapeSelectMode) 
		{
			actor->addForceAtLocalPos(forceVec, shape->getLocalPosition());
		} 
		else 
		{
			actor->addForce(forceVec);
		}
	} 
	else 
	{ 
		actor->addTorque(forceVec);
	}

	return forceVec;
}

NxVec3 ApplyVelocityToActor(NxActor* actor, const NxVec3& velDir, const NxReal velStrength, CBool velMode)
{
	NxVec3 velVec = velStrength*velDir;

	if (velMode) 
	{
		actor->moveGlobalPosition(actor->getGlobalPosition() + 0.0001f * velStrength * velDir);
	} 
	else 
	{
		NxMat33 orient = actor->getGlobalOrientation();
        NxMat33 m;

		m.id();

		if (velDir == NxVec3(1,0,0))
           m.rotX(0.01f);
		else if (velDir == NxVec3(-1,0,0))
           m.rotX(-0.01f);
		else if (velDir == NxVec3(0,1,0))
           m.rotY(0.01f);
		else if (velDir == NxVec3(0,-1,0))
           m.rotY(-0.01f);
		else if (velDir == NxVec3(0,0,1))
           m.rotZ(0.01f);
		else if (velDir == NxVec3(0,0,-1))
           m.rotZ(-0.01f);

		orient = m * orient;

		actor->moveGlobalOrientation(orient);
	}
	return velVec;
}

CVoid CNovodex::InitCharacterControllers(CFloat XPos, CFloat YPos, CFloat ZPos, CFloat radius, CFloat height, CFloat skinWidth, CFloat slopeLimit, CFloat stepOffset)
{
	gCM = NULL;
	gControllers = NULL;
	gCM = NxCreateControllerManager( gAllocator );
	NxCapsuleControllerDesc desc;
	desc.position.x		= XPos;
	desc.position.y		= YPos;
	desc.position.z		= ZPos;
	desc.radius			= radius;
	desc.height			= height;
	desc.upDirection	= NX_Y;
	desc.slopeLimit = cosf(NxMath::degToRad(slopeLimit));
	desc.skinWidth = skinWidth;
	desc.stepOffset = stepOffset;
	desc.climbingMode = CLIMB_CONSTRAINED;
	desc.interactionFlag	= NXIF_INTERACTION_INCLUDE;
	desc.callback		= &gControllerHitReport;
	
	gControllers = (NxCapsuleController*)gCM->createController(gPhysXscene, desc);
}

CVoid CNovodex::ReleaseCharacterControllers()
{
	if( gCM )
		gCM->releaseController( *gControllers );
	NxReleaseControllerManager(gCM);

}

NxU32 CNovodex::MoveCharacter( const NxVec3& dispVector, NxF32 elapsedTime, NxU32 collisionGroups, NxF32 heightDelta)
{
	gControllerHitReport.SetgNbPts(0);
    NxF32 sharpness = 1.0f;
	NxU32 collisionFlags;
    NxVec3 d = dispVector * elapsedTime;

    if (heightDelta != 0.0f) 
	{
		d.y+=heightDelta;
	}
	gControllers->move(d, collisionGroups, 0.000001f, collisionFlags, sharpness);

    return collisionFlags;
}

const NxExtendedVec3 CNovodex::GetFilteredCharacterPos()
{
	return gControllers->getFilteredPosition();
}

CVoid  CNovodex::SetCharacterPos( NxExtendedVec3 pos)
{
	gControllers->setPosition( pos );
}

const NxExtendedVec3 CNovodex::GetRawCharacterPos()
{
	return gControllers->getPosition();
}

NxActor* CNovodex::GetCharacterActor()
{
	return gControllers->getActor();
}

CBool CNovodex::ResetCharacterPos()
{
	NxExtendedVec3 sp;
	sp.x = 0;
	sp.y = 0;
	sp.z = 0;
    return gControllers->setPosition(sp);
}

CBool CNovodex::ResetCharacterPos( NxExtendedVec3 pos )
{
    return gControllers->setPosition(pos);
}

CVoid CNovodex::UpdateControllers()
{
    gCM->updateControllers();
}

CVoid CNovodex::SetupGLMatrix(const NxVec3& pos, const NxMat33& orient)
{
	CFloat glmat[16];	//4x4 column major matrix for OpenGL.
	orient.getColumnMajorStride4(&(glmat[0]));
	pos.get(&(glmat[12]));

	//clear the elements we don't need:
	glmat[3] = glmat[7] = glmat[11] = 0.0f;
	glmat[15] = 1.0f;

	glMultMatrixf(&(glmat[0]));
}
char* CNovodex::CheckHit()
{
	return gTriggerReport.hitName;
}

char* CNovodex::CheckOtherActor()
{
	return gTriggerReport.otherName;
}

NxActor* CNovodex::HitActor()
{
	return gTriggerReport.hitActor;
}

CVoid TriggerReport::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
{
		hitName = NULL;
		hitActor = NULL;

		NxActor* otherActor = &otherShape.getActor();
		otherName = (char *)otherActor->getName();

		if (status & NX_TRIGGER_ON_ENTER)
		{
			// A body just entered the trigger area
			//gNbTouchedBodies++;
			NxActor* triggerActor = &triggerShape.getActor();
			hitActor = triggerActor;
			hitName = (char *)triggerActor->getName();
			if( !triggerActor || !hitActor || !hitName )
				return;

			//Trigger Objects in VScene Mode
			if (g_editorMode == eMODE_VSCENE)
			{
				if (g_mainCharacter)
					g_mainCharacter->OnTriggerEnterScript(otherName);

				for (CUInt i = 0; i < g_triggers.size(); i++)
				{
					if (g_triggers[i]->GetHasScript() && Cmp(hitName, g_triggers[i]->GetInstancePrefab()->GetScene(0)->m_instanceGeometries[0]->m_physXName))
					{
						g_triggers[i]->OnTriggerEnterScript(otherName);
						return;
					}
				}

				for (CUInt i = 0; i < g_instancePrefab.size(); i++)
				{
					CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
					if (prefab && prefab->GetHasScript())
					{
						for (CUInt j = 0; j < 3; j++)
						{
							if (prefab->GetHasLod(j))
							{
								CScene* scene = g_instancePrefab[i]->GetScene(j);
								for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
								{
									if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
									{
										g_instancePrefab[i]->OnTriggerEnterScript(otherName);
										return;
									}
								}
							}
						}
						if (g_instancePrefab[i]->GetHasCollider())
						{
							CScene* scene = g_instancePrefab[i]->GetScene(3);
							for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
							{
								if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
								{
									g_instancePrefab[i]->OnTriggerEnterScript(otherName);
									return;
								}
							}
						}
					}
				}
			}
			else if (g_editorMode == eMODE_PREFAB)
			{
				if (g_prefabProperties.m_hasScript)
				{
					CScene* scene = NULL;
					for (CUInt i = 0; i < g_scene.size(); i++)
					{
						for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
						{
							if (g_scene[i]->m_instanceGeometries[j]->m_isTrigger && Cmp(hitName, g_scene[i]->m_instanceGeometries[j]->m_physXName))
							{
								scene = g_scene[i];
								lua_getglobal(g_lua, "OnTriggerEnter");
								if (lua_isfunction(g_lua, -1))
								{
									lua_pushstring(g_lua, otherName);
									lua_pcall(g_lua, 1, 0, 0);
								}
								lua_settop(g_lua, 0);
							}
						}
					}
				}
			}
		}
		if (status & NX_TRIGGER_ON_LEAVE)
		{
			// A body just left the trigger area
			//gNbTouchedBodies--;
			NxActor* triggerActor = &triggerShape.getActor();
			hitActor = triggerActor;
			hitName = (char *)triggerActor->getName();
			if( !triggerActor || !hitActor || !hitName )
				return;

			//Trigger Objects in VScene Mode
			if (g_editorMode == eMODE_VSCENE)
			{
				if (g_mainCharacter)
					g_mainCharacter->OnTriggerExitScript(otherName);

				for (CUInt i = 0; i < g_triggers.size(); i++)
				{
					if (g_triggers[i]->GetHasScript() && Cmp(hitName, g_triggers[i]->GetInstancePrefab()->GetScene(0)->m_instanceGeometries[0]->m_physXName))
					{
						g_triggers[i]->OnTriggerExitScript(otherName);
						return;
					}
				}
				for (CUInt i = 0; i < g_instancePrefab.size(); i++)
				{
					CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
					if (prefab && prefab->GetHasScript())
					{
						for (CUInt j = 0; j < 3; j++)
						{
							if (prefab->GetHasLod(j))
							{
								CScene* scene = g_instancePrefab[i]->GetScene(j);
								for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
								{
									if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
									{
										g_instancePrefab[i]->OnTriggerExitScript(otherName);
										return;
									}
								}
							}
						}
						if (g_instancePrefab[i]->GetHasCollider())
						{
							CScene* scene = g_instancePrefab[i]->GetScene(3);
							for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
							{
								if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
								{
									g_instancePrefab[i]->OnTriggerExitScript(otherName);
									return;
								}
							}
						}
					}
				}
			}
			else if (g_editorMode == eMODE_PREFAB)
			{
				CScene* scene = NULL;
				if (g_prefabProperties.m_hasScript)
				{
					for (CUInt i = 0; i < g_scene.size(); i++)
					{
						for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
						{
							if (g_scene[i]->m_instanceGeometries[j]->m_isTrigger && Cmp(hitName, g_scene[i]->m_instanceGeometries[j]->m_physXName))
							{
								scene = g_scene[i];
								lua_getglobal(g_lua, "OnTriggerExit");
								if (lua_isfunction(g_lua, -1))
								{
									lua_pushstring(g_lua, otherName);
									lua_pcall(g_lua, 1, 0, 0);
								}
								lua_settop(g_lua, 0);
							}
						}
					}
				}
			}
		}
		//NX_ASSERT(gNbTouchedBodies>=0);

		// Mark actors in the trigger area to apply forcefield forces to them
		//NxActor* triggerActor = &triggerShape.getActor();
		//if (triggerActor->userData == (CVoid*)-1)
		//{
            if (status & NX_TRIGGER_ON_STAY)
            {
                //NxActor* otherActor = &otherShape.getActor();
                //otherActor->userData = (CVoid*)3;
				NxActor* triggerActor = &triggerShape.getActor();
				hitActor = triggerActor;
				hitName = (char *)triggerActor->getName();
				if (!triggerActor || !hitActor || !hitName)
					return;

				//Trigger Objects in VScene Mode
				if (g_editorMode == eMODE_VSCENE)
				{
					if(g_mainCharacter)
						g_mainCharacter->OnTriggerStayScript(otherName);

					for (CUInt i = 0; i < g_triggers.size(); i++)
					{
						if (g_triggers[i]->GetHasScript() && Cmp(hitName, g_triggers[i]->GetInstancePrefab()->GetScene(0)->m_instanceGeometries[0]->m_physXName))
						{
							g_triggers[i]->OnTriggerStayScript(otherName);
							return;
						}
					}

					for (CUInt i = 0; i < g_instancePrefab.size(); i++)
					{
						CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
						if (prefab && prefab->GetHasScript())
						{
							for (CUInt j = 0; j < 3; j++)
							{
								if (prefab->GetHasLod(j))
								{
									CScene* scene = g_instancePrefab[i]->GetScene(j);
									for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
									{
										if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
										{
											g_instancePrefab[i]->OnTriggerStayScript(otherName);
											return;
										}
									}
								}
							}
							if (g_instancePrefab[i]->GetHasCollider())
							{
								CScene* scene = g_instancePrefab[i]->GetScene(3);
								for (CUInt k = 0; k < scene->m_instanceGeometries.size(); k++)
								{
									if (CmpIn(hitName, g_instancePrefab[i]->GetName()) && scene->m_instanceGeometries[k]->m_isTrigger && Cmp(hitName, scene->m_instanceGeometries[k]->m_physXName))
									{
										g_instancePrefab[i]->OnTriggerStayScript(otherName);
										return;
									}
								}
							}
						}
					}
				}
				else if (g_editorMode == eMODE_PREFAB)
				{
					if (g_prefabProperties.m_hasScript)
					{
						CScene* scene = NULL;
						for (CUInt i = 0; i < g_scene.size(); i++)
						{
							for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
							{
								if (g_scene[i]->m_instanceGeometries[j]->m_isTrigger && Cmp(hitName, g_scene[i]->m_instanceGeometries[j]->m_physXName))
								{
									scene = g_scene[i];
									lua_getglobal(g_lua, "OnTriggerStay");
									if (lua_isfunction(g_lua, -1))
									{
										lua_pushstring(g_lua, otherName);
										lua_pcall(g_lua, 1, 0, 0);
									}
									lua_settop(g_lua, 0);
								}
							}
						}
					}
				}
			}
		//}
}


NxControllerAction ControllerHitReport::  onShapeHit(const NxControllerShapeHit& hit)
	{

		//RenderTerraintriangle(hit.faceID);

        if (1 && hit.shape)
        {
            NxCollisionGroup group = hit.shape->getGroup();
            if (group == GROUP_COLLIDABLE_PUSHABLE )
            {
                NxActor& actor = hit.shape->getActor();

                if (actor.isDynamic())
                {
                    if ((gPts[gNbPts].x!=hit.worldPos.x) || (gPts[gNbPts].y!=hit.worldPos.y) || (gPts[gNbPts].z!=hit.worldPos.z))
                    {
                        gPts[gNbPts++].x = (NxReal)hit.worldPos.x;
                        gPts[gNbPts++].y = (NxReal)hit.worldPos.y;
                        gPts[gNbPts++].z = (NxReal)hit.worldPos.z;
                        if (gNbPts==MAX_NB_PTS)	gNbPts=0;
                    }

				    // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
				    // useless stress on the solver. It would be possible to enable/disable vertical pushes on
				    // particular objects, if the gameplay requires it.
				    if (hit.dir.y==0.0f)
				    {
						NxF32 coeff = actor.getMass() * hit.length * g_physXProperties.m_fCharacterPower;
						actor.addForce( hit.dir*coeff, NX_IMPULSE );						
					}
				}
			}
		}

		return NX_ACTION_NONE;
    }

NxControllerAction  ControllerHitReport::onControllerHit(const NxControllersHit& hit)
{
    return NX_ACTION_NONE;
}
CVoid ControllerHitReport::SetgNbPts(NxU32 val)
{
	gNbPts = val;
}

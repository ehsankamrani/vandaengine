//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#define NOMINMAX
#include <windows.h>
#include "../GraphicsEngine/OpenGL.h"
#include "../common/utility.h"
#include "NxDebugRenderer.h"
#include "UserAllocator.h"
#include <PhysX/NxPhysics.h>
#include <PhysX/NxCooking.h>
#include <PhysX/NxController.h>
#include <PhysX/NxControllerManager.h>
#include <PhysX/NxController.h>
//#include <PhysX/NxBoxController.h>
#include <PhysX/NxCapsuleController.h>
#include <PhysX/NxExtended.h>
#include <PhysX/NxMath.h>
#include "stream.h"
#include "NXU_Helper.h"
#include <map>
#include <vector>
#include <stdio.h>
#include <Defines.h>

//#include "TriggerReport.h"
#define SKINWIDTH 0.01f

#pragma comment( lib, "physXLoader.lib" )
#pragma comment( lib, "NxCharacter.lib" )
#pragma comment( lib, "PhysXCooking.lib" )

#define MAX_NB_PTS 100

extern NxScene*  gPhysXscene;
extern NxPhysicsSDK* gPhysicsSDK;
enum GameGroup
{
	//GROUP_NON_COLLIDABLE,
	GROUP_COLLIDABLE_NON_PUSHABLE,
	GROUP_COLLIDABLE_PUSHABLE,
    GROUP_COLLIDABLE_NON_PUSHABLE_NO_CAMERA_HIT,
	GROUP_TRIGGER,
	GROUP_STATIC,
	GROUP_DUMMY,
	GROUP_GROUND,
};


enum CMoveCharacter
{
	MOVE_FRONT,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_FRONT_RIGHT,
	MOVE_FRONT_LEFT,
	MOVE_BACK_RIGHT,
	MOVE_BACK_LEFT,
	MOVE_UP,
	MOVE_DOWN,
	IDLE,
};

#define COLLIDABLE_MASK	(1<<GROUP_COLLIDABLE_NON_PUSHABLE) | (1<<GROUP_COLLIDABLE_PUSHABLE) | (1<<GROUP_COLLIDABLE_NON_PUSHABLE_NO_CAMERA_HIT) | (1<<GROUP_STATIC) | (1<<GROUP_GROUND)

using namespace std;
extern std::map< CUInt, NxMaterial* > g_physXMaterial;

class ControllerHitReport : public NxUserControllerHitReport
{ 
private:
    NxVec3			  gPts[MAX_NB_PTS];
	NxU32			  gNbPts;
public:
	CVoid SetgNbPts(NxU32 val);
	virtual NxControllerAction  onShapeHit(const NxControllerShapeHit& hit);
    virtual NxControllerAction  onControllerHit(const NxControllersHit& hit);
};

//NxI32 gNbTouchedBodies;

class TriggerReport : public NxUserTriggerReport 
{
friend class CNovodex;
private:
	char* hitName;
	char* otherName;
	NxActor* hitActor;
public:
	virtual CVoid onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
} ;


class CNovodex
{ 
public:
	TriggerReport gTriggerReport;
	NxTriangleMeshDesc* triangleMeshDesc;
	ControllerHitReport gControllerHitReport;
	DebugRenderer     gDebugRenderer;
	NxVec3            m_defaultGravity;
	NxVec3		      zero;
	CBool			  gJump;
	UserAllocator* gAllocator;
	NxControllerManager* gCM;
	NxCapsuleController* gControllers;
	NxF32             gTimestepMultiplier;
	NxExtendedVec3	  gCharacterPos;
	CBool			  bPushCharacter;
	CBool			  m_pushCharacter;
	NxVec3			  gCharacterVec;
	NxF32			  gCharacterWalkSpeed;
	NxF32			  gCharacterRunSpeed;
	CBool			  bFixedStep;
	NxF32			  jumpTime;
	NxF32			  m_V0;
	NxVec3 gDir;                       //camera direction 
	NxVec3 gRightDir;                  //Camera right direction  
	NxF32 dist;
	CFloat gDesiredDistance; //Camera distance from character
	//3ds Max scene
	CBool m_hasScene;
	CChar m_sceneName[MAX_NAME_SIZE];
	CVec3f m_horizontalDisp;
	NxF32 GetHeight(NxF32 elapsedTime);
	NxActor* m_groundBox;
	CInt m_currentMoveDirection;
	CInt m_previousMoveDirection;

private:
	NxRay gWorldRay;
	NxVec3 disp;    
	NxReal deltaTime;
	NxF32 cameraHit(); 
	NxReal updateTime();

public:
	//3ds Max Scene 
	CVoid SetSceneName( CChar* sceneName ) {  Cpy( m_sceneName, sceneName ); m_hasScene = CTrue; }
	CVoid SetScene( CBool scene ) { if( scene ) m_hasScene = CTrue; else m_hasScene = CFalse; }

	CVoid debugRenderer();
	CVoid GetCameraAndCharacterPositions( const CFloat pitch, const CFloat yaw, NxVec3& cameraPos, NxVec3& characterPos, NxVec3& cameraDirection );
	CVoid runPhysics( NxVec3 forceDirection, CFloat forceSpeed, CInt moveDirection, CFloat elapsedTime );
	CVoid UpdateCharacter(NxVec3 forceDirection, CFloat forceSpeed, CFloat deltaTime, CInt moveDirection );
	CVoid StartJump(NxF32 v0);
	CVoid StopJump();
	CVoid SetActorCollisionGroup(NxActor* actor, NxCollisionGroup group);
	CVoid PostUpdateCharacter();
	CVoid SetupGLMatrix(const NxVec3& pos, const NxMat33& orient);
	CBool CookTriangleMesh(CInt vertexCount, CInt faceCount, CFloat* meshVertices, CInt* meshFaces, const CChar* path, const CChar* name);
	NxActor* CreateCookedTriangleMesh(CBool isTrigger, const CChar* path, const CChar* name, CPhysXMaterial physicsMaterial);
	NxActor* CreateTriangleMesh(CInt vertexCount, CInt faceCount, CFloat* meshVertices, CInt* meshFaces, CBool isTrigger, const CChar* name, CPhysXMaterial physicsMaterial);
	NxActor* CreateConvexMesh(CInt vertexCount, CFloat* meshVertices, const NxVec3& pos, NxMat33 rotation, const NxReal densit, const CChar* name, CBool IsTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial);

	CNovodex();
	~CNovodex();
    CBool debugMode; 
	CBool wireFrame;
	CBool initNx(CFloat XCharacterPos, CFloat YCharacterPos, CFloat ZCharacterPos, CFloat crtlRadius = 2.5f, CFloat ctrlHeight = 0.01f, CFloat crtSlopeLimit = cosf(NxMath::degToRad(45.0f)), CFloat crtSkinWidth = 0.1f, CFloat crtStepOffset = 0.1f, CBool createScene = CTrue);
	CVoid releaseNx();

	NxActor* CreateBox(const NxVec3& pos, const NxVec3& boxDim, const NxReal density, NxMat33 rotation, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial);
	NxActor* CreateSphere(const NxVec3& pos, const NxReal radius, const NxReal density, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial);
	NxActor* CreateCapsule(const NxVec3& pos, const NxReal height, const NxReal radius, const NxReal density, NxMat33 rotation, const CChar* name, CBool isTrigger, CBool isKinematic, CPhysXMaterial physicsMaterial);
	//	NxActor* CreateBridge(const NxVec3& pos, const NxVec3& boxDim,const NxReal rDegree);

	NxActor* CreateGroundPlane(CFloat groundHeight);
	CVoid ReleaseGroundPlane();
	NxActor* m_planeGroundActor;
	CVoid rotate( NxActor* actor, NxReal xRot, NxReal yRot, NxReal zRot );
	CVoid rotateX( NxActor* actor, NxReal angle );
	CVoid rotateY( NxActor* actor, NxReal angle );
	CVoid rotateZ( NxActor* actor, NxReal angle );

	CVoid processInputs();
	NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength);
	NxVec3 ApplyTorqueToActor(NxActor* actor, const NxVec3& torqueDir, const NxReal torqueStrength);
	NxVec3 ApplyForceToActorAtShape(NxActor* actor, NxShape* shape, const NxVec3& forceDir, const NxReal forceStrength, CBool forceMode, CBool shapeSelectMode);
	NxVec3 ApplyVelocityToActor(NxActor* actor, const NxVec3& velDir, const NxReal velStrength, CBool velMode);
	NxActor* CreateTriggerBox(const NxVec3& pos, const NxVec3& boxDim, NxMat33 rotation, const CChar* name, CBool isKinematic, CPhysXMaterial physicsMaterial);
	CVoid InitCharacterControllers(CFloat XPos, CFloat YPos, CFloat ZPos, CFloat radius, CFloat height, CFloat skinWidth, CFloat slopeLimit, CFloat stepOffset);
	CVoid ReleaseCharacterControllers();
	NxU32 MoveCharacter(const NxVec3& dispVector, NxF32 elapsedTime, NxU32 collisionGroups, NxF32 heightDelta);
	const NxExtendedVec3 GetFilteredCharacterPos();
	CVoid SetCharacterPos( NxExtendedVec3 pos );
	const NxExtendedVec3 GetRawCharacterPos();
	NxActor* GetCharacterActor();
	CBool ResetCharacterPos();
	CBool ResetCharacterPos( NxExtendedVec3 pos );
	CVoid UpdateControllers();
	char* CheckHit();
	char* CheckOtherActor();
	NxActor* HitActor();
	NX_BOOL LoadScene(const CChar *pFilename,NXU::NXU_FileType type );
};


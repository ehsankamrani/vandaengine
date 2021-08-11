// ===============================================================================
//						  NVIDIA PHYSX SDK TRAINING PROGRAMS
//			                     COMMON LESSON CODE
//
//						    Written by Bob Schade, 5-1-06
// ===============================================================================

#ifndef COMMONCODE_H
#define COMMONCODE_H
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glut.h>
#include <stdio.h>

#include "NxPhysics.h"
#include "DrawObjects.h"
#include "UserData.h"
#include "HUD.h"

#include "Stream.h"
#include "NxCooking.h"

#include "DebugRenderer.h"
#include "UserAllocator.h"
#include "ErrorStream.h"


bool IsSelectable(NxActor* actor);
void SelectNextActor();
void SelectNextShapeOnActor(NxActor* actor);

void ProcessCameraKeys();
void SetupCamera();

void RenderActors(bool shadows);
void DrawForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color);
void DrawForce2(NxActor* actor, NxVec3& forceVec, const NxVec3& color);
void DrawForceAtShape(NxActor* actor, NxShape* shape, NxVec3& forceVec, const NxVec3& color);

void DisableAKey(int key);

NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength, bool forceMode);
void ProcessForceKeys();

NxVec3 ApplyForceToActorAtShape(NxActor* actor, NxShape* shape, const NxVec3& forceDir, const NxReal forceStrength, bool forceMode, bool actorSelectMode);
void ProcessForceAtShapeKeys();

NxVec3 ApplyVelocityToActor(NxActor* actor, const NxVec3& velDir, const NxReal velStrength, bool velMode);
NxVec3 MoveActor(NxActor* actor, const NxVec3& moveDir, const NxReal moveStrength, bool moveMode);
void ProcessMoveKeys();

void ProcessInputs();

void RenderCallback();
void ReshapeCallback(int width, int height);
void IdleCallback();
void KeyboardCallback(unsigned char key, int x, int y);
void KeyboardUpCallback(unsigned char key, int x, int y);
void SpecialKeys(unsigned char key, int x, int y);
void SpecialCallback(int key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);
void ExitCallback();
void InitGlut(int argc, char** argv, char* lessonTitle);

NxActor* CreatePyramid(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);
NxActor* CreateGem(const NxVec3& pos, const NxVec3& boxDim, const NxReal density);

void InitializeHUD();

void InitNx();
void ReleaseNx();
void ResetNx();

NxReal getElapsedTime();
void StartPhysics();
void GetPhysicsResults();

void ReleaseActor(NxActor* actor, NxScene* scene);
void ReleaseScene(NxScene* scene);
void ReleasePhysicsSDK(NxPhysicsSDK* pSDK);

#endif  // COMMONCODE_H




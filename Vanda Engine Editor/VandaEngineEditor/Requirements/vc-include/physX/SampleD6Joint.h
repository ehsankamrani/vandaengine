// ===============================================================================
//						  NVIDIA PhysX SDK Sample ProgramS
//					      SIX DEGREE OF FREEDOM JOINTS
//
//						 Written by Bob Schade, 10-15-04
// ===============================================================================

#ifndef SAMPLED6JOINT_H
#define SAMPLED6JOINT_H

#include <GL/glut.h>
#include <stdio.h>

#include "NxPhysics.h"
#include "DebugRenderer.h"
#include "DrawObjects.h"
#include "Timing.h"
#include "Actors.h"
#include "Joints.h"
#include "ErrorStream.h"

void PrintControls();
NxVec3 ApplyForceToActor(NxActor* actor, const NxVec3& forceDir, const NxReal forceStrength, bool forceMode);
void SelectNextActor();
void ProcessKeys();

void SetupCamera();
void RenderActors(bool shadows);
void DrawForce(NxActor* actor, NxVec3& forceVec, const NxVec3& color);

void RenderCallback();
void ReshapeCallback(int width, int height);
void IdleCallback();
void KeyboardCallback(unsigned char key, int x, int y);
void KeyboardUpCallback(unsigned char key, int x, int y);
void SpecialCallback(int key, int x, int y);
void MouseCallback(int button, int state, int x, int y);
void MotionCallback(int x, int y);
void InitGlut(int argc, char **argv);

NxD6Joint* CreateD6Joint(NxActor* a0, NxActor* a1, const NxVec3& globalAnchor, const NxVec3& globalAxis);

bool InitNx();
void ReleaseNx();
void ResetNx();

NxReal UpdateTime();
void RunPhysics();

#endif  // SAMPLED6JOINT_H

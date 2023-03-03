// ===============================================================================
//						  NVIDIA PhysX SDK Sample ProgramS
//					                CLOTH
//
//		 Written by Matthias Müller-Fischer, Brun Heidelberger
// ===============================================================================

#ifndef SAMPLE_CLOTH_H
#define SAMPLE_CLOTH_H

#include <GL/glut.h>
#include <stdio.h>

#include "NxPhysics.h"
#include "NxCooking.h"
#include "DebugRenderer.h"
#include "DrawObjects.h"
#include "Actors.h"
#include "Joints.h"
#include "Stream.h"

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

bool InitNx();
void ReleaseNx();
void ResetNx();

NxReal UpdateTime();
void RunPhysics();

int main(int argc, char** argv);

#endif  // SAMPLE_CLOTH_H

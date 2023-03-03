// ===============================================================================
//						  NVIDIA PhysX SDK Sample ProgramS
//					                PARTICLE FLUID
//
//		 Written by Simon Schirm, Philipp Hatt
// ===============================================================================

#ifndef SAMPLE_PARTICLE_FLUID_H
#define SAMPLE_PARTICLE_FLUID_H

#include <stdio.h>

#include "NxPhysics.h"
#include "NxCooking.h"
#include "DebugRenderer.h"
#include "ErrorStream.h"
#include "DrawObjects.h"

#include "ActorPicking.h"
#include "Stream.h"
#include "CookASE.h"
#include "Timing.h"
#include "GLFontRenderer.h"

#include "MyFluid.h"
#include <GL/glut.h>

#include "Terrain.h"
#include "TerrainRender.h"
#include "cooking.h"

bool InitNx();
void ReleaseNx();
void ResetNx();

class SampleParticleFluid
{
public:
	virtual void setup() = 0;
	virtual void cleanup()										= 0;
	virtual void update()										= 0;
	virtual void onKeyPress(unsigned char key, int x, int y)	= 0;
	virtual const char* getName()								= 0;
};

class SampleCreate: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y) {}
	virtual const char* getName() { return "Create"; }
};

class SampleEmitter: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual const char* getName() { return "Emitter"; }
};

class SampleCollision: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual const char* getName() { return "Collision"; }
};

class SampleForce: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual const char* getName() { return "Force"; }
};

class SampleEvents: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y) {}
	virtual const char* getName() { return "Events"; }
};

class SampleUserData: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual const char* getName() { return "UserData"; }
};

class SamplePacketData: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual const char* getName() { return "PacketData"; }
};

class SampleFuturemark: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y) {}
	virtual const char* getName() { return "Futuremark"; }
};

class SampleCollisionStressTest: public SampleParticleFluid
{
public:
	virtual void setup();
	virtual void cleanup();
	virtual void update() {}
	virtual void onKeyPress(unsigned char key, int x, int y) {}
	virtual const char* getName() { return "Collision Stress Test"; }
};

void SetTitleString(const char *demoName);
void SetHelpString(const char *demoKeyString);

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

NxReal UpdateTime();
void WaitForPhysics();
void RunPhysics();

int main(int argc, char** argv);

#endif  // SAMPLE_PARTICLE_FLUID_H

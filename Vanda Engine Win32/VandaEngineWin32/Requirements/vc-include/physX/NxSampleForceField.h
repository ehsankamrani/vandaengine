// ===============================================================================
//
//						  NVIDIA PhysX SDK Sample ProgramS
//					                FORCE FIELDS
//
// ===============================================================================

#ifndef SAMPLE_FORCE_FIELD_H
#define SAMPLE_FORCE_FIELD_H

#include <GL/glut.h>
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

bool InitNx();
void ReleaseNx();
void ResetNx();

//Interface for the force field demos
class ForceFieldSample
{
public:
	virtual void setup()										= 0;
	virtual void cleanup()										= 0;
	virtual void update()										= 0;
	virtual void onKeyPress(unsigned char key, int x, int y)	= 0;
	virtual void onVirtualKeyPress(int key, int x, int y)		= 0;
	virtual void processKey(int key)							= 0;
	virtual void draw()											= 0;
};

//See VortexSample.cpp for implementation of this demo
class SampleVortex: public ForceFieldSample
{
public:
	SampleVortex();
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual void onVirtualKeyPress(int key, int x, int y);
	virtual void processKey(int key) {}
	virtual void draw() {}
protected:

	void init();
	void moveForceField();
	void createVortexForceField(const NxVec3& pos, NxActor* actor, NxScene* scene);

	bool m_forceFieldMoved;
	bool m_switchExcludeShape;
	bool m_excludeGroupEnabled;
	NxMat34 m_forceFieldTransform;
	NxActor* m_kinematicActor;
	NxForceFieldShape* m_excludeShape;
	NxForceFieldShapeGroup* m_excludeGroup;
};

//See WindSample.cpp for implementation of this demo
class SampleWind: public ForceFieldSample
{
public:
	SampleWind();
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual void onVirtualKeyPress(int key, int x, int y);
	virtual void processKey(int key) {}
	virtual void draw() {}
protected:

	void init();
	void createWindForceField(const NxVec3& pos, NxActor* actor, NxScene* scene);
	void setupScaling();

	bool m_switchExcludeShape;
	bool m_excludeGroupEnabled;
	NxForceFieldShape* m_excludeShape;
	NxForceFieldShapeGroup* m_excludeGroup;
	NxForceFieldLinearKernel* m_linearKernel;
	NxI32 m_gushingWind;
	float m_windPhase;

	NxForceFieldMaterial m_rbMaterial;
	NxForceFieldMaterial m_fluidMaterial;
	NxForceFieldMaterial m_clothMaterial;
	NxForceFieldMaterial m_softBodyMaterial;

};

//See ExplosionSample.cpp for implementation of this demo
class SampleExplosion: public ForceFieldSample
{
public:
	SampleExplosion();
	virtual void setup();
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual void onVirtualKeyPress(int key, int x, int y);
	virtual void processKey(int key) {}
	virtual void draw();
protected:

	void init();
	void createExplosionForceField(const NxVec3& pos, NxActor* actor, NxScene* scene);

	NxArray<NxActor*> m_debrisActors;
	NxActor* m_kinematicActor;
	NxVec3 m_explosionPos;
	NxU32 m_explosionFrame;
	NxForceFieldShape* m_inclusionShape;
	NxForceFieldShape* m_excludeShape;

	NxForceFieldShapeGroup* m_excludeGroup;
	NxForceFieldShapeGroup* m_inclusionGroup;
};

//Some functions used by the main application
void SetTitleString(char *demoName);
void SetHelpString(char *demoKeyString);

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

#endif  // SAMPLE_FORCE_FIELD_H

// ===============================================================================
//
//						  NVIDIA PHYSX SDK SAMPLE PROGRAMS
//					                FORCE FIELDS
//
// ===============================================================================

#ifndef COMMON_FORCE_FIELD_H
#define COMMON_FORCE_FIELD_H

#include <GL/glut.h>
#include <stdio.h>

#include "NxPhysics.h"
#include "NxCooking.h"
#include "DebugRenderer.h"
#include "ErrorStream.h"
#include "DrawObjects.h"

#include "Stream.h"
#include "Timing.h"
#include "GLFontRenderer.h"

struct ParticleSDK
{
	NxVec3	position;
	NxVec3  velocity;
	NxReal	density;
	NxReal  lifetime;
	NxU32	id;
	NxVec3	collisionNormal;
};

//Interface for the force field demos
class MyForceField
{
public:
	virtual void setup(NxScene* scene)							= 0;
	virtual void cleanup()										= 0;
	virtual void update()										= 0;
	virtual void onKeyPress(unsigned char key, int x, int y)	= 0;
	virtual void onVirtualKeyPress(int key, int x, int y)		= 0;
	virtual void processKey(int key)							= 0;
	virtual void draw()											= 0;
	NxForceField* getForceField()		{ return m_forceField;	   };
	NxActor*	  getForceFieldActor()	{ return m_forceFieldActor;};
protected:
	NxForceField*	m_forceField;
	NxScene*		m_scene;
	NxActor*		m_forceFieldActor;
};

//See VortexSample.cpp for implementation of this demo
class SampleVortex: public MyForceField
{
public:
	SampleVortex();
	virtual void setup(NxScene* scene);
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
	void createFluid();

	bool m_forceFieldMoved;
	bool m_switchExcludeShape;
	bool m_excludeGroupEnabled;
	NxMat34						m_forceFieldTransform;
	NxActor*					m_kinematicActor;
	NxForceFieldShape*			m_excludeShape;
	NxForceFieldShapeGroup*		m_excludeGroup;
	NxU32						m_ParticleBufferSize;
};

//See WindSample.cpp for implementation of this demo
class SampleWind: public MyForceField
{
public:
	SampleWind();
	virtual void setup(NxScene* scene);
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
	NxForceFieldShape*			m_excludeShape;
	NxForceFieldShapeGroup*		m_excludeGroup;
	NxForceFieldLinearKernel*	m_linearKernel;
	NxI32						m_gushingWind;
	float						m_windPhase;

	NxForceFieldMaterial		m_rbMaterial;
	NxForceFieldMaterial		m_fluidMaterial;
	NxForceFieldMaterial		m_clothMaterial;
	NxForceFieldMaterial		m_softBodyMaterial;

};

//See ExplosionSample.cpp for implementation of this demo
class SampleExplosion: public MyForceField
{
public:
	SampleExplosion();
	virtual void setup(NxScene* scene);
	virtual void cleanup();
	virtual void update();
	virtual void onKeyPress(unsigned char key, int x, int y);
	virtual void onVirtualKeyPress(int key, int x, int y);
	virtual void processKey(int key) {}
	virtual void draw();
protected:

	void init();
	void createExplosionForceField(const NxVec3& pos, NxActor* actor, NxScene* scene);

	NxArray<NxActor*>		m_debrisActors;
	NxActor*				m_kinematicActor;
	NxVec3					m_explosionPos;
	NxU32					m_explosionFrame;
	NxForceFieldShape*		m_inclusionShape;
	NxForceFieldShape*		m_excludeShape;

	NxForceFieldShapeGroup* m_excludeGroup;
	NxForceFieldShapeGroup* m_inclusionGroup;
};

#endif  // COMMON_FORCE_FIELD_H

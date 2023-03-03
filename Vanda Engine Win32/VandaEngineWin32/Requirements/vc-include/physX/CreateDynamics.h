#ifndef CREATE_DYNAMICS_H

#define CREATE_DYNAMICS_H

#include "TetraGraphics.h"


// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the CREATEDYNAMICS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// CREATEDYNAMICS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CREATEDYNAMICS_EXPORTS
#define CREATEDYNAMICS_API __declspec(dllexport)
#else
#define CREATEDYNAMICS_API __declspec(dllimport)
#endif

class NxTetraInterface;

class CreateDynamicsInterface
{
public:
  virtual const char * cdi_getFileName(const char *fname,bool search) = 0; // convert file name into full path.
  virtual void         cdi_output(const char *str) = 0;
};

enum CD_Format
{
	CD_PSCL    = (1<<0),
	CD_XML     = (1<<1),
  CD_COLLADA = (1<<2),
  CD_ALL = (CD_PSCL | CD_XML | CD_COLLADA )
};

class CreateDynamicsMesh
{
public:
  unsigned int	mVcount;  // number of input vertices.
  const void   *mVertices; // vertices.
  unsigned int  mVstride;  // vertex stride.
  unsigned int  mTcount;   // number of triangles.
  unsigned int *mIndices;  // triangle indices.
};

class CreateDynamicsResult
{
public:
	CreateDynamicsResult(void)
	{
		init();
	}

  void init(void)
  {
	  mBoneCount = 0;          // number of input bones
	  mIgnoreCount = 0;        // number of bones ignored.
	  mCollapseCount = 0;      // number of bones collapsed.
    mActorCount = 0;         // number of actors created
    mShapeCount = 0;         // number of shapes
    mJointCount = 0;         // number of joints
    mBodyPairCount = 0;      // number of body pair collision flags
    mBoxCount = 0;           // number of boxes produced
    mSphereCount = 0;        // number of spheres
    mNullCount = 0;          // number of 'null' placeholder actors.
    mCompoundCount = 0;      // number of compound shapes
    mCapsuleCount = 0;       // number of capsules
    mConvexCount = 0;        // number of convdex.
    mClothCount = 0;         // number of pieces of cloth.
    mClothVertices = 0;      // number of cloth vertices.
    mClothTriangles = 0;     // number of cloth triangles.
	}
	unsigned int  mBoneCount;          // number of input bones
	unsigned int  mIgnoreCount;        // number of bones ignored.
	unsigned int  mCollapseCount;      // number of bones collapsed.
  unsigned int	mActorCount;         // number of actors created
  unsigned int  mShapeCount;         // number of shapes
  unsigned int  mJointCount;         // number of joints
  unsigned int  mBodyPairCount;      // number of body pair collision flags
  unsigned int  mBoxCount;           // number of boxes produced
  unsigned int  mSphereCount;        // number of spheres
  unsigned int  mCapsuleCount;       // number of capsules
  unsigned int  mConvexCount;        // number of convdex.
  unsigned int  mNullCount;
  unsigned int  mCompoundCount;
  unsigned int  mClothCount;         // number of pieces of cloth.
  unsigned int  mClothVertices;      // number of cloth vertices.
  unsigned int  mClothTriangles;     // number of cloth triangles.
};

class CustomBodyRuleInterface;
class RenderDebug;

class CreateDynamicsAPI
{
public:

  virtual bool           createDynamics(const char              *fname,  // name of source mesh.
                                        const char              *rules,  // name of 'rules' file.
                                        CD_Format                format,
                                        CreateDynamicsResult    *result,
                                        CustomBodyRuleInterface *iface=0) = 0;

  virtual bool           createDynamics(const char              *fname,  // name of source mesh.
                                        const char              *rules,  // name of 'rules' file.
  																			CreateDynamicsMesh      &mesh,   // input mesh.
                                        CD_Format                format,
                                        CreateDynamicsResult    *result) = 0;

  virtual const char **  getSkeleton(const char *fname,int &boneCount) = 0;

  virtual NxTetraInterface *getTetraInteface(void) = 0; // loads the tetra maker DLL and returns the interface pointer.

  virtual void setRenderDebug(RenderDebug *rd) = 0;

};


class SOFTBODY::SoftMeshInterface;

extern "C"
{
// Auto-Generate a ragdoll model for this input mesh file.
// using the rules file name
// if you want PSCL output in addition to NxUstream set this bool to true.
// the interface to translate a file name.
 CREATEDYNAMICS_API CreateDynamicsAPI * getCreateDynamics(CreateDynamicsInterface *callback);				// get the create dynamics virtual interface
 CREATEDYNAMICS_API bool loadSoftMeshPSK(const char *oname, SOFTBODY::SoftMeshInterface *smi);
}


#endif

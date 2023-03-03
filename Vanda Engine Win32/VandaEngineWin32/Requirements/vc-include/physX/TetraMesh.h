#ifndef TETRA_MESH_H

#define TETRA_MESH_H

#include <NxPhysics.h>
#include <string.h>
#include "TetraGraphics.h"

class NxSoftBodyMesh;

namespace SOFTBODY
{

class TetraVertex;
class SoftVertexPool;

// This helper class will read in a tetrahedral mesh file and bind it to a
// Wavefront OBJ file for rendering and simulation purposes.

class TetraVertex
{
public:
  TetraVertex(void) { };
  TetraVertex(const TetraGraphicsVertex &v)
  {
  	mPos.x = v.mPos[0];
  	mPos.y = v.mPos[1];
  	mPos.z = v.mPos[2];
  	mNormal.x = 1;  // we don't copy the normal since it is computed.
  	mNormal.y = 0;  // we don't copy the normal since it is computed.
  	mNormal.z = 0;  // we don't copy the normal since it is computed.
  	mTexel[0] = v.mTexel[0];
  	mTexel[1] = v.mTexel[1];
  	mIndex = 0;
  	mBarycentric.x = 0;
  	mBarycentric.y = 0;
  	mBarycentric.z = 0;
  }

	void copyTo(TetraGraphicsVertex &v) const
	{
		v.mPos[0]    = mPos.x;
		v.mPos[1]    = mPos.y;
		v.mPos[2]    = mPos.z;
		v.mNormal[0] = mNormal.x;
		v.mNormal[1] = mNormal.y;
		v.mNormal[2] = mNormal.z;
		v.mTexel[0]  = mTexel[0];
		v.mTexel[1]  = mTexel[1];
	}

  NxVec3  mPos;
  NxVec3  mNormal;
  NxReal  mTexel[2];
  NxU32   mIndex;       // the original index number.
  NxVec3  mBarycentric;  // the baycentric co-ordinate
};

class TetraMesh
{
public:
  TetraMesh(void)
  {
    mMaterial = 0;
		mTetraVbuffer = 0;
    mBoxMaterial = 0;
    mBoxVbuffer = 0;
    mDeletions = 0;
  }

  TetraMesh(NxU32 vcount,const float *vertices,NxU32 tcount,const unsigned int *indices);
  ~TetraMesh(void);

  void render(bool wireFrame);

	void render(const NxVec3 *vertices,
	            const NxU32 *indices,
              NxU32 vcount,
              NxU32 tcount,
              bool considerDeletions,
	            bool wireFrame);

  void applyLinks(TetraVertex *tverts,
                  NxU32 tvcount,
                  const NxVec3 *vertices,
                  const NxU32 *indices,
                  TetraGraphicsVertex *gverts);

  void onDeviceReset(void);
  void setDeletions(NxU8 *deletions) { mDeletions = deletions; };


  void buildLinks(NxArray< TetraVertex > &verts); // compute the links between these source graphics vertices and the tetrahedral mesh

  NxArray< NxVec3 >        mPositions;
  NxArray< NxU32  >        mIndices;
  NxBounds3                mBounds;
  float                    mShrinkDistance;



// for visualization
  TetraMaterial                 *mMaterial;
  TetraMaterial                 *mBoxMaterial;
  void                          *mTetraVbuffer;
  void                          *mBoxVbuffer;
  NxU8                          *mDeletions;
  NxU32                          mLastVcount;
  NxU32                          mLastTcount;
};



// represents the
class TetraModelSection
{
public:

  TetraModelSection(TetraMaterial *mat);
  ~TetraModelSection(void);

	void addTri(NxU32 i1,NxU32 i2,NxU32 i3)
	{
		mIndices.push_back(i1);
		mIndices.push_back(i2);
		mIndices.push_back(i3);
	}

	void render(const NxArray< TetraVertex > &vertices,void *vertexBuffer);

  void onDeviceReset(void);

  void applyNormals(TetraGraphicsVertex *verts);
  void applyNormals(TetraVertex *verts);

  TetraMaterial         *mMaterial;
  NxArray< NxU32       > mIndices;
  void                  *mIndexBuffer;
};

class TetraPositionMesh
{
public:
  NxArray< NxVec3 > mPositions;
  NxArray< NxU32  > mIndices;
  NxArray< NxU32  > mTranslationTable; // translates graphics vertices to position vertices.
};

class TetraModel : public SoftMeshInterface
{
public:

	TetraModel(const char *obj,const char *tet);
  TetraModel(NxSoftBodyMesh *mesh,const char *userProperties);
  ~TetraModel(void);

  TetraMesh * getTetraMesh(void) const { return mTetraMesh; };

  const TetraPositionMesh& getPositionMesh(void);

  bool isMatch(const char *obj) const;
  bool isOk(void) const;

  void setSoftBodyMesh(NxSoftBodyMesh *nxmesh) { mNxSoftBodyMesh = nxmesh; };
  NxSoftBodyMesh * getSoftBodyMesh(void) const { return mNxSoftBodyMesh; };

	void addVertex(const TetraVertex &tv)
	{
		NxU32 index = mVertices.size();
		mVertices.push_back(tv);
	}

	TetraMaterial *locateMaterial(const char *name);

	TetraModelSection *addTetraModelSection(TetraMaterial *tm)
	{
		TetraModelSection *ret = new TetraModelSection(tm);
		mSections.push_back(ret);
		return ret;
	}

	void render(const NxVec3 *vertices,const NxU32 *indices);

  void render(void);

  void addTetraMaterial(TetraMaterial *mat)
  {
    mMaterials.push_back(mat);
  }

  void setTetraMesh(NxU32 vcount,const float *vertices,NxU32 tcount,const unsigned int *indices);

  void clearTetraMesh(void);

  void onDeviceReset(void);

  void setDeletions(NxU8 *deletions);

  void createLinks(void);

	void softMeshMaterial(const TetraMaterial &tm);
	void softMeshTriangle(const TetraGraphicsVertex &v1,const TetraGraphicsVertex &v2,const TetraGraphicsVertex &v3);
	void softMeshTetrahedron(const float *p1,const float *p2,const float *p3,const float *p4);

  char                         mObjName[512];
  char                         mTetName[512];

  TetraMesh                   *mTetraMesh; // the tetrahedral mesh

  NxArray< TetraVertex >       mVertices;  // the array of orignal graphics vertices
  NxArray< TetraModelSection *>mSections;  // the model sections (one for each material)
  NxArray< TetraMaterial * >   mMaterials; // materials in this model.

  NxSoftBodyMesh              *mNxSoftBodyMesh;	 // instance of the soft body mesh on the SDK

  void *                       mVertexBuffer;   // the vertex buffer.

  NxBounds3                    mGraphicsBounds;

  TetraPositionMesh            mPositionMesh;  // only used for mesh editing...

// used during load phase..
  TetraModelSection           *mCurrentSection;
  SoftVertexPool              *mVertexPool; // used to build indexed triangle lists
  SoftVertexPool              *mTetraPool;  // used to build tetrahedral lists

};


}; // END OF SOFTBODY NAMESPACE

#endif

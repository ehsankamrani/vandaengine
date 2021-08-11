#ifndef OBJ_MESH_H
#define OBJ_MESH_H

#include "glRenderer.h"
#include "MeshHash.h"

#ifndef __PPCGEKKO__
#include <iostream>
#endif

//------------------------------------------------------------------------------------
#define OBJ_MESH_STRING_LEN 256
typedef char ObjMeshString[OBJ_MESH_STRING_LEN];


//------------------------------------------------------------------------------------
struct ObjMeshMaterial
{
	void init();
	ObjMeshString  name;
	int            texNr;

	ObjMeshString  texFilename;
	NxReal ambient[3];
	NxReal diffuse[3];
	NxReal specular[3];
	NxReal alpha;
	NxReal shininess;
};

//------------------------------------------------------------------------------------
struct ObjMeshTriangle
{
public:
	void init() {
		vertexNr[0] = -1; vertexNr[1] = -1; vertexNr[2] = -1;
		normalNr[0] = -1; normalNr[1] = -1; normalNr[2] = -1;
		texCoordNr[0] = -1; texCoordNr[1] = -1; texCoordNr[2] = -1;
		materialNr = -1;
	}
	void set(int v0, int v1, int v2, int mat) {
		vertexNr[0] = v0; vertexNr[1] = v1; vertexNr[2] = v2;
		normalNr[0] = v0; normalNr[1] = v1; normalNr[2] = v2;
		texCoordNr[0] = v0; texCoordNr[1] = v1; texCoordNr[2] = v2;
		materialNr = mat;
	}
	bool containsVertexNr(int vNr) const {
		return vNr == vertexNr[0] || vNr == vertexNr[1] || vNr == vertexNr[2];
	}

	// representation
	int vertexNr[3];
	int normalNr[3];
	int texCoordNr[3];
	int materialNr;

	int edges[3];
};

//------------------------------------------------------------------------------------
struct ObjMeshTetraLink
{
	int tetraNr;
	NxVec3 barycentricCoords;
};


//------------------------------------------------------------------------------------
class ObjMesh {
public:
	ObjMesh() { clear(); }

	bool loadFromObjFile(char *filename);
	bool saveToObjFile(char *filename) const;

	virtual bool simulateMesh(const NxMeshData &tetraMeshData);

	// to attach to tetra mesh
	void buildTetraLinks(const NxVec3 *verts, const NxU32 *tetIndices, const NxU32 numTets);
	bool loadTetraLinks(char *filename);

	virtual void draw(unsigned int baseColor, bool wireframe = false, bool shadows = false);
	void clear();

	int   getNumTriangles() const { return (int)mTriangles.size(); }
	const ObjMeshTriangle& getTriangle(int i) const { return mTriangles[i]; }
	void  getTriangleBounds(int i, NxBounds3 &bounds) const;

	int   getNumVertices() const { return (int)mVertices.size(); }
	const NxVec3& getVertex(int i) const { return mVertices[i]; }

	void setDiagonal(NxReal diagonal);
	void setCenter(const NxVec3 &center);
	void transform(const NxMat34 &a);

	void getBounds(NxBounds3 &bounds) const { bounds = mBounds; }

	bool rayTriangleIntersection(const NxVec3 &orig, const NxVec3 &dir,
	 									 const ObjMeshTriangle &triangle, 
										 NxReal &t, NxReal &u, NxReal &v) const;

	bool rayCast(const NxVec3 &orig, const NxVec3 &dir, NxReal &t);

	const char* getName() const { return mName; }

protected:
	bool importMtlFile(char *mtllib);
	void extractPath(char *filename);
	void updateNormals();
	void updateBounds();

	bool updateTetraLinks(const NxMeshData &tetraMeshData);

	virtual void removeTrisRelatedToVertex(const int vertexIndex);

	NxVec3 computeBaryCoords(NxVec3 vertex, NxVec3 p0, NxVec3 p1, NxVec3 p2, NxVec3 p3);

	static const int maxVerticesPerFace = 20;
	
#ifdef __PPCGEKKO__	   //Crash on wii, use nxarray other than std::vector
	NxArray<ObjMeshTriangle> mTriangles;
	NxArray<NxVec3>     mVertices;
	NxArray<NxVec3>     mNormals;
	NxArray<TexCoord>     mTexCoords;
	NxArray<ObjMeshMaterial> mMaterials;

	NxArray<int> mDrawIndices;
	NxArray<ObjMeshTetraLink> mTetraLinks;

	NxArray<bool> mDrainedTriVertices;

#else
	std::vector<ObjMeshTriangle> mTriangles;
	std::vector<NxVec3>     mVertices;
	std::vector<NxVec3>     mNormals;
	std::vector<TexCoord>     mTexCoords;
	std::vector<ObjMeshMaterial> mMaterials;

	std::vector<int> mDrawIndices;
	std::vector<ObjMeshTetraLink> mTetraLinks;

	std::vector<bool> mDrainedTriVertices;
#endif

	ObjMeshString mName;
	ObjMeshString mPath;
	NxBounds3 mBounds;
	bool mHasTextureCoords;
	bool mHasNormals;
};


#endif

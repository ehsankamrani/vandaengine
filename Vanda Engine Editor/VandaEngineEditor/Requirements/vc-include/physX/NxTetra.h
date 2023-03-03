#ifndef NX_TETRA_H

#define NX_TETRA_H

#ifdef NXTETRA_EXPORTS
#define NXTETRA_API __declspec(dllexport)
#else
#define NXTETRA_API __declspec(dllimport)
#endif

class NxTetraMesh
{
public:
  NxTetraMesh(void)
  {
  	mVcount = 0;
  	mVertices = 0;
  	mTcount = 0;
  	mIndices = 0;
    mIsTetra = false;
  }

  bool          mIsTetra;   // true if the mesh represents tetrahedra, otherwise it is triangles.
	unsigned int  mVcount;    // number of vertices.
	float        *mVertices;	// array of vertices.
	unsigned int  mTcount;    // number of triangles.
	unsigned int *mIndices;   // the triangle indices.
};

class NxTetraInterface
{
public:

  virtual bool         createTetraMesh(NxTetraMesh &mesh,         // mesh to populate
                                       unsigned int vcount,       // the number of vertices.
                                       const float *vertices,     // the vertex positions.
                                       unsigned int tcount,       // the number of triangles or tetrahdra
                                       const unsigned int *indices,      // the indices 3 per tri or 4 per tetrahdron
                                       bool isTetra) = 0;         // flag to indicate triangles or tetrahedron.


  virtual void         setSubdivisionLevel(unsigned int subdivisionLevel=30)=0;

	virtual unsigned int createIsoSurface(const NxTetraMesh &input,NxTetraMesh &output,bool isoSingle)=0;

	virtual unsigned int simplifySurface(float factor,const NxTetraMesh &input,NxTetraMesh &output)=0;

  virtual unsigned int createTetraMesh(const NxTetraMesh &inputMesh,NxTetraMesh &outputMesh) = 0;

  virtual bool         releaseTetraMesh(NxTetraMesh &mesh) = 0;
};

extern "C"
{
	NXTETRA_API NxTetraInterface * getTetraInterface(void);
}

#endif

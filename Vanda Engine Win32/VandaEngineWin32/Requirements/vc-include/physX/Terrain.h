#ifndef TERRAIN_H
#define TERRAIN_H

class TerrainData// : public NxAllocateable
	{
	public:
				TerrainData();
				~TerrainData();

	void		init(NxU32 size, NxF32 offset, NxF32 width, NxF32 chaos, bool flat=false, const NxVec3* pos=NULL);
	void		release();

	NxU32		size;
	NxU32		nbVerts;
	NxU32		nbFaces;
	NxF32		offset;
	NxF32		width;
	NxF32		chaos;
	NxVec3*		verts;
	NxVec3*		colors;
	NxVec3*		normals;
	NxU32*		faces;
	};

#endif

	#ifndef __VERTEX_WELDER_H
#define __VERTEX_WELDER_H

//#define DEBUG_WELDER
#include <Nxf.h>
#include <NxMeshData.h>
#include <NxArray.h>
#include <cloth/NxClothMeshDesc.h>

class VertexWelder
{
public:
	VertexWelder(NxReal epsilon = 0);
	~VertexWelder();

	void initialize(const NxClothMeshDesc& unweldedMesh);
	bool isUsed() { return mUsed; }

	void swapInBuffers(NxClothMeshDesc& meshDesc);
	void swapOutBuffers(NxClothMeshDesc& meshDesc);

	void setWriteData(void* vertices, NxU32 vertexStride, void* normals, NxU32 normalStride, void* userData, NxU32 userDataStride, NxU32 userDataSize, void* indices, NxU32 indexStride);

	void update(NxMeshData meshData);

	NxU32 getMappingSize() { return mMappingSize; }

	void applyTearing();

private:
	NxReal          mEpsilon;
	NxU32*          mMapping;
	NxU32           mMappingSize;
	NxU32           mMappingSpace;
	NxU32           mMappingDomain;
	NxU32           mMappingDomainAddition;

	NxU32           getMapping(NxU32 index);
	void            setMapping(NxU32 index, NxU32 value);

	NxArray<NxVec3> mNewVertices;
	NxU32*          mNewFaces32;
	NxU16*          mNewFaces16;
	bool            mUsed;

	void addNewVertex(NxU32 oldIndex);

	// These values are used to modify the cloth descriptor, and to revert it back so that the right buffers get deallocated afterwards
	// Only reason for this is the special allocation for buffers just for the cloth mesh descriptor done by MyCloth.
	//NxU32           mSwappedNumTriangles; // not needed as value does not change
	NxU32           mSwappedNumVertices;
	const void*     mSwappedPoints;
	NxU32           mSwappedPointStride;
	const void*     mSwappedTriangles;
	NxU32           mSwappedTriangleStride;

	// write back data
	void*           mWriteVerticesPtr;
	NxU32           mWriteVerticesStride;

	void*           mWriteNormalsPtr;
	NxU32           mWriteNormalsStride;

	void*           mWriteUserDataPtr;
	NxU32           mWriteUserDataStride;
	NxU32           mWriteUserDataSize;

	void*           mWriteIndicesPtr;
	NxU32           mWriteIndicesStride;

};

#endif

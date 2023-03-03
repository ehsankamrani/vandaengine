// ====================================================================================
//
//                                 NVIDIA PHYSX
//
// Content: Tool to read mesh data and cooking flags from cooked mesh file
//
// Comment: Works for convex and non-convex mesh files
//
// Author:  Michael Sauter
//
// ====================================================================================

#ifndef COOKED_MESH_READER_H
#define COOKED_MESH_READER_H


enum CmMeshType
{
	MT_INVALID_MESH		=   0,
	MT_CONVEX_MESH		=   1,
    MT_TRIANGLE_MESH	=   2,
};


class CmMeshData
{
	public:

	CmMeshData();
	~CmMeshData();
	
	unsigned int numVertices;			// Number of vertices.
	unsigned int numTriangles;			// Number of triangles.
	unsigned int pointStrideBytes;		// Offset between vertex points in bytes.
	unsigned int triangleStrideBytes;	// Offset between triangles in bytes.
	void* points;						// Pointer to array of vertex positions.
	void* triangles;					// Pointer to array of triangle inices.
	unsigned int flags;					// Flags bits.

	unsigned int materialIndexStride;	// Otherwise this is the offset between material indices in bytes.
	void* materialIndices;				// Optional pointer to first material index, or NULL.
	unsigned int heightFieldVerticalAxis;    // The mesh may represent either an arbitrary mesh or a height field.
	float heightFieldVerticalExtent;	// If this mesh is a height field, this sets how far 'below ground' the height volume extends.
	float convexEdgeThreshold;			// Parameter allows you to setup a tolerance for the convex edge detector.
};


/**
 *
 * Extract mesh data from cooked mesh file
 *
 * @param		file				the cooked mesh file (full path)
 * @param		mesh_type			type of mesh in the file (convex or non-convex)
 * @param		meshDesc			structure to store extracted mesh data in
 * @param		hintCollisionSpeed	hint whether the cooked mesh was optimized for speed or for size
 *
 * @return							true on success, otherwise false
 *
 */
bool GetCookedData(const char* file, CmMeshType& mesh_type, CmMeshData& meshDesc, bool& hintCollisionSpeed);


#endif  // COOKED_MESH_READER_H

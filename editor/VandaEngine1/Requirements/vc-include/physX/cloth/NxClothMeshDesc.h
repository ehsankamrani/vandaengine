#ifndef NX_PHYSICS_NX_CLOTHMESHDESC
#define NX_PHYSICS_NX_CLOTHMESHDESC
/** \addtogroup cloth
  @{
*/
/*----------------------------------------------------------------------------*\
|
|					Public Interface to NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#include "NxSimpleTriangleMesh.h"

#define NX_CLOTH_MAX_HIERARCHY_LEVELS 10

/**
\brief Cloth mesh flags.

@see NxClothMeshDesc.flags
*/

enum NxClothMeshFlags
	{
	/**
	\brief Specifies whether extra space is allocated for tearing.
	If this flag is not set, less memory is needed but tearing is not possible.
	These flags for clothMeshes extend the set of flags defined in NxMeshFlags.
	*/
	NX_CLOTH_MESH_TEARABLE	=	(1<<8),
	/**
	\brief Welds close vertices.

	If this flag is set, the cooker maps close vertices (i.e. vertices closer than
	NxClothMeshDesc.weldingDistance) to a single internal vertex.
	This is useful when more than one vertex at the same location is used for handling
	multiple texture coordinates. With welding, the mesh does not fall apart when simulated.

	@see NxClothMeshDesc.weldingDistance
	*/
	NX_CLOTH_MESH_WELD_VERTICES = (1<<9)
	};

/**
\brief Cloth vertex flags.

@see NxClothMeshDesc.vertexFlags
*/

enum NxClothVertexFlags
	{
	/**
	\brief Specifies whether a cloth vertex is attached to a global position.
	*/
	NX_CLOTH_VERTEX_ATTACHED	=	(1<<0),

	/**
	\brief Specifies whether a cloth vertex can be torn.
	*/
	NX_CLOTH_VERTEX_TEARABLE	=	(1<<7)
	
	};

/*----------------------------------------------------------------------------*/

/**
\brief Descriptor class for #NxClothMesh.

Note that this class is derived from NxSimpleTriangleMesh which contains the
members that describe the basic mesh. The mesh data is *copied* when an
NxClothMesh object is created from this descriptor. After the creation the
user may discard the basic mesh data.

@see NxClothMesh NxSimpleTriangleMesh
*/

class NxClothMeshDesc : public NxSimpleTriangleMesh
{
public:
	NxU32 vertexMassStrideBytes;		//!< Offset between vertex masses in bytes.
	NxU32 vertexFlagStrideBytes;		//!< Offset between vertex flags in bytes.
	
	/**
	\brief Pointer to first vertex mass.
	
	Caller may add vertexMassStrideBytes bytes to the pointer to access the next vertex mass.
	*/
	const void* vertexMasses;

	/**
	\brief Pointer to first vertex flag. Flags are of type #NxClothVertexFlags
	
	Caller may add vertexFlagStrideBytes bytes to the pointer to access the next vertex flag.
	*/
	const void* vertexFlags;

	/**
	\brief Specifies the number of additional meshes in the hierarchy.
	If this parameter is greater than zero, the cooker generates a hierarchy of 
	smaller and smaller cloth meshes in addition to the base mesh. 
	With this hierarchy, the cloth solver can be sped up substanially.

	@see NxClothDesc.hierarchicalSolverIterations NxCloth.getHierarchicalSolverIterations() NxCloth.setHierarchicalSolverIterations()
	*/
	NxU32 numHierarchyLevels;

	/**
	\brief For welding close vertices.

	If the NX_CLOTH_MESH_WELD_VERTICES flag is set, the cooker maps close vertices 
	(i.e. vertices closer than NxClothMeshDesc.weldingDistance) to a single internal vertex.
	This is useful when more than one vertex at the same location is used for handling
	multiple texture coordinates. With welding, the mesh does not fall apart when simulated.

	@see NxClothMeshFlags
	*/
	NxReal weldingDistance;

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE NxClothMeshDesc();

	/**
	\brief (Re)sets the structure to the default.	
	*/
	NX_INLINE void setToDefault();

	/**
	\brief Returns true if the current settings are valid
	*/
	NX_INLINE bool isValid() const { return !checkValid(); }
	/**
	\brief returns 0 if the current settings are valid
	*/
	NX_INLINE NxU32 checkValid() const;
};

/*----------------------------------------------------------------------------*/

NX_INLINE NxClothMeshDesc::NxClothMeshDesc()
{
	setToDefault();
}

/*----------------------------------------------------------------------------*/

NX_INLINE void NxClothMeshDesc::setToDefault()
{
	NxSimpleTriangleMesh::setToDefault();
	vertexMassStrideBytes	= sizeof(NxReal);
	vertexFlagStrideBytes	= sizeof(NxU32);
	vertexMasses			= NULL;
	vertexFlags				= NULL;
	numHierarchyLevels      = 0;
	weldingDistance			= 0.0f;
}

/*----------------------------------------------------------------------------*/

NX_INLINE NxU32 NxClothMeshDesc::checkValid() const
{
	if(vertexMasses && (vertexMassStrideBytes < sizeof(NxReal)))
		return 1;
	if(vertexFlags && (vertexFlagStrideBytes < sizeof(NxU32)))
		return 2;
	if (numHierarchyLevels > NX_CLOTH_MAX_HIERARCHY_LEVELS)
		return 3;
	if(weldingDistance < 0.0f)
		return 4;
	return 5*NxSimpleTriangleMesh::checkValid();
}

/*----------------------------------------------------------------------------*/
/** @} */
#endif

//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2010 NVIDIA Corporation
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

#ifndef NX_PHYSICS_NX_CLOTHDESC
#define NX_PHYSICS_NX_CLOTHDESC
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

#include "Nxp.h"
#include "NxBounds3.h"
#include "NxMeshData.h"

class NxClothMesh;
class NxCompartment;

/**
\brief Collection of flags describing the behavior of a cloth object.

@see NxCloth NxClothMesh NxClothMeshDesc
*/
enum NxClothFlag
{
	/**
	\brief Enable/disable pressure simulation. 
	Note: Pressure simulation only produces meaningful results for closed meshes.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.pressure
	*/
	NX_CLF_PRESSURE			  = (1<<0),

	/**
	\brief Makes the cloth static. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_CLF_STATIC			  = (1<<1),

	/**
	\brief Disable collision handling with the rigid body scene. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.collisionResponseCoefficient
	*/
	NX_CLF_DISABLE_COLLISION  = (1<<2),

	/**
	\brief Enable/disable self-collision handling within a single piece of cloth.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NX_CLF_TRIANGLE_COLLISION
	*/
	NX_CLF_SELFCOLLISION	  = (1<<3),

	/**
	\brief Enable/disable debug visualization. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_CLF_VISUALIZATION	  = (1<<4),

	/**
	\brief Enable/disable gravity. If off, the cloth is not subject to the gravitational force
	of the rigid body scene.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_CLF_GRAVITY            = (1<<5),

	/**
	\brief Enable/disable bending resistance. Select the bending resistance through 
	NxClothDesc.bendingStiffness. Two bending modes can be selected via the NX_CLF_BENDING_ORTHO flag.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.bendingStiffness NX_CLF_BENDING_ORTHO
	*/
	NX_CLF_BENDING            = (1<<6),

	/**
	\brief Enable/disable orthogonal bending resistance. This flag has an effect only if
	NX_CLF_BENDING is set. If NX_CLF_BENDING_ORTHO is not set, bending is modeled via an
	additional distance constraint. This mode is fast but not independent of stretching
	resistance. If NX_CLF_BENDING_ORTHO is set, bending is modeled via an angular spring
	between adjacent triangles. This mode is slower but independent of stretching resistance.

	This flag cannot be changed after the cloth has been created.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.bendingStiffness NX_CLF_BENDING
	*/
	NX_CLF_BENDING_ORTHO      = (1<<7),

	/**
	\brief Enable/disable damping of internal velocities. Use NxClothDesc.dampingCoefficient
	to control damping.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.dampingCoefficient
	*/
	NX_CLF_DAMPING            = (1<<8),

	/**
	\brief Enable/disable two way collision of cloth with the rigid body scene.
	
	In either case, cloth is influenced by colliding rigid bodies.
	If NX_CLF_COLLISION_TWOWAY is not set, rigid bodies are not influenced by 
	colliding pieces of cloth. Use NxClothDesc.collisionResponseCoefficient to
	control the strength of the feedback force on rigid bodies.

	When using two way interaction care should be taken when setting the density of the attached objects.
	For example if an object with a very low or high density is attached to a cloth then the simulation 
	may behave poorly. This is because impulses are only transfered between the cloth and rigid body solver
	outside the solvers.

	Two way interaction works best when NX_SF_SEQUENTIAL_PRIMARY is set in the primary scene. If not set,
	collision and attachment artifacts may happen.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.collisionResponseCoefficient
	*/
	NX_CLF_COLLISION_TWOWAY   = (1<<9),

	/**
	Not supported in current release.
	\brief Enable/disable collision detection of cloth triangles against the scene.
	If NX_CLF_TRIANGLE_COLLISION is not set, only collisions of cloth particles are detected.
	If NX_CLF_TRIANGLE_COLLISION is set, collisions of cloth triangles are detected as well.

	<b>Platform:</b>
	\li PC SW: No
	\li GPU  : No
	\li PS3  : No
	\li XB360: No
	*/
	NX_CLF_TRIANGLE_COLLISION = (1<<11),

	/**
	\brief Defines whether the cloth is tearable. 
	
	Note: Make sure meshData.maxVertices and the corresponding buffers
	in meshData are substantially larger (e.g. 2x) then the number 
	of original vertices since tearing will generate new vertices.
	When the buffer cannot hold the new vertices anymore, tearing stops.

	Note: For tearing, make sure you cook the mesh with	the flag
	NX_CLOTH_MESH_TEARABLE set in the NxClothMeshDesc.flags.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.tearFactor NxClothDesc.meshData NxClothMeshDesc.flags
	*/
	NX_CLF_TEARABLE           = (1<<12),

	/**
	\brief Defines whether this cloth is simulated on the GPU.
	
	To simulate a piece of cloth on the GPU
	set this flag and create the cloth in a regular software scene.
	Note: only use this flag during creation, do not change it using NxCloth.setFlags().
	*/
	NX_CLF_HARDWARE           = (1<<13),

	/**
	\brief Enable/disable center of mass damping of internal velocities.

	This flag only has an effect if the flag NX_CLF_DAMPING is set. If set, 
	the global rigid body modes (translation and rotation) are extracted from damping. 
	This way, the cloth can freely move and rotate even under high damping. 
	Use NxClothDesc.dampingCoefficient to control damping. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.dampingCoefficient
	*/
	NX_CLF_COMDAMPING		  = (1<<14),

	/**
	\brief If the flag NX_CLF_VALIDBOUNDS is set, cloth particles outside the volume
	defined by NxClothDesc.validBounds are automatically removed from the simulation. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.validBounds
	*/
	NX_CLF_VALIDBOUNDS		  = (1<<15),

	/**
	\brief Enable/disable collision handling between this cloth and fluids.

	Note: With the current implementation, do not switch on fluid collision for
	many cloths. Create scenes with a few large pieces because the memory usage
	increases linearly with the number of cloths.
	The performance of the collision detection is dependent on both, the thickness
	and the particle radius of the fluid so tuning these parameters might improve
	the performance significantly.

	Note: The current implementation does not obey the NxScene::setGroupCollisionFlag
	settings. If NX_CLF_FLUID_COLLISION is set, collisions will take place even if
	collisions between the groups that the corresponding cloth and fluid belong to are
	disabled.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.toFluidResponseCoefficient NxClothDesc.fromFluidResponseCoefficient
	*/
	NX_CLF_FLUID_COLLISION    = (1<<16),

	/**
	\brief Disable continuous collision detection with dynamic actors. 
	Dynamic actors are handled as static ones.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_CLF_DISABLE_DYNAMIC_CCD  = (1<<17),

	/**
	\brief Moves cloth partially in the frame of the attached actor. 

	This feature is useful when the cloth is attached to a fast moving character.
	In that case the cloth adheres to the shape it is attached to while only 
	velocities below the parameter minAdhereVelocity are used for secondary effects.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxClothDesc.minAdhereVelocity
	*/
	NX_CLF_ADHERE  = (1<<18),

	/**
	\brief Uses the information provided by NxCloth.setConstrainPositions() and
	NxCloth.setConstrainCoefficients() to make the cloth less stretchy.

	If the flag is set, the solver pulls vertices 
	with a maxDistance greater zero towards vertices with maxDistance zero (attached). 
	This reduces the stretchiness even for low solver iteration counts. The process is
	non-physical and can yield small ghost forces. The NxCloth.hardStretchLimitationFactor
	defines by what factor the cloth is allowed to stretch.

	@see NxCloth.setConstrainPositions() NxCloth.setConstrainCoefficients() NxCloth.hardStretchLimitationFactor
	*/
	NX_CLF_HARD_STRETCH_LIMITATION = (1<<20),

	/**
	\brief Untangle the cloth in the neighborhood of vertices.

	This feature is experimental, use with caution!
	When self-collision handling is turned off (for performance reasons), the cloth can locally 
	entangle and remain in this state. When this NX_CLF_UNTANGLING is set, the simulator tries to untangle
	the cloth locally. This is done non-physically and can introduce ghost forces.
	The flag can be turned on and off during run-time but you need to set it when the cloth is
	created in order for the necessary data structures to get initialized.
	*/
	NX_CLF_UNTANGLING = (1<<21),

	/**
	\brief Allows cloth to collide with soft bodies and with other cloth.

	Not implemented.

	<b>Platform:</b>
	\li PC SW: No
	\li GPU  : No
	\li PS3  : No
	\li XB360: No
	\li WII	 : No

	@see NxClothDesc.selfCollisionThickness
	*/
	NX_CLF_INTER_COLLISION = (1<<22)
};

/*----------------------------------------------------------------------------*/

/**
\brief Cloth attachment flags.

@see NxCloth.attachToShape() NxCloth.attachToCollidingShapes() NxCloth.attachVertexToShape()
*/

enum NxClothAttachmentFlag
{
	/**
	\brief The default is only object->cloth interaction (one way).

	With this flag set, cloth->object interaction is turned on as well.
	*/
	NX_CLOTH_ATTACHMENT_TWOWAY			  = (1<<0),

	/**
	\brief When this flag is set, the attachment is tearable.

	\note If the cloth is attached to a dynamic shape using two way interaction
	half way torn attachments can generate unexpected impluses on the shape.
	To prevent this, only attach one row of cloth vertices to the shape.
	@see NxClothDesc.attachmentTearFactor
	*/
	NX_CLOTH_ATTACHMENT_TEARABLE		  = (1<<1)
};

/*----------------------------------------------------------------------------*/

/**
\brief Set of attachment states a vertex can be in.
*/

enum NxClothVertexAttachmentStatus
{
	/**
	\brief The vertex is not attached
	*/
	NX_CLOTH_VERTEX_ATTACHMENT_NONE,

	/**
	\brief The vertex is attached to a global position
	*/
	NX_CLOTH_VERTEX_ATTACHMENT_GLOBAL,

	/**
	\brief The vertex is attached to a shape
	*/
	NX_CLOTH_VERTEX_ATTACHMENT_SHAPE
};

/*----------------------------------------------------------------------------*/

/**
\brief User-side class specifying a triangle split generated from a torn cloth.
*/
class NxClothSplitPair
{
public:
	NxU32 triangleIndex0;
	NxU32 triangleIndex1;
	NxU8 edgeIndex0;
	NxU8 edgeIndex1;    
};

/**
\brief User-side class for receiving triangle split events for torn cloth.

The user can optionally receive triangle split event data if a cloth gets torn.
One split is represented by a pair of triangle indices and a pair of edge indices.
The triangle indices can be used to locate the vertex index triple belonging to 
the two mesh triangles involved in split.

Each pair is garantueed to be reported only once.
*/
class NxClothSplitPairData
{ 
public:
	/**
	\brief Specifies the maximal number of splits the buffer can hold.

	If there are more splits in one time step than the buffer can hold, some will go unreported.
	*/
	NxU32	maxSplitPairs;

	/**
	\brief Points to the user-allocated memory holding the number of splits stored in the buffer.

	If the SDK writes to a given split buffer, it also sets the numbers of entries written.
	If this is set to NULL, the SDK can't write to the buffer.
	*/
	NxU32*	numSplitPairsPtr;

	/**
	\brief The pointer to the user-allocated buffer of split pairs.

	If set to NULL, split pairs are not written.
	*/
	NxClothSplitPair*	splitPairsBegin;
	
	/**
	\brief The separation (in bytes) between consecutive split pairs.

	The first split pair is found at location <tt>splitPairsBegin</tt>;
	the second is at <tt>splitPairsBegin + splitPairsByteStride</tt>;
	and so on.
	*/
	NxU32	splitPairsByteStride;

	NX_INLINE ~NxClothSplitPairData();

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

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE	NxClothSplitPairData();
};

NX_INLINE NxClothSplitPairData::NxClothSplitPairData()
	{
	setToDefault();
	}

NX_INLINE NxClothSplitPairData::~NxClothSplitPairData()
	{
	}

NX_INLINE void NxClothSplitPairData::setToDefault()
	{
	maxSplitPairs			= 0;
	numSplitPairsPtr		= NULL;
	splitPairsBegin			= NULL;
	splitPairsByteStride	= 0;
	}

NX_INLINE NxU32 NxClothSplitPairData::checkValid() const
	{
	if (numSplitPairsPtr  && !splitPairsBegin) return 1;
	if (!numSplitPairsPtr &&  splitPairsBegin) return 2;
	if (splitPairsBegin && !splitPairsByteStride) return 3;
	return 0;
	}

/*----------------------------------------------------------------------------*/

#define NX_CLOTH_EXTENDED_CONSTRAIN_COEFFICIENTS

/**
\brief Defines a set of per vertex coefficients

The user can supply a buffer of positions and normals coming from an animation of the cloth
or instance. The simulated vertices are then corrected via the constrain positions, normals
and the constrain coefficiens.

@see NxCloth.setConstrainCoefficients() NxCloth.setConstrainPositions() NxCloth.setConstrainNormals()
*/
class NxClothConstrainCoefficients
{
public:
	/**
	\brief Distance a vertex is allowed to travel from the constrain position.

	If constrain positions are provided via NxCloth.setConstrainPositions the SDK makes sure
	that the cloth vertices stay within maxDistance from the constrain positions. 
	If maxDistance is zero, the vertex is not simulated but set to the constrain position.
	This behavior is useful for attaching the cloth vertex to the skin of an animated character.

	<b>Default:</b> 0.0 <br>
	<b>Range:</b> [0,inf)

	@see NxCloth.setConstrainCoefficients() NxCloth.setConstrainPositions() NxCloth.setConstrainNormals()
	*/
	NxReal maxDistance;

	/**
	\brief Distorts the sphere defined by the maxDistance.

	For this feature to work the user has to provide constrain normals. The feature is disabled
	for a value of 0.0 (default). In this case the max distance sphere is undistorted.
	Decreasing the maxDistanceBias towards -1.0 reduces the distance the vertex is allowed to
	travel in the tangential direction. For -1.0 the vertex has to stay on the normal through
	the constrain position and within maxDistance to the constrain position.
	Increasing maxDistanceBias towards 1.0 reduces the discance the vertex is allowed to travel
	in the normal direction. At 1.0 the vertex can only move inside the tangental plane within 
	maxDistance from the constrain position.

	<b>Default:</b> 0.0 <br>
	<b>Range:</b> [-1.0, 1.0]

	@see NxCloth.setConstrainCoefficients() NxCloth.setConstrainPositions() NxCloth.setConstrainNormals()
	*/
	NxReal maxDistanceBias;

	/**
	\brief Definition of a sphere a vertex is not allowed to enter. This allows collision against the animated cloth.

	For this parameter to have an effect, both, constrain positions and constrain normals need to be provided via
	NxCloth.setConstrainPositions() and NxCloth.setConstrainNormals(). 
	The pair (collisionSphereRadius, collisionSphereDistance) define a sphere for each cloth vertex. The sphere's
	center is located at the position 
	constrainPosition - constrainNormal * (collisionSphereRadius + collisionSphereDistance) and its radius
	is collisionSphereRadius. The SDK makes sure that the cloth vertex does not enter this sphere.
	As a typical usecase, set collisionSphereDistance to zero and collisionSphereRadius to a large value
	w.r.t. the triangle size. In this setup, the cloth collides against the animated mesh.

	<b>Default:</b> 0.0 <br>
	<b>Range:</b> [0,inf)

	@see NxCloth.setConstrainCoefficients() NxCloth.setConstrainPositions() NxCloth.setConstrainNormals()
	*/
	NxReal collisionSphereRadius;

	/**
	\brief Definition of a sphere a vertex is not allowed to enter. This allows collision against the animated cloth.

	@see NxClothConstrainCoefficients.collisionSphereRadius NxCloth.setConstrainCoefficients() NxCloth.setConstrainPositions() NxCloth.setConstrainNormals()
	*/
	NxReal collisionSphereDistance;

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

NX_INLINE void NxClothConstrainCoefficients::setToDefault()
	{
	maxDistance			    = 0.0f;
	maxDistanceBias         = 0.0f;
	collisionSphereRadius   = 0.0f;
	collisionSphereDistance	= 0.0f;
	}

NX_INLINE NxU32 NxClothConstrainCoefficients::checkValid() const
	{
	if (maxDistance < 0.0f) return 1;
	if (collisionSphereRadius < 0.0f) return 2;
	return 0;
	}

/*----------------------------------------------------------------------------*/

/**
\brief Descriptor class for #NxCloth.

@see NxCloth NxCloth.saveToDesc()
*/

class NxClothDesc
{
public:
	/**
	\brief The cooked cloth mesh.

	<b>Default:</b> NULL

	@see NxClothMesh NxClothMeshDesc NxCloth.getClothMesh()
	*/
	NxClothMesh *clothMesh;

	/**
	\brief The global pose of the cloth in the world.

	<b>Default:</b> Identity Transform
	*/
	NxMat34 globalPose;

	/**
	\brief Thickness of the cloth.

	The thickness is usually a fraction of the overall extent of the cloth and
	should not be set to a value greater than that.	A good value is the maximal
	distance between two adjacent cloth particles in their rest pose. Visual
	artifacts or collision problems may appear if the thickness is too small.

	<b>Default:</b> 0.01 <br>
	<b>Range:</b> [0,inf)

	@see NxCloth.setThickness()
	*/
	NxReal thickness;

	/**
	\brief Size of the particle diameters used for self collision and inter-collision.

	The self collision thickness is usually a fraction of the overall extent of the cloth and
	should not be set to a value greater than that.	A good value is the maximal
	distance between two adjacent cloth particles in their rest pose. Visual
	artifacts or collision problems may appear if the particle radius is too small.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> (0,inf)

	@see NxCloth.setSelfCollisionThickness()
	*/
	NxReal selfCollisionThickness;

	/**
	\brief Density of the cloth (mass per area).

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> (0,inf)
	*/
	NxReal density;

	/**
	\brief Bending stiffness of the cloth in the range 0 to 1.

	Only has an effect if the flag NX_CLF_BENDING is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,1]
	
	@see NX_CLF_BENDING NxCloth.setBendingStiffness()
	*/
	NxReal bendingStiffness;
	
	/**
	\brief Stretching stiffness of the cloth in the range 0 to 1.

	Note: stretching stiffness must be larger than 0.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> (0,1]

	@see NxCloth.setStretchingStiffness()
	*/
	NxReal stretchingStiffness;

	/**
	\brief Defines the hard stretch elongation limit

	If the flag NX_CLF_HARD_STRETCH_LIMITATION is set, the solver pulls vertices 
	with a maxDistance greater zero towards vertices with maxDistance zero (attached). 
	This reduces the stretchiness even for low solver iteration counts. The process is
	non-physical and can yield small ghost forces. The hardStretchLimitationFactor
	defines by what factor the cloth is allowed to stretch.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)

	@see NxCloth.setConstrainPositions() NxCloth.setConstrainCoefficients() NxCloth.setHardStretchLimitationFactor()
	*/
	NxReal hardStretchLimitationFactor;

	/**
	\brief Spring damping of the cloth in the range 0 to 1.

	Only has an effect if the flag NX_CLF_DAMPING is set.

	<b>Default:</b> 0.5 <br>
	<b>Range:</b> [0,1]
	
	@see NX_CLF_DAMPING NxCloth.setDampingCoefficient()
	*/
	NxReal dampingCoefficient;

	/**
	\brief Friction coefficient in the range 0 to 1. 

	Defines the damping of the velocities of cloth particles that are in contact.

	<b>Default:</b> 0.5 <br>
	<b>Range:</b> [0,1]

	@see NxCloth.setFriction()
	*/
	NxReal friction;

	/**
	\brief If the flag NX_CLF_PRESSURE is set, this variable defines the volume
	of air inside the mesh as volume = pressure * restVolume. 

	For pressure < 1 the mesh contracts w.r.t. the rest shape
	For pressure > 1 the mesh expands w.r.t. the rest shape

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)
	
	@see NX_CLF_PRESSURE NxCloth.setPressure()
	*/
	NxReal pressure;

	/**
	\brief If the flag NX_CLF_TEARABLE is set, this variable defines the 
	elongation factor that causes the cloth to tear. 

	Must be larger than 1.
	Make sure meshData.maxVertices and the corresponding buffers
	in meshData are substantially larger (e.g. 2x) than the number 
	of original vertices since tearing will generate new vertices.
	
	When the buffer cannot hold the new vertices anymore, tearing stops.

	<b>Default:</b> 1.5 <br>
	<b>Range:</b> (1,inf)

	@see NxCloth.setTearFactor()
	*/
	NxReal tearFactor;

	/**
	\brief Defines a factor for the impulse transfer from cloth to colliding rigid bodies.

	Only has an effect if NX_CLF_COLLISION_TWOWAY is set.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> [0,inf)
	
	@see NX_CLF_COLLISION_TWOWAY NxCloth.setCollisionResponseCoefficient()
	*/
	NxReal collisionResponseCoefficient;

	/**
	\brief Defines a factor for the impulse transfer from cloth to attached rigid bodies.

	Only has an effect if the mode of the attachment is set to NX_CLOTH_ATTACHMENT_TWOWAY.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> [0,1]
	
	@see NxCloth.attachToShape NxCloth.attachToCollidingShapes NxCloth.attachVertexToShape NxCloth.setAttachmentResponseCoefficient()
	*/
	NxReal attachmentResponseCoefficient;

	/**
	\brief If the flag NX_CLOTH_ATTACHMENT_TEARABLE is set in the attachment method of NxCloth, 
	this variable defines the elongation factor that causes the attachment to tear. 

	Must be larger than 1.

	<b>Default:</b> 1.5 <br>
	<b>Range:</b> (1,inf)

	@see NxCloth.setAttachmentTearFactor() NxCloth.attachToShape NxCloth.attachToCollidingShapes NxCloth.attachVertexToShape

	*/
	NxReal attachmentTearFactor;

	/**
	\brief Defines a factor for the impulse transfer from this cloth to colliding fluids.

	Only has an effect if the NX_CLF_FLUID_COLLISION flag is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)

	Note: Large values can cause instabilities
	
	@see NxClothDesc.flags NxClothDesc.fromFluidResponseCoefficient
	*/
	NxReal toFluidResponseCoefficient;

	/**
	\brief Defines a factor for the impulse transfer from colliding fluids to this cloth.

	Only has an effect if the NX_CLF_FLUID_COLLISION flag is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)
	
	Note: Large values can cause instabilities

	@see NxClothDesc.flags NxClothDesc.toFluidResponseCoefficient
	*/
	NxReal fromFluidResponseCoefficient;

	/**
	\brief Defines a factor up to which the cloth is weak under compression.

	This factor is the lower part of a range [limit, 1]. Whenever an edge is compressed
	to something between [limit, 1] * original length, the stretchingStiffness is
	multiplied with the compressionStiffness.

	Since the compressionStiffness is smaller or equal to 1, this will always define a
	range where the cloth reacts more softly to compressed edges.

	This feature is useful to generate small wrinkles features on the cloth 
	mesh outside the SDK. 

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0, 1]
	
	@see NxClothDesc.compressionStiffness
	*/
	NxReal compressionLimit;

	/**
	\brief Defines the stiffness of the cloth under compression.

	This stiffness scales the stretchingStiffness in the range defined by compressionLimit.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0, 1]
	
	@see NxClothDesc.compressionLimit
	*/
	NxReal compressionStiffness;

	/**
	\brief If the NX_CLF_ADHERE flag is set the cloth moves partially in the frame 
	of the attached actor. 

	This feature is useful when the cloth is attached to a fast moving character.
	In that case the cloth adheres to the shape it is attached to while only 
	velocities below the parameter minAdhereVelocity are used for secondary effects.

	<b>Default:</b> 1.0
	<b>Range:</b> [0,inf)

	@see NX_CLF_ADHERE
	*/ 

	NxReal minAdhereVelocity;

	/**
	\brief Number of solver iterations. 

	Note: Small numbers make the simulation faster while the cloth gets less stiff.

	<b>Default:</b> 5
	<b>Range:</b> [1,inf)

	@see NxCloth.setSolverIterations()
	*/ 

	NxU32  solverIterations;

	/**
	\brief Number of iterations of the hierarchical cloth solver.

	For the this value to have an effect, the parameter NxClothMeshDesc.numHierarchyLevels
	must be greater then one when cooking the cloth mesh. In this case, the hierarchical
	cloth solver uses the mesh hierarchy to speed up convergence, i.e. makes large
	pieces of cloth less stretchy.

	<b>Default:</b> 2
	<b>Range:</b> [0,inf)

	@see NxCloth.setHierarchicalSolverIterations() NxCloth.setHierarchicalSolverIterations NxClothMeshDesc.numHierarchyLevels
	*/ 
	NxU32  hierarchicalSolverIterations;

	/**
	\brief External acceleration which affects all non attached particles of the cloth. 

	<b>Default:</b> (0,0,0)

	@see NxCloth.setExternalAcceleration()
	*/ 
	NxVec3 externalAcceleration;

	/**
	\brief Acceleration which acts normal to the cloth surface at each vertex.

	<b>Default:</b> (0,0,0)

	@see NxCloth.setWindAcceleration()
	*/ 
	NxVec3 windAcceleration;

	/**
	\brief The cloth wake up counter.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 20.0f*0.02f

	@see NxCloth.wakeUp() NxCloth.putToSleep()
	*/
	NxReal wakeUpCounter;

	/**
	\brief Maximum linear velocity at which cloth can go to sleep.
	
	If negative, the global default will be used.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> -1.0

	@see NxCloth.setSleepLinearVelocity() NxCloth.getSleepLinearVelocity()
	*/
	NxReal sleepLinearVelocity;

	/**
	\brief The buffers in meshData are used to communicate the dynamic data of the cloth back to the user.
	
	For example vertex positions, normals, connectivity (triangles) and parent index information. The internal order
	of the contents of meshData's buffers will remain the same as that in the initial mesh data used to create the mesh.

	<b>Default:</b> See #NxMeshData

	@see NxMeshData NxCloth.setMeshData()
	*/
	NxMeshData meshData;

	/**
	\brief 	The buffers in splitPairData are used to communicate the split triangle data of the cloth back to the user.
	
	@see NxClothSplitPairData
	*/
	NxClothSplitPairData splitPairData;

	/**
	\brief Sets which collision group this cloth is part of.

	<b>Range:</b> [0, 31]
	<b>Default:</b> 0

	NxCloth.setCollisionGroup()
	*/
	NxCollisionGroup collisionGroup;

	/**
	\brief Sets the 128-bit mask used for collision filtering.

	<b>Default:</b> 0

	@see NxGroupsMask NxCloth.setGroupsMask() NxCloth.getGroupsMask()
	*/
	NxGroupsMask groupsMask;

	/**
	\brief Force Field Material Index, index != 0 has to be created.

	<b>Default:</b> 0
	*/
	NxU16 forceFieldMaterial;

	/**
	\brief If the flag NX_CLF_VALIDBOUNDS is set, this variable defines the volume
	outside of which cloth particle are automatically removed from the simulation. 

	@see NX_CLF_VALIDBOUNDS NxCloth.setValidBounds()
	*/
	NxBounds3 validBounds;

	/**
	\brief This parameter defines the size of grid cells for collision detection.

	The cloth is represented by a set of world aligned cubical cells in broad phase.
	The size of these cells is determined by multiplying the length of the diagonal
	of the AABB of the initial cloth size with this constant.

	<b>Range:</b> [0.01,inf)<br>
	<b>Default:</b> 0.25
	*/
	NxReal relativeGridSpacing;

	/**
	\brief Flag bits.

	<b>Default:</b> NX_CLF_GRAVITY

	@see NxClothFlag NxCloth.setFlags()
	*/ 
	NxU32 flags;

	/**
	\brief Will be copied to NxCloth::userData

	<b>Default:</b> NULL

	@see NxCloth.userData
	*/
	void* userData;

	/**
	\brief Possible debug name. The string is not copied by the SDK, only the pointer is stored.

	<b>Default:</b> NULL

	@see NxCloth.setName() NxCloth.getName()
	*/
	const char* name;

	/**
	\brief The compartment to place the cloth in. Must be either a pointer to an NxCompartment of type NX_SCT_CLOTH, or NULL.
	A NULL compartment means creating NX_CLF_HARDWARE cloth in the first available cloth compartment (a default cloth compartment is created if none exists).
	Software cloth with a NULL compartment is created in the scene proper.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	<b>Default:</b> NULL
	*/
	NxCompartment *	compartment;

	/**
	\brief Constructor sets to default.
	*/
	NX_INLINE NxClothDesc();

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

NX_INLINE NxClothDesc::NxClothDesc()
{
	setToDefault();
}

/*----------------------------------------------------------------------------*/

NX_INLINE void NxClothDesc::setToDefault()
{
	clothMesh = NULL;
	globalPose.id();
	thickness = 0.01f;
	selfCollisionThickness = 0.2f;
	density = 1.0f;
	bendingStiffness = 1.0f;
	stretchingStiffness = 1.0f;
	hardStretchLimitationFactor = 1.0f;
    dampingCoefficient = 0.5f;
	friction = 0.5f;
	pressure = 1.0f;
	tearFactor = 1.5f;
	attachmentTearFactor = 1.5f;
	attachmentResponseCoefficient = 0.2f;
	collisionResponseCoefficient = 0.2f;
	toFluidResponseCoefficient = 1.0f;
	fromFluidResponseCoefficient = 1.0f;
	compressionLimit = 1.0f;
	compressionStiffness = 1.0f;
	minAdhereVelocity = 1.0f;
	flags = NX_CLF_GRAVITY;
    solverIterations = 5;
    hierarchicalSolverIterations = 2;
	wakeUpCounter = NX_SLEEP_INTERVAL;
	sleepLinearVelocity = -1.0f;
	collisionGroup = 0;
	forceFieldMaterial = 0;
	externalAcceleration.set(0.0f, 0.0f, 0.0f);
	windAcceleration.set(0.0f, 0.0f, 0.0f);
	groupsMask.bits0 = 0;
	groupsMask.bits1 = 0;
	groupsMask.bits2 = 0;
	groupsMask.bits3 = 0;
	validBounds.setEmpty();
	relativeGridSpacing = 0.25f;
	meshData.setToDefault();
	splitPairData.setToDefault();
  	userData = NULL;
	name = NULL;
	compartment = NULL;
}

/*----------------------------------------------------------------------------*/

NX_INLINE NxU32 NxClothDesc::checkValid() const
{
	if (flags & NX_CLF_INTER_COLLISION) return 1;	// not supported on any platform yet
	if(!clothMesh) return 2;
	if(!globalPose.isFinite()) return 3;
	if(thickness < 0.0f) return 4;
	if(selfCollisionThickness <= 0.0f) return 5;
	if(density <= 0.0f) return 6;
	if(bendingStiffness < 0.0f || bendingStiffness > 1.0f) return 7;
	if(stretchingStiffness <= 0.0f || stretchingStiffness > 1.0f) return 8;
	if(pressure < 0.0f) return 9;
	if(tearFactor <= 1.0f) return 10;
	if(attachmentTearFactor <= 1.0f) return 11;
	if(solverIterations < 1) return 12;
	if(friction < 0.0f || friction > 1.0f) return 13;
	if(!meshData.isValid()) return 14;
	if(!splitPairData.isValid()) return 15;
	if(dampingCoefficient < 0.0f || dampingCoefficient > 1.0f) return 16;
    if(collisionResponseCoefficient < 0.0f) return 17;
	if(wakeUpCounter < 0.0f) return 18;
	if(attachmentResponseCoefficient < 0.0f || attachmentResponseCoefficient > 1.0f) return 19;
	if(toFluidResponseCoefficient < 0.0f) return 20;
	if(fromFluidResponseCoefficient < 0.0f) return 21;
	if(minAdhereVelocity < 0.0f) return 22;
	if(relativeGridSpacing < 0.01f) return 23;
	if(collisionGroup >= 32) return 24; // We only support 32 different collision groups
	return 0;
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

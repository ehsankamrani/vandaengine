#ifndef NX_PHYSICS_NX_SOFTBODYDESC
#define NX_PHYSICS_NX_SOFTBODYDESC
/** \addtogroup softbody
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

class NxSoftBodyMesh;
class NxCompartment;

/**
\brief Collection of flags describing the behavior of a soft body.

@see NxSoftBody NxSoftBodyMesh NxSoftBodyMeshDesc
*/
enum NxSoftBodyFlag
{
	/**
	\brief Makes the soft body static. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_SBF_STATIC			  = (1<<1),

	/**
	\brief Disable collision handling with the rigid body scene. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.collisionResponseCoefficient
	*/
	NX_SBF_DISABLE_COLLISION  = (1<<2),

	/**
	\brief Enable/disable self-collision handling within a single soft body.
	
	Note: self-collisions are only handled inbetween the soft body's particles, i.e.,
	particles do not collide against the tetrahedra of the soft body.
	The user should therefore specify a large enough particleRadius to avoid
	most interpenetrations. See NxSoftBodyDesc.particleRadius.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_SBF_SELFCOLLISION	  = (1<<3),

	/**
	\brief Enable/disable debug visualization. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_SBF_VISUALIZATION	  = (1<<4),

	/**
	\brief Enable/disable gravity. If off, the soft body is not subject to the gravitational force
	of the rigid body scene.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes
	*/
	NX_SBF_GRAVITY            = (1<<5),

	/**
	\brief Enable/disable volume conservation. Select volume conservation through 
	NxSoftBodyDesc.volumeStiffness.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.volumeStiffness
	*/
	NX_SBF_VOLUME_CONSERVATION            = (1<<6),

	/**
	\brief Enable/disable damping of internal velocities. Use NxSoftBodyDesc.dampingCoefficient
	to control damping.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.dampingCoefficient
	*/
	NX_SBF_DAMPING            = (1<<7),

	/**
	\brief Enable/disable two way collision of the soft body with the rigid body scene.
	
	In either case, the soft body is influenced by colliding rigid bodies.
	If NX_SBF_COLLISION_TWOWAY is not set, rigid bodies are not influenced by 
	colliding with the soft body. Use NxSoftBodyDesc.collisionResponseCoefficient to
	control the strength of the feedback force on rigid bodies.

	When using two way interaction care should be taken when setting the density of the attached objects.
	For example if an object with a very low or high density is attached to a soft body then the simulation 
	may behave poorly. This is because impulses are only transfered between the soft body and rigid body solver
	outside the solvers.

	Two way interaction works best when NX_SF_SEQUENTIAL_PRIMARY is set in the primary scene. If not set,
	collision and attachment artifacts may happen.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.collisionResponseCoefficient
	*/
	NX_SBF_COLLISION_TWOWAY   = (1<<8),

	/**
	\brief Defines whether the soft body is tearable. 
	
	Make sure meshData.maxVertices and the corresponding buffers
	in meshData are substantially larger (e.g. 2x) than the number 
	of original vertices since tearing will generate new vertices.
	When the buffer cannot hold the new vertices anymore, tearing stops.
	If this buffer is chosen big enough, the entire mesh can be 
	torn into all constituent tetrahedral elements. 
	(The theoretical maximum needed is 12 times the original number of vertices. 
	For reasonable mesh topologies, this should never be reached though.)
	
	If the soft body is simulated on the hardware, additional buffer 
	limitations that cannot be controlled by the user exist. Therefore, soft 
	bodies might cease to tear apart further, even though not all space in 
	the user buffer is used up.

	Note: For tearing in hardware, make sure you cook the mesh with
	the flag NX_SOFTBODY_MESH_TEARABLE set in the NxSoftBodyMeshDesc.flags.

	Only vertices that have the NX_SOFTBODY_VERTEX_TEARABLE flag set are torn.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.tearFactor NxSoftBodyDesc.meshData NxSoftBodyMeshDesc.flags
	*/
	NX_SBF_TEARABLE           = (1<<9),

	/**
	\brief Defines whether this soft body is simulated on the GPU.
	
	To simulate a soft body on the GPU
	set this flag and create the soft body in a regular software scene. 
	Note: only use this flag during creation, do not change it using NxSoftBody.setFlags().
	*/
	NX_SBF_HARDWARE           = (1<<10),

	/**
	\brief Enable/disable center of mass damping of internal velocities. 

	This flag only has an effect if the flag NX_SBF_DAMPING is set. If set, 
	the global rigid body modes (translation and rotation) are extracted from damping. 
	This way, the soft body can freely move and rotate even under high damping. 
	Use NxSoftBodyDesc.dampingCoefficient to control damping. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.dampingCoefficient
	*/
	NX_SBF_COMDAMPING		  = (1<<11),

	/**
	\brief If the flag NX_SBF_VALIDBOUNDS is set, soft body particles outside the volume
	defined by NxSoftBodyDesc.validBounds are automatically removed from the simulation. 

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.validBounds
	*/
	NX_SBF_VALIDBOUNDS		  = (1<<12),

	/**
	\brief Enable/disable collision handling between this soft body and fluids. 

	Note: With the current implementation, do not switch on fluid collision for
	many soft bodies. Create scenes with a few bodies because the memory usage
	increases linearly with the number of soft bodies.
	The performance of the collision detection is dependent on both the particle 
	radius of the soft body and the particle radius of the fluid, so tuning 
	these parameters might improve the performance significantly.

	Note: The current implementation does not obey the NxScene::setGroupCollisionFlag
	settings. If NX_SBF_FLUID_COLLISION is set, collisions will take place even if
	collisions between the groups that the corresponding soft body and fluid belong to are
	disabled.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.fluidCollisionResponseCoefficient
	*/
	NX_SBF_FLUID_COLLISION    = (1<<13),

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
	NX_SBF_DISABLE_DYNAMIC_CCD  = (1<<14),

	/**
	\brief Moves soft body partially in the frame of the attached actor. 

	This feature is useful when the soft body is attached to a fast moving shape.
	In that case the soft body adheres to the shape it is attached to while only 
	velocities below the parameter minAdhereVelocity are used for secondary effects.

	<b>Platform:</b>
	\li PC SW: Yes
	\li GPU  : Yes
	\li PS3  : Yes
	\li XB360: Yes
	\li WII	 : Yes

	@see NxSoftBodyDesc.minAdhereVelocity
	*/
	NX_SBF_ADHERE  = (1<<15),


	/**
	\brief Uses the information provided by NxSoftBody.setConstrainPositions() and
	NxSoftBody.setConstrainCoefficients() to make the cloth less stretchy.

	If the flag is set, the solver pulls vertices 
	with a maxDistance greater zero towards vertices with maxDistance zero (attached). 
	This reduces the stretchiness even for low solver iteration counts. The process is
	non-physical and can yield small ghost forces. The NxSoftBody.hardStretchLimitationFactor
	defines by what factor the soft body is allowed to stretch.

	@see NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainCoefficients() NxSoftBody.hardStretchLimitationFactor
	*/
	NX_SBF_HARD_STRETCH_LIMITATION = (1<<20),

	/**
	\brief Allows soft body to collide with cloth and with other soft bodies.

	Not implemented.

	<b>Platform:</b>
	\li PC SW: No
	\li GPU  : No
	\li PS3  : No
	\li XB360: No
	\li WII	 : No

	@see NxSoftBodyDesc.selfCollisionThickness
	*/
	NX_SBF_INTER_COLLISION = (1<<21)
};

/*----------------------------------------------------------------------------*/

/**
\brief Soft body attachment flags.

@see NxSoftBody.attachToShape() NxSoftBody.attachToCollidingShapes() NxSoftBody.attachVertexToShape()
*/
enum NxSoftBodyAttachmentFlag
{
	/**
	\brief The default is only object->soft body interaction (one way).

	With this flag set, soft body->object interaction is turned on as well.
	
	Care should be taken if objects with small masses (either through low 
	density or small volume) are attached, as the simulation may easily become unstable. 
	The NxSoftBodyDesc.attachmentResponseCoefficient field should be used to lower
	the magnitude of the impulse transfer from the soft body to the attached rigid body.
	*/
	NX_SOFTBODY_ATTACHMENT_TWOWAY			  = (1<<0),

	/**
	\brief When this flag is set, the attachment is tearable.

	@see NxSoftBodyDesc.attachmentTearFactor
	*/
	NX_SOFTBODY_ATTACHMENT_TEARABLE		  = (1<<1)
};

/*----------------------------------------------------------------------------*/

/**
\brief User-side class specifying a tetrahedron split generated from a torn soft body.

Faces 0,1,2,3 contain the tetrahedral vertices {2,1,0}, {0,1,3}, {1,2,3}, {2,0,3} respectively.
*/
class NxSoftBodySplitPair
{
public:
	NxU32 tetrahedronIndex0;
	NxU32 tetrahedronIndex1;
	NxU8 faceIndex0;
	NxU8 faceIndex1;    
};

/**
\brief User-side class for receiving tetrahedron split events for torn softbodies.

The user can optionally receive tetrahedron split event data if a soft body gets torn.
One split is represented by a pair of tetrahedron indices and a pair of face indices.
The tetrahedra indices can be used to locate the vertex index quadruple belonging to 
the two mesh tetrahedra involved in split.

Each pair is garantueed to be reported only once.
*/
class NxSoftBodySplitPairData
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
	NxSoftBodySplitPair*	splitPairsBegin;
	
	/**
	\brief The separation (in bytes) between consecutive split pairs.

	The first split pair is found at location <tt>splitPairsBegin</tt>;
	the second is at <tt>splitPairsBegin + splitPairsByteStride</tt>;
	and so on.
	*/
	NxU32	splitPairsByteStride;

	NX_INLINE ~NxSoftBodySplitPairData();

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
	NX_INLINE	NxSoftBodySplitPairData();
};

NX_INLINE NxSoftBodySplitPairData::NxSoftBodySplitPairData()
	{
	setToDefault();
	}

NX_INLINE NxSoftBodySplitPairData::~NxSoftBodySplitPairData()
	{
	}

NX_INLINE void NxSoftBodySplitPairData::setToDefault()
	{
	maxSplitPairs			= 0;
	numSplitPairsPtr		= NULL;
	splitPairsBegin			= NULL;
	splitPairsByteStride	= 0;
	}

NX_INLINE NxU32 NxSoftBodySplitPairData::checkValid() const
	{
	if (numSplitPairsPtr  && !splitPairsBegin) return 1;
	if (!numSplitPairsPtr &&  splitPairsBegin) return 2;
	if (splitPairsBegin && !splitPairsByteStride) return 3;
	return 0;
	}

/*----------------------------------------------------------------------------*/

/**
\brief Defines a set of per vertex coefficients

The user can supply a buffer of positions and normals coming from an animation of the soft body
or instance. The simulated vertices are then corrected via the constrain positions, normals
and the constrain coefficiens.

@see NxSoftBody.setConstrainCoefficients() NxSoftBody.setConstrainPositions NxSoftBody.setConstrainNormals
*/
class NxSoftBodyConstrainCoefficients
{
public:
	/**
	\brief Distance a vertex is allowed to travel from the constrain position.

	If constrain positions are provided via NxSoftBody.setConstrainPositions the SDK makes sure
	that the soft body vertices stay within maxDistance from the constrain positions. 
	If maxDistance is zero, the vertex is not simulated but set to the constrain position.
	This behavior is useful for attaching the soft body vertex to the skin of an animated character.

	<b>Default:</b> 0.0 <br>
	<b>Range:</b> [0,inf)

	@see NxSoftBody.setConstrainCoefficients() NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainNormals()
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

	@see NxSoftBody.setConstrainCoefficients() NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainNormals()
	*/
	NxReal maxDistanceBias;

	/**
	\brief Definition of a sphere a vertex is not allowed to enter. This allows collision against the animated soft body.

	For this parameter to have an effect, both, constrain positions and constrain normals need to be provided via
	NxSoftBody.setConstrainPositions() and NxSoftBody.setConstrainNormals(). 
	The pair (collisionSphereRadius, collisionSphereDistance) define a sphere for each soft body vertex. The sphere's
	center is located at the position 
	constrainPosition - constrainNormal * (collisionSphereRadius + collisionSphereDistance) and its radius
	is collisionSphereRadius. The SDK makes sure that the soft body vertex does not enter this sphere.
	As a typical usecase, set collisionSphereDistance to zero and collisionSphereRadius to a large value
	w.r.t. the triangle size. In this setup, the soft body collides against the animated mesh.

	<b>Default:</b> 0.0 <br>
	<b>Range:</b> [0,inf)

	@see NxSoftBody.setConstrainCoefficients() NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainNormals()
	*/
	NxReal collisionSphereRadius;

	/**
	\brief Definition of a sphere a vertex is not allowed to enter. This allows collision against the animated soft body.

	@see NxSoftBodyConstrainCoefficients.collisionSphereRadius NxSoftBody.setConstrainCoefficients() NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainNormals()
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

NX_INLINE void NxSoftBodyConstrainCoefficients::setToDefault()
	{
	maxDistance			    = 0.0f;
	maxDistanceBias         = 0.0f;
	collisionSphereRadius   = 0.0f;
	collisionSphereDistance	= 0.0f;
	}

NX_INLINE NxU32 NxSoftBodyConstrainCoefficients::checkValid() const
	{
	if (maxDistance < 0.0f) return 1;
	if (collisionSphereRadius < 0.0f) return 2;
	return 0;
	}


/*----------------------------------------------------------------------------*/

/**
\brief Descriptor class for #NxSoftBody.

@see NxSoftBody NxSoftBody.saveToDesc()
*/
class NxSoftBodyDesc
{
public:
	/**
	\brief The cooked soft body mesh.

	<b>Default:</b> NULL

	@see NxSoftBodyMesh NxSoftBodyMeshDesc NxSoftBody.getSoftBodyMesh()
	*/
	NxSoftBodyMesh *softBodyMesh;

	/**
	\brief The global pose of the soft body in the world.

	<b>Default:</b> Identity Transform
	*/
	NxMat34 globalPose;

	/**
	\brief Size of the particles used for collision detection.

	The particle radius is usually a fraction of the overall extent of the soft body and
	should not be set to a value greater than that.	A good value is the maximal
	distance between two adjacent soft body particles in their rest pose. Visual
	artifacts or collision problems may appear if the particle radius is too small.

	<b>Default:</b> 0.1 <br>
	<b>Range:</b> [0,inf)

	@see NxSoftBody.setParticleRadius()
	*/
	NxReal particleRadius;

	/**
	\brief Size of the particle diameters used for self collision and inter-collision.

	The self collision thickness is usually a fraction of the overall extent of the soft body and
	should not be set to a value greater than that.	A good value is the maximal
	distance between two adjacent soft body particles in their rest pose. Visual
	artifacts or collision problems may appear if the particle radius is too small.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> (0,inf)

	@see NxSoftBody.setSelfCollisionThickness()
	*/
	NxReal selfCollisionThickness;

	/**
	\brief Density of the soft body (mass per volume).

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> (0,inf)
	*/
	NxReal density;

	/**
	\brief Volume stiffness of the soft body in the range 0 to 1. 

	Defines how strongly the soft body counteracts deviations from the rest volume.
	Only has an effect if the flag NX_SBF_VOLUME_CONSERVATION is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,1]
	
	@see NX_SBF_VOLUME_CONSERVATION NxSoftBody.setVolumeStiffness()
	*/
	NxReal volumeStiffness;
	
	/**
	\brief Stretching stiffness of the soft body in the range 0 to 1.

	Defines how strongly the soft body counteracts deviations from the rest lengths of edges.
	
	Note: stretching stiffness must be larger than 0. Even if the stretching stiffness is set very low,
	tetrahedra edges will cease to stretch further if their length exceeds a certain internal limit.
	This is done to prevent heavily degenerated tetrahedral elements which could occur otherwise.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> (0,1]

	@see NxSoftBody.setStretchingStiffness()
	*/
	NxReal stretchingStiffness;

	/**
	\brief Defines the hard stretch elongation limit

	If the flag NX_SBF_HARD_STRETCH_LIMITATION is set, the solver pulls vertices 
	with a maxDistance greater zero towards vertices with maxDistance zero (attached). 
	This reduces the stretchiness even for low solver iteration counts. The process is
	non-physical and can yield small ghost forces. The hardStretchLimitationFactor
	defines by what factor the soft body is allowed to stretch.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)

	@see NxSoftBody.setConstrainPositions() NxSoftBody.setConstrainCoefficients() NxSoftBody.setHardStretchLimitationFactor()
	*/
	NxReal hardStretchLimitationFactor;

	/**
	\brief Spring damping of the soft body in the range 0 to 1.

	Only has an effect if the flag NX_SBF_DAMPING is set.

	<b>Default:</b> 0.5 <br>
	<b>Range:</b> [0,1]
	
	@see NX_SBF_DAMPING NxSoftBody.setDampingCoefficient()
	*/
	NxReal dampingCoefficient;

	/**
	\brief Friction coefficient in the range 0 to 1. 

	Defines the damping of the velocities of soft body particles that are in contact.

	<b>Default:</b> 0.5 <br>
	<b>Range:</b> [0,1]

	@see NxSoftBody.setFriction()
	*/
	NxReal friction;

	/**
	\note Experimental feature.

	\brief If the flag NX_SBF_TEARABLE is set, this variable defines the 
	elongation factor that causes the soft body to tear. 

	Must be larger than 1.
	Make sure meshData.maxVertices and the corresponding buffers
	in meshData are substantially larger (e.g. 2x) then the number 
	of original vertices since tearing will generate new vertices.
	
	When the buffer cannot hold the new vertices anymore, tearing stops.

	<b>Default:</b> 1.5 <br>
	<b>Range:</b> (1,inf)

	@see NxSoftBody.setTearFactor()
	*/
	NxReal tearFactor;

	/**
	\brief Defines a factor for the impulse transfer from the soft body to colliding rigid bodies.

	Only has an effect if NX_SBF_COLLISION_TWOWAY is set.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> [0,inf)
	
	@see NX_SBF_COLLISION_TWOWAY NxSoftBody.setCollisionResponseCoefficient()
	*/
	NxReal collisionResponseCoefficient;

	/**
	\brief Defines a factor for the impulse transfer from the soft body to attached rigid bodies.

	Only has an effect if the mode of the attachment is set to NX_SOFTBODY_ATTACHMENT_TWOWAY.

	<b>Default:</b> 0.2 <br>
	<b>Range:</b> [0,1]
	
	@see NxSoftBody.attachToShape NxSoftBody.attachToCollidingShapes NxSoftBody.attachVertexToShape NxSoftBody.setAttachmentResponseCoefficient()
	*/
	NxReal attachmentResponseCoefficient;
	
	/**
	\brief If the flag NX_SOFTBODY_ATTACHMENT_TEARABLE is set in the attachment method of NxSoftBody, 
	this variable defines the elongation factor that causes the attachment to tear. 

	Must be larger than 1.

	<b>Default:</b> 1.5 <br>
	<b>Range:</b> (1,inf)

	@see NxSoftBody.setAttachmentTearFactor() NxSoftBody.attachToShape NxSoftBody.attachToCollidingShapes NxSoftBody.attachVertexToShape
	*/
	NxReal attachmentTearFactor;

	/**
	\brief Defines a factor for the impulse transfer from this soft body to colliding fluids.

	Only has an effect if the NX_SBF_FLUID_COLLISION flag is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)
	
	Note: Large values can cause instabilities

	@see NxSoftBodyDesc.flags NxSoftBodyDesc.fromFluidResponseCoefficient
	*/
	NxReal toFluidResponseCoefficient;

	/**
	\brief Defines a factor for the impulse transfer from colliding fluids to this soft body.

	Only has an effect if the NX_SBF_FLUID_COLLISION flag is set.

	<b>Default:</b> 1.0 <br>
	<b>Range:</b> [0,inf)

	Note: Large values can cause instabilities

	@see NxSoftBodyDesc.flags NxSoftBodyDesc.toFluidResponseCoefficient
	*/
	NxReal fromFluidResponseCoefficient;

	/**
	\brief If the NX_SBF_ADHERE flag is set the soft body moves partially in the frame 
	of the attached actor. 

	This feature is useful when the soft body is attached to a fast moving shape.
	In that case the soft body adheres to the shape it is attached to while only 
	velocities below the parameter minAdhereVelocity are used for secondary effects.

	<b>Default:</b> 1.0
	<b>Range:</b> [0,inf)

	@see NX_SBF_ADHERE
	*/ 

	NxReal minAdhereVelocity;

	/**
	\brief Number of solver iterations. 

	Note: Small numbers make the simulation faster while the soft body gets less stiff.

	<b>Default:</b> 5
	<b>Range:</b> [1,inf)

	@see NxSoftBody.setSolverIterations()
	*/ 
	NxU32  solverIterations;

	/**
	\brief External acceleration which affects all non attached particles of the soft body. 

	<b>Default:</b> (0,0,0)

	@see NxSoftBody.setExternalAcceleration()
	*/ 
	NxVec3 externalAcceleration;

	/**
	\brief The soft body wake up counter.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> 20.0f*0.02f

	@see NxSoftBody.wakeUp() NxSoftBody.putToSleep()
	*/
	NxReal wakeUpCounter;

	/**
	\brief Maximum linear velocity at which the soft body can go to sleep.
	
	If negative, the global default will be used.

	<b>Range:</b> [0,inf)<br>
	<b>Default:</b> -1.0

	@see NxSoftBody.setSleepLinearVelocity() NxSoftBody.getSleepLinearVelocity()
	*/
	NxReal sleepLinearVelocity;

	/**
	\brief The buffers in meshData are used to communicate the dynamic data of the soft body back to the user.
	
	For example vertex positions and connectivity (tetrahedra). The internal order
	of the contents of meshData's buffers will remain the same as that in the initial mesh data used to create the mesh.

	<b>Default:</b> See #NxMeshData

	@see NxMeshData NxSoftBody.setMeshData()
	*/
	NxMeshData meshData;

	/**
	\brief 	The buffers in splitPairData are used to communicate the split tetrahedra data of the soft body back to the user.
	
	@see NxSoftBodySplitPairData
	*/
	NxSoftBodySplitPairData splitPairData;

	/**
	\brief Sets which collision group this soft body is part of.

	<b>Range:</b> [0, 31]
	<b>Default:</b> 0

	NxSoftBody.setCollisionGroup()
	*/
	NxCollisionGroup collisionGroup;

	/**
	\brief Sets the 128-bit mask used for collision filtering.

	<b>Default:</b> 0

	@see NxGroupsMask NxSoftBody.setGroupsMask() NxSoftBody.getGroupsMask()
	*/
	NxGroupsMask groupsMask;

	/**
	\brief Force Field Material Index, index != 0 has to be created.

	<b>Default:</b> 0
	*/
	NxU16 forceFieldMaterial;

	/**
	\brief If the flag NX_SBF_VALIDBOUNDS is set, this variable defines the volume
	outside of which soft body particles are automatically removed from the simulation. 

	@see NX_SBF_VALIDBOUNDS NxSoftBody.setValidBounds()
	*/
	NxBounds3 validBounds;

	/**
	\brief This parameter defines the size of grid cells for collision detection.

	The soft body is represented by a set of world aligned cubical cells in broad phase.
	The size of these cells is determined by multiplying the length of the diagonal
	of the AABB of the initial soft body size with this constant.

	<b>Range:</b> [0.01,inf)<br>
	<b>Default:</b> 0.25
	*/
	NxReal relativeGridSpacing;

	/**
	\brief Flag bits.

	<b>Default:</b> NX_SBF_GRAVITY | NX_SBF_VOLUME_CONSERVATION

	@see NxSoftBodyFlag NxSoftBody.setFlags()
	*/ 
	NxU32 flags;

	/**
	\brief Will be copied to NxSoftBody::userData

	<b>Default:</b> NULL

	@see NxSoftBody.userData
	*/
	void* userData;

	/**
	\brief Possible debug name. The string is not copied by the SDK, only the pointer is stored.

	<b>Default:</b> NULL

	@see NxSoftBody.setName() NxSoftBody.getName()
	*/
	const char* name;

	/**
	\brief The compartment to place the soft body in. The soft body feature currently uses the cloth 
	simulation, so this must be either a pointer to an NxCompartment of type NX_SCT_SOFTBODY 
	(or NX_SCT_CLOTH, since cloth and softbody currently use the same compartments), or NULL.
	A NULL compartment means creating the soft body in the first available cloth compartment 
	(a default cloth compartment is created if none exists). A software soft body with a NULL 
	compartment is created in the scene on which createSoftBody() is called.

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
	NX_INLINE NxSoftBodyDesc();

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

NX_INLINE NxSoftBodyDesc::NxSoftBodyDesc()
{
	setToDefault();
}

/*----------------------------------------------------------------------------*/

NX_INLINE void NxSoftBodyDesc::setToDefault()
{
	softBodyMesh = NULL;
	globalPose.id();
	particleRadius = 0.1f;
	selfCollisionThickness = 0.2f;
	density = 1.0f;
	volumeStiffness = 1.0f;
	stretchingStiffness = 1.0f;
	hardStretchLimitationFactor = 1.0f;
    dampingCoefficient = 0.5f;
	friction = 0.5f;
	tearFactor = 1.5f;
	attachmentTearFactor = 1.5f;
	attachmentResponseCoefficient = 0.2f;
	collisionResponseCoefficient = 0.2f;
	toFluidResponseCoefficient = 1.0f;
	fromFluidResponseCoefficient = 1.0f;
	minAdhereVelocity = 1.0f;
	flags = NX_SBF_GRAVITY | NX_SBF_VOLUME_CONSERVATION;
    solverIterations = 5;
	wakeUpCounter = NX_SLEEP_INTERVAL;
	sleepLinearVelocity = -1.0f;
	collisionGroup = 0;
	externalAcceleration.set(0.0f, 0.0f, 0.0f);
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
	forceFieldMaterial = 0;
}

/*----------------------------------------------------------------------------*/

NX_INLINE NxU32 NxSoftBodyDesc::checkValid() const
{
	if (flags & NX_SBF_INTER_COLLISION) return 1;	// not supported on any platform yet

	if(!softBodyMesh) return 2;
	if(!globalPose.isFinite()) return 3;
	if(particleRadius < 0.0f) return 4;
	if(selfCollisionThickness <= 0.0f) return 5;
	if(density <= 0.0f) return 6;
	if(volumeStiffness < 0.0f || volumeStiffness > 1.0f) return 7;
	if(stretchingStiffness <= 0.0f || stretchingStiffness > 1.0f) return 8;
	if(tearFactor <= 1.0f) return 9;
	if(attachmentTearFactor <= 1.0f) return 10;
	if(solverIterations < 1) return 11;
	if(friction < 0.0f || friction > 1.0f) return 12;
	if(!meshData.isValid()) return 13;
	if(!splitPairData.isValid()) return 14;
	if(dampingCoefficient < 0.0f || dampingCoefficient > 1.0f) return 15;
    if(collisionResponseCoefficient < 0.0f) return 16;
	if(wakeUpCounter < 0.0f) return 17;
	if(attachmentResponseCoefficient < 0.0f || attachmentResponseCoefficient > 1.0f) return 18;
	if(toFluidResponseCoefficient < 0.0f) return 19;
	if(fromFluidResponseCoefficient < 0.0f) return 20;
	if(minAdhereVelocity < 0.0f) return 21;
	if(relativeGridSpacing < 0.01f) return 22;
	if(collisionGroup >= 32) return 23; // We only support 32 different collision groups
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

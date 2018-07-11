#ifndef	CORE_CONTAINER_H

#define	CORE_CONTAINER_H

#include <NxVersionNumber.h>

#include <NxPhysics.h>
#include <stdio.h>

#define MAX_FLT_DIFF 0.00000001f

typedef NxArray< char * >			CharacterArray;

class AsciiCoreDump;

//==================================================================================
typedef	struct
{
	unsigned	  mFlag;
	int			  mActorIndex1;
	int			  mActorIndex2;
	int			  mShapeIndex1;
	int			  mShapeIndex2;
} PairFlagCapsule;

//==================================================================================
typedef struct
{
	NxVec3			mPlaneNormal;
	NxVec3          mWorldLimitPt;
	float           mPlaneD;
} PlaneInfo;

//==================================================================================
typedef struct
{
	NxVec3                       mPlaneLimitPoint;
	bool                         mOnActor2;
	NxJointDesc                 *mDesc;
	NxArray< PlaneInfo * >       mPlaneInfo;
} JointDescription;

enum SceneType
{
	ST_DEFAULT,
	ST_FORCE_SOFTWARE,
	ST_FORCE_HARDWARE,
	ST_LAST
};

//==================================================================================
enum CoreDifference
{
	CD_NUM_ACTORS,						// # of 'NxActorDesc's differ
	CD_NUM_JOINTS,						// # of 'NxJointDesc's differ
	CD_NUM_CORE_SCENES,					// # of 'CoreScene's differ
	CD_NUM_TRIANGLE_MESHES,				// # of 'NxTriangleMeshDesc's differ
	CD_NUM_CONVEX_MESHES,				// # of 'NxConvexMeshDesc's differ
	CD_NUM_MATERIALS,					// # of 'NxMaterialDesc's differ
	CD_NUM_PAIR_COUNTS,					// # of 'PairFlagCapsule's differ
	CD_NUM_SADE,                        // # of 'SpringAndDamperEffectorDesc's differs
	CD_NUM_JOINT_LIMIT_INFO,            // # of a joint's Limit plane info's differ
	CD_MATERIAL_DESC,					// an item in an NxMaterialDesc differs
	CD_ACTOR_DESC,						// an item in an NxActorDesc differs
	CD_ACTOR_SHAPE_DESC_MISSING,		// an NxActorShapeDesc is missing
	CD_ACTOR_SHAPE_DESC,				// an item in an 'NxActorDesc's NxShapeDesc differs
	CD_ACTOR_BODY_DESC_DIFF,            // an NxBodyDesc is missing or is now present for an NxActorDesc
	CD_ACTOR_SHAPE_NAME_DESC,			// an NxActorDesc name item is missing or differs
	CD_ACTOR_STATE_POSROT_INFO,         // an NxActor's position or rotation differs
	CD_ACTOR_STATE_VEL_INFO,            // an NxActor's linear or angular velocity differs
	CD_ACTOR_BODY_DESC_MEMBER_INFO,     // an NxActor's NxBodyDesc has a difference
	CD_NUM_ACTOR_SCENES,				// # of 'NxSceneDesc's for an NxActor differs
	CD_PAIR_FLAG_DESC,					// an item in a 'PairFlagCapsule' differs
	
	CD_JOINT_DESC_DIFF,					// an item in an NxJointDesc differs
	CD_JOINT_DESC_ACTOR_DIFF,			// one of the joint's actor references differs
	CD_JOINT_DESC_VECTOR_DIFF,			// one of the NxVec3 items in an NxJointDesc differs
	CD_JOINT_DESC_NAME_DIFF,			// an NxJointDesc name item is missing or differs

	CD_REV_JOINT_DESC_DIFF,				// a "normal" revolution joint diff
	CD_REV_JOINT_DESC_LOW_LIMIT_DIFF,	// a NxJointLimitDesc (low limit) revolution joint diff
	CD_REV_JOINT_DESC_HIGH_LIMIT_DIFF,	// a NxJointLimitDesc (high limit) revolution joint diff
	CD_REV_JOINT_DESC_MOTOR_DIFF,		// a NxMotorDesc revolution joint diff
	CD_REV_JOINT_DESC_SPRING_DIFF,		// a NxSpringDesc revolution joint diff

	CD_PULLEY_JOINT_DESC_DIFF,			// a "normal" pully joint diff
	CD_PULLEY_JOINT_DESC_MOTOR_DIFF,	// a pully's NxMotorDesc diff
	CD_PULLEY_JOINT_DESC_PULLEY_DIFF,	// a NxVec3 of pully's pully joint has a diff

	CD_SPHERE_JOINT_DESC_DIFF,			// a "normal" spherical joint diff
	CD_SPHERE_JOINT_DESC_SWINGAXIS_DIFF,// a swing-axis (NxVec3) joint diff for a spherical joint
	CD_SPHERE_JOINT_DESC_LIMIT_DIFF,	// a NxJointLimitDesc diff for a spherical joint
	CD_SPHERE_JOINT_DESC_SPRING_DIFF,	// a NxSpringDesc diff for a spherical joint

	CD_DIST_JOINT_DESC_DIFF,			// a "normal" distance joint desc diff
	CD_DIST_JOINT_DESC_SPRING_DIFF,		// a NxSpringDesc diff for a distance joint

	CD_D6_JOINT_DESC_DIFF,				// a "normal" D6 joint desc diff
	CD_D6_JOINT_DESC_MOTION_DIFF,		// a motion item of the D6 joint has a diff
	CD_D6_JOINT_SOFT_DESC_DIFF,			// a NxJointLimitSoftDesc diff for a D6 joint desc
	CD_D6_JOINT_DRIVE_DESC_DIFF,		// a NxJointDriveDesc diff for a D6 joint desc
	CD_D6_JOINT_VEC_DESC_DIFF,			// one of the NxVec3 has a diff for a D6 joint desc
	CD_D6_JOINT_QUAT_DESC_DIFF,			// the NxQuat has a diff for a D6 joint desc

	CD_SADE_BODY_DIFF,					// the body indexes do not match for an NxSpringAndDamperEffectorDesc
	CD_SADE_SPRING_PARAM,               // one or more of the spring parameters do not match for an NxSpringAndDamperEffectorDesc
	CD_SADE_DAMPER_PARAM,				// one or more of the damper parameters do not match for an NxSpringAndDamperEffectorDesc

	CD_JOINT_LIMIT_PLANE_NORMAL,        // a joint's limit plane's normal differs in either x,y, and/or z
	CD_JOINT_LIMIT_PLANE_POINT,			// a joint's limit plane's point differs
	CD_JOINT_LIMIT_PLANE_D,  			// a joint's limit plane's planeD differs
	CD_JOINT_LIMIT_PLANE_WORLD_PT,		// a joint's limit plane's world pt differs

	CD_HEIGHT_FIELD_NUM,				// number of height fields
	CD_HEIGHT_FIELD_CET_DIFF,			// convex edge threshold diff
	CD_HEIGHT_FIELD_FLAGS,				// flags
	CD_HEIGHT_FIELD_FORMAT,				// format diff
	CD_HEIGHT_FIELD_NUM_COLUMNS,		// nb columns diff
	CD_HEIGHT_FIELD_NUM_ROWS,			// nb rows diff
	CD_HEIGHT_FIELD_SAMPLE_STRIDE,		// sample stride diff
	CD_HEIGHT_FIELD_VERTICAL_EXTENT,	// vertical extent diff
	CD_HEIGHT_FIELD_MISSING_SAMPLES,	// one is missing samples, and other has them
	CD_HEIGHT_FIELD_SAMPLE_MEM_DIFF,	// both have samples, but they differ

	CD_LAST
};

//==================================================================================
enum TriangleMeshDifferences
{
	TMD_CET,
	TMD_FLAGS,
	TMD_HFVA,
	TMD_HFVE,
	TMD_MIS,
	TMD_PMAP_MISSING,
	TMD_PMAP_NUMVERTS,
	TMD_VERT_NUM,
	TMD_VERT_STRIDE,
	TMD_VERT_PTS,
	TMD_TRI_NUMVERTS,
	TMD_TRI_STRIDE,
	TMD_TRI_TRIS,
	TMD_LAST
};

//==================================================================================
enum ConvexMeshDifferences
{
	CMD_FLAGS,
	CMD_VERT_NUM,
	CMD_VERT_STRIDE,
	CMD_VERT_PTS,
	CMD_TRI_NUMVERTS,
	CMD_TRI_STRIDE,
	CMD_TRI_TRIS,
	CMD_LAST
};

//==================================================================================
//==================================================================================
class CoreUserNotify
{
public:

	virtual	void CoreNotifyScene(NxScene *scene) = 0;

	/**
	* Notify application of	a joint	creation.
	*/
	virtual	void CoreNotifyJoint(NxJoint *joint) = 0;

	/**
	* Notify application of	a actor	creation.
	*/
	virtual	void CoreNotifyActor(NxActor *actor) = 0;
};

class CoreUserScene
{
public:
  virtual NxScene * CoreCreateScene(NxPhysicsSDK *sdk,const NxSceneDesc &desc) = 0;
};

//==================================================================================
//==================================================================================
class CoreCompareNotify
{
public:

	// if user returns true for any of these functions, then that means the difference was
	// too great, and to STOP comparing - we are done.  Returning false from these
	// means to continue with the comparison - the difference is acceptable.
	virtual	bool CoreDiff( NxParameter param, float v1, float v2 ) = 0;
	virtual	bool CoreDiff( CoreDifference type, int n1, int n2 ) = 0;
	virtual	bool CoreDiff( const NxSceneDesc &s1, const NxSceneDesc &s2 ) = 0;
	virtual	bool CoreDiff( const NxJoint &j1, const NxJoint &j2 ) = 0;	// if user returns true, continue comparing, otherwise abort.
	virtual	bool CoreDiff( const NxActor &a1, const NxActor &a2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, int arrayIndex, const NxMaterialDesc &m1, const NxMaterialDesc &m2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, int arrayIndex, const NxActorDesc &a1, const NxActorDesc &a2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxShapeDesc &s1, const NxShapeDesc &s2 ) = 0;
	virtual bool CoreDiff( TriangleMeshDifferences type, const NxTriangleMeshDesc &t1, const NxTriangleMeshDesc &t2 ) = 0;
	virtual bool CoreDiff( ConvexMeshDifferences type, const NxConvexMeshDesc &c1, const NxConvexMeshDesc &c2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const PairFlagCapsule &p1, const PairFlagCapsule &p2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxJointDesc &j1, const NxJointDesc &j2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxActorDesc &a1, const NxActorDesc &b2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxBodyDesc &b1, const NxBodyDesc &b2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxMat34 &m1, const NxMat34 &m2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxSpringAndDamperEffectorDesc &s1, const NxSpringAndDamperEffectorDesc &s2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const NxVec3 &v1, const NxVec3 &v2 ) = 0;
	virtual bool CoreDiff( CoreDifference type, const PlaneInfo &p1, const PlaneInfo &p2 ) = 0;
#if NX_SDK_VERSION_NUMBER >= 240
	virtual bool CoreDiff( CoreDifference type, const NxHeightFieldDesc &h1, NxHeightFieldDesc &h2 ) = 0;
#endif

	static const char * GetCoreDifferenceTypeString( const CoreDifference type );
	static const char * GetCoreDifferenceDescriptionString( const CoreDifference type );
	static const char * GetTriangleMeshDifferenceTypeString( const TriangleMeshDifferences &type );
	static const char * GetTriangleMeshDifferenceDescriptionString( const TriangleMeshDifferences &type );
	static const char * GetConvexMeshDifferenceTypeString( const ConvexMeshDifferences &type );
	static const char * GetConvexMeshDifferenceDescriptionString( const ConvexMeshDifferences &type );
};

//==================================================================================
//==================================================================================
class CoreScene
{
public:
							     CoreScene(void);
							    ~CoreScene(void);

  bool ValidateSleep(int &awake,int &asleep) const;
  bool ValidateEnergy(float maxVel,float maxAngularVelocity,int &lowEnergy,int &highEnergy) const;

  NxArray< NxMaterialDesc *	>    mMaterials;
  NxArray< NxActorDesc *	>    mActors;

  //NxArray< NxJointDesc * >	     mJointArray;
  NxArray< JointDescription * >  mJointArray;
  PairFlagCapsule			    *mPairFlagArray;
  int						     mPairCount;
  NxSceneDesc				     mDesc;

  NxArray< NxSpringAndDamperEffectorDesc * > mEffectorArray;
};

//==================================================================================
//==================================================================================
class TriangleMeshData
{
public:
							TriangleMeshData(void);
						   ~TriangleMeshData(void);
	void					setToDefault(void);

	NxTriangleMeshDesc 		mTmd;
	void *					mCookedData;
	int						mCookedDataSize;
};

//==================================================================================
//==================================================================================
class ConvexMeshData
{
public:
							ConvexMeshData(void);
						   ~ConvexMeshData(void);
	void					setToDefault(void);

	NxConvexMeshDesc 		mCmd;
	void *					mCookedData;
	int						mCookedDataSize;
};

//==================================================================================
//==================================================================================
class HeightFieldData
{
public:
							HeightFieldData(void);
						   ~HeightFieldData(void);
	void					setToDefault(void);

#if NX_SDK_VERSION_NUMBER >= 240
	NxHeightFieldDesc 		mHfd;
#endif
};

//==================================================================================
//==================================================================================
class CoreContainer
{
public:

									CoreContainer(void);
								   ~CoreContainer(void);


									// load	a core dump...
	bool							LoadCoreDump(NxPhysicsSDK *sdk,const char	*fname); // loads into the container but does not instantiate it.  Needs physics SDK pointer to validate the version
	bool							LoadCoreDump(const char	*fname); // loads into the container but does not instantiate it.  Needs physics SDK pointer to validate the version

	CoreScene				 *GetCoreSceneInfo( unsigned which );
	NxScene				   *InstantiateCoreDump(NxPhysicsSDK *sdk,             // SDK to load the core container into.
	                                      CoreUserNotify *callback	= 0, // notification events to the application as the scene is loaded.
	                                      CoreUserScene  *scene     = 0, // if the user wants control over scene creation
	                                      NxVec3 *offset=0,
	                                      SceneType stype=ST_DEFAULT);              // relative offset to place actors into the scene.


	bool							Compare(const CoreContainer	&diff, CoreCompareNotify *callback, float tolerance = MAX_FLT_DIFF);

	bool							ValidateEnergy(float maxVel,float maxAngularVelocity,int &lowEnergy,int &highEnergy) const;
	bool							ValidateSleep(int &asleep,int &awake) const;

	void							SetParam( unsigned which, float paramValue );
	void							AddTMD( TriangleMeshData *tmd );
	void							AddCMD( ConvexMeshData *cmd );
	void							AddHFD( HeightFieldData *hfd );
	void							AddCoreScene( CoreScene *cs );
	NxShapeDesc	*					CreateShapeFromType( NxShapeType type );
	void							SaveAsPsCommand( int argc, const char **argv, AsciiCoreDump *helper );
	CharacterArray &				GetPsCommands( void );
	
	static const char *             GetStringPntr( const char *str );
	static void						ClearAllStringPntrs( void );

protected:

	bool                            CompareTriMeshDescriptions( NxTriangleMeshDesc *t1, NxTriangleMeshDesc *t2, CoreCompareNotify *callback, int &diffcount, float tolerance = MAX_FLT_DIFF );
	bool                            CompareConvexMeshDescriptions( NxConvexMeshDesc *c1, NxConvexMeshDesc *c2, CoreCompareNotify *callback, int &diffcount, float tolerance = MAX_FLT_DIFF );
#if NX_SDK_VERSION_NUMBER >= 240
	bool                            CompareHeightFieldDescriptions( NxHeightFieldDesc *h1, NxHeightFieldDesc *h2, CoreCompareNotify *callback, int &diffcount, float tolerance = MAX_FLT_DIFF );
#endif
	bool                            CompareSceneDescriptions( CoreScene *c1, CoreScene *c2, CoreCompareNotify *callback, int &diffcount, float tolerance = MAX_FLT_DIFF );
	bool                            FloatDiff( const float &, const float &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            Vec3Diff( const NxVec3 &, const NxVec3 &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            QuatDiff( const NxQuat &, const NxQuat &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            JointLimitSoftDescDiff( const NxJointLimitSoftDesc &, const NxJointLimitSoftDesc &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            JointDriveDescDiff( const NxJointDriveDesc &, const NxJointDriveDesc &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            SpringDescDiff( const NxSpringDesc &, const NxSpringDesc &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            MotorDescDiff( const NxMotorDesc &, const NxMotorDesc &, float tolerance = MAX_FLT_DIFF ) const;
	bool                            JointLimitDescDiff( const NxJointLimitDesc &, const NxJointLimitDesc &, float tolerance = MAX_FLT_DIFF ) const;
	int                             SceneDescDiff( const NxSceneDesc &, const NxSceneDesc &, float tolerance = MAX_FLT_DIFF ) const;

private:

	// private member fn's
	void							ClearAllData( void );
	bool                            GetBool( void );
	char                            GetChar( void );
	int                             GetInt( void );
	long                            GetLong( void );
	short                           GetShort( void );
	unsigned                        GetUnsigned( void );
	unsigned long                   GetUnsignedLong( void );
	unsigned short                  GetUnsignedShort( void );
	float                           GetFloat( void );
	double                          GetDouble( void );
	int                             GetString( char *buff, int buffSize );
	unsigned                        GetFlag( void );
	void                            GetMatrix( NxMat34 &matrix );
	void                            GetVec3( NxVec3 &v );
	void                            GetQuat( NxQuat &q );
	bool                            GetBodyDesc( NxBodyDesc &b );
	NxShapeType                     GetShapeType( void );
	void                            GetShapeDesc( NxShapeDesc &desc );
	void                            GetSphereShapeDesc(	NxSphereShapeDesc &desc ); 
	void                            GetBoxShapeDesc( NxBoxShapeDesc &desc );
	void                            GetCapsuleShapeDesc( NxCapsuleShapeDesc &desc );
	void                            GetConvexShapeDesc(	NxConvexShapeDesc &desc );
	void                            GetTriangleMeshShapeDesc( NxTriangleMeshShapeDesc &desc );
#if NX_SDK_VERSION_NUMBER >= 240
	void							GetHeightFieldShapeDesc( NxHeightFieldShapeDesc &desc );
	void							GetHeightFieldDesc( HeightFieldData *hfd, int indexToCheck );
#endif
	void                            GetTriangleMeshDesc( TriangleMeshData *tmd, int indexToCheck );
	void                            GetConvexMeshDesc( ConvexMeshData *cmd, int indexToCheck	);
	void                            GetPlaneShapeDesc( NxPlaneShapeDesc &desc );
	void                            GetActorDesc( NxActorDesc *nad );
	NxShapeDesc                    *GetActorShape( void );
	void                            GetJointDesc( JointDescription &d );
	void                            GetPrismaticJointDesc( JointDescription &d );
	void                            GetRevoluteJointDesc( JointDescription &d );
	void                            GetCylindricalJointDesc( JointDescription &d );
	void                            GetSphericalJointDesc( JointDescription &d );
	void                            GetPointOnLineJointDesc( JointDescription &d );
	void                            GetPointInPlaneJointDesc( JointDescription &d );
	void                            GetDistanceJointDesc( JointDescription &d );
	void                            GetPulleyJointDesc(	JointDescription &d );
	void                            GetFixedJointDesc( JointDescription &d );
	void                            GetJointLimitSoftDesc( NxJointLimitSoftDesc &l );
	void                            GetJointDriveDesc( NxJointDriveDesc &d );
	void                            GetD6JointDesc(	JointDescription &d );
	JointDescription               *GetJoint( int whichJoint );
	void                            GetScene( CoreScene *scene, int whichScene );
	
	// private member variables
	NxReal							mParameters[NX_PARAMS_NUM_VALUES];
	NxArray< ConvexMeshData	* >		mConvexMeshes;
	NxArray< TriangleMeshData * >	mTriangleMeshes;
	NxArray< HeightFieldData * >	mHeightFields;
	NxArray< CoreScene * >			mScenes;

	NxPhysicsSDK				   *mPhysicsSDK;
	CoreUserNotify				   *mCallback;

	CharacterArray					mCommands;
	FILE                           *mFp;

	static CharacterArray			mConsistentStrings;
};

//==================================================================================
inline void CoreContainer::SetParam( unsigned which, float paramValue )
{
	if ( which < NX_PARAMS_NUM_VALUES )
	{
		mParameters[which] = paramValue;
	}
}

//==================================================================================
inline void CoreContainer::AddTMD( TriangleMeshData *tmd )
{
	if ( tmd )
	{
		mTriangleMeshes.push_back( tmd );
	}
}

//==================================================================================
inline void CoreContainer::AddCMD( ConvexMeshData *cmd )
{
	if ( cmd )
	{
		mConvexMeshes.push_back( cmd );
	}
}

//==================================================================================
inline void CoreContainer::AddHFD( HeightFieldData *hfd )
{
	if ( hfd )
	{
		mHeightFields.push_back( hfd );
	}
}

//==================================================================================
inline void CoreContainer::AddCoreScene( CoreScene *cs )
{
	if ( cs )
	{
		mScenes.push_back( cs );
	}
}

//==================================================================================
inline CharacterArray & CoreContainer::GetPsCommands( void )
{
	return mCommands;
}

#endif

#ifndef SOFTBODY_H

#define SOFTBODY_H

#include <NxPhysics.h>
#include <NxScene.h>

class NxSoftBody;
class NxTetraInterface;
class NxTetraMesh;
class NxDebugRenderable;

#include "NXU_helper.h"
#include "TetraGraphics.h"

namespace SOFTBODY
{

class SoftBody;
class TetraD3D;
class TetraModel;
class SkinnedMeshInstance;
class SkinnedMesh;
class NxMouseDrag;

// support for passing scripted commands to the soft body system for real-time tweakables.
enum SoftBodyCommand
{
	SBC_VOLUME_STIFFNESS,
	SBC_STRETCHING_STIFFNESS,
	SBC_DAMPING_COEFFICIENT,
	SBC_FRICTION,
	SBC_PARTICLE_RADIUS,
	SBC_SOLVER_ITERATIONS,
	SBC_STATIC,
	SBC_DISABLE_COLLISION,
	SBC_SELFCOLLISION,
	SBC_VISUALIZATION,
	SBC_GRAVITY,
	SBC_VOLUME_CONSERVATION,
	SBC_DAMPING,
	SBC_COLLISION_TWOWAY,
	SBC_TEARABLE,
  SBC_HARDWARE,
	SBC_COMDAMPING,
	SBC_FLUID_COLLISION,
  SBC_CORE_DUMP_XML,
  SBC_CORE_DUMP_DAE,
  SBC_CORE_DUMP_NXB,

// for editing tetrahedral meshes
  SBC_RESET_SCENE,
  SBC_IMPORT,
  SBC_IMPORT_OBJ,
  SBC_IMPORT_PSK,
  SBC_IMPORT_EZM,
  SBC_IMPORT_XML,
  SBC_IMPORT_COLLADA,
  SBC_IMPORT_NXB,
  SBC_EXPORT_OBJ,
  SBC_EXPORT_EZM,
  SBC_EXPORT_XML,
  SBC_EXPORT_SURFACE,
  SBC_COPY_SURFACE,
  SBC_ISO_SURFACE,
  SBC_GENERATE_VOLUME,
  SBC_SUBDIVISION_LEVEL,
  SBC_MESH_DETAIL,
  SBC_SOFTBODY,
  SBC_ATTACH_SOFTBODY,
  SBC_NEW_SOFTBODY,
  SBC_SIMULATE_SOFTBODY,
  SBC_SHOW_TETRAHEDRA,
  SBC_SHOW_OVERLAY,
  SBC_SHOW_GRAPHICS_MESH,
  SBC_SHOW_BACKFACES,
  SBC_RAYCAST_OK,
  SBC_PAUSE_SIMULATION,
  SBC_DEBUG_VISUALIZATION,
  SBC_ISO_SINGLE,
  SBC_STOP_SIMULATION,
	SBC_LAST
};

class SoftBodySystem : public NXU_userNotify
{
public:

  SoftBodySystem(NxScene *scene);
  ~SoftBodySystem(void);

	 int          processCommand(SoftBodyCommand sbc,int argc,const char **argv);

   void         setSoftFileInterface(SoftFileInterface *iface);
 	 SoftFileInterface * getSoftFileInterface(void) const;

   SoftBody *   createSoftBody(const char *fname,const NxMat34 *globalPose,const char *nameId);
   bool         attachSoftBody(const char *softbodyName,const char *actorName); // attach this actor to this softbody.

   SoftBody *   createSoftBody(TetraModel *tm,const NxMat34 *globalPose);

   SoftBody *   createSoftBody(NxSoftBodyDesc &desc,const char *userProperties);

   NxSoftBody * getNxSoftBody(SoftBody *body);

   bool         releaseSoftBody(SoftBody *body);
   void         release(bool sdk); // release all soft bodies

   void         setDevice(void *d3device,void *hwnd); // set the d3d device
   void         onDeviceReset(void *d3device);
   void         onLostDevice(void);

   void         render(const void *view,const void *projection,bool drawGrid,float dtime); // render all of the soft bodies, if SDK is true, then release the meshes as well.


   void         setScene(NxScene *scene);

   TetraModel * locateTetraModel(const char *obj,const char *tet);

   TetraGraphicsInterface *getTetraGraphicsInterface(void);

   void setTetraMaker(NxTetraInterface *t) { mTetraMaker = t; };

   void logMessage(const char *fmt,...);

   void releaseSoftBodies(TetraModel *tm); // release all soft bodies that use this tetramodel.  Only releases the

   void clearEditing(void); // clear editing mode.

   bool trackMouse(int screenX,
                   int screenY,
                   bool lbutton,
                   bool rbutton,
                   bool lshift,
                   bool rshift,
                   bool dragOk); // cast a ray into the soft body that is being edited for highlighting and selection.

	 bool  processMouseWheel(int delta); // returns false if it wasn't snarfed.

   bool intersectBound(const NxBounds3 &b,const NxVec3 &p1,const NxVec3 &p2); // does this line segment intersect this bounding volume?

   void	  NXU_notifySoftBody(NxSoftBody	*softBody,	const	char *userProperties);
   void 	NXU_notifySoftBodyMesh(NxSoftBodyMesh *t,const char *userProperties);
   bool	  NXU_preNotifySoftBody(NxSoftBodyDesc &softBody, const char	*userProperties);
   bool 	NXU_preNotifySoftBodyMesh(NxSoftBodyMeshDesc &t,const char *userProperties);
   void	  NXU_notifySoftBodyFailed(NxSoftBodyDesc &softBody, const char	*userProperties);
   void 	NXU_notifySoftBodyMeshFailed(NxSoftBodyMeshDesc &t,const char *userProperties);

   void   releaseSoftBody(NxSoftBody *sb);

   TetraModel *locateTetraModel(NxSoftBodyMesh *mesh);
   TetraModel *getEditModel(void);

	 void loadNxuStream(const char *fname,const NxMat34 *globalPose);

	 void copySurface(TetraModel *tm);
	 void copyIsoSurface(TetraModel *tm);
	 void createTetrahedra(TetraModel *tm);
   void saveNxuStream(TetraModel *tm);

   bool getRaycastOk(void) const { return mRaycastOk; };

	 SkinnedMeshInstance * createSkinnedMeshInstance(const char *fname,const NxMat34 *rootNode);
	 SkinnedMesh *locateSkinnedMesh(const char *name);

	 void setWorld(const void *world);

	 bool isPaused(void) const { return mPaused; };
	 void setPaused(bool s) { mPaused = s; };

   void getCenter(float *center) const;

	 const char *getImportName(NxBounds3 &b); // return the name of the last file imported and its bounding volume.

 	NxActor *    locateActor(const char *_name); // convenience function, find actor by name.
  NxSoftBody * locateSoftBody(const char *name); // convenience function, find softbody by name.

  void         coreDump(const char *fname,SoftBodyCommand mode); // if fname is null, a name will be auto-generated.

  const NxBounds3& getBounds(void) const { return mBounds; };

  void setShowTetrahedra(bool state);
  bool hasShowTetrahedra(void) const { return mShowTetrahedra; };

	void swapBuffers(void); // swap the write buffers for all softbody data.

	bool isActiveState(void) const { return mActiveState; };
	void setActiveState(bool state) { mActiveState = state; };

private:


  void drawGrid(void);

  void rebuildSoftBodyMesh(TetraModel &tm);
  void renderData(const NxDebugRenderable &data);
	NxSoftBodyMesh * createSoftBodyMeshes(NxSoftBodyMeshDesc &sd,bool hardware);

  SoftBody             *mNotify;
	SoftBody             *mEdit;
  NxScene              *mScene;
  TetraD3D             *mTetraD3D; // the direct3d rendering context
  NxArray< SoftBody * >      mSoftBodies; // all of the softbodies we have created so far.
  NxArray< TetraModel *>     mTetraModels; // collection of models so far.
  NxArray< SkinnedMeshInstance *>   mSkinnedSoftBodies;
  NxArray< SkinnedMesh * > mSkinnedMeshs;

//*** Used for dynamic editing of tetrahedral meshes
  NxTetraInterface        *mTetraMaker;           // the interface to the TetraMaker DLL plug-in.

  NxTetraMesh             *mSourceMesh;      // the raw source mesh (no duplicate positions)
  NxTetraMesh             *mSurfaceMesh;     // the currently generated source mesh.
  NxTetraMesh             *mTetraMesh;       // The tetrahedral mesh generated.

  NxU32                    mSubdivisionLevel;
  NxReal                   mDetailLevel;
  bool                     mShowTetrahedra;
  bool                     mShowOverlay;
  bool                     mShowGraphicsMesh;
  int                      mLastX;
  int                      mLastY;
  NxU32                    mHitIndex; // the tetrahedron that has been currently selected with the mouse
  NxVec3                   mCenter;
  float                    mRadius;
  NxVec3                   mRayDir; // world ray direction this frame
  NxVec3                   mLastRayDir; // ray direction the last frame.
  NxArray<NxU8>            mDeletions;
#if NX_USE_SOFTBODY_API
  NxSoftBodyDesc           mSoftBodyDesc;
#endif
  bool                     mRaycastOk;
  char                     mLastFileName[512];
  float                    mWorld[16];
  bool                     mPaused;
  bool                     mResetScene;
  bool                     mLastLeftButton;
  bool                     mLastRightButton;
  int                      mMouseX;
  int                      mMouseY;
  float                    mXrot;
  float                    mYrot;
  NxMouseDrag             *mMouseDrag;
  float                    mViewMatrix[16];
  float                    mProjectionMatrix[16];
  float                    mDtime;
  bool                     mDebugVisualization;
  bool                     mIsoSingle;
  NxU32                    mLastEditCount;
  NxU32                    mEditCount;
  NxBounds3                mBounds;
  bool                     mActiveState;
  bool                     mHardwareOk;
};

const char *stristr(const char *str,const char *scan);

}; // END OF SOFTBODY NAMESPACE


extern SOFTBODY::SoftBodySystem *gSoftBodySystem;

#endif

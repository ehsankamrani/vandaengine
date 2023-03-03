#ifndef NX_EXTENSIONS_H

#define NX_EXTENSIONS_H

#ifdef _USRDLL
	#define NXEXTENSIONSDLL_API __declspec(dllexport)
#elif defined NX_USE_SDK_STATICLIBS
	#define NXEXTENSIONSDLL_API
#else
	#define NXEXTENSIONSDLL_API __declspec(dllimport)
#endif


#ifndef NX_SDK_VERSION_MAJOR
#include <NxVersionNumber.h>
#include <NxPhysics.h>
#endif

class NxPhysicsSDK;

#if NX_SDK_VERSION_NUMBER >= 220
class NxConvexMeshDesc;
#endif

class NxTriangleMeshDesc;
class NxJoint;
class NxActor;
class NxVec3;
class NxQuat;
class NxScene;
class NxUserDebugRenderer;
class NxUserAllocator;
class NxUserErrorStream;

//
class NxAsset;

namespace EXTERNAL_UTILS
{
class ODF_Shape;
class ODF_Container;
class ODF_RigidBody;
class ODF_JointInstance;
class OdfLoaderInterface;
class ODF_ConvexHull;
class ODF_TriangleMesh;
class ODF_PhysicsModelInstance;
class FileStream;
};

enum NxSystemTestResult
{
	NX_STR_KEYPRESS,            // send a keypress to the application.
	NX_STR_CONTINUE,            // continue running the application, but don't step the simulation.
	NX_STR_EXIT,                // exit the application
	NX_STR_APP_STEP,            // continue running and let the application step physics.
	NX_STR_COMMAND,             // received data over telnet we don't know how to process.  Returning it back to the application in case it wants it.
	NX_STR_RESET,               // request to reset the physics SDK
	NX_STR_LOAD,                // request to load a data asset.
};


class NxSystemTestRequest
{
public:
	NxSystemTestRequest(void)
	{
		mClient = 0;
		mIvalue = 0;
		mCommand = 0;
	}
	int         mClient;
	int         mIvalue; // processo
	const char *mCommand;
};



class NxUserInstanceNotify  // Interface to notify application as assets are loaded.
{
public:


	virtual bool InstanceNotifyJoint(NxJoint *joint,const char *name,const char *settings,EXTERNAL_UTILS::ODF_JointInstance *odf) = 0;
	virtual bool InstanceNotifyActor(NxActor *actor,const char *name,const char *settings,const char *meshname,EXTERNAL_UTILS::ODF_RigidBody *odf) = 0;
	virtual bool InstanceCommand(int argc,const char **argv,const char *command) = 0; // notify application of a script command to process.
	virtual bool InstanceNotifyModel(const char *name,const char *usersettings,const float *pos,const float *quat,EXTERNAL_UTILS::ODF_PhysicsModelInstance *pmi) = 0; // notify application that a model is about to be instanced!
  virtual bool InstanceNotifyShape(const char *name,const char *usersettings,EXTERNAL_UTILS::ODF_Shape *shape) = 0; // notify that a unique shape has been formed, give the application a chance to fill the display mesh pointer.

};


class NxExtensions
{
public:
  virtual NxAsset *          NxLoadAsset(const char *fname) =0;    // load an asset with this filename. TODO, abstract stream interface..
  virtual bool               NxReleaseAsset(NxAsset *asset) =0;    // release previously loaded asset.
  virtual bool               NxInstanceAsset(NxPhysicsSDK *sdk,NxScene *scene,NxAsset *asset,NxUserInstanceNotify *callback,const char *modelname=0,const NxVec3 *position=0,const NxQuat *quat=0) =0;
  virtual bool               NxInstanceAsset(NxPhysicsSDK *sdk,NxScene *scene,EXTERNAL_UTILS::ODF_Container *asset,NxUserInstanceNotify *callback,const char *modelname=0,const NxVec3 *position=0,const NxQuat *quat=0) =0;
  virtual EXTERNAL_UTILS::OdfLoaderInterface *  NxCreateLoaderInterface(NxUserInstanceNotify *notify,NxPhysicsSDK *sdk,NxScene *scene) =0;
  virtual bool               NxReleaseLoaderInterface(EXTERNAL_UTILS::OdfLoaderInterface *iface) =0;
  virtual bool               NxSaveAsset(NxAsset *asset,const char *dest_name,bool binary_precision,const char *addendum) =0;
  virtual bool               NxCook(EXTERNAL_UTILS::ODF_Container *container) =0; // cook the contents of this ODF container.
  virtual bool               NxReleaseCooked(EXTERNAL_UTILS::ODF_Container *container) =0;
  virtual bool               NxCook(EXTERNAL_UTILS::ODF_TriangleMesh *mesh) = 0;
  virtual bool               NxCook(EXTERNAL_UTILS::ODF_ConvexHull   *hull) =0;


  virtual EXTERNAL_UTILS::ODF_Container * NxGetCoreDump(NxPhysicsSDK *sdk) =0;
  virtual bool               NxSaveCoreDump(NxPhysicsSDK *sdk,const char *fname,bool binary,const char *addendum) =0;

  #if NX_SDK_VERSION_NUMBER >= 220
  virtual bool               NxCreateConvexHull(const NxConvexMeshDesc &source,NxConvexMeshDesc &dest,float skinwidth=0) =0; // create faces from point cloud.
  virtual bool               NxCreateConvexHullBox(const NxConvexMeshDesc &source,NxConvexMeshDesc &dest,float skinwidth=0)=0; // just create a box around the point cloud
  virtual bool               NxReleaseConvexHullMemory(const NxConvexMeshDesc &dest)=0;
  virtual NxConvexMesh *     NxCreateConvexMesh(NxPhysicsSDK *sdk,const NxConvexMeshDesc &source,float skinwidth=0)=0;
  virtual NxTriangleMesh *   NxCreateTriangleMesh(NxPhysicsSDK *sdk,const NxTriangleMeshDesc &source)=0;
  #else
  virtual bool               NxCreateConvexHull(const NxTriangleMeshDesc &source,NxTriangleMeshDesc &dest, float skinwidth)=0;  // create faces from point cloud.
  #endif

  virtual void               NxSetSystemTest(bool state)=0; // enable or disable by default.
  virtual NxSystemTestResult NxProcessSystemTest(NxPhysicsSDK *sdk,NxSystemTestRequest &request)=0; // process system test requests. If 'true' then exit the application.
  virtual NxSystemTestResult NxProcessSystemTest(NxPhysicsSDK *sdk,NxSystemTestRequest &request,const char *command)=0;
  virtual void               NxSendMessage(int client,const char *msg)=0; // just send a message over telnet.
  virtual void               NxCloseSystemTest(void)=0; // close the system test connection.

  virtual void               NxExtensionsCheckMemory(const char *label)=0;

	virtual void               Release(void) = 0; // release the NxExtensions library
};


NXEXTENSIONSDLL_API NxExtensions *GetNxExtensions(NxUserAllocator *allocator,NxUserOutputStream *stream,EXTERNAL_UTILS::FileStream *fstream); // return the NxExtensions interface.

#endif

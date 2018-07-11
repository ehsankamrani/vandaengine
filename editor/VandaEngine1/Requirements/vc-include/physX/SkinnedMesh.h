#ifndef SKINNED_MESH_H

#define SKINNED_MESH_H

class NxMat34;
class NxScene;
class NxPhysicsSDK;
class NxShape;
// Creates the illusion of a soft body simulation by mapping a deformable mesh to a set of constrained rigid bodies.
// Can also be used for ragdoll graphics.

namespace NXU
{

class NxuPhysicsCollection;

};

namespace SOFTBODY
{

class SkinnedMeshInstance;
class SkinnedMesh;
class SoftMeshSystem;

SkinnedMesh *sm_CreateSkinnedMesh(const char *fname);

SkinnedMeshInstance  *sm_CreateSkinnedMeshInstance(SkinnedMesh *model,NxScene *scene,const NxMat34 *rootNode);

void           sm_ReleaseSkinnedMeshInstance(SkinnedMeshInstance *fb);
void           sm_ReleaseSkinnedMesh(SkinnedMesh *fm);
void           sm_RenderSkinnedMeshInstance(SkinnedMeshInstance *fb);
bool           sm_MatchSkinnedMesh(const SkinnedMesh *model,const char *name); // true if these are the same names.
void           sm_onDeviceReset(SkinnedMesh *fsm,void *device);
SoftMeshSystem *  sm_locateRenderContext(NxShape *shape); // builds a rendering context for a shape of this type.

};


#endif

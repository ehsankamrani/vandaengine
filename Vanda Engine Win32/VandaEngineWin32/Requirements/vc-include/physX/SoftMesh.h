#ifndef SOFT_MESH_H

#define SOFT_MESH_H

class NxShape;

namespace NXU
{
class NxuSkeleton;
};

namespace SOFTBODY
{

class SoftMeshSystem;

SoftMeshSystem *   createSoftMeshSystem(const char *fname,NXU::NxuSkeleton *skeleton);
void               releaseSoftMeshSystem(SoftMeshSystem *smesh);
void               renderSoftMeshSystem(SoftMeshSystem *smesh,const float **transforms); // multiple transforms
void               renderSoftMeshSystem(SoftMeshSystem *smesh,const float *transform); // single transform
NXU::NxuSkeleton * getSkeleton(SoftMeshSystem *smesh); // return a pointer to the graphics skeleton if there is one.
void               onDeviceReset(SoftMeshSystem *smesh,void *device);    // device reset for an individual mesh.
void               sm_onDeviceReset(void *device); // reset all mesh systems

SoftMeshSystem *   locateSoftMeshSystem(const char *fname);
void               releaseSoftMeshSystems(void); // release all mesh systems.

// algorithmically generates a rendering context for these primitives.
SoftMeshSystem *   locateBox(const char *shader,const float *sides); // return a mesh asset for a box of this size.
SoftMeshSystem *   locatePlane(const char *shader,const float *plane); // return a mesh asset for a box of this size.
SoftMeshSystem *   locateSphere(const char *shader,float radius);
SoftMeshSystem *   locateCapsule(const char *shader,float radius,float height);
SoftMeshSystem *   locateTriangleMesh(const char *name,const char *shader,unsigned int vcount,const float *verts,unsigned int tcount,const unsigned int *indices);
SoftMeshSystem *   locateRenderContext(NxShape *shape); // builds a rendering context for a shape of this type.

};

#endif

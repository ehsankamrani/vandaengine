#ifndef SOFT_VERTEX_H

#define SOFT_VERTEX_H

namespace SOFTBODY
{

enum SoftVertexType
{
	SVT_TETRA_VERTEX,
	SVT_TETRA_POSITION_VERTEX,
	SVT_TETRA_DEFORM_VERTEX,
	SVT_TETRA_GRAPHICS_VERTEX,
};

class SoftVertexPool;

SoftVertexPool *createSoftVertexPool(SoftVertexType type);
bool            releaseSoftVertexPool(SoftVertexPool *vpool);
unsigned int    getSoftVertexIndex(SoftVertexPool *vpool,const void *vertex);
void *          getSoftVertexPoolBuffer(SoftVertexPool *vpool,unsigned int &vcount);


}; // END OF SOFTBODY NAMESPACE

#endif

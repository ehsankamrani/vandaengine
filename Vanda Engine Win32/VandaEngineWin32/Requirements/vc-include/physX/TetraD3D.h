#ifndef TETRA_D3D_H

#define TETRA_D3D_H

// Implements the ability to render soft body tetrahedral meshes via a Direct3D interface.

#include "TetraGraphics.h"

namespace SOFTBODY
{

class DirectHelper;

class TetraD3D : public TetraGraphicsInterface
{
public:
  TetraD3D(void);
  ~TetraD3D(void);

  void   setDevice(void *d3device,void *hwnd);
  void   onDeviceReset(void *d3device);
  void   setWireFrame(bool state);
  void	 setShowBackfaces(bool state);

	void   setViewProjectionMatrix(const void *view,const void *projection);
  void   setWorldMatrix(const void *world);

  bool   releaseMaterial(TetraMaterial *tm); // releases device handle for this material if one is present

  void * createVertexBuffer(unsigned int vcount,const TetraGraphicsVertex *vertices);
  bool   releaseVertexBuffer(void *buffer);
  void * lockVertexBuffer(void *buffer);
  bool   unlockVertexBuffer(void *buffer);

  void * createIndexBuffer(unsigned int icount,const unsigned int *indices);
  bool   releaseIndexBuffer(void *ibuffer);
  void * lockIndexBuffer(void *buffer);
  bool   unlockIndexBuffer(void *buffer);


  bool   renderSection(TetraMaterial *material,void *buffer,void *ibufferm,unsigned int vcount,unsigned int tcount);
  bool   renderSection(TetraMaterial *material,void *vbuffer,unsigned int vcount);

  // render using UP data.
  bool   renderSection(TetraMaterial *material,TetraGraphicsVertex *vbuffer,unsigned int *ibuffer,unsigned int vcount,unsigned int tcount);
  bool   renderSection(TetraMaterial *material,TetraGraphicsVertex *vbuffer,unsigned int vcount);

  void   addLine(unsigned int color,const float *p1,const float *p2);
  void   flushLines(void);

  bool   screenToWorld(int sx,      // screen x position
                       int sy,      // screen y position
                       float *world, // world position of the eye
                       float *direction); // direction vector into the world

  void   getEyePos(float *eye);

  virtual void   wireBox(unsigned int color,const float *bmin,const float *bmax);

private:
  DirectHelper	*mDirect;  // use the pimple pattern to avoid littering the public header with DirectX crap

};

}; // END OF SOFTBODY NAMESPACE

#endif

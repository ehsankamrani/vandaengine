#ifndef BILLBOARDSRENDER_H
#define BILLBOARDSRENDER_H

#include <stdio.h>
#include <vector>
#include <algorithm>

#include "GL/glut.h"
#include "NxFoundation.h"
#include "tga.h"

typedef	struct									
{
	GLubyte	* imageData;									// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
	GLuint	type;											// Image Type (GL_RGB, GL_RGBA)
} TGATexture;	

typedef struct
{
	GLubyte Header[12];										// TGA File Header
} TGAHeader;


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

bool LoadUncompressedTGA(TGATexture *, char *, FILE *);	// Load an Uncompressed file
bool LoadCompressedTGA(TGATexture *, char *, FILE *);		// Load a Compressed file

//Depthpos and DepthposSort used for Sorting of the billboards
class Depthpos {
public:
  float depth;
  float * ptrpos;	//pointer to particle position array
};

class DepthposSort {
public:
	bool operator()(const Depthpos &a,const Depthpos &b) const
  {
     return a.depth > b.depth;
   }
};

typedef std::vector<Depthpos> DepthposVec;

typedef struct {
	float x;
	float y;
	float z;
} float3;

class BillboardsRender {
public:
	BillboardsRender(int maxParticles);	//Maximum Number of Particles
	~BillboardsRender();
	
	void Init();

	void CreateBillboardsQuads(NxVec3 eye, NxVec3 facing);
	void Render();
	void DummyRender();
	void PrintoutBillboardsVertices(int count);


	//Vertex arrays
	float * ParticleVertices;			//The ParticleVertices are stored here
	const int maxParticleVertices;		//Array size
	int numParticles;					//Number of particles
	float scale;						//Scaling of billboards Quads

private:
	float * BillboardsTexelCoords;
	float * BillboardsVertices;			//The BillboardVertices are stored here

	TGATexture * tgatexture;
	GLuint textureID;					//ID to access texture
	GLuint * texturePtr;				//pointer to texture data
	int texsize;						//height and width of texture

};

#endif //BILLBOARDSRENDER_H

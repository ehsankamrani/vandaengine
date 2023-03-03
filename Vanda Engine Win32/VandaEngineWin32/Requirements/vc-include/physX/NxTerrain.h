// An NVIDIA PhysX demo application, using debug visualization and joints
// by Simon Schirm, terrain code nagged from Pierre Terdiman's SampleTerrain

#ifdef __PPCGEKKO__
#define TERRAIN_SIZE    55
#else
#define TERRAIN_SIZE    65 //129
#endif
#define TERRAIN_NB_VERTS  TERRAIN_SIZE*TERRAIN_SIZE
#define TERRAIN_NB_FACES  (TERRAIN_SIZE-1)*(TERRAIN_SIZE-1)*2
#define TERRAIN_OFFSET    -50.0f
#define TERRAIN_WIDTH   10.0f
#define TERRAIN_CHAOS   40.0f

static NxVec3* gTerrainVerts = NULL;
static NxVec3* gTerrainNormals = NULL;
static NxU32* gTerrainFaces = NULL;
static NxActor* gTerrain = NULL;

#define TEST_COOKING
#include "cooking.h"
#include "Stream.h"
#include "CustomRandom.h"

float trand()
{
	static Random random;
	return ((float)random.rand()/((float)random.rand_max+1))*(2.0f) -1.0f;
}

static void InitTerrain(NxPhysicsSDK& physicsSDK, NxScene& scene)
{
  // Initialize terrain vertices
  gTerrainVerts = new NxVec3[TERRAIN_NB_VERTS];
  for(NxU32 y=0;y<TERRAIN_SIZE;y++)
  {
    for(NxU32 x=0;x<TERRAIN_SIZE;x++)
    {
      gTerrainVerts[x+y*TERRAIN_SIZE] = NxVec3(NxF32(x)-(NxF32(TERRAIN_SIZE-1)*0.5f), 0.0f, NxF32(y)-(NxF32(TERRAIN_SIZE-1)*0.5f)) * TERRAIN_WIDTH;
    }
  }

  // Initialize terrain faces
  gTerrainFaces = new NxU32[TERRAIN_NB_FACES*3];
  NxU32 k = 0;
  for(NxU32 j=0;j<TERRAIN_SIZE-1;j++)
  {
    for(NxU32 i=0;i<TERRAIN_SIZE-1;i++)
    {
      // Create first triangle
      gTerrainFaces[k++] = i   + j*TERRAIN_SIZE;
      gTerrainFaces[k++] = i   + (j+1)*TERRAIN_SIZE;
      gTerrainFaces[k++] = i+1 + (j+1)*TERRAIN_SIZE;

      // Create second triangle
      gTerrainFaces[k++] = i   + j*TERRAIN_SIZE;
      gTerrainFaces[k++] = i+1 + (j+1)*TERRAIN_SIZE;
      gTerrainFaces[k++] = i+1 + j*TERRAIN_SIZE;
    }
  }

  struct Local
  {
    static void _Compute(bool* done, NxVec3* field, NxU32 x0, NxU32 y0, NxU32 size, NxF32 value)
    {
      // Compute new size
      size>>=1;
      if(!size) return;

		// Compute new heights
		float v0 = (value * trand());
		float v1 = (value * trand());
		float v2 = (value * trand());
		float v3 = (value * trand());
		float v4 = (value * trand());
 
      NxU32 x1 = (x0+size)    % TERRAIN_SIZE;
      NxU32 x2 = (x0+size+size) % TERRAIN_SIZE;
      NxU32 y1 = (y0+size)    % TERRAIN_SIZE;
      NxU32 y2 = (y0+size+size) % TERRAIN_SIZE;

      if(!done[x1 + y0*TERRAIN_SIZE]) field[x1 + y0*TERRAIN_SIZE].y = v0 + 0.5f * (field[x0 + y0*TERRAIN_SIZE].y + field[x2 + y0*TERRAIN_SIZE].y);
      if(!done[x0 + y1*TERRAIN_SIZE]) field[x0 + y1*TERRAIN_SIZE].y = v1 + 0.5f * (field[x0 + y0*TERRAIN_SIZE].y + field[x0 + y2*TERRAIN_SIZE].y);
      if(!done[x2 + y1*TERRAIN_SIZE]) field[x2 + y1*TERRAIN_SIZE].y = v2 + 0.5f * (field[x2 + y0*TERRAIN_SIZE].y + field[x2 + y2*TERRAIN_SIZE].y);
      if(!done[x1 + y2*TERRAIN_SIZE]) field[x1 + y2*TERRAIN_SIZE].y = v3 + 0.5f * (field[x0 + y2*TERRAIN_SIZE].y + field[x2 + y2*TERRAIN_SIZE].y);
      if(!done[x1 + y1*TERRAIN_SIZE]) field[x1 + y1*TERRAIN_SIZE].y = v4 + 0.5f * (field[x0 + y1*TERRAIN_SIZE].y + field[x2 + y1*TERRAIN_SIZE].y);

      done[x1 + y0*TERRAIN_SIZE] = true;
      done[x0 + y1*TERRAIN_SIZE] = true;
      done[x2 + y1*TERRAIN_SIZE] = true;
      done[x1 + y2*TERRAIN_SIZE] = true;
      done[x1 + y1*TERRAIN_SIZE] = true;

      // Recurse through 4 corners
      value *= 0.5f;
      _Compute(done, field, x0, y0, size, value);
      _Compute(done, field, x0, y1, size, value);
      _Compute(done, field, x1, y0, size, value);
      _Compute(done, field, x1, y1, size, value);
    }
  };

  // Fractalize
  bool* done = new bool[TERRAIN_NB_VERTS];
  memset(done, 0, TERRAIN_NB_VERTS*sizeof(bool));

  NxF32 initHeight = 10.0f;
  gTerrainVerts[0].y = initHeight;
  gTerrainVerts[TERRAIN_SIZE-1].y = initHeight;
  gTerrainVerts[TERRAIN_SIZE*(TERRAIN_SIZE-1)].y = initHeight;
  gTerrainVerts[TERRAIN_NB_VERTS-1].y = initHeight;
  Local::_Compute(done, gTerrainVerts, 0, 0, TERRAIN_SIZE, TERRAIN_CHAOS);

  for(int y=0;y<TERRAIN_SIZE;y++)
  {
    for(NxU32 x=0;x<TERRAIN_SIZE;x++)
    {
      gTerrainVerts[x+y*TERRAIN_SIZE].y = gTerrainVerts[x+y*TERRAIN_SIZE].y + 15.0f*sinf(y*0.01f) + 15.0f*cosf(x*0.01f);
	  float vx = 2*(x-TERRAIN_SIZE*0.5f)/TERRAIN_SIZE;
	  float vy = 2*(y-TERRAIN_SIZE*0.5f)/TERRAIN_SIZE;
	  float vr = NxMath::min(1.0f, (vx*vx + vy*vy));
	  gTerrainVerts[x+y*TERRAIN_SIZE].y *= vr;
    }
  }
  for(NxU32 i=0;i<TERRAIN_NB_VERTS;i++) 
  {
    gTerrainVerts[i].y *= 1.5f;
    gTerrainVerts[i].y += TERRAIN_OFFSET;
  }
  for(int y=0;y<TERRAIN_SIZE;y++)
  {
	  gTerrainVerts[0+y*TERRAIN_SIZE].y -= 50;
	  gTerrainVerts[TERRAIN_SIZE-1+y*TERRAIN_SIZE].y -= 50;
  }
  for(NxU32 x=0;x<TERRAIN_SIZE;x++)
  {
	  gTerrainVerts[x+0].y -= 50;
	  gTerrainVerts[x + TERRAIN_SIZE * (TERRAIN_SIZE-1)].y -= 50;
  }
  
  delete[] done;

  // Build vertex normals
  gTerrainNormals = new NxVec3[TERRAIN_NB_VERTS];
  NxBuildSmoothNormals(TERRAIN_NB_FACES, TERRAIN_NB_VERTS, gTerrainVerts, gTerrainFaces, NULL, gTerrainNormals,true);

  // Build physical model
  NxTriangleMeshDesc terrainDesc;
  terrainDesc.numVertices         = TERRAIN_NB_VERTS;
  terrainDesc.numTriangles        = TERRAIN_NB_FACES;
  terrainDesc.pointStrideBytes      = sizeof(NxVec3);
  terrainDesc.triangleStrideBytes     = 3*sizeof(NxU32);
  terrainDesc.points            = gTerrainVerts;
  terrainDesc.triangles         = gTerrainFaces;              
  terrainDesc.flags           = 0;


  terrainDesc.heightFieldVerticalAxis   = NX_Y;
  terrainDesc.heightFieldVerticalExtent = -50;

  NxTriangleMeshShapeDesc terrainShapeDesc;

  // Cooking from memory
  NxInitCooking();
  MemoryWriteBuffer buf;
  bool status = NxCookTriangleMesh(terrainDesc, buf);
  MemoryReadBuffer readBuffer(buf.data);
  terrainShapeDesc.meshData = physicsSDK.createTriangleMesh(readBuffer);
  //
  // Please note about the created Triangle Mesh, user needs to release it when no one uses it to save memory. It can be detected
  // by API "meshData->getReferenceCount() == 0". And, the release API is "gPhysicsSDK->releaseTriangleMesh(*meshData);"
  //

  terrainShapeDesc.materialIndex = terrainMaterial;
  NxActorDesc ActorDesc;

  ActorDesc.shapes.pushBack(&terrainShapeDesc);
  gTerrain = scene.createActor(ActorDesc);
  gTerrain->userData = (void*)0;

  NxCloseCooking();

}

static void RenderTerrain()
{
  static float* pVertList = NULL;
  static float* pNormList = NULL;

  glEnable(GL_LIGHTING);

  if(pVertList == NULL && pNormList == NULL)
  {
    pVertList = new float[TERRAIN_NB_FACES*3*3];
    pNormList = new float[TERRAIN_NB_FACES*3*3];

    int vertIndex = 0;
    int normIndex = 0;
    for(int i=0;i<TERRAIN_NB_FACES;i++)
    {
      for(int j=0;j<3;j++)
      {
        pVertList[vertIndex++] = gTerrainVerts[gTerrainFaces[i*3+j]].x;
        pVertList[vertIndex++] = gTerrainVerts[gTerrainFaces[i*3+j]].y;
        pVertList[vertIndex++] = gTerrainVerts[gTerrainFaces[i*3+j]].z;

        pNormList[normIndex++] = gTerrainNormals[gTerrainFaces[i*3+j]].x;
        pNormList[normIndex++] = gTerrainNormals[gTerrainFaces[i*3+j]].y;
        pNormList[normIndex++] = gTerrainNormals[gTerrainFaces[i*3+j]].z;
      }
    }
  }

  if(pVertList != NULL && pNormList != NULL)
  {
    glColor4f(0.5f, 0.4f, 0.0f, 1.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
#ifdef __PPCGEKKO__
	glVertexPointer(3,GL_FLOAT, 0, TERRAIN_NB_FACES*3, pVertList);
    glNormalPointer(GL_FLOAT, 0, TERRAIN_NB_FACES*3, pNormList);
#else   
    glVertexPointer(3,GL_FLOAT, 0, pVertList);
    glNormalPointer(GL_FLOAT, 0, pNormList);
#endif    

    glDrawArrays(GL_TRIANGLES, 0, TERRAIN_NB_FACES*3);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

#ifdef __PPCGEKKO__
	glVertexPointer(3,GL_FLOAT, 0, TERRAIN_NB_FACES*3, pVertList);
    glNormalPointer(GL_FLOAT, 0, TERRAIN_NB_FACES*3, pNormList);
#else   
    glVertexPointer(3,GL_FLOAT, 0, pVertList);
    glNormalPointer(GL_FLOAT, 0, pNormList);
#endif

    glColor4f(0.4f, 0.3f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, TERRAIN_NB_FACES*3);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    
  }

}

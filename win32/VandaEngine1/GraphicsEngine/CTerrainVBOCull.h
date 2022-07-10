////////////////////////////////////////////////////////////////////////////
///	\File "CTerrainVBOCull.h"
//
///	Author: Brian Story
//
///	Creation Date: 5/26/2005
//
///	Purpose: Definition of the CTerrainVBOCull class.
////////////////////////////////////////////////////////////////////////////


//Modified work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license


#ifndef _CTERRAINVBOCULL_H_
#define _CTERRAINVBOCULL_H_

#include "OpenGL.h"
#include "CHeightClass.h"
#include "../Common/Utility.h"
#include "../Common/Defines.h"
#include "../physXEngine/nx.h"
class CInstanceLight;
///////////////////////////////////
//
///	Class CTerrainVBOCull
//
///	Created: 5/26/2005
///
///////////////////////////////////

class CTerrainVBOCull
{
	/////////////////////
	// Private Members //
	/////////////////////

	private:
		CVec3f* m_tangents;
		CVec3f* m_bNormals;

		
		GLuint bufferVertList;	// Vertex list.

		// The height and width of the heightmap mesh.
		int Width = 513;
		int Height = 513;

		// The height and width of a single chunk of the mesh.
		int ChunkWidth = 16;
		int ChunkHeight = 16;
		

		struct chunk
		{
			GLuint bufferTriList;		// Triangle index list for a chunk.
			float maxX, maxY, maxZ;		// Maximum vertex values in this chunk.
			float minX, minY, minZ;		// Minimum vertex values in this chunk.
			CVec3f max_t, min_t;		//transformed max and min
			CVec3f center;
			float radius;
			CBool m_calculateDistance;
			float m_distance_from_camera;
			NxActor* m_actor;

			CInstanceLight* m_lights[8];
			CUInt m_totalLights;
			CUInt m_totalVisibleLights;
			CBool m_lightCooked;

			std::vector<std::string>m_attachedActors; //PhysX actors attached to this chunk

			float GetDistanceFromCamera() { return m_distance_from_camera; }
			float GetRadius() { return radius; }
			NxActor* GetActor() { return m_actor; }
			CVoid SetActor(NxActor* actor) { m_actor = actor; }

			CBool GetLightCooked() { return m_lightCooked; }
			CVoid SetLightCooked(CBool set) { m_lightCooked = set; }

			CChar m_chunkName[MAX_NAME_SIZE];

			chunk()
			{
				m_calculateDistance = CTrue;
				m_actor = NULL;
				for (CUInt i = 0; i < 8; i++)
					m_lights[i] = NULL;
				m_lightCooked = CFalse;
			}
		};

		// A multidimentional array of mesh chunks.
		chunk **chunkArray;


		// Heightmap data (will come from the heightmap class).
		heightData **data;

		// Data offsets into the vert list.
		int vertOffset;
		int normalOffset;
		int colorOffset;
		int textureCoordOffset;
		int tangentOffset;
		int bitangentOffset;
		int lightmapTexCoordOffset;

		// The number of total triangles in the mesh.
		int numElements;

		//update min, max and center
		CBool m_updateMinMaxCenter;
		//////////////////////////////////////////////////////////
		///	Function: "buildBufferObjectVertexArrays"
		//
		///	FirstModified: 5/12/2005
		//
		///	\param None
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Creates the VBO's for the heightmap.
		//////////////////////////////////////////////////////////
		void buildBufferObjectVertexArrays(void);
		void CalculateTangentArray(CInt vertexCount, CInt triangleCount, CVec3f* meshVertices, CVec3f* meshTriangles, CVec3f* normals, CVec2f* texCoords);



	////////////////////
	// Public Members //
	////////////////////

	public:


	/////////////////
	// Constructor //
	/////////////////

		//////////////////////////////////////////////////////////
		///	Function: CTerrainVBOCull
		//
		///	FirstModified: 5/26/2005
		//
		///	\param	None
		//
		///	Output:	None
		//
		///	\return None
		//
		///	Purpose: Constructor for the class
		//////////////////////////////////////////////////////////
		CTerrainVBOCull(void)
		{
			m_tangents = NULL;
			m_bNormals = NULL;

			// Initialize our variables.
			data = NULL;
			bufferVertList = 0;

			vertOffset   = 0;
			normalOffset = 0;
			colorOffset  = 0;
			textureCoordOffset = 0;
			tangentOffset = 0;
			bitangentOffset = 0;
			lightmapTexCoordOffset = 0;

			numElements = 0;

			m_updateMinMaxCenter = CTrue;

			// Create the chunk array and initialize it's values.
			chunkArray = new chunk*[Width/(ChunkWidth-1)];
			for (int x = 0; x < Width/(ChunkWidth-1); x++)
			{
				chunkArray[x] = new chunk[Height/(ChunkHeight-1)];
			}

			for (int z = 0; z < Height/(ChunkHeight-1); z++)
			{
				for (int x = 0; x < Width/(ChunkWidth-1); x++)
				{
					chunkArray[x][z].bufferTriList = 0;
				}
			}
		}


	////////////////
	// Destructor //
	////////////////

		//////////////////////////////////////////////////////////
		///	Function: ~CTerrainVBOCull
		//
		///	FirstModified: 5/26/2005
		//
		///	\param	None
		//
		///	Output:	None
		//
		///	\return None
		//
		///	Purpose: Destructor for the class
		//////////////////////////////////////////////////////////
		virtual ~CTerrainVBOCull(void)
		{
			releaseVBO();

			if (chunkArray)
			{
				for (int x = 0; x < Width / (ChunkWidth-1); x++)
					delete [] chunkArray[x];

				delete [] chunkArray;
			}
			CDeleteData(m_tangents);
			CDeleteData(m_bNormals);
		}


		//////////////////////////////////////////////////////////
		///	Function: "init"
		//
		///	FirstModified: 5/26/2005
		//
		///	\param heightData ***heights	The height data for the mesh.	
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Initializes the class and provides the heightmap data.
		//////////////////////////////////////////////////////////
		void init(heightData ***heights)
		{
			// Keep a copy of the heightmap data for ourselves.
			data = *heights;

			// Build the buffer objects.
			buildBufferObjectVertexArrays();
		}

		void releaseVBO()
		{
			glDeleteBuffers(1, &bufferVertList);
			bufferVertList = 0;

			for (int chunkZ = 0; chunkZ < int((float)(Height) / (float)(ChunkHeight - 1)); chunkZ++)
			{
				for (int chunkX = 0; chunkX < (int)((float)(Width) / (float)(ChunkWidth - 1)); chunkX++)
				{
					glDeleteBuffers(1, &chunkArray[chunkX][chunkZ].bufferTriList);
				}
			}
		}

		void SetUpdate(bool set) { m_updateMinMaxCenter = set; }
		//////////////////////////////////////////////////////////
		///	Function: "drawBufferObjectVertexArrays"
		//
		///	FirstModified: 5/12/2005
		//
		///	\param bool boundingBox		True if the bounding boxes are to be displayed.
		//
		///	Output: None
		//
		///	\return None
		//
		///	Purpose: Draws the VBO's for the heightmap.
		//////////////////////////////////////////////////////////
		void draw();

		void resetPhysXActors();
		//draw chunks for dynamic shadow here
		void drawShadow();

		//Set all lights affecting the terrain
		void SetLight(CVec3f min, CVec3f max, chunk* chunkArray);
		void SetLightCooked(CBool cook);
		//Check to see if point or spot light intersect each chunk of the terrain
		CBool DoesLightIntersectsChunk(CVec3f C1, CVec3f C2, CVec3f S, CFloat R);

		inline CFloat squared(CFloat v) { return v * v; }

		//Calculate the distance of each individual chunk from camera
		void calculateDistance(CVec3f center1, CVec3f center2, CFloat & distance);

		CVoid ManagePhysics();

		CVoid ManagePhysXTriangleActorForCharacterController(CInt x, CInt z);
		CVoid ManagePhysXTriangleActorsForPrefabInstance(CInt x, CInt z);

		CVoid DrawBoundingBox();
};

#endif
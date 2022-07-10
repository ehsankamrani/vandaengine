#ifndef _SG_MESH_H__
#define _SG_MESH_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/


#include <string>
#include <vector>
#include <3DMath.h>

struct GLMmodel;
struct GLMgroup;

namespace SceneGraph
	{
	
	class SubMesh
		{
		public:
		SubMesh()
			{
			vertexList = 0;
			indexList = 0;
			nVertices = 0;
			nTriangles = 0;
			displayList = 0;
			userData = 0;
			}
		~SubMesh();
		void changed();
		void render();
		void renderAsPoints(float size = 0);
		void DEBUGassertIntegrity();
		
		float * vertexList;
		unsigned * indexList;
		
		unsigned nVertices;				//a vertex is 3 + 3 + 2 dwords
		unsigned nTriangles;			//a trig is 3 dwords
		
		
		std::string name;				//name of submesh
		unsigned displayList;			//the display list of the submesh, 0xffffffff if none.
		
		void * userData;
		};

/**
A mesh is an ordered list of submeshes.  Each submesh can have a different material assigned
in the model class.
*/
class Mesh
	{
	public:
	typedef std::vector<SubMesh *> SubMeshList;

	SubMeshList subMeshList;	//all the submeshes are owned.
	std::string name;

	Mesh(); 
	~Mesh();
	void load(const char * MeshFName,bool TextureCoords = true,float Scale = 0.0f, bool forceNormals = true, unsigned forceTexCoordType = 0);
	virtual void render(int subMeshIndex = -1);	//-1 means "ALL".
	virtual int findGroup(const char * name);	//returns negative if not found.
	void getBoundingBox(Vec3 & dims);			//returns box edge lengths, not radii.
	void changed(int submeshIndex = -1);		//call to invalidate display lists.  -1 for all of them.
	void collapseToSingleSubmesh();				//all but one of the submeshes get freed.  That submesh gets all the geometry packed in.

	protected:
	Vec3 bbox;

	static void glmGroupToIndexedList(GLMmodel * m, GLMgroup * g, unsigned & nVertices, unsigned & nTriangles, float * & vertexList, unsigned * & indexList);
	/*-------------------------\
	| converts a group to a simple
	| indexed triangle list with
	| 32 bit indices, and vertices
	| of: point, normal, u, v
	\-------------------------*/
	};
	};
#endif //__MESH_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	
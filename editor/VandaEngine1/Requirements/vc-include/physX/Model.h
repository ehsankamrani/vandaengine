#ifndef _SG_MODEL_H__
#define _SG_MODEL_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <iostream>    //ostream would be enough, but gcc only has iostream
#include <3DMath.h>

namespace SceneGraph
	{
	class Material;
	class Mesh;
/**
A model pairs a mesh with a list of materials.  The materials are in the same order
as the mesh' submeshes they correspond to.
*/
class Model
	{
	public:
	Model();
	Model(const Model &);
	~Model();

	void load(std::istream & s);	//loads from ODScript
	void render();
	//void renderAsLight(int lightNo);
	void getBoundingBox(Vec3 & dims);
	void merge(bool keepMaterials, Model & destination, clMatrix4x4 * xform = 0);	//merges this into destination.  if keepMaterials are false, submeshes are collapsed into a single mesh.  The xform is also applied to all vertices.

	

	typedef std::vector<Material *> MaterialList;
	MaterialList materialList;		//materials are not owned.
	Mesh * mesh;					//not owned.

	std::string name;

	void * userData;
	};

	};
#endif //__MODEL_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	

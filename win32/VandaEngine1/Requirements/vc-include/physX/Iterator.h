#ifndef _S_ITERATOR_H__
#define _S_ITERATOR_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

#include <vector>
#include <3DMath.h>

namespace SceneGraph
	{
class Object;
class Model;
class Material;
class Mesh;
class SubMesh;

class Iterator
/*-------------------------------*\
| This class is used to encapsulate scene
| graph traversal in a user app.
| The traversal has to be read only in the
| sense that the scene graph connectivity
| has to stay unchanged.  Data such as positions,
| etc. may be changed.

  Iteration order is depth first.
  To get all possible objects, query as follows:

  example:
  Object * t = ...;

  Iterator i(t);
  i.setCumulateTransforms(true, false);
  Object * o;
  Model * mo;
  Material * ma;
  Mesh * me;
  SubMesh * s;
  while ((o = i.getNextObject())
	{
	clMatrix4x4 * x = i.getCumulatedTransform();

	o->...;
	while ((mo = i.getNextModelOfCurrObject() ))
		{
		mo->...;
		while ((ma = i.getNextMaterialOfCurrModel() ))
			{
			ma->...;
			}
		while ((me = getNextMeshOfCurrModel() ))
			{
			me->...;
			while ((s = i.getNextSubmeshOfCurrMesh() ))
				{
				s->...;
				}
			}
		}
	}


\*-------------------------------*/
	{
	public:
	Iterator(Object *);
	Iterator(Model *);
	Iterator(Mesh *);
	~Iterator();

	void setCumulateTransforms(bool cumulate, bool cumulateRootObject);			//default is false
	clMatrix4x4 * getCumulatedTransform();

	//the list of 'next' objects starts with the first one passed in a ctor! 
	Object * getNextObject();
	Model * getNextModelOfCurrObject();
	Material * getNextMaterialOfCurrModel();
	Mesh * getNextMeshOfCurrModel();
	SubMesh * getNextSubmeshOfCurrMesh();

	private:
	std::vector<clMatrix4x4> xformStack;
	//'next' object pointers.  The current object is the next one to be returned with a next() call.
	Object * o, * starto;
	Model * mo, * currentVisitModel;
	Mesh * me, * currentVisitMesh;
	//Material * ma;
	unsigned subMeshIndex;
	unsigned materialIndex;
	unsigned numDelayedPops;


	bool cumulateTransforms;
	bool cumulateRoot;

	void init();
	void visit(Object *);	//does xform cumulation,etc.
	void visit(Model *);
	void visit(Mesh *);

	void descend(Object *);	//go down one level in the tree
	void ascend(Object *);			//go up one level.

	};

	};
#endif
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
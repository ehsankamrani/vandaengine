#ifndef _SG_OBJECT_H__
#define _SG_OBJECT_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/


#include <3DMath.h>

namespace SceneGraph
	{
	class Model;
	class Primitive;

class Object
/*-------------------------------*\
| Anything that is displayed in the scene. 
| Has location (but may be special for)
| background, may have special status like camera.
| May or may not (camera) have "looks" == a model. 

  Objects are either owned by the scene (top level) or by their parents. This is strictly a forest,
  not a dag, i.e. objects always have max a single parent.
\*-------------------------------*/
	{
	public:
	Object(Model * m = 0, Object * parent = 0);
	~Object();
	virtual void render();
	void renderAsCamera();
	void renderAsLight(int lightNo);

	//manipulation:
	void setScale(flo s);
	void setPosition(flo x,flo y, flo z);
	void setPosition(Vec3 * Position);					//define later as needed
	void setOrientation(Quat * Quat);
	void setOrientation(Vec3 * YawPitchRoll);
	void setVisibility(bool bVisible);
	void lookAt(Vec3 * Target, Vec3 * Up);				//useful for cameras
	void updateMatrix();								//call this if Pos or orient changed manually.

	//tree structure:
	Object	*createChild(Model * clopModel);		//if all 3 nodes are filled, expands tree with a NULL node and creates a new leaf.
	void addChild(Object	*child);				//ditto.
	bool deleteChild(Object	* clopObj);				//removes passed obj from subtrees if its there. (returns true on success.)
	bool removeChild(Object * clopObj);				//removes passed object, removing also it's whole subtree, without deleting anything. 

	void getBoundingBox(Vec3 & dims);				//ask for bounding box.  Only works when containing a Model! Returns box edge lengths, not radii.


	Model * collapseSubtreeToNewModel(Model * m = 0, bool keepMaterials = true, bool meshesInParentsSpace = false, clMatrix4x4 * _ = 0);	
														//create a new model3 that will have a single mesh with all the submeshes of this object, with vertices in the space of this object.
														//if keep materials is false, all the submeshes also get merged.
														//if a model with a mesh is passed, stuff gets merged in there, otherwise a new one is created.
														//xforms encountered in the subtree will be executed on the meshes in the subtree.
														//meshesInParentsSpace determines if the transform of this is execute or not.
														//Note: the returned model is not made into the model of the current node.														

	void deleteSubtree();								//deletes all child objects of this node.  Other referenced objects are not deleted.
	void removeSubtree();								//same as deleteSubtree, but doesn't deallocate nodes in subtree. 
	void executeTransform();							//transforms all meshes in subtree to the space of our parent, and sets our transform to identity.



	Model * model;										//a model (may be NULL for cameras) not owned.
	Primitive * primitive;								//a graphics primitive.  Owned.
	float scale;		
	Vec3 position;
	Quat qOrientation;
	clMatrix4x4 orientation;
	clMatrix4x4 model2World;							//does not contain scaling
	bool bNullXform;									//indicates that above xforms and model are to be ignored -- this obj is only a storage node for 
														//child nodes.
	Object * leftObj, *middleObj,*rightObj;				//descendants ternary tree
														//objs.  Owned.
	Object * parentObj;									//parent of this node in ternary tree, may be null.
														//Only needed for rendering obj as camera, 
														//would be nice if we could eliminate it.

	bool bHideModel;									//set to true to not render model.  Does not hide entire subtree.
	bool bHideSubtree;									//hides all children
	bool bWireFrame;									//forces wireframe view.
	bool bTwoSided;										//no culling
	};

	};
#endif //__OBJECT_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	
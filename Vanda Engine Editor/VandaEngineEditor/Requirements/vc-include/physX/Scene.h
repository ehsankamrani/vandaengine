#ifndef _SG_SCENE_H__
#define _SG_SCENE_H__
/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/


class Object;
class clModel;
class clMesh;
class clMaterial;
class clTexture;

#include <vector>
#include <Smart.h>
#include <3DMath.h>
/*-Revision----------------------*\
| At: 3/14/99 10:03:12 PM
| Made clSceneObj into ternary tree. 
\*-------------------------------*/
/*-Revision----------------------\
| At: 10/3/99 8:32:19 PM
|
| Added some accessor functs.
|
\-------------------------------*/
/*-Revision----------------------\
| At: 4/16/00 7:02:26 PM
| Removed dependency on cl3DGraphics.
|
|
\-------------------------------*/
/*
Revision: August 7, 2003
Refactored.
Renamed:
clScene -> Scene
clSceneObj -> Object
clModel(3) -> Model
clMesh(3) -> Mesh
clMaterial -> Material
clTexture -> Texture

Replaced:
clFNodeList -> STL vector
static scene with scene object.
*/
namespace SceneGraph
	{
	class Object;
	class Model;
	class Mesh;
	class Texture;
	class Material;

class Scene
	{
	public:
	static Scene & getInstance();
	static void shutDown();


	Scene();
	~Scene();

	void	addObject(Object &);
	void	addModel(Model &);
	void	addMesh (Mesh &);
	void	addMaterial(Material &);
	void	addTexture(Texture &);

	void	removeObject(Object &);
	void	removeModel(Model &);
	void	removeMesh (Mesh &);
	void	removeMaterial(Material &);
	void	removeTexture(Texture &);

	//Object		*getObject	(const char * name);
	Model		*getModel	(const char * name);
	Mesh		*getMesh	(const char * name);
	Material	*getMaterial(const char * name);
	Texture		*getTexture	(const char * name);

	void purge();							//purges every loaded object
	void clear(bool bRendertarget=true,bool bDepth=true);
	void render();						//render a frame
	void renderToTexture(float deg_horiz_fov,int rendertarg_w,int rendertarg_h,int dest_w,clTexture & destination,Object * target, int rmode, Object * camera = NULL);
	void setCamera(Object *);		//sets passed obj as the camera.  Obj has to have been created w. CreateObject() call.
	void setLight(int lightNum,Object *);//sets passed obj as a light.  Uses its material settings to produce lighting effects.
	void setProjection(flo Near, flo Far, flo Angle,flo aspect=1.0f);

	void	deletedObject(Object &);


	typedef std::vector<Object*>		ObjectList;
	typedef std::vector<Model*>		ModelList;
	typedef std::vector<Mesh*>		MeshList;
	typedef std::vector<Material*>	MaterialList;
	typedef std::vector<Texture*>		TextureList;

	ObjectList objectList;		//top level scene graph object list.
	ModelList modelList;
	MeshList meshList;
	MaterialList materialList;
	TextureList textureList;


	protected:
	Object * camera;			//the current camera.  (not owned)
	Object * lights[8];			//lights (not owned)

	flo nearPlane, farPlane, FOVAngle, aspect;	//view settings

	static Scene * scene;
	};

	};
#endif //__SCENE_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND
	
/*----------------------------------------------------------------------------*\
|
|						     Nvidia PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/

//
//   nxmltypes.h
//
//
// Internal header file for NXML processing application.
// Declares C++ classes for nxml data types.
//

#ifndef NXMLTYPES_H
#define NXMLTYPES_H

#include <NxPhysics.h>
#include "stringclass.h"
#include "array.h"
#define OFFSET(Class,Member)  (((char*) (&(((Class*)NULL)-> Member )))- ((char*)NULL))


namespace nxml {

class int3  
{
public:
	int x,y,z;
	int3(){};
	int3(int _x,int _y, int _z){x=_x;y=_y;z=_z;}
	const int& operator[](int i) const {return (&x)[i];}
	int& operator[](int i) {return (&x)[i];}
};


class Geometry 
{
public:
	String id;
	Geometry(){}
	virtual ~Geometry(){}
	virtual NxShapeDesc *BuildNX()=0;
};

class Box : public Geometry ,public NxBoxShapeDesc
{
	public:
	NxVec3 size;  // only needed because nx stores their "dimensions" as half the actual size
	Box():Geometry(),size(0,0,0){}
	virtual NxShapeDesc *BuildNX(){dimensions = size/2;return this ;}
};

class Sphere: public Geometry , public NxSphereShapeDesc
{
public:
	Sphere():Geometry(){}
	virtual NxShapeDesc *BuildNX(){return this;}
};

class Plane:public Geometry  , public NxPlaneShapeDesc
{
public:
	Plane():Geometry(){}
	virtual NxShapeDesc *BuildNX(){return this;}
};

class Capsule: public Geometry , public NxCapsuleShapeDesc
{
public:
	NxVec3 p0;
	NxVec3 p1;
	Capsule():Geometry(),p0(0,0,0),p1(0,0,0){}
	virtual NxShapeDesc *BuildNX(){return this;}
};


class Convex: public Geometry
{
	public:
	Array<NxVec3> vertices; 
	Array<int3>   triangles; 
	Array<int>    indices;  // f0.numverts v00 v01 ... v0n f1.numverts v10 v11 ... v1n ... fm.numverts vm0 vm1 ... vmn
	Array<int>    faces;    // index into indices array value is start position in indices array of that face ??
	virtual NxShapeDesc *BuildNX();
    NxConvexMesh* nxmesh;
	Convex():Geometry(),nxmesh(NULL){}
};

class TriMesh:public Geometry 
{
	public:
	Array<NxVec3> vertices;
	Array<int3>   triangles;
	virtual NxShapeDesc *BuildNX();
    NxTriangleMesh* nxmesh;
	TriMesh():Geometry(),nxmesh(NULL){}
};
class Material : public NxMaterialDesc
{
	public:
	int index; // PhysX does everything by index 
	NxMaterial *nxmaterial;
	String id;
	Material(){index=-1;}
};

class Shape
{
public:
	String     id;
	NxVec3     position;
	NxQuat     orientation;
	float	   mass;
	float      density;
	Geometry  *geometry;
	Material*  material;
	Array<Shape*> shape;
	Shape(const char *_id):id(_id),position(0,0,0),orientation(NxVec3(0,0,0),1),geometry(NULL),material(NULL),density(1.0f),mass(0.0f){}
};
class RigidBody : public NxActorDesc , public NxBodyDesc
{ 
	public:
	String     id;
	int        dynamic; // flag true or false;
	NxVec3     position;
	NxQuat     orientation;
	NxVec3     com;
	NxMat33    inertia;
	float      skinwidth;
	Array<Shape*>     shape;
	NxActor *nxactor;
	RigidBody():dynamic(1),position(0,0,0),orientation(NxVec3(0,0,0),1),com(NxVec3(0,0,0)),inertia(NX_ZERO_MATRIX),skinwidth(0),nxactor(NULL){density=1.0;}
};

class Placement
{
public:
	NxVec3 x;
	NxVec3 y;
	NxVec3 z;
	NxVec3 position;
	NxQuat orientation;
	String frame;
	int specified;
	Placement():specified(0),position(0,0,0),orientation(NxVec3(0,0,0),1){}
};

class Joint : public NxD6JointDesc
{
public:
	String id;
	RigidBody *parent;
	RigidBody *child;
	Placement childplacement;
	Placement parentplacement;
	NxVec3 rotlimitmin;
	NxVec3 rotlimitmax;
	//float  spring;
	int	interpenetrate;
	NxJoint *nxjoint;
	Joint(const char *_id):id(_id),parent(NULL),child(NULL),rotlimitmin(0,0,0),rotlimitmax(0,0,0),interpenetrate(0),nxjoint(NULL){}
};

class Model
{
public:
	String id;
	Array<RigidBody *> rigidbody;
	Array<Joint *>     joint;
	Model(const char *_id=""):id(_id){}
};

class SceneDesc
{
public:
	NxVec3 gravity;
	NxVec3 eye;
	NxVec3 lookat;
	NxVec3 up;
	SceneDesc():gravity(0,0,0),eye(0,0,0),lookat(0,0,0),up(0,0,0){}
};

class NxExtra
{
public:
	Array<String> extras;
	NxExtra(){}
};

class Library
{
public:
	Array<Geometry *>  geometry;
	Array<Material *>  material;
	Array<Model *>     model;
	SceneDesc scenedesc;
	NxExtra extradata;
};

	void releaseMemory();
}; // namespace nxml


extern void nxmlcook(nxml::Library *library);
nxml::Library *nxmlLoadScene(const char *filename);



#endif
//AGCOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 NVIDIA Technologies.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//AGCOPYRIGHTEND

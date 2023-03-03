/*----------------------------------------------------------------------------*\
|
|						    NVIDIA PhysX Technology
|
|							     www.nvidia.com
|
\*----------------------------------------------------------------------------*/
#ifndef _SG_PRIMITIVE_H__
#define _SG_PRIMITIVE_H__

#include <3DMath.h>

namespace SceneGraph
	{
	class Texture;


class Primitive
	{
	public:
	virtual void render() = 0;
	};


class Billboard : public Primitive
	{
	public:
	Texture * texture;		//not owned!
	float xmin,  xmax, ymin, ymax;
	bool bHide;
	Billboard(Texture * t, float xmin_=-1.0f, float xmax_=1.0f, float ymin_=-1.0f, float ymax_=1.0f)
		{
		// these extends are in a coord system where (-1, -1) is lower left corner, 
		// and 1, 1 is upper right. Default is full screen.
		// The billboard is rendered at the Z plane, but with z buffering, so a full 
		// screen bb will hide everything.
		xmin = xmin_;
		xmax = xmax_;
		ymin = ymin_;
		ymax = ymax_;
		texture = t;
		bHide = false;
		}
	void render();
	};

class DisplayList : public Primitive
	{
	int dispList;
	public:
	DisplayList(int no)
		{
		dispList = no;
		}
	~DisplayList();

	void render();
	};

class Line : public Primitive
	{
	Vec3 s,e;
	public:
	Line(const Vec3 & start, const Vec3 & end)
		{
		s = start;
		e = end;
		}
	void set(const Vec3 & start,const Vec3 & end)
		{
		s = start;
		e = end;
		}
	void render();
	};

class Plane : public Primitive
	{
	public:
	Vec3 v[4];		//four vertices in world coords for visualization.  
	Vec3 base[2];	//two other vectors which make up base at point along with normal.
	Vec3 point,normal;

	void computeVertices(float size = 1.0f)
		{
		v[2] = (base[0] + base[1]) * size;
		v[3] = (base[0] - base[1]) * size;
		v[1] = v[3] * -1;
		v[0] = v[2] * -1;

		v[0] += point;
		v[1] += point;
		v[2] += point;
		v[3] += point;
		}
	Plane() {}
	Plane(Vec3 & loc,Vec3 & normala, float size = 1.0f)
		{
		construct(loc,normala,size);
		}
	void construct(Vec3 & loc,Vec3 & normala, float size = 1.0f)
		{
		//This code comes up with 4 vertices in the plane specified, which make a quad around loc. 
		Vec3 x(1,0,0);
		Vec3 y(0,1,0);

		normal = normala;
		normal.Normalize();
		point = loc;

		if (normal.x >= 0.9f && normal.x <= 1.1f)
			{//normal is approximately equal to x, use y for cross product instead.
			base[0].Cross(normal,y);
			}
		else
			{//use x for cross product.
			base[0].Cross(normal,x);
			}
		base[0].Normalize();
		base[1].Cross(normal,base[0]);//v[1] should be of unit length.

		computeVertices(size);
		//Coool!
		}

	void render();
	}; 

	};

#endif //__PRIMITIVE_H__
//NVIDIACOPYRIGHTBEGIN
///////////////////////////////////////////////////////////////////////////
// Copyright © 2010 NVIDIA Corporation.
// All rights reserved. www.nvidia.com
///////////////////////////////////////////////////////////////////////////
//NVIDIACOPYRIGHTEND

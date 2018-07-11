/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

/*************************************************
*******HOW TO SPECIFY THE LENS OF THE CCamera*****
******Docment Written by Ehsan Kamrani ***********

Files:
..\GraphicEngine\CCamera.h
..\GraphicEngine\CCamera.cpp

Usage:

1)Include the header file:
   #include "GraphicEngine\CCamera.h"

2)Define a CCameraLENS object:
   CCamera lens;

3)To initialize a perspective projection:
   lens.SetPerspective);

4)To zoom In by a small value:
   lens.ZoomIn( smallValue );

5)To zoom Outby a small value:
   lens.ZoomOut( smallValue );

6)To move the CCamera position to the left, right, upon and back 
use from the MoveLeft(), MoveRight(), MoveForward() and
MoveBackward() respectively. To rotate to the left and right
use from the functions RotateLeft() and RotateRight() respectively.

7)To insert the CCamera in a position, call UpdatePosition(). call it 
after the functions listed in number 6.
************************************************/

#pragma once
#include "base.h"
#include "matrix.h"
#include "node.h"
class CCamera;

class CInstanceCamera
{
public:
	CInstanceCamera()
	{
		m_x=0;
		m_y=0;
		m_z=0;
		m_pan=0;
		m_tilt=0;
		m_zoom=0;
	};
	CNode *m_parent;			// Node where this instance was instantiated
	CCamera	*m_abstractCamera;	// The abstract Camera where the CCamera parameters are stored
	CMatrix m_transform;
	CVoid SetPanAndTilt(CFloat setpan, CFloat settilt)
	{
		m_pan += setpan;
		m_tilt += settilt;
		SetTransform();
	}

	CVoid SetPanAndTilt2(CFloat setpan, CFloat settilt)
	{
		m_pan = setpan;
		m_tilt = settilt;
		SetTransform();
	}

	CVoid MoveOrbit(CFloat xx, CFloat yy)
	{
		CMatrixTranslate( m_transform, 0, 0, -m_zoom);
		CMatrixTranslate( m_transform, xx, yy, 0 );
		m_x = m_transform[M30];
		m_y = m_transform[M31];
		m_z = m_transform[M32];
		SetTransform();
	}
	CVoid MoveTransform(CFloat forward, CFloat strafe, CFloat jump)
	{  
		CFloat COSPAN = cos(m_pan * DEGREES_TO_RADIANS);
		CFloat SINPAN = sin(m_pan * DEGREES_TO_RADIANS);

		m_x += - COSPAN * strafe + SINPAN * forward;
		m_y += jump;
		m_z += SINPAN * strafe + COSPAN * forward;
		SetTransform();
	}
	CVoid MoveTransform2(CFloat x, CFloat y, CFloat z)
	{  
		m_x = x;
		m_y = y;
		m_z = z;
		SetTransform();
	}

	CVoid ZoomTransform(CFloat zoomz) 
	{
		m_zoom += zoomz;
		SetTransform();
	}
	CVoid ZoomTransform2(CFloat zoomz) 
	{
		m_zoom = zoomz;
		SetTransform();
	}

public:
	CVoid RenderIcon();
	CFloat	m_pan;
	CFloat	m_tilt;
	CFloat m_x,m_y,m_z;
	CFloat	m_zoom;
	CVoid SetTransform();
};

#pragma once

#include <math.h>
#include "OpenGL.h"
#include "render.h"
#include "..\Common\Point.h"
#include "..\Common\Vector.h"
#include "..\PhysXEngine\Nx.h"
#include <PhysX/NxPhysics.h>

const CDouble piover180 = 0.0174532925f;

class CCamera:public CBase
{
private:
	GLfloat m_frustum[6][4];
	GLvoid SetBillboard( CFloat p1, CFloat p2, CFloat p3, GLuint texID, CFloat sizex, CFloat sizey );
protected:
	CVoid Update( CInt32 sWidth, CInt32 sHeight );
public:
    CCamera();
	~CCamera();

	CVoid Init();
	GLvoid SetPerspective();
	GLvoid SetPerspective( GLdouble far );
	GLvoid SetPerspective( GLdouble angle, GLdouble width, GLdouble height, GLdouble near, GLdouble far );
	GLvoid Set2DOrtho( CDouble left, CDouble right, CDouble bottom, CDouble top );
	CBool SetZoomIn( GLdouble delta );
	CBool SetZoomOut( GLdouble delta );
	GLdouble GetAngle();
	GLdouble GetMinAngle();
	GLdouble GetMaxAngle();
	GLdouble GetDefaultAngle();

	CVoid SetAngle( GLdouble angle );
	CVoid SetMinAngle(GLdouble angle);
	CVoid SetMaxAngle(GLdouble angle);
	CVoid SetDefaultAngle(GLdouble angle);

    GLvoid UpdateFrustum();

	GLvoid UpdateCameraPosDir( const NxVec3& cameraPos, const NxVec3& atPos, const NxVec3& cameraDir, const CFloat y_offset );
	CVoid GetInverseMatrix(float mCameraInverse[16]);
	CBool IsPointInFrustum( Point p );
	CBool IsBoxInFrustum( CVec3f* p, CUInt numPoints );
	CBool IsPointInFrustum( GLfloat x, GLfloat y, GLfloat z );
	CBool IsSphereInFrustum( Point p, GLfloat Radius );
	CBool IsSphereInFrustum( GLfloat x, GLfloat y, GLfloat z, GLfloat radius );

	CBool IsOccluded( Point p );

	//CBool InitializeLensFlare();
	//GLvoid RenderLensFlare();
	//GLvoid ReleaseLensFlare();

	//GLvoid RenderGlow( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
	//	                  Point CenterPoint, GLfloat scale );
	//GLvoid RenderHalo( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
	//	               Point CenterPoint, GLfloat scale );   

	//functions related to COLLADA camera
	inline CFloat	GetXFov()	{ return m_xFov;	 }
	inline CFloat	GetYFov()	{ return m_yFov;	 }
	inline CFloat	GetZNear()	{ return m_zNear;  }
	inline CFloat	GetZFar()	{ return m_zFar;	 }
	inline CFloat	GetAspect()	{ return m_aspect; }
	inline CFloat	GetXMag()	{ return m_xMag;	 }
	inline CFloat	GetYMag()	{ return m_yMag;	 }

	inline CVoid	SetXFov(CFloat fovx)     { m_xFov = fovx;  }
	inline CVoid 	SetYFov(CFloat fovf)     { m_yFov = fovf;  }
	inline CVoid 	SetZNear(CFloat nearf)   { m_zNear = nearf; }
	inline CVoid	SetZFar(CFloat farf)     { m_zFar = farf;  }
	inline CVoid	SetAspect(CFloat aspect) { m_aspect = aspect;}
	inline CVoid	SetXMag(CFloat magx)     { m_xMag = magx;  }
	inline CVoid 	SetYMag(CFloat magy)     { m_yMag = magy;  }

	//Point m_lightSourcePos;                 //Leight source position
    CVector m_vLightSourceToCCamera;        //A vector from light source to the CCamera position
	Point m_position;                       //CCamera position 
	Point m_ptintersect;                    //intersection point
	CVector m_directionVector;               //Direction of our CCamera
	CVector m_vLightSourceTointersect;       //A vector from the light source to the intersection point
	Point m_pt;                               //POINT to temp 

private:
	GLdouble m_angle;
	GLdouble m_defaultAngleValue;
	GLdouble m_maxAngleValue;
	GLdouble m_minAngleValue;

private:
	//variables related to COLLADA camera
	CFloat		m_xFov;		// X field of view for perspective CCamera
	CFloat		m_yFov;		// Y field of view for perspective CCamera
	CFloat		m_aspect;	// Aspect Ratio for perspective CCamera
	CFloat		m_zNear;	// Z clip near for perspective CCamera
	CFloat		m_zFar;		// Z clip far for perspective CCamera

	CFloat		m_xMag;		// X magnification for an orthographic CCamera
	CFloat		m_yMag;		// Y magnification for an orthographic CCamera

	//GLuint m_haloTexture;
	//GLuint m_glowTexture;
};

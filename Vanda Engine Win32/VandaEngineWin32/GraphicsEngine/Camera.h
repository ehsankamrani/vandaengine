//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/*************************************************
*******HOW TO SPECIFY THE LENS OF THE CCamera*****


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
	CInstanceCamera();
	~CInstanceCamera();

	CNode *m_parent;			// Node where this instance was instantiated
	CCamera	*m_abstractCamera;	// The abstract Camera where the CCamera parameters are stored
	CMatrix m_transform;

	CBool IsActive() { return m_active; }
	CVoid SetActive(CBool set) { m_active = set; }

	CBool IsTimerEnabled() { return m_enableTimer; }
	CVoid SetIsTimerEnabled(CBool set) { m_enableTimer = set; }
	CFloat GetElaspedSeconds() { return m_elaspedSeconds; }
	CVoid SetEndTime(CFloat time) { m_endTime = time; }
	CBool IncreaseElapsedSeconds(CFloat elapsedSeconds)
	{
		if (m_enableTimer)
		{
			m_elaspedSeconds += elapsedSeconds;
			if (m_elaspedSeconds > m_endTime)
			{
				m_enableTimer = CFalse;
				m_elaspedSeconds = m_endTime = 0.0f;
				return CFalse;
			}
			else
			{
				return CTrue;
			}
		}
		else
			return CTrue;
	}
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

	//Get
	CFloat GetZoom() { return m_zoom; }
	CVec3f GetPos() { CVec3f m_pos(m_x, m_y, m_z); return m_pos; }
	CFloat GetNCP() { return m_ncp; }
	CFloat GetFCP() { return m_fcp; }
	CFloat GetPan() { return m_pan; }
	CFloat GetTilt() { return m_tilt; }
	//Set
	CVoid SetZoom(CFloat zoom) { m_zoom = zoom; }
	CVoid SetPos(CVec3f pos) { m_x = pos.x; m_y = pos.y; m_z = pos.z; }
	CVoid SetNCP(CFloat ncp) { m_ncp = ncp; }
	CVoid SetFCP(CFloat fcp) { m_fcp = fcp; }
	CVoid SetPan(CFloat pan) { m_pan = pan; }
	CVoid SetTilt(CFloat tilt) { m_tilt = tilt; }
	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CInt GetIndex() { return m_nameIndex; }

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScript(CChar* script) { Cpy(m_script, script); }
	CChar* GetScript() { return m_script; }
	CVoid SetLastScriptPath(CChar* script) { Cpy(m_lastScriptPath, script); }
	CChar* GetLastScriptPath() { return m_lastScriptPath; }

	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

	CVoid ResetLua();
	CBool LoadLuaFile();

	CVoid InitScript();
	CVoid UpdateScript();

	//functions to get and set script variables
	CChar* GetScriptStringVariable(CChar* variableName);
	CBool GetScriptBoolVariable(CChar* variableName);
	CInt GetScriptIntVariable(CChar* variableName);
	CDouble GetScriptDoubleVariable(CChar* variableName);
	CVoid SetScriptStringVariable(CChar* variableName, CChar* value);
	CVoid SetScriptBoolVariable(CChar* variableName, CBool value);
	CVoid SetScriptIntVariable(CChar* variableName, CInt value);
	CVoid SetScriptDoubleVariable(CChar* variableName, CDouble value);

	CVoid SetUpdateEvent(CBool set) { m_updateEvent = set; }
	CBool GetUpdateEvent() { return m_updateEvent; }

private:
	CFloat	m_pan;
	CFloat	m_tilt;
	CFloat m_x, m_y, m_z;
	CFloat	m_zoom;
	CFloat m_ncp, m_fcp;
	CBool m_active;
	CVec3f m_up;
	CVec3f m_direction;
	CInt m_nameIndex;
	CFloat m_cameraSpeed;
	CBool m_enableTimer;
	CFloat m_elaspedSeconds;
	CFloat m_endTime;

	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
	CBool m_updateEvent;
public:
	CVoid SetTransform();  //it's use for free camera instance
	CFloat GetCameraSpeed() { return m_cameraSpeed; }
	CVoid SetCameraSpeed(CFloat speed) { m_cameraSpeed = speed; }
	CVoid IncreaseOrDecreaseCameraSpeed(CFloat speed) { m_cameraSpeed += speed; }
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

	CVoid SetAngle(GLdouble angle);
	CVoid SetMinAngle(GLdouble angle);
	CVoid SetMaxAngle(GLdouble angle);
	CVoid SetDefaultAngle(GLdouble angle);

	GLvoid UpdateFrustum();
	CVoid GetInverseMatrix(float mCameraInverse[16]);

	GLvoid UpdateCameraPosDir( const NxVec3& cameraPos, const NxVec3& atPos, const NxVec3& cameraDir, const CFloat y_offset );
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

	CVoid SetPureName(const CChar* name) { Cpy(m_pureName, name); }
	CChar* GetPureName() { return m_pureName; }

private:
	GLdouble m_angle;
	GLdouble m_defaultAngleValue;
	GLdouble m_maxAngleValue;
	GLdouble m_minAngleValue;
	CChar m_pureName[MAX_NAME_SIZE];

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


struct CUpdateCamera
{
	CCamera *m_cameraManager; //Default camera of the scene, I don't use the external cameras of the Collada file

	NxVec3 m_perspectiveCameraPos;
	NxVec3 m_perspectiveCameraPosOfPreviousFrame;
	NxVec3 m_perspectiveCameraDir;
	NxVec3 m_perspectiveCharacterPos; //equals AtPos
	NxVec3 m_perspectiveCharacterPosOfPreviousFrame;
	CFloat m_perspectiveCameraYaw;
	CFloat m_perspectiveCameraPitch;
	CFloat m_perspectiveCameraTilt; //Currently m_tilt must  be passed directly to UpdateCameraPosDir(), I should find a way to calculate the tilt inside the GetCameraAndCharaterPosition().
	CFloat m_perspectiveCurrentCameraTilt;
	CFloat m_perspectiveCameraMinTilt;
	CFloat m_perspectiveCameraMaxTilt;
	CDouble m_perspectiveCameraZoom;
	CDouble m_perspectiveCurrentCameraZoom;
	CFloat m_cameraSpeed;

	CUpdateCamera()
	{
		m_cameraManager = new CCamera();

		m_perspectiveCameraYaw = 0.0f;
		m_perspectiveCameraPitch = 0.0f;
		m_perspectiveCameraTilt = 0.0f;
		m_perspectiveCurrentCameraTilt = 0.0f;
		m_perspectiveCameraMinTilt = -0.5f;
		m_perspectiveCameraMaxTilt = 0.5f;
		m_perspectiveCameraZoom = 0.0;
		m_perspectiveCurrentCameraZoom = 0.0f;
		m_cameraSpeed = 1.0f;

	}
	~CUpdateCamera()
	{
		CDelete( m_cameraManager );
	}

	CVoid Reset()
	{
		m_perspectiveCameraYaw = 0.0f;
		m_perspectiveCameraPitch = 0.0f;
		m_perspectiveCameraTilt = 0.0f;
		m_perspectiveCurrentCameraTilt = 0.0f;
		m_perspectiveCameraMinTilt = -0.5f;
		m_perspectiveCameraMaxTilt = 0.5f;
		m_perspectiveCameraZoom = 0.0;
		m_perspectiveCurrentCameraZoom = 0.0f;
		m_cameraSpeed = 1.0f;
	}

};

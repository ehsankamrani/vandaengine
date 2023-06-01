//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "camera.h"
#include "../VandaEngineEditorDlg.h"
#include "..//GraphicsEngine/Render.h"

CInstanceCamera::CInstanceCamera()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_pan = 0;
	m_tilt = 0;
	m_zoom = 0;
	m_ncp = 0.01f;
	m_fcp = 50000.f;
	m_active = CFalse;
	m_cameraSpeed = DEFAULT_CAMERA_SPEED;
	m_enableTimer = CFalse;
	m_elaspedSeconds = 0.0f;
	m_endTime = 0.0f;

	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
	m_updateEvent = CTrue;

}

CInstanceCamera::~CInstanceCamera()
{
	LuaClose(m_lua);
}

CVoid CInstanceCamera::SetTransform()
{
	CMatrixLoadIdentity(m_transform);
	CMatrixTranslate(m_transform, m_x, m_y, m_z);
	CMatrix4x4RotateAngleAxis(m_transform, 0.0f, 1.0f, 0.0f, m_pan);
	CMatrix4x4RotateAngleAxis(m_transform, 1.0f, 0.0f, 0.0f, m_tilt);
	CMatrixTranslate(m_transform, 0, 0, m_zoom);
	m_parent->SetLocalToWorldMatrix(&m_transform);
}

CVoid CInstanceCamera::RenderIcon(CBool selectionMode)
{
	if (m_active) return;

	CVec3f final_pos;
	CVec3f final_at;
	if (m_parent)
	{
		CMatrix mat;
		const CMatrix *ltow;
		ltow = m_parent->GetLocalToWorldMatrix();
		CMatrixCopy(*ltow, mat);
		CVec3f at(0, 0, -1), pos(0, 0, 0);
		CMatrixTransform(mat, at, final_at);
		CMatrixTransform(mat, pos, final_pos);
	}
	else
	{
		final_pos.x = m_x; final_pos.y = m_y; final_pos.z = m_z;
	}

	if (selectionMode)
	{
		glPushName(m_nameIndex);
	}
	if (!selectionMode)
	{
		if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;
			if (g_transformObject)
			{
				final_pos.x = g_arrowPosition.x;
				final_pos.y = g_arrowPosition.y;
				final_pos.z = g_arrowPosition.z;
				m_x = final_pos.x; m_y = final_pos.y; m_z = final_pos.z;
				SetTransform();
			}
			else
			{
				g_arrowPosition.x = final_pos.x;
				g_arrowPosition.y = final_pos.y;
				g_arrowPosition.z = final_pos.z;
			}
			if (g_menu.m_showCameraIcons)
				g_glUtil.Billboarding(final_pos.x, final_pos.y, final_pos.z, g_cameraImg->GetId(), 1.0f, 1.0f, 1.0, 0.0, 0.0);

			if (g_currentCameraType != eCAMERA_ENGINE)
				g_showArrow = CTrue;
		}
		else
		{
			if (g_menu.m_showCameraIcons)
				g_glUtil.Billboarding(final_pos.x, final_pos.y, final_pos.z, g_cameraImg->GetId(), 1.0f, 1.0f);
		}
	}
	else
	{
		if (g_menu.m_showCameraIcons)
			g_glUtil.Billboarding(final_pos.x, final_pos.y, final_pos.z, g_cameraImg->GetId(), 1.0f, 1.0f);
	}
	if (selectionMode)
		glPopName();

}

CChar* CInstanceCamera::GetLastName()
{
	return m_lastName;
}

CVoid CInstanceCamera::SetLastName(CChar* name)
{
	Cpy(m_lastName, name);
}

CVoid CInstanceCamera::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CInstanceCamera::LoadLuaFile()
{
	ResetLua();

	if (!m_hasScript)
	{
		return CFalse;
	}

	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

CChar* CInstanceCamera::GetScriptStringVariable(CChar* variableName)
{
	CChar *s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CInstanceCamera::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CInstanceCamera::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CInstanceCamera::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CInstanceCamera::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstanceCamera::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstanceCamera::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstanceCamera::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CInstanceCamera::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CInstanceCamera::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CCamera::Update( CInt32 sWidth, CInt32 sHeight )
{

}

CCamera::CCamera()
{
	Init();
}

CCamera::~CCamera()
{
}

CVoid CCamera::Init()
{
	//Defalut values for the camera lens
	m_defaultAngleValue = DEFAULT_CAMERA_ANGLE;
	m_maxAngleValue = MAX_CAMERA_ANGLE;
	m_minAngleValue = MIN_CAMERA_ANGLE;
	m_angle = m_defaultAngleValue;
/*	m_lightSourcePos.x = -40.0f;
	m_lightSourcePos.y = 70.0f;
	m_lightSourcePos.z = 200.0f;
	m_haloTexture = 0;
	m_glowTexture = 0;
 */
	//variables related to COLLADA camera
	m_yFov = 54.0f;
	m_aspect = 16.0f / 9.0f;
	m_zNear = 1.0f;
	m_zFar = 100000.0f;		

}

GLvoid CCamera::SetBillboard( CFloat p1, CFloat p2, CFloat p3, GLuint texID, CFloat sizex, CFloat sizey )
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	CFloat mat[16];
	glGetFloatv( GL_MODELVIEW_MATRIX, mat );

	CVector right( mat[0], mat[4], mat[8] );
	CVector up( mat[1], mat[5], mat[9] );
	CVector p( p1, p2, p3 );

	glEnable( GL_TEXTURE_2D );
	CVector temp;
	glBindTexture( GL_TEXTURE_2D, texID );
	glBegin( GL_QUADS );
	glTexCoord2f( 0.0f, 0.0f );
	CVector tempRight = right * sizex;
	CVector tempUp = up * sizey;
	temp = p + ( tempRight + tempUp ) * -1.0;
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 0.0f );
	temp = p + ( tempRight - tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 1.0f, 1.0f );
	temp = p + (tempRight + tempUp );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glTexCoord2f( 0.0f, 1.0f );
	temp = p + ( tempUp - tempRight );
	glVertex3f( temp.m_i, temp.m_j, temp.m_k );
	glEnd();
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );
}

GLvoid CCamera::SetPerspective()
{
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	//Switch to projection matrix
	g_render.ProjectionMatrix();
	g_render.IdentityMatrix();
	gluPerspective( m_angle, (GLdouble)viewport[2] / (GLdouble)viewport[3], 0.01, 3000.0 );
	//Return back to model-view matrix
	g_render.ModelViewMatrix();
}

GLvoid CCamera::SetPerspective( GLdouble angle, GLdouble width, GLdouble height, GLdouble zNear, GLdouble zFar )
{
	//Switch to projection matrix
	g_render.ProjectionMatrix();
	g_render.IdentityMatrix();
	gluPerspective( angle, (GLdouble)width / (GLdouble)height, zNear, zFar );
	//Return back to model-view matrix
	g_render.ModelViewMatrix();
}

GLvoid CCamera::SetPerspective( GLdouble Far )
{
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );

	//Switch to projection matrix
	g_render.ProjectionMatrix();
	g_render.IdentityMatrix();
	gluPerspective( m_angle, (GLdouble)viewport[2] / (GLdouble)viewport[3], 0.01f, Far );
	//Return back to model-view matrix
	g_render.ModelViewMatrix();
}

GLvoid CCamera::Set2DOrtho( CDouble left, CDouble right, CDouble bottom, CDouble top )
{
	g_render.ProjectionMatrix();
	g_render.IdentityMatrix();
	glOrtho( left, right, bottom, top, -50000., 50000. );
}

CBool CCamera::SetZoomOut( GLdouble delta )
{
	if( m_angle < m_maxAngleValue )
	{
		m_angle += delta; //Zoom In( Increment m_angle )
		return true;
	}
	return false;
}

CBool CCamera::SetZoomIn( GLdouble delta)
{
	if( m_angle > m_minAngleValue )
	{
		m_angle -= delta; //Zoom In( Increment m_angle )
		return true;
	}
	return false;
}

//We need this m_angle in selection mode
GLdouble CCamera::GetDefaultAngle()
{
	return m_defaultAngleValue;
}

CVoid CCamera::SetDefaultAngle(GLdouble angle)
{
	m_defaultAngleValue = angle;
}

GLdouble CCamera::GetAngle()
{
	return m_angle;
}

GLdouble CCamera::GetMinAngle()
{
	return m_minAngleValue;
}

GLdouble CCamera::GetMaxAngle()
{
	return m_maxAngleValue;
}

CVoid CCamera::SetAngle( GLdouble angle )
{
	m_angle = angle;
}

CVoid CCamera::SetMinAngle(GLdouble angle)
{
	m_minAngleValue = angle;
}

CVoid CCamera::SetMaxAngle(GLdouble angle)
{
	m_maxAngleValue = angle;
}

GLvoid CCamera::UpdateCameraPosDir(const NxVec3& cameraPos, const NxVec3& characterPos, const NxVec3& cameraDir, const CFloat y_offset)
{
	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	if ((g_currentCameraType == eCAMERA_PHYSX && !g_mainCharacter) || (g_mainCharacter && g_mainCharacter->GetCameraType() == ePHYSX_CAMERA_FIRST_PERSON))
	{
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, //Eye position
			characterPos.x, characterPos.y + g_physXProperties.m_fCapsuleHeight + y_offset, characterPos.z,    //At position 
			0.0f, 1.0f, 0.0f);           //Direction of the viewer
	}
	else
	{
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, //Eye position
			characterPos.x, characterPos.y + (g_physXProperties.m_fCapsuleHeight / 2.0f) + y_offset, characterPos.z,    //At position 
			0.0f, 1.0f, 0.0f);           //Direction of the viewer
	}

	///////////Update the position and direction of our camera////////////
	m_directionVector.m_i = characterPos.x - cameraPos.x;
	m_directionVector.m_j = characterPos.y - cameraPos.y;
	m_directionVector.m_k = characterPos.z - cameraPos.z;

	m_directionVector.Magnitude();
	m_directionVector.Normalize();

	m_position.m_x = cameraPos.x;
	m_position.m_y = cameraPos.y;
	m_position.m_z = cameraPos.z;
}

GLvoid CCamera::UpdateFrustum()
{
	GLfloat   clip[16];
	GLfloat   proj[16];
	GLfloat   modl[16];
	GLfloat   t;

	/* Get the current PROJECTION matrix from OpenGL */
	glGetFloatv( GL_PROJECTION_MATRIX, proj );

	/* Get the current MODELVIEW matrix from OpenGL */
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );

	/* Combine the two matrices (multiply projection by modelview) 
	   but keep in mind this function will only work if you do NOT
	   rotate or translate your projection matrix                  */
	clip[ 0] = modl[ 0] * proj[ 0];
    clip[ 1] = modl[ 1] * proj[ 5];
    clip[ 2] = modl[ 2] * proj[10] + modl[ 3] * proj[14];
    clip[ 3] = modl[ 2] * proj[11];

    clip[ 4] = modl[ 4] * proj[ 0];
    clip[ 5] = modl[ 5] * proj[ 5];
    clip[ 6] = modl[ 6] * proj[10] + modl[ 7] * proj[14];
    clip[ 7] = modl[ 6] * proj[11];

    clip[ 8] = modl[ 8] * proj[ 0];
    clip[ 9] = modl[ 9] * proj[ 5];
    clip[10] = modl[10] * proj[10] + modl[11] * proj[14];
    clip[11] = modl[10] * proj[11];

    clip[12] = modl[12] * proj[ 0];
    clip[13] = modl[13] * proj[ 5];
    clip[14] = modl[14] * proj[10] + modl[15] * proj[14];
    clip[15] = modl[14] * proj[11];

	/* Extract the numbers for the RIGHT plane */
	m_frustum[0][0] = clip[ 3] - clip[ 0];
	m_frustum[0][1] = clip[ 7] - clip[ 4];
	m_frustum[0][2] = clip[11] - clip[ 8];
	m_frustum[0][3] = clip[15] - clip[12];

	/* Normalize the result */
	t = GLfloat(sqrt( m_frustum[0][0] * m_frustum[0][0] + m_frustum[0][1] * m_frustum[0][1] + m_frustum[0][2] * m_frustum[0][2] ));
	m_frustum[0][0] /= t;
	m_frustum[0][1] /= t;
	m_frustum[0][2] /= t;
	m_frustum[0][3] /= t;

    /* Extract the numbers for the LEFT plane */
    m_frustum[1][0] = clip[ 3] + clip[ 0];
    m_frustum[1][1] = clip[ 7] + clip[ 4];
    m_frustum[1][2] = clip[11] + clip[ 8];
    m_frustum[1][3] = clip[15] + clip[12];

    /* Normalize the result */
    t = GLfloat(sqrt( m_frustum[1][0] * m_frustum[1][0] + m_frustum[1][1] * m_frustum[1][1] + m_frustum[1][2] * m_frustum[1][2] ));
    m_frustum[1][0] /= t;
    m_frustum[1][1] /= t;
    m_frustum[1][2] /= t;
    m_frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
    m_frustum[2][0] = clip[ 3] + clip[ 1];
    m_frustum[2][1] = clip[ 7] + clip[ 5];
    m_frustum[2][2] = clip[11] + clip[ 9];
    m_frustum[2][3] = clip[15] + clip[13];

    /* Normalize the result */
    t = GLfloat(sqrt( m_frustum[2][0] * m_frustum[2][0] + m_frustum[2][1] * m_frustum[2][1] + m_frustum[2][2] * m_frustum[2][2] ));
    m_frustum[2][0] /= t;
    m_frustum[2][1] /= t;
    m_frustum[2][2] /= t;
    m_frustum[2][3] /= t;

    /* Extract the TOP plane */
    m_frustum[3][0] = clip[ 3] - clip[ 1];
    m_frustum[3][1] = clip[ 7] - clip[ 5];
    m_frustum[3][2] = clip[11] - clip[ 9];
    m_frustum[3][3] = clip[15] - clip[13];

    /* Normalize the result */
    t = GLfloat(sqrt( m_frustum[3][0] * m_frustum[3][0] + m_frustum[3][1] * m_frustum[3][1] + m_frustum[3][2] * m_frustum[3][2] ));
    m_frustum[3][0] /= t;
    m_frustum[3][1] /= t;
    m_frustum[3][2] /= t;
    m_frustum[3][3] /= t;

    /* Extract the FAR plane */
    m_frustum[4][0] = clip[ 3] - clip[ 2];
    m_frustum[4][1] = clip[ 7] - clip[ 6];
    m_frustum[4][2] = clip[11] - clip[10];
    m_frustum[4][3] = clip[15] - clip[14];

    /* Normalize the result */
    t = GLfloat(sqrt( m_frustum[4][0] * m_frustum[4][0] + m_frustum[4][1] * m_frustum[4][1] + m_frustum[4][2] * m_frustum[4][2] ));
    m_frustum[4][0] /= t;
    m_frustum[4][1] /= t;
    m_frustum[4][2] /= t;
    m_frustum[4][3] /= t;

    /* Extract the NEAR plane */
    m_frustum[5][0] = clip[ 3] + clip[ 2];
    m_frustum[5][1] = clip[ 7] + clip[ 6];
    m_frustum[5][2] = clip[11] + clip[10];
    m_frustum[5][3] = clip[15] + clip[14];

    /* Normalize the result */
    t = GLfloat(sqrt( m_frustum[5][0] * m_frustum[5][0] + m_frustum[5][1] * m_frustum[5][1] + m_frustum[5][2] * m_frustum[5][2] ));
    m_frustum[5][0] /= t;
    m_frustum[5][1] /= t;
    m_frustum[5][2] /= t;
    m_frustum[5][3] /= t;
}

// The idea behind this algorithum is that if the point
// is inside all 6 clipping planes then it is inside our
// viewing volume so we can return true.

CBool CCamera::IsBoxInFrustum( CVec3f* p, CUInt numPoints )
{
	for( CInt i = 0; i < 6; i++ ) //for all the planes
	{
		CInt count = 0;
		for( CUInt j = 0; j < numPoints; j++ ) //for all the vertexes of bounding box
			if( m_frustum[i][0] * p[j].x + m_frustum[i][1] * p[j].y + m_frustum[i][2] * p[j].z + m_frustum[i][3] <= 0 )
				count++;
		if( count == numPoints )
			return false; //the box is outside the frustum
	}
	return true; //the box is inside the frustum
}

CBool CCamera::IsPointInFrustum( Point p )
{
	for( CInt i = 0; i < 6; i++ )
	{
		if( m_frustum[i][0] * p.m_x + m_frustum[i][1] * p.m_y + m_frustum[i][2] * p.m_z + m_frustum[i][3] <= 0 )
			return false;
	}
	return true;
}

// The idea behind this algorithum is that if the point
// is inside all 6 clipping planes then it is inside our
// viewing volume so we can return true.
CBool CCamera::IsPointInFrustum( GLfloat x, GLfloat y, GLfloat z )
{
	for( CInt i = 0; i < 6; i++ )
	{
		if( m_frustum[i][0] * x + m_frustum[i][1] * y + m_frustum[i][2] * z + m_frustum[i][3] <= 0 )
			return false;
	}
	return true;
}

// The idea here is the same as the PointInFrustum function.
CBool CCamera::IsSphereInFrustum(Point p, GLfloat Radius)
{
	for(CInt i = 0; i < 6; i++)
	{
		// If the point is outside of the plane then its not in the viewing volume.
		if(m_frustum[i][0] * p.m_x + m_frustum[i][1] * p.m_y + m_frustum[i][2] * p.m_z + m_frustum[i][3] <= -Radius)
		{
			return false;
		}
	}
	
	return true;
}

CBool CCamera::IsSphereInFrustum( GLfloat x, GLfloat y, GLfloat z, GLfloat Radius )
{
	for( CInt i = 0; i < 6; i++ )
	{
		if( m_frustum[i][0] * x + m_frustum[i][1] * y + m_frustum[i][2] * z + m_frustum[i][3] <= -Radius )
		{
			return false;
		}
	}
	return true;
}

CBool CCamera::IsOccluded(Point p)
{
	GLint viewport[4];							// Space For Viewport Data
	GLdouble mvmatrix[16], projmatrix[16];		// Space For Transform Matrix
	GLdouble winx, winy, winz;					// Space For Returned Projected Coords
	GLdouble flareZ;							// Here We Will Store The Transformed Flare Z
	GLfloat bufferZ;							// Here We Will Store The Read Z From The Buffer

	glGetIntegerv (GL_VIEWPORT, viewport);					// Get Actual Viewport
	glGetDoublev (GL_MODELVIEW_MATRIX, mvmatrix);			// Get Actual Model View Matrix
	glGetDoublev (GL_PROJECTION_MATRIX, projmatrix);		// Get Actual Projection Matrix

	// This Asks OGL To Guess The 2D Position Of A 3D Point Inside The Viewport
	gluProject(p.m_x, p.m_y, p.m_z, mvmatrix, projmatrix, viewport, &winx, &winy, &winz);
	flareZ = winz;

	// We Read Back One Pixel From The Depth Buffer (Exactly Where Our Flare Should Be Drawn)
	glReadPixels((GLint)winx, (GLint)winy,1,1,GL_DEPTH_COMPONENT, GL_FLOAT, &bufferZ);

	// If The Buffer Z Is Lower Than Our Flare Guessed Z Then Don't Draw
	// This Means There Is Something In Front Of Our Flare
	if (bufferZ < flareZ)
		return true;
	else
		return false;
}

void CCamera::GetInverseMatrix(float mCameraInverse[16])
{
	float m[16] = {0};

	// Grab the current modelview matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, m);

	// Below we do a little algebra to invert our current modelview matrix.
	// Instead of doing a more complicated method of determining the inverse
	// of a matrix, we can use this simplified version because we assume our
	// matrix is an orthogonal matrix, meaning that each column is perpendicular
	// to the other column.  What we do is remove the translation of the matrix
	// and then multiply it later by the negative translation, which reverses the
	// calculations of the original matrix.
	mCameraInverse[0]  = m[0]; mCameraInverse[1] = m[4]; mCameraInverse[2]  = m[8];
	mCameraInverse[4]  = m[1]; mCameraInverse[5] = m[5]; mCameraInverse[6]  = m[9];
	mCameraInverse[8]  = m[2]; mCameraInverse[9] = m[6]; mCameraInverse[10] = m[10];
	mCameraInverse[3]  = 0.0f; mCameraInverse[7] = 0.0f; mCameraInverse[11] = 0.0f;
	mCameraInverse[15] = 1.0f;

	mCameraInverse[12] = -(m[12] * m[0]) - (m[13] * m[1]) - (m[14] * m[2]);
	mCameraInverse[13] = -(m[12] * m[4]) - (m[13] * m[5]) - (m[14] * m[6]);
	mCameraInverse[14] = -(m[12] * m[8]) - (m[13] * m[9]) - (m[14] * m[10]);
}
////
////CBool CCamera::InitializeLensFlare()
////{
////	//Load halo texture
////	glGenTextures( 1, &m_HaloTexture );
////	if( !commonGL.LoadBitmapTexture( "data/images/level1/lens/halo.sbf", m_HaloTexture ) )
////		return false;
////
////	//Load glow texture
////	glGenTextures( 1, &m_GlowTexture );
////	if( !commonGL.LoadBitmapTexture( "data/images/level1/lens/Glow.sbf" , m_GlowTexture ) )
////		return false;
////
////
////	return true;
////
////}
////
////GLvoid CCamera::RenderLensFlare()
////{
////	CFloat Length;
////
////	// Draw the flare only If the light source is in our line of sight
////	if( SphereInFrustum( m_LightSourcePos, 1.0f ) == true )
////	{
////		// Lets compute the vector that points to the camera from the light source
////        vLightSourceToCamera = m_Position - m_LightSourcePos;		
////        //Find the length of the vector
////		Length = vLightSourceToCamera.Magnitude();
////
////		ptintersect = m_DirectionVector * Length;					// Now lets find an point along the cameras direction
////																	// vector that we can use as an intersection point. 
////																	// Lets translate down this vector the same distance
////																	// that the camera is away from the light source.
////		ptintersect += m_Position;
////
////		vLightSourceTointersect = ptintersect - m_LightSourcePos;	// Lets compute the vector that points to the intersect
////																	// point from the light source
////		Length = vLightSourceTointersect.Magnitude();				// Save the length we will need it later.
////		vLightSourceTointersect.Normalize();						// Normalize the vector so its unit length
////
////		glEnable( GL_TEXTURE_2D );
////		glDisable( GL_DEPTH_TEST );
////
////		if (!IsOccluded(m_LightSourcePos))	//Check if the center of the flare is occluded
////		{
////			pt = vLightSourceTointersect * (Length * 0.2755f);		
////			pt += m_LightSourcePos;									
////		
////			RenderGlow(0.4f, 0.3f, 0.2f, 0.15f, pt, 16.0f);			
////
////			pt = vLightSourceTointersect * (Length * 0.4775f);		
////			pt += m_LightSourcePos;										
////																	
////			RenderGlow(0.53f, 0.32f, 0.13f, 0.15f, pt, 20.0f);		
////		
////			pt = vLightSourceTointersect * (Length * 0.61f);		
////			pt += m_LightSourcePos;									
////		
////			RenderHalo(0.4f, 0.0f, 0.2f, 0.15f, pt, 20.0f);				
////
////			pt = vLightSourceTointersect * (Length * 0.65f);		
////			pt += m_LightSourcePos;						
////																
////			RenderGlow(0.4f, 0.2f, 0.1f, 0.15f, pt, 28.0f);	
////		
////			pt = vLightSourceTointersect * (Length * 0.83f);		
////			pt += m_LightSourcePos;										
////																	
////			RenderGlow(0.4f, 0.3f, 0.2f, 0.15f, pt, 20.0f);			
////
////			pt = vLightSourceTointersect * (Length * 1.1f);			
////			pt += m_LightSourcePos;									
////																
////			RenderHalo(0.0f, 0.0f, 0.5f, 0.1f, pt, 48.0f);				
////		
////			pt = vLightSourceTointersect * (Length * 1.1825f);			
////			pt += m_LightSourcePos;										
////																	
////			RenderGlow(0.4f, 0.1f, 0.0f, 0.15f, pt, 30.0f);				
////
////			pt = vLightSourceTointersect * (Length * 1.5f);				
////			pt += m_LightSourcePos;										
////																	
////			RenderHalo(0.3f, 0.0f, 0.0f, 0.15f, pt, 30.0f);			
////			RenderGlow( 0.3f, 0.0f, 0.4f, 0.15f, pt, 24.0f );
////		
////			pt = vLightSourceTointersect * (Length * 2.1f);		
////			pt += m_LightSourcePos;										
////																	
////			RenderHalo(0.2f, 0.2f, 0.0f, 0.15f, pt, 50.0f);			
////
////			pt = vLightSourceTointersect * (Length * 2.2f);		
////			pt += m_LightSourcePos;									
////
////			RenderGlow( 0.3f, 0.1f, 0.2f, 0.15f, pt, 20.0f );
////		}
////
////		glEnable( GL_DEPTH_TEST );
////        glDisable( GL_TEXTURE_2D );
////	}
////
////}
////
////GLvoid CCamera::ReleaseLensFlare()
////{
////	//Free the texture objects
////	glDeleteTextures( 1, &m_HaloTexture );
////	glDeleteTextures( 1, &m_GlowTexture );
////
////}
////
////GLvoid CCamera::RenderHalo( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
////		               Point CenterPoint, GLfloat scale )
////{
////	glPushAttrib( GL_CURRENT_BIT );
////	glColor3f( red, green, blue );
////	Billboard( CenterPoint.x, CenterPoint.y, CenterPoint.z, m_HaloTexture, scale/2, scale/2 );
////	glPopAttrib();
////}
////
////GLvoid CCamera::RenderGlow( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha,
////						   Point CenterPoint, GLfloat scale )
////{
////	glPushAttrib( GL_CURRENT_BIT );
////	glColor3f( red, green, blue );
////	Billboard( CenterPoint.x, CenterPoint.y, CenterPoint.z, m_GlowTexture, scale/2, scale/2 );
////	glPopAttrib();
////}

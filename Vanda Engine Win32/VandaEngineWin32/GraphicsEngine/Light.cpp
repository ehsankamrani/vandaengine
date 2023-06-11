//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Light.h"

CInstanceLight::CInstanceLight()
{
	if (GLEW_NV_occlusion_query)
	{
		glGenQueries(1, &m_queryIndex);
	}
	m_runTimeVisible = CTrue;
	m_updateEvent = CTrue;
}

CInstanceLight::~CInstanceLight()
{
	glDeleteQueries(1, &m_queryIndex);
}

GLuint CInstanceLight::GetQueryIndex()
{
	return m_queryIndex;
}

CDouble CInstanceLight::GetRadius()
{
	long CDouble radius;

	if( m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL )
	{
		radius = 1000000.0f; //infinit
		return radius;
	}

	CDouble epsilon = 1/g_lightProperties.m_tolerance; 
	long CDouble C = m_abstractLight->GetConstantAttenuation();
	long CDouble L = m_abstractLight->GetLinearAttenuation();
	long CDouble Q = m_abstractLight->GetQuadraticAttenuation();
	if( Q > 0.0 )
		radius = ( -L + sqrt( (L* L)+ ( 4 * Q * ( epsilon - C ) ) ) ) / (2 * Q);
	else if ( L > 0.0 )
		radius = ( epsilon - C ) / L;
	else
		radius = 1000000.0f; //infinit

	return (CDouble)radius;

}

CVoid CInstanceLight::CalculateDistance()
{
	if (!g_camera)
		return;
	if (m_parent)
	{
		float *matrix = (float *)m_parent->GetLocalToWorldMatrix();
		m_position.x = matrix[12]; m_position.y = matrix[13]; m_position.z = matrix[14];
	}
	else
	{
		m_position.x = m_abstractLight->GetPosition()[0];
		m_position.y = m_abstractLight->GetPosition()[1];
		m_position.z = m_abstractLight->GetPosition()[2];
	}

	CFloat x = g_camera->m_perspectiveCameraPos.x - m_position.x;
	CFloat y = g_camera->m_perspectiveCameraPos.y - m_position.y;
	CFloat z = g_camera->m_perspectiveCameraPos.z - m_position.z;

	m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

}

CFloat CInstanceLight::GetDistanceFromCamera()
{
	return m_distanceFromCamera;
}

CVoid CInstanceLight::SetPosition(CVec3f pos)
{
	m_position.x = pos.x;
	m_position.y = pos.y;
	m_position.z = pos.z;
}

CVec3f CInstanceLight::GetPosition()
{
	return m_position;
}

CLight::CLight()
{
	m_color = CColor4f( 0.5f, 0.5f, 0.5f, 1.0f ); //default color
	m_spotCutoff = 180.0f;
	m_spotExponent = 0.0f;
	m_constantAttenuation = 1.0f;
	m_linearAttenuation	= 0.0f;
	m_quadraticAttenuation = 0.0f;
	m_lightType	= eLIGHTTYPE_POINT;

	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);

}

CLight::~CLight()
{
    Destroy(); 
	LuaClose(m_lua);
}

CVoid CLight::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CLight::LoadLuaFile()
{
	//ResetLua();

	if (!m_hasScript)
	{
		return CFalse;
	}

	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

GLvoid CLight::EnableGL()
{
	glEnable( GL_LIGHT0 + m_lightNumber );
}

GLvoid CLight::DisableGL()
{
	glDisable( GL_LIGHT0 + m_lightNumber );
}

GLvoid CLight::SetShininess( GLfloat shininess )
{
	m_shininess = shininess;
}

GLvoid CLight::SetPositionGL( GLfloat* positionArray )
{
	glLightfv( GL_LIGHT0 + m_lightNumber , GL_POSITION, positionArray );
}

GLvoid CLight::SetAmbientGL( GLfloat* ambientArray )
{
	glLightfv( GL_LIGHT0 + m_lightNumber , GL_AMBIENT, ambientArray );
}

GLvoid CLight::SetDiffuseGL( GLfloat* diffuseArray )
{
	glLightfv( GL_LIGHT0 + m_lightNumber , GL_DIFFUSE, diffuseArray );
}

GLvoid CLight::SetSpecularGL( GLfloat* specularArray )
{
	glLightfv( GL_LIGHT0 + m_lightNumber , GL_SPECULAR, specularArray );
}

GLvoid CLight::SetSpotDirectionGL( GLfloat* spotArray )
{
	glLightfv( GL_LIGHT0 + m_lightNumber , GL_SPOT_DIRECTION, spotArray );
}

GLvoid CLight::SetSpotCutoffGL( GLfloat angle )
{
	glLightf( GL_LIGHT0 + m_lightNumber , GL_SPOT_CUTOFF, angle );
}

GLvoid CLight::SetSpotExponentGL( GLfloat exponent )
{
	glLightf( GL_LIGHT0 + m_lightNumber , GL_SPOT_EXPONENT, exponent );
}

GLvoid CLight::SetConstantAttenuationGL( GLfloat factor )
{
	glLightf( GL_LIGHT0 + m_lightNumber , GL_CONSTANT_ATTENUATION, factor );
}

GLvoid CLight::SetLinearAttenuationGL( GLfloat factor )
{
	glLightf( GL_LIGHT0 + m_lightNumber , GL_LINEAR_ATTENUATION, factor );
}

GLvoid CLight::SetQuadraticAttenuationGL( GLfloat factor )
{
	glLightf( GL_LIGHT0 + m_lightNumber , GL_QUADRATIC_ATTENUATION, factor );
}

GLvoid CLight::ResetGL()
{
	if( m_lightNumber == 0 )
	{

		GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );

		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	}
	else
	{
		GLfloat diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightfv( GL_LIGHT0 + m_lightNumber, GL_DIFFUSE, diffuse );

		GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightfv( GL_LIGHT0 + m_lightNumber, GL_SPECULAR, specular );
	}

	GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv( GL_LIGHT0 + m_lightNumber, GL_AMBIENT, ambient );

	GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0 };
	glLightfv( GL_LIGHT0 + m_lightNumber, GL_POSITION, position );

	GLfloat spotDirection[] = { 0.0f, 0.0f, -1.0f };
	glLightfv( GL_LIGHT0 + m_lightNumber, GL_SPOT_DIRECTION, spotDirection );

	glLightf( GL_LIGHT0 + m_lightNumber, GL_SPOT_EXPONENT, 0.0f );

	glLightf( GL_LIGHT0 + m_lightNumber, GL_SPOT_CUTOFF, 180.0f );

	glLightf( GL_LIGHT0 + m_lightNumber, GL_CONSTANT_ATTENUATION, 1.0f );

	glLightf( GL_LIGHT0 + m_lightNumber, GL_LINEAR_ATTENUATION, 0.0f );

	glLightf( GL_LIGHT0 + m_lightNumber, GL_QUADRATIC_ATTENUATION, 0.0f );
}

//These functions just fill the private data of the class. The user must then use an appropriate API to use these values

GLvoid CLight::SetPosition( GLfloat* positionArray )
{
	m_position[0] = positionArray[0];
	m_position[1] = positionArray[1];
	m_position[2] = positionArray[2];
	m_position[3] = positionArray[3];

}

GLvoid CLight::SetAmbient( GLfloat* ambientArray )
{
	m_ambient[0] = ambientArray[0];
	m_ambient[1] = ambientArray[1];
	m_ambient[2] = ambientArray[2];
	m_ambient[3] = ambientArray[3];
}

GLvoid CLight::SetDiffuse( GLfloat* diffuseArray )
{
	m_diffuse[0] = diffuseArray[0];
	m_diffuse[1] = diffuseArray[1];
	m_diffuse[2] = diffuseArray[2];
	m_diffuse[3] = diffuseArray[3];
}

GLvoid CLight::SetSpecular( GLfloat* specularArray )
{
	m_specular[0] = specularArray[0];
	m_specular[1] = specularArray[1];
	m_specular[2] = specularArray[2];
	m_specular[3] = specularArray[3];
}
GLvoid CLight::SetSpotDirection( GLfloat* spotDirectionArray )
{
	m_spotDirection[0] = spotDirectionArray[0];
	m_spotDirection[1] = spotDirectionArray[1];
	m_spotDirection[2] = spotDirectionArray[2];
	m_spotDirection[3] = spotDirectionArray[3];
}
GLvoid CLight::SetSpotCutoff( GLfloat cutoff )
{
	m_spotCutoff = cutoff;
}
GLvoid CLight::SetSpotExponent( GLfloat exponent )
{
	m_spotExponent = exponent;
}
GLvoid CLight::SetConstantAttenuation( GLfloat cFactor )
{
	m_constantAttenuation = cFactor;
}
GLvoid CLight::SetLinearAttenuation( GLfloat lFactor )
{
	m_linearAttenuation = lFactor;
}
GLvoid CLight::SetQuadraticAttenuation( GLfloat qFactor )
{
	m_quadraticAttenuation = qFactor;
}

//This function is specially used for Collada format
CVoid CLight::SetColor( CColor4f& color )
{
	m_color = color;
	CFloat diffuse[4] = { color.r, color.g, color.b, color.a };
	CFloat specular[4] = { g_lightProperties.m_specularColor[0], g_lightProperties.m_specularColor[1], g_lightProperties.m_specularColor[2], g_lightProperties.m_specularColor[3] };
	CFloat ambient[4] = {g_lightProperties.m_ambientColor[0], g_lightProperties.m_ambientColor[1], g_lightProperties.m_ambientColor[2], g_lightProperties.m_ambientColor[3] }; //It seems that collada doesn't specify the ambient property
	SetAmbient( ambient );
	SetDiffuse( diffuse );
	SetSpecular( specular );
	SetShininess(g_lightProperties.m_shininess);
}

CVoid CLight::SetLightNumber( CInt lightNumber )
{
	m_lightNumber = lightNumber;
}

CVoid CLight::SetType(CLightType type)
{
	m_lightType = type;
}

//These function are used to get the information
CFloat* CLight::GetPosition()
{
	return m_position;
}
CFloat* CLight::GetAmbient()
{
	return m_ambient;
}
CFloat* CLight::GetDiffuse()
{
	return m_diffuse;
}
CFloat* CLight::GetSpecular()
{
	return m_specular;
}
CFloat* CLight::GetSpotDirection()
{
	return m_spotDirection;
}
CFloat CLight::GetSpotCutoff()
{
	return m_spotCutoff;
}
CFloat CLight::GetSpotExponent()
{
	return m_spotExponent;
}
CFloat CLight::GetConstantAttenuation()
{
	return m_constantAttenuation;
}
CFloat CLight::GetLinearAttenuation()
{
	return m_linearAttenuation;
}
CFloat CLight::GetQuadraticAttenuation()
{
	return m_quadraticAttenuation;
}

CColor4f CLight::GetColor()
{
	return m_color;
}

CInt CLight::GetLightNumber()
{
	return m_lightNumber;
}

CLightType CLight::GetType()
{
	return m_lightType;
}

CFloat CLight::GetShininess()
{
	return m_shininess;
}

CChar* CLight::GetScriptStringVariable(CChar* variableName)
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

CBool CLight::GetScriptBoolVariable(CChar* variableName)
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

CInt CLight::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CLight::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CLight::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CLight::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CLight::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CLight::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CLight::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = this;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CLight::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;
		g_currentWater = NULL;
		g_currentLight = this;
		g_currentEngineCamera = NULL;
		g_currentVideo = NULL;
		g_current3DSound = NULL;
		g_currentAmbientSound = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

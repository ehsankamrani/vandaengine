//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "..\common\utility.h"
#include "base.h"
#include "opengl.h"
#include "node.h"

class CLight;


/* The CInstanceLight class holds the information needed to make an instance of an abstract light.
 *  This maps to the <instance_light> tag in COLLADA
 *  NOTE: This assumes that all light instances that reference the same CLight are sharing the info
 *  in that abstract light, ie: if someone changes the stuff in the CLight all the instances derived
 *  from it will change.  We could avoid this by keeping a copy of CLight in the instance.
 */

class CInstanceLight
{
public:
	CInstanceLight();
	~CInstanceLight();
	CNode *m_parent;			
	CLight *m_abstractLight;
	CInt m_nameIndex;
	CFloat m_lodPercent;
	GLuint m_queryIndex;
	CVec3f m_position;
	CFloat m_distanceFromCamera;
	CBool m_runTimeVisible;

	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CInt GetIndex() { return m_nameIndex; }
	CBool RenderIcon(CBool selectionMode = CFalse);
	CBool RenderExtents();
	CDouble GetRadius();
	GLuint GetQueryIndex();
	CVoid SetLODPercent(CFloat percent) { m_lodPercent = percent; }
	CFloat GetLODPercent() { return m_lodPercent; }
	CVoid CalculateDistance();
	CFloat GetDistanceFromCamera();
	CVoid SetPosition(CVec3f pos);
	CVec3f GetPosition();
	CVoid SetRunTimeVisible(CBool set) { m_runTimeVisible = set; }
	CBool GetRunTimeVisible() { return m_runTimeVisible; }
	CVoid SetUpdateEvent(CBool set) { m_updateEvent = set; }
	CBool GetUpdateEvent() { return m_updateEvent; }
private:
	CBool m_updateEvent;

};

class CLight : public CBase 
{
public:
	CLight();
	~CLight();
public:
	CColor4f m_color;				// The color of the light (all types)
	CFloat m_constantAttenuation;	// Constant attenuation factor (point and spot)
	CFloat m_linearAttenuation;	    // Linear attenuation factor (point and spot)
	CFloat m_quadraticAttenuation;	// Quadratic attenuation factor (point and spot)
	CFloat m_shininess;
	CFloat m_spotCutoff;
	CFloat m_spotDirection[4];
	CFloat m_spotExponent;
	CFloat m_position[4];
	CFloat m_ambient[4];
	CFloat m_diffuse[4];
	CFloat m_specular[4];
	CLightType m_lightType;
	CInt m_lightNumber;
	CChar m_lastName[MAX_NAME_SIZE];

public:
	CLightType GetType();
	CVoid SetType(CLightType type);
	CColor4f	GetColor();
	CInstanceLight* m_instanceLight;
public:
	CVoid Update( CInt light );

	//These function with gl prefixes use direct OpenGL function to set the data
	GLvoid SetPositionGL( GLfloat* positionArray );
	GLvoid SetAmbientGL( GLfloat* ambientArray );
	GLvoid SetDiffuseGL( GLfloat* diffuseArray );
	GLvoid SetSpecularGL( GLfloat* specularArray );
	GLvoid SetSpotDirectionGL( GLfloat* spotArray );
	GLvoid SetSpotCutoffGL( GLfloat angle );
	GLvoid SetSpotExponentGL( GLfloat exponent );
	GLvoid SetConstantAttenuationGL( GLfloat factor );
	GLvoid SetLinearAttenuationGL( GLfloat factor );
	GLvoid SetQuadraticAttenuationGL( GLfloat facor );

	GLvoid ResetGL();
    GLvoid EnableGL();
	GLvoid DisableGL();
	
	//These functions just fill the private data of the class. The user must then use an appropriate API to use these values
	CVoid SetPosition( CFloat* positionArray );
	CVoid SetAmbient( CFloat* ambientArray );
	CVoid SetDiffuse( CFloat* diffuseArray );
	CVoid SetSpecular( CFloat* specularArray );
	CVoid SetSpotDirection( CFloat* spotDirectionArray );
	CVoid SetSpotCutoff( CFloat cutoff );
	CVoid SetSpotExponent( CFloat spotExponent );
	CVoid SetShininess( CFloat shininess );
	CVoid SetConstantAttenuation( CFloat factor );
	CVoid SetLinearAttenuation( CFloat factor );
	CVoid SetQuadraticAttenuation( CFloat facor );
	CVoid SetColor( CColor4f& color, CBool setDiffuse = CTrue );
	CVoid SetLightNumber( CInt lightNumber );

	CFloat* GetPosition();
	CFloat* GetAmbient();
	CFloat* GetDiffuse();
	CFloat* GetSpecular();
	CFloat* GetSpotDirection();
	CFloat GetSpotCutoff();
	CFloat GetSpotExponent();
	CFloat GetConstantAttenuation();
	CFloat GetLinearAttenuation();
	CFloat GetQuadraticAttenuation();
	CInt GetLightNumber();
	CFloat GetShininess();

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

	CVoid ResetLua();
	CBool LoadLuaFile();

	CChar* GetLastName();
	CVoid SetLastName(CChar* name);

private:
	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];

};



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
	CBool m_visible;
	GLuint m_queryIndex;
	CVec3f m_position;
	CFloat m_distanceFromCamera;

	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CInt GetIndex() { return m_nameIndex; }
	CBool RenderIcon(CBool selectionMode = CFalse);
	CBool RenderExtents();
	CDouble GetRadius();
	GLuint GetQueryIndex();
	CVoid SetVisible(CBool visible) { m_visible = visible; }
	CBool GetVisible() { return m_visible; }
	CVoid CalculateDistance();
	CFloat GetDistanceFromCamera();
	CVoid SetPosition(CVec3f pos);

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


public:
	CLightType GetType();
	CVoid SetType(CLightType type);
	CColor4f	GetColor();
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
	CInt SetLightNumber( CInt lightNumber );

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
};



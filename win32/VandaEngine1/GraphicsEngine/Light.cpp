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

#include "stdafx.h"
#include "Light.h"

CInstanceLight::CInstanceLight()
{
	glGenQueries(1, &m_queryIndex);
	m_visible = CTrue;
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

CLight::CLight()
{
	m_color = CColor4f( 0.5f, 0.5f, 0.5f, 1.0f ); //default color
	m_spotCutoff = 180.0f;
	m_spotExponent = 0.0f;
	m_constantAttenuation = 1.0f;
	m_linearAttenuation	= 0.0f;
	m_quadraticAttenuation = 0.0f;
	m_lightType	= eLIGHTTYPE_POINT;
}

CLight::~CLight()
{
    Destroy(); 
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

CInt CLight::SetLightNumber( CInt lightNumber )
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
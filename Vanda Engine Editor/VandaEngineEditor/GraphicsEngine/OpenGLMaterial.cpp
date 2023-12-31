//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenGLMaterial.h"

GLvoid COpenGLMaterial::SetFrontAmbient( GLfloat* ambient )
{
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
}

GLvoid COpenGLMaterial::SetBackAmbient( GLfloat* ambient )
{
	glMaterialfv( GL_BACK, GL_AMBIENT, ambient );
}

GLvoid COpenGLMaterial::SetFrontDiffuse( GLfloat* diffuse )
{
	glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
}

GLvoid COpenGLMaterial::SetBackDiffuse( GLfloat* diffuse )
{
	glMaterialfv( GL_BACK, GL_DIFFUSE, diffuse );
}

GLvoid COpenGLMaterial::SetFrontSpecular( GLfloat* specular )
{
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
}

GLvoid COpenGLMaterial::SetBackSpecular( GLfloat* specular )
{
	glMaterialfv( GL_BACK, GL_SPECULAR, specular );
}

GLvoid COpenGLMaterial::SetFrontShininess( GLfloat shininess )
{
	glMaterialf( GL_FRONT, GL_SHININESS, shininess );
}

GLvoid COpenGLMaterial::SetBackShininess( GLfloat shininess )
{
	glMaterialf( GL_BACK, GL_SHININESS, shininess );
}

GLvoid COpenGLMaterial::SetFrontEmission( GLfloat emission )
{
	glMaterialf( GL_FRONT, GL_EMISSION, emission );
}

GLvoid COpenGLMaterial::SetBackEmission( GLfloat emission )
{
	glMaterialf( GL_BACK, GL_EMISSION, emission );
}
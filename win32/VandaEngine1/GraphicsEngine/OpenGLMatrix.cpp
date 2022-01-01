//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "OpenGLMatrix.h"

GLvoid COpenGLMatrix::SetModelView()
{
	glMatrixMode( GL_MODELVIEW );
}

GLvoid COpenGLMatrix::SetProjection()
{
	glMatrixMode( GL_PROJECTION );
}

GLvoid COpenGLMatrix::SetTexture()
{
	glMatrixMode( GL_TEXTURE );
}

GLvoid COpenGLMatrix::SetInit()
{
	glLoadIdentity();
}

GLvoid COpenGLMatrix::SetTranslate( GLfloat tx, GLfloat ty, GLfloat tz )
{
	glTranslatef( tx, ty, tz );
}

GLvoid COpenGLMatrix::SetRotate( GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz )
{
	glRotatef( angle, rx, ry, rz );
}

GLvoid COpenGLMatrix::SetRotateX( GLfloat angle )
{
	glRotatef( angle, 1.0f, 0.0f, 0.0f );
}

GLvoid COpenGLMatrix::SetRotateY( GLfloat angle )
{
	glRotatef( angle, 0.0f, 1.0f, 0.0f );
}

GLvoid COpenGLMatrix::SetRotateZ( GLfloat angle )
{
	glRotatef( angle, 0.0f, 0.0f, 1.0f );
}

GLvoid COpenGLMatrix::SetScale( GLfloat sx, GLfloat sy, GLfloat sz )
{
	glScalef( sx, sy, sz );
}

GLvoid COpenGLMatrix::SetPush()
{
	glPushMatrix();
}

GLvoid COpenGLMatrix::SetPop()
{
	glPopMatrix();
}

GLvoid COpenGLMatrix::LoadMatrix( CFloat * mat )
{
	glLoadMatrixf( mat );
}

//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "OpenGL.h"

class COpenGLMatrix
{
public:
    GLvoid SetTranslate( GLfloat x, GLfloat y, GLfloat z );
	GLvoid SetRotateX( GLfloat angle );
	GLvoid SetRotateY( GLfloat angle );
	GLvoid SetRotateZ( GLfloat angle );
	GLvoid SetRotate( GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz );
    GLvoid SetScale( GLfloat sx, GLfloat sy, GLfloat sz );
	GLvoid SetProjection();
	GLvoid SetModelView();
	GLvoid SetTexture();
	GLvoid LoadMatrix( CFloat * mat );
	GLvoid SetInit();
	GLvoid SetPush();
	GLvoid SetPop();
};


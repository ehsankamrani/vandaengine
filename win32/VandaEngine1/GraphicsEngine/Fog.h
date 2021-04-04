//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once 

#include "OpenGL.h"

class CFog
{
public:
	GLvoid Enable(CBool enable);
	GLvoid SetColor( GLfloat* color );
	GLvoid SetDensity( GLfloat density );
	GLvoid SetStart( GLfloat start );
	GLvoid SetEnd( GLfloat end );
	GLvoid SetMode( GLenum mode );
};

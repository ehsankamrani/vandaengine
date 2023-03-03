//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/**************************************************
*****************HOW TO USE FOG******************
******Docment Written by Ehsan Kamrani ***********

Files:
..\GraphicsEngine\Fog.h
..\GraphicsEngine\Fog.cpp

Usage:
1)Include the header file:
   #include "GraphicsEngine\fog.h"

2)Define a fog object:
   CFog fog

3) call the functions( see the functions of this class ).
************************************************/

#include "stdafx.h"
#include "fog.h"

GLvoid CFog::Enable(CBool enable)
{
	if( enable )
		glEnable( GL_FOG );
	else
		glDisable( GL_FOG );
}

GLvoid CFog::SetColor( GLfloat* color )
{
	glFogfv( GL_FOG_COLOR, color );
}

GLvoid CFog::SetDensity( GLfloat density )
{
	glFogf( GL_FOG_DENSITY, density );
}

GLvoid CFog::SetStart( GLfloat start )
{
	glFogf( GL_FOG_START, start );
}

GLvoid CFog::SetEnd( GLfloat end )
{
	glFogf( GL_FOG_END, end );
}

GLvoid CFog::SetMode( GLenum mode )
{
	glFogi( GL_FOG_MODE, mode );
}

//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/*************************************************
***********HOW TO USE COMMON FUNCTIONS***********
******Docment Written by Ehsan Kamrani ***********

Files:
..\GraphicsEngine\OpenGLUtility.h
..\GraphicsEngine\OpenGLUtility.cpp

Usage:
1)Include the header file:
   #include "GraphicsEngine\OpenGLUtility.h"

2)To load a bitmap texture:
   GLuint value;
   value = glGenLists( 1 );   //Generate one unique value
   CLoadBitmapTexture( "Your_File.bmp", value );
   glBindTexture( GL_TEXTURE_2D, value );
   //Draw your object with this texture here

3)To load a targa texture:
   GLuint value;
   value = glGenLists( 1 );   //Generate one unique value
   CLoadTargaTexture( "Your_File.tga", value );
   glBindTexture( GL_TEXTURE_2D, value );
   //Draw your object with this texture here

4)To daw a quad, call the function drawQuad( CFloat *P );
p is an array that consist of 4 points. See the following example:
   	CFloat Sky[] = { 0.0f,0.0f, -800.0f,70.0f,800.0f,
                   3.0f,0.0f, -800.0f,70.0f,-800.0f,
				   3.0f,3.0f, 800.0f,70.0f,-800.0f,
				   0.0f,3.0f, 800.0f,70.0f,800.0f};

	glBindTexture(GL_TEXTURE_2D, SKY_TEXTURE );
    CDrawQuad( sky );  

5)By defalut we have choosen no bits for stencil buffer. For more information,
see the raster class. you should specify the stencil bits explicitly.
( common values are 16 and 32;more bits = more memory;-) ).
In the function StencilPattern:
 n= Number of vertics
 array= array of the stencil pattern that consist of n points
 type= type of the pattern( POLYGON, QUAD )
 bit = 0 or 1.
example:
CFloat houseStencilPatternA[] =
{ -3.0f,0.0f,-1.0f,
-3.0f,0.0f,1.0f,
-3.0f,2.0f,1.0f,
-3.0f,2.7f,0.0f,
-3.0f,2.0f,-1.0f };   // n = 5 = five points.

CStencilPattern( 5, houseStencilPatternA, POLYGON, 1 );

//Then do everything and then disable the stencil buffer:
glDisable( GL_STENCIL_TEST );

Note: you do not need to enable the stencil pattern before 
calling the function CStencilPattern().It enables the stencil
pattern imlicitely. 

6)To use billboarding, call the function CBillboarding().
p1, p2 and p3 are the center of your object to be affected 
by this function. size is the size of your object.and texID
is the texture id.

************************************************/
#pragma once 

#define NOMINMAX

#include <fstream>
#include "OpenGL.h"
#include "targa.h" //advanced texture loader
#include "..\common\vector.h"
#include "..\common\defines.h"
class COpenGLUtility
{
public:
	CVoid InitGLEW();
	CVoid GetGLInfo();
	GLvoid DrawCWBoxWithLines( CVector &min, CVector &max, CVector color );
	GLvoid DrawCWBoxWithQuads( CVector &min, CVector &max );
	GLvoid DrawCCWBox( CVector &min, CVector &max, CBool boundingBox, CBool selectionMode );
	GLvoid DrawCube( GLdouble size, CFloat* pos );
	GLvoid DrawSphere( GLdouble radius, GLint slices, GLint stacks, CFloat* pos, CFloat* diffuseColor );
	GLvoid DrawSolidSphere(GLdouble radius, GLint slices, GLint stacks, CFloat* pos, CFloat* diffuseColor);
	GLvoid DrawCone( GLdouble base, GLint height, GLint slices, GLint stacks, CFloat* diffuseColor );
	GLvoid DrawQuad( CFloat* p );
	GLvoid Billboarding( CFloat p1, CFloat p2, CFloat p3, GLuint texID, CFloat sizex, CFloat sizey, CFloat r = 1.0, CFloat g = 1.0, CFloat b = 1.0);
	GLvoid BillboardingWithUserVectors( CFloat centerX, CFloat centerY, CFloat centerZ, GLuint texID, CFloat sizeX, CFloat sizeY,  CVector& up,  CVector& right );
    GLvoid StencilPattern( CInt n, CFloat* array, COpenGLShape type, CInt bit );
	CInt WriteTGAFile( CChar *fileName, CInt16 CInt width, CInt16 CInt height, CUChar* imageData );
	CVoid SaveScreenShot( CChar* fileName, CInt16 CInt width, CInt16 CInt height );

	//VBO functions here
	CBool CheckForVBOs();
	CInt GenerateVBO();
	CBool CopyVBOData( CUInt type, CUInt vboId, CVoid * data, CInt size );
	CBool BindVBO( CUInt type, CUInt vboId );
	CVoid FreeVBO( CUInt vboId );

	//FBO functions

};

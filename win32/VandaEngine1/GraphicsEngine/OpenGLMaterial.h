//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "OpenGL.h"

class COpenGLMaterial
{
public:
    GLvoid SetFrontAmbient( GLfloat* ambient );
	GLvoid SetBackAmbient( GLfloat* ambient );
	GLvoid SetFrontDiffuse( GLfloat* diffuse );
	GLvoid SetBackDiffuse( GLfloat* diffuse );
	GLvoid SetFrontSpecular( GLfloat* specular );
	GLvoid SetBackSpecular( GLfloat* specular );
	GLvoid SetFrontShininess( GLfloat shininess );
	GLvoid SetBackShininess( GLfloat shininess );
	GLvoid SetFrontEmission( GLfloat emission );
	GLvoid SetBackEmission( GLfloat emission );
};


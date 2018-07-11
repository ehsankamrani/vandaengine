//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include <windows.h>
#include "OpenGL.h"

class CSimpleFont
{
public:
	bool Init( CChar* fontName, int fontSize );
	void Release();
	void Print( char* string, GLfloat xPos, GLfloat yPos, GLfloat zPos, float r, float g, float b );
	void StartRendering(GLdouble w = 768.0f, GLdouble height = 1024.0f);
	void EndRendering();

private:
	HDC hdc;
	HFONT hFont;
	GLuint base;
};



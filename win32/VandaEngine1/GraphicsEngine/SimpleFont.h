//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include <windows.h>
#include "OpenGL.h"

class CFont
{
public:
	bool Init( LPCWSTR fontName, int fontSize );
	void Release();
	void Print(char* string, GLfloat xPos, GLfloat yPos, GLfloat zPos, float r, float g, float b, bool selectionMode = false);
	void StartRendering(GLdouble width = 768.0f, GLdouble height = 1024.0f);
	void EndRendering();

private:
	HDC hdc;
	HFONT hFont;
	GLuint base;
	int m_fontSize;
};



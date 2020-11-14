//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "SimpleFont.h"

bool CSimpleFont::Init( CChar* fontName, int fontSize )
{
	m_fontSize = fontSize;
	//hdc = CreateCompatibleDC(0);
	hdc = GetDC(NULL);
	if( !hdc )
	{
		//MessageBox( NULL, "CFont Class:Couldn't create compatible DC", "VandaEngine Error", MB_OK | MB_ICONERROR );
		return false;
	}
	base = glGenLists( 96 );
	if( !base )
	{
		//MessageBox( NULL, "CFont Class:Couldn't create the list", "VandaEngine Error", MB_OK | MB_ICONERROR );
		return false;

	}

	hFont = CreateFont( fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
		fontName );
	if( !hFont )
	{
		//MessageBox( NULL, "CFont Class:Couldn't create the requested font", "VandaEngine Error", MB_OK | MB_ICONERROR );
		return false;
	}
	SelectObject( hdc, hFont );
	if (!wglUseFontBitmaps(hdc, 32, 96, base))
	{
		//MessageBox(NULL, "wglUseFontBitmaps Failed!", "VandaEngine Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}

void CSimpleFont::Release()
{
	if( hFont )
        DeleteObject( hFont );
	if( base != 0 )
	glDeleteLists( base, 96 );
}

void CSimpleFont::Print( char* string, GLfloat xPos, GLfloat yPos, GLfloat zPos, float r, float g, float b, bool selectionMode )
{
	if (selectionMode)
	{
		glUseProgram(0);

		glBegin(GL_QUADS);
		glVertex3f(xPos, yPos, 0.0f);
		glVertex3f(xPos + (strlen(string) * m_fontSize * 0.5f), yPos, 0.0f);
		glVertex3f(xPos + (strlen(string) * m_fontSize * 0.5f), yPos + m_fontSize, 0.0f);
		glVertex3f(xPos, yPos + m_fontSize, 0.0f);
		glEnd();
	}
	else
	{
		glUseProgram(0);
		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIST_BASE);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glColor3f(r, g, b);
		glRasterPos3f(xPos, yPos, zPos);
		glListBase(base - 32);
		glCallLists((GLsizei)strlen(string), GL_UNSIGNED_BYTE, string);
		glPopAttrib();
	}
}

void CSimpleFont::StartRendering(GLdouble width, GLdouble height)
{
	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void CSimpleFont::EndRendering()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
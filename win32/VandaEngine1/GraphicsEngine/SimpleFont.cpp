//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "SimpleFont.h"

bool CFont::Init( LPCWSTR fontName, int fontSize )
{
	m_fontSize = fontSize;
	//hdc = CreateCompatibleDC(0);
	hdc = GetDC(NULL);

	if( !hdc )
	{
		//MessageBoxW( NULL, _T("CFont Class:Couldn't create compatible DC"), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return false;
	}
	base = glGenLists( 96 );
	if( !base )
	{
		//MessageBoxW( NULL, _T("CFont Class:Couldn't create the list"), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return false;

	}

	hFont = CreateFont( fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH,
		fontName );
	if( !hFont )
	{
		//MessageBoxW( NULL, _T("CFont Class:Couldn't create the requested font"), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
		return false;
	}
	SelectObject( hdc, hFont );
	if(!wglUseFontBitmaps( hdc, 32, 96, base ))
	{
		//MessageBoxA(NULL, "wglUseFontBitmaps Failed!", "VandaEngine Error", MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void CFont::Release()
{
	if( hFont )
        DeleteObject( hFont );
	if( base != 0 )
	glDeleteLists( base, 96 );
}

void CFont::Print(char* string, GLfloat xPos, GLfloat yPos, GLfloat zPos, float r, float g, float b, bool selectionMode)
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
		glPushAttrib(GL_CURRENT_BIT);
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glColor3f(r, g, b);
		glRasterPos3f(xPos, yPos, zPos);
		glPushAttrib(GL_LIST_BASE);
		glListBase(base - 32);
		glCallLists((GLsizei)strlen(string), GL_UNSIGNED_BYTE, string);
		glPopAttrib();//GL_LIST_BASE
		glPopAttrib();//GL_ENABLE_BIT
		glPopAttrib();//GL_CURRENT_BIT
	}
}

void CFont::StartRendering(GLdouble widht, GLdouble height)
{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, widht, 0.0, height, -1.0, 1.0);
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
}

void CFont::EndRendering()
{
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}
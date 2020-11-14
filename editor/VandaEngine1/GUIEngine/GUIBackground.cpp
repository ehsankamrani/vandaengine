//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CAddAmbientSound.cpp : implementation file
//

#include "stdafx.h"
#include "..\\VandaEngine1.h"
#include "GUIBackground.h"

CGUIBackground::CGUIBackground()
{
	m_image = NULL;
	m_updateImage = CFalse;
	SetIndex();
}

CGUIBackground::~CGUIBackground()
{
	CDelete(m_image);
}

CBool CGUIBackground::LoadBackgroundImage()
{
	if (m_image)
		CDelete(m_image);
	m_image = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_image, m_imagePath, NULL))
	{
		PrintInfo("Couldn't load the image", COLOR_RED);
		CDelete(m_image);
		return CFalse;
	}
	return CTrue;
}

CVoid CGUIBackground::Render(CBool selectionMode)
{
	CFloat w;
	if (g_editorMode == eMODE_GUI || (g_editorMode == eMODE_VSCENE && g_menu.m_justPerspective))
		w = m_size * g_width / 100.0f;
	else if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
		w = m_size * g_width / 200.0f;

	CFloat h = (w / m_image->GetWidth() ) * m_image->GetHeight();

	if (selectionMode)
	{
		glPushName(m_nameIndex);
		glUseProgram(0);

		if (g_editorMode == eMODE_GUI || (g_editorMode == eMODE_VSCENE && g_menu.m_justPerspective))
		{
			glBegin(GL_QUADS);
			glVertex3f(m_position.x, m_position.y - h, -1.0f);
			glVertex3f(m_position.x + w, m_position.y - h, -1.0f);
			glVertex3f(m_position.x + w, m_position.y, -1.0f);
			glVertex3f(m_position.x, m_position.y, -1.0f);
			glEnd();
		}
		else if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
		{
			glBegin(GL_QUADS);
			glVertex3f(m_position.x * 0.5f, m_position.y * 0.5f - h, -1.0f);
			glVertex3f(m_position.x * 0.5f + w, m_position.y * 0.5f - h, -1.0f);
			glVertex3f(m_position.x * 0.5f + w, m_position.y * 0.5f, -1.0f);
			glVertex3f(m_position.x * 0.5f, m_position.y * 0.5f, -1.0f);
			glEnd();
		}

		glPopName();
		return;
	}

	glUseProgram(0);

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_VIEWPORT_BIT);
	glViewport(0, 0, g_width, g_height);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, g_width, 0.0, g_height, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	//Upper Left: Position.x, Position.y


	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, m_image->GetId());

	if (m_image->GetFormat() == 4)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (g_editorMode == eMODE_GUI || (g_editorMode == eMODE_VSCENE && g_menu.m_justPerspective))
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1);  glVertex3f(m_position.x, m_position.y, -1.0f);
		glTexCoord2d(1, 1);  glVertex3f(m_position.x + w, m_position.y, -1.0f);
		glTexCoord2d(1, 0);  glVertex3f(m_position.x + w, m_position.y - h, -1.0f);
		glTexCoord2d(0, 0);  glVertex3f(m_position.x, m_position.y - h, -1.0f);
		glEnd();
	}
	else if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1);  glVertex3f(m_position.x * 0.5f, m_position.y * 0.5f, -1.0f);
		glTexCoord2d(1, 1);  glVertex3f(m_position.x * 0.5f + w, m_position.y * 0.5f, -1.0f);
		glTexCoord2d(1, 0);  glVertex3f(m_position.x * 0.5f + w, m_position.y * 0.5f - h, -1.0f);
		glTexCoord2d(0, 0);  glVertex3f(m_position.x * 0.5f, m_position.y * 0.5f - h, -1.0f);
		glEnd();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();
}

CVec2f CGUIBackground::SetPosition(CVec2f pos)
{
	if (m_image)
	{
		CFloat w = m_size * g_width / 100.0f;
		CFloat h = (w / m_image->GetWidth()) * m_image->GetHeight();

		m_position.x = pos.x;
		if (m_position.x < 0.0)
			m_position.x = 0.0;
		else if (m_position.x > g_multipleView->m_width - w)
			m_position.x = g_multipleView->m_width - w;

		m_position.y = pos.y;

		if (m_position.y <  h)
			m_position.y = h;
		else if (m_position.y > g_multipleView->m_height)
			m_position.y = g_multipleView->m_height;
	}
	else
	{
		m_position = pos;
	}
	return m_position;
}

CVoid CGUIBackground::SetPosition2(CVec2f pos)
{
	if (m_image)
	{
		CFloat w = m_size * g_width / 100.0f;
		CFloat h = (w / m_image->GetWidth()) * m_image->GetHeight();

		m_position.x += pos.x;
		if (m_position.x < 0.0)
			m_position.x = 0.0;
		else if (m_position.x > g_multipleView->m_width - w)
			m_position.x = g_multipleView->m_width - w;

		m_position.y -= pos.y;

		if (m_position.y <  h)
			m_position.y = h;
		else if (m_position.y > g_multipleView->m_height)
			m_position.y = g_multipleView->m_height;
	}
	else
	{
		m_position.x += pos.x;
		m_position.y -= pos.y;
	}

}


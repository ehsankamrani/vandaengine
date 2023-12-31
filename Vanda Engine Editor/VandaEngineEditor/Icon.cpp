//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Icon.h"
#include "VandaEngineEditorDlg.h"

CIcon::CIcon()
{
	m_visible = CFalse;
	Cpy(m_name, "\n");
	m_image = NULL;
	m_size = 3; //3 percents of the screen width
}


CIcon::~CIcon()
{
}

CVoid CIcon::SetImage(CImage* image)
{
	m_image = image;
}

CVoid CIcon::Render(CVec2f pos)
{
	if (!GetVisible())
		return;

	CFloat w = m_size * g_width / 100.0f;
	CFloat h = (w / m_image->GetWidth()) * m_image->GetHeight();

	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, g_width, 0.0, g_height, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_VIEWPORT_BIT);
	glViewport(0, 0, g_width, g_height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	//Upper Left: Position.x, Position.y


	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_image->GetId());

	if (m_image->GetFormat() == 4)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
	}

	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);  glVertex3f(pos.x - (w / 2.0f), pos.y + (h / 2.0f), -1.0f);
	glTexCoord2d(1, 1);  glVertex3f(pos.x + w - (w / 2.0f), pos.y + (h / 2.0f), -1.0f);
	glTexCoord2d(1, 0);  glVertex3f(pos.x + w - (w / 2.0f), pos.y - h + (h / 2.0f), -1.0f);
	glTexCoord2d(0, 0);  glVertex3f(pos.x - (w / 2.0f), pos.y - h + (h / 2.0f), -1.0f);
	glEnd();

	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

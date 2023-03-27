//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CGUIImage.cpp : implementation file
//
#include "stdafx.h"
#include "GUIImage.h"
#include "../Main.h"

CGUIImage::CGUIImage()
{
	m_image = NULL;
	m_updateImage = CFalse;
	m_visible = CTrue;
	m_scale = 1.0;
	SetIndex();
}

CGUIImage::~CGUIImage()
{
	CDelete(m_image);
}

CBool CGUIImage::LoadGUIImage()
{
	if (m_image)
		CDelete(m_image);
	m_image = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_image, m_imagePath, NULL))
	{
		CDelete(m_image);
		return CFalse;
	}
	return CTrue;
}

CVoid CGUIImage::Render(CVec2f globalPosition, CBool selectionMode)
{
	if (!m_visible) return;

	CFloat h = m_scale * m_size * g_height / 100.0f;
	CFloat w = h * (m_image->GetWidth() / m_image->GetHeight());

	if (selectionMode)
	{
		glPushName(m_nameIndex);
		glUseProgram(0);

		glBegin(GL_QUADS);
		glVertex3f(globalPosition.x + m_position.x, globalPosition.y + m_position.y - h, -1.0f);
		glVertex3f(globalPosition.x + m_position.x + w, globalPosition.y + m_position.y - h, -1.0f);
		glVertex3f(globalPosition.x + m_position.x + w, globalPosition.y + m_position.y, -1.0f);
		glVertex3f(globalPosition.x + m_position.x, globalPosition.y + m_position.y, -1.0f);
		glEnd();

		glPopName();
		return;
	}

	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, g_width, 0.0, g_height, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_VIEWPORT_BIT);
	glViewport(0, g_main->GetPadding(), g_width, g_height);
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
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);  glVertex3f(globalPosition.x + m_position.x, globalPosition.y + m_position.y, -1.0f);
	glTexCoord2d(1, 1);  glVertex3f(globalPosition.x + m_position.x + w, globalPosition.y + m_position.y, -1.0f);
	glTexCoord2d(1, 0);  glVertex3f(globalPosition.x + m_position.x + w, globalPosition.y + m_position.y - h, -1.0f);
	glTexCoord2d(0, 0);  glVertex3f(globalPosition.x + m_position.x, globalPosition.y + m_position.y - h, -1.0f);
	glEnd();

	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


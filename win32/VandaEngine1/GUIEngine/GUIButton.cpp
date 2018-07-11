//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CAddAmbientSound.cpp : implementation file
//
#include "stdafx.h"
#include "GUIButton.h"
#include "..\\Main.h"
CGUIButton::CGUIButton()
{
	m_mainImage = NULL;
	m_leftClickImage = NULL;
	m_hoverImage = NULL;
	m_rightClickImage = NULL;
	m_disableImage = NULL;

	m_updateMainImage = CFalse;
	m_updateLeftClickImage = CFalse;
	m_updateHoverImage = CFalse;
	m_updateRightClickImage = CFalse;
	m_updateDisableImage = CFalse;
	m_updateLeftClickScript = CFalse;
	m_updateHoverScript = CFalse;
	m_updateRightClickScript = CFalse;

	m_currentImageType = eBUTTON_IMAGE_MAIN;

	SetIndex();

	m_rightClickTimer = m_leftClickTimer = 0.0f;
	m_maxRightClickTimer = 0.1f;
	m_maxLeftClickTimer = 0.1f;
}

CGUIButton::~CGUIButton()
{
	CDelete(m_mainImage);
	CDelete(m_leftClickImage);
	CDelete(m_hoverImage);
	CDelete(m_rightClickImage);
	CDelete(m_disableImage);

}

CBool CGUIButton::LoadMainImage()
{
	if (m_mainImage)
		CDelete(m_mainImage);
	m_mainImage = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_mainImage, m_mainImagePath, NULL))
	{
		CDelete(m_mainImage);
		return CFalse;
	}
	return CTrue;

}

CBool CGUIButton::LoadLeftClickImage()
{
	if (m_leftClickImage)
		CDelete(m_leftClickImage);
	m_leftClickImage = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_leftClickImage, m_leftClickImagePath, NULL))
	{
		CDelete(m_leftClickImage);
		return CFalse;
	}
	return CTrue;

}

CBool CGUIButton::LoadHoverImage()
{
	if (m_hoverImage)
		CDelete(m_hoverImage);
	m_hoverImage = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_hoverImage, m_hoverImagePath, NULL))
	{
		CDelete(m_hoverImage);
		return CFalse;
	}
	return CTrue;

}

CBool CGUIButton::LoadRightClickImage()
{
	if (m_rightClickImage)
		CDelete(m_rightClickImage);
	m_rightClickImage = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_rightClickImage, m_rightClickImagePath, NULL))
	{
		CDelete(m_rightClickImage);
		return CFalse;
	}
	return CTrue;

}

CBool CGUIButton::LoadDisableImage()
{
	if (m_disableImage)
		CDelete(m_disableImage);
	m_disableImage = CNew(CImage);
	if (!CTexture::LoadDDSTexture(m_disableImage, m_disableImagePath, NULL))
	{
		CDelete(m_disableImage);
		return CFalse;
	}
	return CTrue;

}

CVoid CGUIButton::Render(CBool selectionMode)
{
	CFloat w = m_size * g_width / 100.0f;
	CFloat h = (w / m_mainImage->GetWidth()) * m_mainImage->GetHeight();

	if (selectionMode)
	{
		glPushName(m_nameIndex);
		glUseProgram(0);

		glBegin(GL_QUADS);
		glVertex3f(m_position.x, m_position.y - h, 0.0f);
		glVertex3f(m_position.x + w, m_position.y - h, 0.0f);
		glVertex3f(m_position.x + w, m_position.y, 0.0f);
		glVertex3f(m_position.x, m_position.y, 0.0f);
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
	glViewport(0, 0, g_width, g_height);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	//Upper Left: Position.x, Position.y

	if (m_currentImageType == eBUTTON_IMAGE_LEFT_CLICK)
	{
		m_leftClickTimer += g_timer->GetElapsedSeconds2();
		if (m_leftClickTimer >= m_maxLeftClickTimer)
		{
			m_leftClickTimer = 0.0f;

			CUInt index = g_main->GetSelectedGUI();
			if (GetIndex() == index)
			{
				if (GetHasHoverImage())
					m_currentImageType = eBUTTON_IMAGE_HOVER;
				else
					m_currentImageType = eBUTTON_IMAGE_MAIN;
			}
			else
			{
				m_currentImageType = eBUTTON_IMAGE_MAIN;
			}

			if (GetHasLeftClickScript())
				LuaLoadAndExecute(g_lua, GetLeftClickScriptPath());

		}
	}
	else if (m_currentImageType == eBUTTON_IMAGE_RIGHT_CLICK)
	{
		m_rightClickTimer += g_timer->GetElapsedSeconds2();
		if (m_rightClickTimer >= m_maxRightClickTimer)
		{
			m_rightClickTimer = 0.0f;

			CUInt index = g_main->GetSelectedGUI();
			if (GetIndex() == index)
			{
				if (GetHasHoverImage())
					m_currentImageType = eBUTTON_IMAGE_HOVER;
				else
					m_currentImageType = eBUTTON_IMAGE_MAIN;
			}
			else
			{
				m_currentImageType = eBUTTON_IMAGE_MAIN;
			}

			if (GetHasRightClickScript())
				LuaLoadAndExecute(g_lua, GetRightClickScriptPath());
		}
	}
	glActiveTextureARB(GL_TEXTURE0_ARB);
	switch (m_currentImageType)
	{
	case eBUTTON_IMAGE_MAIN:
		glBindTexture(GL_TEXTURE_2D, m_mainImage->GetId());
		break;
	case eBUTTON_IMAGE_HOVER:
		if (GetHasHoverImage())
			glBindTexture(GL_TEXTURE_2D, m_hoverImage->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, m_mainImage->GetId());
		break;
	case eBUTTON_IMAGE_DISABLE:
		if (GetHasDisableImage())
			glBindTexture(GL_TEXTURE_2D, m_disableImage->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, m_mainImage->GetId());
		break;
	case eBUTTON_IMAGE_RIGHT_CLICK:
		if (GetHasRightClickImage())
			glBindTexture(GL_TEXTURE_2D, m_rightClickImage->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, m_mainImage->GetId());
		break;
	case eBUTTON_IMAGE_LEFT_CLICK:
		if (GetHasLeftClickImage())
			glBindTexture(GL_TEXTURE_2D, m_leftClickImage->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, m_mainImage->GetId());
		break;
	}

	if (m_mainImage->GetFormat() == 4)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);
	}

	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);  glVertex3f(m_position.x, m_position.y, -1.0f);
	glTexCoord2d(1, 1);  glVertex3f(m_position.x + w, m_position.y, -1.0f);
	glTexCoord2d(1, 0);  glVertex3f(m_position.x + w, m_position.y - h, -1.0f);
	glTexCoord2d(0, 0);  glVertex3f(m_position.x, m_position.y - h, -1.0f);
	glEnd();

	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

}

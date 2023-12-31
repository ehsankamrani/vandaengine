//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CGUIText.cpp : implementation file
//

#include "stdafx.h"
#include "..\\VandaEngineEditor.h"
#include "GUIText.h"

CGUIText::CGUIText()
{
	m_font = CNew(CSimpleFont);
	m_fontSmall = CNew(CSimpleFont);

	m_visible = CTrue;
	m_scale = 1.0;
	m_gui = NULL;

	SetIndex();
}

CGUIText::~CGUIText()
{
	m_font->Release();
	CDelete(m_font);

	m_fontSmall->Release();
	CDelete(m_fontSmall);
}

CBool CGUIText::SetFont()
{
	CChar font[MAX_NAME_SIZE];
	Cpy(font, "Arial"); //default value
	if (m_type == eFONT_ARIAL)
	{
		Cpy(font, "Arial");
	}
	else if (m_type == eFONT_TIMES_NEW_ROMAN)
	{
		Cpy(font, "Times New Roman");
	}

	if (!m_font->Init(font, m_size))
	{
		//try again
		if (!m_font->Init(font, m_size))
		{
			MessageBox(NULL, "Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
			return false;
		}
	}

	if (!m_fontSmall->Init(font, CInt((CFloat)m_size / 2.0f)))
	{
		//try again
		if (!m_fontSmall->Init(font, CInt((CFloat)m_size / 2.0f)))
		{
			MessageBox(NULL, "Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
			return false;
		}
	}
	return CTrue;
}

void CGUIText::Render(CVec2f globalPosition, CBool selectionMode)
{
	if (!m_visible) return;

	if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
	{
		globalPosition.x /= 2.0f;
		globalPosition.y /= 2.0f;
	}

	if (selectionMode)
		glPushName(m_nameIndex);

	if (!selectionMode)
	{
		if(g_menu.m_justPerspective)
			m_font->StartRendering(g_width, g_height);
		else
			m_fontSmall->StartRendering(g_width / 2, g_height / 2);
	}
	if (g_editorMode == eMODE_GUI || (g_editorMode == eMODE_VSCENE && g_menu.m_justPerspective))
		m_font->Print(m_text, globalPosition.x + m_position.x, globalPosition.y + m_position.y, 0.0f, m_color.x, m_color.y, m_color.z, selectionMode);
	else if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
		m_fontSmall->Print(m_text, globalPosition.x + m_position.x * 0.5f, globalPosition.y + m_position.y * 0.5f, 0.0f, m_color.x, m_color.y, m_color.z, selectionMode);


	if (!selectionMode)
	{
		if (g_menu.m_justPerspective)
			m_font->EndRendering();
		else
			m_fontSmall->EndRendering();
	}
	if (selectionMode)
		glPopName();
}

CVec2f CGUIText::SetPosition(CVec2f pos)
{
	m_position.x = pos.x;
	if (m_position.x < 0.0)
		m_position.x = 0.0;
	else if (m_position.x > g_multipleView->m_width)
		m_position.x = g_multipleView->m_width;

	m_position.y = pos.y;

	if (m_position.y < 0.0)
		m_position.y = 0.0;
	else if (m_position.y > g_multipleView->m_height)
		m_position.y = g_multipleView->m_height;

	return m_position;

}

CVoid CGUIText::SetPosition2(CVec2f pos)
{
	m_position.x += pos.x;
	if (m_position.x < 0.0)
		m_position.x = 0.0;
	else if (m_position.x > g_multipleView->m_width)
		m_position.x = g_multipleView->m_width;

	m_position.y -= pos.y;

	if (m_position.y < 0.0)
		m_position.y = 0.0;
	else if (m_position.y > g_multipleView->m_height)
		m_position.y = g_multipleView->m_height;

}


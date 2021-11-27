//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CGUIText.cpp : implementation file
//

#include "stdafx.h"
#include "..\\VandaEngine1.h"
#include "GUIText.h"

CGUIText::CGUIText()
{
	m_font = CNew(CSimpleFont);
	SetIndex();
}

CGUIText::~CGUIText()
{
	m_font->Release();
	CDelete(m_font);
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
	return CTrue;
}

void CGUIText::Render(CBool selectionMode)
{
	if (selectionMode)
		glPushName(m_nameIndex);

	if (!selectionMode)
	{
		m_font->StartRendering(g_width, g_height);
	}
	if (g_editorMode == eMODE_GUI || (g_editorMode == eMODE_VSCENE && g_menu.m_justPerspective))
		m_font->Print(m_text, m_position.x, m_position.y, 0.0f, m_color.x, m_color.y, m_color.z, selectionMode);
	else if (g_editorMode == eMODE_VSCENE && !g_menu.m_justPerspective)
		m_font->Print(m_text, m_position.x * 0.5f, m_position.y * 0.5f, 0.0f, m_color.x, m_color.y, m_color.z, selectionMode);


	if (!selectionMode)
		m_font->EndRendering();

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


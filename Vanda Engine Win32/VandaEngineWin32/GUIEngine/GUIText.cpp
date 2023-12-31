//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CGUIText.cpp : implementation file
//
#include "stdafx.h"
#include "GUIText.h"
#include "..\\VandaEngineWin32.h"
CGUIText::CGUIText()
{
	m_font = CNew(CFont);
	m_visible = CTrue;
	m_scale = 1.0;
	m_gui = NULL;

	SetIndex();
}

CGUIText::~CGUIText()
{
	m_font->Release();
	CDelete(m_font);
}

CBool CGUIText::SetFont()
{
	if (m_type == eFONT_ARIAL)
	{
		if (!m_font->Init(_T("Arial"), m_size))
		{
			if (!m_font->Init(_T("Arial"), m_size))
			{
				MessageBoxA(NULL, "Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
				return false;
			}
		}
	}
	else if (m_type == eFONT_TIMES_NEW_ROMAN)
	{
		if (!m_font->Init(_T("Times New Roman"), m_size))
		{
			if (!m_font->Init(_T("Times New Roman"), m_size))
			{
				MessageBoxA(NULL, "Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
				return false;
			}
		}
	}
	return CTrue;
}

void CGUIText::Render(CVec2f globalPosition, CBool selectionMode)
{
	if (!m_visible) return;

	if (selectionMode)
		glPushName(m_nameIndex);

	if (!selectionMode)
		m_font->StartRendering(g_width, g_height);
	m_font->Print(m_text, globalPosition.x + m_position.x, globalPosition.y + m_position.y, 0.0f, m_color.x, m_color.y, m_color.z, selectionMode);

	if (!selectionMode)
		m_font->EndRendering();

	if (selectionMode)
		glPopName();
}


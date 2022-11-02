//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CAddAmbientSound.cpp : implementation file
//

#include "stdafx.h"
#include "GUIImage.h"
#include "GUIButton.h"
#include "GUIText.h"
#include "GUI.h"
#include "VandaEngine1Win32.h"

CGUI::CGUI()
{
	m_visible = CTrue;
	m_loadedFromScript = CFalse;
	m_position.x = m_position.y = 0.0f;
	m_rotation = 0.0f;
}

CGUI::~CGUI()
{
	for (CUInt i = 0; i < m_guiButtons.size(); i++)
		CDelete(m_guiButtons[i]);
	m_guiButtons.clear();

	for (CUInt i = 0; i < m_guiImages.size(); i++)
		CDelete(m_guiImages[i]);
	m_guiImages.clear();

	for (CUInt i = 0; i < m_guiTexts.size(); i++)
		CDelete(m_guiTexts[i]);
	m_guiTexts.clear();
}

CVoid CGUI::AddGUIButton(CGUIButton* button)
{
	m_guiButtons.push_back(button); 
}

CVoid CGUI::AddGUIImage(CGUIImage* image)
{ 
	m_guiImages.push_back(image);
}

CVoid CGUI::AddGUIText(CGUIText* text)
{
	m_guiTexts.push_back(text);
}

CVec2f CGUI::GetPosition(CBool positionForRender)
{
	if (!positionForRender)
		return m_position;

	CVec2f position;

	position.x = (m_position.x * (CFloat)g_width) / 100.0f;
	position.y = (m_position.y * (CFloat)g_height) / 100.0f;

	return position;
}

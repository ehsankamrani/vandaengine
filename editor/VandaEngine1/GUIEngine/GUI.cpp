//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CAddAmbientSound.cpp : implementation file
//

#include "stdafx.h"
#include "GUIBackground.h"
#include "GUIButton.h"
#include "GUIText.h"
#include "GUI.h"

CGUI::CGUI()
{
	m_visible = CTrue;
	m_loadedFromScript = CFalse;
}

CGUI::~CGUI()
{

}

CVoid CGUI::AddGUIButton(CGUIButton* button)
{
	m_guiButtons.push_back(button);
}

CVoid CGUI::AddGUIBackground(CGUIBackground* background)
{
	m_guiBackgrounds.push_back(background);
}

CVoid CGUI::AddGUIText(CGUIText* text)
{
	m_guiTexts.push_back(text);
}



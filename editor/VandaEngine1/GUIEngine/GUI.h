//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "Utility.h"

class CGUIButton;
class CGUIImage;
class CGUIText;

class CGUI
{
public:
	CGUI();
	~CGUI();
	CVoid AddGUIButton(CGUIButton* button);
	CVoid AddGUIImage(CGUIImage* image);
	CVoid AddGUIText(CGUIText* text);

	inline CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CVoid SetPackageName(CChar* name) { Cpy(m_packageName, name); }
	inline CVoid SetGUIName(CChar* name) { Cpy(m_guiName, name); }
	inline CVoid SetVisible(CBool state) { m_visible = state; }
	inline CVoid SetLoadedFromScript(CBool state) { m_loadedFromScript = state; }
	inline CVoid SetPosition(CVec2f position) { m_position = position; }
	inline CVoid SetRotation(CFloat rotation) { m_rotation = rotation; }

	inline CBool GetVisible() { return m_visible; }
	inline CChar* GetName() { return m_name; }
	inline CChar* GetPackageName() { return m_packageName; }
	inline CChar* GetGUIName() { return m_guiName; }
	inline CBool GetLoadedFromScript() { return m_loadedFromScript; }
	inline CVec2f GetPosition() { return m_position; }
	inline CFloat GetRotation() { return m_rotation; }

	std::vector<CGUIButton*> m_guiButtons;
	std::vector<CGUIImage*> m_guiImages;
	std::vector<CGUIText*> m_guiTexts;

private:

	CChar m_name[MAX_NAME_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_guiName[MAX_NAME_SIZE];

	CBool m_visible;
	CBool m_loadedFromScript;
	CVec2f m_position;
	CFloat m_rotation;
};



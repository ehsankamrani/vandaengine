//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "Utility.h"
#include "..\\GraphicsEngine\\SimpleFont.h"
#include "..\\GraphicsEngine\\PerspectiveWindow.h"
class CGUIText
{
public:
	CGUIText();
	~CGUIText();
private:
	CChar m_name[MAX_NAME_SIZE];
	CVec2f m_position;
	CInt m_size;
	CBool m_visible;
	CFloat m_scale;
	CFontType m_type;
	CVec3f m_color;
	CChar m_text[MAX_URI_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_guiName[MAX_NAME_SIZE];
	CSimpleFont* m_font;
	CInt m_nameIndex;
public:
	CVec2f SetPosition(CVec2f pos);
	CVoid SetPosition2(CVec2f pos);
	inline CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CVoid SetPackageName(CChar* name) { Cpy(m_packageName, name); }
	inline CVoid SetGUIName(CChar* name) { Cpy(m_guiName, name); }
	inline CVoid SetSize(CInt size) { m_size = size; }
	inline CVoid SetScale(CFloat scale) { m_scale = scale; }
	inline CVoid Show() { m_visible = CTrue; }
	inline CVoid Hide() { m_visible = CFalse; }
	inline CVoid SetVisible(CBool visible) { m_visible = visible; }
	inline CBool IsVisible() { if (m_visible) return CTrue; else return CFalse; }
	inline CVoid SetType(CFontType type) { m_type = type; }
	inline CVoid SetText(CChar* text) { Cpy(m_text, text); }
	inline CVoid SetColor(CVec3f color) { m_color = color; }
	CBool SetFont();
	void Render(CBool selectionMode = CFalse);

	inline CChar* GetName() { return m_name; }
	inline CChar* GetPackageName() { return m_packageName; }
	inline CChar* GetGUIName() { return m_guiName; }
	inline CVec2f GetPosition() { return m_position; }
	inline CInt GetSize() { return m_size; }
	inline CChar* GetText() { return m_text; }
	inline CVec3f GetColor() { return m_color; }
	inline CFontType GetFontType() { return m_type; }

	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CInt GetIndex() { return m_nameIndex; }
};


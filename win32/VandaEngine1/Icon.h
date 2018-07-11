#pragma once

#include "Utility.h"
class CImage;
class CIcon
{
private:
	CChar m_name[MAX_NAME_SIZE]; //we will show this name
	CBool m_visible; //show or hide
	CImage* m_image;
	CFloat m_size;
public:
	CIcon();
	~CIcon();

	CVoid SetName(CChar* name) { Cpy(m_name, name); }
	CChar* GetName() { return m_name; }

	CVoid SetVisible(CBool state) { m_visible = state; }
	CBool GetVisible() { return m_visible; }

	CVoid SetImage(CImage* image);

	CVoid SetSize(CFloat size) { m_size = size; }

	CVoid Render(CVec2f pos);
};


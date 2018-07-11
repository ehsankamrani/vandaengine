//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "Utility.h"
#include "..\\GraphicsEngine\\Image.h"
class CGUIButton
{
public:
	CGUIButton();
	~CGUIButton();
private:
	CChar m_name[MAX_NAME_SIZE];
	CChar m_packageName[MAX_NAME_SIZE];
	CChar m_guiName[MAX_NAME_SIZE];

	CVec2f m_position;
	CInt m_size;

	CChar m_mainImagePath[MAX_NAME_SIZE];
	CChar m_leftClickImagePath[MAX_NAME_SIZE];
	CChar m_hoverImagePath[MAX_NAME_SIZE];
	CChar m_rightClickImagePath[MAX_NAME_SIZE];
	CChar m_disableImagePath[MAX_NAME_SIZE];

	CChar m_leftClickScriptPath[MAX_NAME_SIZE];
	CChar m_rightClickScriptPath[MAX_NAME_SIZE];
	CChar m_hoverScriptPath[MAX_NAME_SIZE];

	CImage* m_mainImage;
	CImage* m_leftClickImage;
	CImage* m_hoverImage;
	CImage* m_rightClickImage;
	CImage* m_disableImage;

	CBool m_updateMainImage;
	CBool m_updateLeftClickImage;
	CBool m_updateHoverImage;
	CBool m_updateRightClickImage;
	CBool m_updateDisableImage;
	CBool m_updateLeftClickScript;
	CBool m_updateHoverScript;
	CBool m_updateRightClickScript;

	CButtonImageType m_currentImageType;

	CInt m_nameIndex;

	CFloat m_rightClickTimer;
	CFloat m_leftClickTimer;

	CFloat m_maxRightClickTimer;
	CFloat m_maxLeftClickTimer;

public:
	inline CVoid SetMainImagePath(CChar* path) { Cpy(m_mainImagePath, path); }
	inline CVoid SetLeftClickImagePath(CChar* path) { Cpy(m_leftClickImagePath, path); }
	inline CVoid SetHoverImagePath(CChar* path) { Cpy(m_hoverImagePath, path); }
	inline CVoid SetRightClickImagePath(CChar* path) { Cpy(m_rightClickImagePath, path); }
	inline CVoid SetDisableImagePath(CChar* path) { Cpy(m_disableImagePath, path); }

	inline CVoid SetLeftClickScriptPath(CChar* path) { Cpy(m_leftClickScriptPath, path); }
	inline CVoid SetRightClickScriptPath(CChar* path) { Cpy(m_rightClickScriptPath, path); }
	inline CVoid SetHoverScriptPath(CChar* path) { Cpy(m_hoverScriptPath, path); }

	inline CVoid SetPosition(CVec2f pos) { m_position.x = pos.x; m_position.y = pos.y; }
	inline CVoid SetName(CChar* name) { Cpy(m_name, name); }
	inline CVoid SetPackageName(CChar* name) { Cpy(m_packageName, name); }
	inline CVoid SetGUIName(CChar* name) { Cpy(m_guiName, name); }
	inline CVoid SetSize(CInt size) { m_size = size; }

	inline CChar* GetName() { return m_name; }
	inline CChar* GetPackageName() { return m_packageName; }
	inline CChar* GetGUIName() { return m_guiName; }

	inline CChar* GetMainImagePath() { return m_mainImagePath; }
	inline CChar* GetLeftClickImagePath() { return m_leftClickImagePath; }
	inline CChar* GetHoverImagePath() { return m_hoverImagePath; }
	inline CChar* GetRightClickImagePath() { return m_rightClickImagePath; }
	inline CChar* GetDisableImagePath() { return m_disableImagePath; }

	inline CChar* GetLeftClickScriptPath() { return m_leftClickScriptPath; }
	inline CChar* GetRightClickScriptPath() { return m_rightClickScriptPath; }
	inline CChar* GetHoverScriptPath() { return m_hoverScriptPath; }

	inline CVec2f GetPosition() { return m_position; }
	inline CInt GetSize() { return m_size; }

	inline CVoid SetUpdateMainImage(CBool state) { m_updateMainImage = state; }
	inline CVoid SetUpdateLeftClickImage(CBool state) { m_updateLeftClickImage = state; }
	inline CVoid SetUpdateHoverImage(CBool state) { m_updateHoverImage = state; }
	inline CVoid SetUpdateRightClickImage(CBool state) { m_updateRightClickImage = state; }
	inline CVoid SetUpdateDisableImage(CBool state) { m_updateDisableImage = state; }
	inline CVoid SetUpdateLeftClickScript(CBool state) { m_updateLeftClickScript = state; }
	inline CVoid SetUpdateRightClickScript(CBool state) { m_updateRightClickScript = state; }
	inline CVoid SetUpdateHoverScript(CBool state) { m_updateHoverScript = state; }

	inline CVoid SetCurrentImageType(CButtonImageType type) { m_currentImageType = type; }

	inline CBool GetUpdateMainImage() { return m_updateMainImage; }
	inline CBool GetUpdateLeftClickImage() { return m_updateLeftClickImage; }
	inline CBool GetUpdateHoverImage() { return m_updateHoverImage; }
	inline CBool GetUpdateRightClickImage() { return m_updateRightClickImage; }
	inline CBool GetUpdateDisableImage() { return m_updateDisableImage; }
	inline CBool GetUpdateLeftClickScript() { return m_updateLeftClickScript; }
	inline CBool GetUpdateRightClickScript() { return m_updateRightClickScript; }
	inline CBool GetUpdateHoverScript() { return m_updateHoverScript; }

	inline CButtonImageType GetCurrentImageType() { return m_currentImageType; }

	CVoid SetIndex() { m_nameIndex = g_nameIndex++; }
	CInt GetIndex() { return m_nameIndex; }

	CBool LoadMainImage();
	CBool LoadLeftClickImage();
	CBool LoadHoverImage();
	CBool LoadRightClickImage();
	CBool LoadDisableImage();

	CBool m_hasLeftClickImage;
	CBool m_hasHoverImage;
	CBool m_hasRightClickImage;
	CBool m_hasDisableImage;
	CBool m_hasLeftClickScript;
	CBool m_hasRightClickScript;
	CBool m_hasHoverScript;

	inline CBool GetHasLeftClickImage() { return m_hasLeftClickImage; }
	inline CBool GetHasHoverImage() { return m_hasHoverImage; }
	inline CBool GetHasRightClickImage() { return m_hasRightClickImage; }
	inline CBool GetHasDisableImage() { return m_hasDisableImage; }

	inline CBool GetHasLeftClickScript() { return m_hasLeftClickScript; }
	inline CBool GetHasRightClickScript() { return m_hasRightClickScript; }
	inline CBool GetHasHoverScript() { return m_hasHoverScript; }

	inline CVoid SetHasLeftClickImage(CBool state) { m_hasLeftClickImage = state; }
	inline CVoid SetHasHoverImage(CBool state) { m_hasHoverImage = state; }
	inline CVoid SetHasRightClickImage(CBool state) { m_hasRightClickImage = state; }
	inline CVoid SetHasDisableImage(CBool state) { m_hasDisableImage = state; }

	inline CVoid SetHasLeftClickScript(CBool state) { m_hasLeftClickScript = state; }
	inline CVoid SetHasRightClickScript(CBool state) { m_hasRightClickScript = state; }
	inline CVoid SetHasHoverScript(CBool state) { m_hasHoverScript = state; }

	CVoid Render(CBool selectionMode = CFalse);
};



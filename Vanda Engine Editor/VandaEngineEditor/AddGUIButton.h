//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddGUIButton dialog

class CAddGUIButton : public CDialog
{
	DECLARE_DYNAMIC(CAddGUIButton)

public:
	CAddGUIButton(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddGUIButton();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUI_BUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CBool m_updateMainImage;
	CBool m_updateLeftClickImage;
	CBool m_updateHoverImage;
	CBool m_updateRightClickImage;
	CBool m_updateDisableImage;
	CBool m_updateScript;

public:
	afx_msg void OnBnClickedButtonAddMainImg();
	afx_msg void OnBnClickedButtonAddLeftClkImg();
	afx_msg void OnBnClickedButtonRemoveLeftClkImg();
	afx_msg void OnBnClickedButtonAddHoverImg();
	afx_msg void OnBnClickedButtonRemoveHoverImg();
	afx_msg void OnBnClickedButtonAddRightClkImg();
	afx_msg void OnBnClickedButtonRemoveRightClkImg();
	afx_msg void OnBnClickedButtonAddDisableImg();
	afx_msg void OnBnClickedButtonRemoveDisableImg();
	afx_msg void OnBnClickedButtonAddScript();
	afx_msg void OnBnClickedButtonRemoveScript();
	CEdit m_editMainImg;
	CEdit m_editLeftClickImg;
	CEdit m_editHoverImg;
	CEdit m_editRightClickImg;
	CEdit m_editDisableImg;
	CEdit m_editScript;

	CString m_strMainImgPath;
	CString m_strMainPureImgPath;
	CString m_strLeftClickImgPath;
	CString m_strLeftClickPureImgPath;
	CString m_strRightClickImgPath;
	CString m_strRightClickPureImgPath;
	CString m_strHoverImgPath;
	CString m_strHoverPureImgPath;
	CString m_strDisableImgPath;
	CString m_strDisablePureImgPath;

	CBool m_hasLeftClickImage;
	CBool m_hasRightClickImage;
	CBool m_hasHoverImage;
	CBool m_hasDisableImage;
	CBool m_hasScript;

	inline CBool GetHasLeftClickImage() { return m_hasLeftClickImage; }
	inline CBool GetHasHoverImage() { return m_hasHoverImage; }
	inline CBool GetHasRightClickImage() { return m_hasRightClickImage; }
	inline CBool GetHasDisableImage() { return m_hasDisableImage; }

	inline CBool GetHasScript() { return m_hasScript; }


	CString m_strSize;
	CFloat m_fSize;
	
	CBool m_visible;

	CString m_strScriptPath;
	CString m_strPureScriptPath;
	CString m_strHoverPureScriptPath;
	CString m_strRightClickPureScriptPath;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_editSize;
	afx_msg void OnEnChangeEditSize();
	CEdit m_editName;
	CEdit m_editPosX;
	CEdit m_editPosY;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();

	CString m_strName;
	CString m_strTempName;

	CString m_strPosX;
	CFloat m_fPosX;

	CString m_strPosY;
	CFloat m_fPosY;

	CVoid SetCreate(CBool create);
	CBool m_create;

	CVoid SetName(CChar* name);
	CVoid SetPosition(CVec2f pos);
	CVoid SetSize(CFloat size);
	CVoid SetVisible(CBool state);
	CVoid SetMainImagePath(CChar* path);
	CVoid SetLeftClickImagePath(CChar* path);
	CVoid SetHoverImagePath(CChar* path);
	CVoid SetRightClickImagePath(CChar* path);
	CVoid SetDisableImagePath(CChar* path);

	CVoid SetScriptPath(CChar* path);

	inline CVoid SetUpdateMainImage(CBool state) { m_updateMainImage = state; }
	inline CVoid SetUpdateLeftClickImage(CBool state) { m_updateLeftClickImage = state; }
	inline CVoid SetUpdateHoverImage(CBool state) { m_updateHoverImage = state; }
	inline CVoid SetUpdateRightClickImage(CBool state) { m_updateRightClickImage = state; }
	inline CVoid SetUpdateDisableImage(CBool state) { m_updateDisableImage = state; }
	inline CVoid SetUpdateScript(CBool state) { m_updateScript = state; }

	inline CBool GetUpdateMainImage() { return m_updateMainImage; }
	inline CBool GetUpdateLeftClickImage() { return m_updateLeftClickImage; }
	inline CBool GetUpdateHoverImage() { return m_updateHoverImage; }
	inline CBool GetUpdateRightClickImage() { return m_updateRightClickImage; }
	inline CBool GetUpdateDisableImage() { return m_updateDisableImage; }
	inline CBool GetUpdateScript() { return m_updateScript; }

	CChar* GetName();
	CVec2f GetPosition();
	CFloat GetSize();
	CBool IsVisible();

	CChar* GetMainImagePath();
	CChar* GetLeftClickImagePath();
	CChar* GetHoverImagePath();
	CChar* GetRightClickImagePath();
	CChar* GetDisableImagePath();

	CChar* GetScriptPath();
	afx_msg void OnBnClickedButtonViewScript();
};

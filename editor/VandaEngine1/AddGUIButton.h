//Copyright (C) 2018 Ehsan Kamrani 
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
	CBool m_updateLeftClickScript;
	CBool m_updateHoverScript;
	CBool m_updateRightClickScript;

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
	afx_msg void OnBnClickedButtonAddLeftClkScript();
	afx_msg void OnBnClickedButtonRemoveLeftClkScript();
	afx_msg void OnBnClickedButtonAddHoverScript();
	afx_msg void OnBnClickedButtonRemoveHoverScript();
	afx_msg void OnBnClickedButtonAddRightClkScript();
	afx_msg void OnBnClickedButtonRemoveRightClkScript();
	CEdit m_editMainImg;
	CEdit m_editLeftClickImg;
	CEdit m_editHoverImg;
	CEdit m_editRightClickImg;
	CEdit m_editDisableImg;
	CEdit m_editLeftClickScript;
	CEdit m_editHoverScript;
	CEdit m_editRightClickScript;

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


	CString m_strSize;
	CFloat m_fSize;

	CString m_strLeftClickScriptPath;
	CString m_strLeftClickPureScriptPath;
	CString m_strHoverScriptPath;
	CString m_strHoverPureScriptPath;
	CString m_strRightClickScriptPath;
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

	CVoid SetMainImagePath(CChar* path);
	CVoid SetLeftClickImagePath(CChar* path);
	CVoid SetHoverImagePath(CChar* path);
	CVoid SetRightClickImagePath(CChar* path);
	CVoid SetDisableImagePath(CChar* path);

	CVoid SetLeftClickScriptPath(CChar* path);
	CVoid SetHoverScriptPath(CChar* path);
	CVoid SetRightClickScriptPath(CChar* path);

	inline CVoid SetUpdateMainImage(CBool state) { m_updateMainImage = state; }
	inline CVoid SetUpdateLeftClickImage(CBool state) { m_updateLeftClickImage = state; }
	inline CVoid SetUpdateHoverImage(CBool state) { m_updateHoverImage = state; }
	inline CVoid SetUpdateRightClickImage(CBool state) { m_updateRightClickImage = state; }
	inline CVoid SetUpdateDisableImage(CBool state) { m_updateDisableImage = state; }
	inline CVoid SetUpdateLeftClickScript(CBool state) { m_updateLeftClickScript = state; }
	inline CVoid SetUpdateRightClickScript(CBool state) { m_updateRightClickScript = state; }
	inline CVoid SetUpdateHoverScript(CBool state) { m_updateHoverScript = state; }

	inline CBool GetUpdateMainImage() { return m_updateMainImage; }
	inline CBool GetUpdateLeftClickImage() { return m_updateLeftClickImage; }
	inline CBool GetUpdateHoverImage() { return m_updateHoverImage; }
	inline CBool GetUpdateRightClickImage() { return m_updateRightClickImage; }
	inline CBool GetUpdateDisableImage() { return m_updateDisableImage; }
	inline CBool GetUpdateLeftClickScript() { return m_updateLeftClickScript; }
	inline CBool GetUpdateRightClickScript() { return m_updateRightClickScript; }
	inline CBool GetUpdateHoverScript() { return m_updateHoverScript; }

	CChar* GetName();
	CVec2f GetPosition();
	CFloat GetSize();

	CChar* GetMainImagePath();
	CChar* GetLeftClickImagePath();
	CChar* GetHoverImagePath();
	CChar* GetRightClickImagePath();
	CChar* GetDisableImagePath();

	CChar* GetLeftClickScriptPath();
	CChar* GetHoverScriptPath();
	CChar* GetRightClickScriptPath();

};

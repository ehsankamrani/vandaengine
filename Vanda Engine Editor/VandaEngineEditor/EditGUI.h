//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "GUIEngine/GUI.h"

// CEditGUI dialog

class CEditGUI : public CDialog
{
	DECLARE_DYNAMIC(CEditGUI)

public:
	CEditGUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditGUI();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_GUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyGuiInstanceName();
	CRichEditCtrl m_richGUIInstanceName;

	CVoid SetGUIInstance(CGUI* instance_gui);

private:
	CGUI* m_instanceGUI;
	HBITMAP m_hBitmap;
	CVoid UpdatePreview();
	CString m_strPosX;
	CString m_strPosY;
	CFloat m_posX;
	CFloat m_posY;

public:
	virtual BOOL OnInitDialog();
	CStatic m_textGUIName;
	CStatic m_imageCtrl;
	CEdit m_editBoxPosX;
	CEdit m_editBoxPosY;
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();

	virtual void OnOK();
};

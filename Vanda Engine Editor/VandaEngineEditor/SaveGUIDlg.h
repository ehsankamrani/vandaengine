//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "GUINameDlg.h"

// CSaveGUIDlg dialog

class CSaveGUIDlg : public CDialog
{
	DECLARE_DYNAMIC(CSaveGUIDlg)

public:
	CSaveGUIDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveGUIDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_GUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddPackage();
	afx_msg void OnEnChangeGuiName();
	CEdit m_editBoxGUIName;
	CString m_strGUIName;

	std::string m_strNewGUIPackageName;
	std::string m_strNewGUIName; //package_gui.vpf
	std::string m_strNewPackageAndGUIName; //package_gui.vpf

	virtual BOOL OnInitDialog();
	CComboBox m_guiPackageList;
	afx_msg void OnBnClickedOk();
	CGUINameDlg* m_guiNameDlg;
};

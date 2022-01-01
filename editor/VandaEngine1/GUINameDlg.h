//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CGUINameDlg dialog

class CGUINameDlg : public CDialog
{
	DECLARE_DYNAMIC(CGUINameDlg)

public:
	CGUINameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGUINameDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUI_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editBoxName;
	afx_msg void OnBnClickedOk();
	CVoid SetInitialData(std::string selectedPackageName, std::string selectedGUIName, CBool package, CBool rename = CFalse);
	std::string m_selectedPackageName;
	std::string m_selectedGUIName;
	CString m_strName; //edit box field
	std::string m_newName;
	CBool m_package; //are we dealing with package or GUI?
	CBool m_rename;
	CChar* GetNewName();

	afx_msg void OnEnChangeGuiName();
};

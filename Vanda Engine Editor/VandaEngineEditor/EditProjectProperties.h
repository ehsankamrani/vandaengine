//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditProjectProperties dialog

class CEditProjectProperties : public CDialog
{
	DECLARE_DYNAMIC(CEditProjectProperties)

public:
	CEditProjectProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditProjectProperties();
	CVoid SetName(CChar* name);

// Dialog Data
	enum { IDD = IDD_DIALOG_NEW_EDIT_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxProjectName;
	CString m_strProjectName;
	CString m_strOldProjectName;
	virtual void OnOK();
	afx_msg void OnEnChangeProjectName();
	virtual BOOL OnInitDialog();
	CVoid SetEdit(CBool edit);
	CBool m_edit;
};

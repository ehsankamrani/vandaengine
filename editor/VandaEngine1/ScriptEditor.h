//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CScriptEditor dialog

class CScriptEditor : public CDialog
{
	DECLARE_DYNAMIC(CScriptEditor)

public:
	CScriptEditor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptEditor();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_EDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editScript;
	CRichEditCtrl m_richReport;
	afx_msg void OnBnClickedButtonApiUtility();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};

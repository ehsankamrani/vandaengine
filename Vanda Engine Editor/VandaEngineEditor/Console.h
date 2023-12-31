//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CConsole dialog

class CConsole : public CDialog
{
	DECLARE_DYNAMIC(CConsole)

public:
	CConsole(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConsole();
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONSOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richEditConsole;
	afx_msg void OnClose();
protected:
	virtual void OnCancel();
	virtual void OnOK();
public:
	afx_msg void OnBnClickedRemoveText();
};

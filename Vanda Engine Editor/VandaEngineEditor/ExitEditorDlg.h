//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "CustomButton.h"
#include "CustomBitmapButton.h"


// CExitEditorDlg dialog

class CExitEditorDlg : public CDialog
{
	DECLARE_DYNAMIC(CExitEditorDlg)

public:
	CExitEditorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExitEditorDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_EXIT_EDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenWebsite();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CCustomButton m_btnVisitWebsite;
	CCustomButton m_btnExit;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CCustomBitmapButton m_btnUncheck;
	CCustomBitmapButton m_btnCheck;
	afx_msg void OnBnClickedExitButtonCheck();
	afx_msg void OnBnClickedExitButtonUncheck();
	virtual BOOL OnInitDialog();
};

//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "custombitmapbutton.h"
#include "custombutton.h"
#include "afxwin.h"

// CWelcomeDialog dialog

class CWelcomeDialog : public CDialog
{
	DECLARE_DYNAMIC(CWelcomeDialog)

public:
	CWelcomeDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWelcomeDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG_WELCOME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedWelcomeButtonCheck();
	afx_msg void OnBnClickedWelcomeButtonUncheck();
	afx_msg void OnBnClickedDonate();
	afx_msg void OnBnClickedEmailme();
	afx_msg void OnBnClickedOfficialwebsite();
	afx_msg void OnBnClickedGithub();
	afx_msg void OnBnClickedSourceforge();
	afx_msg void OnBnClickedFacebook();

	CCustomBitmapButton m_btnCheck;
	CCustomBitmapButton m_btnUncheck;
	CCustomButton m_btnOK;
	CCustomButton m_btnDonateNow;
	CCustomButton m_btnWebsite;
	CCustomButton m_btnEmailMe;
	CCustomButton m_btnGitHub;
	CCustomButton m_btnSourceforge;
	CCustomButton m_btnFacebook;
};

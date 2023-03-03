//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditLight dialog

class CEditLight : public CDialog
{
	DECLARE_DYNAMIC(CEditLight)

public:
	CEditLight(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditLight();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxTolerance;
	afx_msg void OnEnChangeEditLightTolerance();
	afx_msg void OnBnClickedButtonAmbientLight();
	afx_msg void OnBnClickedButtonSpecularLight();
	afx_msg void OnEnChangeEditShininess();
	CEdit m_editBoxAmbientColor;
	CEdit m_editBoxSpecularColor;
	CEdit m_editBoxShininess;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CVoid SetCOLLADALight();
	COLORREF m_ambientColor, m_specularColor;
	CBrush m_ambientBrush, m_specularBrush;
	CFloat m_fAmbientColor[4];
	CFloat m_fSpecularColor[4];

	CFloat m_fShininess;
	CFloat m_fTolerance;
	CString m_strShininess;
	CString m_strTolerance;

protected:
	virtual void OnOK();
};

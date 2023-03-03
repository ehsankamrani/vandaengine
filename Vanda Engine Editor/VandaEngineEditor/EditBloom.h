//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditBloom dialog

class CEditBloom : public CDialog
{
	DECLARE_DYNAMIC(CEditBloom)

public:
	CEditBloom(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditBloom();

// Dialog Data
	enum { IDD = IDD_DIALOG_BLOOM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual INT_PTR DoModal();
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CButton m_checkBoxEnableBloom;
	CEdit m_editBoxBloomColor;
	CEdit m_editBoxBloomIntensity;
	CButton m_btnBloomColor;
	afx_msg void OnBnClickedButtonBloomColor();
	afx_msg void OnEnChangeBloomIntensity();
	void GetInformation();

	COLORREF m_bloomColor;
	CBrush m_bloomBrush;
	CFloat m_fBloomColor[4];
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_strBloomIntensity;
	CFloat m_bloomIntensity;
};

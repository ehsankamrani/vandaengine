//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CGeneralAmbientColor dialog

class CGeneralAmbientColor : public CDialog
{
	DECLARE_DYNAMIC(CGeneralAmbientColor)

public:
	CGeneralAmbientColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGeneralAmbientColor();

// Dialog Data
	enum { IDD = IDD_DIALOG_AMBIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxAmbientColor;
	CButton m_checkBoxUseAmbientColor;
	afx_msg void OnBnClickedButtonAmbient();
	COLORREF m_ambientColor;
	CBrush m_ambientBrush;
	CFloat m_fAmbientColor[4];
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

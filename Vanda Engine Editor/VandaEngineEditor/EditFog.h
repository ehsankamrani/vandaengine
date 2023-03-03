//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "GraphicsEngine/fog.h"

// CEditFog dialog

class CEditFog : public CDialog
{
	DECLARE_DYNAMIC(CEditFog)

public:
	CEditFog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditFog();

// Dialog Data
	enum { IDD = IDD_DIALOG_FOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxFogColor;
	afx_msg void OnBnClickedButtonFogColor();
private:
	COLORREF m_fogColor;
	CBrush m_fogBrush;
	CFloat m_fColor[4];

	CString m_strFogDensity;
	CFloat m_fogDensity;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	CEdit m_editBoxFogDensity;
	CButton m_checkBoxEnableFog;
	afx_msg void OnEnChangeEditFogDensity();
	CVoid GetInformation();
};

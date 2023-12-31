//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditOptions dialog

class CEditOptions : public CDialog
{
	DECLARE_DYNAMIC(CEditOptions)

public:
	CEditOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboMultisample;
	CComboBox m_comboAnisotropy;
	afx_msg void OnCbnSelchangeComboOptionsNumanisotropy();
	afx_msg void OnCbnSelchangeComboOptionsNumsamples();
	virtual BOOL OnInitDialog();
	CButton m_checkBoxShader;
	CButton m_checkBoxMultisample;
	CButton m_checkBoxAnisotropy;
	CButton m_checkBoxFBO;
	CButton m_checkBoxVBO;
	CButton m_checkBoxVSync;
	CButton m_checkBoxWaterReflection;
	CButton m_checkBoxWelcomeDialog;
	afx_msg void OnBnClickedOk();
};

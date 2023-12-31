//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddMultipleAnimations dialog

class CAddMultipleAnimations : public CDialog
{
	DECLARE_DYNAMIC(CAddMultipleAnimations)

public:
	CAddMultipleAnimations(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddMultipleAnimations();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_MULTIPLE_ANIMATIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddToList();
	afx_msg void OnBnClickedOk();
	CComboBox m_comboAnimations;
	CInt m_comboIndex;
	std::vector<std::string> m_animationNames;
	std::string m_baseModelName;
	afx_msg void OnBnClickedButtonAddBaseModel();
	CEdit m_editBoxBaseModel;
};

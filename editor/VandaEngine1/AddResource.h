//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAddResource dialog

class CAddResource : public CDialog
{
	DECLARE_DYNAMIC(CAddResource)

public:
	CAddResource(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddResource();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_RESOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNewDirectory();
	afx_msg void OnBnClickedButtonRemoveDirectory();
	afx_msg void OnBnClickedButtonAddResource();
	afx_msg void OnBnClickedButtonRemoveResource();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_comboDirectory;
	CVoid InserItemToList(char * name);
	CListCtrl m_listFiles;
	CInt m_index;
	CInt m_listIndex;
	afx_msg void OnCbnSelchangeCombPackage();
	CVoid SaveResFile();
};

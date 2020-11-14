//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddNewDirectory dialog

class CAddNewDirectory : public CDialog
{
	DECLARE_DYNAMIC(CAddNewDirectory)

public:
	CAddNewDirectory(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddNewDirectory();

// Dialog Data
	enum { IDD = IDD_DIALOG_NEW_DIRECTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editNewDirectory;
	afx_msg void OnEnChangeDirectoryName();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CChar* GetDirectoryName();
private:
	CString m_strNewDirectory;
	CChar m_newDirectory[MAX_NAME_SIZE];
};

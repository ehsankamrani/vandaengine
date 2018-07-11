//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditSceneManager dialog

class CEditSceneManager : public CDialog
{
	DECLARE_DYNAMIC(CEditSceneManager)

public:
	CEditSceneManager(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditSceneManager();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_SCENEMANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditScenemanagerObjectPerSplit();
	CEdit m_editBoxObjectsPerSplit;
protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
private:
	CString m_strObjectsPerSplit;
	CInt m_iObjectsPerSplit;
public:
	afx_msg void OnBnClickedOk();
};

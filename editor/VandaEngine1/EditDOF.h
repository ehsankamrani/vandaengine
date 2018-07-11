//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditDOF dialog

class CEditDOF : public CDialog
{
	DECLARE_DYNAMIC(CEditDOF)

public:
	CEditDOF(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditDOF();

// Dialog Data
	enum { IDD = IDD_DIALOG_DOF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxFocalDistance;
	CEdit m_editBoxFocalRange;
	CButton m_checkBoxEnableDOF;
	afx_msg void OnEnChangeEditFocalDistance();
	afx_msg void OnEnChangeEditFocalRange();
	virtual BOOL OnInitDialog();
	CVoid GetInformation();

private:
	CString m_strFocalDistance;
	CString m_strFocalRange;
	CFloat m_focalDistance;
	CFloat m_focalRange;
protected:
	virtual void OnOK();
public:
	CButton m_checkBoxDebug;
};

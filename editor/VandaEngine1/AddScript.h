//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CAddScript dialog

class CAddScript : public CDialog
{
	DECLARE_DYNAMIC(CAddScript)

public:
	CAddScript(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddScript();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnTriggerEnter();
	afx_msg void OnBnClickedBtnTriggerExit();
	CRichEditCtrl m_editBoxEnter;
	CRichEditCtrl m_editBoxExit;

	CString m_strTriggerExitScriptName;
	CString m_strTriggerEnterScriptName;
	CRichEditCtrl m_reportScriptInfo;
	CInstanceGeometry* m_instanceGeo;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDeleteTriggerRemove();
	afx_msg void OnBnClickedBtnDeleteTriggerEnter();
	CVoid SetInstanceGeo( CInstanceGeometry* instanceGeo );
	CBool m_changed;
protected:
	virtual void OnOK();
};

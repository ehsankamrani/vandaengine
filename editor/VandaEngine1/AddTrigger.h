//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "defines.h"
#include "afxcmn.h"


// CAddTrigger dialog
class CTrigger;

class CAddTrigger : public CDialog
{
	DECLARE_DYNAMIC(CAddTrigger)

public:
	CAddTrigger(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddTrigger();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_TRIGGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_comboTrigger;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombTrigger();
	CTriggerType m_triggerType;
	CTrigger* m_trigger;
	CEdit m_editBoxTrigger;
	CString m_strTriggerName;
	afx_msg void OnEnChangeEditTrigger();
	CVoid Init(CTrigger* trigger);
	CRichEditCtrl m_editBoxScript;
	afx_msg void OnBnClickedBtnAddTrigger();
	afx_msg void OnBnClickedBtnRemoveTrigger();
private:
	CBool m_changed;
	CString m_strScript;
	CBool m_hasScript;
public:
	afx_msg void OnBnClickedButtonViewScript();
};

//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "CustomRichEditCtrl.h"

// CScriptEditor dialog

class CScriptEditor : public CDialog
{
	DECLARE_DYNAMIC(CScriptEditor)

public:
	CScriptEditor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptEditor();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_EDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richReport;
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CVoid LoadFile(CChar* filePath);
	CVoid WriteFile(CChar* filePath);
	CCustomRichEditCtrl m_richScriptEditor;
	CBool m_changed;
	CBool SaveChanges();
	CString savePath;
	afx_msg void OnEnChangeRichedScriptEditor();
	CVoid PrintScriptInfo(CString strText, COLORREF color);
	afx_msg void OnNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CViewScript dialog

class CViewScript : public CDialog
{
	DECLARE_DYNAMIC(CViewScript)
private:
	CChar m_scriptPath[MAX_URI_SIZE];
public:
	CViewScript(CWnd* pParent = NULL);   // standard constructor
	virtual ~CViewScript();

// Dialog Data
	enum { IDD = IDD_DIALOG_VIEW_SCRIPT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richViewScript;
	virtual BOOL OnInitDialog();
	CVoid SetScriptPath(CChar* path) { Cpy(m_scriptPath, path); }
	CChar* GetScriptPath() { return m_scriptPath; }
	CVoid LoadFile(CChar* filePath);
};

//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptEditor.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptEditor.h"
#include "afxdialogex.h"


// CScriptEditor dialog

IMPLEMENT_DYNAMIC(CScriptEditor, CDialog)

CScriptEditor::CScriptEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEditor::IDD, pParent)
{

}

CScriptEditor::~CScriptEditor()
{
}

void CScriptEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCRIPT_EDITOR, m_editScript);
	DDX_Control(pDX, IDC_RICHED_REPORT, m_richReport);
}


BEGIN_MESSAGE_MAP(CScriptEditor, CDialog)
	ON_BN_CLICKED(ID_BUTTON_API_UTILITY, &CScriptEditor::OnBnClickedButtonApiUtility)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CANCEL, &CScriptEditor::OnBnClickedCancel)
END_MESSAGE_MAP()


// CScriptEditor message handlers


void CScriptEditor::OnBnClickedButtonApiUtility()
{
	// TODO: Add your control notification handler code here
}


void CScriptEditor::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}


void CScriptEditor::OnBnClickedCancel()
{
	OnCancel();
}


BOOL CScriptEditor::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

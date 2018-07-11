//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddScript.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddScript.h"


// CAddScript dialog

IMPLEMENT_DYNAMIC(CAddScript, CDialog)

CAddScript::CAddScript(CWnd* pParent /*=NULL*/)
	: CDialog(CAddScript::IDD, pParent)
{
	ex_pRichEditScript = &m_reportScriptInfo;
	m_instanceGeo = NULL;
	m_changed = CFalse;
}

CAddScript::~CAddScript()
{
}

void CAddScript::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TRIGGER_ENTER, m_editBoxEnter);
	DDX_Control(pDX, IDC_EDIT_TRIGGER_EXIT, m_editBoxExit);
	DDX_Control(pDX, IDC_RICHEDIT_REPORT_SCRIPT_INFO, m_reportScriptInfo);
}


BEGIN_MESSAGE_MAP(CAddScript, CDialog)
	ON_BN_CLICKED(IDC_BTN_TRIGGER_ENTER, &CAddScript::OnBnClickedBtnTriggerEnter)
	ON_BN_CLICKED(IDC_BTN_TRIGGER_EXIT, &CAddScript::OnBnClickedBtnTriggerExit)
	ON_BN_CLICKED(IDC_BTN_DELETE_TRIGGER_REMOVE, &CAddScript::OnBnClickedBtnDeleteTriggerRemove)
	ON_BN_CLICKED(IDC_BTN_DELETE_TRIGGER_ENTER, &CAddScript::OnBnClickedBtnDeleteTriggerEnter)
END_MESSAGE_MAP()


// CAddScript message handlers

void CAddScript::OnBnClickedBtnTriggerEnter()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		g_testScript = CTrue;
		CString m_string;
		m_string = (CString)dlgOpen.GetPathName();

		int s = luaL_loadfile(g_lua, m_string);
		if ( s==0 ) {
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		LuaReportErrors(g_lua, s);
		if( s == 0 )
		{
			m_editBoxEnter.SetWindowText( m_string );
			m_strTriggerEnterScriptName = m_string;
			m_changed = CTrue;
			PrintScriptInfo("Script loaded scuccessfully", COLOR_GREEN);
		}
		g_testScript = CFalse;
	}
}

void CAddScript::OnBnClickedBtnTriggerExit()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		g_testScript = CTrue;
		CString m_string;
		m_string = (CString)dlgOpen.GetPathName();

		int s = luaL_loadfile(g_lua, m_string);
		if ( s==0 )
		{
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		LuaReportErrors(g_lua, s);
		if( s == 0 )
		{
			m_editBoxExit.SetWindowText( m_string );
			m_strTriggerExitScriptName = m_string;
			m_changed = CTrue;
			PrintScriptInfo("Script loaded scuccessfully", COLOR_GREEN);
		}
		g_testScript = CFalse;
	}
}


BOOL CAddScript::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_editBoxEnter.SetWindowTextA( m_instanceGeo->m_enterScript );
	m_editBoxExit.SetWindowTextA( m_instanceGeo->m_exitScript );
	if( !Cmp(m_instanceGeo->m_enterScript, "\n" ) )
		m_strTriggerEnterScriptName = m_instanceGeo->m_enterScript;
	if( !Cmp(m_instanceGeo->m_exitScript, "\n" ) )
		m_strTriggerExitScriptName = m_instanceGeo->m_exitScript;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddScript::OnBnClickedBtnDeleteTriggerRemove()
{
	m_editBoxExit.SetWindowTextA( "\n" );
	m_strTriggerExitScriptName.Empty();
}

void CAddScript::OnBnClickedBtnDeleteTriggerEnter()
{
	m_editBoxEnter.SetWindowTextA( "\n" );
	m_strTriggerEnterScriptName.Empty();
}

CVoid CAddScript::SetInstanceGeo( CInstanceGeometry* instanceGeo )
{
	m_instanceGeo = instanceGeo;
}


void CAddScript::OnOK()
{
	if( !m_strTriggerEnterScriptName.IsEmpty() )
	{
		m_instanceGeo->m_hasEnterScript = m_instanceGeo->m_updateEnterScript = CTrue;
		Cpy( m_instanceGeo->m_enterScript, m_strTriggerEnterScriptName.GetBuffer( m_strTriggerEnterScriptName.GetLength() ) );
		m_strTriggerEnterScriptName.ReleaseBuffer();
	}
	else
	{
		m_instanceGeo->m_hasEnterScript = m_instanceGeo->m_updateEnterScript = CFalse;
		Cpy( m_instanceGeo->m_enterScript, "\n" );
	}

	if( !m_strTriggerExitScriptName.IsEmpty() )
	{
		m_instanceGeo->m_hasExitScript = m_instanceGeo->m_updateExitScript = CTrue;
		Cpy( m_instanceGeo->m_exitScript, m_strTriggerExitScriptName.GetBuffer( m_strTriggerExitScriptName.GetLength() ) );
		m_strTriggerExitScriptName.ReleaseBuffer();
	}
	else
	{
		m_instanceGeo->m_hasExitScript = m_instanceGeo->m_updateExitScript = CFalse;
		Cpy( m_instanceGeo->m_exitScript, "\n" );
	}
	if( m_changed )
	{
		for (CUInt index = 0; index < g_allPrefabNames.size(); index++)
		{
			m_instanceGeo->m_node->GetScene()->IsInPrefabList(g_allPrefabNames[index].c_str(), CFalse, CTrue);
		}
	}
	CDialog::OnOK();
}

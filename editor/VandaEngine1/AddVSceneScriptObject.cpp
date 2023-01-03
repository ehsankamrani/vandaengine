//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddVSceneScriptObject.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddVSceneScriptObject.h"
#include "afxdialogex.h"
#include "ScriptEditor.h"
#include "ViewScript.h"

// CAddVSceneScriptObject dialog

IMPLEMENT_DYNAMIC(CAddVSceneScriptObject, CDialog)

CAddVSceneScriptObject::CAddVSceneScriptObject(CWnd* pParent /*=NULL*/)
	: CDialog(CAddVSceneScriptObject::IDD, pParent)
	, m_strName(_T(""))
	, m_strScript(_T(""))
{
	m_updateScript = CFalse;
	Cpy(m_strOldName, "\n");
	m_create = CTrue;
}

CAddVSceneScriptObject::~CAddVSceneScriptObject()
{
}

void CAddVSceneScriptObject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VSCENE_SCRIPT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_SCRIPT, m_editScript);
}


BEGIN_MESSAGE_MAP(CAddVSceneScriptObject, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SCRIPT, &CAddVSceneScriptObject::OnBnClickedButtonAddScript)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_SCRIPT, &CAddVSceneScriptObject::OnBnClickedButtonRemoveScript)
	ON_BN_CLICKED(IDOK, &CAddVSceneScriptObject::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_VSCENE_SCRIPT_NAME, &CAddVSceneScriptObject::OnEnChangeEditVSceneScriptName)
	ON_EN_CHANGE(IDC_EDIT_SCRIPT, &CAddVSceneScriptObject::OnEnChangeEditScript)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_SCRIPT, &CAddVSceneScriptObject::OnBnClickedButtonViewScript)
END_MESSAGE_MAP()


// CAddVSceneScriptObject message handlers


void CAddVSceneScriptObject::OnBnClickedButtonAddScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		g_testScript = CTrue;
		CString m_string;
		m_string = (CString)dlgOpen.GetPathName();

		lua_close(g_lua);
		g_lua = LuaNewState();
		LuaOpenLibs(g_lua);
		LuaRegisterFunctions(g_lua);

		int s = luaL_loadfile(g_lua, m_string);
		if (s == 0) {
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		if (s == 0)
		{
			m_editScript.SetWindowText(m_string);
			m_strScript = m_string;
			m_updateScript = CTrue;
			PrintInfo("\nScript loaded scuccessfully", COLOR_GREEN);
		}
		else
		{
			MessageBox("Script contains error(s).\nPlease use script editor to fix the issue(s)", "Error", MB_OK | MB_ICONERROR);
		}
		g_testScript = CFalse;
	}
}

void CAddVSceneScriptObject::OnBnClickedButtonRemoveScript()
{
	if (!m_strScript.IsEmpty())
	{
		if (MessageBox("Remove current script?", "Warning", MB_YESNO) == IDYES)
		{
			m_strScript.Empty();
			m_editScript.SetWindowTextA("\n");
			m_updateScript = CTrue;
		}
	}
}

void CAddVSceneScriptObject::OnBnClickedOk()
{
	if (m_create)
	{
		if (g_multipleView->IsPlayGameMode())
		{
			if (MessageBox("Exit from play mode?", "Vanda Engine Error", MB_YESNO | MB_ICONINFORMATION) == IDYES)
			{
				ex_pVandaEngine1Dlg->OnBnClickedBtnPlayActive();

			}
			else
			{
				return;
			}
		}
	}

	if (m_strName.IsEmpty() || m_strScript.IsEmpty())
	{
		MessageBox("Please specify name as well as script", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
	{
		CChar engineObjectCapsName[MAX_NAME_SIZE];
		Cpy(engineObjectCapsName, (*it).c_str());
		StringToUpper(engineObjectCapsName);

		CChar currentObjectName[MAX_NAME_SIZE];
		Cpy(currentObjectName, (LPCSTR)m_strName);
		StringToUpper(currentObjectName);

		CChar oldObjectName[MAX_NAME_SIZE];
		Cpy(oldObjectName, (LPCSTR)m_strOldName);
		StringToUpper(oldObjectName);

		if (!Cmp(oldObjectName, engineObjectCapsName) && Cmp(currentObjectName, engineObjectCapsName))
		{
			MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	if (m_create)
	{
		if (!g_VSceneScript)
			g_VSceneScript = CNew(CVSceneScript);
		CChar name[MAX_NAME_SIZE];
		CChar path[MAX_URI_SIZE];
		Cpy(name, m_strName.GetBuffer(m_strName.GetLength()));
		Cpy(path, m_strScript.GetBuffer(m_strScript.GetLength()));
		g_VSceneScript->SetName(name);
		g_VSceneScript->SetScriptPath(path);
		g_VSceneScript->SetUpdateScript(m_updateScript);

		ex_pVandaEngine1Dlg->InsertItemToEngineObjectList(name, eENGINEOBJECTLIST_VSCENESCRIPT);
		ex_pVandaEngine1Dlg->m_mainBtnVSceneScript.EnableWindow(FALSE);
		ex_pVandaEngine1Dlg->GetMenu()->EnableMenuItem(ID_INSERT_VSCENE_SCRIPT, MF_DISABLED);
		g_menu.m_insertVSceneScript = CTrue;
		g_showArrow = CFalse;

		g_engineObjectNames.push_back(name);

		for (int k = 0; k < ex_pVandaEngine1Dlg->m_listBoxEngineObjects.GetItemCount(); k++)
		{
			if (Cmp(name, ex_pVandaEngine1Dlg->m_listBoxEngineObjects.GetItemText(k, 0)))
			{
				ex_pVandaEngine1Dlg->m_listBoxEngineObjects.SetItemState(k, LVIS_SELECTED, LVIS_SELECTED);
				ex_pVandaEngine1Dlg->m_listBoxEngineObjects.SetSelectionMark(k);
				ex_pVandaEngine1Dlg->m_listBoxEngineObjects.Update(k);
			}
			else
			{
				ex_pVandaEngine1Dlg->m_listBoxEngineObjects.SetItemState(k, ~LVIS_SELECTED, LVIS_SELECTED);
				ex_pVandaEngine1Dlg->m_listBoxEngineObjects.Update(k);
			}
		}
	}
	CDialog::OnOK();
}


BOOL CAddVSceneScriptObject::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!m_strName.IsEmpty())
		m_editName.SetWindowTextA(m_strName);
	if (!m_strScript.IsEmpty())
		m_editScript.SetWindowTextA(m_strScript);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddVSceneScriptObject::OnEnChangeEditVSceneScriptName()
{
	m_editName.GetWindowTextA(m_strName);
}


void CAddVSceneScriptObject::OnEnChangeEditScript()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

CVoid CAddVSceneScriptObject::SetCreate(CBool state)
{
	m_create = state;
}

CBool CAddVSceneScriptObject::GetCreate()
{
	return m_create;
}

void CAddVSceneScriptObject::OnBnClickedButtonViewScript()
{
	if (m_strScript.IsEmpty())
	{
		MessageBox("Please add a script!", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CViewScript* dlg = CNew(CViewScript);
	dlg->SetScriptPath(m_strScript.GetBuffer(m_strScript.GetLength()));
	m_strScript.ReleaseBuffer();
	dlg->DoModal();
	CDelete(dlg);
}

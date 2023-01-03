//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddTrigger.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddTrigger.h"
#include "afxdialogex.h"
#include "ViewScript.h"

// CAddTrigger dialog

IMPLEMENT_DYNAMIC(CAddTrigger, CDialog)

CAddTrigger::CAddTrigger(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTrigger::IDD, pParent)
{
	m_triggerType = eTRIGGER_BOX;
	m_trigger = NULL;
	m_changed = CFalse;
	m_hasScript = CFalse;
}

CAddTrigger::~CAddTrigger()
{
}

void CAddTrigger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_TRIGGER, m_comboTrigger);
	DDX_Control(pDX, IDC_EDIT_TRIGGER, m_editBoxTrigger);
	DDX_Control(pDX, IDC_EDIT_TRIGGER_SCRIPT, m_editBoxScript);
}


BEGIN_MESSAGE_MAP(CAddTrigger, CDialog)
	ON_BN_CLICKED(IDOK, &CAddTrigger::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMB_TRIGGER, &CAddTrigger::OnCbnSelchangeCombTrigger)
	ON_EN_CHANGE(IDC_EDIT_TRIGGER, &CAddTrigger::OnEnChangeEditTrigger)
	ON_BN_CLICKED(IDC_BTN_ADD_TRIGGER, &CAddTrigger::OnBnClickedBtnAddTrigger)
	ON_BN_CLICKED(IDC_BTN_REMOVE_TRIGGER, &CAddTrigger::OnBnClickedBtnRemoveTrigger)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_SCRIPT, &CAddTrigger::OnBnClickedButtonViewScript)
END_MESSAGE_MAP()


// CAddTrigger message handlers


void CAddTrigger::OnBnClickedOk()
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

	if (m_strTriggerName.IsEmpty())
	{
		MessageBox("Please select a name for this trigger", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (m_strScript.IsEmpty())
	{
		MessageBox("Please select a script for this trigger", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	CChar name[MAX_NAME_SIZE];
	Cpy(name, (CChar*)m_strTriggerName.GetBuffer(m_strTriggerName.GetLength()));
	m_strTriggerName.ReleaseBuffer();

	std::string s(name);
	int n = s.length();
	if (n > 3)
	{
		if (s[0] == 't' && s[1] == 'e' && s[2] == 'm' && s[3] == 'p')
		{
			MessageBox("temp string at the beginning of trigger name is not allowed", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			return;
		}
	}

	CChar oldName[MAX_NAME_SIZE];
	Cpy(oldName, "\n");
	if (m_trigger)
		Cpy(oldName, m_trigger->GetName());

	for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
	{
		CChar engineObjectCapsName[MAX_NAME_SIZE];
		Cpy(engineObjectCapsName, (*it).c_str());
		StringToUpper(engineObjectCapsName);

		CChar currentObjectName[MAX_NAME_SIZE];
		Cpy(currentObjectName, name);
		StringToUpper(currentObjectName);

		CChar oldObjectName[MAX_NAME_SIZE];
		Cpy(oldObjectName, oldName);
		StringToUpper(oldObjectName);

		if (!Cmp(oldObjectName, engineObjectCapsName) && Cmp(currentObjectName, engineObjectCapsName))
		{
			MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	if (!Cmp(oldName, "\n"))
	{
		for (CUInt i = 0; i < g_engineObjectNames.size(); i++)
		{
			if (Cmp(g_engineObjectNames[i].c_str(), oldName))
				g_engineObjectNames[i] = "";
		}
	}

	CTrigger* new_trigger = NULL;
	CVec3f translation;
	CVec4f rotation;
	CVec3f scaling;

	if (m_trigger)
	{
		new_trigger = m_trigger;
		translation = m_trigger->GetInstancePrefab()->GetTranslate();
		rotation = m_trigger->GetInstancePrefab()->GetRotate();
		scaling = m_trigger->GetInstancePrefab()->GetScale();
	}
	else
		new_trigger = CNew(CTrigger);
	new_trigger->SetName(name);

	if (!m_trigger)
	{
		new_trigger->SetLastName(name);
	}

	CChar packageName[MAX_NAME_SIZE];
	CChar prefabName[MAX_NAME_SIZE];

	Cpy(packageName, "Vanda_Basics");
	
	if (m_triggerType == eTRIGGER_BOX)
	{
		Cpy(prefabName, "Box_Trigger");
		new_trigger->SetTriggerType(eTRIGGER_BOX);
	}
	else
	{
		Cpy(prefabName, "Sphere_Trigger");
		new_trigger->SetTriggerType(eTRIGGER_SPHERE);
	}

	new_trigger->SetHasScript(m_hasScript);
	new_trigger->SetUpdateScript(m_changed);
	if (m_hasScript)
	{
		new_trigger->SetScript(m_strScript.GetBuffer(m_strScript.GetLength()));
		m_strScript.ReleaseBuffer();
	}

	g_importPrefab = CTrue;

	CBool PhysXCam = CFalse;
	CBool selected = CFalse;
	if (m_trigger)
	{
		g_arrowPosition = translation;
		g_arrowRotate.x = rotation.x; g_arrowRotate.y = rotation.y; g_arrowRotate.z = rotation.z;
		g_arrowScale = scaling;
		if (g_selectedName == m_trigger->GetInstancePrefab()->GetNameIndex())
			selected = CTrue;
		m_trigger->Destroy();

	}
	else
	{
		g_arrowPosition.x = g_arrowPosition.y = g_arrowPosition.z = 0.0f;
		g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
		g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = 1.0f;
	}

	ex_pVandaEngine1Dlg->m_dlgPrefabs = CNew(CPrefabDlg);
	ex_pDlgPrefabs = ex_pVandaEngine1Dlg->m_dlgPrefabs;
	ex_pVandaEngine1Dlg->OnMenuClickedInsertPrefab(NULL, packageName, prefabName);

	new_trigger->SetInstancePrefab(g_instancePrefab[g_instancePrefab.size() - 1]); //last element
	new_trigger->GetInstancePrefab()->SetIsTrigger(CTrue);
	CDelete(ex_pVandaEngine1Dlg->m_dlgPrefabs);

	g_importPrefab = CFalse;

	if (selected)
	{
		g_selectedName = new_trigger->GetInstancePrefab()->GetNameIndex();
	}

	if (m_trigger)
	{
		new_trigger->GetInstancePrefab()->SetTranslate(translation);
		new_trigger->GetInstancePrefab()->SetRotate(rotation);
		new_trigger->GetInstancePrefab()->SetScale(scaling);
		new_trigger->GetInstancePrefab()->UpdateBoundingBox(CTrue);
		new_trigger->GetInstancePrefab()->CalculateDistance();
		//new_trigger->GetInstancePrefab()->UpdateIsStaticOrAnimated();
	}
	else
	{
		g_triggers.push_back(new_trigger);
		ex_pVandaEngine1Dlg->InsertItemToEngineObjectList(new_trigger->GetName(), eENGINEOBJECTLIST_TRIGGER);
		g_engineObjectNames.push_back(new_trigger->GetName());
	}

	CChar triggerName[MAX_NAME_SIZE];
	Cpy(triggerName, new_trigger->GetName());

	for (int k = 0; k < ex_pVandaEngine1Dlg->m_listBoxEngineObjects.GetItemCount(); k++)
	{
		if (Cmp(triggerName, ex_pVandaEngine1Dlg->m_listBoxEngineObjects.GetItemText(k, 0)))
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

	//Erase all items of m_listBoxEngineObjects
	for (int k = 0; k < ex_pVandaEngine1Dlg->m_listBoxScenes.GetItemCount(); k++)
	{
		ex_pVandaEngine1Dlg->m_listBoxScenes.SetItemState(k, ~LVIS_SELECTED, LVIS_SELECTED);
		ex_pVandaEngine1Dlg->m_listBoxScenes.Update(k);
	}
	ex_pVandaEngine1Dlg->m_btnRemoveScene.EnableWindow(FALSE);
	ex_pVandaEngine1Dlg->m_btnSceneProperties.EnableWindow(FALSE);

	g_multipleView->SetElapsedTimeFromBeginning();

	if (g_editorMode == eMODE_VSCENE)
		g_multipleView->RenderQueries(CTrue);

	CDialog::OnOK();
}


BOOL CAddTrigger::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_comboTrigger.InsertString(0, "Box");
	m_comboTrigger.InsertString(1, "Sphere");
	if (m_trigger)
	{
		m_triggerType = m_trigger->GetTriggerType();
		m_comboTrigger.SetCurSel(m_triggerType);
	}
	else
		m_comboTrigger.SetCurSel(0);

	m_comboTrigger.UpdateWindow();

	if (m_trigger)
	{
		m_editBoxTrigger.SetWindowTextA(m_trigger->GetName());
		if (m_trigger->GetHasScript())
		{
			m_editBoxScript.SetWindowTextA(m_trigger->GetScript());
			m_strScript = m_trigger->GetScript();
			m_changed = m_trigger->GetUpdateScript();
			m_hasScript = CTrue;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddTrigger::OnCbnSelchangeCombTrigger()
{
	CInt curSel = m_comboTrigger.GetCurSel();
	switch (curSel)
	{
	case eTRIGGER_BOX: //box
		m_triggerType = eTRIGGER_BOX;
		break;
	case eTRIGGER_SPHERE: //sphere
		m_triggerType = eTRIGGER_SPHERE;
		break;
	default:
		break;
	}
}

void CAddTrigger::OnEnChangeEditTrigger()
{
	m_editBoxTrigger.GetWindowTextA(m_strTriggerName);
}

CVoid CAddTrigger::Init(CTrigger* trigger)
{
	m_trigger = trigger;
}


void CAddTrigger::OnBnClickedBtnAddTrigger()
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
			m_editBoxScript.SetWindowText(m_string);
			m_strScript = m_string;
			m_changed = CTrue;
			m_hasScript = CTrue;
			PrintInfo("\nScript loaded scuccessfully", COLOR_GREEN);
		}
		else
		{
			MessageBox("Script contains error(s).\nPlease use script editor to fix the issue(s)", "Error", MB_OK | MB_ICONERROR);
		}
		g_testScript = CFalse;
	}
}


void CAddTrigger::OnBnClickedBtnRemoveTrigger()
{
	if (!m_strScript.IsEmpty())
	{
		if (MessageBox("Remove current script?", "Warning", MB_YESNO) == IDYES)
		{
			m_editBoxScript.SetWindowTextA("\n");
			m_strScript.Empty();
			m_hasScript = CFalse;
		}
	}
}


void CAddTrigger::OnBnClickedButtonViewScript()
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

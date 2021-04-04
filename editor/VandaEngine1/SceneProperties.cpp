//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SceneProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "SceneProperties.h"
#include "GraphicsEngine/Animation.h"
// CSceneProperties dialog

IMPLEMENT_DYNAMIC(CSceneProperties, CDialog)

CSceneProperties::CSceneProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CSceneProperties::IDD, pParent)
{
	m_updateScript = CFalse;
	m_hasScript = CFalse;
}

CSceneProperties::~CSceneProperties()
{
}

void CSceneProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAY_ANIMATION_ENABLECHECK, m_checkBoxPlayAnimation);
	DDX_Control(pDX, IDC_LOOP_ANIMATION_ENABLECHECK2, m_checkBoxLoopAnimation);
	DDX_Control(pDX, IDC_COMBO_ANIMATION_CLIP, m_comboAnimationClip);
	DDX_Control(pDX, IDC_ALWAYS_VISIBLE, m_checkBoxAlwaysVisible);
	DDX_Control(pDX, IDC_CASTSHADOW, m_checkBoxCastShadow);
	DDX_Control(pDX, IDC_PREFAB_SCRIPT_PATH, m_editBoxScriptPath);
	DDX_Control(pDX, IDC_RICHED_ANIMATION_NAME, m_richAnimationName);
}


BEGIN_MESSAGE_MAP(CSceneProperties, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_ANIMATION_CLIP, &CSceneProperties::OnCbnSelchangeComboAnimationClip)
	ON_BN_CLICKED(IDC_BTN_ADD_PREFAB_SCRIPT, &CSceneProperties::OnBnClickedBtnAddPrefabScript)
	ON_BN_CLICKED(IDC_BTN_REMOVE_PREFAB_SCRIPT, &CSceneProperties::OnBnClickedBtnRemovePrefabScript)
	ON_BN_CLICKED(IDC_BUTTON_COPY_ANIMATION, &CSceneProperties::OnBnClickedButtonCopyAnimation)
END_MESSAGE_MAP()


// CSceneProperties message handlers

BOOL CSceneProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	if( g_prefabProperties.m_playAnimationAtStart )
		m_checkBoxPlayAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxPlayAnimation.SetCheck( BST_UNCHECKED );

	if (g_prefabProperties.m_loopAnimationAtStart)
		m_checkBoxLoopAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxLoopAnimation.SetCheck( BST_UNCHECKED );

	if (g_prefabProperties.m_alwaysVisible)
	{
		m_checkBoxAlwaysVisible.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkBoxAlwaysVisible.SetCheck(BST_UNCHECKED);
	}

	if (g_prefabProperties.m_castShadow)
	{
		m_checkBoxCastShadow.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkBoxCastShadow.SetCheck(BST_UNCHECKED);
	}

	for( CUInt i = 0; i < g_prefabProperties.m_names.size(); i++ )
	{
		m_comboAnimationClip.InsertString(i, g_prefabProperties.m_names[i].c_str());
	}
	m_currentAnimClip = g_prefabProperties.m_clipIndex;
	m_comboAnimationClip.SetCurSel( m_currentAnimClip );

	if (m_comboAnimationClip.GetCount())
	{
		CString s;
		m_comboAnimationClip.GetLBText(m_comboAnimationClip.GetCurSel(), s);
		m_richAnimationName.SetWindowTextA(s);
		CInt end = m_richAnimationName.GetWindowTextLengthA();
		m_richAnimationName.SetSel(0, end);
	}

	if (!Cmp(g_prefabProperties.m_scriptPath, "\n"))
	{
		m_editBoxScriptPath.SetWindowText(g_prefabProperties.m_scriptPath);
		m_strScriptName = g_prefabProperties.m_scriptPath;
		m_updateScript = g_prefabProperties.m_updateScript;
		m_hasScript = CTrue;
	}
	else
	{
		m_hasScript = CFalse;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSceneProperties::OnOK()
{
	CInt checkState;
	checkState = m_checkBoxPlayAnimation.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_playAnimationAtStart = CTrue;
	else
		g_prefabProperties.m_playAnimationAtStart = CFalse;

	checkState = m_checkBoxLoopAnimation.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_loopAnimationAtStart = CTrue;
	else
		g_prefabProperties.m_loopAnimationAtStart = CFalse;

	checkState = m_checkBoxAlwaysVisible.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_alwaysVisible = CTrue;
	else
		g_prefabProperties.m_alwaysVisible = CFalse;

	checkState = m_checkBoxCastShadow.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_castShadow = CTrue;
	else
		g_prefabProperties.m_castShadow = CFalse;

	for (CUInt i = 0; i < g_prefabProperties.m_names.size(); i++)
	{
		if (Cmp(g_prefabProperties.m_names[m_currentAnimClip].c_str(), g_prefabProperties.m_names[i].c_str()))
		{
			g_prefabProperties.m_clipIndex = i;
		}
	}

	if (!m_strScriptName.IsEmpty())
	{
		Cpy(g_prefabProperties.m_scriptPath, m_strScriptName.GetBuffer(m_strScriptName.GetLength()));
		m_strScriptName.ReleaseBuffer();
		g_prefabProperties.m_updateScript = m_updateScript;
		g_prefabProperties.m_hasScript = CTrue;
	}
	else
	{
		Cpy(g_prefabProperties.m_scriptPath, "\n");
		g_prefabProperties.m_hasScript = CFalse;
	}

	if (g_prefabProperties.m_hasScript)
	{
		//reset lua
		lua_close(g_lua);
		g_lua = LuaNewState();
		LuaOpenLibs(g_lua);
		LuaRegisterFunctions(g_lua);

		if (!LuaLoadFile(g_lua, g_prefabProperties.m_scriptPath))
			MessageBox("Couldn't load the script", "Error");
	}


	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CScene* m_scene = g_scene[i];

		m_scene->m_playAnimation = g_prefabProperties.m_playAnimationAtStart;
		m_scene->m_loopAnimationAtStartup = g_prefabProperties.m_loopAnimationAtStart;
		m_scene->m_alwaysVisible = g_prefabProperties.m_alwaysVisible;
		m_scene->m_castShadow = g_prefabProperties.m_castShadow;
		m_scene->SetClipIndexForStartup(g_prefabProperties.m_clipIndex);
	}

	CDialog::OnOK();
}

void CSceneProperties::OnCbnSelchangeComboAnimationClip()
{
	m_currentAnimClip = m_comboAnimationClip.GetCurSel();
	CString s;
	m_comboAnimationClip.GetLBText(m_comboAnimationClip.GetCurSel(), s);
	m_richAnimationName.SetWindowTextA(s);
	CInt end = m_richAnimationName.GetWindowTextLengthA();
	m_richAnimationName.SetSel(0, end);
}

void CSceneProperties::OnBnClickedBtnAddPrefabScript()
{
	CFileDialog dlgOpen(TRUE, _T("*.lua"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("LUA File (*.lua)|*.lua||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		g_testScript = CTrue;
		CString m_string;
		m_string = (CString)dlgOpen.GetPathName();

		int s = luaL_loadfile(g_lua, m_string);
		if (s == 0) {
			// execute Lua program
			s = LuaExecuteProgram(g_lua);
		}
		if (s == 0)
		{
			m_editBoxScriptPath.SetWindowText(m_string);
			m_strScriptName = m_string;
			m_updateScript = CTrue;
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


void CSceneProperties::OnBnClickedBtnRemovePrefabScript()
{
	m_editBoxScriptPath.SetWindowTextA("\n");
	m_strScriptName.Empty();
}


void CSceneProperties::OnBnClickedButtonCopyAnimation()
{
	CString s;
	m_richAnimationName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select an animation from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richAnimationName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}

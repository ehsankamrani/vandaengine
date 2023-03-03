//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddVideo.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "afxdialogex.h"
#include "AddVideo.h"
#include "ViewScript.h"

// CAddVideo dialog

IMPLEMENT_DYNAMIC(CAddVideo, CDialog)

CAddVideo::CAddVideo(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_ADD_VIDEO, pParent)
{
	m_loop = m_play = CFalse;
	m_create = CFalse; //I assume the user wants to edit the dialog data at the beginning. To change it, use the SetCreate() function.
	m_editMode = CFalse;
	m_dataUpdated = CFalse;
	m_scriptUpdated = CFalse;
	m_hasScript = CFalse;
}

CAddVideo::~CAddVideo()
{
	m_strScript.ReleaseBuffer();
}

void CAddVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_VIDEO_DATA, m_editBoxVideoData);
	DDX_Control(pDX, IDC_EDIT_VIDEO_SCRIPT, m_editBoxScript);
	DDX_Control(pDX, IDC_COMBO_VIDEO_PLAY, m_comboVideoPlay);
	DDX_Control(pDX, IDC_EDIT_VIDEO_NAME, m_editBoxVideoName);
	DDX_Control(pDX, IDC_COMBO_VIDEO_LOOP, m_comboVideoLoop);
	DDX_Control(pDX, IDC_EDIT_AUDIO_VOLUME, m_editBoxAudioVolume);
}


BEGIN_MESSAGE_MAP(CAddVideo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_DATA, &CAddVideo::OnBnClickedButtonVideoData)
	ON_BN_CLICKED(IDC_BTN_ADD_SCRIPT, &CAddVideo::OnBnClickedBtnAddScript)
	ON_BN_CLICKED(IDC_BTN_REMOVE_SCRIPT, &CAddVideo::OnBnClickedBtnRemoveScript)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_SCRIPT, &CAddVideo::OnBnClickedButtonViewScript)
	ON_EN_CHANGE(IDC_EDIT_VIDEO_NAME, &CAddVideo::OnEnChangeEditVideoName)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_LOOP, &CAddVideo::OnCbnSelchangeComboVideoLoop)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEO_PLAY, &CAddVideo::OnCbnSelchangeComboVideoPlay)
	ON_EN_CHANGE(IDC_EDIT_AUDIO_VOLUME, &CAddVideo::OnEnChangeEditAudioVolume)
END_MESSAGE_MAP()


// CAddVideo message handlers

BOOL CAddVideo::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_create)
	{
		CChar VideoPath[MAX_NAME_SIZE];
		sprintf(VideoPath, "%s%s", g_pathProperties.m_videoPath, "defaultVideo.mp4");
		m_strVideoDataPath = VideoPath;
		m_strAudioVolume = "1.0";
		m_strVideoDataFileName = "defaultVideo";
		Cpy(m_videoFileName, "defaultVideo.mp4");
		m_dataUpdated = CTrue;
	}

	if (m_editMode)
	{
		if (m_hasScript)
		{
			m_editBoxScript.SetWindowTextA(m_strScript);
		}
	}

	m_editBoxVideoName.SetWindowTextA(m_strVideoName);
	m_editBoxVideoData.SetWindowTextA(m_strVideoDataPath);
	m_editBoxAudioVolume.SetWindowTextA(m_strAudioVolume);

	m_comboVideoPlay.InsertString(0, "True");
	m_comboVideoPlay.InsertString(1, "False");
	if (m_play)
		m_comboVideoPlay.SetCurSel(0);
	else
		m_comboVideoPlay.SetCurSel(1);

	m_comboVideoPlay.UpdateWindow();

	m_comboVideoLoop.InsertString(0, "True");
	m_comboVideoLoop.InsertString(1, "False");
	if (m_loop)
		m_comboVideoLoop.SetCurSel(0);
	else
		m_comboVideoLoop.SetCurSel(1);

	m_comboVideoLoop.UpdateWindow();

	m_strVideoTempName = m_strVideoName;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddVideo::OnBnClickedButtonVideoData()
{
	static char szFilter[] = "MP4 (*.mp4)|*.mp4|MOV (*.mov)|*.mov|AVI (*.avi)|*.avi||";

	CFileDialog dlgOpen(TRUE, _T("*.mp4"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		szFilter, NULL, NULL);

	if (IDOK == dlgOpen.DoModal())
	{
		m_strVideoDataPath = (CString)dlgOpen.GetPathName();
		m_strVideoDataFileName = dlgOpen.GetFileTitle();

		CChar* videoPath = (CChar*)m_strVideoDataPath.GetBuffer(m_strVideoDataPath.GetLength());
		CChar* fileAfterPath = GetAfterPath(videoPath);
		Cpy(m_videoFileName, fileAfterPath);

		m_editBoxVideoData.SetWindowText(m_strVideoDataPath);

		m_strVideoDataPath.ReleaseBuffer();

		m_dataUpdated = CTrue;
	}
}


void CAddVideo::OnBnClickedBtnAddScript()
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
			m_scriptUpdated = CTrue;
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


void CAddVideo::OnBnClickedBtnRemoveScript()
{
	if (!m_hasScript)
	{
		MessageBox("No script was found!", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_hasScript)
	{
		if (MessageBox("Remove current script?", "Warning", MB_YESNO) == IDYES)
		{
			m_editBoxScript.SetWindowTextA("\n");
			m_strScript.Empty();
			m_hasScript = CFalse;
		}
	}
}


void CAddVideo::OnBnClickedButtonViewScript()
{
	if (!m_hasScript)
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


void CAddVideo::OnOK()
{
	CBool compare = CFalse;
	if (!m_strVideoName.IsEmpty())
	{
		compare = CTrue;
		if (m_editMode)
		{
			CChar name[MAX_NAME_SIZE];
			CChar tempName[MAX_NAME_SIZE];
			Cpy(name, (LPCSTR)m_strVideoName);
			Cpy(tempName, (LPCSTR)m_strVideoTempName);

			StringToUpper(name);
			StringToUpper(tempName);

			if (Cmp(name, tempName))
				compare = CFalse;
		}
	}
	else
		compare = CFalse;

	if (compare)
	{
		for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
		{
			CChar engineObjectCapsName[MAX_NAME_SIZE];
			Cpy(engineObjectCapsName, (*it).c_str());
			StringToUpper(engineObjectCapsName);

			CChar currentObjectName[MAX_NAME_SIZE];
			Cpy(currentObjectName, (LPCSTR)m_strVideoName);
			StringToUpper(currentObjectName);

			if (Cmp(currentObjectName, engineObjectCapsName))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}

	if (m_strVideoName.IsEmpty() || m_strVideoDataPath.IsEmpty() || m_strAudioVolume.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_volume > 1.0f || m_volume < 0.0f)
	{
		MessageBox("Volume must be in [0,1] range", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CDialog::OnOK();
}


void CAddVideo::OnEnChangeEditVideoName()
{
	m_editBoxVideoName.GetWindowTextA(m_strVideoName);
}


void CAddVideo::OnCbnSelchangeComboVideoLoop()
{
	CInt curSel = m_comboVideoLoop.GetCurSel();

	switch (curSel)
	{
	case 0: //true;
		m_loop = CTrue;
		break;
	case 1: //false;
		m_loop = CFalse;
		break;
	}
}


void CAddVideo::OnCbnSelchangeComboVideoPlay()
{
	CInt curSel = m_comboVideoPlay.GetCurSel();
	switch (curSel)
	{
	case 0: //true;
		m_play = CTrue;
		break;
	case 1: //false;
		m_play = CFalse;
		break;
	}
}


void CAddVideo::OnEnChangeEditAudioVolume()
{
	m_editBoxAudioVolume.GetWindowTextA(m_strAudioVolume);
	m_volume = atof(m_strAudioVolume);
}

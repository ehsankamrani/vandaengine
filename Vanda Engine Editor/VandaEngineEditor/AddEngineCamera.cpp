//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddEngineCamera.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "AddEngineCamera.h"
#include "afxdialogex.h"
#include "ViewScript.h"

// CAddEngineCamera dialog

IMPLEMENT_DYNAMIC(CAddEngineCamera, CDialog)

CAddEngineCamera::CAddEngineCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEngineCamera::IDD, pParent)
{
	m_create = CTrue;
	m_isActive = CFalse;
	m_scriptUpdated = CFalse;
	m_hasScript = CFalse;
}

CAddEngineCamera::~CAddEngineCamera()
{
	m_strScript.ReleaseBuffer();
}

void CAddEngineCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POS_X, m_editBoxPosX);
	DDX_Control(pDX, IDC_POS_Y, m_editBoxPosY);
	DDX_Control(pDX, IDC_POS_Z, m_editBoxPosZ);
	DDX_Control(pDX, IDC_NCP, m_editBoxNCP);
	DDX_Control(pDX, IDC_FCP, m_editBoxFCP);
	DDX_Control(pDX, IDC_EDIT_CAMERA_NAME, m_editBoxCameraName);
	DDX_Control(pDX, IDC_FOV, m_editBoxFOV);
	DDX_Control(pDX, IDC_PAN, m_editBoxPan);
	DDX_Control(pDX, IDC_TILT, m_editBoxTilt);
	DDX_Control(pDX, IDC_BUTTON_ACTIVATE, m_activateButton);
	DDX_Control(pDX, IDC_EDIT_CAMERA_SCRIPT, m_editBoxScript);
}


BEGIN_MESSAGE_MAP(CAddEngineCamera, CDialog)
	ON_BN_CLICKED(IDOK, &CAddEngineCamera::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_NAME, &CAddEngineCamera::OnEnChangeEditCameraName)
	ON_EN_CHANGE(IDC_POS_X, &CAddEngineCamera::OnEnChangePosX)
	ON_EN_CHANGE(IDC_POS_Y, &CAddEngineCamera::OnEnChangePosY)
	ON_EN_CHANGE(IDC_POS_Z, &CAddEngineCamera::OnEnChangePosZ)
	ON_EN_CHANGE(IDC_NCP, &CAddEngineCamera::OnEnChangeNcp)
	ON_EN_CHANGE(IDC_FCP, &CAddEngineCamera::OnEnChangeFcp)
	ON_EN_CHANGE(IDC_FOV, &CAddEngineCamera::OnEnChangeFov)
	ON_BN_CLICKED(IDC_BUTTON_ACTIVATE, &CAddEngineCamera::OnBnClickedButtonActivate)
	ON_EN_CHANGE(IDC_PAN, &CAddEngineCamera::OnEnChangePan)
	ON_EN_CHANGE(IDC_TILT, &CAddEngineCamera::OnEnChangeTilt)
	ON_BN_CLICKED(IDC_BTN_ADD_SCRIPT, &CAddEngineCamera::OnBnClickedBtnAddScript)
	ON_BN_CLICKED(IDC_BTN_REMOVE_SCRIPT, &CAddEngineCamera::OnBnClickedBtnRemoveScript)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_SCRIPT, &CAddEngineCamera::OnBnClickedButtonViewScript)
END_MESSAGE_MAP()


// CAddEngineCamera message handlers


void CAddEngineCamera::OnBnClickedOk()
{
	if (m_strName.IsEmpty() || m_strPosX.IsEmpty() || m_strPosY.IsEmpty() || m_strPosZ.IsEmpty() || m_strPan.IsEmpty()
		|| m_strTilt.IsEmpty() || m_strFOV.IsEmpty() || m_strNCP.IsEmpty() || m_strFCP.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_ncp <= 0.0)
	{
		MessageBox("Near clip plane must be greater than 0.0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_fcp <= 0.0)
	{
		MessageBox("Far clip plane must be greater than 0.0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CBool compare = CFalse;
	if (!m_strName.IsEmpty())
	{
		compare = CTrue;
		if (!m_create)
		{
			CChar name[MAX_NAME_SIZE];
			CChar tempName[MAX_NAME_SIZE];
			Cpy(name, (LPCSTR)m_strName);
			Cpy(tempName, (LPCSTR)m_strTempName);

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
			Cpy(currentObjectName, (LPCSTR)m_strName);
			StringToUpper(currentObjectName);

			if (Cmp(currentObjectName, engineObjectCapsName))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}

	if (!m_strName.IsEmpty())
	{
		CChar name[MAX_NAME_SIZE];
		Cpy(name, (LPCSTR)m_strName);
		StringToUpper(name);

		if (Cmp(name, "THIS"))
		{
			MessageBox("'this' is a reserved name. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	CDialog::OnOK();
}


BOOL CAddEngineCamera::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_create)
	{
		m_strPan = m_strTilt = "0.0";
		m_strFOV = "54.0";
		m_strPosX = m_strPosY = m_strPosZ = "0.0";
		m_strNCP = "0.01"; m_strFCP = "5000.0";

		m_editBoxPan.SetWindowTextA(m_strPan);
		m_editBoxTilt.SetWindowTextA(m_strTilt);
		m_editBoxFOV.SetWindowTextA(m_strFOV);
		m_editBoxNCP.SetWindowTextA(m_strNCP);
		m_editBoxFCP.SetWindowTextA(m_strFCP);
		m_editBoxPosX.SetWindowTextA(m_strPosX);
		m_editBoxPosY.SetWindowTextA(m_strPosY);
		m_editBoxPosZ.SetWindowTextA(m_strPosZ);
		m_activateButton.EnableWindow(FALSE);
	}
	else
	{
		m_editBoxCameraName.SetWindowTextA(m_strName);
		m_editBoxPan.SetWindowTextA(m_strPan);
		m_editBoxTilt.SetWindowTextA(m_strTilt);
		m_editBoxFOV.SetWindowTextA(m_strFOV);
		m_editBoxNCP.SetWindowTextA(m_strNCP);
		m_editBoxFCP.SetWindowTextA(m_strFCP);
		m_editBoxPosX.SetWindowTextA(m_strPosX);
		m_editBoxPosY.SetWindowTextA(m_strPosY);
		m_editBoxPosZ.SetWindowTextA(m_strPosZ);
		m_activateButton.EnableWindow(TRUE);

		if (m_hasScript)
		{
			m_editBoxScript.SetWindowTextA(m_strScript);
		}
	}

	m_strTempName = m_strName;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddEngineCamera::OnEnChangeEditCameraName()
{
	m_editBoxCameraName.GetWindowTextA(m_strName);
}


void CAddEngineCamera::OnEnChangePosX()
{
	m_editBoxPosX.GetWindowTextA(m_strPosX);
	m_posX = atof(m_strPosX);
}


void CAddEngineCamera::OnEnChangePosY()
{
	m_editBoxPosY.GetWindowTextA(m_strPosY);
	m_posY = atof(m_strPosY);
}


void CAddEngineCamera::OnEnChangePosZ()
{
	m_editBoxPosZ.GetWindowTextA(m_strPosZ);
	m_posZ = atof(m_strPosZ);
}

void CAddEngineCamera::OnEnChangeNcp()
{
	m_editBoxNCP.GetWindowTextA(m_strNCP);
	m_ncp = atof(m_strNCP);
}


void CAddEngineCamera::OnEnChangeFcp()
{
	m_editBoxFCP.GetWindowTextA(m_strFCP);
	m_fcp = atof(m_strFCP);
}


void CAddEngineCamera::OnEnChangeFov()
{
	m_editBoxFOV.GetWindowTextA(m_strFOV);
	m_fov = atof(m_strFOV);
}


void CAddEngineCamera::OnBnClickedButtonActivate()
{
	m_isActive = CTrue;
	CDialog::OnOK();
}


void CAddEngineCamera::OnEnChangePan()
{
	m_editBoxPan.GetWindowTextA(m_strPan);
	m_pan = atof(m_strPan);
}


void CAddEngineCamera::OnEnChangeTilt()
{
	m_editBoxTilt.GetWindowTextA(m_strTilt);
	m_tilt = atof(m_strTilt);
}


void CAddEngineCamera::OnBnClickedBtnAddScript()
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


void CAddEngineCamera::OnBnClickedBtnRemoveScript()
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


void CAddEngineCamera::OnBnClickedButtonViewScript()
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

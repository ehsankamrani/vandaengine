//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddEngineCamera.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddEngineCamera.h"
#include "afxdialogex.h"


// CAddEngineCamera dialog

IMPLEMENT_DYNAMIC(CAddEngineCamera, CDialog)

CAddEngineCamera::CAddEngineCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEngineCamera::IDD, pParent)
{
	m_create = CTrue;
	m_isActive = CFalse;
}

CAddEngineCamera::~CAddEngineCamera()
{
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

//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditCamera.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditCamera.h"
#include "afxdialogex.h"


// CEditCamera dialog

IMPLEMENT_DYNAMIC(CEditCamera, CDialog)

CEditCamera::CEditCamera(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCamera::IDD, pParent)
{

}

CEditCamera::~CEditCamera()
{
}

void CEditCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_FREE_PERSPECTIVE_CAMERA_FOV2, m_richEditFreeCameraFOV);
	DDX_Control(pDX, IDC_RICHEDIT_FREE_PERSPECTIVE_CAMERA_NCP2, m_richEditFreeCameraNCP);
	DDX_Control(pDX, IDC_RICHEDIT_FREE_PERSPECTIVE_CAMERA_FCP2, m_richEditFreeCameraFCP);
	DDX_Control(pDX, IDC_RICHEDIT_PERSPECTIVE_CAMERA_FOV, m_richEditPlayModeCameraFOV);
	DDX_Control(pDX, IDC_RICHEDIT_PERSPECTIVE_CAMERA_NCP, m_richEditPlayModeCameraNCP);
	DDX_Control(pDX, IDC_RICHEDIT_PERSPECTIVE_CAMERA_FCP, m_richEditPlayModeCameraFCP);
	DDX_Control(pDX, IDC_RICHEDIT_PERSPECTIVE_CAMERA_MINFOV, m_richEditPlayModeCameraMinFOV);
	DDX_Control(pDX, IDC_RICHEDIT_PERSPECTIVE_CAMERA_MAXFOV, m_richEditPlayModeCameraMaxFOV);
	DDX_Control(pDX, IDC_RICHEDIT_DAE_CAMERA_FOV, m_richEditColladaCameraFOV);
	DDX_Control(pDX, IDC_RICHEDIT_DAE_CAMERA_NEAR_CLIP_PLANE, m_richEditColladaCameraNCP);
	DDX_Control(pDX, IDC_RICHEDIT_DAE_CAMERA_FAR_CLIP_PLANE, m_richEditColladaCameraFCP);
	DDX_Control(pDX, IDC_OPTIONS_DAE_CAMERA_READ_FOV_FROM_FILE, m_btnCheckColladaFOV);
	DDX_Control(pDX, IDC_OPTIONS_DAE_CAMERA_READ_NCP_FROM_FILE, m_btnCheckColladaNCP);
	DDX_Control(pDX, IDC_OPTIONS_DAE_CAMERA_READ_FCP_FROM_FILE, m_btnCheckColladaFCP);
}


BEGIN_MESSAGE_MAP(CEditCamera, CDialog)
	ON_BN_CLICKED(IDOK, &CEditCamera::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_RESET_CAMERA_PROPERTIES, &CEditCamera::OnBnClickedButtonResetCameraProperties)
	ON_BN_CLICKED(IDC_OPTIONS_DAE_CAMERA_READ_FOV_FROM_FILE, &CEditCamera::OnBnClickedOptionsDaeCameraReadFovFromFile)
	ON_BN_CLICKED(IDC_OPTIONS_DAE_CAMERA_READ_NCP_FROM_FILE, &CEditCamera::OnBnClickedOptionsDaeCameraReadNCPFromFile)
	ON_BN_CLICKED(IDC_OPTIONS_DAE_CAMERA_READ_FCP_FROM_FILE, &CEditCamera::OnBnClickedOptionsDaeCameraReadFCPFromFile)
END_MESSAGE_MAP()


// CEditCamera message handlers


BOOL CEditCamera::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Free Perspective Camera Properties
	m_strFreeCameraFOV.Format(_T("%.3f"), g_render.GetDefaultInstanceCamera()->m_abstractCamera->GetAngle());
	m_richEditFreeCameraFOV.SetWindowTextA(m_strFreeCameraFOV);

	m_strFreeCameraNCP.Format(_T("%.3f"), g_cameraProperties.m_freePerspectiveNCP);
	m_richEditFreeCameraNCP.SetWindowTextA(m_strFreeCameraNCP);

	m_strFreeCameraFCP.Format(_T("%.3f"), g_cameraProperties.m_freePerspectiveFCP);
	m_richEditFreeCameraFCP.SetWindowTextA(m_strFreeCameraFCP);


	//play mode perspective camera properties
	m_strPlayModeCameraFOV.Format(_T("%.3f"), g_cameraProperties.m_playModePerspectiveFOV);
	m_richEditPlayModeCameraFOV.SetWindowTextA(m_strPlayModeCameraFOV);

	m_strPlayModeCameraMinFOV.Format(_T("%.3f"), g_cameraProperties.m_playModePerspectiveMinFOV);
	m_richEditPlayModeCameraMinFOV.SetWindowTextA(m_strPlayModeCameraMinFOV);

	m_strPlayModeCameraMaxFOV.Format(_T("%.3f"), g_cameraProperties.m_playModePerspectiveMaxFOV);
	m_richEditPlayModeCameraMaxFOV.SetWindowTextA(m_strPlayModeCameraMaxFOV);

	m_strPlayModeCameraNCP.Format(_T("%.3f"), g_cameraProperties.m_playModePerspectiveNCP);
	m_richEditPlayModeCameraNCP.SetWindowTextA(m_strPlayModeCameraNCP);

	m_strPlayModeCameraFCP.Format(_T("%.3f"), g_cameraProperties.m_playModePerspectiveFCP);
	m_richEditPlayModeCameraFCP.SetWindowTextA(m_strPlayModeCameraFCP);

	//Collada Cameras loaded from dae file
	m_strDAECameraFOV.Format(_T("%.3f"), g_cameraProperties.m_daeCameraFOV);
	m_richEditColladaCameraFOV.SetWindowTextA(m_strDAECameraFOV);

	m_strDAECameraNCP.Format(_T("%.3f"), g_cameraProperties.m_daeCameraNCP);
	m_richEditColladaCameraNCP.SetWindowTextA(m_strDAECameraNCP);

	m_strDAECameraFCP.Format(_T("%.3f"), g_cameraProperties.m_daeCameraFCP);
	m_richEditColladaCameraFCP.SetWindowTextA(m_strDAECameraFCP);

	//check fov
	if (g_cameraProperties.m_readDAECameraFOVFromFile)
	{
		m_btnCheckColladaFOV.SetCheck(BST_CHECKED);
		m_richEditColladaCameraFOV.EnableWindow(FALSE);
	}
	else
	{
		m_btnCheckColladaFOV.SetCheck(BST_UNCHECKED);
		m_richEditColladaCameraFOV.EnableWindow(TRUE);
	}

	//check ncp
	if (g_cameraProperties.m_readDAECameraNCPFromFile)
	{
		m_btnCheckColladaNCP.SetCheck(BST_CHECKED);
		m_richEditColladaCameraNCP.EnableWindow(FALSE);
	}
	else
	{
		m_btnCheckColladaNCP.SetCheck(BST_UNCHECKED);
		m_richEditColladaCameraNCP.EnableWindow(TRUE);
	}

	//check fcp
	if (g_cameraProperties.m_readDAECameraFCPFromFile)
	{
		m_btnCheckColladaFCP.SetCheck(BST_CHECKED);
		m_richEditColladaCameraFCP.EnableWindow(FALSE);
	}
	else
	{
		m_btnCheckColladaFCP.SetCheck(BST_UNCHECKED);
		m_richEditColladaCameraFCP.EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditCamera::OnBnClickedOk()
{
	//fov
	m_richEditFreeCameraFOV.GetWindowTextA(m_strFreeCameraFOV);
	if (m_strFreeCameraFOV.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera FOV");
		return;
	}
	g_cameraProperties.m_freePerspectiveFOV = atof(m_strFreeCameraFOV);
	g_render.GetDefaultInstanceCamera()->m_abstractCamera->SetAngle(atof(m_strFreeCameraFOV));
	//ncp
	m_richEditFreeCameraNCP.GetWindowTextA(m_strFreeCameraNCP);
	if (m_strFreeCameraNCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera NCP");
		return;
	}
	g_cameraProperties.m_freePerspectiveNCP = atof(m_strFreeCameraNCP);

	//fcp 
	m_richEditFreeCameraFCP.GetWindowTextA(m_strFreeCameraFCP);
	if (m_strFreeCameraFCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera FCP");
		return;
	}
	g_cameraProperties.m_freePerspectiveFCP = atof(m_strFreeCameraFCP);

	//fov
	m_richEditPlayModeCameraFOV.GetWindowTextA(m_strPlayModeCameraFOV);
	if (m_strPlayModeCameraFOV.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera FOV");
		return;
	}
	g_cameraProperties.m_playModePerspectiveFOV = atof(m_strPlayModeCameraFOV);

	//min fov
	m_richEditPlayModeCameraMinFOV.GetWindowTextA(m_strPlayModeCameraMinFOV);
	if (m_strPlayModeCameraMinFOV.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera Min FOV");
		return;
	}
	g_cameraProperties.m_playModePerspectiveMinFOV = atof(m_strPlayModeCameraMinFOV);

	//max fov
	m_richEditPlayModeCameraMaxFOV.GetWindowTextA(m_strPlayModeCameraMaxFOV);
	if (m_strPlayModeCameraMaxFOV.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera Max FOV");
		return;
	}
	g_cameraProperties.m_playModePerspectiveMaxFOV = atof(m_strPlayModeCameraMaxFOV);

	//ncp
	m_richEditPlayModeCameraNCP.GetWindowTextA(m_strPlayModeCameraNCP);
	if (m_strPlayModeCameraNCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera NCP");
		return;
	}
	g_cameraProperties.m_playModePerspectiveNCP = atof(m_strPlayModeCameraNCP);

	//fcp
	m_richEditPlayModeCameraFCP.GetWindowTextA(m_strPlayModeCameraFCP);
	if (m_strPlayModeCameraFCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Perspective Camera FCP");
		return;
	}
	g_cameraProperties.m_playModePerspectiveFCP = atof(m_strPlayModeCameraFCP);

	//fov
	m_richEditColladaCameraFOV.GetWindowTextA(m_strDAECameraFOV);
	if (m_strDAECameraFOV.IsEmpty())
	{
		MessageBox("Please Enter a Value for Collada Camera FOV");
		return;
	}
	g_cameraProperties.m_daeCameraFOV = atof(m_strDAECameraFOV);

	//ncp
	m_richEditColladaCameraNCP.GetWindowTextA(m_strDAECameraNCP);
	if (m_strDAECameraNCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Collada Camera NCP");
		return;
	}
	g_cameraProperties.m_daeCameraNCP = atof(m_strDAECameraNCP);

	//fcp
	m_richEditColladaCameraFCP.GetWindowTextA(m_strDAECameraFCP);
	if (m_strDAECameraFCP.IsEmpty())
	{
		MessageBox("Please Enter a Value for Collada Camera FCP");
		return;
	}
	g_cameraProperties.m_daeCameraFCP = atof(m_strDAECameraFCP);

	//check fov
	CInt checkState = m_btnCheckColladaFOV.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_cameraProperties.m_readDAECameraFOVFromFile = CTrue;
	}
	else
	{
		g_cameraProperties.m_readDAECameraFOVFromFile = CFalse;
	}

	//check ncp
	checkState = m_btnCheckColladaNCP.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_cameraProperties.m_readDAECameraNCPFromFile = CTrue;
	}
	else
	{
		g_cameraProperties.m_readDAECameraNCPFromFile = CFalse;
	}

	//check fcp
	checkState = m_btnCheckColladaFCP.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_cameraProperties.m_readDAECameraFCPFromFile = CTrue;
	}
	else
	{
		g_cameraProperties.m_readDAECameraFCPFromFile = CFalse;
	}

	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();

	if (g_camera && g_camera->m_cameraManager)
	{
		g_camera->m_cameraManager->SetDefaultAngle(g_cameraProperties.m_playModePerspectiveFOV);
		g_camera->m_cameraManager->SetMinAngle(g_cameraProperties.m_playModePerspectiveMinFOV);
		g_camera->m_cameraManager->SetMaxAngle(g_cameraProperties.m_playModePerspectiveMaxFOV);
		g_camera->m_cameraManager->SetZNear(g_cameraProperties.m_playModePerspectiveNCP);
		g_camera->m_cameraManager->SetZFar(g_cameraProperties.m_playModePerspectiveFCP);

		if (g_camera->m_cameraManager->GetAngle() > g_camera->m_cameraManager->GetMaxAngle())
			g_camera->m_cameraManager->SetAngle(g_camera->m_cameraManager->GetMaxAngle());

		if (g_camera->m_cameraManager->GetAngle() < g_camera->m_cameraManager->GetMinAngle())
			g_camera->m_cameraManager->SetAngle(g_camera->m_cameraManager->GetMinAngle());
	}

	CDialog::OnOK();
}


void CEditCamera::OnBnClickedButtonResetCameraProperties()
{
	if (MessageBox("reset factory Camera settings?", "Vanda Engine", MB_YESNO | MB_ICONINFORMATION) == IDYES)
	{
		CCameraProperties cameraProperties;
		//Free Perspective Camera Properties
		m_strFreeCameraFOV.Format(_T("%.3f"), cameraProperties.m_freePerspectiveFOV);
		m_richEditFreeCameraFOV.SetWindowTextA(m_strFreeCameraFOV);

		m_strFreeCameraNCP.Format(_T("%.3f"), cameraProperties.m_freePerspectiveNCP);
		m_richEditFreeCameraNCP.SetWindowTextA(m_strFreeCameraNCP);

		m_strFreeCameraFCP.Format(_T("%.3f"), cameraProperties.m_freePerspectiveFCP);
		m_richEditFreeCameraFCP.SetWindowTextA(m_strFreeCameraFCP);


		//play mode perspective camera properties
		m_strPlayModeCameraFOV.Format(_T("%.3f"), cameraProperties.m_playModePerspectiveFOV);
		m_richEditPlayModeCameraFOV.SetWindowTextA(m_strPlayModeCameraFOV);

		m_strPlayModeCameraMinFOV.Format(_T("%.3f"), cameraProperties.m_playModePerspectiveMinFOV);
		m_richEditPlayModeCameraMinFOV.SetWindowTextA(m_strPlayModeCameraMinFOV);

		m_strPlayModeCameraMaxFOV.Format(_T("%.3f"), cameraProperties.m_playModePerspectiveMaxFOV);
		m_richEditPlayModeCameraMaxFOV.SetWindowTextA(m_strPlayModeCameraMaxFOV);

		m_strPlayModeCameraNCP.Format(_T("%.3f"), cameraProperties.m_playModePerspectiveNCP);
		m_richEditPlayModeCameraNCP.SetWindowTextA(m_strPlayModeCameraNCP);

		m_strPlayModeCameraFCP.Format(_T("%.3f"), cameraProperties.m_playModePerspectiveFCP);
		m_richEditPlayModeCameraFCP.SetWindowTextA(m_strPlayModeCameraFCP);

		//Collada Cameras loaded from dae file
		m_strDAECameraFOV.Format(_T("%.3f"), cameraProperties.m_daeCameraFOV);
		m_richEditColladaCameraFOV.SetWindowTextA(m_strDAECameraFOV);

		m_strDAECameraNCP.Format(_T("%.3f"), cameraProperties.m_daeCameraNCP);
		m_richEditColladaCameraNCP.SetWindowTextA(m_strDAECameraNCP);

		m_strDAECameraFCP.Format(_T("%.3f"), cameraProperties.m_daeCameraFCP);
		m_richEditColladaCameraFCP.SetWindowTextA(m_strDAECameraFCP);

		//check fov
		if (cameraProperties.m_readDAECameraFOVFromFile)
		{
			m_btnCheckColladaFOV.SetCheck(BST_CHECKED);
			m_richEditColladaCameraFOV.EnableWindow(FALSE);
		}
		else
		{
			m_btnCheckColladaFOV.SetCheck(BST_UNCHECKED);
			m_richEditColladaCameraFOV.EnableWindow(TRUE);
		}

		//check ncp
		if (cameraProperties.m_readDAECameraNCPFromFile)
		{
			m_btnCheckColladaNCP.SetCheck(BST_CHECKED);
			m_richEditColladaCameraNCP.EnableWindow(FALSE);
		}
		else
		{
			m_btnCheckColladaNCP.SetCheck(BST_UNCHECKED);
			m_richEditColladaCameraNCP.EnableWindow(TRUE);
		}

		//check fcp
		if (cameraProperties.m_readDAECameraFCPFromFile)
		{
			m_btnCheckColladaFCP.SetCheck(BST_CHECKED);
			m_richEditColladaCameraFCP.EnableWindow(FALSE);
		}
		else
		{
			m_btnCheckColladaFCP.SetCheck(BST_UNCHECKED);
			m_richEditColladaCameraFCP.EnableWindow(TRUE);
		}

	}
}

void CEditCamera::OnBnClickedOptionsDaeCameraReadFovFromFile()
{
	//check fov
	if (m_btnCheckColladaFOV.GetCheck())
	{
		m_richEditColladaCameraFOV.EnableWindow(FALSE);
	}
	else
	{
		m_richEditColladaCameraFOV.EnableWindow(TRUE);
	}
}


void CEditCamera::OnBnClickedOptionsDaeCameraReadNCPFromFile()
{
	//check ncp
	if (m_btnCheckColladaNCP.GetCheck())
	{
		m_richEditColladaCameraNCP.EnableWindow(FALSE);
	}
	else
	{
		m_richEditColladaCameraNCP.EnableWindow(TRUE);
	}
}


void CEditCamera::OnBnClickedOptionsDaeCameraReadFCPFromFile()
{
	//check fcp
	if (m_btnCheckColladaFCP.GetCheck())
	{
		m_richEditColladaCameraFCP.EnableWindow(FALSE);
	}
	else
	{
		m_richEditColladaCameraFCP.EnableWindow(TRUE);
	}
}

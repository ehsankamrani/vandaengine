//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// MainCharacterProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "MainCharacterProperties.h"
#include "afxdialogex.h"


// CMainCharacterProperties dialog

IMPLEMENT_DYNAMIC(CMainCharacterProperties, CDialog)

CMainCharacterProperties::CMainCharacterProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CMainCharacterProperties::IDD, pParent)
{
	m_camera = new CUpdateCamera();
}

CMainCharacterProperties::~CMainCharacterProperties()
{
	CDelete(m_camera);
}

void CMainCharacterProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WALK_CHARACTER_SPEED, m_editWalkSpeed);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_RUN_SPEED, m_editRunSpeed);
	DDX_Control(pDX, IDC_EDIT_CAMERA_CHARACTER_DISTANCE, m_editBoxCameraCharacterDistance);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_POWER, m_editBoxCharacterPower);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_RADIUS, m_editBoxCapsuleRadius);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_HEIGHT, m_editBoxCapsuleHeight);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_SKIN_WIDTH, m_editBoxCharacterSkinWidth);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_STEP_OFFSET, m_editBoxCharacterStepOffset);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_JUMP_POWER, m_editBoxJumpPower);
	DDX_Control(pDX, IDC_CHECK_JUMP, m_checkBoxJumping);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_SLOPE_LIMIT, m_editBoxCharacterSlopeLimit);
	DDX_Control(pDX, IDC_CHECK_DEBUG_MODE, m_checkBoxDebugMode);
	DDX_Control(pDX, IDC_EDIT_IDLE_DELAY_IN, m_editBoxIdleDelayIn);
	DDX_Control(pDX, IDC_EDIT_WALK_DELAY_IN, m_editBoxWalkDelayIn);
	DDX_Control(pDX, IDC_EDIT_RUN_DELAY_IN, m_editBoxRunDelayIn);
	DDX_Control(pDX, IDC_EDIT_JUMP_DELAY_IN, m_editBoxJumpDelayIn);
	DDX_Control(pDX, IDC_EDIT_JUMP_DELAY_OUT, m_editBoxJumpDelayOut);
	DDX_Control(pDX, IDC_EDIT_CAMERA_DEFAULT_FOV, m_editBoxDefaultFOV);
	DDX_Control(pDX, IDC_EDIT_CAMERA_MIN_FOV, m_editBoxMinFOV);
	DDX_Control(pDX, IDC_EDIT_CAMERA_MAX_FOV, m_editBoxMaxFOV);
	DDX_Control(pDX, IDC_EDIT_CAMERA_DEFAULT_TILT, m_editBoxDefaultTilt);
	DDX_Control(pDX, IDC_EDIT_CAMERA_MIN_TILT, m_editBoxMinTilt);
	DDX_Control(pDX, IDC_EDIT_CAMERA_MAX_TILT, m_editBoxMaxTilt);
}


BEGIN_MESSAGE_MAP(CMainCharacterProperties, CDialog)
	ON_EN_CHANGE(IDC_EDIT_WALK_CHARACTER_SPEED, &CMainCharacterProperties::OnEnChangeEditWalkCharacterSpeed)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_RUN_SPEED, &CMainCharacterProperties::OnEnChangeEditCharacterRunSpeed)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_CHARACTER_DISTANCE, &CMainCharacterProperties::OnEnChangeEditCameraCharacterDistance)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_POWER, &CMainCharacterProperties::OnEnChangeEditCharacterPower)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_RADIUS, &CMainCharacterProperties::OnEnChangeEditCharacterRadius)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_HEIGHT, &CMainCharacterProperties::OnEnChangeEditCharacterHeight)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_SLOPE_LIMIT, &CMainCharacterProperties::OnEnChangeEditCharacterSlopeLimit)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_SKIN_WIDTH, &CMainCharacterProperties::OnEnChangeEditCharacterSkinWidth)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_STEP_OFFSET, &CMainCharacterProperties::OnEnChangeEditCharacterStepOffset)
	ON_EN_CHANGE(IDC_EDIT_CHARACTER_JUMP_POWER, &CMainCharacterProperties::OnEnChangeEditCharacterJumpPower)
	ON_BN_CLICKED(IDOK, &CMainCharacterProperties::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CMainCharacterProperties::OnBnClickedButtonReset)
	ON_EN_CHANGE(IDC_EDIT_IDLE_DELAY_IN, &CMainCharacterProperties::OnEnChangeEditIdleDelayIn)
	ON_EN_CHANGE(IDC_EDIT_WALK_DELAY_IN, &CMainCharacterProperties::OnEnChangeEditWalkDelayIn)
	ON_EN_CHANGE(IDC_EDIT_RUN_DELAY_IN, &CMainCharacterProperties::OnEnChangeEditRunDelayIn)
	ON_EN_CHANGE(IDC_EDIT_JUMP_DELAY_IN, &CMainCharacterProperties::OnEnChangeEditJumpDelayIn)
	ON_EN_CHANGE(IDC_EDIT_JUMP_DELAY_OUT, &CMainCharacterProperties::OnEnChangeEditJumpDelayOut)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_DEFAULT_FOV, &CMainCharacterProperties::OnEnChangeEditCameraDefaultFov)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MIN_FOV, &CMainCharacterProperties::OnEnChangeEditCameraMinFov)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MAX_FOV, &CMainCharacterProperties::OnEnChangeEditCameraMaxFov)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_DEFAULT_TILT, &CMainCharacterProperties::OnEnChangeEditCameraDefaultTilt)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MIN_TILT, &CMainCharacterProperties::OnEnChangeEditCameraMinTilt)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MAX_TILT, &CMainCharacterProperties::OnEnChangeEditCameraMaxTilt)
END_MESSAGE_MAP()


// CMainCharacterProperties message handlers


void CMainCharacterProperties::OnEnChangeEditWalkCharacterSpeed()
{
	m_editWalkSpeed.GetWindowTextA(m_strCharacterWalkSpeed);
	m_fCharacterWalkSpeed = atof(m_strCharacterWalkSpeed);
}


void CMainCharacterProperties::OnEnChangeEditCharacterRunSpeed()
{
	m_editRunSpeed.GetWindowTextA(m_strCharacterRunSpeed);
	m_fCharacterRunSpeed = atof(m_strCharacterRunSpeed);
}


void CMainCharacterProperties::OnEnChangeEditCameraCharacterDistance()
{
	m_editBoxCameraCharacterDistance.GetWindowTextA(m_strCameraCharacterDistance);
	m_fCameraCharacterDistance = atof(m_strCameraCharacterDistance);
}


void CMainCharacterProperties::OnEnChangeEditCharacterPower()
{
	m_editBoxCharacterPower.GetWindowTextA(m_strCharacterPower);
	m_fCharacterPower = atof(m_strCharacterPower);
}


void CMainCharacterProperties::OnEnChangeEditCharacterRadius()
{
	m_editBoxCapsuleRadius.GetWindowTextA(m_strCapsuleRadius);
	m_fCapsuleRadius = atof(m_strCapsuleRadius);
}


void CMainCharacterProperties::OnEnChangeEditCharacterHeight()
{
	m_editBoxCapsuleHeight.GetWindowTextA(m_strCapsuleHeight);
	m_fCapsuleHeight = atof(m_strCapsuleHeight);
}


void CMainCharacterProperties::OnEnChangeEditCharacterSlopeLimit()
{
	m_editBoxCharacterSlopeLimit.GetWindowTextA(m_strCharacterSlopeLimit);
	m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
}


void CMainCharacterProperties::OnEnChangeEditCharacterSkinWidth()
{
	m_editBoxCharacterSkinWidth.GetWindowTextA(m_strCharacterSkinWidth);
	m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
}


void CMainCharacterProperties::OnEnChangeEditCharacterStepOffset()
{
	m_editBoxCharacterStepOffset.GetWindowTextA(m_strCharacterStepOffset);
	m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
}


void CMainCharacterProperties::OnEnChangeEditCharacterJumpPower()
{
	m_editBoxJumpPower.GetWindowTextA(m_strJumpPower);
	m_fJumpPower = atof(m_strJumpPower);
}


BOOL CMainCharacterProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strCameraCharacterDistance.Format("%.2f", m_physXProperties.m_fCameraCharacterDistance);
	m_strCapsuleRadius.Format("%.2f", m_physXProperties.m_fCapsuleRadius);
	m_strCapsuleHeight.Format("%.2f", m_physXProperties.m_fCapsuleHeight);
	m_strCharacterPower.Format("%.2f", m_physXProperties.m_fCharacterPower);
	m_strCharacterWalkSpeed.Format("%.2f", m_physXProperties.m_fCharacterWalkSpeed);
	m_strCharacterRunSpeed.Format("%.2f", m_physXProperties.m_fCharacterRunSpeed);
	m_strCharacterSlopeLimit.Format("%.2f", m_physXProperties.m_fCharacterSlopeLimit);
	m_strCharacterSkinWidth.Format("%.2f", m_physXProperties.m_fCharacterSkinWidth);
	m_strCharacterStepOffset.Format("%.2f", m_physXProperties.m_fCharacterStepOffset);
	m_strJumpPower.Format("%.2f", m_physXProperties.m_fJumpPower);
	m_strIdleDelayIn.Format("%.2f", m_characterBlendingProperties.m_idleDelayIn);
	m_strWalkDelayIn.Format("%.2f", m_characterBlendingProperties.m_walkDelayIn);
	m_strRunDelayIn.Format("%.2f", m_characterBlendingProperties.m_runDelayIn);
	m_strJumpDelayIn.Format("%.2f", m_characterBlendingProperties.m_jumpDelayIn);
	m_strJumpDelayOut.Format("%.2f", m_characterBlendingProperties.m_jumpDelayOut);

	m_strDefaultFOV.Format("%.2f", m_camera->m_cameraManager->GetDefaultAngle());
	m_strMinFOV.Format("%.2f", m_camera->m_cameraManager->GetMinAngle());
	m_strMaxFOV.Format("%.2f", m_camera->m_cameraManager->GetMaxAngle());
	m_strDefaultTilt.Format("%.2f", m_camera->m_perspectiveCameraTilt);
	m_strMinTilt.Format("%.2f", m_camera->m_perspectiveCameraMinTilt);
	m_strMaxTilt.Format("%.2f", m_camera->m_perspectiveCameraMaxTilt);

	m_fCameraCharacterDistance = atof(m_strCameraCharacterDistance);
	m_fCapsuleRadius = atof(m_strCapsuleRadius);
	m_fCapsuleHeight = atof(m_strCapsuleHeight);
	m_fCharacterPower = atof(m_strCharacterPower);
	m_fCharacterWalkSpeed = atof(m_strCharacterWalkSpeed);
	m_fCharacterRunSpeed = atof(m_strCharacterRunSpeed);
	m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
	m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
	m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
	m_fJumpPower = atof(m_strJumpPower);
	m_fIdleDelayIn = atof(m_strIdleDelayIn);
	m_fWalkDelayIn = atof(m_strWalkDelayIn);
	m_fRunDelayIn = atof(m_strRunDelayIn);
	m_fJumpDelayIn = atof(m_strJumpDelayIn);
	m_fJumpDelayOut = atof(m_strJumpDelayOut);

	m_fDefaultFOV = atof(m_strDefaultFOV);
	m_fMinFOV = atof(m_strMinFOV);
	m_fMaxFOV = atof(m_strMaxFOV);
	m_fDefaultTilt = atof(m_strDefaultTilt);
	m_fMinTilt = atof(m_strMinTilt);
	m_fMaxTilt = atof(m_strMaxTilt);

	m_editBoxCameraCharacterDistance.SetWindowTextA(m_strCameraCharacterDistance);
	m_editBoxCapsuleRadius.SetWindowTextA(m_strCapsuleRadius);
	m_editBoxCapsuleHeight.SetWindowTextA(m_strCapsuleHeight);
	m_editBoxCharacterPower.SetWindowTextA(m_strCharacterPower);
	m_editWalkSpeed.SetWindowTextA(m_strCharacterWalkSpeed);
	m_editRunSpeed.SetWindowTextA(m_strCharacterRunSpeed);
	m_editBoxCharacterSlopeLimit.SetWindowTextA(m_strCharacterSlopeLimit);
	m_editBoxCharacterSkinWidth.SetWindowTextA(m_strCharacterSkinWidth);
	m_editBoxCharacterStepOffset.SetWindowTextA(m_strCharacterStepOffset);
	m_editBoxJumpPower.SetWindowTextA(m_strJumpPower);
	m_editBoxIdleDelayIn.SetWindowTextA(m_strIdleDelayIn);
	m_editBoxWalkDelayIn.SetWindowTextA(m_strWalkDelayIn);
	m_editBoxRunDelayIn.SetWindowTextA(m_strRunDelayIn);
	m_editBoxJumpDelayIn.SetWindowTextA(m_strJumpDelayIn);
	m_editBoxJumpDelayOut.SetWindowTextA(m_strJumpDelayOut);

	m_editBoxDefaultFOV.SetWindowTextA(m_strDefaultFOV);
	m_editBoxMinFOV.SetWindowTextA(m_strMinFOV);
	m_editBoxMaxFOV.SetWindowTextA(m_strMaxFOV);
	m_editBoxDefaultTilt.SetWindowTextA(m_strDefaultTilt);
	m_editBoxMinTilt.SetWindowTextA(m_strMinTilt);
	m_editBoxMaxTilt.SetWindowTextA(m_strMaxTilt);

	if (m_physXProperties.m_bJumping)
		m_checkBoxJumping.SetCheck(BST_CHECKED);
	else
		m_checkBoxJumping.SetCheck(BST_UNCHECKED);

	if (m_physXProperties.m_bDebugMode)
		m_checkBoxDebugMode.SetCheck(BST_CHECKED);
	else
		m_checkBoxDebugMode.SetCheck(BST_UNCHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CMainCharacterProperties::OnBnClickedOk()
{
	if (m_strCameraCharacterDistance.IsEmpty() || m_strCapsuleRadius.IsEmpty() || m_strCapsuleHeight.IsEmpty() ||
		m_strCharacterPower.IsEmpty() || m_strCharacterWalkSpeed.IsEmpty() || m_strCharacterRunSpeed.IsEmpty() ||
		m_strJumpPower.IsEmpty() || m_strCharacterSkinWidth.IsEmpty() || m_strCharacterSlopeLimit.IsEmpty() ||
		m_strCharacterStepOffset.IsEmpty() || m_strRunDelayIn.IsEmpty() || m_strWalkDelayIn.IsEmpty() || m_strRunDelayIn.IsEmpty() ||
		m_strJumpDelayIn.IsEmpty() || m_strJumpDelayOut.IsEmpty() || m_strDefaultFOV.IsEmpty() || m_strMinFOV.IsEmpty() ||
		m_strMaxFOV.IsEmpty() || m_strDefaultTilt.IsEmpty() || m_strMinTilt.IsEmpty() || m_strMaxTilt.IsEmpty())
	{
		MessageBox("Please enter valid data for all of the required fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_physXProperties.m_fCameraCharacterDistance = atof(m_strCameraCharacterDistance);
		m_physXProperties.m_fCapsuleRadius = atof(m_strCapsuleRadius);
		m_physXProperties.m_fCapsuleHeight = atof(m_strCapsuleHeight);
		m_physXProperties.m_fCharacterPower = atof(m_strCharacterPower);
		m_physXProperties.m_fCharacterWalkSpeed = atof(m_strCharacterWalkSpeed);
		m_physXProperties.m_fCharacterRunSpeed = atof(m_strCharacterRunSpeed);
		m_physXProperties.m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
		m_physXProperties.m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
		m_physXProperties.m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
		m_physXProperties.m_fJumpPower = atof(m_strJumpPower);

		m_characterBlendingProperties.m_idleDelayIn = atof(m_strIdleDelayIn);
		m_characterBlendingProperties.m_walkDelayIn = atof(m_strWalkDelayIn);
		m_characterBlendingProperties.m_runDelayIn = atof(m_strRunDelayIn);
		m_characterBlendingProperties.m_jumpDelayIn = atof(m_strJumpDelayIn);
		m_characterBlendingProperties.m_jumpDelayOut = atof(m_strJumpDelayOut);

		m_camera->m_cameraManager->SetDefaultAngle(atof(m_strDefaultFOV));
		m_camera->m_cameraManager->SetMinAngle(atof(m_strMinFOV));
		m_camera->m_cameraManager->SetMaxAngle(atof(m_strMaxFOV));

		m_camera->m_perspectiveCameraTilt = atof(m_strDefaultTilt);
		m_camera->m_perspectiveCameraMinTilt = atof(m_strMinTilt);
		m_camera->m_perspectiveCameraMaxTilt = atof(m_strMaxTilt);

		CInt checkState;
		checkState = m_checkBoxJumping.GetCheck();
		if (checkState == BST_CHECKED)
			m_physXProperties.m_bJumping = CTrue;
		else
			m_physXProperties.m_bJumping = CFalse;

		checkState = m_checkBoxDebugMode.GetCheck();
		if (checkState == BST_CHECKED)
			m_physXProperties.m_bDebugMode = CTrue;
		else
			m_physXProperties.m_bDebugMode = CFalse;

		ex_pMainCharacterDlg->SetPhysXProperties(m_physXProperties);
		ex_pMainCharacterDlg->SetCharacterBlendingProperties(m_characterBlendingProperties);
		ex_pMainCharacterDlg->SetCharacterCameraProperties(m_camera);

	}
	CDialog::OnOK();
}


void CMainCharacterProperties::OnBnClickedButtonReset()
{
	if (MessageBox("Are you sure you want to reset PhysX Properties?", "Warning", MB_YESNO) == IDYES)
	{
		m_physXProperties.Reset();
		m_characterBlendingProperties.Reset();
		m_camera->Reset();

		m_strCameraCharacterDistance.Format("%.2f", m_physXProperties.m_fCameraCharacterDistance);
		m_strCapsuleRadius.Format("%.2f", m_physXProperties.m_fCapsuleRadius);
		m_strCapsuleHeight.Format("%.2f", m_physXProperties.m_fCapsuleHeight);
		m_strCharacterPower.Format("%.2f", m_physXProperties.m_fCharacterPower);
		m_strCharacterWalkSpeed.Format("%.2f", m_physXProperties.m_fCharacterWalkSpeed);
		m_strCharacterRunSpeed.Format("%.2f", m_physXProperties.m_fCharacterRunSpeed);
		m_strCharacterSlopeLimit.Format("%.2f", m_physXProperties.m_fCharacterSlopeLimit);
		m_strCharacterSkinWidth.Format("%.2f", m_physXProperties.m_fCharacterSkinWidth);
		m_strCharacterStepOffset.Format("%.2f", m_physXProperties.m_fCharacterStepOffset);
		m_strJumpPower.Format("%.2f", m_physXProperties.m_fJumpPower);
		m_strIdleDelayIn.Format("%.2f", m_characterBlendingProperties.m_idleDelayIn);
		m_strWalkDelayIn.Format("%.2f", m_characterBlendingProperties.m_walkDelayIn);
		m_strRunDelayIn.Format("%.2f", m_characterBlendingProperties.m_runDelayIn);
		m_strJumpDelayIn.Format("%.2f", m_characterBlendingProperties.m_jumpDelayIn);
		m_strJumpDelayOut.Format("%.2f", m_characterBlendingProperties.m_jumpDelayOut);

		m_strDefaultFOV.Format("%.2f", m_camera->m_cameraManager->GetDefaultAngle());
		m_strMinFOV.Format("%.2f", m_camera->m_cameraManager->GetMinAngle());
		m_strMaxFOV.Format("%.2f", m_camera->m_cameraManager->GetMaxAngle());
		m_strDefaultTilt.Format("%.2f", m_camera->m_perspectiveCameraTilt);
		m_strMinTilt.Format("%.2f", m_camera->m_perspectiveCameraMinTilt);
		m_strMaxTilt.Format("%.2f", m_camera->m_perspectiveCameraMaxTilt);

								
		m_fCameraCharacterDistance = atof(m_strCameraCharacterDistance);
		m_fCapsuleRadius = atof(m_strCapsuleRadius);
		m_fCapsuleHeight = atof(m_strCapsuleHeight);
		m_fCharacterPower = atof(m_strCharacterPower);
		m_fCharacterWalkSpeed = atof(m_strCharacterWalkSpeed);
		m_fCharacterRunSpeed = atof(m_strCharacterRunSpeed);
		m_fCharacterSkinWidth = atof(m_strCharacterSkinWidth);
		m_fCharacterStepOffset = atof(m_strCharacterStepOffset);
		m_fCharacterSlopeLimit = atof(m_strCharacterSlopeLimit);
		m_fJumpPower = atof(m_strJumpPower);
		m_fIdleDelayIn = atof(m_strIdleDelayIn);
		m_fWalkDelayIn = atof(m_strWalkDelayIn);
		m_fRunDelayIn = atof(m_strRunDelayIn);
		m_fJumpDelayIn = atof(m_strJumpDelayIn);
		m_fJumpDelayOut = atof(m_strJumpDelayOut);

		m_fDefaultFOV = atof(m_strDefaultFOV);
		m_fMinFOV = atof(m_strMinFOV);
		m_fMaxFOV = atof(m_strMaxFOV);
		m_fDefaultTilt = atof(m_strDefaultTilt);
		m_fMinTilt = atof(m_strMinTilt);
		m_fMaxTilt = atof(m_strMaxTilt);

		m_editBoxCameraCharacterDistance.SetWindowTextA(m_strCameraCharacterDistance);
		m_editBoxCapsuleRadius.SetWindowTextA(m_strCapsuleRadius);
		m_editBoxCapsuleHeight.SetWindowTextA(m_strCapsuleHeight);
		m_editBoxCharacterPower.SetWindowTextA(m_strCharacterPower);
		m_editWalkSpeed.SetWindowTextA(m_strCharacterWalkSpeed);
		m_editRunSpeed.SetWindowTextA(m_strCharacterRunSpeed);
		m_editBoxCharacterSlopeLimit.SetWindowTextA(m_strCharacterSlopeLimit);
		m_editBoxCharacterSkinWidth.SetWindowTextA(m_strCharacterSkinWidth);
		m_editBoxCharacterStepOffset.SetWindowTextA(m_strCharacterStepOffset);
		m_editBoxJumpPower.SetWindowTextA(m_strJumpPower);
		m_editBoxIdleDelayIn.SetWindowTextA(m_strIdleDelayIn);
		m_editBoxWalkDelayIn.SetWindowTextA(m_strWalkDelayIn);
		m_editBoxRunDelayIn.SetWindowTextA(m_strRunDelayIn);
		m_editBoxJumpDelayIn.SetWindowTextA(m_strJumpDelayIn);
		m_editBoxJumpDelayOut.SetWindowTextA(m_strJumpDelayOut);

		m_editBoxDefaultFOV.SetWindowTextA(m_strDefaultFOV);
		m_editBoxMinFOV.SetWindowTextA(m_strMinFOV);
		m_editBoxMaxFOV.SetWindowTextA(m_strMaxFOV);
		m_editBoxDefaultTilt.SetWindowTextA(m_strDefaultTilt);
		m_editBoxMinTilt.SetWindowTextA(m_strMinTilt);
		m_editBoxMaxTilt.SetWindowTextA(m_strMaxTilt);

		if (m_physXProperties.m_bJumping)
			m_checkBoxJumping.SetCheck(BST_CHECKED);
		else
			m_checkBoxJumping.SetCheck(BST_UNCHECKED);

		if (m_physXProperties.m_bDebugMode)
			m_checkBoxDebugMode.SetCheck(BST_CHECKED);
		else
			m_checkBoxDebugMode.SetCheck(BST_UNCHECKED);

	}
}


void CMainCharacterProperties::OnEnChangeEditIdleDelayIn()
{
	m_editBoxIdleDelayIn.GetWindowTextA(m_strIdleDelayIn);
	m_fIdleDelayIn = atof(m_strIdleDelayIn);
}


void CMainCharacterProperties::OnEnChangeEditWalkDelayIn()
{
	m_editBoxWalkDelayIn.GetWindowTextA(m_strWalkDelayIn);
	m_fWalkDelayIn = atof(m_strWalkDelayIn);
}


void CMainCharacterProperties::OnEnChangeEditRunDelayIn()
{
	m_editBoxRunDelayIn.GetWindowTextA(m_strRunDelayIn);
	m_fRunDelayIn = atof(m_strRunDelayIn);
}


void CMainCharacterProperties::OnEnChangeEditJumpDelayIn()
{
	m_editBoxJumpDelayIn.GetWindowTextA(m_strJumpDelayIn);
	m_fJumpDelayIn = atof(m_strJumpDelayIn);
}


void CMainCharacterProperties::OnEnChangeEditJumpDelayOut()
{
	m_editBoxJumpDelayOut.GetWindowTextA(m_strJumpDelayOut);
	m_fJumpDelayOut = atof(m_strJumpDelayOut);
}


void CMainCharacterProperties::OnEnChangeEditCameraDefaultFov()
{
	m_editBoxDefaultFOV.GetWindowTextA(m_strDefaultFOV);
	m_fDefaultFOV = atof(m_strDefaultFOV);
}


void CMainCharacterProperties::OnEnChangeEditCameraMinFov()
{
	m_editBoxMinFOV.GetWindowTextA(m_strMinFOV);
	m_fMinFOV = atof(m_strMinFOV);
}


void CMainCharacterProperties::OnEnChangeEditCameraMaxFov()
{
	m_editBoxMaxFOV.GetWindowTextA(m_strMaxFOV);
	m_fMaxFOV = atof(m_strMaxFOV);
}


void CMainCharacterProperties::OnEnChangeEditCameraDefaultTilt()
{
	m_editBoxDefaultTilt.GetWindowTextA(m_strDefaultTilt);
	m_fDefaultTilt = atof(m_strDefaultTilt);
}


void CMainCharacterProperties::OnEnChangeEditCameraMinTilt()
{
	m_editBoxMinTilt.GetWindowTextA(m_strMinTilt);
	m_fMinTilt = atof(m_strMinTilt);

}


void CMainCharacterProperties::OnEnChangeEditCameraMaxTilt()
{
	m_editBoxMaxTilt.GetWindowTextA(m_strMaxTilt);
	m_fMaxTilt = atof(m_strMaxTilt);
}

CVoid CMainCharacterProperties::SetCharacterCameraProperties(CUpdateCamera* properties)
{
	m_camera->m_cameraManager->SetDefaultAngle(properties->m_cameraManager->GetDefaultAngle());
	m_camera->m_cameraManager->SetMinAngle(properties->m_cameraManager->GetMinAngle());
	m_camera->m_cameraManager->SetMaxAngle(properties->m_cameraManager->GetMaxAngle());

	m_camera->m_perspectiveCameraTilt = properties->m_perspectiveCameraTilt;
	m_camera->m_perspectiveCameraMinTilt = properties->m_perspectiveCameraMinTilt;
	m_camera->m_perspectiveCameraMaxTilt = properties->m_perspectiveCameraMaxTilt;
}

//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddMainCharacter.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddMainCharacter.h"
#include "afxdialogex.h"
#include "physXEngine\MainCharacter.h"
#include "SelectAnimationClips.h"
#include "SaveLoadCharacterProfile.h"
#include "MainCharacterProperties.h"
#include "AddCharacterSound.h"
#include "..\\GraphicsEngine\\PerspectiveWindow.h"
// CAddMainCharacter dialog

IMPLEMENT_DYNAMIC(CAddMainCharacter, CDialog)

CAddMainCharacter::CAddMainCharacter(CWnd* pParent /*=NULL*/)
	: CDialog(CAddMainCharacter::IDD, pParent)
{
	m_idleIndex = 0;
	m_walkIndex = 0;
	m_jumpIndex = 0;
	m_runIndex = 0;
	m_instance = NULL;
	m_bRemoved = CFalse;
	Cpy(m_oldName, "\n");
	m_characterType = ePHYSX_CAMERA_THIRD_PERSON;
	m_camera = new CUpdateCamera();
	m_newCharacter = CFalse;
	m_clickedWalkSound = CFalse;
	m_clickedRunSound = CFalse;
	m_clickedJumpSound = CFalse;

}

CAddMainCharacter::~CAddMainCharacter()
{
}

void CAddMainCharacter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IDLE, m_comboIdle);
	DDX_Control(pDX, IDC_COMBO_WALK, m_comboWalk);
	DDX_Control(pDX, IDC_COMBO_RUN, m_comboRun);
	DDX_Control(pDX, IDC_COMBO_JUMP, m_comboJump);
	DDX_Control(pDX, IDC_EDIT_PREFAB_INSTANCE, m_editCharacterModel);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_POS_X, m_editPosX);
	DDX_Control(pDX, IDC_EDIT_POS_Y, m_editPosY);
	DDX_Control(pDX, IDC_EDIT_POS_Z, m_editPosZ);
	DDX_Control(pDX, IDC_EDIT_POS_SCALE, m_editScale);
	DDX_Control(pDX, IDC_EDIT_DELAY_PLAY_MORE_IDLES_RANDOMLY, m_editBoxPlayMoreIdlesEveryXSeconds);
}


BEGIN_MESSAGE_MAP(CAddMainCharacter, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_JUMP, &CAddMainCharacter::OnBnClickedButtonSelectJump)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_RUN, &CAddMainCharacter::OnBnClickedButtonSelectRun)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WALK, &CAddMainCharacter::OnBnClickedButtonSelectWalk)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_IDLE, &CAddMainCharacter::OnBnClickedButtonSelectIdle)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_CHARACTER, &CAddMainCharacter::OnBnClickedButtonSelectCharacter)
	ON_BN_CLICKED(IDOK, &CAddMainCharacter::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_PROPERTIES, &CAddMainCharacter::OnBnClickedButtonProperties)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_CHARACTER, &CAddMainCharacter::OnBnClickedButtonRemoveCharacter)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_IDLE, &CAddMainCharacter::OnBnClickedButtonRemoveIdle)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_WALK, &CAddMainCharacter::OnBnClickedButtonRemoveWalk)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_RUN, &CAddMainCharacter::OnBnClickedButtonRemoveRun)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_JUMP, &CAddMainCharacter::OnBnClickedButtonRemoveJump)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_PROFILE, &CAddMainCharacter::OnBnClickedButtonLoadProfile)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_PROFILE, &CAddMainCharacter::OnBnClickedButtonSaveProfile)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CAddMainCharacter::OnEnChangeEditName)
	ON_BN_CLICKED(IDCANCEL, &CAddMainCharacter::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_POS_X, &CAddMainCharacter::OnEnChangeEditPosX)
	ON_EN_CHANGE(IDC_EDIT_POS_Y, &CAddMainCharacter::OnEnChangeEditPosY)
	ON_EN_CHANGE(IDC_EDIT_POS_Z, &CAddMainCharacter::OnEnChangeEditPosZ)
	ON_EN_CHANGE(IDC_EDIT_POS_SCALE, &CAddMainCharacter::OnEnChangeEditPosScale)
	ON_EN_CHANGE(IDC_EDIT_DELAY_PLAY_MORE_IDLES_RANDOMLY, &CAddMainCharacter::OnEnChangeEditDelayPlayMoreIdlesRandomly)
	ON_BN_CLICKED(IDC_BUTTON_SOUNDS, &CAddMainCharacter::OnBnClickedButtonSounds)
END_MESSAGE_MAP()


// CAddMainCharacter message handlers


void CAddMainCharacter::OnBnClickedButtonSelectJump()
{
	if (m_comboJump.GetCount()) return;

	if (m_instance)
	{
		CSelectAnimationClips* m_dlgAnimationClips = CNew(CSelectAnimationClips);
		m_dlgAnimationClips->SetAnimationList(m_instance->GetScene(0)->m_animationSceneNames);
		if (m_dlgAnimationClips->DoModal() == IDOK)
		{
			CChar* name = m_dlgAnimationClips->GetSelectedAnimation();
			CBool foundTarget = CFalse;
			for (CInt i = 0; i < m_comboJump.GetCount(); i++)
			{
				CString currentString;
				m_comboJump.GetLBText(m_comboJump.GetCurSel(), currentString);
				if (Cmp(name, (LPCTSTR)currentString))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (!foundTarget)
			{
				m_comboJump.InsertString(m_jumpIndex, name);
				m_comboJump.SetCurSel(m_jumpIndex);
				m_jumpIndex++;
			}
			else
			{
				MessageBox("You have already assigned this name to jump list", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		CDelete(m_dlgAnimationClips);
	}
}


void CAddMainCharacter::OnBnClickedButtonSelectRun()
{
	if (m_comboRun.GetCount()) return;

	if (m_instance)
	{
		CSelectAnimationClips* m_dlgAnimationClips = CNew(CSelectAnimationClips);
		m_dlgAnimationClips->SetAnimationList(m_instance->GetScene(0)->m_animationSceneNames);
		if (m_dlgAnimationClips->DoModal() == IDOK)
		{
			CChar* name = m_dlgAnimationClips->GetSelectedAnimation();
			CBool foundTarget = CFalse;
			for (CInt i = 0; i < m_comboRun.GetCount(); i++)
			{
				CString currentString;
				m_comboRun.GetLBText(m_comboRun.GetCurSel(), currentString);
				if (Cmp(name, (LPCTSTR)currentString))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (!foundTarget)
			{
				m_comboRun.InsertString(m_runIndex, name);
				m_comboRun.SetCurSel(m_runIndex);
				m_runIndex++;
			}
			else
			{
				MessageBox("You have already assigned this name to run list", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		CDelete(m_dlgAnimationClips);
	}
}


void CAddMainCharacter::OnBnClickedButtonSelectWalk()
{
	if (m_comboWalk.GetCount()) return;

	if (m_instance)
	{
		CSelectAnimationClips* m_dlgAnimationClips = CNew(CSelectAnimationClips);
		m_dlgAnimationClips->SetAnimationList(m_instance->GetScene(0)->m_animationSceneNames);
		if (m_dlgAnimationClips->DoModal() == IDOK)
		{
			CChar* name = m_dlgAnimationClips->GetSelectedAnimation();
			CBool foundTarget = CFalse;
			for (CInt i = 0; i < m_comboWalk.GetCount(); i++)
			{
				CString currentString;
				m_comboWalk.GetLBText(m_comboWalk.GetCurSel(), currentString);
				if (Cmp(name, (LPCTSTR)currentString))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (!foundTarget)
			{
				m_comboWalk.InsertString(m_walkIndex, name);
				m_comboWalk.SetCurSel(m_walkIndex);
				m_walkIndex++;
			}
			else
			{
				MessageBox("You have already assigned this name to walk list", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		CDelete(m_dlgAnimationClips);
	}
}


void CAddMainCharacter::OnBnClickedButtonSelectIdle()
{
	if (m_instance)
	{
		CSelectAnimationClips* m_dlgAnimationClips = CNew(CSelectAnimationClips);
		m_dlgAnimationClips->SetAnimationList(m_instance->GetScene(0)->m_animationSceneNames);
		if (m_dlgAnimationClips->DoModal() == IDOK)
		{
			CChar* name = m_dlgAnimationClips->GetSelectedAnimation();
			CBool foundTarget = CFalse;
			for (CInt i = 0; i < m_comboIdle.GetCount(); i++)
			{
				CString currentString;
				m_comboIdle.GetLBText(m_comboIdle.GetCurSel(), currentString);
				if (Cmp(name, (LPCTSTR)currentString))
				{
					foundTarget = CTrue;
					break;
				}
			}
			if (!foundTarget)
			{
				m_comboIdle.InsertString(m_idleIndex, name);
				m_comboIdle.SetCurSel(m_idleIndex);
				m_idleIndex++;
			}
			else
			{
				MessageBox("You have already assigned this name to idle list", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			}
		}
		CDelete(m_dlgAnimationClips);
	}
}


void CAddMainCharacter::OnBnClickedButtonSelectCharacter()
{
	ex_pDlgPrefabs = CNew(CPrefabDlg);
	ex_pDlgPrefabs->SetSelectForMainCharacter(CTrue);
	INT_PTR result = ex_pDlgPrefabs->DoModal();
	CDelete(ex_pDlgPrefabs);
	if (result == IDOK)
	{
		if (m_instance)
		{
			Destroy();
			m_comboIdle.ResetContent();
			m_comboWalk.ResetContent();
			m_comboJump.ResetContent();
			m_comboRun.ResetContent();

			m_idleIndex = 0;
			m_walkIndex = 0;
			m_jumpIndex = 0;
			m_runIndex = 0;
		}
		g_importPrefab = CTrue;

		ex_pVandaEngine1Dlg->m_dlgPrefabs = CNew(CPrefabDlg);
		ex_pDlgPrefabs = ex_pVandaEngine1Dlg->m_dlgPrefabs;
		ex_pVandaEngine1Dlg->OnMenuClickedInsertPrefab(NULL, g_currentPrefabPackageName, g_currentPrefabName);

		for (CUInt j = 0; j < g_instancePrefab.size(); j++)
		{
			if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
			{
				if (g_instancePrefab[j]->GetRadius() > g_maxInstancePrefabRadius)
					g_maxInstancePrefabRadius = g_instancePrefab[j]->GetRadius();
			}
		}

		CDelete(ex_pVandaEngine1Dlg->m_dlgPrefabs);

		g_importPrefab = CFalse;
		m_instance = g_instancePrefab[g_instancePrefab.size() - 1];
		if (m_instance->GetScene(0)->GetNumClips() < 4)
		{
			MessageBox("Your model must have at least 4 animation clips for idle, walk, run, and jump actions.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			PrintInfo("\nRemoving model from memory...", COLOR_RED);

			Destroy();
			m_instance = NULL;
			std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
			std::vector<std::string> walkName = g_mainCharacter->GetWalkName();
			std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();
			std::vector<std::string> runName = g_mainCharacter->GetRunName();
			m_editCharacterModel.SetWindowTextA(g_mainCharacter->GetName());
			m_comboIdle.ResetContent();
			for (CUInt i = 0; i < idleName.size(); i++)
				m_comboIdle.InsertString(i, idleName[i].c_str());
			m_comboIdle.SetCurSel(0);
			m_comboWalk.ResetContent();
			for (CUInt i = 0; i < walkName.size(); i++)
				m_comboWalk.InsertString(i, walkName[i].c_str());
			m_comboWalk.SetCurSel(0);
			m_comboJump.ResetContent();
			for (CUInt i = 0; i < jumpName.size(); i++)
				m_comboJump.InsertString(i, jumpName[i].c_str());
			m_comboJump.SetCurSel(0);
			m_comboRun.ResetContent();
			for (CUInt i = 0; i < runName.size(); i++)
				m_comboRun.InsertString(i, runName[i].c_str());
			m_comboRun.SetCurSel(0);

			m_idleIndex = 0;
			m_walkIndex = 0;
			m_jumpIndex = 0;
			m_runIndex = 0;
		}
		else
		{
			m_editCharacterModel.SetWindowTextA(g_currentPrefabName);
			m_comboIdle.ResetContent();
			m_comboWalk.ResetContent();
			m_comboJump.ResetContent();
			m_comboRun.ResetContent();

			m_idleIndex = 0;
			m_walkIndex = 0;
			m_jumpIndex = 0;
			m_runIndex = 0;

			CFloat scale = 1.0f;
			m_strScale.Format("%.2f", scale);
			m_editScale.SetWindowTextA(m_strScale);

			m_bCharacterChanged = CTrue;
		}

	}
}


BOOL CAddMainCharacter::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!g_mainCharacter)
	{
		m_newCharacter = CTrue;
		g_mainCharacter = CNew(CMainCharacter);
	}
	if (g_mainCharacter->GetCameraType() == ePHYSX_CAMERA_THIRD_PERSON)
		CheckRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON, IDC_RADIO_THIRD_PERSON);
	else
		CheckRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON, IDC_RADIO_FIRST_PERSON);

	m_editName.SetWindowTextA(g_mainCharacter->GetName());

	CFloat x = g_mainCharacter->GetPosition().x;
	m_strPosX.Format("%.2f", x);
	m_editPosX.SetWindowTextA(m_strPosX);

	CFloat y = g_mainCharacter->GetPosition().y;
	m_strPosY.Format("%.2f", y);
	m_editPosY.SetWindowTextA(m_strPosY);

	CFloat z = g_mainCharacter->GetPosition().z;
	m_strPosZ.Format("%.2f", z);
	m_editPosZ.SetWindowTextA(m_strPosZ);

	CFloat scale = g_mainCharacter->GetScale();
	m_strScale.Format("%.2f", scale);
	m_editScale.SetWindowTextA(m_strScale);

	CFloat idleDelay = g_mainCharacter->GetIdleDelayForRandomPlay();
	m_strPlayMoreIdlesEveryXSeconds.Format("%.2f", idleDelay);
	m_editBoxPlayMoreIdlesEveryXSeconds.SetWindowTextA(m_strPlayMoreIdlesEveryXSeconds);

	m_editCharacterModel.SetWindowTextA(g_mainCharacter->GetPrefabName());
	Cpy(g_currentPrefabPackageName, g_mainCharacter->GetPackageName());
	Cpy(g_currentPrefabName, g_mainCharacter->GetPrefabName());

	m_instance = g_mainCharacter->GetInstancePrefab();
	std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
	std::vector<std::string> walkName = g_mainCharacter->GetWalkName();
	std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();
	std::vector<std::string> runName = g_mainCharacter->GetRunName();
	m_comboIdle.ResetContent();
	for (CUInt i = 0; i < idleName.size(); i++)
		m_comboIdle.InsertString(i, idleName[i].c_str());
	m_comboIdle.SetCurSel(0);
	m_comboWalk.ResetContent();
	for (CUInt i = 0; i < walkName.size(); i++)
		m_comboWalk.InsertString(i, walkName[i].c_str());
	m_comboWalk.SetCurSel(0);
	m_comboJump.ResetContent();
	for (CUInt i = 0; i < jumpName.size(); i++)
		m_comboJump.InsertString(i, jumpName[i].c_str());
	m_comboJump.SetCurSel(0);
	m_comboRun.ResetContent();
	for (CUInt i = 0; i < runName.size(); i++)
		m_comboRun.InsertString(i, runName[i].c_str());
	m_comboRun.SetCurSel(0);

	m_idleIndex = 0;
	m_walkIndex = 0;
	m_jumpIndex = 0;
	m_runIndex = 0;
	m_bCharacterChanged = CFalse;
	m_physXProperties = g_physXProperties;
	m_characterBlendingProperties = g_characterBlendingProperties;

	Cpy(m_characterSoundProperties.m_walkSound, g_mainCharacter->GetSoundWalkPath());
	Cpy(m_characterSoundProperties.m_runSound, g_mainCharacter->GetSoundRunPath());
	Cpy(m_characterSoundProperties.m_jumpSound, g_mainCharacter->GetSoundJumpPath());

	m_camera->m_cameraManager->SetDefaultAngle(g_camera->m_cameraManager->GetDefaultAngle());
	m_camera->m_cameraManager->SetMinAngle(g_camera->m_cameraManager->GetMinAngle());
	m_camera->m_cameraManager->SetMaxAngle(g_camera->m_cameraManager->GetMaxAngle());

	m_camera->m_perspectiveCameraTilt = g_camera->m_perspectiveCameraTilt;
	m_camera->m_perspectiveCameraMinTilt = g_camera->m_perspectiveCameraMinTilt;
	m_camera->m_perspectiveCameraMaxTilt = g_camera->m_perspectiveCameraMaxTilt;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddMainCharacter::OnBnClickedOk()
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

	if (m_strPosX.IsEmpty() || m_strPosY.IsEmpty() || m_strPosZ.IsEmpty() || m_strScale.IsEmpty() || m_strName.IsEmpty() || m_strPlayMoreIdlesEveryXSeconds.IsEmpty() || m_comboIdle.GetCount() == 0 || m_comboWalk.GetCount() == 0 || m_comboJump.GetCount() == 0 || m_comboRun.GetCount() == 0)
	{
		MessageBox("Please Fill In All Of The Required Fields.", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (!Cmp(m_oldName, "\n"))
	{
		for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
		{
			if (!Cmp(m_oldName, (*it).c_str()) && Cmp((LPCTSTR)m_strName, (*it).c_str()))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	else
	{
		for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
		{
			if (Cmp((LPCTSTR)m_strName, (*it).c_str()))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}

	}
	if (!Cmp(m_oldName, "\n"))
	{
		for (CUInt i = 0; i < g_engineObjectNames.size(); i++)
		{
			if (Cmp(g_engineObjectNames[i].c_str(), m_oldName))
				g_engineObjectNames[i] = "";
		}
	}

	int newState = GetCheckedRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON);
	if (newState == IDC_RADIO_FIRST_PERSON)
		g_mainCharacter->SetCameraType(ePHYSX_CAMERA_FIRST_PERSON);
	else
		g_mainCharacter->SetCameraType(ePHYSX_CAMERA_THIRD_PERSON);

	g_mainCharacter->SetName((CChar*)(LPCTSTR)m_strName);
	if (m_instance)
	{
		g_mainCharacter->SetPackageName(g_currentPrefabPackageName);
		g_mainCharacter->SetPrefabName(g_currentPrefabName);
	}

	std::vector<std::string> idleName;
	std::vector<std::string> walkName;
	std::vector<std::string> jumpName;
	std::vector<std::string> runName;

	//set idle name
	for (CInt i = 0; i < m_comboIdle.GetCount(); i++)
	{
		CString currentString;
		m_comboIdle.GetLBText(i, currentString);
		idleName.push_back((LPCTSTR)currentString);
	}
	g_mainCharacter->SetIdleName(idleName);

	//set walk name
	for (CInt i = 0; i < m_comboWalk.GetCount(); i++)
	{
		CString currentString;
		m_comboWalk.GetLBText(i, currentString);
		walkName.push_back((LPCTSTR)currentString);
	}
	g_mainCharacter->SetWalkName(walkName);

	//set run name
	for (CInt i = 0; i < m_comboRun.GetCount(); i++)
	{
		CString currentString;
		m_comboRun.GetLBText(i, currentString);
		runName.push_back((LPCTSTR)currentString);
	}
	g_mainCharacter->SetRunName(runName);
	
	//set jump name
	for (CInt i = 0; i < m_comboJump.GetCount(); i++)
	{
		CString currentString;
		m_comboJump.GetLBText(i, currentString);
		jumpName.push_back((LPCTSTR)currentString);
	}
	g_mainCharacter->SetJumpName(jumpName);

	if (m_instance)
	{
		g_mainCharacter->SetInstancePrefab(m_instance);
	}
	else
	{
		g_importPrefab = CTrue;

		ex_pVandaEngine1Dlg->m_dlgPrefabs = CNew(CPrefabDlg);
		ex_pDlgPrefabs = ex_pVandaEngine1Dlg->m_dlgPrefabs;
		ex_pVandaEngine1Dlg->OnMenuClickedInsertPrefab(NULL, g_mainCharacter->GetPackageName(), g_mainCharacter->GetPrefabName());

		for (CUInt j = 0; j < g_instancePrefab.size(); j++)
		{
			if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
			{
				if (g_instancePrefab[j]->GetRadius() > g_maxInstancePrefabRadius)
					g_maxInstancePrefabRadius = g_instancePrefab[j]->GetRadius();
			}
		}

		CDelete(ex_pVandaEngine1Dlg->m_dlgPrefabs);

		g_importPrefab = CFalse;
		m_instance = g_instancePrefab[g_instancePrefab.size() - 1];
		
		g_mainCharacter->SetInstancePrefab(m_instance);
	}
	g_physXProperties = m_physXProperties;
	g_characterBlendingProperties = m_characterBlendingProperties;

	g_camera->m_cameraManager->SetDefaultAngle(m_camera->m_cameraManager->GetDefaultAngle());
	g_camera->m_cameraManager->SetMinAngle(m_camera->m_cameraManager->GetMinAngle());
	g_camera->m_cameraManager->SetMaxAngle(m_camera->m_cameraManager->GetMaxAngle());

	g_camera->m_perspectiveCameraTilt = m_camera->m_perspectiveCameraTilt;
	g_camera->m_perspectiveCameraMinTilt = m_camera->m_perspectiveCameraMinTilt;
	g_camera->m_perspectiveCameraMaxTilt = m_camera->m_perspectiveCameraMaxTilt;

	ex_pVandaEngine1Dlg->ResetPhysX(CFalse);

	CVec3f translate, scale;
	CVec4f rotate;
	CBool selected = CFalse;

	if (selected)
	{
		g_selectedName = g_mainCharacter->GetInstancePrefab()->GetNameIndex();
	}
	else if (!m_instance)
	{
		g_selectedName = g_mainCharacter->GetInstancePrefab()->GetNameIndex();
	}

	CFloat scale_char;
	CVec3f pos_char;
	scale_char = atof(m_strScale);
	pos_char.x = atof(m_strPosX);
	pos_char.y = atof(m_strPosY);
	pos_char.z = atof(m_strPosZ);
	CVec3f scale_XYZ;
	scale_XYZ.x = scale_XYZ.y = scale_XYZ.z = scale_char;
	g_mainCharacter->GetInstancePrefab()->SetTranslate(pos_char);
	//g_mainCharacter->GetInstancePrefab()->SetRotate(rotation);
	g_mainCharacter->GetInstancePrefab()->SetScale(scale_XYZ);
	g_mainCharacter->GetInstancePrefab()->UpdateBoundingBox(CTrue);
	g_mainCharacter->GetInstancePrefab()->CalculateDistance();
	//g_mainCharacter->GetInstancePrefab()->UpdateIsStaticOrAnimated();


	g_arrowPosition = pos_char;
	g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
	g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = scale_char;

	g_mainCharacter->SetPosition(pos_char);
	g_mainCharacter->SetScale(scale_char);

	m_fPlayMoreIdlesEveryXSeconds = atof(m_strPlayMoreIdlesEveryXSeconds);
	if (m_fPlayMoreIdlesEveryXSeconds < 1.0f)
		m_fPlayMoreIdlesEveryXSeconds = 1.0f;
	else if (m_fPlayMoreIdlesEveryXSeconds > 50.0f)
		m_fPlayMoreIdlesEveryXSeconds = 60.0f;
	g_mainCharacter->SetIdleDelayForRandomPlay(m_fPlayMoreIdlesEveryXSeconds);

	g_mainCharacter->SetWalkSoundPath(m_characterSoundProperties.m_walkSound);
	g_mainCharacter->SetRunSoundPath(m_characterSoundProperties.m_runSound);
	g_mainCharacter->SetJumpSoundPath(m_characterSoundProperties.m_jumpSound);

	for (CUInt index = 0; index < g_VSceneNamesOfCurrentProject.size(); index++)
	{
		g_mainCharacter->AddVSceneToList(g_VSceneNamesOfCurrentProject[index], CTrue);
	}
	if (m_newCharacter || m_clickedWalkSound)
		g_mainCharacter->SetWalkSound();
	if (m_newCharacter || m_clickedRunSound)
		g_mainCharacter->SetRunSound();
	if (m_newCharacter || m_clickedJumpSound)
		g_mainCharacter->SetJumpSound();


	NxExtendedVec3 pos;
	pos.x = g_arrowPosition.x;
	pos.y = g_arrowPosition.y + (g_physXProperties.m_fCapsuleHeight * 0.5f) + g_physXProperties.m_fCapsuleRadius + g_physXProperties.m_fCharacterSkinWidth;
	pos.z = g_arrowPosition.z;

	g_multipleView->m_nx->gControllers->setPosition(pos);

	//set default rotation and idle status here
	g_multipleView->ManageCharacterBlends("idle");

	g_multipleView->RenderCharacter(CFalse);
	if (Cmp(m_oldName, "\n"))
	{
		ex_pVandaEngine1Dlg->InsertItemToEngineObjectList(g_mainCharacter->GetName(), eENGINEOBJECTLIST_CHARACTER);
		g_engineObjectNames.push_back(g_mainCharacter->GetName());
	}
	m_instance->SetName("VANDA_MAIN_CHARACTER");

	CChar name[MAX_NAME_SIZE];
	Cpy(name, g_mainCharacter->GetName());

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


	//Erase all items of m_listBoxEngineObjects
	for (int k = 0; k < ex_pVandaEngine1Dlg->m_listBoxScenes.GetItemCount(); k++)
	{
		ex_pVandaEngine1Dlg->m_listBoxScenes.SetItemState(k, ~LVIS_SELECTED, LVIS_SELECTED);
		ex_pVandaEngine1Dlg->m_listBoxScenes.Update(k);
	}
	ex_pVandaEngine1Dlg->m_btnRemoveScene.EnableWindow(FALSE);
	ex_pVandaEngine1Dlg->m_btnSceneProperties.EnableWindow(FALSE);

	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
	if (g_editorMode == eMODE_VSCENE)
		g_multipleView->RenderQueries(CTrue);
	g_menu.m_insertCharacter = CTrue;
	ex_pVandaEngine1Dlg->m_mainBtnPlayer.EnableWindow(FALSE);
	ex_pVandaEngine1Dlg->GetMenu()->EnableMenuItem(ID_INSERT_PLAYER, MF_DISABLED | MF_GRAYED);
	g_multipleView->SetElapsedTimeFromBeginning();


	CDialog::OnOK();
}

void CAddMainCharacter::Init(CChar* oldName)
{
	Cpy(m_oldName, oldName);
}

void CAddMainCharacter::OnBnClickedButtonProperties()
{
	CMainCharacterProperties *m_dlgCharacterProperties = CNew(CMainCharacterProperties);
	m_dlgCharacterProperties->SetPhysXProperties(m_physXProperties);
	m_dlgCharacterProperties->SetCharacterBlendingProperties(m_characterBlendingProperties);

	m_dlgCharacterProperties->SetCharacterCameraProperties(m_camera);
	if (m_dlgCharacterProperties->DoModal() == IDOK)
	{
	}
	CDelete(m_dlgCharacterProperties);
}

void CAddMainCharacter::OnBnClickedButtonRemoveCharacter()
{
	if (MessageBox("This will load the parameters of default character. Continue?", "Warning", MB_YESNO) == IDYES)
	{
		if (m_instance)
		{
			Destroy();
			m_instance = NULL;
		}
		g_mainCharacter->Reset();
		m_editName.SetWindowTextA(g_mainCharacter->GetName());
		Cpy(g_currentPrefabPackageName, g_mainCharacter->GetPackageName());
		Cpy(g_currentPrefabName, g_mainCharacter->GetPrefabName());
		m_editCharacterModel.SetWindowTextA(g_mainCharacter->GetPrefabName());
		std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
		std::vector<std::string> walkName = g_mainCharacter->GetWalkName();
		std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();
		std::vector<std::string> runName = g_mainCharacter->GetRunName();
		m_comboIdle.ResetContent();
		for (CUInt i = 0; i < idleName.size(); i++)
			m_comboIdle.InsertString(i, idleName[i].c_str());
		m_comboIdle.SetCurSel(0);
		m_comboWalk.ResetContent();
		for (CUInt i = 0; i < walkName.size(); i++)
			m_comboWalk.InsertString(i, walkName[i].c_str());
		m_comboWalk.SetCurSel(0);
		m_comboJump.ResetContent();
		for (CUInt i = 0; i < jumpName.size(); i++)
			m_comboJump.InsertString(i, jumpName[i].c_str());
		m_comboJump.SetCurSel(0);
		m_comboRun.ResetContent();
		for (CUInt i = 0; i < runName.size(); i++)
			m_comboRun.InsertString(i, runName[i].c_str());
		m_comboRun.SetCurSel(0);

		m_idleIndex = 0;
		m_walkIndex = 0;
		m_jumpIndex = 0;
		m_runIndex = 0;

		m_bRemoved = CTrue;
	}
}

void CAddMainCharacter::OnBnClickedButtonRemoveIdle()
{
	if (!m_instance) return;
	CString currentString;
	if (m_comboIdle.GetCount())
		m_comboIdle.GetLBText(m_comboIdle.GetCurSel(), currentString);
	CChar message[MAX_NAME_SIZE];
	sprintf(message, "Are you sure you want to remove ' %s ' animation from idle list?", (LPCTSTR)currentString);
	if (MessageBox(message, "Warning", MB_YESNO) == IDYES)
	{
		m_comboIdle.DeleteString(m_comboIdle.GetCurSel());
		m_idleIndex--;
		m_comboIdle.SetCurSel(m_idleIndex);
	}
	m_comboIdle.UpdateWindow();
}


void CAddMainCharacter::OnBnClickedButtonRemoveWalk()
{
	if (!m_instance) return;

	CString currentString;
	if (m_comboWalk.GetCount())
		m_comboWalk.GetLBText(m_comboWalk.GetCurSel(), currentString);
	CChar message[MAX_NAME_SIZE];
	sprintf(message, "Are you sure you want to remove ' %s ' animation from walk list?", (LPCTSTR)currentString);
	if (MessageBox(message, "Warning", MB_YESNO) == IDYES)
	{
		m_comboWalk.DeleteString(m_comboWalk.GetCurSel());
		m_walkIndex--;
		m_comboWalk.SetCurSel(m_walkIndex);
	}
	m_comboWalk.UpdateWindow();
}


void CAddMainCharacter::OnBnClickedButtonRemoveRun()
{
	if (!m_instance) return;

	CString currentString;
	if (m_comboRun.GetCount())
		m_comboRun.GetLBText(m_comboRun.GetCurSel(), currentString);
	CChar message[MAX_NAME_SIZE];
	sprintf(message, "Are you sure you want to remove ' %s ' animation from run list?", (LPCTSTR)currentString);
	if (MessageBox(message, "Warning", MB_YESNO) == IDYES)
	{
		m_comboRun.DeleteString(m_comboRun.GetCurSel());
		m_runIndex--;
		m_comboRun.SetCurSel(m_runIndex);
	}
	m_comboRun.UpdateWindow();
}

void CAddMainCharacter::OnBnClickedButtonRemoveJump()
{
	if (!m_instance) return;

	CString currentString;
	if (m_comboJump.GetCount())
		m_comboJump.GetLBText(m_comboJump.GetCurSel(), currentString);
	CChar message[MAX_NAME_SIZE];
	sprintf(message, "Are you sure you want to remove ' %s ' animation from jump list?", (LPCTSTR)currentString);
	if (MessageBox(message, "Warning", MB_YESNO) == IDYES)
	{
		m_comboJump.DeleteString(m_comboJump.GetCurSel());
		m_jumpIndex--;
		m_comboJump.SetCurSel(m_jumpIndex);
	}
	m_comboJump.UpdateWindow();
}

void CAddMainCharacter::OnBnClickedButtonLoadProfile()
{
	CSaveLoadCharacterProfile m_dlgProfiles;
	m_dlgProfiles.SetSaveMode(CFalse);
	if (m_dlgProfiles.DoModal() == IDOK)
	{
		if (m_instance)
		{
			Destroy();
		}
		g_importPrefab = CTrue;

		ex_pVandaEngine1Dlg->m_dlgPrefabs = CNew(CPrefabDlg);
		ex_pDlgPrefabs = ex_pVandaEngine1Dlg->m_dlgPrefabs;
		ex_pVandaEngine1Dlg->OnMenuClickedInsertPrefab(NULL, g_currentPrefabPackageName, g_currentPrefabName);

		for (CUInt j = 0; j < g_instancePrefab.size(); j++)
		{
			if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
			{
				if (g_instancePrefab[j]->GetRadius() > g_maxInstancePrefabRadius)
					g_maxInstancePrefabRadius = g_instancePrefab[j]->GetRadius();
			}
		}

		CDelete(ex_pVandaEngine1Dlg->m_dlgPrefabs);

		g_importPrefab = CFalse;
		m_instance = g_instancePrefab[g_instancePrefab.size() - 1];

		m_editCharacterModel.SetWindowTextA(g_currentPrefabName);


		m_editName.SetWindowTextA(m_characterName);

		CFloat x = m_position.x;
		m_strPosX.Format("%.2f", x);
		m_editPosX.SetWindowTextA(m_strPosX);

		CFloat y = m_position.y;
		m_strPosY.Format("%.2f", y);
		m_editPosY.SetWindowTextA(m_strPosY);

		CFloat z = m_position.z;
		m_strPosZ.Format("%.2f", z);
		m_editPosZ.SetWindowTextA(m_strPosZ);

		CFloat scale = m_scale;
		m_strScale.Format("%.2f", scale);
		m_editScale.SetWindowTextA(m_strScale);

		CFloat delayIdle = m_fPlayMoreIdlesEveryXSeconds;
		m_strPlayMoreIdlesEveryXSeconds.Format("%.2f", delayIdle);
		m_editBoxPlayMoreIdlesEveryXSeconds.SetWindowTextA(m_strPlayMoreIdlesEveryXSeconds);

		m_comboIdle.ResetContent();
		m_idleIndex = 0;
		for (CUInt i = 0; i < m_idleName.size(); i++)
			m_comboIdle.InsertString(i, m_idleName[i].c_str());
		m_comboIdle.SetCurSel(0);

		m_comboWalk.ResetContent();
		m_walkIndex = 0;
		for (CUInt i = 0; i < m_walkName.size(); i++)
			m_comboWalk.InsertString(i, m_walkName[i].c_str());
		m_comboWalk.SetCurSel(0);

		m_comboRun.ResetContent();
		m_runIndex = 0;
		for (CUInt i = 0; i < m_runName.size(); i++)
			m_comboRun.InsertString(i, m_runName[i].c_str());
		m_comboRun.SetCurSel(0);

		m_comboJump.ResetContent();
		m_jumpIndex = 0;
		for (CUInt i = 0; i < m_jumpName.size(); i++)
			m_comboJump.InsertString(i, m_jumpName[i].c_str());
		m_comboJump.SetCurSel(0);

		if (m_characterType == ePHYSX_CAMERA_THIRD_PERSON)
			CheckRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON, IDC_RADIO_THIRD_PERSON);
		else
			CheckRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON, IDC_RADIO_FIRST_PERSON);

	}
}

CVoid CAddMainCharacter::SetCharacterCameraType(CPhysXCameraType characterType)
{
	m_characterType = characterType;
}

CVoid CAddMainCharacter::SetCharacterName(CChar* name)
{
	Cpy(m_characterName, name);
}

CVoid CAddMainCharacter::SetCharacterPosition(CVec3f pos)
{
	m_position = pos;
}

CVoid CAddMainCharacter::SetCharacterScale(CFloat scale)
{
	m_scale = scale;
}

CVoid CAddMainCharacter::SetCharacterPlayMoreIdlesEveryXSeconds(CFloat m_delayIdle)
{
	m_fPlayMoreIdlesEveryXSeconds = m_delayIdle;
}

CVoid CAddMainCharacter::SetIdle(std::vector<std::string> idleName)
{
	m_idleName.clear();
	m_idleName = idleName;
}

CVoid CAddMainCharacter::SetWalk(std::vector<std::string> walkName)
{
	m_walkName.clear();
	m_walkName = walkName;
}

CVoid CAddMainCharacter::SetRun(std::vector<std::string> runName)
{
	m_runName.clear();
	m_runName = runName;
}

CVoid CAddMainCharacter::SetJump(std::vector<std::string> jumpName)
{
	m_jumpName.clear();
	m_jumpName = jumpName;
}

void CAddMainCharacter::OnBnClickedButtonSaveProfile()
{
	if (m_comboIdle.GetCount() == 0 || m_comboWalk.GetCount() == 0 || m_comboRun.GetCount() == 0 || m_comboJump.GetCount() == 0)
	{
		MessageBox("Please specify idle, walk, run and jump actions.", "Vanda Engine Error", MB_OK);
		return;
	}
	CString name;
	m_editName.GetWindowTextA(name);
	if (name.IsEmpty())
	{
		MessageBox("Please specify a name for your character.", "Vanda Engine Error", MB_OK);
		return;
	}

	CSaveLoadCharacterProfile m_dlgProfiles;
	m_dlgProfiles.SetSaveMode(CTrue);

	int newState = GetCheckedRadioButton(IDC_RADIO_FIRST_PERSON, IDC_RADIO_THIRD_PERSON);
	if (newState == IDC_RADIO_FIRST_PERSON)
		m_dlgProfiles.SetCharacterCameraType(ePHYSX_CAMERA_FIRST_PERSON);
	else
		m_dlgProfiles.SetCharacterCameraType(ePHYSX_CAMERA_THIRD_PERSON);

	CChar characterName[MAX_NAME_SIZE];
	Cpy(characterName, (LPCSTR)name);

	m_dlgProfiles.SetCharacterName(characterName);

	CFloat scale_char;
	CVec3f pos_char;
	CFloat delayIdle;

	scale_char = atof(m_strScale);
	pos_char.x = atof(m_strPosX);
	pos_char.y = atof(m_strPosY);
	pos_char.z = atof(m_strPosZ);

	delayIdle = atof(m_strPlayMoreIdlesEveryXSeconds);

	m_dlgProfiles.SetPosition(pos_char);
	m_dlgProfiles.SetScale(scale_char);
	m_dlgProfiles.SetPlayMoreIdlesEveryXSeconds(delayIdle);

	std::vector<std::string> idleName;
	std::vector<std::string> walkName;
	std::vector<std::string> jumpName;
	std::vector<std::string> runName;

	//set idle name
	for (CInt i = 0; i < m_comboIdle.GetCount(); i++)
	{
		CString currentString;
		m_comboIdle.GetLBText(i, currentString);
		idleName.push_back((LPCTSTR)currentString);
	}
	m_dlgProfiles.SetIdleName(idleName);

	//set walk name
	for (CInt i = 0; i < m_comboWalk.GetCount(); i++)
	{
		CString currentString;
		m_comboWalk.GetLBText(i, currentString);
		walkName.push_back((LPCTSTR)currentString);
	}
	m_dlgProfiles.SetWalkName(walkName);

	//set run name
	for (CInt i = 0; i < m_comboRun.GetCount(); i++)
	{
		CString currentString;
		m_comboRun.GetLBText(i, currentString);
		runName.push_back((LPCTSTR)currentString);
	}
	m_dlgProfiles.SetRunName(runName);

	//set jump name
	for (CInt i = 0; i < m_comboJump.GetCount(); i++)
	{
		CString currentString;
		m_comboJump.GetLBText(i, currentString);
		jumpName.push_back((LPCTSTR)currentString);
	}
	m_dlgProfiles.SetJumpName(jumpName);

	m_dlgProfiles.SetPhysXProperties(m_physXProperties);
	m_dlgProfiles.SetCharacterBlendingProperties(m_characterBlendingProperties);
	m_dlgProfiles.SetCharacterCameraProperties(m_camera);


	m_dlgProfiles.DoModal();
}


void CAddMainCharacter::OnEnChangeEditName()
{
	m_editName.GetWindowTextA(m_strName);
}

CVoid CAddMainCharacter::Destroy()
{
	if (!m_instance)
		return;
	CBool foundTarget = CFalse;
	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (Cmp(g_instancePrefab[i]->GetName(), m_instance->GetName()))
		{
			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
		return;

	if (g_selectedName == m_instance->GetNameIndex())
	{
		g_selectedName = -1;
		g_lastEngineObjectSelectedName = -1;
		g_showArrow = CFalse;
		SetDialogData3(CFalse);
	}
	CPrefab* dstPrefab = NULL;
	dstPrefab = m_instance->GetPrefab();
	//remove instance from prefab
	for (CUInt j = 0; j < dstPrefab->GetNumInstances(); j++)
	{
		CBool foundTarget = CFalse;
		if (Cmp(dstPrefab->GetInstance(j)->GetName(), m_instance->GetName()))
		{
			dstPrefab->RemoveInstance(j);
			foundTarget = CTrue;
		}
		if (foundTarget)
			break;
	}
	if (m_instance->GetScene(0))
	{
		CScene* scene = m_instance->GetScene(0);
		ex_pVandaEngine1Dlg->RemoveSelectedScene(scene->GetName(), scene->GetDocURI());
	}

	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (Cmp(g_instancePrefab[i]->GetName(), m_instance->GetName()))
		{
			g_instancePrefab.erase(g_instancePrefab.begin() + i);
			break;
		}
	}
	CDelete(m_instance);

	if (dstPrefab->GetNumInstances() == 0)
	{
		//now remove the prefab
		for (CUInt k = 0; k < g_prefab.size(); k++)
		{
			if (Cmp(dstPrefab->GetName(), g_prefab[k]->GetName()))
			{
				CChar prefabName[MAX_NAME_SIZE];
				sprintf(prefabName, "%s%s%s", "\nPrefab ' ", dstPrefab->GetName(), " ' removed from memory");
				PrintInfo(prefabName, COLOR_YELLOW);

				CDelete(g_prefab[k]);
				g_prefab.erase(g_prefab.begin() + k);
				break;
			}
		}
	}
	m_editName.SetWindowTextA(g_mainCharacter->GetName());
	m_editCharacterModel.SetWindowTextA(g_mainCharacter->GetPrefabName());
	std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
	std::vector<std::string> walkName = g_mainCharacter->GetWalkName();
	std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();
	std::vector<std::string> runName = g_mainCharacter->GetRunName();
	m_comboIdle.ResetContent();
	for (CUInt i = 0; i < idleName.size(); i++)
		m_comboIdle.InsertString(i, idleName[i].c_str());
	m_comboIdle.SetCurSel(0);
	m_comboWalk.ResetContent();
	for (CUInt i = 0; i < walkName.size(); i++)
		m_comboWalk.InsertString(i, walkName[i].c_str());
	m_comboWalk.SetCurSel(0);
	m_comboJump.ResetContent();
	for (CUInt i = 0; i < jumpName.size(); i++)
		m_comboJump.InsertString(i, jumpName[i].c_str());
	m_comboJump.SetCurSel(0);
	m_comboRun.ResetContent();
	for (CUInt i = 0; i < runName.size(); i++)
		m_comboRun.InsertString(i, runName[i].c_str());
	m_comboRun.SetCurSel(0);

	m_idleIndex = 0;
	m_walkIndex = 0;
	m_jumpIndex = 0;
	m_runIndex = 0;

	m_idleIndex = 0;
	m_walkIndex = 0;
	m_jumpIndex = 0;
	m_runIndex = 0;

}

void CAddMainCharacter::OnBnClickedCancel()
{
	if (!g_menu.m_insertCharacter)
	{
		Destroy();
		CDelete(g_mainCharacter);
	}
	// TODO: Add your control notification handler code here
	else if ((!m_instance && g_menu.m_insertCharacter) || m_bCharacterChanged )
	{
		if (m_bCharacterChanged)
			Destroy();

		//load instance again
		g_importPrefab = CTrue;

		ex_pVandaEngine1Dlg->m_dlgPrefabs = CNew(CPrefabDlg);
		ex_pDlgPrefabs = ex_pVandaEngine1Dlg->m_dlgPrefabs;
		ex_pVandaEngine1Dlg->OnMenuClickedInsertPrefab(NULL, g_mainCharacter->GetPackageName(), g_mainCharacter->GetPrefabName());

		for (CUInt j = 0; j < g_instancePrefab.size(); j++)
		{
			if (g_instancePrefab[j]->GetScene(0) && g_instancePrefab[j]->GetScene(0)->CastShadow())
			{
				if (g_instancePrefab[j]->GetRadius() > g_maxInstancePrefabRadius)
					g_maxInstancePrefabRadius = g_instancePrefab[j]->GetRadius();
			}
		}

		CDelete(ex_pVandaEngine1Dlg->m_dlgPrefabs);

		g_importPrefab = CFalse;
		m_instance = g_instancePrefab[g_instancePrefab.size() - 1];
		g_mainCharacter->SetInstancePrefab(m_instance);

		CFloat scale_char = g_mainCharacter->GetScale();
		CVec3f pos_char = g_mainCharacter->GetPosition();
		CVec3f scale_XYZ;
		scale_XYZ.x = scale_XYZ.y = scale_XYZ.z = g_mainCharacter->GetScale();
		g_mainCharacter->GetInstancePrefab()->SetTranslate(pos_char);
		//g_mainCharacter->GetInstancePrefab()->SetRotate(rotation);
		g_mainCharacter->GetInstancePrefab()->SetScale(scale_XYZ);
		g_mainCharacter->GetInstancePrefab()->UpdateBoundingBox(CTrue);
		g_mainCharacter->GetInstancePrefab()->CalculateDistance();
		//g_mainCharacter->GetInstancePrefab()->UpdateIsStaticOrAnimated();
		g_camera->m_perspectiveCameraYaw = NxMath::degToRad(180.f);

		g_arrowPosition = pos_char;
		g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
		g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = scale_char;

		NxExtendedVec3 pos;
		pos.x = g_arrowPosition.x;
		pos.y = g_arrowPosition.y + (g_physXProperties.m_fCapsuleHeight * 0.5f) + g_physXProperties.m_fCapsuleRadius + g_physXProperties.m_fCharacterSkinWidth;
		pos.z = g_arrowPosition.z;

		g_multipleView->m_nx->gControllers->setPosition(pos);

		//set default rotation and idle status here
		std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
		g_multipleView->ManageCharacterBlends("idle");

		g_multipleView->RenderCharacter(CFalse);

	}
	else if (m_bRemoved)
	{
		CDelete(g_mainCharacter);
	}
	g_multipleView->RenderQueries(CTrue);

	CDialog::OnCancel();
}


void CAddMainCharacter::OnEnChangeEditPosX()
{
	m_editPosX.GetWindowTextA(m_strPosX);
}


void CAddMainCharacter::OnEnChangeEditPosY()
{
	m_editPosY.GetWindowTextA(m_strPosY);
}


void CAddMainCharacter::OnEnChangeEditPosZ()
{
	m_editPosZ.GetWindowTextA(m_strPosZ);
}


void CAddMainCharacter::OnEnChangeEditPosScale()
{
	m_editScale.GetWindowTextA(m_strScale);
}

CVoid CAddMainCharacter::SetPhysXProperties(CPhysXProperties properties)
{
	m_physXProperties = properties;
}

CVoid CAddMainCharacter::SetCharacterBlendingProperties(CCharacterBlendingProperties properties)
{
	m_characterBlendingProperties = properties;
}

CVoid CAddMainCharacter::SetCharacterCameraProperties(CUpdateCamera* properties)
{
	m_camera->m_cameraManager->SetDefaultAngle(properties->m_cameraManager->GetDefaultAngle());
	m_camera->m_cameraManager->SetMinAngle(properties->m_cameraManager->GetMinAngle());
	m_camera->m_cameraManager->SetMaxAngle(properties->m_cameraManager->GetMaxAngle());

	m_camera->m_perspectiveCameraTilt = properties->m_perspectiveCameraTilt;
	m_camera->m_perspectiveCameraMinTilt = properties->m_perspectiveCameraMinTilt;
	m_camera->m_perspectiveCameraMaxTilt = properties->m_perspectiveCameraMaxTilt;
}

CVoid CAddMainCharacter::SetCharacterSoundProperties(CCharacterSoundProperties properties)
{
	m_characterSoundProperties = properties;
}

void CAddMainCharacter::OnEnChangeEditDelayPlayMoreIdlesRandomly()
{
	m_editBoxPlayMoreIdlesEveryXSeconds.GetWindowTextA(m_strPlayMoreIdlesEveryXSeconds);
	m_fPlayMoreIdlesEveryXSeconds = atof(m_strPlayMoreIdlesEveryXSeconds);
}


void CAddMainCharacter::OnBnClickedButtonSounds()
{
	CAddCharacterSound* m_characterSounds = CNew(CAddCharacterSound);
	m_characterSounds->SetCharacterSoundProperties(m_characterSoundProperties);
	m_characterSounds->DoModal();
	CDelete(m_characterSounds);
}

CVoid CAddMainCharacter::SetClickedWalkSound(CBool state)
{
	m_clickedWalkSound = state;
}

CVoid CAddMainCharacter::SetClickedRunSound(CBool state)
{
	m_clickedRunSound = state;
}

CVoid CAddMainCharacter::SetClickedJumpSound(CBool state)
{
	m_clickedJumpSound = state;
}



//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// CurrentSceneOptions.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "EditCurrentSceneOptions.h"
#include "afxdialogex.h"


// CEditCurrentSceneOptions dialog

IMPLEMENT_DYNAMIC(CEditCurrentSceneOptions, CDialog)

CEditCurrentSceneOptions::CEditCurrentSceneOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCurrentSceneOptions::IDD, pParent)
{
	setBanner = CFalse;
}

CEditCurrentSceneOptions::~CEditCurrentSceneOptions()
{
}

void CEditCurrentSceneOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BANNER, m_editBoxBanner);
	DDX_Control(pDX, IDC_EDIT_CURSOR_ICON, m_editBoxCursorIcon);
	DDX_Control(pDX, IDC_BTN_LOADING_CURSOR_ICON, m_btnCursorIcon);
	DDX_Control(pDX, IDC_EDIT_CURSOR_PERCENT, m_editBoxCursorSize);
	DDX_Control(pDX, IDC_EDIT_GLOBAL_SOUND_VOLUME, m_editBoxGlobalSoundVolume);
	DDX_Control(pDX, IDC_CHECKBOX_SHOW__CURSOR, m_checkShowCursor);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_MAIN_CHARACTER_ANIMATIONS, m_checkPauseMainCharacterAnimations);
	DDX_Control(pDX, IDC_CHECKBOX_LOCK_CHARACTER_CONTROLLER, m_checkLockCharacterController);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_ALL_PREFAB_INSTANCE_ANIMATIONS, m_checkPauseAllAnimationsOfPrefabInstances);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_PHYSICS, m_checkPausePhysics);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_WATERS, m_checkPauseAnimationOfAllWaters);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_SOUNDS, m_checkPauseAllSounds);
	DDX_Control(pDX, IDC_CHECKBOX_PAUSE_UPDATE_EVENTS, m_checkPauseAllUpdateEvents);
}


BEGIN_MESSAGE_MAP(CEditCurrentSceneOptions, CDialog)
	ON_BN_CLICKED(IDC_BTN_LOADING_BANNER, &CEditCurrentSceneOptions::OnBnClickedBtnLoadingBanner)
	ON_BN_CLICKED(IDC_BTN_LOADING_CURSOR_ICON, &CEditCurrentSceneOptions::OnBnClickedBtnLoadingCursorIcon)
	ON_EN_CHANGE(IDC_EDIT_CURSOR_PERCENT, &CEditCurrentSceneOptions::OnEnChangeEditCursorPercent)
	ON_EN_CHANGE(IDC_EDIT_GLOBAL_SOUND_VOLUME, &CEditCurrentSceneOptions::OnEnChangeEditGlobalSoundVolume)
END_MESSAGE_MAP()


// CEditCurrentSceneOptions message handlers


void CEditCurrentSceneOptions::OnBnClickedBtnLoadingBanner()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.tga"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("TGA File (*.tga)|*.tga||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		setBanner = CTrue;
		m_strBanner = (CString)dlgOpen.GetPathName();
		m_editBoxBanner.SetWindowText(m_strBanner);
	}
}


BOOL CEditCurrentSceneOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editBoxBanner.SetWindowTextA(g_sceneBanner.GetBannerPath());
	m_editBoxBanner.GetWindowTextA(m_strBanner);

	if (g_currentVSceneProperties.m_lockCharacterController)
	{
		m_checkLockCharacterController.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkLockCharacterController.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pauseAllAnimationsOfPrefabInstances)
	{
		m_checkPauseAllAnimationsOfPrefabInstances.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPauseAllAnimationsOfPrefabInstances.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pauseMainCharacterAnimations)
	{
		m_checkPauseMainCharacterAnimations.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPauseMainCharacterAnimations.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pausePhysics)
	{
		m_checkPausePhysics.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPausePhysics.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pauseAllWaterAnimations)
	{
		m_checkPauseAnimationOfAllWaters.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPauseAnimationOfAllWaters.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pauseAllUpdateEvents)
	{
		m_checkPauseAllUpdateEvents.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPauseAllUpdateEvents.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_pauseAllSounds)
	{
		m_checkPauseAllSounds.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkPauseAllSounds.SetCheck(BST_UNCHECKED);
	}

	if (g_multipleView->m_showMenuCursor)
	{
		m_checkShowCursor.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkShowCursor.SetCheck(BST_UNCHECKED);
	}

	m_menuCursorSize = g_currentVSceneProperties.m_menuCursorSize;
	m_strCursorSize.Format("%d", m_menuCursorSize);
	m_editBoxCursorSize.SetWindowTextA(m_strCursorSize);

	m_fGlobalSoundVolume = g_currentVSceneProperties.m_globalSoundVolume;
	m_strGlobalSoundVolume.Format("%.2f", m_fGlobalSoundVolume);
	m_editBoxGlobalSoundVolume.SetWindowTextA(m_strGlobalSoundVolume);

	m_editBoxCursorIcon.SetWindowTextA(g_vsceneMenuCursor.GetCursorPath());
	m_editBoxCursorIcon.GetWindowTextA(m_strCursorImage);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditCurrentSceneOptions::OnOK()
{
	if (g_multipleView->IsPlayGameMode())
	{
		if (MessageBox("Exit from play mode?", "Vanda Engine", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			ex_pVandaEngineDlg->OnBnClickedBtnDeactivatePlayMode();

		}
		else
		{
			return;
		}
	}

	if (m_strCursorImage.IsEmpty())
	{
		MessageBox("Please Choose Cursor Icon", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_strCursorSize.IsEmpty())
	{
		MessageBox("Please Fill In Cursor Size", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_strGlobalSoundVolume.IsEmpty())
	{
		MessageBox("Please Fill In Global Sound Volume", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_strBanner.IsEmpty())
	{
		MessageBox("Please Choose Banner", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_menuCursorSize < 0)
	{
		MessageBox("Cursor size must be greater than 0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_fGlobalSoundVolume > 1.0f || m_fGlobalSoundVolume < 0.0f)
	{
		MessageBox("Global sound volume must be in [0,1] range", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	g_currentVSceneProperties.m_globalSoundVolume = m_fGlobalSoundVolume;

	g_currentVSceneProperties.m_menuCursorSize = m_menuCursorSize;

	CInt checkState;
	checkState = m_checkLockCharacterController.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_currentVSceneProperties.m_lockCharacterController = CTrue;
	}
	else
	{
		g_currentVSceneProperties.m_lockCharacterController = CFalse;
	}

	checkState = m_checkPauseAllAnimationsOfPrefabInstances.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pauseAllAnimationsOfPrefabInstances = CTrue;

		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			g_instancePrefab[i]->SetUpdateAnimation(CFalse);
		}
	}
	else
	{
		g_multipleView->m_pauseAllAnimationsOfPrefabInstances = CFalse;

		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			g_instancePrefab[i]->SetUpdateAnimation(CTrue);
		}

	}

	checkState = m_checkPauseMainCharacterAnimations.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pauseMainCharacterAnimations = CTrue;
	}
	else
	{
		g_multipleView->m_pauseMainCharacterAnimations = CFalse;
	}

	checkState = m_checkPausePhysics.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pausePhysics = CTrue;
	}
	else
	{
		g_multipleView->m_pausePhysics = CFalse;
	}

	checkState = m_checkPauseAnimationOfAllWaters.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pauseAllWaterAnimations = CTrue;

		for (CUInt i = 0; i < g_engineWaters.size(); i++)
		{
			g_engineWaters[i]->SetUpdateAnimation(CFalse);
		}
	}
	else
	{
		g_multipleView->m_pauseAllWaterAnimations = CFalse;

		for (CUInt i = 0; i < g_engineWaters.size(); i++)
		{
			g_engineWaters[i]->SetUpdateAnimation(CTrue);
		}
	}

	checkState = m_checkPauseAllUpdateEvents.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pauseAllUpdateEvents = CTrue;
	}
	else
	{
		g_multipleView->m_pauseAllUpdateEvents = CFalse;
	}

	checkState = m_checkPauseAllSounds.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_pauseAllSounds = CTrue;
	}
	else
	{
		g_multipleView->m_pauseAllSounds = CFalse;
	}

	checkState = m_checkShowCursor.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_multipleView->m_showMenuCursor = CTrue;
	}
	else
	{
		g_multipleView->m_showMenuCursor = CFalse;
	}

	//Save Cursor Image
	Cpy(g_currentVSceneProperties.m_strCursorImage, m_strCursorImage.GetBuffer(m_strCursorImage.GetLength()));
	m_strCursorImage.ReleaseBuffer();

	g_vsceneMenuCursor.SetCursorPath((CChar*)m_strCursorImage.GetBuffer(m_strCursorImage.GetLength()));
	m_strCursorImage.ReleaseBuffer();
	//save functions/////////////////////////////////
	for (CUInt index = 0; index < g_VSceneNamesOfCurrentProject.size(); index++)
	{
		g_vsceneMenuCursor.IsInVSceneList(g_VSceneNamesOfCurrentProject[index], CFalse, CTrue); //Write to zip file and copy the texture
	}
	//save functions/////////////////////////////////
	Cpy(g_currentVSceneProperties.m_strCursorImage, g_vsceneMenuCursor.GetCursorPath());


	if (setBanner)
	{
		g_sceneBanner.SetBannerPath((CChar*)m_strBanner.GetBuffer(m_strBanner.GetLength()));
		m_strBanner.ReleaseBuffer();
		//save functions/////////////////////////////////
		for (CUInt index = 0; index < g_VSceneNamesOfCurrentProject.size(); index++)
		{
			g_sceneBanner.IsInVSceneList(g_VSceneNamesOfCurrentProject[index], CFalse, CTrue); //Write to zip file and copy the texture
		}
		//save functions/////////////////////////////////
		Cpy(g_currentVSceneProperties.m_strBanner, g_sceneBanner.GetBannerPath());
	}

	g_multipleView->m_soundSystem->SetListenerGain(g_currentVSceneProperties.m_globalSoundVolume);

	CDialog::OnOK();
}


void CEditCurrentSceneOptions::OnBnClickedBtnLoadingCursorIcon()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strCursorImage = (CString)dlgOpen.GetPathName();
		m_editBoxCursorIcon.SetWindowText(m_strCursorImage);
	}
}

void CEditCurrentSceneOptions::OnEnChangeEditCursorPercent()
{
	m_editBoxCursorSize.GetWindowTextA(m_strCursorSize);
	m_menuCursorSize = atoi(m_strCursorSize);
}


void CEditCurrentSceneOptions::OnEnChangeEditGlobalSoundVolume()
{
	m_editBoxGlobalSoundVolume.GetWindowTextA(m_strGlobalSoundVolume);
	m_fGlobalSoundVolume = atof(m_strGlobalSoundVolume);
}

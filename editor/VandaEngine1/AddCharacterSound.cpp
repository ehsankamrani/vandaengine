//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddCharacterSound.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddCharacterSound.h"
#include "afxdialogex.h"


// CAddCharacterSound dialog

IMPLEMENT_DYNAMIC(CAddCharacterSound, CDialog)

CAddCharacterSound::CAddCharacterSound(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCharacterSound::IDD, pParent)
{

}

CAddCharacterSound::~CAddCharacterSound()
{
}

void CAddCharacterSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_WALK_SOUND, m_editWalkSound);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_RUN_SOUND, m_editRunSound);
	DDX_Control(pDX, IDC_EDIT_CHARACTER_JUMP_SOUND, m_editJumpSound);
}


BEGIN_MESSAGE_MAP(CAddCharacterSound, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_WALK, &CAddCharacterSound::OnBnClickedButtonSelectWalk)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_RUN, &CAddCharacterSound::OnBnClickedButtonSelectRun)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_JUMP, &CAddCharacterSound::OnBnClickedButtonSelectJump)
	ON_BN_CLICKED(IDOK, &CAddCharacterSound::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddCharacterSound message handlers


void CAddCharacterSound::OnBnClickedButtonSelectWalk()
{
	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg File (*.ogg)|*.ogg||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strWalkSoundDataPath = (CString)dlgOpen.GetPathName();
		m_strWalkSoundPureDataPath = dlgOpen.GetFileTitle();
		Cpy(m_characterSoundProperties.m_walkSound, m_strWalkSoundDataPath);

		m_editWalkSound.SetWindowText(m_strWalkSoundDataPath);
		ex_pMainCharacterDlg->SetClickedWalkSound(CTrue);
	}
}


void CAddCharacterSound::OnBnClickedButtonSelectRun()
{
	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg File (*.ogg)|*.ogg||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strRunSoundDataPath = (CString)dlgOpen.GetPathName();
		m_strRunSoundPureDataPath = dlgOpen.GetFileTitle();
		Cpy(m_characterSoundProperties.m_runSound, m_strRunSoundDataPath);

		m_editRunSound.SetWindowText(m_strRunSoundDataPath);
		ex_pMainCharacterDlg->SetClickedRunSound(CTrue);

	}
}


void CAddCharacterSound::OnBnClickedButtonSelectJump()
{
	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg File (*.ogg)|*.ogg||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strJumpSoundDataPath = (CString)dlgOpen.GetPathName();
		m_strJumpSoundPureDataPath = dlgOpen.GetFileTitle();
		Cpy(m_characterSoundProperties.m_jumpSound, m_strJumpSoundDataPath);

		m_editJumpSound.SetWindowText(m_strJumpSoundDataPath);
		ex_pMainCharacterDlg->SetClickedJumpSound(CTrue);

	}
}


BOOL CAddCharacterSound::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strWalkSoundDataPath = m_characterSoundProperties.m_walkSound;
	m_strWalkSoundPureDataPath = GetAfterPath(m_characterSoundProperties.m_walkSound);

	m_editWalkSound.SetWindowTextA(m_strWalkSoundDataPath);

	m_strRunSoundDataPath = m_characterSoundProperties.m_runSound;
	m_strRunSoundPureDataPath = GetAfterPath(m_characterSoundProperties.m_runSound);

	m_editRunSound.SetWindowTextA(m_strRunSoundDataPath);

	m_strJumpSoundDataPath = m_characterSoundProperties.m_jumpSound;
	m_strJumpSoundPureDataPath = GetAfterPath(m_characterSoundProperties.m_jumpSound);

	m_editJumpSound.SetWindowTextA(m_strJumpSoundDataPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CAddCharacterSound::OnBnClickedOk()
{
	ex_pMainCharacterDlg->SetCharacterSoundProperties(m_characterSoundProperties);
	CDialog::OnOK();
}

CVoid CAddCharacterSound::SetCharacterSoundProperties(CCharacterSoundProperties properties)
{
	m_characterSoundProperties = properties;
}

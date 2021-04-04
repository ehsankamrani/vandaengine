//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddStaticSound.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddStaticSound.h"
#include  "AFXPRIV.H"

// CAddStaticSound dialog

IMPLEMENT_DYNAMIC(CAddStaticSound, CDialog)

CAddStaticSound::CAddStaticSound(CWnd* pParent /*=NULL*/)
	: CDialog(CAddStaticSound::IDD, pParent)
{
	m_loop = m_play = CTrue;
	m_create = CFalse; //I assume the user wants to edit the dialog data at the beginning. To change it, use the SetCreate() function.
	m_editMode = CFalse;
}

CAddStaticSound::~CAddStaticSound()
{
}

void CAddStaticSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_X_POS, m_editBoxStaticSoundPosX);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_Y_POS, m_editBoxStaticSoundPosY);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_Z_POS, m_editBoxStaticSoundPosZ);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_ROLLOFF, m_editBoxStaticSoundRolloff);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_PITCH, m_editBoxStaticSoundPitch);
	DDX_Control(pDX, IDC_COMBO_STATIC_SOUND_LOOP, m_comboStaticSoundLoop);
	DDX_Control(pDX, IDC_COMBO_STATIC_SOUND_PLAY, m_comboStaticSoundPlay);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_DATA, m_editBoxStaticSoundData);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_NAME, m_editBoxStaticSoundName);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_REFERENCE_DISTANCE, m_editBoxStaticSoundReferenceDistance);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_MAX_DISTANCE, m_editBoxStaticSoundMaxDistance);
	DDX_Control(pDX, IDC_EDIT_STATIC_SOUND_VOLUME, m_editBoxStaticSoundVolume);
}

BOOL CAddStaticSound::OnInitDialog()
{
	CDialog::OnInitDialog();

	if( m_create )
	{
		m_strStaticSoundPosX = "0.0f";
		m_strStaticSoundPosY = "2.0f";
		m_strStaticSoundPosZ = "0.0f";
		m_strStaticSoundRolloff = "1.0f";
		m_strStaticSoundPitch = "1.0f";
		m_strStaticSoundVolume = "1.0f";
		m_strStaticSoundReferenceDistance = "10.0f";
		m_strStaticSoundMaxDistance = "1.0f";

		CChar StaticSoundPath[MAX_NAME_SIZE];
		sprintf( StaticSoundPath, "%s%s", g_pathProperties.m_soundPath, "defaultStatic.ogg" );
		m_strStaticSoundDataPath = StaticSoundPath;
		m_strStaticSoundPureDataPath = "defaultStatic";
	}

	m_editBoxStaticSoundPosX.SetWindowTextA( m_strStaticSoundPosX );
	m_editBoxStaticSoundPosY.SetWindowTextA( m_strStaticSoundPosY );
	m_editBoxStaticSoundPosZ.SetWindowTextA( m_strStaticSoundPosZ );
	m_editBoxStaticSoundRolloff.SetWindowTextA( m_strStaticSoundRolloff );
	m_editBoxStaticSoundPitch.SetWindowTextA( m_strStaticSoundPitch );
	m_editBoxStaticSoundVolume.SetWindowTextA( m_strStaticSoundVolume );
	m_editBoxStaticSoundReferenceDistance.SetWindowTextA( m_strStaticSoundReferenceDistance );
	m_editBoxStaticSoundMaxDistance.SetWindowTextA( m_strStaticSoundMaxDistance );
	m_editBoxStaticSoundName.SetWindowTextA( m_strStaticSoundName);
	m_editBoxStaticSoundData.SetWindowTextA( m_strStaticSoundDataPath);

	m_editBoxStaticSoundVolume.EnableWindow( FALSE );
	m_comboStaticSoundPlay.InsertString( 0, "True" );
	m_comboStaticSoundPlay.InsertString( 1, "False" );
	if( m_play )
		m_comboStaticSoundPlay.SetCurSel( 0 );
	else
		m_comboStaticSoundPlay.SetCurSel( 1 );

	m_comboStaticSoundPlay.UpdateWindow();

	m_comboStaticSoundLoop.InsertString( 0, "True" );
	m_comboStaticSoundLoop.InsertString( 1, "False" );
	if( m_loop )
		m_comboStaticSoundLoop.SetCurSel( 0 );
	else
		m_comboStaticSoundLoop.SetCurSel( 1 );

	m_comboStaticSoundLoop.UpdateWindow();

	m_strStaticSoundTempName = m_strStaticSoundName;

	return TRUE;
}

BEGIN_MESSAGE_MAP(CAddStaticSound, CDialog)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_X_POS, &CAddStaticSound::OnEnChangeEditStaticSoundXPos)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_Y_POS, &CAddStaticSound::OnEnChangeEditStaticSoundYPos)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_Z_POS, &CAddStaticSound::OnEnChangeEditStaticSoundZPos)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_PITCH, &CAddStaticSound::OnEnChangeEditStaticSoundPitch)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_ROLLOFF, &CAddStaticSound::OnEnChangeEditStaticSoundRolloff)
	ON_CBN_SELCHANGE(IDC_COMBO_STATIC_SOUND_LOOP, &CAddStaticSound::OnCbnSelchangeComboStaticSoundLoop)
	ON_CBN_SELCHANGE(IDC_COMBO_STATIC_SOUND_PLAY, &CAddStaticSound::OnCbnSelchangeComboStaticSoundPlay)
	ON_BN_CLICKED(IDC_BUTTON_STATIC_SOUND_DATA, &CAddStaticSound::OnBnClickedButtonStaticSoundData)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_NAME, &CAddStaticSound::OnEnChangeEditStaticSoundName)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_REFERENCE_DISTANCE, &CAddStaticSound::OnEnChangeEditStaticSoundReferenceDistance)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_MAX_DISTANCE, &CAddStaticSound::OnEnChangeEditStaticSoundMaxDistance)
	ON_EN_CHANGE(IDC_EDIT_STATIC_SOUND_VOLUME, &CAddStaticSound::OnEnChangeEditStaticSoundVolume)
	ON_BN_CLICKED(IDOK, &CAddStaticSound::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddStaticSound message handlers

void CAddStaticSound::OnEnChangeEditStaticSoundName()
{
	m_editBoxStaticSoundName.GetWindowTextA( m_strStaticSoundName );
}

void CAddStaticSound::OnEnChangeEditStaticSoundXPos()
{
	m_editBoxStaticSoundPosX.GetWindowTextA( m_strStaticSoundPosX );
	m_fStaticSoundPos[0] = atof( m_strStaticSoundPosX );
}

void CAddStaticSound::OnEnChangeEditStaticSoundYPos()
{
	m_editBoxStaticSoundPosY.GetWindowTextA( m_strStaticSoundPosY );
	m_fStaticSoundPos[1] = atof( m_strStaticSoundPosY );
}

void CAddStaticSound::OnEnChangeEditStaticSoundZPos()
{
	m_editBoxStaticSoundPosZ.GetWindowTextA( m_strStaticSoundPosZ );
	m_fStaticSoundPos[2] = atof( m_strStaticSoundPosZ );
}

void CAddStaticSound::OnEnChangeEditStaticSoundPitch()
{
	m_editBoxStaticSoundPitch.GetWindowTextA( m_strStaticSoundPitch );
	m_fStaticSoundPitch = atof( m_strStaticSoundPitch );
}

void CAddStaticSound::OnEnChangeEditStaticSoundRolloff()
{
	m_editBoxStaticSoundRolloff.GetWindowTextA( m_strStaticSoundRolloff );
	m_fStaticSoundRolloff = atof( m_strStaticSoundRolloff );
}

void CAddStaticSound::OnEnChangeEditStaticSoundVolume()
{
	m_editBoxStaticSoundVolume.GetWindowTextA( m_strStaticSoundVolume );
	m_fStaticSoundVolume = atof( m_strStaticSoundVolume );
}

void CAddStaticSound::OnEnChangeEditStaticSoundReferenceDistance()
{
	m_editBoxStaticSoundReferenceDistance.GetWindowTextA( m_strStaticSoundReferenceDistance );
	m_fStaticSoundReferenceDistance = atof( m_strStaticSoundReferenceDistance );
}

void CAddStaticSound::OnEnChangeEditStaticSoundMaxDistance()
{
	m_editBoxStaticSoundMaxDistance.GetWindowTextA( m_strStaticSoundMaxDistance );
	m_fStaticSoundMaxDistance = atof( m_strStaticSoundMaxDistance );
}

void CAddStaticSound::OnCbnSelchangeComboStaticSoundLoop()
{
	CInt curSel = m_comboStaticSoundLoop.GetCurSel();

	switch( curSel )
	{
	case 0: //true;
		m_loop = CTrue;
		break;
	case 1: //false;
		m_loop = CFalse;
		break;
	}
}

void CAddStaticSound::OnCbnSelchangeComboStaticSoundPlay()
{
	CInt curSel = m_comboStaticSoundPlay.GetCurSel();
	switch( curSel )
	{
	case 0: //true;
		m_play = CTrue;
		break;
	case 1: //false;
		m_play = CFalse;
		break;
	}
}

void CAddStaticSound::OnBnClickedButtonStaticSoundData()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg File (*.ogg)|*.ogg||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strStaticSoundDataPath = (CString)dlgOpen.GetPathName();
		m_strStaticSoundPureDataPath = dlgOpen.GetFileTitle();

		//CChar* originalStaticSoundPath = (CChar*)m_strStaticSoundDataPath.GetBuffer(m_strStaticSoundDataPath.GetLength() ); ;
		//CChar* tempStaticSoundPath = GetAfterPath( originalStaticSoundPath );
		//CChar StaticSoundPath[MAX_NAME_SIZE];
		//sprintf( StaticSoundPath, "%s%s", g_pathProperties.m_soundPath, tempStaticSoundPath );
		//m_strStaticSoundDataPath = StaticSoundPath;
		//m_strStaticSoundDataPath.ReleaseBuffer();

		m_editBoxStaticSoundData.SetWindowText( m_strStaticSoundDataPath );
	}
}

void CAddStaticSound::OnOK()
{
	CBool compare = CFalse;
	if( !m_strStaticSoundName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
			if( m_strStaticSoundName == m_strStaticSoundTempName )
				compare = CFalse;
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			if( Cmp((LPCSTR)m_strStaticSoundName, (*it).c_str() ) )
			{
				MessageBox( "This name already exist. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR );
				return;
			}
		}
	}

	if(	m_strStaticSoundPosX.IsEmpty() || m_strStaticSoundPosY.IsEmpty() || m_strStaticSoundPosZ.IsEmpty() || m_strStaticSoundPitch.IsEmpty() 
		|| m_strStaticSoundName.IsEmpty() || m_strStaticSoundDataPath.IsEmpty() || m_strStaticSoundRolloff.IsEmpty() ||	m_strStaticSoundMaxDistance.IsEmpty()
		|| m_strStaticSoundVolume.IsEmpty() )
	{
		MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	}
	else
		CDialog::OnOK();
}



INT_PTR CAddStaticSound::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddStaticSound::IDD))) return -1;
	// set the font, for example "Arial", 10 pts.
	dlt.SetFont("Arial", 8);
	// get pointer to the modified dialog template
	LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	// let MFC know that you are using your own template
	m_lpszTemplateName = NULL;
	InitModalIndirect(pdata);
	// display dialog box
	nResult = CDialog::DoModal();
	// unlock memory object
	GlobalUnlock(dlt.m_hTemplate);
	return nResult;
}

void CAddStaticSound::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

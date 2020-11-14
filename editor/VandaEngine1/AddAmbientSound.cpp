//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// CAddAmbientSound.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddAmbientSound.h"
#include  "AFXPRIV.H"


// CAddAmbientSound dialog

IMPLEMENT_DYNAMIC(CAddAmbientSound, CDialog)

CAddAmbientSound::CAddAmbientSound(CWnd* pParent /*=NULL*/)
	: CDialog(CAddAmbientSound::IDD, pParent)
{
	m_create = CFalse;
	m_editMode = CFalse;
}

CAddAmbientSound::~CAddAmbientSound()
{
}

void CAddAmbientSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_SOUND_BUFFER, m_editBoxAmbientSoundBuffer);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_SOUND_NAME, m_editBoxAmbientSoundName);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_SOUND_PITCH, m_editBoxAmbientSoundPitch);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_SOUND_VOLUME, m_editBoxAmbientSoundVolume);
}


BEGIN_MESSAGE_MAP(CAddAmbientSound, CDialog)
	ON_BN_CLICKED(ID_BUTTON_AMBIENT_SOUND, &CAddAmbientSound::OnBnClickedButtonAmbientSound)
	ON_EN_CHANGE(IDC_EDIT_AMBIENT_SOUND_NAME, &CAddAmbientSound::OnEnChangeEditAmbientSoundName)
	ON_EN_CHANGE(IDC_EDIT_AMBIENT_SOUND_PITCH, &CAddAmbientSound::OnEnChangeEditAmbientSoundPitch)
	ON_EN_CHANGE(IDC_EDIT_AMBIENT_SOUND_VOLUME, &CAddAmbientSound::OnEnChangeEditAmbientSoundVolume)
END_MESSAGE_MAP()


// CAddAmbientSound message handlers

void CAddAmbientSound::OnBnClickedButtonAmbientSound()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.ogg"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Ogg File (*.ogg)|*.ogg||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strAmbientSoundBuffer = (CString)dlgOpen.GetPathName();
		m_strPureAmbientSoundBuffer = dlgOpen.GetFileTitle();

		//CChar* originalAmbientSoundPath = (CChar*)m_strAmbientSoundBuffer.GetBuffer(m_strAmbientSoundBuffer.GetLength() ); ;
		//CChar* tempAmbientSoundPath = GetAfterPath( originalAmbientSoundPath );
		//CChar AmbientSoundPath[MAX_NAME_SIZE];
		//sprintf( AmbientSoundPath, "%s%s", g_pathProperties.m_soundPath, tempAmbientSoundPath );
		//m_strAmbientSoundBuffer = AmbientSoundPath;
		//m_strAmbientSoundBuffer.ReleaseBuffer();

		m_editBoxAmbientSoundBuffer.SetWindowText( m_strAmbientSoundBuffer );
	}
}

void CAddAmbientSound::OnOK()
{
	CBool compare = CFalse;
	if( !m_strAmbientSoundName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
			if( m_strAmbientSoundName == m_strAmbientSoundTempName )
				compare = CFalse;
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			if( Cmp((LPCSTR)m_strAmbientSoundName, (*it).c_str() ) )
			{
				MessageBox( "This name already exist. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR );
				return;
			}
		}
	}
	if( m_strAmbientSoundName.IsEmpty() || m_strAmbientSoundBuffer.IsEmpty() || m_strAmbientSoundVolume.IsEmpty() || m_strAmbientSoundPitch.IsEmpty() )
		MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	else
		CDialog::OnOK();
}

void CAddAmbientSound::OnEnChangeEditAmbientSoundName()
{
	m_editBoxAmbientSoundName.GetWindowTextA( m_strAmbientSoundName );
}

void CAddAmbientSound::OnEnChangeEditAmbientSoundPitch()
{
	m_editBoxAmbientSoundPitch.GetWindowTextA( m_strAmbientSoundPitch );
	m_pitch = atof( m_strAmbientSoundPitch );
}

void CAddAmbientSound::OnEnChangeEditAmbientSoundVolume()
{
	m_editBoxAmbientSoundVolume.GetWindowTextA( m_strAmbientSoundVolume );
	m_volume = atof( m_strAmbientSoundVolume );
}

BOOL CAddAmbientSound::OnInitDialog()
{
	CDialog::OnInitDialog();

	if( m_create )
	{
		m_strAmbientSoundName = "Ambient Sound";
		m_strAmbientSoundVolume = "1.0f";
		m_strAmbientSoundPitch = "1.0f";
		CChar AmbientSoundPath[MAX_NAME_SIZE];
		sprintf( AmbientSoundPath, "%s%s", g_pathProperties.m_soundPath, "defaultAmbient.ogg" );
		m_strAmbientSoundBuffer = AmbientSoundPath;
		m_strPureAmbientSoundBuffer = "defaultAmbient";
	}
	m_editBoxAmbientSoundName.SetWindowTextA( m_strAmbientSoundName );
	m_editBoxAmbientSoundVolume.SetWindowTextA( m_strAmbientSoundVolume );
	m_editBoxAmbientSoundPitch.SetWindowTextA( m_strAmbientSoundPitch );
	m_editBoxAmbientSoundBuffer.SetWindowTextA( m_strAmbientSoundBuffer );
	m_strAmbientSoundTempName = m_strAmbientSoundName;

	return TRUE;  // return TRUE unless you set the focus to a control
}

INT_PTR CAddAmbientSound::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddAmbientSound::IDD))) return -1;
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

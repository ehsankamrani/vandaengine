//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddSkyDome.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddSkyDome.h"
#include  "AFXPRIV.H"

// CAddSkyDome dialog

IMPLEMENT_DYNAMIC(CAddSkyDome, CDialog)

CAddSkyDome::CAddSkyDome(CWnd* pParent /*=NULL*/)
	: CDialog(CAddSkyDome::IDD, pParent)
{
	m_bSkyDomeExponential = CFalse;
	m_create = CFalse;
	m_editMode = CFalse;
}

CAddSkyDome::~CAddSkyDome()
{
}

void CAddSkyDome::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_NAME, m_editBoxSkyDomeName);
	DDX_Control(pDX, IDC_EDIT_SKYDOM_PATH, m_editBoxSkyDomeData);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_X_POS, m_editBoxSkyDomePosX);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_Y_POS, m_editBoxSkyDomePosY);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_Z_POS, m_editBoxSkyDomePosZ);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_SIDES, m_editBoxSkyDomeSides);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_SLICES, m_editBoxSkyDomeSlices);
	DDX_Control(pDX, IDC_COMBO_SKYDOM_EXPONENTIAL, m_comboSkyDomeExponential);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_RADIUS, m_editBoxSkyDomeRadius);
	DDX_Control(pDX, IDC_EDIT_SKYDOME_DAMPENING, m_editBoxSkyDomeDampening);
}


BEGIN_MESSAGE_MAP(CAddSkyDome, CDialog)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_NAME, &CAddSkyDome::OnEnChangeEditSkydomeName)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_X_POS, &CAddSkyDome::OnEnChangeEditSkydomeXPos)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_Y_POS, &CAddSkyDome::OnEnChangeEditSkydomeYPos)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_RADIUS, &CAddSkyDome::OnEnChangeEditSkydomeRadius)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_DAMPENING, &CAddSkyDome::OnEnChangeEditSkydomeDampening)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_Z_POS, &CAddSkyDome::OnEnChangeEditSkydomeZPos)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_SIDES, &CAddSkyDome::OnEnChangeEditSkydomeSides)
	ON_EN_CHANGE(IDC_EDIT_SKYDOME_SLICES, &CAddSkyDome::OnEnChangeEditSkydomeSlices)
	ON_CBN_SELCHANGE(IDC_COMBO_SKYDOM_EXPONENTIAL, &CAddSkyDome::OnCbnSelchangeComboSkydomExponential)
	ON_BN_CLICKED(ID_BUTTON_SKYDOM_PATH, &CAddSkyDome::OnBnClickedButtonSkydomPath)
	ON_BN_CLICKED(IDOK, &CAddSkyDome::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_SKYDOM_PATH, &CAddSkyDome::OnEnChangeEditSkydomPath)
END_MESSAGE_MAP()


// CAddSkyDome message handlers
BOOL CAddSkyDome::OnInitDialog()
{
	if( m_create )
	{
		m_strSkyDomeName = "Sky Dome";
		m_strSkyDomePosX = "0.0f";
		m_strSkyDomePosY = "0.0f";
		m_strSkyDomePosZ = "0.0f";

		m_strSkyDomeSides = "15.0f";
		m_strSkyDomeSlices = "15.0f";

		m_strSkyDomeDampening = "0.8f";

		m_strSkyDomeRadius = "850.0f";

		CChar skyPath[MAX_NAME_SIZE];
		sprintf( skyPath, "%s%s", g_pathProperties.m_skyPath, "defaultTexture.dds" );
		m_strSkyDomePath = skyPath;
		m_strSkyDomePurePath = "defaultTexture";
	}
	CDialog::OnInitDialog();
	m_comboSkyDomeExponential.InsertString( 0, "True" );
	m_comboSkyDomeExponential.InsertString( 1, "False" );

	if( m_bSkyDomeExponential )
		m_comboSkyDomeExponential.SetCurSel( 0 );
	else
		m_comboSkyDomeExponential.SetCurSel( 1 );

	m_comboSkyDomeExponential.UpdateWindow();

	m_editBoxSkyDomePosX.SetWindowTextA( m_strSkyDomePosX );
	m_editBoxSkyDomePosY.SetWindowTextA( m_strSkyDomePosY );
	m_editBoxSkyDomePosZ.SetWindowTextA( m_strSkyDomePosZ );
	m_editBoxSkyDomeName.SetWindowTextA( m_strSkyDomeName );
	m_editBoxSkyDomeData.SetWindowTextA( m_strSkyDomePath );
	m_editBoxSkyDomeSides.SetWindowTextA( m_strSkyDomeSides );
	m_editBoxSkyDomeSlices.SetWindowTextA( m_strSkyDomeSlices );
	m_editBoxSkyDomeRadius.SetWindowTextA( m_strSkyDomeRadius );
	m_editBoxSkyDomeDampening.SetWindowTextA( m_strSkyDomeDampening );

	m_strSkyDomeTempName = m_strSkyDomeName;

	return TRUE;
}

void CAddSkyDome::OnOK()
{
	CBool compare = CFalse;
	if( !m_strSkyDomeName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
		{
			CChar name[MAX_NAME_SIZE];
			CChar tempName[MAX_NAME_SIZE];
			Cpy(name, (LPCSTR)m_strSkyDomeName);
			Cpy(tempName, (LPCSTR)m_strSkyDomeTempName);

			StringToUpper(name);
			StringToUpper(tempName);

			if (Cmp(name, tempName))
				compare = CFalse;
		}
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			CChar engineObjectCapsName[MAX_NAME_SIZE];
			Cpy(engineObjectCapsName, (*it).c_str());
			StringToUpper(engineObjectCapsName);

			CChar currentObjectName[MAX_NAME_SIZE];
			Cpy(currentObjectName, (LPCSTR)m_strSkyDomeName);
			StringToUpper(currentObjectName);

			if (Cmp(currentObjectName, engineObjectCapsName))
			{
				MessageBox("This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	
	if(	m_strSkyDomePosX.IsEmpty() || m_strSkyDomePosY.IsEmpty() || m_strSkyDomePosZ.IsEmpty() || m_strSkyDomeName.IsEmpty() 
		|| m_strSkyDomePath.IsEmpty() || m_strSkyDomeSides.IsEmpty() || m_strSkyDomeSlices.IsEmpty() ||	m_strSkyDomeDampening.IsEmpty()
		|| m_strSkyDomeRadius.IsEmpty() )
	{
		MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	}
	else
		CDialog::OnOK();
}


void CAddSkyDome::OnEnChangeEditSkydomeName()
{
	m_editBoxSkyDomeName.GetWindowTextA( m_strSkyDomeName ); 
}

void CAddSkyDome::OnEnChangeEditSkydomeXPos()
{
	m_editBoxSkyDomePosX.GetWindowTextA( m_strSkyDomePosX );
	m_fSkyDomePos[0] = atof( m_strSkyDomePosX );

}

void CAddSkyDome::OnEnChangeEditSkydomeYPos()
{
	m_editBoxSkyDomePosY.GetWindowTextA( m_strSkyDomePosY );
	m_fSkyDomePos[1] = atof( m_strSkyDomePosY );

}

void CAddSkyDome::OnEnChangeEditSkydomeZPos()
{
	m_editBoxSkyDomePosZ.GetWindowTextA( m_strSkyDomePosZ );
	m_fSkyDomePos[2] = atof( m_strSkyDomePosZ );

}

void CAddSkyDome::OnEnChangeEditSkydomeRadius()
{
	m_editBoxSkyDomeRadius.GetWindowTextA( m_strSkyDomeRadius );
	m_fSkyDomeRadius = atof( m_strSkyDomeRadius );

}

void CAddSkyDome::OnEnChangeEditSkydomeDampening()
{
	m_editBoxSkyDomeDampening.GetWindowTextA( m_strSkyDomeDampening );
	m_fSkyDomeDampening = atof( m_strSkyDomeDampening );
}

void CAddSkyDome::OnEnChangeEditSkydomeSides()
{
	m_editBoxSkyDomeSides.GetWindowTextA( m_strSkyDomeSides );
	m_iSkyDomeSides = atoi( m_strSkyDomeSides );
}

void CAddSkyDome::OnEnChangeEditSkydomeSlices()
{
	m_editBoxSkyDomeSlices.GetWindowTextA( m_strSkyDomeSlices );
	m_iSkyDomeSlices = atoi( m_strSkyDomeSlices );
}

void CAddSkyDome::OnCbnSelchangeComboSkydomExponential()
{
	CInt curSel = m_comboSkyDomeExponential.GetCurSel();
	switch( curSel )
	{
	case 0: //true;
		m_bSkyDomeExponential = CTrue;
		break;
	case 1: //false;
		m_bSkyDomeExponential = CFalse;
		break;
	}
}

void CAddSkyDome::OnBnClickedButtonSkydomPath()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strSkyDomePath = (CString)dlgOpen.GetPathName();
		m_strSkyDomePurePath = dlgOpen.GetFileTitle();

		//CChar* originalSkyPath = (CChar*)m_strSkyDomePath.GetBuffer(m_strSkyDomePath.GetLength() ); ;
		//CChar* tempSkyPath = GetAfterPath( originalSkyPath );
		//CChar skyPath[MAX_NAME_SIZE];
		//sprintf( skyPath, "%s%s", g_pathProperties.m_skyPath, tempSkyPath );
		//m_strSkyDomePath = skyPath;
		//m_strSkyDomePath.ReleaseBuffer();

		m_editBoxSkyDomeData.SetWindowText( m_strSkyDomePath );
	}
}

INT_PTR CAddSkyDome::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddSkyDome::IDD))) return -1;
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


void CAddSkyDome::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CAddSkyDome::OnEnChangeEditSkydomPath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

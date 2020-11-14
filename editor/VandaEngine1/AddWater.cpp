//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddWater.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddWater.h"
#include  "AFXPRIV.H"


// CAddWater dialog

IMPLEMENT_DYNAMIC(CAddWater, CDialog)

CAddWater::CAddWater(CWnd* pParent /*=NULL*/)
	: CDialog(CAddWater::IDD, pParent)
{
	m_create = CFalse;
	m_editMode = CFalse;
}

CAddWater::~CAddWater()
{
}

BOOL CAddWater::OnInitDialog()
{
	CDialog::OnInitDialog();
	if( m_create )
	{
		m_strWaterSpeed = "0.08f";
		m_strWaterUV = "4.0f";
		m_strWaterScale = "20.0f";
		
		m_strWaterCX = "0.0f";
		m_strWaterCY = "0.0f";
		m_strWaterCZ = "0.0f";

		m_strWaterLX = "25.0f";
		m_strWaterLY = "3.0f";
		m_strWaterLZ = "25.0f";

		m_strWaterHeight = "0.0f";
		CChar DuDvPath[MAX_NAME_SIZE];
		CChar NormalMapPath[MAX_NAME_SIZE];
		sprintf( DuDvPath, "%s%s", g_pathProperties.m_waterPath, "dudvmap.dds" );
		m_strDuDvMap = DuDvPath;
		m_strPureDuDvMap = "dudvmap";
		sprintf( NormalMapPath, "%s%s", g_pathProperties.m_waterPath, "normalmap.dds" );
		m_strNormalMap = NormalMapPath;
		m_strPureNormalMap = "normalmap";
		m_isVisible = CTrue;
	}
	m_editBoxDuDvMap.SetWindowTextA( m_strDuDvMap );
	m_editBoxNormalMap.SetWindowTextA( m_strNormalMap );
	m_editBoxWaterName.SetWindowTextA( m_strWaterName );
	m_editBoxHeight.SetWindowTextA( m_strWaterHeight );
	m_editBoxSpeed.SetWindowTextA( m_strWaterSpeed );
	m_editBoxUV.SetWindowTextA( m_strWaterUV );
	m_editBoxScale.SetWindowTextA( m_strWaterScale );
	m_editBoxCX.SetWindowTextA( m_strWaterCX );
	m_editBoxCY.SetWindowTextA( m_strWaterCY );
	m_editBoxCZ.SetWindowTextA( m_strWaterCZ );
	m_editBoxLX.SetWindowTextA( m_strWaterLX );
	m_editBoxLY.SetWindowTextA( m_strWaterLY );
	m_editBoxLZ.SetWindowTextA( m_strWaterLZ );

	if (m_isVisible)
		m_checkIsVisible.SetCheck(BST_CHECKED);
	else
		m_checkIsVisible.SetCheck(BST_UNCHECKED);

	m_strTempWaterName = m_strWaterName;

	m_editBoxHeight.EnableWindow( FALSE );
	return TRUE;
}

void CAddWater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WATER_DUDV, m_editBoxDuDvMap);
	DDX_Control(pDX, IDC_EDIT_WATER_NORMAL, m_editBoxNormalMap);
	DDX_Control(pDX, IDC_EDIT_WATER_NAME, m_editBoxWaterName);
	DDX_Control(pDX, IDC_EDIT_WATER_HEIGHT, m_editBoxHeight);
	DDX_Control(pDX, IDC_EDIT_WATER_SPEED, m_editBoxSpeed);
	DDX_Control(pDX, IDC_EDIT_WATER_UV, m_editBoxUV);
	DDX_Control(pDX, IDC_EDIT_WATER_SCALE, m_editBoxScale);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_X, m_editBoxCX);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_Y, m_editBoxCY);
	DDX_Control(pDX, IDC_EDIT_WATER_CENTER_Z, m_editBoxCZ);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_X, m_editBoxLX);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_Y, m_editBoxLY);
	DDX_Control(pDX, IDC_EDIT_WATER_LIGHT_Z, m_editBoxLZ);
	DDX_Control(pDX, IDC_CHECK_IS_WATER_VISIBLE, m_checkIsVisible);
}


BEGIN_MESSAGE_MAP(CAddWater, CDialog)
	ON_BN_CLICKED(ID_BUTTON_WATER_DUDV, &CAddWater::OnBnClickedButtonWaterDudv)
	ON_BN_CLICKED(ID_BUTTON_WATER_NORMAL, &CAddWater::OnBnClickedButtonWaterNormal)
	ON_EN_CHANGE(IDC_EDIT_WATER_NAME, &CAddWater::OnEnChangeEditWaterName)
	ON_EN_CHANGE(IDC_EDIT_WATER_HEIGHT, &CAddWater::OnEnChangeEditWaterHeight)
	ON_EN_CHANGE(IDC_EDIT_WATER_SPEED, &CAddWater::OnEnChangeEditWaterSpeed)
	ON_EN_CHANGE(IDC_EDIT_WATER_UV, &CAddWater::OnEnChangeEditWaterUv)
	ON_EN_CHANGE(IDC_EDIT_WATER_SCALE, &CAddWater::OnEnChangeEditWaterScale)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_X, &CAddWater::OnEnChangeEditWaterCenterX)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_Y, &CAddWater::OnEnChangeEditWaterCenterY)
	ON_EN_CHANGE(IDC_EDIT_WATER_CENTER_Z, &CAddWater::OnEnChangeEditWaterCenterZ)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_X, &CAddWater::OnEnChangeEditWaterLightX)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_Y, &CAddWater::OnEnChangeEditWaterLightY)
	ON_EN_CHANGE(IDC_EDIT_WATER_LIGHT_Z, &CAddWater::OnEnChangeEditWaterLightZ)
END_MESSAGE_MAP()


// CAddWater message handlers

void CAddWater::OnBnClickedButtonWaterDudv()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strDuDvMap = (CString)dlgOpen.GetPathName();
		m_strPureDuDvMap = dlgOpen.GetFileTitle();

		//CChar* originalDuDvPath = (CChar*)m_strDuDvMap.GetBuffer(m_strDuDvMap.GetLength() ); ;
		//CChar* tempDuDvPath = GetAfterPath( originalDuDvPath );
		//CChar DuDvPath[MAX_NAME_SIZE];
		//sprintf( DuDvPath, "%s%s", g_pathProperties.m_waterPath, tempDuDvPath );
		//m_strDuDvMap = DuDvPath;
		//m_strDuDvMap.ReleaseBuffer();

		m_editBoxDuDvMap.SetWindowText( m_strDuDvMap );
	}
}

void CAddWater::OnBnClickedButtonWaterNormal()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		m_strNormalMap = (CString)dlgOpen.GetPathName();
		m_strPureNormalMap = dlgOpen.GetFileTitle();

		//CChar* originalNormalMapPath = (CChar*)m_strNormalMap.GetBuffer(m_strNormalMap.GetLength() ); ;
		//CChar* tempNormalMapPath = GetAfterPath( originalNormalMapPath );
		//CChar NormalMapPath[MAX_NAME_SIZE];
		//sprintf( NormalMapPath, "%s%s", g_pathProperties.m_waterPath, tempNormalMapPath );
		//m_strNormalMap = NormalMapPath;
		//m_strNormalMap.ReleaseBuffer();

		m_editBoxNormalMap.SetWindowText( m_strNormalMap );
	}
}

void CAddWater::OnOK()
{
	CBool compare = CFalse;
	if( !m_strWaterName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
			if( m_strWaterName == m_strTempWaterName )
				compare = CFalse;
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			if( Cmp((LPCSTR)m_strWaterName, (*it).c_str() ) )
			{
				MessageBox( "This name already exists. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR );
				return;
			}
		}
	}
	CInt checkState;
	checkState = m_checkIsVisible.GetCheck();
	if (checkState == BST_CHECKED)
		m_isVisible = CTrue;
	else
		m_isVisible = CFalse;

	// TODO: Add your specialized code here and/or call the base class
	if( m_strNormalMap.IsEmpty() || m_strDuDvMap.IsEmpty() || m_strWaterName.IsEmpty() || m_strWaterHeight.IsEmpty() ||
		m_strWaterSpeed.IsEmpty() || m_strWaterUV.IsEmpty() || m_strWaterScale.IsEmpty() || m_strWaterCX.IsEmpty() ||
		m_strWaterCY.IsEmpty() || m_strWaterCZ.IsEmpty() || m_strWaterLX.IsEmpty() || m_strWaterLY.IsEmpty() || 
		m_strWaterLZ.IsEmpty() )
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	else
		CDialog::OnOK();
}
void CAddWater::OnEnChangeEditWaterName()
{
	m_editBoxWaterName.GetWindowTextA( m_strWaterName );
}

INT_PTR CAddWater::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddWater::IDD))) return -1;
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

void CAddWater::OnEnChangeEditWaterHeight()
{
	m_editBoxHeight.GetWindowTextA( m_strWaterHeight );
	m_fWaterHeight = atof( m_strWaterHeight );

}

void CAddWater::OnEnChangeEditWaterSpeed()
{
	m_editBoxSpeed.GetWindowTextA( m_strWaterSpeed );
	m_fWaterSpeed = atof( m_strWaterSpeed );
}

void CAddWater::OnEnChangeEditWaterUv()
{
	m_editBoxUV.GetWindowTextA( m_strWaterUV );
	m_fWaterUV = atof( m_strWaterUV );
}

void CAddWater::OnEnChangeEditWaterScale()
{
	m_editBoxScale.GetWindowTextA( m_strWaterScale );
	m_fWaterScale = atof( m_strWaterScale );
}

void CAddWater::OnEnChangeEditWaterCenterX()
{
	m_editBoxCX.GetWindowTextA( m_strWaterCX );
	m_fWaterCPos[0] = atof( m_strWaterCX );
}

void CAddWater::OnEnChangeEditWaterCenterY()
{
	m_editBoxCY.GetWindowTextA( m_strWaterCY );
	m_fWaterCPos[1] = atof( m_strWaterCY );
}

void CAddWater::OnEnChangeEditWaterCenterZ()
{
	m_editBoxCZ.GetWindowTextA( m_strWaterCZ );
	m_fWaterCPos[2] = atof( m_strWaterCZ );
}

void CAddWater::OnEnChangeEditWaterLightX()
{
	m_editBoxLX.GetWindowTextA( m_strWaterLX );
	m_fWaterLPos[0] = atof( m_strWaterLX );
}

void CAddWater::OnEnChangeEditWaterLightY()
{
	m_editBoxLY.GetWindowTextA( m_strWaterLY );
	m_fWaterLPos[1] = atof( m_strWaterLY );
}

void CAddWater::OnEnChangeEditWaterLightZ()
{
	m_editBoxLZ.GetWindowTextA( m_strWaterLZ );
	m_fWaterLPos[2] = atof( m_strWaterLZ );
}


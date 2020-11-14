//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddLight.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddLight.h"
#include  "AFXPRIV.H"

enum
{
	eDIALOG_POINT_LIGHT = 0, eDIALOG_DIRECTIONAL_LIGHT, eDIALOG_SPOT_LIGHT
};
// CAddLight dialog

IMPLEMENT_DYNAMIC(CAddLight, CDialog)

CAddLight::CAddLight(CWnd* pParent /*=NULL*/)
	: CDialog(CAddLight::IDD, pParent)
{
	m_create = CFalse;
	m_editMode = CFalse;
}

CAddLight::~CAddLight()
{
}

void CAddLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_AMBIENT_LIGHT, m_btnAmbientLight);
	DDX_Control(pDX, IDC_BUTTON_DIFFUSE_LIGHT, m_btnDiffuseLight);
	DDX_Control(pDX, IDC_BUTTON_SPECULAR_LIGHT, m_btnSpecularLight);
	DDX_Control(pDX, IDC_EDIT_LIGHT_POS_X, m_editBoxLightPosX);
	DDX_Control(pDX, IDC_EDIT_LIGHT_POS_Y, m_editBoxLightPosY);
	DDX_Control(pDX, IDC_EDIT_LIGHT_POS_Z, m_editBoxLightPosZ);
	DDX_Control(pDX, IDC_EDIT_CONSTANT_ATTENUATION, m_editBoxConstantAttenuation);
	DDX_Control(pDX, IDC_EDIT_LINEAR_ATTENUATION, m_editBoxLinearAttenuation);
	DDX_Control(pDX, IDC_EDIT_QUAD_ATTENUATION, m_editBoxQuadAttenuation);
	DDX_Control(pDX, IDC_EDIT_SPOT_CUTOFF, m_editBoxSpotCutoff);
	DDX_Control(pDX, IDC_EDIT_SPOT_DIRECTION_X, m_editBoxSpotDirectionX);
	DDX_Control(pDX, IDC_EDIT_SPOT_EXPONENT, m_editBoxSpotExponent);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_COMB_LIGHT_TYPE, m_comboLightType);
	DDX_Control(pDX, IDC_EDIT_LIGHT_AMBIENT_COLOR, m_editBoxAmbientColor);
	DDX_Control(pDX, IDC_EDIT_LIGHT_DIFFUSE_COLOR, m_editBoxDiffuseColor);
	DDX_Control(pDX, IDC_EDIT_LIGHT_SPECULAR_COLOR, m_editBoxSpecularColor);
	DDX_Control(pDX, IDC_EDIT_SHININESS, m_editBoxShininess);
	DDX_Control(pDX, IDC_EDIT_SPOT_DIRECTION_Y, m_editBoxSpotDirectionY);
	DDX_Control(pDX, IDC_EDIT_SPOT_DIRECTION_Z, m_editBoxSpotDirectionZ);
	DDX_Control(pDX, IDC_EDIT_LIGHT_NAME, m_editBoxLightName);
}


BEGIN_MESSAGE_MAP(CAddLight, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_AMBIENT_LIGHT, &CAddLight::OnBnClickedButtonAmbientLight)
	ON_BN_CLICKED(IDC_BUTTON_DIFFUSE_LIGHT, &CAddLight::OnBnClickedButtonDiffuseLight)
	ON_BN_CLICKED(IDC_BUTTON_SPECULAR_LIGHT, &CAddLight::OnBnClickedButtonSpecularLight)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_CONSTANT_ATTENUATION, &CAddLight::OnEnChangeEditConstantAttenuation)
	ON_EN_CHANGE(IDC_EDIT_LINEAR_ATTENUATION, &CAddLight::OnEnChangeEditLinearAttenuation)
	ON_EN_CHANGE(IDC_EDIT_QUAD_ATTENUATION, &CAddLight::OnEnChangeEditQuadAttenuation)
	ON_EN_CHANGE(IDC_EDIT_SHININESS, &CAddLight::OnEnChangeEditShininess)
	ON_EN_CHANGE(IDC_EDIT_SPOT_DIRECTION_X, &CAddLight::OnEnChangeEditSpotDirectionX)
	ON_EN_CHANGE(IDC_EDIT_SPOT_EXPONENT, &CAddLight::OnEnChangeEditSpotExponent)
	ON_EN_CHANGE(IDC_EDIT_SPOT_CUTOFF, &CAddLight::OnEnChangeEditSpotCutoff)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_POS_X, &CAddLight::OnEnChangeEditLightPosX)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_POS_Y, &CAddLight::OnEnChangeEditLightPosY)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_POS_Z, &CAddLight::OnEnChangeEditLightPosZ)
	ON_EN_CHANGE(IDC_EDIT_SPOT_DIRECTION_Y, &CAddLight::OnEnChangeEditSpotDirectionY)
	ON_EN_CHANGE(IDC_EDIT_SPOT_DIRECTION_Z, &CAddLight::OnEnChangeEditSpotDirectionZ)
	ON_CBN_SELCHANGE(IDC_COMB_LIGHT_TYPE, &CAddLight::OnCbnSelchangeCombLightType)
	ON_BN_CLICKED(IDOK, &CAddLight::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_NAME, &CAddLight::OnEnChangeEditLightName)
	ON_BN_CLICKED(IDCANCEL, &CAddLight::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAddLight message handlers

void CAddLight::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	//CInt width = GetSystemMetrics( SM_CXFULLSCREEN );
	//CInt height = GetSystemMetrics( SM_CYFULLSCREEN );
	//CRect rect( 0,0, int(25 * width / 100 ) , int( 50 * height / 100 ) );
	//ScreenToClient( rect );
	//MoveWindow( rect );
	// TODO: Add your message handler code here
}

void CAddLight::OnBnClickedButtonAmbientLight()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_ambientColor = dlg.GetColor();
		m_fAmbientColor[0] = ( CFloat )GetRValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[1] = ( CFloat )GetGValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[2] = ( CFloat )GetBValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_ambientBrush.CreateSolidBrush( m_ambientColor );
		m_editBoxAmbientColor.RedrawWindow();
	}
}

void CAddLight::OnBnClickedButtonDiffuseLight()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_diffuseColor = dlg.GetColor();
		m_fDiffuseColor[0] = ( CFloat )GetRValue( m_diffuseColor ) / 255.f;
		m_fDiffuseColor[1] = ( CFloat )GetGValue( m_diffuseColor ) / 255.f;
		m_fDiffuseColor[2] = ( CFloat )GetBValue( m_diffuseColor ) / 255.f;
		m_fDiffuseColor[3] = 1.0f;
		m_diffuseBrush.CreateSolidBrush( m_diffuseColor );
		m_editBoxDiffuseColor.RedrawWindow();
	}

}

void CAddLight::OnBnClickedButtonSpecularLight()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_specularColor = dlg.GetColor();
		m_fSpecularColor[0] = ( CFloat )GetRValue( m_specularColor ) / 255.f;
		m_fSpecularColor[1] = ( CFloat )GetGValue( m_specularColor ) / 255.f;
		m_fSpecularColor[2] = ( CFloat )GetBValue( m_specularColor ) / 255.f;
		m_fSpecularColor[3] = 1.0f;
		m_specularBrush.CreateSolidBrush( m_specularColor );
		m_editBoxSpecularColor.RedrawWindow();
	}
}

HBRUSH CAddLight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch( pWnd->GetDlgCtrlID() )
	{
	case IDC_EDIT_LIGHT_AMBIENT_COLOR:
		pDC->SetBkColor( m_ambientColor );
		return m_ambientBrush;
	case IDC_EDIT_LIGHT_DIFFUSE_COLOR:
		pDC->SetBkColor( m_diffuseColor );
		return m_diffuseBrush;
	case IDC_EDIT_LIGHT_SPECULAR_COLOR:
		pDC->SetBkColor( m_specularColor );
		return m_specularBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


INT_PTR CAddLight::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CAddLight::IDD))) return -1;
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

void CAddLight::OnEnChangeEditConstantAttenuation()
{
	m_editBoxConstantAttenuation.GetWindowTextA( m_strConstantAttenuation );
	m_fConstantAttenuation = atof( m_strConstantAttenuation );
}

void CAddLight::OnEnChangeEditLinearAttenuation()
{
	m_editBoxLinearAttenuation.GetWindowTextA( m_strLinearAttenuation );
	m_fLinearAttenuation = atof( m_strLinearAttenuation );
}

void CAddLight::OnEnChangeEditQuadAttenuation()
{
	m_editBoxQuadAttenuation.GetWindowTextA( m_strQuadAttenuation );
	m_fQuadAttenuation = atof( m_strQuadAttenuation );
}

void CAddLight::OnEnChangeEditShininess()
{
	m_editBoxShininess.GetWindowTextA( m_strShininess );
	m_fShininess = atof( m_strShininess );
}

void CAddLight::OnEnChangeEditSpotDirectionX()
{
	m_editBoxSpotDirectionX.GetWindowTextA( m_strSpotDirectionX );
	m_fSpotDirection[0] = atof( m_strSpotDirectionX );
}

void CAddLight::OnEnChangeEditSpotDirectionY()
{
	m_editBoxSpotDirectionY.GetWindowTextA( m_strSpotDirectionY );
	m_fSpotDirection[1] = atof( m_strSpotDirectionY );
}

void CAddLight::OnEnChangeEditSpotDirectionZ()
{
	m_editBoxSpotDirectionZ.GetWindowTextA( m_strSpotDirectionZ );
	m_fSpotDirection[2] = atof( m_strSpotDirectionZ );
}

void CAddLight::OnEnChangeEditSpotExponent()
{
	m_editBoxSpotExponent.GetWindowTextA( m_strSpotExponent );
	m_fSpotExponent = atof( m_strSpotExponent );
}

void CAddLight::OnEnChangeEditSpotCutoff()
{
	m_editBoxSpotCutoff.GetWindowTextA( m_strSpotCutoff );
	m_fSpotCuttoff = atof( m_strSpotCutoff );
}

void CAddLight::OnEnChangeEditLightPosX()
{
	m_editBoxLightPosX.GetWindowTextA( m_strLightPosX );
	m_fLightPos[0] = atof( m_strLightPosX );
}

void CAddLight::OnEnChangeEditLightPosY()
{
	m_editBoxLightPosY.GetWindowTextA( m_strLightPosY );
	m_fLightPos[1] = atof( m_strLightPosY );
}

void CAddLight::OnEnChangeEditLightPosZ()
{
	m_editBoxLightPosZ.GetWindowTextA( m_strLightPosZ );
	m_fLightPos[2] = atof( m_strLightPosZ );
}



BOOL CAddLight::OnInitDialog()
{
	if( m_create )
	{
		m_ambientColor = RGB( 128, 128, 128 );
		m_diffuseColor = RGB( 128, 128, 128 );
		m_specularColor = RGB( 128, 128, 128 );
	}
	else if (m_editMode )
	{
		m_ambientColor = RGB( (CInt) (m_fAmbientColor[0] * 255), (CInt)(m_fAmbientColor[1]* 255), (CInt)(m_fAmbientColor[2] * 255));
		m_diffuseColor = RGB( (CInt)(m_fDiffuseColor[0]* 255), (CInt)(m_fDiffuseColor[1]* 255), (CInt)(m_fDiffuseColor[2]* 255) );
		m_specularColor = RGB( (CInt)(m_fSpecularColor[0]* 255), (CInt)(m_fSpecularColor[1]* 255), (CInt)(m_fSpecularColor[2]* 255) );
	}
	m_ambientBrush.CreateSolidBrush( m_ambientColor );
	m_diffuseBrush.CreateSolidBrush( m_diffuseColor );
	m_specularBrush.CreateSolidBrush( m_specularColor );

	CDialog::OnInitDialog();

	//I prefer to select point light at the beginning
	// TODO:  Add extra initialization here
	if( m_create )
	{
		m_comboLightType.InsertString( 0, "Point Light" );
		m_comboLightType.InsertString( 1, "Directional Light" );
		m_comboLightType.InsertString( 2, "Spot Light" );
		m_comboLightType.SetCurSel( 0 );
		m_comboLightType.UpdateWindow();

		m_editBoxLightPosX.SetWindowTextA( "0.0f" );
		m_editBoxLightPosY.SetWindowTextA( "0.0f" );
		m_editBoxLightPosZ.SetWindowTextA( "0.0f" );
		
		m_strLightPosX.SetString( "0.0f" );
		m_strLightPosY.SetString( "0.0f" );
		m_strLightPosZ.SetString( "0.0f" );

		m_editBoxConstantAttenuation.SetWindowTextA( "1.0f" );
		m_editBoxLinearAttenuation.SetWindowTextA( "0.0f" );
		m_editBoxQuadAttenuation.SetWindowTextA( "0.0f" );

		m_strConstantAttenuation.SetString( "0.0f" );
		m_strLinearAttenuation.SetString( "0.0f" );
		m_strQuadAttenuation.SetString( "0.0f" );

		m_editBoxShininess.SetWindowTextA( "15.0f" );

		m_strShininess.SetString( "15.0f" );

		m_editBoxSpotDirectionX.EnableWindow( 0 );
		m_editBoxSpotDirectionY.EnableWindow( 0 );
		m_editBoxSpotDirectionZ.EnableWindow( 0 );
		m_editBoxSpotExponent.EnableWindow( 0 );
		m_editBoxSpotCutoff.EnableWindow( 0 );

		m_lightType = eLIGHTTYPE_POINT;
		m_fLightPos[0] = m_fLightPos[1] = m_fLightPos[2] = 0.0f;
		m_fConstantAttenuation = 1.0f;
		m_fLinearAttenuation = 0.0f;
		m_fQuadAttenuation = 0.0f;
		m_fShininess = 15.0f;
		m_fLightPos[3] = 1.0f; //Point light

		for ( CInt i = 0; i < 4; i++ )
		{
			if( i == 3 )
			{
				m_fAmbientColor[i] = 1.0f;
				m_fDiffuseColor[i] = 1.0f;
				m_fSpecularColor[i] = 1.0f;
			}
			else
			{
				m_fAmbientColor[i] = 0.5f;
				m_fDiffuseColor[i] = 0.5f;
				m_fSpecularColor[i] = 0.5f;
			}
		}
	}
	else if (m_editMode)
	{
		m_comboLightType.InsertString( 0, "Point Light" );
		m_comboLightType.InsertString( 1, "Directional Light" );
		m_comboLightType.InsertString( 2, "Spot Light" );

		if( m_lightType == eLIGHTTYPE_POINT )
			m_comboLightType.SetCurSel( 0 );
		else if( m_lightType == eLIGHTTYPE_DIRECTIONAL )
			m_comboLightType.SetCurSel( 1 );
		else if( m_lightType == eLIGHTTYPE_SPOT )
			m_comboLightType.SetCurSel( 2 );

		m_initLightType = m_lightType;

		m_comboLightType.UpdateWindow();

		m_editBoxLightName.SetWindowTextA( m_strLightName );

		m_editBoxLightPosX.SetWindowTextA( m_strLightPosX );
		m_editBoxLightPosY.SetWindowTextA( m_strLightPosY );
		m_editBoxLightPosZ.SetWindowTextA( m_strLightPosZ );
		
		m_editBoxConstantAttenuation.SetWindowTextA( m_strConstantAttenuation );
		m_editBoxLinearAttenuation.SetWindowTextA( m_strLinearAttenuation );
		m_editBoxQuadAttenuation.SetWindowTextA( m_strQuadAttenuation );

		m_editBoxShininess.SetWindowTextA(m_strShininess );

		if( m_lightType != eLIGHTTYPE_SPOT )
		{
			m_editBoxSpotDirectionX.EnableWindow( 0 );
			m_editBoxSpotDirectionY.EnableWindow( 0 );
			m_editBoxSpotDirectionZ.EnableWindow( 0 );
			m_editBoxSpotExponent.EnableWindow( 0 );
			m_editBoxSpotCutoff.EnableWindow( 0 );
		}
		else
		{
			m_editBoxSpotDirectionX.SetWindowTextA(m_strSpotDirectionX);
			m_editBoxSpotDirectionY.SetWindowTextA(m_strSpotDirectionY);
			m_editBoxSpotDirectionZ.SetWindowTextA(m_strSpotDirectionZ);
			m_editBoxSpotExponent.SetWindowTextA(m_strSpotExponent);
			m_editBoxSpotCutoff.SetWindowTextA(m_strSpotCutoff);
		}
		if( m_lightType == eLIGHTTYPE_DIRECTIONAL )
		{
			m_editBoxConstantAttenuation.EnableWindow( 0 );
			m_editBoxLinearAttenuation.EnableWindow( 0 );
			m_editBoxQuadAttenuation.EnableWindow( 0 );
		}

		OnEnChangeEditConstantAttenuation();
		OnEnChangeEditLinearAttenuation();
		OnEnChangeEditQuadAttenuation();
		OnEnChangeEditShininess();
		OnEnChangeEditLightPosX();
		OnEnChangeEditLightPosY();
		OnEnChangeEditLightPosZ();

		if( m_lightType == eLIGHTTYPE_SPOT )
		{
			OnEnChangeEditSpotDirectionX();
			OnEnChangeEditSpotDirectionY();
			OnEnChangeEditSpotDirectionZ();
			OnEnChangeEditSpotExponent();
			OnEnChangeEditSpotCutoff();
		}
		if( m_lightType != eLIGHTTYPE_DIRECTIONAL )
			m_fLightPos[3] = 1.0f;
		else
			m_fLightPos[3] = 0.0f;

	}
	m_strLightTempName = m_strLightName;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddLight::OnCbnSelchangeCombLightType()
{
	// TODO: Add your control notification handler code here
	CInt curSel = m_comboLightType.GetCurSel();
	switch( curSel )
	{
	case eDIALOG_POINT_LIGHT:
		m_editBoxSpotDirectionX.EnableWindow( 0 );
		m_editBoxSpotDirectionY.EnableWindow( 0 );
		m_editBoxSpotDirectionZ.EnableWindow( 0 );
		m_editBoxSpotExponent.EnableWindow( 0 );
		m_editBoxSpotCutoff.EnableWindow( 0 );
		m_editBoxConstantAttenuation.EnableWindow();
		m_editBoxLinearAttenuation.EnableWindow();
		m_editBoxQuadAttenuation.EnableWindow();

		m_lightType = eLIGHTTYPE_POINT;
		m_fLightPos[3] = 1.0f; //Point light

		break;
	case eDIALOG_DIRECTIONAL_LIGHT:

		m_lightType = eLIGHTTYPE_DIRECTIONAL;
		m_editBoxSpotDirectionX.EnableWindow( 0 );
		m_editBoxSpotDirectionY.EnableWindow( 0 );
		m_editBoxSpotDirectionZ.EnableWindow( 0 );
		m_editBoxSpotExponent.EnableWindow( 0 );
		m_editBoxSpotCutoff.EnableWindow( 0 );
		m_editBoxConstantAttenuation.EnableWindow( 0 );
		m_editBoxLinearAttenuation.EnableWindow( 0 );
		m_editBoxQuadAttenuation.EnableWindow( 0 );

		m_fLightPos[3] = 0.0f; //Directional light

		break;
	case eDIALOG_SPOT_LIGHT:
		m_editBoxSpotDirectionX.EnableWindow();
		m_editBoxSpotDirectionY.EnableWindow();
		m_editBoxSpotDirectionZ.EnableWindow();
		m_editBoxSpotExponent.EnableWindow();
		m_editBoxSpotCutoff.EnableWindow();
		m_editBoxConstantAttenuation.EnableWindow();
		m_editBoxLinearAttenuation.EnableWindow();
		m_editBoxQuadAttenuation.EnableWindow();

		m_lightType = eLIGHTTYPE_SPOT;
		m_fLightPos[3] = 1.0f; //Point light
		break;
	}
}

void CAddLight::OnOK()
{
	CInt dirLightCount = 0;

	if (m_create)
	{
		if (m_lightType == eLIGHTTYPE_DIRECTIONAL)
			dirLightCount++;
	}
	else
	{
		if (m_initLightType != m_lightType && m_lightType == eLIGHTTYPE_DIRECTIONAL)
			dirLightCount++;
	}
	for (CUInt i = 0; i < g_engineLights.size(); i++)
	{
		if (g_engineLights[i]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
		{
			dirLightCount++;
		}
	}
	if (dirLightCount > NR_DIR_LIGHTS)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "Up to %d directional lights are supported", NR_DIR_LIGHTS);
		MessageBox(temp, "Vanda Engine Error", MB_OK);
		return;
	}

	CBool compare = CFalse;
	if( !m_strLightName.IsEmpty() )
	{
		compare = CTrue;
		if( m_editMode )
			if( m_strLightName == m_strLightTempName )
				compare = CFalse;
	}
	else
		compare = CFalse;

	if( compare )
	{
		for( std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end();it++ )
		{
			if( Cmp((LPCSTR)m_strLightName, (*it).c_str() ) )
			{
				MessageBox( "This name already exist. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR );
				return;
			}
		}
	}
	// TODO: Add your specialized code here and/or call the base class
	switch ( m_lightType )
	{
	case eLIGHTTYPE_POINT:
		if( m_strLightName.IsEmpty() || m_strLightPosX.IsEmpty() || m_strLightPosY.IsEmpty() || m_strLightPosZ.IsEmpty() ||
			m_strConstantAttenuation.IsEmpty() || m_strLinearAttenuation.IsEmpty() || m_strQuadAttenuation.IsEmpty() ||
			m_strShininess.IsEmpty()
			)
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		else
			CDialog::OnOK();
		break;
	case eLIGHTTYPE_DIRECTIONAL:
		if( m_strLightName.IsEmpty() || m_strLightPosX.IsEmpty() || m_strLightPosY.IsEmpty() || m_strLightPosZ.IsEmpty() ||
			m_strConstantAttenuation.IsEmpty() || m_strLinearAttenuation.IsEmpty() || m_strQuadAttenuation.IsEmpty() ||
			m_strShininess.IsEmpty()
			)
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		else
			CDialog::OnOK();
		break;
	case eLIGHTTYPE_SPOT:
		if( m_strLightName.IsEmpty() || m_strLightPosX.IsEmpty() || m_strLightPosY.IsEmpty() || m_strLightPosZ.IsEmpty() ||
			m_strConstantAttenuation.IsEmpty() || m_strLinearAttenuation.IsEmpty() || m_strQuadAttenuation.IsEmpty() ||
			m_strShininess.IsEmpty() || m_strSpotCutoff.IsEmpty() || m_strSpotExponent.IsEmpty() ||
			m_strSpotDirectionX.IsEmpty() || m_strSpotDirectionY.IsEmpty() || m_strSpotDirectionZ.IsEmpty()
			)
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		else
			CDialog::OnOK();
	}
}

void CAddLight::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CAddLight::OnEnChangeEditLightName()
{
	m_editBoxLightName.GetWindowTextA( m_strLightName );
}


void CAddLight::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

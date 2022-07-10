//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditLight.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditLight.h"


// CEditLight dialog

IMPLEMENT_DYNAMIC(CEditLight, CDialog)

CEditLight::CEditLight(CWnd* pParent /*=NULL*/)
	: CDialog(CEditLight::IDD, pParent)
{

}

CEditLight::~CEditLight()
{
}

void CEditLight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LIGHT_TOLERANCE, m_editBoxTolerance);
	DDX_Control(pDX, IDC_EDIT_LIGHT_AMBIENT_COLOR, m_editBoxAmbientColor);
	DDX_Control(pDX, IDC_EDIT_LIGHT_SPECULAR_COLOR, m_editBoxSpecularColor);
	DDX_Control(pDX, IDC_EDIT_SHININESS, m_editBoxShininess);
}


BEGIN_MESSAGE_MAP(CEditLight, CDialog)
	ON_EN_CHANGE(IDC_EDIT_LIGHT_TOLERANCE, &CEditLight::OnEnChangeEditLightTolerance)
	ON_BN_CLICKED(IDC_BUTTON_AMBIENT_LIGHT, &CEditLight::OnBnClickedButtonAmbientLight)
	ON_BN_CLICKED(IDC_BUTTON_SPECULAR_LIGHT, &CEditLight::OnBnClickedButtonSpecularLight)
	ON_EN_CHANGE(IDC_EDIT_SHININESS, &CEditLight::OnEnChangeEditShininess)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEditLight message handlers

void CEditLight::OnEnChangeEditLightTolerance()
{
	m_editBoxTolerance.GetWindowTextA( m_strTolerance );
	m_fTolerance = atof( m_strTolerance );
}

void CEditLight::OnBnClickedButtonAmbientLight()
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_ambientColor = dlg.GetColor();
		m_fAmbientColor[0] = ( CFloat )GetRValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[1] = ( CFloat )GetGValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[2] = ( CFloat )GetBValue( m_ambientColor ) / 255.f;
		m_fAmbientColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_ambientBrush.DeleteObject();
		m_ambientBrush.CreateSolidBrush( m_ambientColor );
		m_editBoxAmbientColor.RedrawWindow();
	}
}

void CEditLight::OnBnClickedButtonSpecularLight()
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_specularColor = dlg.GetColor();
		m_fSpecularColor[0] = ( CFloat )GetRValue( m_specularColor ) / 255.f;
		m_fSpecularColor[1] = ( CFloat )GetGValue( m_specularColor ) / 255.f;
		m_fSpecularColor[2] = ( CFloat )GetBValue( m_specularColor ) / 255.f;
		m_fSpecularColor[3] = 1.0f;
		m_specularBrush.DeleteObject();
		m_specularBrush.CreateSolidBrush( m_specularColor );
		m_editBoxSpecularColor.RedrawWindow();
	}
}

void CEditLight::OnEnChangeEditShininess()
{
	m_editBoxShininess.GetWindowTextA( m_strShininess );
	m_fShininess = atof( m_strShininess );
}

HBRUSH CEditLight::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch( pWnd->GetDlgCtrlID() )
	{
	case IDC_EDIT_LIGHT_AMBIENT_COLOR:
		pDC->SetBkColor( m_ambientColor );
		return m_ambientBrush;
	case IDC_EDIT_LIGHT_SPECULAR_COLOR:
		pDC->SetBkColor( m_specularColor );
		return m_specularBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CEditLight::OnInitDialog()
{
	for( CInt i = 0; i < 4; i++ )
	{
		m_fAmbientColor[i] = g_lightProperties.m_ambientColor[i];
		m_fSpecularColor[i] = g_lightProperties.m_specularColor[i];
	}
	m_ambientColor = RGB( (CInt) (m_fAmbientColor[0] * 255), (CInt)(m_fAmbientColor[1]* 255), (CInt)(m_fAmbientColor[2] * 255));
	m_specularColor = RGB( (CInt)(m_fSpecularColor[0]* 255), (CInt)(m_fSpecularColor[1]* 255), (CInt)(m_fSpecularColor[2]* 255) );

	m_ambientBrush.DeleteObject();
	m_specularBrush.DeleteObject();

	m_ambientBrush.CreateSolidBrush( m_ambientColor );
	m_specularBrush.CreateSolidBrush( m_specularColor );

	m_fShininess = g_lightProperties.m_shininess;
	m_fTolerance = g_lightProperties.m_tolerance;

	CDialog::OnInitDialog();
	m_strShininess.Format( "%.3f", m_fShininess );
	m_strTolerance.Format( "%.3f", m_fTolerance );
	m_editBoxShininess.SetWindowTextA( m_strShininess );
	m_editBoxTolerance.SetWindowTextA( m_strTolerance );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditLight::OnOK()
{
	if( m_strShininess.IsEmpty() || m_strTolerance.IsEmpty() )
	{
		MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	else
	{
		for( CInt i = 0; i < 4; i++ )
		{
			g_lightProperties.m_ambientColor[i] = m_fAmbientColor[i];
			g_lightProperties.m_specularColor[i] = m_fSpecularColor[i];
		}
		g_lightProperties.m_shininess = m_fShininess;
		g_lightProperties.m_tolerance = m_fTolerance;

		SetCOLLADALight();
		CDialog::OnOK();
	}
}

CVoid CEditLight::SetCOLLADALight()
{
	//COLLADA Lights. Not recommended
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i] );
		
		//set all the lights here
		for( CUInt i = 0; i < g_render.GetScene()->GetLightInstanceCount(); i++ )
		{
			CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(i);
			instanceLight->m_abstractLight->SetColor(CColor4f(), CFalse );
		}
	}
}
//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditFog.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "EditFog.h"


// CEditFog dialog

IMPLEMENT_DYNAMIC(CEditFog, CDialog)

CEditFog::CEditFog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditFog::IDD, pParent)
{
	for ( CInt i = 0; i < 4; i++ )
	{
		m_fColor[i] = g_fogProperties.m_fogColor[i];
	}
	m_fogBrush.DeleteObject();
	COLORREF fogColor = RGB( CInt( m_fColor[0] * 255), CInt(m_fColor[1] * 255), CInt(m_fColor[2] * 255) );
	m_fogBrush.CreateSolidBrush( fogColor );
}

CEditFog::~CEditFog()
{
}

void CEditFog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FOG_COLOR, m_editBoxFogColor);
	DDX_Control(pDX, IDC_EDIT_FOG_DENSITY, m_editBoxFogDensity);
	DDX_Control(pDX, IDC_FOG_ENABLECHECK, m_checkBoxEnableFog);
}


BEGIN_MESSAGE_MAP(CEditFog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FOG_COLOR, &CEditFog::OnBnClickedButtonFogColor)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_FOG_DENSITY, &CEditFog::OnEnChangeEditFogDensity)
END_MESSAGE_MAP()


// CEditFog message handlers

void CEditFog::OnBnClickedButtonFogColor()
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_fogColor = dlg.GetColor();
		m_fColor[0] = ( CFloat )GetRValue( m_fogColor ) / 255.f;
		m_fColor[1] = ( CFloat )GetGValue( m_fogColor ) / 255.f;
		m_fColor[2] = ( CFloat )GetBValue( m_fogColor ) / 255.f;
		m_fColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_fogBrush.DeleteObject();
		m_fogBrush.CreateSolidBrush( m_fogColor );
		m_editBoxFogColor.RedrawWindow();
	}
}

HBRUSH CEditFog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch( pWnd->GetDlgCtrlID() )
	{
	case IDC_EDIT_FOG_COLOR:
		pDC->SetBkColor( m_fogColor );
		return m_fogBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CEditFog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strFogDensity.Format( "%.3f", g_fogProperties.m_fogDensity);
	m_editBoxFogDensity.SetWindowTextA( m_strFogDensity );

	if( g_fogProperties.m_enable )
		m_checkBoxEnableFog.SetCheck( BST_CHECKED );
	else
		m_checkBoxEnableFog.SetCheck( BST_UNCHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEditFog::OnOK()
{
	if (m_strFogDensity.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		GetInformation();

		if (m_fogDensity < 0.0f)
		{
			MessageBox("Fog density must be equal or greater than 0.0", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}

		g_fogProperties.m_fogDensity = m_fogDensity;

		CInt checkState = m_checkBoxEnableFog.GetCheck();
		if( checkState == BST_CHECKED )
		{
			if( g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader())
				MessageBox( "Note: Fog does not work because you have enabled dynamic shadow debug mode. To solve this problem, please go to 'Modify -> Shadow' and select another shadow type in the dialog box that appears.", "Vanda Engine Warning", MB_OK | MB_ICONINFORMATION );
			g_fogProperties.m_enable = CTrue;
		}
		else
		{
			g_fogProperties.m_enable = CFalse;
		}

		for( CInt i = 0; i < 4; i++ )
			g_fogProperties.m_fogColor[i] = m_fColor[i];

		CFog fog;
		fog.SetColor( g_fogProperties.m_fogColor );
		fog.SetDensity( g_fogProperties.m_fogDensity );

		CDialog::OnOK();
	}

	return;
}

void CEditFog::OnEnChangeEditFogDensity()
{
	m_editBoxFogDensity.GetWindowTextA( m_strFogDensity );
	m_fogDensity = atof( m_strFogDensity );
}

CVoid CEditFog::GetInformation()
{
	OnEnChangeEditFogDensity();
}
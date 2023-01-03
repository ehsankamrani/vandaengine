//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// GeneralAmbientColor.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "GeneralAmbientColor.h"


// CGeneralAmbientColor dialog

IMPLEMENT_DYNAMIC(CGeneralAmbientColor, CDialog)

CGeneralAmbientColor::CGeneralAmbientColor(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralAmbientColor::IDD, pParent)
{

}

CGeneralAmbientColor::~CGeneralAmbientColor()
{
}

void CGeneralAmbientColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_COLOR, m_editBoxAmbientColor);
	DDX_Control(pDX, IDC_CHECK_USE_AMBIENT, m_checkBoxUseAmbientColor);
}


BEGIN_MESSAGE_MAP(CGeneralAmbientColor, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_AMBIENT, &CGeneralAmbientColor::OnBnClickedButtonAmbient)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGeneralAmbientColor message handlers

void CGeneralAmbientColor::OnBnClickedButtonAmbient()
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
		m_ambientBrush.DeleteObject();
		m_ambientBrush.CreateSolidBrush( m_ambientColor );
		m_editBoxAmbientColor.RedrawWindow();
	}
}

BOOL CGeneralAmbientColor::OnInitDialog()
{
	m_ambientColor = RGB( g_globalAmbientColor.r * 255, g_globalAmbientColor.g * 255, g_globalAmbientColor.b * 255 );
	m_ambientBrush.CreateSolidBrush( m_ambientColor );
	CDialog::OnInitDialog();

	if( g_useGlobalAmbientColor )
		m_checkBoxUseAmbientColor.SetCheck( BST_CHECKED );
	else
		m_checkBoxUseAmbientColor.SetCheck( BST_UNCHECKED );


	m_fAmbientColor[0] = g_globalAmbientColor.r;
	m_fAmbientColor[1] = g_globalAmbientColor.g;
	m_fAmbientColor[2] = g_globalAmbientColor.b;
	m_fAmbientColor[3] = g_globalAmbientColor.a;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGeneralAmbientColor::OnOK()
{
	CInt checkState;
	checkState = m_checkBoxUseAmbientColor.GetCheck();
		if( checkState == BST_CHECKED )
		{
			g_useGlobalAmbientColor = CTrue;
		}
		else
		{
			g_useGlobalAmbientColor = CFalse;
		}
		g_globalAmbientColor.r = m_fAmbientColor[0];
		g_globalAmbientColor.g = m_fAmbientColor[1];
		g_globalAmbientColor.b = m_fAmbientColor[2];
		g_globalAmbientColor.a = m_fAmbientColor[3];

	CDialog::OnOK();
}

HBRUSH CGeneralAmbientColor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch( pWnd->GetDlgCtrlID() )
	{
	case IDC_EDIT_AMBIENT_COLOR:
		pDC->SetBkColor( m_ambientColor );
		return m_ambientBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

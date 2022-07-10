//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditBloom.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditBloom.h"


// CEditBloom dialog

IMPLEMENT_DYNAMIC(CEditBloom, CDialog)

CEditBloom::CEditBloom(CWnd* pParent /*=NULL*/)
	: CDialog(CEditBloom::IDD, pParent)
{
	for ( CInt i = 0; i < 3; i++ )
	{
		m_fBloomColor[i] = g_bloomProperties.m_bloomColor[i];
	}
	m_bloomBrush.DeleteObject();
	COLORREF bloomColor = RGB( CInt( m_fBloomColor[0] * 255), CInt(m_fBloomColor[1] * 255), CInt(m_fBloomColor[2] * 255) );
	m_bloomBrush.CreateSolidBrush( bloomColor );
}

CEditBloom::~CEditBloom()
{
}

void CEditBloom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BLOOM_ENABLECHECK, m_checkBoxEnableBloom);
	DDX_Control(pDX, IDC_BLOOM_COLOR, m_editBoxBloomColor);
	DDX_Control(pDX, IDC_BLOOM_INTENSITY, m_editBoxBloomIntensity);
	DDX_Control(pDX, IDC_BUTTON_BLOOM_COLOR, m_btnBloomColor);
}


BEGIN_MESSAGE_MAP(CEditBloom, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BLOOM_COLOR, &CEditBloom::OnBnClickedButtonBloomColor)
	ON_EN_CHANGE(IDC_BLOOM_INTENSITY, &CEditBloom::OnEnChangeBloomIntensity)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CEditBloom message handlers

INT_PTR CEditBloom::DoModal()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::DoModal();
}

void CEditBloom::OnOK()
{
	if(	m_strBloomIntensity.IsEmpty() )
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	else
	{
		GetInformation();
		g_bloomProperties.m_bloomIntensity = m_bloomIntensity;

		CInt checkState;
		checkState = m_checkBoxEnableBloom.GetCheck();
		if( checkState == BST_CHECKED )
			g_bloomProperties.m_enable = CTrue;
		else
			g_bloomProperties.m_enable = CFalse;

		for( CInt i = 0; i < 3; i++ )
			g_bloomProperties.m_bloomColor[i] = m_fBloomColor[i];

		CDialog::OnOK();
	}
}

BOOL CEditBloom::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strBloomIntensity.Format( "%.3f", g_bloomProperties.m_bloomIntensity);
	m_editBoxBloomIntensity.SetWindowTextA( m_strBloomIntensity );

	if( g_bloomProperties.m_enable )
		m_checkBoxEnableBloom.SetCheck( BST_CHECKED );
	else
		m_checkBoxEnableBloom.SetCheck( BST_UNCHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditBloom::OnBnClickedButtonBloomColor()
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_bloomColor = dlg.GetColor();
		m_fBloomColor[0] = ( CFloat )GetRValue( m_bloomColor ) / 255.f;
		m_fBloomColor[1] = ( CFloat )GetGValue( m_bloomColor ) / 255.f;
		m_fBloomColor[2] = ( CFloat )GetBValue( m_bloomColor ) / 255.f;
		m_fBloomColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_bloomBrush.DeleteObject();
		m_bloomBrush.CreateSolidBrush( m_bloomColor );
		m_editBoxBloomColor.RedrawWindow();
	}
}

void CEditBloom::OnEnChangeBloomIntensity()
{
	m_editBoxBloomIntensity.GetWindowTextA( m_strBloomIntensity );
	m_bloomIntensity = atof( m_strBloomIntensity );
}

void CEditBloom::GetInformation()
{
	OnEnChangeBloomIntensity();
}

HBRUSH CEditBloom::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch( pWnd->GetDlgCtrlID() )
	{
	case IDC_BLOOM_COLOR:
		pDC->SetBkColor( m_bloomColor );
		return m_bloomBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

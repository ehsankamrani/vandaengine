//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditDOF.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditDOF.h"


// CEditDOF dialog

IMPLEMENT_DYNAMIC(CEditDOF, CDialog)

CEditDOF::CEditDOF(CWnd* pParent /*=NULL*/)
	: CDialog(CEditDOF::IDD, pParent)
{

}

CEditDOF::~CEditDOF()
{
}

void CEditDOF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FOCAL_DISTANCE, m_editBoxFocalDistance);
	DDX_Control(pDX, IDC_EDIT_FOCAL_RANGE, m_editBoxFocalRange);
	DDX_Control(pDX, IDC_DOF_ENABLECHECK, m_checkBoxEnableDOF);
	DDX_Control(pDX, De, m_checkBoxDebug);
}


BEGIN_MESSAGE_MAP(CEditDOF, CDialog)
	ON_EN_CHANGE(IDC_EDIT_FOCAL_DISTANCE, &CEditDOF::OnEnChangeEditFocalDistance)
	ON_EN_CHANGE(IDC_EDIT_FOCAL_RANGE, &CEditDOF::OnEnChangeEditFocalRange)
END_MESSAGE_MAP()


// CEditDOF message handlers

void CEditDOF::OnEnChangeEditFocalDistance()
{
	m_editBoxFocalDistance.GetWindowTextA( m_strFocalDistance );
	m_focalDistance = atof( m_strFocalDistance );
}

void CEditDOF::OnEnChangeEditFocalRange()
{
	m_editBoxFocalRange.GetWindowTextA( m_strFocalRange );
	m_focalRange = atof( m_strFocalRange );
}

CVoid CEditDOF::GetInformation()
{
	OnEnChangeEditFocalDistance();
	OnEnChangeEditFocalRange();
}

BOOL CEditDOF::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strFocalDistance.Format( "%.3f", g_dofProperties.m_dofFocalDistance);
	m_editBoxFocalDistance.SetWindowTextA( m_strFocalDistance );

	m_strFocalRange.Format( "%.3f", g_dofProperties.m_dofFocalRange);
	m_editBoxFocalRange.SetWindowTextA( m_strFocalRange );

	if( g_dofProperties.m_enable )
		m_checkBoxEnableDOF.SetCheck( BST_CHECKED );
	else
		m_checkBoxEnableDOF.SetCheck( BST_UNCHECKED );

	if( g_dofProperties.m_debug )
		m_checkBoxDebug.SetCheck( BST_CHECKED );
	else
		m_checkBoxDebug.SetCheck( BST_UNCHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditDOF::OnOK()
{
	if(	m_strFocalDistance.IsEmpty() || m_strFocalRange.IsEmpty() )
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	else
	{
		GetInformation();
		g_dofProperties.m_dofFocalDistance = m_focalDistance;
		g_dofProperties.m_dofFocalRange = m_focalRange;

		CInt checkState;
		checkState = m_checkBoxEnableDOF.GetCheck();
		if( checkState == BST_CHECKED )
			g_dofProperties.m_enable = CTrue;
		else
			g_dofProperties.m_enable = CFalse;

		checkState = m_checkBoxDebug.GetCheck();
		if( checkState == BST_CHECKED )
			g_dofProperties.m_debug = CTrue;
		else
			g_dofProperties.m_debug = CFalse;

		CDialog::OnOK();
	}
}

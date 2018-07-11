//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditOptions.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditOptions.h"


// CEditOptions dialog

IMPLEMENT_DYNAMIC(CEditOptions, CDialog)

CEditOptions::CEditOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CEditOptions::IDD, pParent)
{

}

CEditOptions::~CEditOptions()
{
}

void CEditOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OPTIONS_NUMSAMPLES, m_comboMultisample);
	DDX_Control(pDX, IDC_COMBO_OPTIONS_NUMANISOTROPY, m_comboAnisotropy);
	DDX_Control(pDX, IDC_OPTIONS_SHADERCHECK, m_checkBoxShader);
	DDX_Control(pDX, IDC_OPTIONS_MULTISAMPLECHECK, m_checkBoxMultisample);
	DDX_Control(pDX, IDC_OPTIONS_ANISOTROPYECHECK, m_checkBoxAnisotropy);
	DDX_Control(pDX, IDC_OPTIONS_FBOCHECK, m_checkBoxFBO);
	DDX_Control(pDX, IDC_OPTIONS_VBOCHECK, m_checkBoxVBO);
	DDX_Control(pDX, IDC_OPTIONS_VSYNCCHECK, m_checkBoxVSync);
	DDX_Control(pDX, IDC_OPTIONS_WATERREFLECTIONCHECK, m_checkBoxWaterReflection);
	DDX_Control(pDX, IDC_OPTIONS_SHOWWELCOMEDIALOGCHECK, m_checkBoxWelcomeDialog);
}


BEGIN_MESSAGE_MAP(CEditOptions, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTIONS_NUMANISOTROPY, &CEditOptions::OnCbnSelchangeComboOptionsNumanisotropy)
	ON_CBN_SELCHANGE(IDC_COMBO_OPTIONS_NUMSAMPLES, &CEditOptions::OnCbnSelchangeComboOptionsNumsamples)
	ON_BN_CLICKED(IDOK, &CEditOptions::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditOptions message handlers

void CEditOptions::OnCbnSelchangeComboOptionsNumanisotropy()
{
}

void CEditOptions::OnCbnSelchangeComboOptionsNumsamples()
{
}

BOOL CEditOptions::OnInitDialog()
{
	CDialog::OnInitDialog();
	//shader
	if( g_render.UsingShader() )
	{
		if( g_options.m_enableShader )
			m_checkBoxShader.SetCheck( BST_CHECKED );
		else
			m_checkBoxShader.SetCheck( BST_UNCHECKED );
	}
	else
	{
		m_checkBoxShader.EnableWindow( FALSE );
	}
	
	//multisample
	if( g_multipleView->m_multiSample )
	{
		if( g_options.m_numSamples )
			m_checkBoxMultisample.SetCheck( BST_CHECKED );
		else
			m_checkBoxMultisample.SetCheck( BST_UNCHECKED );

		m_comboMultisample.InsertString( 0, "2" );
		m_comboMultisample.InsertString( 1, "4" );
		m_comboMultisample.InsertString( 2, "8" );
		m_comboMultisample.InsertString( 3, "16" );

		CInt curSel = 0;
		switch( g_options.m_numSamples )
		{
		case 2:
			curSel = 0;
			break;
		case 4:
			curSel = 1;
			break;
		case 8:
			curSel = 2;
			break;
		case 16:
			curSel = 3;
			break;
		}
		m_comboMultisample.SetCurSel( curSel );
		m_comboMultisample.UpdateWindow();
	}
	else
	{
		m_checkBoxMultisample.EnableWindow( FALSE );
	}

	//Anisotropy
	if(  GLEW_EXT_texture_filter_anisotropic )
	{
		if( g_options.m_anisotropy )
			m_checkBoxAnisotropy.SetCheck( BST_CHECKED );
		else
			m_checkBoxAnisotropy.SetCheck( BST_UNCHECKED );

		m_comboAnisotropy.InsertString( 0, "2" );
		m_comboAnisotropy.InsertString( 1, "4" );
		m_comboAnisotropy.InsertString( 2, "8" );
		m_comboAnisotropy.InsertString( 3, "16" );

		CInt curSel = 0;
		switch( g_options.m_anisotropy )
		{
		case 2:
			curSel = 0;
			break;
		case 4:
			curSel = 1;
			break;
		case 8:
			curSel = 2;
			break;
		case 16:
			curSel = 3;
			break;
		}
		m_comboAnisotropy.SetCurSel( curSel );
		m_comboAnisotropy.UpdateWindow();
	}
	else
	{
		m_checkBoxAnisotropy.EnableWindow( FALSE );
	}

	//VSync
	if( WGLEW_EXT_swap_control )
	{
		if( g_options.m_disableVSync )
			m_checkBoxVSync.SetCheck( BST_CHECKED );
		else
			m_checkBoxVSync.SetCheck( BST_UNCHECKED );
	}
	else
		m_checkBoxVSync.EnableWindow( FALSE );

	//show welcome dialog
	if( g_options.m_showStartupDialog )
		m_checkBoxWelcomeDialog.SetCheck( BST_CHECKED );
	else
		m_checkBoxWelcomeDialog.SetCheck( BST_UNCHECKED );

	//FBO
	if( g_render.UsingFBOs() )
	{
		if( g_options.m_enableFBO )
			m_checkBoxFBO.SetCheck( BST_CHECKED );
		else
			m_checkBoxFBO.SetCheck( BST_UNCHECKED );
	}
	else
	{
		m_checkBoxFBO.EnableWindow( FALSE );
	}

	//VBO
	if( g_render.UsingVBOs() )
	{
		if( g_options.m_enableVBO )
			m_checkBoxVBO.SetCheck( BST_CHECKED );
		else
			m_checkBoxVBO.SetCheck( BST_UNCHECKED );
	}
	else
	{
		m_checkBoxVBO.EnableWindow( FALSE );
	}
	//water
	if(	g_render.m_useWaterReflection )
	{
		if( g_options.m_enableWaterReflection )
			m_checkBoxWaterReflection.SetCheck( BST_CHECKED );
		else
			m_checkBoxWaterReflection.SetCheck( BST_UNCHECKED );
	}
	else
	{
		m_checkBoxWaterReflection.EnableWindow( FALSE );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditOptions::OnBnClickedOk()
{
	//shader
	CInt checkState = m_checkBoxShader.GetCheck();
	if( checkState == BST_CHECKED )
		g_options.m_enableShader = CTrue;
	else
		g_options.m_enableShader = CFalse;

	//multisample
	if( g_multipleView->m_multiSample )
	{
		checkState = m_checkBoxMultisample.GetCheck();
		if( checkState == BST_CHECKED )
		{
			CInt curSel = m_comboMultisample.GetCurSel();
			switch( curSel )
			{
			case 0:
				g_options.m_numSamples = 2;
				break;
			case 1:
				g_options.m_numSamples = 4;
				break;
			case 2:
				g_options.m_numSamples = 8;
				break;
			case 3:
				g_options.m_numSamples = 16;
				break;
			}
		}
		else
			g_options.m_numSamples = 0;
	}

	//Anisotropy
	if( GLEW_EXT_texture_filter_anisotropic )
	{
		checkState = m_checkBoxAnisotropy.GetCheck();
		if( checkState == BST_CHECKED )
		{
			CInt curSel = m_comboAnisotropy.GetCurSel();
			switch( curSel )
			{
			case 0:
				g_options.m_anisotropy = 2;
				break;
			case 1:
				g_options.m_anisotropy = 4;
				break;
			case 2:
				g_options.m_anisotropy = 8;
				break;
			case 3:
				g_options.m_anisotropy = 16;
				break;
			}
		}
		else
			g_options.m_anisotropy = 0;
	}

	//VSync
	if( WGLEW_EXT_swap_control )
	{
		checkState = m_checkBoxVSync.GetCheck();
		if( checkState == BST_CHECKED )
		{
			g_options.m_disableVSync = CTrue;
			wglSwapIntervalEXT(0);
		}
		else
		{
			g_options.m_disableVSync = CFalse;
			wglSwapIntervalEXT(1);
		}
	}
	
	//FBO
	if( g_render.UsingFBOs() )
	{
		checkState = m_checkBoxFBO.GetCheck();
		if( checkState == BST_CHECKED )
		{
			g_options.m_enableFBO = CTrue;
		}
		else
		{
			g_options.m_enableFBO = CFalse;
		}
	}

	//VBO
	if( g_render.UsingVBOs() )
	{
		checkState = m_checkBoxVBO.GetCheck();
		if( checkState == BST_CHECKED )
		{
			g_options.m_enableVBO = CTrue;
		}
		else
		{
			g_options.m_enableVBO = CFalse;
		}
	}
	//welcome dialog
	checkState = m_checkBoxWelcomeDialog.GetCheck();
	if( checkState == BST_CHECKED )
		g_options.m_showStartupDialog = CTrue;
	else
		g_options.m_showStartupDialog = CFalse;

	//water
	if(	g_render.m_useWaterReflection )
	{
		checkState = m_checkBoxWaterReflection.GetCheck();
		if( checkState == BST_CHECKED )
			g_options.m_enableWaterReflection = CTrue;
		else
			g_options.m_enableWaterReflection = CFalse;
	}
	OnOK();
}

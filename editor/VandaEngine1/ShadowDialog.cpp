//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ShadowDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ShadowDialog.h"


// CEditShadow dialog

IMPLEMENT_DYNAMIC(CEditShadow, CDialog)

CEditShadow::CEditShadow(CWnd* pParent /*=NULL*/)
	: CDialog(CEditShadow::IDD, pParent)
{

}

CEditShadow::~CEditShadow()
{
}

void CEditShadow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHADOW_SPLITWEIGHT, m_editBoxSplitWeight);
	DDX_Control(pDX, IDC_COMBO_SHADOW_RENDERINGALGORITHM, m_comboAlgorithm);
	DDX_Control(pDX, IDC_COMBO_SHADOW_SPLITS, m_comboNumSplits);
	DDX_Control(pDX, IDC_EDIT_SHADOW_FARCLIPPLANE, m_editBoxFarClipPlane);
	DDX_Control(pDX, IDC_EDIT_SHADOW_NEARCLIPPLANE, m_editBoxNearClipPlane);
	DDX_Control(pDX, IDC_COMBO_SHADOW_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_SHADOW_ENABLECHECK, m_checkBoxEnableShadow);
	DDX_Control(pDX, IDC_EDIT_SHADOW_INTENSITY, m_editBoxIntensity);
	DDX_Control(pDX, IDC_COMBO_SHADOW_DIRECTIONAL_LIGHT, m_comboDirectionalLight);
}


BEGIN_MESSAGE_MAP(CEditShadow, CDialog)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_SPLITWEIGHT, &CEditShadow::OnEnChangeEditShadowSplitweight)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_FARCLIPPLANE, &CEditShadow::OnEnChangeEditShadowFarclipplane)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_NEARCLIPPLANE, &CEditShadow::OnEnChangeEditShadowNearclipplane)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADOW_RENDERINGALGORITHM, &CEditShadow::OnCbnSelchangeComboShadowRenderingalgorithm)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADOW_SPLITS, &CEditShadow::OnCbnSelchangeComboShadowSplits)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADOW_RESOLUTION, &CEditShadow::OnCbnSelchangeComboShadowResolution)
	ON_EN_CHANGE(IDC_EDIT_SHADOW_INTENSITY, &CEditShadow::OnEnChangeEditShadowIntensity)
	ON_CBN_SELCHANGE(IDC_COMBO_SHADOW_DIRECTIONAL_LIGHT, &CEditShadow::OnCbnSelchangeComboShadowDirectionalLight)
END_MESSAGE_MAP()


// CEditShadow message handlers

void CEditShadow::OnEnChangeEditShadowSplitweight()
{
	m_editBoxSplitWeight.GetWindowTextA( m_strSplitWeight );
	m_splitWeight = atof( m_strSplitWeight );
}

void CEditShadow::OnOK()
{
	if( g_vandaDemo )
	{
		MessageBox( "This feature is not available in RTI demo Edition", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION );
		return;
	}

	// TODO: Add your specialized code here and/or call the base class
	if(	m_strSplitWeight.IsEmpty() || m_strNearClipPlane.IsEmpty() || m_strFarClipPlane.IsEmpty())
			MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
	else
	{
		GetInformation();
		g_shadowProperties.m_shadowSplitWeight = m_splitWeight;
		g_shadowProperties.m_shadowFarClipPlane = m_farClipPlane;
		g_shadowProperties.m_shadowNearClipPlane = m_nearClipPlane;
		g_shadowProperties.m_shadowType = (CShadowType)m_shadowType;
		g_shadowProperties.m_shadowSplits = (CShadowSplits)m_shadowSplits;
		g_shadowProperties.m_shadowResolution = (CShadowResolution)m_shadowResolution;
		g_shadowProperties.m_intensity = m_intensity;

		switch( g_shadowProperties.m_shadowResolution )
		{
		case eSHADOW_1024:
			g_dynamicShadowMap->depth_size = 1024;
				break;
		case eSHADOW_2048:
			g_dynamicShadowMap->depth_size = 2048;
			break;
		case eSHADOW_4096:
			g_dynamicShadowMap->depth_size = 4096;
			break;
		default:
			break;
		}
		g_dynamicShadowMap->RegenerateDepthTex( g_dynamicShadowMap->depth_size );

		switch( g_shadowProperties.m_shadowSplits )
		{
		case eSHADOW_1_SPLIT:
			g_dynamicShadowMap->cur_num_splits = 1;
			break;
		case eSHADOW_2_SPLITS:
			g_dynamicShadowMap->cur_num_splits = 2;
			break;
		case eSHADOW_3_SPLITS:
			g_dynamicShadowMap->cur_num_splits = 3;
			break;
		case eSHADOW_4_SPLITS:
			g_dynamicShadowMap->cur_num_splits = 4;
			break;
		default:
			break;
		}

		g_dynamicShadowMap->split_weight = g_shadowProperties.m_shadowSplitWeight;
		Cpy( g_shadowProperties.m_directionalLightName,(LPCSTR)m_currentLightName);

		CInt checkState;
		checkState = m_checkBoxEnableShadow.GetCheck();
		if( checkState == BST_CHECKED && !g_vandaDemo)
			g_shadowProperties.m_enable = CTrue;
		else
			g_shadowProperties.m_enable = CFalse;

		CDialog::OnOK();
	}
}

BOOL CEditShadow::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_strSplitWeight.Format( "%f", g_shadowProperties.m_shadowSplitWeight);
	m_editBoxSplitWeight.SetWindowTextA( m_strSplitWeight );

	m_strNearClipPlane.Format( "%f", g_shadowProperties.m_shadowNearClipPlane);
	m_editBoxNearClipPlane.SetWindowTextA( m_strNearClipPlane );

	m_strFarClipPlane.Format( "%f", g_shadowProperties.m_shadowFarClipPlane);
	m_editBoxFarClipPlane.SetWindowTextA( m_strFarClipPlane );

	m_strIntensity.Format( "%f", g_shadowProperties.m_intensity);
	m_editBoxIntensity.SetWindowTextA( m_strIntensity );

	m_comboAlgorithm.InsertString( 0, "Debug" );
	m_comboAlgorithm.InsertString( 1, "Single" );
	m_comboAlgorithm.InsertString( 2, "Leak" );
	m_comboAlgorithm.InsertString( 3, "No Leak" );
	m_comboAlgorithm.InsertString( 4, "PCF" );
	m_comboAlgorithm.InsertString( 5, "PCF Trilinear" );
	m_comboAlgorithm.InsertString( 6, "PCF 4 Tap" );
	m_comboAlgorithm.InsertString( 7, "PCF 8 Tap" );
	m_comboAlgorithm.InsertString( 8, "PCF Gaussian" );
	m_comboAlgorithm.SetCurSel( g_shadowProperties.m_shadowType );
	m_comboAlgorithm.UpdateWindow();

	m_comboNumSplits.InsertString( 0, "1" );
	m_comboNumSplits.InsertString( 1, "2" );
	m_comboNumSplits.InsertString( 2, "3" );
	m_comboNumSplits.InsertString( 3, "4" );
	m_comboNumSplits.SetCurSel( g_shadowProperties.m_shadowSplits );
	m_comboNumSplits.UpdateWindow();

	m_comboResolution.InsertString( 0, "1024" );
	m_comboResolution.InsertString( 1, "2048" );
	m_comboResolution.InsertString( 2, "4096" );
	m_comboResolution.SetCurSel( g_shadowProperties.m_shadowResolution );
	m_comboResolution.UpdateWindow();

	if( g_shadowProperties.m_enable )
		m_checkBoxEnableShadow.SetCheck( BST_CHECKED );
	else
		m_checkBoxEnableShadow.SetCheck( BST_UNCHECKED );

	CInt numLights = 0;
	CInt numDirectionalLights = 0;
	for( CUInt j = 0; j < g_engineLights.size(); j++ )
	{
		if( numLights < 8 ) // 8 lights are supported
		{
			if( g_engineLights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL )
			{
				m_comboDirectionalLight.InsertString( numDirectionalLights, g_engineLights[j]->m_abstractLight->GetName() );
				if( Cmp( g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName() ) )
					m_comboDirectionalLight.SetCurSel( numDirectionalLights );
				numDirectionalLights++;
			}
		}
		++numLights;
	}
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i] );
		
		//set all the lights here
		for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
		{
			if( numLights < 8 ) // 8 lights are supported
			{
				CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
				if( instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL )
				{
					m_comboDirectionalLight.InsertString( numDirectionalLights, instanceLight->m_abstractLight->GetName() );
					if( Cmp( g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName() ) )
						m_comboDirectionalLight.SetCurSel( numDirectionalLights );
					numDirectionalLights++;
				}
			}
			++numLights;
		}
	}

	m_currentLightName = g_shadowProperties.m_directionalLightName; 
	return TRUE;  // return TRUE unless you set the focus to a control
}

CVoid CEditShadow::GetInformation()
{
	OnEnChangeEditShadowSplitweight();
	OnEnChangeEditShadowFarclipplane();
	OnEnChangeEditShadowNearclipplane();
	OnEnChangeEditShadowIntensity();
	OnCbnSelchangeComboShadowRenderingalgorithm();
	OnCbnSelchangeComboShadowSplits();
	OnCbnSelchangeComboShadowResolution();
}

void CEditShadow::OnEnChangeEditShadowFarclipplane()
{
	m_editBoxFarClipPlane.GetWindowTextA( m_strFarClipPlane );
	m_farClipPlane = atof( m_strFarClipPlane );
}

void CEditShadow::OnEnChangeEditShadowNearclipplane()
{
	m_editBoxNearClipPlane.GetWindowTextA( m_strNearClipPlane );
	m_nearClipPlane = atof( m_strNearClipPlane );
}

void CEditShadow::OnCbnSelchangeComboShadowRenderingalgorithm()
{
	m_shadowType = m_comboAlgorithm.GetCurSel();
}

void CEditShadow::OnCbnSelchangeComboShadowSplits()
{
	m_shadowSplits = m_comboNumSplits.GetCurSel();
}

void CEditShadow::OnCbnSelchangeComboShadowResolution()
{
	m_shadowResolution = m_comboResolution.GetCurSel();
}

void CEditShadow::OnEnChangeEditShadowIntensity()
{
	m_editBoxIntensity.GetWindowTextA( m_strIntensity );
	m_intensity = atof( m_strIntensity );
}

void CEditShadow::OnCbnSelchangeComboShadowDirectionalLight()
{
	m_comboDirectionalLight.GetWindowTextA(m_currentLightName);
}

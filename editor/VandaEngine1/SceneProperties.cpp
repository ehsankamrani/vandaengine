//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SceneProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "SceneProperties.h"
#include "GraphicsEngine/Animation.h"

// CSceneProperties dialog

IMPLEMENT_DYNAMIC(CSceneProperties, CDialog)

CSceneProperties::CSceneProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CSceneProperties::IDD, pParent)
{
}

CSceneProperties::~CSceneProperties()
{
}

void CSceneProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLAY_ANIMATION_ENABLECHECK, m_checkBoxPlayAnimation);
	DDX_Control(pDX, IDC_LOOP_ANIMATION_ENABLECHECK2, m_checkBoxLoopAnimation);
	DDX_Control(pDX, IDC_COMBO_ANIMATION_CLIP, m_comboAnimationClip);
	DDX_Control(pDX, IDC_ALWAYS_VISIBLE, m_checkBoxAlwaysVisible);
	DDX_Control(pDX, IDC_CASTSHADOW, m_checkBoxCastShadow);
}


BEGIN_MESSAGE_MAP(CSceneProperties, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_ANIMATION_CLIP, &CSceneProperties::OnCbnSelchangeComboAnimationClip)
END_MESSAGE_MAP()


// CSceneProperties message handlers

BOOL CSceneProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	if( g_prefabProperties.m_playAnimationAtStart )
		m_checkBoxPlayAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxPlayAnimation.SetCheck( BST_UNCHECKED );

	if (g_prefabProperties.m_loopAnimationAtStart)
		m_checkBoxLoopAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxLoopAnimation.SetCheck( BST_UNCHECKED );

	if (g_prefabProperties.m_alwaysVisible)
	{
		m_checkBoxAlwaysVisible.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkBoxAlwaysVisible.SetCheck(BST_UNCHECKED);
	}

	if (g_prefabProperties.m_castShadow)
	{
		m_checkBoxCastShadow.SetCheck(BST_CHECKED);
	}
	else
	{
		m_checkBoxCastShadow.SetCheck(BST_UNCHECKED);
	}

	for( CUInt i = 0; i < g_prefabProperties.m_names.size(); i++ )
	{
		m_comboAnimationClip.InsertString(i, g_prefabProperties.m_names[i].c_str());
	}
	m_currentAnimClip = g_prefabProperties.m_clipIndex;
	m_comboAnimationClip.SetCurSel( m_currentAnimClip );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSceneProperties::OnOK()
{
	CInt checkState;
	checkState = m_checkBoxPlayAnimation.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_playAnimationAtStart = CTrue;
	else
		g_prefabProperties.m_playAnimationAtStart = CFalse;

	checkState = m_checkBoxLoopAnimation.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_loopAnimationAtStart = CTrue;
	else
		g_prefabProperties.m_loopAnimationAtStart = CFalse;

	checkState = m_checkBoxAlwaysVisible.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_alwaysVisible = CTrue;
	else
		g_prefabProperties.m_alwaysVisible = CFalse;

	checkState = m_checkBoxCastShadow.GetCheck();
	if (checkState == BST_CHECKED)
		g_prefabProperties.m_castShadow = CTrue;
	else
		g_prefabProperties.m_castShadow = CFalse;

	for (CUInt i = 0; i < g_prefabProperties.m_names.size(); i++)
	{
		if (Cmp(g_prefabProperties.m_names[m_currentAnimClip].c_str(), g_prefabProperties.m_names[i].c_str()))
		{
			g_prefabProperties.m_clipIndex = i;
		}
	}

	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CScene* m_scene = g_scene[i];

		m_scene->m_playAnimation = g_prefabProperties.m_playAnimationAtStart;
		m_scene->m_loopAnimationAtStartup = g_prefabProperties.m_loopAnimationAtStart;
		m_scene->m_alwaysVisible = g_prefabProperties.m_alwaysVisible;
		m_scene->m_castShadow = g_prefabProperties.m_castShadow;
		m_scene->SetClipIndexForStartup(g_prefabProperties.m_clipIndex);
	}


	CDialog::OnOK();
}

void CSceneProperties::OnCbnSelchangeComboAnimationClip()
{
	m_currentAnimClip = m_comboAnimationClip.GetCurSel();
}


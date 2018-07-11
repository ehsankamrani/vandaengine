//Copyright (C) 2018 Ehsan Kamrani 
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
	m_scene = NULL;
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
}


BEGIN_MESSAGE_MAP(CSceneProperties, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_ANIMATION_CLIP, &CSceneProperties::OnCbnSelchangeComboAnimationClip)
END_MESSAGE_MAP()


// CSceneProperties message handlers

BOOL CSceneProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	if( m_scene->m_playAnimation )
		m_checkBoxPlayAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxPlayAnimation.SetCheck( BST_UNCHECKED );

	if( m_scene->m_loopAnimationAtStartup )
		m_checkBoxLoopAnimation.SetCheck( BST_CHECKED );
	else
		m_checkBoxLoopAnimation.SetCheck( BST_UNCHECKED );

	for( CInt i = 0; i < m_scene->GetNumClips(); i++ )
	{
		m_comboAnimationClip.InsertString( i, m_scene->m_animationClips[i]->GetName() );
	}
	m_currentAnimClip = m_scene->GetClipIndexForStartup();
	m_comboAnimationClip.SetCurSel( m_currentAnimClip );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSceneProperties::OnOK()
{
	CInt checkState;
	checkState = m_checkBoxPlayAnimation.GetCheck();
	if( checkState == BST_CHECKED )
		m_scene->m_playAnimation = CTrue;
	else
		m_scene->m_playAnimation = CFalse;

	checkState = m_checkBoxLoopAnimation.GetCheck();
	if( checkState == BST_CHECKED )
		m_scene->m_loopAnimationAtStartup = CTrue;
	else
		m_scene->m_loopAnimationAtStartup = CFalse;

	for( CInt i = 0; i < m_scene->GetNumClips(); i++ )
	{
		if( Cmp( m_scene->m_animationClips[m_currentAnimClip]->GetName(), m_scene->m_animationClips[i]->GetName() ) )
		{
			m_scene->SetClipIndexForStartup(i);
		}
	}

	CDialog::OnOK();
}

CVoid CSceneProperties::SetScene(CScene* scene)
{
	m_scene = scene;
}
void CSceneProperties::OnCbnSelchangeComboAnimationClip()
{
	m_currentAnimClip = m_comboAnimationClip.GetCurSel();
}

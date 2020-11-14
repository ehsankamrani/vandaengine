//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// CEditSceneOptions.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditSceneOptions.h"


// CEditSceneOptions dialog

IMPLEMENT_DYNAMIC(CEditSceneOptions, CDialog)

CEditSceneOptions::CEditSceneOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CEditSceneOptions::IDD, pParent)
{
}

CEditSceneOptions::~CEditSceneOptions()
{
}

void CEditSceneOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_MESH_PATH, m_editBoxMeshPath);
	//DDX_Control(pDX, IDC_EDIT_DIFFUSE_TEXTURES, m_editBoxDiffuseTexture);
	//DDX_Control(pDX, IDC_EDIT_EXTRA_TEXTURES, m_editBoxExtraTexture);
	//DDX_Control(pDX, IDC_EDIT_SKY_TEXTURE, m_editBoxSkyTexture);
	//DDX_Control(pDX, IDC_EDIT_WATER_TEXTURES, m_editBoxWaterTexture);
	//DDX_Control(pDX, IDC_EDIT_SOUND_PATH, m_editBoxSoundPath);
	//DDX_Control(pDX, IDC_EDIT_PHYSX_PATH, m_editBoxPhysXPath);
	DDX_Control(pDX, IDC_EDIT_NORMALMAP_NAME, m_editBoxNormalMapName);
	DDX_Control(pDX, IDC_EDIT_GLOSSMAP_NAME, m_editBoxGlossMapName);
	DDX_Control(pDX, IDC_EDIT_DIRTMAP_NAME, m_editBoxDirtMapName);
	DDX_Control(pDX, IDC_EDIT_DIFFUSE_EXCEPT, m_editBoxDiffuseExcept);
}


BEGIN_MESSAGE_MAP(CEditSceneOptions, CDialog)
	//ON_EN_CHANGE(IDC_EDIT_MESH_PATH, &CEditSceneOptions::OnEnChangeEditMeshPath)
	//ON_EN_CHANGE(IDC_EDIT_DIFFUSE_TEXTURES, &CEditSceneOptions::OnEnChangeEditDiffuseTextures)
	//ON_EN_CHANGE(IDC_EDIT_EXTRA_TEXTURES, &CEditSceneOptions::OnEnChangeEditExtraTextures)
	//ON_EN_CHANGE(IDC_EDIT_SKY_TEXTURE, &CEditSceneOptions::OnEnChangeEditSkyTexture)
	//ON_EN_CHANGE(IDC_EDIT_WATER_TEXTURES, &CEditSceneOptions::OnEnChangeEditWaterTextures)
	//ON_EN_CHANGE(IDC_EDIT_SOUND_PATH, &CEditSceneOptions::OnEnChangeEditSoundPath)
	//ON_EN_CHANGE(IDC_EDIT_PHYSX_PATH, &CEditSceneOptions::OnEnChangeEditPhysxPath)
	ON_BN_CLICKED(IDOK, &CEditSceneOptions::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_NORMALMAP_NAME, &CEditSceneOptions::OnEnChangeEditNormalmapName)
	ON_EN_CHANGE(IDC_EDIT_GLOSSMAP_NAME, &CEditSceneOptions::OnEnChangeEditGlossmapName)
	ON_EN_CHANGE(IDC_EDIT_DIRTMAP_NAME, &CEditSceneOptions::OnEnChangeEditDirtmapName)
	ON_EN_CHANGE(IDC_EDIT_DIFFUSE_EXCEPT, &CEditSceneOptions::OnEnChangeEditDiffuseExcept)
END_MESSAGE_MAP()

//void CEditSceneOptions::OnEnChangeEditMeshPath()
//{
//	m_editBoxMeshPath.GetWindowTextA( m_strMeshPath );
//}

//void CEditSceneOptions::OnEnChangeEditDiffuseTextures()
//{
//	m_editBoxDiffuseTexture.GetWindowTextA( m_strDiffuseTexture );
//}
//
//void CEditSceneOptions::OnEnChangeEditExtraTextures()
//{
//	m_editBoxExtraTexture.GetWindowTextA( m_strExtraTexture );
//}
//
//void CEditSceneOptions::OnEnChangeEditSkyTexture()
//{
//	m_editBoxSkyTexture.GetWindowTextA( m_strSkyTexture );
//}
//
//void CEditSceneOptions::OnEnChangeEditWaterTextures()
//{
//	m_editBoxWaterTexture.GetWindowTextA( m_strWaterTexture );
//}
//
//void CEditSceneOptions::OnEnChangeEditSoundPath()
//{
//	m_editBoxSoundPath.GetWindowTextA( m_strSoundPath );
//}

BOOL CEditSceneOptions::OnInitDialog()
{
	//m_strMeshPath = g_pathProperties.m_meshPath;
	//m_strDiffuseTexture = g_pathProperties.m_meshDiffuseTexturePath;
	//m_strExtraTexture = g_pathProperties.m_meshOtherTexturesPath;
	//m_strSkyTexture = g_pathProperties.m_skyPath;
	//m_strWaterTexture = g_pathProperties.m_waterPath;
	//m_strSoundPath = g_pathProperties.m_soundPath;
	//m_strPhysXPath = g_pathProperties.m_physXPath;

	m_strDiffuseNameExcept = g_extraTexturesNamingConventions.m_diffuseNameExcept;
	m_strNormalMapName = g_extraTexturesNamingConventions.m_normalMapName;
	m_strGlossMapName = g_extraTexturesNamingConventions.m_glossMapName;
	m_strDirtMapName = g_extraTexturesNamingConventions.m_dirtMapName;

	CDialog::OnInitDialog();
	//m_editBoxMeshPath.SetWindowTextA( m_strMeshPath ) ;
	//m_editBoxDiffuseTexture.SetWindowTextA( m_strDiffuseTexture ) ;
	//m_editBoxExtraTexture.SetWindowTextA( m_strExtraTexture ) ;
	//m_editBoxSkyTexture.SetWindowTextA( m_strSkyTexture ) ;
	//m_editBoxWaterTexture.SetWindowTextA( m_strWaterTexture ) ;
	//m_editBoxSoundPath.SetWindowTextA( m_strSoundPath ) ;
	//m_editBoxPhysXPath.SetWindowTextA( m_strPhysXPath );

	m_editBoxDiffuseExcept.SetWindowTextA( m_strDiffuseNameExcept );
	m_editBoxNormalMapName.SetWindowTextA(m_strNormalMapName);
	m_editBoxGlossMapName.SetWindowTextA(m_strGlossMapName);
	m_editBoxDirtMapName.SetWindowTextA(m_strDirtMapName);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//void CEditSceneOptions::OnEnChangeEditPhysxPath()
//{
//	m_editBoxPhysXPath.GetWindowTextA( m_strPhysXPath );
//}

void CEditSceneOptions::OnOK()
{
	//Cpy( g_pathProperties.m_meshPath, (LPCSTR)m_strMeshPath );
	//Cpy( g_pathProperties.m_meshDiffuseTexturePath, (LPCSTR)m_strDiffuseTexture );
	//Cpy( g_pathProperties.m_meshOtherTexturesPath, (LPCSTR)m_strExtraTexture );
	//Cpy( g_pathProperties.m_skyPath, (LPCSTR)m_strSkyTexture );
	//Cpy( g_pathProperties.m_waterPath, (LPCSTR)m_strWaterTexture );
	//Cpy( g_pathProperties.m_soundPath, (LPCSTR)m_strSoundPath );
	//Cpy( g_pathProperties.m_physXPath, (LPCSTR)m_strPhysXPath );

	Cpy( g_extraTexturesNamingConventions.m_diffuseNameExcept, (LPCSTR) m_strDiffuseNameExcept );
	Cpy( g_extraTexturesNamingConventions.m_glossMapName, (LPCSTR) m_strGlossMapName );
	Cpy( g_extraTexturesNamingConventions.m_normalMapName, (LPCSTR) m_strNormalMapName );
	Cpy( g_extraTexturesNamingConventions.m_dirtMapName, (LPCSTR) m_strDirtMapName );

	//AddSlash( g_pathProperties.m_meshPath );
	//AddSlash( g_pathProperties.m_meshDiffuseTexturePath );
	//AddSlash( g_pathProperties.m_meshOtherTexturesPath );
	//AddSlash( g_pathProperties.m_skyPath );
	//AddSlash( g_pathProperties.m_waterPath );
	//AddSlash( g_pathProperties.m_soundPath );
	//AddSlash( g_pathProperties.m_physXPath );

	//if( g_skyDome )
	//{
	//	CChar* tempSkyPath = GetAfterPath( g_skyDome->GetPath() );
	//	CChar skyPath[MAX_NAME_SIZE];
	//	sprintf( skyPath, "%s%s", g_pathProperties.m_skyPath, tempSkyPath );
	//	g_skyDome->SetPath( skyPath  );
	//}

	CDialog::OnOK();
}

void CEditSceneOptions::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CEditSceneOptions::AddSlash(CChar* string)
{
	CInt len;
	CChar* pos; //position of last char

	len=(CInt)strlen(string); // save length of string
	pos= string+len-1; // make pos point to last char of string
	if( !Cmp2( pos, "/" ) )
	{
		strcat( string, "/" );
	}
}

void CEditSceneOptions::OnEnChangeEditNormalmapName()
{
	m_editBoxNormalMapName.GetWindowTextA(m_strNormalMapName);
}

void CEditSceneOptions::OnEnChangeEditGlossmapName()
{
	m_editBoxGlossMapName.GetWindowTextA(m_strGlossMapName);
}

void CEditSceneOptions::OnEnChangeEditDirtmapName()
{
	m_editBoxDirtMapName.GetWindowTextA(m_strDirtMapName);
}

void CEditSceneOptions::OnEnChangeEditDiffuseExcept()
{
	m_editBoxDiffuseExcept.GetWindowTextA(m_strDiffuseNameExcept);
}

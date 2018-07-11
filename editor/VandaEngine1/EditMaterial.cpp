//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditMaterial.h"
#include  "AFXPRIV.H"
#include <string>
#include <set>
#include <map>
#include <vector>
using namespace std;
// CEditMaterial dialog

IMPLEMENT_DYNAMIC(CEditMaterial, CDialog)

CEditMaterial::CEditMaterial(CWnd* pParent /*=NULL*/)
	: CDialog(CEditMaterial::IDD, pParent)
{
	m_firstBias = m_firstScale = CTrue;
}

CEditMaterial::~CEditMaterial()
{
}

void CEditMaterial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NORMALMAP, m_editBoxNormalMap);
	DDX_Control(pDX, IDC_BTN_NORMALMAP, m_btnNormalMap);
	DDX_Control(pDX, IDC_BTN_DELETE_NORMALMAP, m_btnRemoveNormalMap);
	DDX_Control(pDX, IDC_EDIT_GLOSSMAP, m_editBoxGlossMap);
	DDX_Control(pDX, IDC_EDIT_DIRTMAP, m_editBoxDirtMap);
	DDX_Control(pDX, IDC_EDIT_DIFFUSE, m_editBoxDiffuse);
	DDX_Control(pDX, IDC_BTN_GLOSSMAP, m_btnGlossMap);
	DDX_Control(pDX, IDC_BTN_DIRTMAP, m_btnDirtMap);
	DDX_Control(pDX, IDC_BTN_DIFFUSE, m_btnDiffuse);
	DDX_Control(pDX, IDC_BTN_DELETE_GLOSSMAP, m_btnRemoveGlossMap);
	DDX_Control(pDX, IDC_BTN_DELETE_DIRTMAP, m_btnRemoveDirtMap);
	DDX_Control(pDX, IDC_BTN_DELETE_DIFFUSE, m_btnRemoveDiffuse);
	DDX_Control(pDX, IDC_EDIT_NORMALMAP_SCALE, m_editBoxScale);
	DDX_Control(pDX, IDC_EDIT_NORMALMAP_BIAS, m_editBoxBias);
}


BEGIN_MESSAGE_MAP(CEditMaterial, CDialog)
	ON_BN_CLICKED(IDC_BTN_NORMALMAP, &CEditMaterial::OnBnClickedBtnNormalmap)
	ON_BN_CLICKED(IDC_BTN_GLOSSMAP, &CEditMaterial::OnBnClickedBtnGlossmap)
	ON_BN_CLICKED(IDC_BTN_DIRTMAP, &CEditMaterial::OnBnClickedBtnDirtmap)
	ON_BN_CLICKED(IDC_BTN_DIFFUSE, &CEditMaterial::OnBnClickedBtnDiffuse)
	ON_BN_CLICKED(IDC_BTN_DELETE_NORMALMAP, &CEditMaterial::OnBnClickedBtnDeleteNormalmap)
	ON_BN_CLICKED(IDC_BTN_DELETE_GLOSSMAP, &CEditMaterial::OnBnClickedBtnDeleteGlossmap)
	ON_BN_CLICKED(IDC_BTN_DELETE_DIRTMAP, &CEditMaterial::OnBnClickedBtnDeleteDirtmap)
	ON_BN_CLICKED(IDC_BTN_DELETE_DIFFUSE, &CEditMaterial::OnBnClickedBtnDeleteDiffuse)
	ON_EN_CHANGE(IDC_EDIT_NORMALMAP_BIAS, &CEditMaterial::OnEnChangeEditNormalmapBias)
	ON_EN_CHANGE(IDC_EDIT_NORMALMAP_SCALE, &CEditMaterial::OnEnChangeEditNormalmapScale)
END_MESSAGE_MAP()

CVoid CEditMaterial::SetEditBoxBias( CFloat bias )
{
	m_parallaxMapBias = bias;
	m_strParallaxMapBias.Format( "%f", m_parallaxMapBias);
}

CVoid CEditMaterial::SetEditBoxScale( CFloat scale )
{
	m_parallaxMapScale = scale;
	m_strParallaxMapScale.Format( "%f", m_parallaxMapScale);
}

CVoid CEditMaterial::SetEditBoxNormalMapName( CString string )
{
	m_strNormalMapName = string;
}

CVoid CEditMaterial::SetEditBoxGlossMapName( CString string )
{
	m_strGlossMapName = string;
}

CVoid CEditMaterial::SetEditBoxDirtMapName( CString string )
{
	m_strDirtMapName = string;
}

CVoid CEditMaterial::SetEditBoxDiffuseName( CString string )
{
	m_strDiffuseName = string;
}
//Button States
CVoid CEditMaterial::SetNormalBtnState( CBool state )
{
	m_normalBtnState = state;
}

CVoid CEditMaterial::SetGlossBtnState( CBool state )
{
	m_glossBtnState = state;
}

CVoid CEditMaterial::SetDirtBtnState( CBool state )
{
	m_dirtBtnState = state;
}

CVoid CEditMaterial::SetDiffuseBtnState( CBool state )
{
	m_diffuseBtnState = state;
}

//Remove Button States
CVoid CEditMaterial::SetRemoveNormalBtnState( CBool state )
{
	m_removeNormalBtnState = state;
}

CVoid CEditMaterial::SetRemoveGlossBtnState( CBool state )
{
	m_removeGlossBtnState = state;
}

CVoid CEditMaterial::SetRemoveDirtBtnState( CBool state )
{
	m_removeDirtBtnState = state;
}

CVoid CEditMaterial::SetRemoveDiffuseBtnState( CBool state )
{
	m_removeDiffuseBtnState = state;
}

// CEditMaterial message handlers
void CEditMaterial::OnBnClickedBtnNormalmap()
{
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		CString str_prevNormatMap = m_strNormalMapName;

		g_updateTextureViaEditor = CTrue;
		m_strNormalMapName = (CString)dlgOpen.GetPathName();
		m_strPureNormalMapName = dlgOpen.GetFileTitle();
		CBool error = CFalse;
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			if( !g_scene[i]->SetNormalMap( m_strNormalMapName/*m_strPureNormalMapName*/, m_parallaxMapBias, m_parallaxMapScale, CFalse, CFalse ) )
				error = CTrue;
		}
		if( !error )
		{
			PrintInfo( "\nNew normal map added successfully" );
			m_editBoxNormalMap.SetWindowText( m_strPureNormalMapName + ".dds" );
			m_btnRemoveNormalMap.EnableWindow( TRUE );
			m_editBoxBias.EnableWindow( TRUE );
			m_editBoxScale.EnableWindow( TRUE );
		}
		else
		{
			PrintInfo( "\nError! An error occured while creating the normal map", COLOR_RED );
			numErrors += 1;
		}
		RemoveUnsharedImage(str_prevNormatMap, eNORMAL_MAP);

		g_updateTextureViaEditor = CFalse;

		g_multipleView->SetElapsedTimeFromBeginning();
		g_multipleView->RenderWindow();
	}
}

void CEditMaterial::OnBnClickedBtnGlossmap()
{
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		CString str_prevGlossMap = m_strGlossMapName;

		g_updateTextureViaEditor = CTrue;
		m_strGlossMapName = (CString)dlgOpen.GetPathName();
		m_strPureGlossMapName = dlgOpen.GetFileTitle();
		CBool error = CFalse;
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			if( !g_scene[i]->SetGlossMap( m_strGlossMapName/*m_strPureGlossMapName*/ ) )
				error = CTrue;
		}
		if( !error )
		{
			PrintInfo( "\nNew gloss map added successfully" );
			m_editBoxGlossMap.SetWindowText( m_strPureGlossMapName + ".dds" );
			m_btnRemoveGlossMap.EnableWindow( TRUE );
		}
		else
		{
			PrintInfo( "\nError! An error occured while creating the gloss map", COLOR_RED );
			numErrors += 1;
		}
		g_updateTextureViaEditor = CFalse;
		RemoveUnsharedImage(str_prevGlossMap, eGLOSS_MAP);

		g_multipleView->SetElapsedTimeFromBeginning();
		g_multipleView->RenderWindow();
	}
}

void CEditMaterial::OnBnClickedBtnDirtmap()
{
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		CString str_prevDirtMap = m_strDirtMapName;

		g_updateTextureViaEditor = CTrue;
		m_strDirtMapName = (CString)dlgOpen.GetPathName();
		m_strPureDirtMapName = dlgOpen.GetFileTitle();
		CBool error = CFalse;
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			if( !g_scene[i]->SetDirtMap( m_strDirtMapName/*m_strPureDirtMapName*/ ) )
			error = CTrue;
		}
		if( !error )
		{
			PrintInfo( "\nNew Dirt map added successfully" );
			m_editBoxDirtMap.SetWindowText( m_strPureDirtMapName + ".dds" );
			m_btnRemoveDirtMap.EnableWindow( TRUE );
		}

		else
		{
			PrintInfo( "\nError! An error occured while creating the dirt map", COLOR_RED );
			numErrors += 1;
		}
		g_updateTextureViaEditor = CFalse;
		RemoveUnsharedImage(str_prevDirtMap, eDIRT_MAP);

		g_multipleView->SetElapsedTimeFromBeginning();
		g_multipleView->RenderWindow();
	}
}

void CEditMaterial::OnBnClickedBtnDiffuse()
{
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if( IDOK == dlgOpen.DoModal() )
	{
		CString str_prevDiffuse = m_strDiffuseName;

		g_updateTextureViaEditor = CTrue;
		m_strDiffuseName = (CString)dlgOpen.GetPathName();
		m_strPureDiffuseName = dlgOpen.GetFileTitle();


		CBool error = CFalse;
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			if( !g_scene[i]->SetDiffuse( m_strDiffuseName/*m_strPureDiffuseName*/ ) )
				error = CTrue;
		}
		if( !error )
		{
			PrintInfo( "\nNew diffuse texture added successfully" );
			m_editBoxDiffuse.SetWindowText( m_strPureDiffuseName + ".dds" );
			m_btnRemoveDiffuse.EnableWindow( TRUE );
		}
		else
		{
			PrintInfo( "\nError! An error occured while creating the diffuse texture", COLOR_RED );
			numErrors += 1;
		}
		g_updateTextureViaEditor = CFalse;
		RemoveUnsharedImage(str_prevDiffuse, eDIFFUSE);

		g_multipleView->SetElapsedTimeFromBeginning();
		g_multipleView->RenderWindow();
	}
}

void CEditMaterial::OnBnClickedBtnDeleteNormalmap()
{
	if( MessageBox( "Remove current normal map?", "Warning", MB_YESNO ) == IDYES )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->RemoveNormalMap();
		RemoveUnsharedImage(m_strNormalMapName, eNORMAL_MAP);

		m_editBoxNormalMap.SetWindowTextA( NULL );
		m_btnRemoveNormalMap.EnableWindow( FALSE );
		m_editBoxBias.EnableWindow( FALSE );
		m_editBoxScale.EnableWindow( FALSE );
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
}

void CEditMaterial::OnBnClickedBtnDeleteGlossmap()
{
	if( MessageBox( "Remove current gloss map?", "Warning", MB_YESNO ) == IDYES )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->RemoveGlossMap();
		RemoveUnsharedImage(m_strGlossMapName, eGLOSS_MAP);

		m_editBoxGlossMap.SetWindowTextA( NULL );
		m_btnRemoveGlossMap.EnableWindow( FALSE );
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
}

void CEditMaterial::OnBnClickedBtnDeleteDirtmap()
{
	if( MessageBox( "Remove current dirt map?", "Warning", MB_YESNO ) == IDYES )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->RemoveDirtMap();
		RemoveUnsharedImage(m_strDirtMapName, eDIRT_MAP);

		m_editBoxDirtMap.SetWindowTextA( NULL );
		m_btnRemoveDirtMap.EnableWindow( FALSE );
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
}

void CEditMaterial::OnBnClickedBtnDeleteDiffuse()
{
	if( MessageBox( "Remove current diffuse map?", "Warning", MB_YESNO ) == IDYES )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->RemoveDiffuse();
		RemoveUnsharedImage(m_strDiffuseName, eDIFFUSE);

		m_editBoxDiffuse.SetWindowTextA( NULL );
		m_btnRemoveDiffuse.EnableWindow( FALSE );
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
}

BOOL CEditMaterial::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editBoxNormalMap.SetWindowTextA(m_strNormalMapName);
	m_editBoxGlossMap.SetWindowTextA(m_strGlossMapName);
	m_editBoxDirtMap.SetWindowTextA(m_strDirtMapName);
	m_editBoxDiffuse.SetWindowTextA(m_strDiffuseName);
	m_editBoxScale.SetWindowTextA( m_strParallaxMapScale );
	m_editBoxBias.SetWindowTextA( m_strParallaxMapBias );

	m_btnNormalMap.EnableWindow(m_normalBtnState);
	m_btnGlossMap.EnableWindow(m_glossBtnState);
	m_btnDirtMap.EnableWindow(m_dirtBtnState);
	m_btnDiffuse.EnableWindow(m_diffuseBtnState);
	m_btnRemoveNormalMap.EnableWindow(m_removeNormalBtnState);
	m_btnRemoveGlossMap.EnableWindow(m_removeGlossBtnState);
	m_btnRemoveDirtMap.EnableWindow(m_removeDirtBtnState);
	m_btnRemoveDiffuse.EnableWindow(m_removeDiffuseBtnState);
	m_editBoxScale.EnableWindow( m_removeNormalBtnState );
	m_editBoxBias.EnableWindow( m_removeNormalBtnState );

	return TRUE;
}

void CEditMaterial::OnOK()
{
	if( !Cmp((LPCTSTR)m_strNormalMapName, "\n" ) && (m_strParallaxMapBias.IsEmpty() || m_strParallaxMapScale.IsEmpty() ))
	{
		MessageBox( "Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	CDialog::OnOK();
}

INT_PTR CEditMaterial::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CEditMaterial::IDD))) return -1;
	// set the font, for example "Arial", 10 pts.
	dlt.SetFont("Arial", 8);
	// get pointer to the modified dialog template
	LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	// let MFC know that you are using your own template
	m_lpszTemplateName = NULL;
	InitModalIndirect(pdata);
	// display dialog box
	nResult = CDialog::DoModal();
	// unlock memory object
	GlobalUnlock(dlt.m_hTemplate);
	return nResult;
}
void CEditMaterial::OnEnChangeEditNormalmapBias()
{
	m_editBoxBias.GetWindowTextA( m_strParallaxMapBias );
	m_parallaxMapBias = atof( m_strParallaxMapBias );
	if(!m_firstBias )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->SetNormalMap( "", m_parallaxMapBias, m_parallaxMapScale, CTrue, CFalse );
	}
	m_firstBias = CFalse;
}

void CEditMaterial::OnEnChangeEditNormalmapScale()
{
	m_editBoxScale.GetWindowTextA( m_strParallaxMapScale );
	m_parallaxMapScale = atof( m_strParallaxMapScale );
	if( !m_firstScale )
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
			g_scene[i]->SetNormalMap( "", m_parallaxMapBias, m_parallaxMapScale, CFalse, CTrue );
	}
	m_firstScale = CFalse;
}

void CEditMaterial::RemoveUnsharedImage( CString string, CTextureMapType type )
{
	CChar imageNameTemp[MAX_NAME_SIZE];
	Cpy( imageNameTemp, string.GetBuffer(string.GetLength()));
	GetWithoutDot( imageNameTemp );
	CChar* imageName = GetAfterPath( imageNameTemp );
	string.ReleaseBuffer();
	std::vector <std::string> m_strImageNames;
	CInt maxImages = 0;
	std::vector <std::map <std::string, size_t>> occurences;
	if( Cmp( imageName, "*Different Textures*" ) )
	{
		if( g_selectedName != -1 )
		{
			CBool foundTarget = CFalse;
			for( CUInt sceneIndex  = 0; sceneIndex < g_scene.size(); sceneIndex++ )
			{
				for( CUInt i = 0; i < g_scene[sceneIndex]->m_instanceGeometries.size(); i++ )
				{
					CBool selected = CFalse;
					if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups.size(); j++ )
						{
							switch (type)
							{
							case eDIFFUSE:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasDiffuse )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strDiffuse );
									Append( temp, ".dds" );
									m_strImageNames.push_back( temp );
								}
								break;
							case eNORMAL_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasNormalMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strNormalMap );
									Append( temp, ".dds" );
									m_strImageNames.push_back( temp );
								}
								break;
							case eDIRT_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasDirtMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strDirtMap );
									Append( temp, ".dds" );
									m_strImageNames.push_back( temp );
								}
								break;
							case eGLOSS_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasGlossMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strGlossMap );
									Append( temp, ".dds" );
									m_strImageNames.push_back( temp );
								}
								break;
							}
						}
					}
					if( foundTarget )
						break;
				}
				if( foundTarget )
					break;
			}
			//fill map with data
			for( CUInt i = 0; i < m_strImageNames.size(); i++ )
			{
				CBool foundTarget = CFalse;
				for( CUInt j = 0; j < occurences.size(); j++ )
				{
					if( occurences[j].begin()->first == m_strImageNames[i] )
					{
						foundTarget = CTrue;
						occurences[j].begin()->second +=1;
					}
				}
				if( !foundTarget )
				{
					std::map<std::string, size_t> temp;
					temp[m_strImageNames[i]] = 1;
					occurences.push_back( temp );
				}
			}
		}
	}
	else
	{
		Append( imageName, ".dds" );
		m_strImageNames.push_back(imageName);

		if( g_menu.m_geometryBasedSelection )
		{
			CBool foundTarget = CFalse;
			for( CUInt sceneIndex = 0; sceneIndex < g_scene.size(); sceneIndex++ )
			{
				for( CUInt i = 0; i < g_scene[sceneIndex]->m_instanceGeometries.size(); i++ )
				{
					CGeometry* m_geo = g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry;
					CBool selected = CFalse;
					if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_nameIndex == g_selectedName )
					{
						selected = CTrue;
						foundTarget = CTrue;
					}

					if( selected )
					{
						for( CUInt j = 0; j < m_geo->m_groups.size(); j++ )
						{
							switch (type)
							{
							case eDIFFUSE:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasDiffuse )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strDiffuse );
									Append( temp, ".dds" );
									if( Cmp( GetAfterPath(temp), imageName))
										maxImages++;
								}
								break;
							case eDIRT_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasDirtMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strDirtMap );
									Append( temp, ".dds" );
									if( Cmp( GetAfterPath(temp), imageName))
										maxImages++;
								}
								break;
							case eGLOSS_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasGlossMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strGlossMap );
									Append( temp, ".dds" );
									if( Cmp( GetAfterPath(temp), imageName))
										maxImages++;
								}
								break;
							case eNORMAL_MAP:
								if( g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_hasNormalMap )
								{
									CChar temp[MAX_NAME_SIZE];
									Cpy( temp, g_scene[sceneIndex]->m_instanceGeometries[i]->m_abstractGeometry->m_groups[j]->m_strNormalMap );
									Append( temp, ".dds" );
									if( Cmp( GetAfterPath(temp), imageName))
										maxImages++;
								}
								break;
							}//switch
						}//for all of the groups
					}//if selected
					if( foundTarget )
						break;
				}
				if( foundTarget )
					break;
			}
		}
		else
		{
			maxImages = 1;
		}
		std::map<std::string, size_t> temp;
		temp[m_strImageNames[0]] = maxImages;
		occurences.push_back( temp );
	}
	for( CUInt imgIndex = 0; imgIndex < occurences.size(); imgIndex++ )
	{
		CChar imageName[MAX_NAME_SIZE];
		Cpy( imageName, occurences[imgIndex].begin()->first.c_str() );
		CInt maxImages =  (CInt)occurences[imgIndex].begin()->second;
		int numImages = 0;
		CBool foundTarget = CFalse;
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
			{
				CGeometry* m_geo = g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry;
				for( CUInt k = 0; k < m_geo->m_groups.size(); k++ )
				{
					if( m_geo->m_groups[k]->m_hasDiffuse && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_diffuseImg->m_fileName) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasNormalMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_normalMapImg->m_fileName) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasGlossMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_glossMapImg->m_fileName) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasDirtMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_dirtMapImg->m_fileName) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
				}
				if( foundTarget )
					break;
			}
			if( foundTarget )
				break;
		}
		if( !foundTarget )
		{
			for( CUInt p = 0; p < g_images.size(); p++ )
			{
				if( Cmp( GetAfterPath(g_images[p]->m_fileName), imageName ) )
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf( temp, "\n%s%s%s", "Image '", imageName, "' removed from memory" );
					PrintInfo( temp, COLOR_YELLOW );
					CDelete( *(g_images.begin() + p) );
					g_images.erase( g_images.begin() + p );
					break;
				}
			}
		}
	}
}


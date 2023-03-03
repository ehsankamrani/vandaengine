//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
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
	m_updateAmbient = m_updateDiffuse = m_updateSpecular = m_updateEmission = CFalse;
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
	DDX_Control(pDX, IDC_EDIT_SPECULAR_COLOR, m_editBoxSpecularColor);
	DDX_Control(pDX, IDC_EDIT_DIFFUSE_COLOR, m_editBoxDiffuseColor);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_COLOR, m_editBoxAmbientColor);
	DDX_Control(pDX, IDC_EDIT_SHININESS, m_editBoxShininess);
	DDX_Control(pDX, IDC_EDIT_TRANSPARENCY, m_editBoxTransparency);
	DDX_Control(pDX, IDC_EDIT_EMISSION_COLOR, m_editBoxEmissionColor);
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
	ON_BN_CLICKED(IDC_BUTTON_AMBIENT, &CEditMaterial::OnBnClickedButtonAmbient)
	ON_BN_CLICKED(IDC_BUTTON_DIFFUSE, &CEditMaterial::OnBnClickedButtonDiffuse)
	ON_BN_CLICKED(IDC_BUTTON_SPECULAR, &CEditMaterial::OnBnClickedButtonSpecular)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_SHININESS, &CEditMaterial::OnEnChangeEditShininess)
	ON_EN_CHANGE(IDC_EDIT_TRANSPARENCY, &CEditMaterial::OnEnChangeEditTransparency)
	ON_BN_CLICKED(IDC_BUTTON_EMISSION, &CEditMaterial::OnBnClickedButtonEmission)
END_MESSAGE_MAP()

CVoid CEditMaterial::SetEditBoxBias( CFloat bias )
{
	m_parallaxMapBias = bias;
	m_strParallaxMapBias.Format( "%.3f", m_parallaxMapBias);
}

CVoid CEditMaterial::SetEditBoxScale( CFloat scale )
{
	m_parallaxMapScale = scale;
	m_strParallaxMapScale.Format( "%.3f", m_parallaxMapScale);
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
		if (!m_strNormalMapName.IsEmpty())
		{
			RemoveUnsharedImage(m_strNormalMapName, eNORMAL_MAP);
			for (CUInt i = 0; i < g_scene.size(); i++)
				g_scene[i]->RemoveNormalMap();
		}
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
		if (!m_strGlossMapName.IsEmpty())
		{
			RemoveUnsharedImage(m_strGlossMapName, eGLOSS_MAP);
			for (CUInt i = 0; i < g_scene.size(); i++)
				g_scene[i]->RemoveGlossMap();
		}
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
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
			{
				CGeometry* m_geo = g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry;
				if (g_menu.m_geometryBasedSelection)
				{
					if (g_scene[i]->m_instanceGeometries[j]->m_nameIndex == g_selectedName)
					{
						if (!m_geo->m_texCoords[1])
						{
							MessageBoxA("In order to set dirt map, you must export UV set 2 for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR);
							return;
						}
					}
				}
				else //Material Based Selection
				{
					for (CUInt k = 0; k < m_geo->m_groups.size(); k++)
					{
						if (m_geo->m_groups[k]->m_nameIndex == g_selectedName)
						{
							if (!m_geo->m_texCoords[1])
							{
								MessageBoxA("In order to set dirt map, you must export UV set 2 for COLLADA model", "VandaEngine Error", MB_OK | MB_ICONERROR);
								return;
							}
						}

					}
				} // else
			}
		}

		if (m_strDirtMapName.IsEmpty())
		{
			RemoveUnsharedImage(m_strDirtMapName, eDIRT_MAP);
			for (CUInt i = 0; i < g_scene.size(); i++)
				g_scene[i]->RemoveDirtMap();
		}
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
		if (!m_strDiffuseName.IsEmpty())
		{
			RemoveUnsharedImage(m_strDiffuseName, eDIFFUSE);
			for (CUInt i = 0; i < g_scene.size(); i++)
				g_scene[i]->RemoveDiffuse();
		}

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

		g_multipleView->SetElapsedTimeFromBeginning();
		g_multipleView->RenderWindow();
	}
}

void CEditMaterial::OnBnClickedBtnDeleteNormalmap()
{
	if( MessageBox( "Remove current normal map?", "Warning", MB_YESNO ) == IDYES )
	{
		RemoveUnsharedImage(m_strNormalMapName, eNORMAL_MAP);
		for (CUInt i = 0; i < g_scene.size(); i++)
			g_scene[i]->RemoveNormalMap();

		m_strNormalMapName = CString("");

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
		RemoveUnsharedImage(m_strGlossMapName, eGLOSS_MAP);
		for (CUInt i = 0; i < g_scene.size(); i++)
			g_scene[i]->RemoveGlossMap();

		m_strGlossMapName = CString("");

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
		RemoveUnsharedImage(m_strDirtMapName, eDIRT_MAP);
		for (CUInt i = 0; i < g_scene.size(); i++)
			g_scene[i]->RemoveDirtMap();

		m_strDirtMapName = CString("");

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
		RemoveUnsharedImage(m_strDiffuseName, eDIFFUSE);
		for (CUInt i = 0; i < g_scene.size(); i++)
			g_scene[i]->RemoveDiffuse();
		m_strDiffuseName = CString("");
		m_editBoxDiffuse.SetWindowTextA( NULL );
		m_btnRemoveDiffuse.EnableWindow( FALSE );
	}
	g_multipleView->SetElapsedTimeFromBeginning();
	g_multipleView->RenderWindow();
}

BOOL CEditMaterial::OnInitDialog()
{
	m_foundShininessDifference = m_foundTransparencyDifference = CFalse;
	CBool foundAmbientDifference = CFalse;
	CBool foundDiffuseDifference = CFalse;
	CBool foundSpecularDifference = CFalse;
	CBool foundEmissionDifference = CFalse;
	CBool foundTransparencyDifference = CFalse;
	CBool foundShininessDifference = CFalse;
	CChar ambientText[MAX_NAME_SIZE];
	CChar diffuseText[MAX_NAME_SIZE];
	CChar specularText[MAX_NAME_SIZE];
	CChar emissionText[MAX_NAME_SIZE];

	if (m_geometry)
	{
		//ambient difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat ambient1[4];
			ambient1[0] = m_geometry->m_groups[i]->GetAmbient()[0];
			ambient1[1] = m_geometry->m_groups[i]->GetAmbient()[1];
			ambient1[2] = m_geometry->m_groups[i]->GetAmbient()[2];
			ambient1[3] = m_geometry->m_groups[i]->GetAmbient()[3];
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat ambient2[4];
				ambient2[0] = m_geometry->m_groups[j]->GetAmbient()[0];
				ambient2[1] = m_geometry->m_groups[j]->GetAmbient()[1];
				ambient2[2] = m_geometry->m_groups[j]->GetAmbient()[2];
				ambient2[3] = m_geometry->m_groups[j]->GetAmbient()[3];
				if ((ambient1[0] - ambient2[0]) > EPSILON || (ambient1[1] - ambient2[1]) > EPSILON || (ambient1[2] - ambient2[2]) > EPSILON || (ambient1[3] - ambient2[3]) > EPSILON)
				{
					foundAmbientDifference = CTrue;
					break;
				}
			}
			if (foundAmbientDifference)
				break;
		}
		if (!foundAmbientDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetAmbientColor(m_geometry->m_groups[0]->GetAmbient());
				sprintf(ambientText, "R: %.2f, G: %.2f, B: %.2f", m_geometry->m_groups[0]->GetAmbient()[0], m_geometry->m_groups[0]->GetAmbient()[1], m_geometry->m_groups[0]->GetAmbient()[2]);
			}
		}
		//diffuse difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat diffuse1[4];
			diffuse1[0] = m_geometry->m_groups[i]->GetDiffuse()[0];
			diffuse1[1] = m_geometry->m_groups[i]->GetDiffuse()[1];
			diffuse1[2] = m_geometry->m_groups[i]->GetDiffuse()[2];
			diffuse1[3] = m_geometry->m_groups[i]->GetDiffuse()[3];
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat diffuse2[4];
				diffuse2[0] = m_geometry->m_groups[j]->GetDiffuse()[0];
				diffuse2[1] = m_geometry->m_groups[j]->GetDiffuse()[1];
				diffuse2[2] = m_geometry->m_groups[j]->GetDiffuse()[2];
				diffuse2[3] = m_geometry->m_groups[j]->GetDiffuse()[3];
				if ((diffuse1[0] - diffuse2[0]) > EPSILON || (diffuse1[1] - diffuse2[1]) > EPSILON || (diffuse1[2] - diffuse2[2]) > EPSILON || (diffuse1[3] - diffuse2[3]) > EPSILON)
				{
					foundDiffuseDifference = CTrue;
					break;
				}
			}
			if (foundDiffuseDifference)
				break;
		}
		if (!foundDiffuseDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetDiffuseColor(m_geometry->m_groups[0]->GetDiffuse());
				sprintf(diffuseText, "R: %.2f, G: %.2f, B: %.2f", m_geometry->m_groups[0]->GetDiffuse()[0], m_geometry->m_groups[0]->GetDiffuse()[1], m_geometry->m_groups[0]->GetDiffuse()[2]);
			}
		}

		//Specular difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat specular1[4];
			specular1[0] = m_geometry->m_groups[i]->GetSpecular()[0];
			specular1[1] = m_geometry->m_groups[i]->GetSpecular()[1];
			specular1[2] = m_geometry->m_groups[i]->GetSpecular()[2];
			specular1[3] = m_geometry->m_groups[i]->GetSpecular()[3];
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat specular2[4];
				specular2[0] = m_geometry->m_groups[j]->GetSpecular()[0];
				specular2[1] = m_geometry->m_groups[j]->GetSpecular()[1];
				specular2[2] = m_geometry->m_groups[j]->GetSpecular()[2];
				specular2[3] = m_geometry->m_groups[j]->GetSpecular()[3];
				if ((specular1[0] - specular2[0]) > EPSILON || (specular1[1] - specular2[1]) > EPSILON || (specular1[2] - specular2[2]) > EPSILON || (specular1[3] - specular2[3]) > EPSILON)
				{
					foundSpecularDifference = CTrue;
					break;
				}
			}
			if (foundSpecularDifference)
				break;
		}
		if (!foundSpecularDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetSpecularColor(m_geometry->m_groups[0]->GetSpecular());
				sprintf(specularText, "R: %.2f, G: %.2f, B: %.2f", m_geometry->m_groups[0]->GetSpecular()[0], m_geometry->m_groups[0]->GetSpecular()[1], m_geometry->m_groups[0]->GetSpecular()[2]);
			}
		}

		//Emission difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat emission1[4];
			emission1[0] = m_geometry->m_groups[i]->GetEmission()[0];
			emission1[1] = m_geometry->m_groups[i]->GetEmission()[1];
			emission1[2] = m_geometry->m_groups[i]->GetEmission()[2];
			emission1[3] = m_geometry->m_groups[i]->GetEmission()[3];
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat emission2[4];
				emission2[0] = m_geometry->m_groups[j]->GetEmission()[0];
				emission2[1] = m_geometry->m_groups[j]->GetEmission()[1];
				emission2[2] = m_geometry->m_groups[j]->GetEmission()[2];
				emission2[3] = m_geometry->m_groups[j]->GetEmission()[3];
				if ((emission1[0] - emission2[0]) > EPSILON || (emission1[1] - emission2[1]) > EPSILON || (emission1[2] - emission2[2]) > EPSILON || (emission1[3] - emission2[3]) > EPSILON)
				{
					foundEmissionDifference = CTrue;
					break;
				}
			}
			if (foundEmissionDifference)
				break;
		}
		if (!foundEmissionDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetEmissionColor(m_geometry->m_groups[0]->GetEmission());
				sprintf(emissionText, "R: %.2f, G: %.2f, B: %.2f", m_geometry->m_groups[0]->GetEmission()[0], m_geometry->m_groups[0]->GetEmission()[1], m_geometry->m_groups[0]->GetEmission()[2]);
			}
		}

		//Transparency difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat transparency1;
			transparency1 = m_geometry->m_groups[i]->GetTransparency();
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat transparency2;
				transparency2 = m_geometry->m_groups[j]->GetTransparency();
				if (transparency1 - transparency2 > EPSILON)
				{
					foundTransparencyDifference = CTrue;
					break;
				}
			}
			if (foundTransparencyDifference)
				break;
		}
		if (!foundTransparencyDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetTransparency(m_geometry->m_groups[0]->GetTransparency());
			}
		}
		else
		{
			m_foundTransparencyDifference = CTrue;
		}

		//Shininess difference for geometries
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CFloat shininess1;
			shininess1 = m_geometry->m_groups[i]->GetShininess();
			for (CUInt j = 0; j < m_geometry->m_groups.size(); j++)
			{
				CFloat shininess2;
				shininess2 = m_geometry->m_groups[j]->GetShininess();
				if (shininess1 - shininess2 > EPSILON)
				{
					foundShininessDifference = CTrue;
					break;
				}
			}
			if (foundShininessDifference)
				break;
		}
		if (!foundShininessDifference)
		{
			if (m_geometry->m_groups.size())
			{
				SetShininess(m_geometry->m_groups[0]->GetShininess());
			}
		}
		else
		{
			m_foundShininessDifference = CTrue;
		}

	}
	else if (m_polyGroup)
	{
		sprintf(ambientText, "R: %.2f, G: %.2f, B: %.2f", m_polyGroup->GetAmbient()[0], m_polyGroup->GetAmbient()[1], m_polyGroup->GetAmbient()[2]);
		sprintf(diffuseText, "R: %.2f, G: %.2f, B: %.2f", m_polyGroup->GetDiffuse()[0], m_polyGroup->GetDiffuse()[1], m_polyGroup->GetDiffuse()[2]);
		sprintf(specularText, "R: %.2f, G: %.2f, B: %.2f", m_polyGroup->GetSpecular()[0], m_polyGroup->GetSpecular()[1], m_polyGroup->GetSpecular()[2]);
		sprintf(emissionText, "R: %.2f, G: %.2f, B: %.2f", m_polyGroup->GetEmission()[0], m_polyGroup->GetEmission()[1], m_polyGroup->GetEmission()[2]);

	}

	m_ambientBrush.DeleteObject();

	if (!foundAmbientDifference)
	{
		m_ambientColor = RGB((CInt)(m_fAmbientColor[0] * 255), (CInt)(m_fAmbientColor[1] * 255), (CInt)(m_fAmbientColor[2] * 255));
		m_ambientBrush.CreateSolidBrush(m_ambientColor);
	}
	else
	{
		m_ambientColor = RGB(255, 255, 255);
		m_ambientBrush.CreateSolidBrush(m_ambientColor);
	}

	m_diffuseBrush.DeleteObject();

	if (!foundDiffuseDifference)
	{
		m_diffuseColor = RGB((CInt)(m_fDiffuseColor[0] * 255), (CInt)(m_fDiffuseColor[1] * 255), (CInt)(m_fDiffuseColor[2] * 255));
		m_diffuseBrush.CreateSolidBrush(m_diffuseColor);
	}
	else
	{
		m_diffuseColor = RGB(255, 255, 255);
		m_diffuseBrush.CreateSolidBrush(m_diffuseColor);
	}

	m_specularBrush.DeleteObject();

	if (!foundSpecularDifference)
	{
		m_specularColor = RGB((CInt)(m_fSpecularColor[0] * 255), (CInt)(m_fSpecularColor[1] * 255), (CInt)(m_fSpecularColor[2] * 255));
		m_specularBrush.CreateSolidBrush(m_specularColor);
	}
	else
	{
		m_specularColor = RGB(255, 255, 255);
		m_specularBrush.CreateSolidBrush(m_specularColor);
	}

	m_emissionBrush.DeleteObject();

	if (!foundEmissionDifference)
	{
		m_emissionColor = RGB((CInt)(m_fEmissionColor[0] * 255), (CInt)(m_fEmissionColor[1] * 255), (CInt)(m_fEmissionColor[2] * 255));
		m_emissionBrush.CreateSolidBrush(m_emissionColor);
	}
	else
	{
		m_emissionColor = RGB(255, 255, 255);
		m_emissionBrush.CreateSolidBrush(m_emissionColor);
	}

	CDialog::OnInitDialog();

	m_editBoxNormalMap.SetWindowTextA(m_strNormalMapName);
	m_editBoxGlossMap.SetWindowTextA(m_strGlossMapName);
	m_editBoxDirtMap.SetWindowTextA(m_strDirtMapName);
	m_editBoxDiffuse.SetWindowTextA(m_strDiffuseName);
	m_editBoxScale.SetWindowTextA( m_strParallaxMapScale );
	m_editBoxBias.SetWindowTextA(m_strParallaxMapBias);


	if (foundAmbientDifference)
		m_editBoxAmbientColor.SetWindowTextA("*Multiple Colors*");
	else
		m_editBoxAmbientColor.SetWindowTextA(ambientText);

	if (foundDiffuseDifference)
		m_editBoxDiffuseColor.SetWindowTextA("*Multiple Colors*");
	else
		m_editBoxDiffuseColor.SetWindowTextA(diffuseText);

	if (foundSpecularDifference)
		m_editBoxSpecularColor.SetWindowTextA("*Multiple Colors*");
	else
		m_editBoxSpecularColor.SetWindowTextA(specularText);

	if (foundEmissionDifference)
		m_editBoxEmissionColor.SetWindowTextA("*Multiple Colors*");
	else
		m_editBoxEmissionColor.SetWindowTextA(emissionText);

	if (!foundTransparencyDifference)
		m_editBoxTransparency.SetWindowTextA(m_strTransparency);
	else
		m_editBoxTransparency.SetWindowTextA("");

	if (!foundShininessDifference)
		m_editBoxShininess.SetWindowTextA(m_strShininess);
	else
		m_editBoxShininess.SetWindowTextA("");


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
		MessageBox( "Please Fill In Parallax Map Bias And Parallax Map Scale Fileds", "Vanda Engine Error", MB_OK | MB_ICONERROR );
		return;
	}
	if (m_strShininess.IsEmpty() && !m_foundShininessDifference)
	{
		MessageBox("Please Fill In Shininess Filed", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_strTransparency.IsEmpty() && !m_foundTransparencyDifference)
	{
		MessageBox("Please Fill In Transparency Filed", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (!m_strShininess.IsEmpty() && m_fShininess < 0.0f)
	{
		MessageBox("Shininess must be 0.0 or higher", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (!m_strTransparency.IsEmpty() && (m_fTransparency < 0.0f || m_fTransparency > 1.0f))
	{
		MessageBox("Transparency must be between 0.0 and 1.0", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	//Material Colors
	if (m_geometry)
	{
		for (CUInt i = 0; i < m_geometry->m_groups.size(); i++)
		{
			CString ambient, diffuse, specular, emission, shininess, transparency;
			m_editBoxAmbientColor.GetWindowTextA(ambient);
			m_editBoxDiffuseColor.GetWindowTextA(diffuse);
			m_editBoxSpecularColor.GetWindowTextA(specular);
			m_editBoxEmissionColor.GetWindowTextA(emission);
			if (!m_strShininess.IsEmpty())
				m_editBoxShininess.GetWindowTextA(shininess);

			if (!m_strTransparency.IsEmpty())
				m_editBoxTransparency.GetWindowTextA(transparency);

			if (m_updateAmbient && !Cmp(ambient.GetBuffer(ambient.GetLength()), "*Multiple Colors*"))
			{
				m_geometry->m_groups[i]->SetAmbient(m_fAmbientColor);
			}
			if (m_updateDiffuse && !Cmp(diffuse.GetBuffer(diffuse.GetLength()), "*Multiple Colors*"))
			{
				m_geometry->m_groups[i]->SetDiffuse(m_fDiffuseColor);
			}
			if (m_updateSpecular && !Cmp(specular.GetBuffer(specular.GetLength()), "*Multiple Colors*"))
			{
				m_geometry->m_groups[i]->SetSpecular(m_fSpecularColor);
			}
			if (m_updateEmission && !Cmp(emission.GetBuffer(emission.GetLength()), "*Multiple Colors*"))
			{
				m_geometry->m_groups[i]->SetEmission(m_fEmissionColor);
			}
			if (!m_strShininess.IsEmpty())
				m_geometry->m_groups[i]->SetShininess(m_fShininess);

			if (!m_strTransparency.IsEmpty())
				m_geometry->m_groups[i]->SetTransparency(m_fTransparency);
		}
	}
	else if (m_polyGroup)
	{
		m_polyGroup->SetAmbient(m_fAmbientColor);
		m_polyGroup->SetDiffuse(m_fDiffuseColor);
		m_polyGroup->SetSpecular(m_fSpecularColor);
		m_polyGroup->SetEmission(m_fEmissionColor);
		m_polyGroup->SetShininess(m_fShininess);
		m_polyGroup->SetTransparency(m_fTransparency);

	}
	CDialog::OnOK();
}

INT_PTR CEditMaterial::DoModal()
{
	INT_PTR nResult;
	nResult = CDialog::DoModal();
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
					if( m_geo->m_groups[k]->m_hasDiffuse && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_diffuseImg->GetFileName()) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasNormalMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_normalMapImg->GetFileName()) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasGlossMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_glossMapImg->GetFileName()) ) )
					{
						numImages++;
						if( numImages > maxImages )
						{
							foundTarget = CTrue;
							break;
						}
					}
					if( m_geo->m_groups[k]->m_hasDirtMap && Cmp(imageName, GetAfterPath(m_geo->m_groups[k]->m_dirtMapImg->GetFileName()) ) )
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
				if( Cmp( GetAfterPath(g_images[p]->GetFileName()), imageName ) )
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf( temp, "\n%s%s%s", "Image '", imageName, "' removed from memory" );
					PrintInfo( temp, COLOR_YELLOW );
					CDelete(g_images[p]);
					g_images.erase( g_images.begin() + p );
					break;
				}
			}
		}
	}
}



void CEditMaterial::OnBnClickedButtonAmbient()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_ambientColor = dlg.GetColor();
		m_fAmbientColor[0] = (CFloat)GetRValue(m_ambientColor) / 255.0f;
		m_fAmbientColor[1] = (CFloat)GetGValue(m_ambientColor) / 255.0f;
		m_fAmbientColor[2] = (CFloat)GetBValue(m_ambientColor) / 255.0f;
		m_fAmbientColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_ambientBrush.DeleteObject();
		m_ambientBrush.CreateSolidBrush(m_ambientColor);
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "R: %.2f, G: %.2f, B: %.2f", m_fAmbientColor[0], m_fAmbientColor[1], m_fAmbientColor[2]);
		m_editBoxAmbientColor.SetWindowTextA(temp);
		m_editBoxAmbientColor.RedrawWindow();
		m_updateAmbient = CTrue;
	}
}


void CEditMaterial::OnBnClickedButtonDiffuse()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_diffuseColor = dlg.GetColor();
		m_fDiffuseColor[0] = (CFloat)GetRValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[1] = (CFloat)GetGValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[2] = (CFloat)GetBValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[3] = 1.0f;
		m_diffuseBrush.DeleteObject();
		m_diffuseBrush.CreateSolidBrush(m_diffuseColor);
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "R: %.2f, G: %.2f, B: %.2f", m_fDiffuseColor[0], m_fDiffuseColor[1], m_fDiffuseColor[2]);
		m_editBoxDiffuseColor.SetWindowTextA(temp);
		m_editBoxDiffuseColor.RedrawWindow();
		m_updateDiffuse = CTrue;
	}
}


void CEditMaterial::OnBnClickedButtonSpecular()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_specularColor = dlg.GetColor();
		m_fSpecularColor[0] = (CFloat)GetRValue(m_specularColor) / 255.f;
		m_fSpecularColor[1] = (CFloat)GetGValue(m_specularColor) / 255.f;
		m_fSpecularColor[2] = (CFloat)GetBValue(m_specularColor) / 255.f;
		m_fSpecularColor[3] = 1.0f;
		m_specularBrush.DeleteObject();
		m_specularBrush.CreateSolidBrush(m_specularColor);
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "R: %.2f, G: %.2f, B: %.2f", m_fSpecularColor[0], m_fSpecularColor[1], m_fSpecularColor[2]);
		m_editBoxSpecularColor.SetWindowTextA(temp);
		m_editBoxSpecularColor.RedrawWindow();
		m_updateSpecular = CTrue;
	}
}


void CEditMaterial::OnBnClickedButtonEmission()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_emissionColor = dlg.GetColor();
		m_fEmissionColor[0] = (CFloat)GetRValue(m_emissionColor) / 255.f;
		m_fEmissionColor[1] = (CFloat)GetGValue(m_emissionColor) / 255.f;
		m_fEmissionColor[2] = (CFloat)GetBValue(m_emissionColor) / 255.f;
		m_fEmissionColor[3] = 1.0f;
		m_emissionBrush.DeleteObject();
		m_emissionBrush.CreateSolidBrush(m_emissionColor);
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "R: %.2f, G: %.2f, B: %.2f", m_fEmissionColor[0], m_fEmissionColor[1], m_fEmissionColor[2]);
		m_editBoxEmissionColor.SetWindowTextA(temp);
		m_editBoxEmissionColor.RedrawWindow();
		m_updateEmission = CTrue;
	}
}

HBRUSH CEditMaterial::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_AMBIENT_COLOR:
		pDC->SetBkColor(m_ambientColor);
		if (GetRValue(m_ambientColor) < 128 && GetGValue(m_ambientColor) < 128 && GetBValue(m_ambientColor) < 128)
			pDC->SetTextColor(RGB(255, 255, 255));
		else
			pDC->SetTextColor(RGB(0, 0, 0));

		return m_ambientBrush;
	case IDC_EDIT_DIFFUSE_COLOR:
		pDC->SetBkColor(m_diffuseColor);
		if (GetRValue(m_diffuseColor) < 128 && GetGValue(m_diffuseColor) < 128 && GetBValue(m_diffuseColor) < 128)
			pDC->SetTextColor(RGB(255, 255, 255));
		else
			pDC->SetTextColor(RGB(0, 0, 0));

		return m_diffuseBrush;
	case IDC_EDIT_SPECULAR_COLOR:
		pDC->SetBkColor(m_specularColor);
		if (GetRValue(m_specularColor) < 128 && GetGValue(m_specularColor) < 128 && GetBValue(m_specularColor) < 128)
			pDC->SetTextColor(RGB(255, 255, 255));
		else
			pDC->SetTextColor(RGB(0, 0, 0));

		return m_specularBrush;
	case IDC_EDIT_EMISSION_COLOR:
		pDC->SetBkColor(m_emissionColor);
		if (GetRValue(m_emissionColor) < 128 && GetGValue(m_emissionColor) < 128 && GetBValue(m_emissionColor) < 128)
			pDC->SetTextColor(RGB(255, 255, 255));
		else
			pDC->SetTextColor(RGB(0, 0, 0));

		return m_emissionBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CEditMaterial::OnEnChangeEditShininess()
{
	m_editBoxShininess.GetWindowTextA(m_strShininess);
	m_fShininess = atof(m_strShininess);
}

void CEditMaterial::OnEnChangeEditTransparency()
{
	m_editBoxTransparency.GetWindowTextA(m_strTransparency);
	m_fTransparency = atof(m_strTransparency);
}



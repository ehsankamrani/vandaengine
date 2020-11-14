// AddTerrain.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddTerrain.h"
#include "afxdialogex.h"


// CAddTerrain dialog

IMPLEMENT_DYNAMIC(CAddTerrain, CDialog)

CAddTerrain::CAddTerrain(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTerrain::IDD, pParent)
	, m_create(false)
	, m_editMode(false)
{
}

CAddTerrain::~CAddTerrain()
{
}

void CAddTerrain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HEIGHTMAP_TEXTURE_PATH, m_editBoxHeightMapPath);
	DDX_Control(pDX, IDC_EDIT_BOTTOM_TEXTURE_PATH, m_editBoxBottomTexturePath);
	DDX_Control(pDX, IDC_EDIT_BOTTOM_NORMALMAP_PATH, m_editBoxBottomNormalMapPath);
	DDX_Control(pDX, IDC_EDIT_SLOPE_TEXTURE_PATH, m_editBoxSlopeTexturePath);
	DDX_Control(pDX, IDC_EDIT_SLOPE_NORMALMAP_PATH, m_editBoxSlopeNormalMapPath);
	DDX_Control(pDX, IDC_EDIT_SLOPE_FACTOR, m_editBoxSlopeFactor);
	DDX_Control(pDX, IDC_EDIT_TOP_TEXTURE_PATH, m_editBoxTopTexturePath);
	DDX_Control(pDX, IDC_EDIT_TOP_NORMALMAP_PATH, m_editBoxTopNormalMapPath);
	DDX_Control(pDX, IDC_EDIT_START_HEIGHT, m_editBoxTopStartHeight);
	DDX_Control(pDX, IDC_EDIT_SHININESS, m_editBoxShininess);
	DDX_Control(pDX, IDC_EDIT_SMOOTH, m_editBoxSmooth);
	DDX_Control(pDX, IDC_EDIT_SCALE_HEIGHT, m_editBoxScaleHeight);
	DDX_Control(pDX, IDC_EDIT_SCALE_WIDTH, m_editBoxScaleWidth);
	DDX_Control(pDX, IDC_EDIT_AMBIENT_COLOR, m_editBoxAmbientColor);
	DDX_Control(pDX, IDC_EDIT_DIFFUSE_COLOR, m_editBoxDiffuseColor);
	DDX_Control(pDX, IDC_EDIT_SPECULAR_COLOR, m_editBoxSpecularColor);
	DDX_Control(pDX, IDC_EDIT_TERRAIN_NAME, m_editBoxName);
	DDX_Control(pDX, IDC_FLAT_FILTER, m_checkBoxFlatten);
}


BEGIN_MESSAGE_MAP(CAddTerrain, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADD_HEIGHTMAP, &CAddTerrain::OnBnClickedButtonAddHeightmap)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BOTTOM_TEXTURE, &CAddTerrain::OnBnClickedButtonAddBottomTexture)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BOTTOM_NORMALMAP, &CAddTerrain::OnBnClickedButtonAddBottomNormalmap)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SLOPE_TEXTURE, &CAddTerrain::OnBnClickedButtonAddSlopeTexture)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SLOPE_NORMALMAP, &CAddTerrain::OnBnClickedButtonAddSlopeNormalmap)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TOP_TEXTURE, &CAddTerrain::OnBnClickedButtonAddTopTexture)
	ON_BN_CLICKED(IDC_BUTTON_ADD_TOP_NORMALMAP, &CAddTerrain::OnBnClickedButtonAddTopNormalmap)
	ON_BN_CLICKED(IDC_BUTTON_ADD_AMBIENT_COLOR, &CAddTerrain::OnBnClickedButtonAddAmbientColor)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DIFFUSE_COLOR, &CAddTerrain::OnBnClickedButtonAddDiffuseColor)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SPECULAR_COLOR, &CAddTerrain::OnBnClickedButtonAddSpecularColor)
	ON_EN_CHANGE(IDC_EDIT_SLOPE_FACTOR, &CAddTerrain::OnEnChangeEditSlopeFactor)
	ON_EN_CHANGE(IDC_EDIT_START_HEIGHT, &CAddTerrain::OnEnChangeEditStartHeight)
	ON_EN_CHANGE(IDC_EDIT_SMOOTH, &CAddTerrain::OnEnChangeEditSmooth)
	ON_EN_CHANGE(IDC_EDIT_SCALE_HEIGHT, &CAddTerrain::OnEnChangeEditScaleHeight)
	ON_EN_CHANGE(IDC_EDIT_SCALE_WIDTH, &CAddTerrain::OnEnChangeEditScaleWidth)
	ON_EN_CHANGE(IDC_EDIT_TERRAIN_NAME, &CAddTerrain::OnEnChangeEditTerrainName)
	ON_EN_CHANGE(IDC_EDIT_SHININESS, &CAddTerrain::OnEnChangeEditShininess)
	ON_BN_CLICKED(IDOK, &CAddTerrain::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddTerrain message handlers


void CAddTerrain::OnBnClickedButtonAddHeightmap()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.tga"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("Targa File (*.tga)|*.tga||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_changedHeightMap = CTrue;
		m_strHeightMapPath = (CString)dlgOpen.GetPathName();
		m_editBoxHeightMapPath.SetWindowText(m_strHeightMapPath);
	}
}


void CAddTerrain::OnBnClickedButtonAddBottomTexture()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strBottomTexturePath = (CString)dlgOpen.GetPathName();
		m_editBoxBottomTexturePath.SetWindowText(m_strBottomTexturePath);
	}
}


void CAddTerrain::OnBnClickedButtonAddBottomNormalmap()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strBottomNormalMapPath = (CString)dlgOpen.GetPathName();
		m_editBoxBottomNormalMapPath.SetWindowText(m_strBottomNormalMapPath);
	}
}


void CAddTerrain::OnBnClickedButtonAddSlopeTexture()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strSlopeTexturePath = (CString)dlgOpen.GetPathName();
		m_editBoxSlopeTexturePath.SetWindowText(m_strSlopeTexturePath);
	}
}


void CAddTerrain::OnBnClickedButtonAddSlopeNormalmap()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strSlopeNormalMapPath = (CString)dlgOpen.GetPathName();
		m_editBoxSlopeNormalMapPath.SetWindowText(m_strSlopeNormalMapPath);
	}
}


void CAddTerrain::OnBnClickedButtonAddTopTexture()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strTopTexturePath = (CString)dlgOpen.GetPathName();
		m_editBoxTopTexturePath.SetWindowText(m_strTopTexturePath);
	}
}


void CAddTerrain::OnBnClickedButtonAddTopNormalmap()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("dds File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strTopNormalMapPath = (CString)dlgOpen.GetPathName();
		m_editBoxTopNormalMapPath.SetWindowText(m_strTopNormalMapPath);
	}
}


void CAddTerrain::OnBnClickedButtonAddAmbientColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_ambientColor = dlg.GetColor();
		m_fAmbientColor[0] = (CFloat)GetRValue(m_ambientColor) / 255.f;
		m_fAmbientColor[1] = (CFloat)GetGValue(m_ambientColor) / 255.f;
		m_fAmbientColor[2] = (CFloat)GetBValue(m_ambientColor) / 255.f;
		m_fAmbientColor[3] = 1.0f; //I write it directly, no need to use alpha value for the ambient light
		m_ambientBrush.CreateSolidBrush(m_ambientColor);
		m_editBoxAmbientColor.RedrawWindow();
	}
}


void CAddTerrain::OnBnClickedButtonAddDiffuseColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_diffuseColor = dlg.GetColor();
		m_fDiffuseColor[0] = (CFloat)GetRValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[1] = (CFloat)GetGValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[2] = (CFloat)GetBValue(m_diffuseColor) / 255.f;
		m_fDiffuseColor[3] = 1.0f;
		m_diffuseBrush.CreateSolidBrush(m_diffuseColor);
		m_editBoxDiffuseColor.RedrawWindow();
	}
}


void CAddTerrain::OnBnClickedButtonAddSpecularColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_specularColor = dlg.GetColor();
		m_fSpecularColor[0] = (CFloat)GetRValue(m_specularColor) / 255.f;
		m_fSpecularColor[1] = (CFloat)GetGValue(m_specularColor) / 255.f;
		m_fSpecularColor[2] = (CFloat)GetBValue(m_specularColor) / 255.f;
		m_fSpecularColor[3] = 1.0f;
		m_specularBrush.CreateSolidBrush(m_specularColor);
		m_editBoxSpecularColor.RedrawWindow();
	}
}


BOOL CAddTerrain::OnInitDialog()
{
	if (m_create)
	{
		m_strName = "Terrain";

		m_strShininess = "100.0f";
		m_fShininess = 100.0f;

		m_strSmooth = "1";
		m_smooth = 1;

		m_strScaleHeight = "128.0f";
		m_fScaleHeight = 128.0f;

		m_strScaleWidth = "2.0f";
		m_fScaleWidth = 2.0f;

		m_strSlopeFactor = "0.3f";
		m_fSlopeFactor = 0.3f;

		m_strTopStartHeight = "30.0f";
		m_fTopStartHeight = 30.0f;

		m_flatten = CTrue;

		CChar terrainTopNormalmapPath[MAX_NAME_SIZE];
		sprintf(terrainTopNormalmapPath, "%s%s", g_pathProperties.m_terrainPath, "top_normal.dds");
		m_strTopNormalMapPath = terrainTopNormalmapPath;

		CChar terrainTopTexturePath[MAX_NAME_SIZE];
		sprintf(terrainTopTexturePath, "%s%s", g_pathProperties.m_terrainPath, "top.dds");
		m_strTopTexturePath = terrainTopTexturePath;

		CChar terrainSlopeNormalmapPath[MAX_NAME_SIZE];
		sprintf(terrainSlopeNormalmapPath, "%s%s", g_pathProperties.m_terrainPath, "slope_normal.dds");
		m_strSlopeNormalMapPath = terrainSlopeNormalmapPath;

		CChar terrainSlopeTexturePath[MAX_NAME_SIZE];
		sprintf(terrainSlopeTexturePath, "%s%s", g_pathProperties.m_terrainPath, "slope.dds");
		m_strSlopeTexturePath = terrainSlopeTexturePath;

		CChar terrainHeightMapTexturePath[MAX_NAME_SIZE];
		sprintf(terrainHeightMapTexturePath, "%s%s", g_pathProperties.m_terrainPath, "height.tga");
		m_strHeightMapPath = terrainHeightMapTexturePath;

		CChar terrainBottomNormalmapPath[MAX_NAME_SIZE];
		sprintf(terrainBottomNormalmapPath, "%s%s", g_pathProperties.m_terrainPath, "bottom_normal.dds");
		m_strBottomNormalMapPath = terrainBottomNormalmapPath;

		CChar terrainBottomTexturePath[MAX_NAME_SIZE];
		sprintf(terrainBottomTexturePath, "%s%s", g_pathProperties.m_terrainPath, "bottom.dds");
		m_strBottomTexturePath = terrainBottomTexturePath;

		m_ambientColor = RGB(128, 128, 128);
		m_diffuseColor = RGB(128, 128, 128);
		m_specularColor = RGB(128, 128, 128);

		m_fAmbientColor[0] = m_fAmbientColor[1] = m_fAmbientColor[2] = 0.5f; m_fAmbientColor[3] = 1.0f;
		m_fDiffuseColor[0] = m_fDiffuseColor[1] = m_fDiffuseColor[2] = 0.5f; m_fDiffuseColor[3] = 1.0f;
		m_fSpecularColor[0] = m_fSpecularColor[1] = m_fSpecularColor[2] = 0.5f; m_fSpecularColor[3] = 1.0f;
	}
	else if (m_editMode)
	{
		m_ambientColor = RGB((CInt)(m_fAmbientColor[0] * 255), (CInt)(m_fAmbientColor[1] * 255), (CInt)(m_fAmbientColor[2] * 255));
		m_diffuseColor = RGB((CInt)(m_fDiffuseColor[0] * 255), (CInt)(m_fDiffuseColor[1] * 255), (CInt)(m_fDiffuseColor[2] * 255));
		m_specularColor = RGB((CInt)(m_fSpecularColor[0] * 255), (CInt)(m_fSpecularColor[1] * 255), (CInt)(m_fSpecularColor[2] * 255));

		m_changedHeightMap = CFalse;
	}

	m_ambientBrush.CreateSolidBrush(m_ambientColor);
	m_diffuseBrush.CreateSolidBrush(m_diffuseColor);
	m_specularBrush.CreateSolidBrush(m_specularColor);


	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editBoxName.SetWindowTextA(m_strName);
	m_editBoxHeightMapPath.SetWindowTextA(m_strHeightMapPath);
	m_editBoxBottomTexturePath.SetWindowTextA(m_strBottomTexturePath);
	m_editBoxBottomNormalMapPath.SetWindowTextA(m_strBottomNormalMapPath);
	m_editBoxSlopeTexturePath.SetWindowTextA(m_strSlopeTexturePath);
	m_editBoxSlopeNormalMapPath.SetWindowTextA(m_strSlopeNormalMapPath);
	m_editBoxSlopeFactor.SetWindowTextA(m_strSlopeFactor);
	m_editBoxTopTexturePath.SetWindowTextA(m_strTopTexturePath);
	m_editBoxTopNormalMapPath.SetWindowTextA(m_strTopNormalMapPath);
	m_editBoxTopStartHeight.SetWindowTextA(m_strTopStartHeight);
	m_editBoxShininess.SetWindowTextA(m_strShininess);
	m_editBoxSmooth.SetWindowTextA(m_strSmooth);
	m_editBoxScaleHeight.SetWindowTextA(m_strScaleHeight);
	m_editBoxScaleWidth.SetWindowTextA(m_strScaleWidth);

	if (m_flatten)
		m_checkBoxFlatten.SetCheck(BST_CHECKED);
	else
		m_checkBoxFlatten.SetCheck(BST_UNCHECKED);

	m_strTempName = m_strName;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAddTerrain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_EDIT_AMBIENT_COLOR:
		pDC->SetBkColor(m_ambientColor);
		return m_ambientBrush;
	case IDC_EDIT_DIFFUSE_COLOR:
		pDC->SetBkColor(m_diffuseColor);
		return m_diffuseBrush;
	case IDC_EDIT_SPECULAR_COLOR:
		pDC->SetBkColor(m_specularColor);
		return m_specularBrush;
	}
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}



void CAddTerrain::OnEnChangeEditSlopeFactor()
{
	m_editBoxSlopeFactor.GetWindowTextA(m_strSlopeFactor);
	m_fSlopeFactor = atof(m_strSlopeFactor);
}


void CAddTerrain::OnEnChangeEditStartHeight()
{
	m_editBoxTopStartHeight.GetWindowTextA(m_strTopStartHeight);
	m_fTopStartHeight = atof(m_strTopStartHeight);
}


void CAddTerrain::OnEnChangeEditSmooth()
{
	m_editBoxSmooth.GetWindowTextA(m_strSmooth);
	m_smooth = atoi(m_strSmooth);
}


void CAddTerrain::OnEnChangeEditScaleHeight()
{
	m_editBoxScaleHeight.GetWindowTextA(m_strScaleHeight);
	m_fScaleHeight = atof(m_strScaleHeight);
}


void CAddTerrain::OnEnChangeEditScaleWidth()
{
	m_editBoxScaleWidth.GetWindowTextA(m_strScaleWidth);
	m_fScaleWidth = atof(m_strScaleWidth);
}


void CAddTerrain::OnEnChangeEditTerrainName()
{
	m_editBoxName.GetWindowTextA(m_strName);
}


void CAddTerrain::OnEnChangeEditShininess()
{
	m_editBoxShininess.GetWindowTextA(m_strShininess);
	m_fShininess = atof(m_strShininess);
}


void CAddTerrain::OnBnClickedOk()
{
	if (g_multipleView->IsPlayGameMode())
	{
		if (MessageBox("Exit from play mode?", "Vanda Engine Error", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			ex_pVandaEngine1Dlg->OnBnClickedBtnPlayActive();

		}
		else
		{
			return;
		}
	}

	CInt checkState;
	checkState = m_checkBoxFlatten.GetCheck();
	if (checkState == BST_CHECKED)
		m_flatten = CTrue;
	else
		m_flatten = CFalse;

	CBool compare = CFalse;
	if (!m_strName.IsEmpty())
	{
		compare = CTrue;
		if (m_editMode)
			if (m_strName == m_strTempName)
				compare = CFalse;
	}
	else
		compare = CFalse;

	if (compare)
	{
		for (std::vector<std::string>::iterator it = g_engineObjectNames.begin(); it != g_engineObjectNames.end(); it++)
		{
			if (Cmp((LPCSTR)m_strName, (*it).c_str()))
			{
				MessageBox("This name already exist. Please select another name!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				return;
			}
		}
	}
	if (!m_strHeightMapPath.IsEmpty())
	{
		CImage* image = CNew(CImage);
		if (CTexture::LoadTexture(image, (CChar*)m_strHeightMapPath.GetBuffer(m_strHeightMapPath.GetLength()), NULL, CFalse))
		{
			if (image->GetWidth() != 512 || image->GetHeight() != 512)
			{
				MessageBox("Height Map Width x Height Must Be 512 x 512", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				CDelete(image);
				return;
			}
		}
		else
		{
			CDelete(image);
			MessageBox("Couldn't load height map image", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	if (m_strHeightMapPath.IsEmpty() || m_strBottomTexturePath.IsEmpty() ||	m_strBottomNormalMapPath.IsEmpty() ||
		m_strSlopeTexturePath.IsEmpty() || m_strSlopeNormalMapPath.IsEmpty() || m_strSlopeFactor.IsEmpty() ||
		m_strTopTexturePath.IsEmpty() || m_strTopNormalMapPath.IsEmpty() || m_strTopStartHeight.IsEmpty() ||
		m_strShininess.IsEmpty() || m_strSmooth.IsEmpty() || m_strScaleHeight.IsEmpty() ||
		m_strScaleWidth.IsEmpty() || m_strName.IsEmpty())
	{
		MessageBox("Please Fill In All Of The Required Fields", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CImage* m_bottomImg = CNew(CImage);
	CImage*m_bottomNormalImg = CNew(CImage);
	CImage*m_slopeImg = CNew(CImage);
	CImage*m_slopeNormalImg = CNew(CImage);
	CImage*m_topImg = CNew(CImage);
	CImage*m_topNormalImg = CNew(CImage);
	// Load our textures.

	if (!CTexture::LoadDDSTexture(m_bottomImg, (CChar*)m_strBottomTexturePath.GetBuffer(m_strBottomTexturePath.GetLength()), NULL))
	{
		MessageBox("Couldn't load bottom texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_bottomImg);
		return;
	}
	if (!CTexture::LoadDDSTexture(m_bottomNormalImg, (CChar*)m_strBottomNormalMapPath.GetBuffer(m_strBottomNormalMapPath.GetLength()), NULL))
	{
		MessageBox("Couldn't load bottom normal texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_bottomNormalImg);
		return;
	}
	if (!CTexture::LoadDDSTexture(m_slopeImg, (CChar*)m_strSlopeTexturePath.GetBuffer(m_strSlopeTexturePath.GetLength()), NULL))
	{
		MessageBox("Couldn't load slope texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_slopeImg);
		return;
	}
	if (!CTexture::LoadDDSTexture(m_slopeNormalImg, (CChar*)m_strSlopeNormalMapPath.GetBuffer(m_strSlopeNormalMapPath.GetLength()), NULL))
	{
		MessageBox("Couldn't load slope normal texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_slopeNormalImg);
		return;
	}
	if (!CTexture::LoadDDSTexture(m_topImg, (CChar*)m_strTopTexturePath.GetBuffer(m_strTopTexturePath.GetLength()), NULL))
	{
		MessageBox("Couldn't load top texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_topImg);
		return;
	}
	if (!CTexture::LoadDDSTexture(m_topNormalImg, (CChar*)m_strTopNormalMapPath.GetBuffer(m_strTopNormalMapPath.GetLength()), NULL))
	{
		MessageBox("Couldn't load top normal texture", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		CDelete(m_topNormalImg);
		return;
	}

	CDelete(m_bottomImg);
	CDelete(m_bottomNormalImg);
	CDelete(m_slopeImg);
	CDelete(m_slopeNormalImg);
	CDelete(m_topImg);
	CDelete(m_topNormalImg);

	CDialog::OnOK();
}

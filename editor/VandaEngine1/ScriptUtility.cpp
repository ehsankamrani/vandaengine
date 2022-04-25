//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptUtility.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtility.h"
#include "afxdialogex.h"
#include "ScriptUtilityPrefabInstances.h"
#include "ScriptUtilityPrefabs.h"
#include "ScriptUtilityImportedCameras.h"
#include "ScriptUtilityGameObjects.h"
#include "ScriptUtilityGUIs.h"
#include "ScriptUtilityResources.h"
#include "GUIDlg.h"
// CScriptUtility dialog

IMPLEMENT_DYNAMIC(CScriptUtility, CDialog)

CScriptUtility::CScriptUtility(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtility::IDD, pParent)
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);
}

CScriptUtility::~CScriptUtility()
{
}

void CScriptUtility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB_PROJECT_NAME, m_comboProject);
	DDX_Control(pDX, IDC_COMB_VSCENE_NAME, m_comboVScene);
	DDX_Control(pDX, IDC_RICHED_VSCENE_NAME, m_richVSceneName);
	DDX_Control(pDX, IDC_COPY_VSCENE_NAME, m_btnCopyVSceneName);
	DDX_Control(pDX, IDC_PREFAB_INSTANCES, m_btnVScenePrefabInstances);
	DDX_Control(pDX, IDC_GAMEOBJECTS, m_btnVSceneGameObjects);
	DDX_Control(pDX, IDC_IMPORTED_CAMERAS, m_btnVSceneImportedCameras);
	DDX_Control(pDX, IDC_GUIs, m_btnVSceneGUIs);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
}


BEGIN_MESSAGE_MAP(CScriptUtility, CDialog)
	ON_BN_CLICKED(IDC_PREFAB_INSTANCES, &CScriptUtility::OnBnClickedPrefabInstances)
	ON_BN_CLICKED(IDC_GAMEOBJECTS, &CScriptUtility::OnBnClickedGameobjects)
	ON_BN_CLICKED(IDC_IMPORTED_CAMERAS, &CScriptUtility::OnBnClickedImportedCameras)
	ON_BN_CLICKED(IDC_RESOURCES, &CScriptUtility::OnBnClickedResources)
	ON_BN_CLICKED(IDC_COPY_VSCENE_NAME, &CScriptUtility::OnBnClickedCopyVsceneName)
	ON_CBN_SELCHANGE(IDC_COMB_PROJECT_NAME, &CScriptUtility::OnCbnSelchangeCombProjectName)
	ON_CBN_SELCHANGE(IDC_COMB_VSCENE_NAME, &CScriptUtility::OnCbnSelchangeCombVsceneName)
	ON_BN_CLICKED(IDC_ALL_GUI_ITEMS, &CScriptUtility::OnBnClickedAllGuiItems)
	ON_BN_CLICKED(IDC_GUIs, &CScriptUtility::OnBnClickedGuis)
	ON_BN_CLICKED(IDOK, &CScriptUtility::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PREFABS, &CScriptUtility::OnBnClickedPrefabs)
END_MESSAGE_MAP()


// CScriptUtility message handlers


void CScriptUtility::OnBnClickedPrefabInstances()
{
	CString projectName;
	CString VSceneName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), VSceneName);

	CScriptUtilityPrefabInstances* dlg = CNew(CScriptUtilityPrefabInstances);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()), VSceneName.GetBuffer(VSceneName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
	VSceneName.ReleaseBuffer();
}


void CScriptUtility::OnBnClickedGameobjects()
{
	CString projectName;
	CString VSceneName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), VSceneName);

	CScriptUtilityGameObjects* dlg = CNew(CScriptUtilityGameObjects);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()), VSceneName.GetBuffer(VSceneName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
	VSceneName.ReleaseBuffer();
}


void CScriptUtility::OnBnClickedImportedCameras()
{
	CString projectName;
	CString VSceneName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), VSceneName);

	CScriptUtilityImportedCameras* dlg = CNew(CScriptUtilityImportedCameras);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()), VSceneName.GetBuffer(VSceneName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
	VSceneName.ReleaseBuffer();
}


void CScriptUtility::OnBnClickedResources()
{
	CString projectName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);

	CScriptUtilityResources* dlg = CNew(CScriptUtilityResources);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
}


void CScriptUtility::OnBnClickedCopyVsceneName()
{
	CString s;
	m_richVSceneName.GetWindowTextA(s);
	m_richVSceneName.Copy();
	CChar message[MAX_URI_SIZE];
	sprintf(message, "VScene '%s' copied to clipboard", s);
	MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);

}


BOOL CScriptUtility::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (CUInt pr = 0; pr < g_projects.size(); pr++)
	{
		m_comboProject.InsertString(pr, g_projects[pr]->m_name);
	}
	if (m_comboProject.GetCount())
		m_comboProject.SetCurSel(0);

	for (CUInt pr = 0; pr < g_projects.size(); pr++)
	{
		if (pr == 0)
		{
			for (CUInt vs = 0; vs < g_projects[pr]->m_sceneNames.size(); vs++)
			{
				CChar VSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(VSceneNameWithoutDot, g_projects[pr]->m_sceneNames[vs].c_str());
				GetWithoutDot(VSceneNameWithoutDot);

				m_comboVScene.InsertString(vs, VSceneNameWithoutDot);
			}
			break;
		}
	}
	if (m_comboVScene.GetCount())
	{
		m_comboVScene.SetCurSel(0);
		CString s;
		m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), s);
		m_richVSceneName.SetWindowTextA(s);
		CInt end = m_richVSceneName.GetWindowTextLengthA();
		m_richVSceneName.SetSel(0, end);

		UpdatePreview();
	}
	else
	{
		m_btnCopyVSceneName.EnableWindow(FALSE);
		m_btnVSceneGameObjects.EnableWindow(FALSE);
		m_btnVSceneGUIs.EnableWindow(FALSE);
		m_btnVSceneImportedCameras.EnableWindow(FALSE);
		m_btnVScenePrefabInstances.EnableWindow(FALSE);

		HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
		if (hOldBitmap)
			DeleteObject(hOldBitmap);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CScriptUtility::OnCbnSelchangeCombProjectName()
{
	CInt curSel = m_comboProject.GetCurSel();
	m_comboVScene.ResetContent();
	for (CUInt vs = 0; vs < g_projects[curSel]->m_sceneNames.size(); vs++)
	{
		CChar VSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy(VSceneNameWithoutDot, g_projects[curSel]->m_sceneNames[vs].c_str());
		GetWithoutDot(VSceneNameWithoutDot);
		m_comboVScene.InsertString(vs, VSceneNameWithoutDot);
	}
	if (m_comboVScene.GetCount())
	{
		m_comboVScene.SetCurSel(0);
		CString s;
		m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), s);
		m_richVSceneName.SetWindowTextA(s);
		CInt end = m_richVSceneName.GetWindowTextLengthA();
		m_richVSceneName.SetSel(0, end);

		m_btnCopyVSceneName.EnableWindow(TRUE);
		m_btnVSceneGameObjects.EnableWindow(TRUE);
		m_btnVSceneGUIs.EnableWindow(TRUE);
		m_btnVSceneImportedCameras.EnableWindow(TRUE);
		m_btnVScenePrefabInstances.EnableWindow(TRUE);

		UpdatePreview();
	}
	else
	{
		m_btnCopyVSceneName.EnableWindow(FALSE);
		m_btnVSceneGameObjects.EnableWindow(FALSE);
		m_btnVSceneGUIs.EnableWindow(FALSE);
		m_btnVSceneImportedCameras.EnableWindow(FALSE);
		m_btnVScenePrefabInstances.EnableWindow(FALSE);

		HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
		if (hOldBitmap)
			DeleteObject(hOldBitmap);
	}

}


void CScriptUtility::OnCbnSelchangeCombVsceneName()
{
	CString s;
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), s);
	m_richVSceneName.SetWindowTextA(s);
	CInt end = m_richVSceneName.GetWindowTextLengthA();
	m_richVSceneName.SetSel(0, end);

	UpdatePreview();
}

void CScriptUtility::OnBnClickedAllGuiItems()
{
	CGUIDlg* dlg = CNew(CGUIDlg);
	dlg->OpenForScriptUtility(CTrue);
	dlg->DoModal();
	CDelete(dlg);
}


void CScriptUtility::OnBnClickedGuis()
{
	CString projectName;
	CString VSceneName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), VSceneName);

	CScriptUtilityGUIs* dlg = CNew(CScriptUtilityGUIs);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()), VSceneName.GetBuffer(VSceneName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
	VSceneName.ReleaseBuffer();
}

CVoid CScriptUtility::UpdatePreview()
{
	DeleteObject(m_hBitmap);
	//get document folder
	CChar docPath[MAX_URI_SIZE];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
	if (result != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder", COLOR_RED);
		return;
	}

	//get project and VScene names
	CString strProjectName;
	CString strVSceneName;
	CChar projectName[MAX_NAME_SIZE];
	CChar VSceneName[MAX_NAME_SIZE];

	m_comboProject.GetLBText(m_comboProject.GetCurSel(), strProjectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), strVSceneName);

	Cpy(projectName, strProjectName.GetBuffer(strProjectName.GetLength()));
	Cpy(VSceneName, strVSceneName.GetBuffer(strVSceneName.GetLength()));

	CChar bitmapPath[MAX_URI_SIZE];
	sprintf(bitmapPath, "%s%s%s%s%s%s%s%s", docPath, "/Vanda/Projects/", projectName, "/", VSceneName, "/", VSceneName, ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);

	strProjectName.ReleaseBuffer();
	strVSceneName.ReleaseBuffer();
}

void CScriptUtility::OnBnClickedOk()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
	CDialog::OnOK();
}


void CScriptUtility::OnBnClickedPrefabs()
{
	CString projectName;
	CString VSceneName;
	m_comboProject.GetLBText(m_comboProject.GetCurSel(), projectName);
	m_comboVScene.GetLBText(m_comboVScene.GetCurSel(), VSceneName);

	CScriptUtilityPrefabs* dlg = CNew(CScriptUtilityPrefabs);
	dlg->SetSelectedProjectAndVSceneNames(projectName.GetBuffer(projectName.GetLength()), VSceneName.GetBuffer(VSceneName.GetLength()));
	dlg->DoModal();
	CDelete(dlg);

	projectName.ReleaseBuffer();
	VSceneName.ReleaseBuffer();
}

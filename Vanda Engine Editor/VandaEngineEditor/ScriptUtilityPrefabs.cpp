//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptUtilityPrefabs.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "ScriptUtilityPrefabs.h"
#include "afxdialogex.h"


// CScriptUtilityPrefabs dialog

IMPLEMENT_DYNAMIC(CScriptUtilityPrefabs, CDialog)

CScriptUtilityPrefabs::CScriptUtilityPrefabs(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityPrefabs::IDD, pParent)
{
	m_prefabIndex = -1;
}

CScriptUtilityPrefabs::~CScriptUtilityPrefabs()
{
	for (CUInt i = 0; i < m_prefabs.size(); i++)
	{
		CDelete(m_prefabs[i]);
	}
	m_prefabs.clear();
	DeleteObject(m_hBitmap);
}

void CScriptUtilityPrefabs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PREFAB_NAMES, m_listPrefabNames);
	DDX_Control(pDX, IDC_RICHED_PREFAB_NAME, m_richSelectedPrefab);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
}


BEGIN_MESSAGE_MAP(CScriptUtilityPrefabs, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_NAME, &CScriptUtilityPrefabs::OnBnClickedButtonCopyPrefabName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_NAMES, &CScriptUtilityPrefabs::OnLvnItemchangedListPrefabNames)
END_MESSAGE_MAP()


// CScriptUtilityPrefabs message handlers


void CScriptUtilityPrefabs::OnBnClickedButtonCopyPrefabName()
{
	CString s;
	m_richSelectedPrefab.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a prefab from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedPrefab.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityPrefabs::OnLvnItemchangedListPrefabNames(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listPrefabNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabNames.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024];

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listPrefabNames.GetItem(&lvi);

		m_richSelectedPrefab.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedPrefab.GetWindowTextLengthA();
		m_richSelectedPrefab.SetSel(0, end);

		for (CUInt i = 0; i < m_prefabs.size(); i++)
		{
			if (Cmp(szBuffer, m_prefabs[i]->GetName()))
			{
				UpdatePreview(m_prefabs[i]);
				break;
			}
		}
	}
	else
	{
		m_richSelectedPrefab.SetWindowTextA("");
		m_richSelectedPrefab.SetSel(0, 0);

		HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
		if (hOldBitmap)
			DeleteObject(hOldBitmap);
	}
	*pResult = 0;
}


BOOL CScriptUtilityPrefabs::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBool foundTarget = CFalse;

	for (CUInt pr = 0; pr < g_projects.size(); pr++)
	{
		if (Cmp(g_projects[pr]->m_name, m_projectName))
		{
			for (CUInt vs = 0; vs < g_projects[pr]->m_sceneNames.size(); vs++)
			{
				CChar VSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(VSceneNameWithoutDot, g_projects[pr]->m_sceneNames[vs].c_str());
				GetWithoutDot(VSceneNameWithoutDot);

				if (Cmp(VSceneNameWithoutDot, m_VSceneName))
				{
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_prefabNames.size(); j++)
					{
						CPrefab* newPrefab = CNew(CPrefab);
						newPrefab->SetName(g_projects[pr]->m_vsceneObjectNames[vs].m_prefabNames[j].m_name);
						newPrefab->SetPackageName(g_projects[pr]->m_vsceneObjectNames[vs].m_prefabNames[j].m_packageName);
						newPrefab->SetPrefabName(g_projects[pr]->m_vsceneObjectNames[vs].m_prefabNames[j].m_prefabName);
						PushPrefab(newPrefab);
					}

					foundTarget = CTrue;
				}
				if (foundTarget)
					break;
			}
		}
		if (foundTarget)
			break;
	}


	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s - VScene: %s", m_projectName, m_VSceneName);
	m_textProjectVSceneName.SetWindowTextA(text);

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_imageList.Create(32, 32, ILC_COLOR24, 1, 1);
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_PREFAB);
	m_imageList.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();
	m_listPrefabNames.SetImageList(&m_imageList, LVSIL_SMALL);

	RECT tempRect;
	m_listPrefabNames.GetClientRect(&tempRect);
	m_listPrefabNames.InsertColumn(0, "Prefabs", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listPrefabNames.ShowWindow(SW_SHOW);
	m_listPrefabNames.UpdateWindow();

	for (CUInt i = 0; i < m_prefabs.size(); i++)
	{
		InsertItemToPrefabList(m_prefabs[i]->GetName());
	}

	if (m_listPrefabNames.GetItemCount())
	{
		m_richSelectedPrefab.SetWindowTextA(m_prefabs[0]->GetName());
		CInt end = m_richSelectedPrefab.GetWindowTextLengthA();
		m_richSelectedPrefab.SetSel(0, end);

		m_listPrefabNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabNames.SetSelectionMark(0);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CScriptUtilityPrefabs::PushPrefab(CPrefab* prefab)
{
	m_prefabs.push_back(prefab);
}

CVoid CScriptUtilityPrefabs::InsertItemToPrefabList(CChar* prefabName)
{
	m_prefabIndex++;
	int index = m_prefabIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.iImage = 0;
	lvItem.pszText = prefabName;
	m_listPrefabNames.InsertItem(&lvItem);

	m_listPrefabNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);
	m_listPrefabNames.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listPrefabNames.SetSelectionMark(index);
	m_listPrefabNames.EnsureVisible(index, FALSE);
	m_listPrefabNames.UpdateWindow();
}

CVoid CScriptUtilityPrefabs::UpdatePreview(CPrefab *prefab)
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

	CChar bitmapPath[MAX_URI_SIZE];
	sprintf(bitmapPath, "%s%s%s%s%s%s%s%s", docPath, "/Vanda/Packages/", prefab->GetPackageName(), "/", prefab->GetPrefabName(), "/", prefab->GetName(), ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);
}

CVoid CScriptUtilityPrefabs::SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName)
{
	Cpy(m_projectName, projectName);
	Cpy(m_VSceneName, VSceneName);
}
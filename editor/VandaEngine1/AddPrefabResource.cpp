//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// AddPrefabResource.cpp : implementation file

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddPrefabResource.h"
#include "afxdialogex.h"

// CAddPrefabResource dialog

IMPLEMENT_DYNAMIC(CAddPrefabResource, CDialog)

CAddPrefabResource::CAddPrefabResource(CWnd* pParent /*=NULL*/)
	: CDialog(CAddPrefabResource::IDD, pParent)
{
	m_prefabIndex = -1;
}

CAddPrefabResource::~CAddPrefabResource()
{
	m_prefabs.clear();
	DeleteObject(m_hBitmap);
}

void CAddPrefabResource::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PREFAB_NAMES, m_listPrefabNames);
	DDX_Control(pDX, IDC_RICHED_PREFAB_NAME, m_richSelectedPrefab);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
}


BEGIN_MESSAGE_MAP(CAddPrefabResource, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PREFAB, &CAddPrefabResource::OnBnClickedButtonAddPrefab)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_PREFAB, &CAddPrefabResource::OnBnClickedButtonRemovePrefab)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_NAME, &CAddPrefabResource::OnBnClickedButtonCopyPrefabName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_NAMES, &CAddPrefabResource::OnLvnItemchangedListPrefabNames)
	ON_BN_CLICKED(IDOK, &CAddPrefabResource::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddPrefabResource message handlers


void CAddPrefabResource::OnBnClickedButtonAddPrefab()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);

	CPrefabDlg* m_dlgPrefabs = CNew(CPrefabDlg);
	m_dlgPrefabs->SetPrefabResourceMode(CTrue);
	if (m_dlgPrefabs->DoModal() == IDOK)
	{
		for (CUInt i = 0; i < m_prefabs.size(); i++)
		{
			if (Cmp(m_dlgPrefabs->GetSelectedPrefab()->GetName(), m_prefabs[i]->GetName()))
			{
				MessageBoxA("This item already exists", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				CDelete(m_dlgPrefabs);
				return;
			}
		}

		CPrefab* newPrefab = CNew(CPrefab);
		newPrefab->SetPackageName(m_dlgPrefabs->GetSelectedPrefab()->GetPackageName());
		newPrefab->SetPrefabName(m_dlgPrefabs->GetSelectedPrefab()->GetPrefabName());
		newPrefab->SetName(m_dlgPrefabs->GetSelectedPrefab()->GetName());

		InsertItemToPrefabList(m_dlgPrefabs->GetSelectedPrefab()->GetName());
		PushPrefab(newPrefab);

		m_richSelectedPrefab.SetWindowTextA(newPrefab->GetName());
		CInt end = m_richSelectedPrefab.GetWindowTextLengthA();
		m_richSelectedPrefab.SetSel(0, end);

		UpdatePreview(newPrefab);
	}
	CDelete(m_dlgPrefabs);

	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
}


void CAddPrefabResource::OnBnClickedButtonRemovePrefab()
{
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

		CChar message[MAX_URI_SIZE];
		sprintf(message, "Delete '%s' ?", szBuffer);
		if (MessageBox(message, "Warning", MB_YESNO | MB_ICONINFORMATION) == IDNO)
			return;

		for (CUInt i = 0; i < m_prefabs.size(); i++)
		{
			if (Cmp(szBuffer, m_prefabs[i]->GetName()))
			{
				CDelete(m_prefabs[i]);
				m_prefabs.erase(m_prefabs.begin() + i);

				m_listPrefabNames.SetItemState(nSelected, 0, LVIS_SELECTED);
				m_richSelectedPrefab.SetWindowTextA("");
				m_richSelectedPrefab.SetSel(0, 0);

				HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
				if (hOldBitmap)
					DeleteObject(hOldBitmap);

				m_listPrefabNames.DeleteItem(nSelected);
				m_prefabIndex--;

				break;
			}
		}
	}
	else
	{
		MessageBox("Please select an item!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
	}
}


void CAddPrefabResource::OnBnClickedButtonCopyPrefabName()
{
	CString s;
	m_richSelectedPrefab.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a prefab from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedPrefab.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


BOOL CAddPrefabResource::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT tempRect;
	m_listPrefabNames.GetClientRect(&tempRect);
	m_listPrefabNames.InsertColumn(0, "Prefab Instances", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listPrefabNames.ShowWindow(SW_SHOW);
	m_listPrefabNames.UpdateWindow();

	for (CUInt i = 0; i < m_prefabs.size(); i++)
	{
		InsertItemToPrefabList(m_prefabs[i]->GetName());
	}

	ModifyStyle(WS_SYSMENU, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddPrefabResource::PushPrefab(CPrefab* prefab)
{
	m_prefabs.push_back(prefab);
}

void CAddPrefabResource::OnLvnItemchangedListPrefabNames(NMHDR *pNMHDR, LRESULT *pResult)
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

CVoid CAddPrefabResource::InsertItemToPrefabList(CChar* prefabName)
{
	m_prefabIndex++;
	int index = m_prefabIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = prefabName;
	m_listPrefabNames.InsertItem(&lvItem);

	m_listPrefabNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);
	m_listPrefabNames.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listPrefabNames.SetSelectionMark(index);
	m_listPrefabNames.EnsureVisible(index, FALSE);
	m_listPrefabNames.UpdateWindow();
}

CVoid CAddPrefabResource::UpdatePreview(CPrefab *prefab)
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

void CAddPrefabResource::OnBnClickedOk()
{
	g_resourcePrefab.clear();
	for (CUInt i = 0; i < m_prefabs.size(); i++)
	{
		g_resourcePrefab.push_back(m_prefabs[i]);
	}

	CDialog::OnOK();
}

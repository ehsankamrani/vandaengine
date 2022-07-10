//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptUtilityPrefabInstances.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtilityPrefabInstances.h"
#include "afxdialogex.h"


// CScriptUtilityPrefabInstances dialog

IMPLEMENT_DYNAMIC(CScriptUtilityPrefabInstances, CDialog)

CScriptUtilityPrefabInstances::CScriptUtilityPrefabInstances(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityPrefabInstances::IDD, pParent)
{

}

CScriptUtilityPrefabInstances::~CScriptUtilityPrefabInstances()
{
}

void CScriptUtilityPrefabInstances::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_NAME, m_richSelectedPrefabInstance);
	DDX_Control(pDX, IDC_LIST_PREFAB_INSTANCES, m_listPrefabInstanceNames);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_ANIMATION_NAME, m_richSelectedAnimationName);
	DDX_Control(pDX, IDC_LIST_PREFAB_INSTANCE_ANIMATIONS, m_listPrefabInstanceAnimationNames);
	DDX_Control(pDX, IDC_RICHED_PREFAB_INSTANCE_CAMERA_NAME, m_richSelectedCameraName);
	DDX_Control(pDX, IDC_LIST_PREFAB_INSTANCE_CAMERAS, m_listPrefabInstanceCameraNames);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
}


BEGIN_MESSAGE_MAP(CScriptUtilityPrefabInstances, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_NAME, &CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_INSTANCES, &CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstances)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_ANIMATION_NAME, &CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceAnimationName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_INSTANCE_ANIMATIONS, &CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstanceAnimations)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PREFAB_INSTANCE_CAMERAS, &CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstanceCameras)
	ON_BN_CLICKED(IDC_BUTTON_COPY_PREFAB_INSTANCE_CAMERA_NAME, &CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceCameraName)
END_MESSAGE_MAP()

CVoid CScriptUtilityPrefabInstances::SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName)
{
	Cpy(m_projectName, projectName);
	Cpy(m_VSceneName, VSceneName);
}

// CScriptUtilityPrefabInstances message handlers


void CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceName()
{
	CString s;
	m_richSelectedPrefabInstance.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a prefab instance from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedPrefabInstance.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


BOOL CScriptUtilityPrefabInstances::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s - VScene: %s", m_projectName, m_VSceneName);
	m_textProjectVSceneName.SetWindowTextA(text);

	RECT tempRect;
	m_listPrefabInstanceNames.GetClientRect(&tempRect);
	m_listPrefabInstanceNames.InsertColumn(0, "Prefab Instances", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listPrefabInstanceNames.ShowWindow(SW_SHOW);
	m_listPrefabInstanceNames.UpdateWindow();

	RECT tempAnimationRect;
	m_listPrefabInstanceAnimationNames.GetClientRect(&tempAnimationRect);
	m_listPrefabInstanceAnimationNames.InsertColumn(0, "Prefab Animations", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempAnimationRect.right - tempAnimationRect.left) * 90 / 100);
	m_listPrefabInstanceAnimationNames.ShowWindow(SW_SHOW);
	m_listPrefabInstanceAnimationNames.UpdateWindow();

	RECT tempCameraRect;
	m_listPrefabInstanceCameraNames.GetClientRect(&tempCameraRect);
	m_listPrefabInstanceCameraNames.InsertColumn(0, "Prefab Cameras", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempCameraRect.right - tempCameraRect.left) * 90 / 100);
	m_listPrefabInstanceCameraNames.ShowWindow(SW_SHOW);
	m_listPrefabInstanceCameraNames.UpdateWindow();

	CInt PrefabInstanceIndex = -1;
	CInt prefabInstanceAnimationIndex = -1;
	CInt prefabInstanceCameraIndex = -1;
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
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames.size(); j++)
					{
						PrefabInstanceIndex++;
						int index = PrefabInstanceIndex;
						LVITEM lvItem;
						lvItem.mask = LVIF_TEXT;
						lvItem.iItem = index;
						lvItem.iSubItem = 0;
						lvItem.pszText = g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_name;
						m_listPrefabInstanceNames.InsertItem(&lvItem);
						m_listPrefabInstanceNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

						m_listPrefabInstanceNames.EnsureVisible(index, FALSE);
						m_listPrefabInstanceNames.UpdateWindow();

						if (PrefabInstanceIndex == 0)
						{
							for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[0].m_animationNames.size(); k++)
							{
								prefabInstanceAnimationIndex++;
								int index = prefabInstanceAnimationIndex;
								LVITEM lvItem;
								lvItem.mask = LVIF_TEXT;
								lvItem.iItem = index;
								lvItem.iSubItem = 0;
								lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[0].m_animationNames[k].c_str();
							    m_listPrefabInstanceAnimationNames.InsertItem(&lvItem);
								m_listPrefabInstanceAnimationNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

								m_listPrefabInstanceAnimationNames.EnsureVisible(index, FALSE);
								m_listPrefabInstanceAnimationNames.UpdateWindow();

								if (k == 0)
								{
									m_richSelectedAnimationName.SetWindowTextA(lvItem.pszText);
									CInt end = m_richSelectedAnimationName.GetWindowTextLengthA();
									m_richSelectedAnimationName.SetSel(0, end);
								}
							}

							for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[0].m_cameraNames.size(); k++)
							{
								prefabInstanceCameraIndex++;
								int index = prefabInstanceCameraIndex;
								LVITEM lvItem;
								lvItem.mask = LVIF_TEXT;
								lvItem.iItem = index;
								lvItem.iSubItem = 0;
								lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[0].m_cameraNames[k].c_str();
								m_listPrefabInstanceCameraNames.InsertItem(&lvItem);
								m_listPrefabInstanceCameraNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

								m_listPrefabInstanceCameraNames.EnsureVisible(index, FALSE);
								m_listPrefabInstanceCameraNames.UpdateWindow();

								if (k == 0)
								{
									m_richSelectedCameraName.SetWindowTextA(lvItem.pszText);
									CInt end = m_richSelectedCameraName.GetWindowTextLengthA();
									m_richSelectedCameraName.SetSel(0, end);
								}
							}

							m_richSelectedPrefabInstance.SetWindowTextA(lvItem.pszText);
							CInt end = m_richSelectedPrefabInstance.GetWindowTextLengthA();
							m_richSelectedPrefabInstance.SetSel(0, end);
						}
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
	if (m_listPrefabInstanceNames.GetItemCount())
	{
		m_listPrefabInstanceNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceNames.SetSelectionMark(0);
	}

	if (m_listPrefabInstanceAnimationNames.GetItemCount())
	{
		m_listPrefabInstanceAnimationNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceAnimationNames.SetSelectionMark(0);
	}

	if (m_listPrefabInstanceCameraNames.GetItemCount())
	{
		m_listPrefabInstanceCameraNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceCameraNames.SetSelectionMark(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstances(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	//Animations
	for (int nItem = m_listPrefabInstanceAnimationNames.GetItemCount() - 1; nItem >= 0; nItem--)
	{
		m_listPrefabInstanceAnimationNames.DeleteItem(nItem);
	}

	//Cameras
	for (int nItem = m_listPrefabInstanceCameraNames.GetItemCount() - 1; nItem >= 0; nItem--)
	{
		m_listPrefabInstanceCameraNames.DeleteItem(nItem);
	}

	int nSelected = -1;
	POSITION p = m_listPrefabInstanceNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabInstanceNames.GetNextSelectedItem(p);
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
		m_listPrefabInstanceNames.GetItem(&lvi);

		m_richSelectedPrefabInstance.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedPrefabInstance.GetWindowTextLengthA();
		m_richSelectedPrefabInstance.SetSel(0, end);

		CInt prefabInstanceAnimationIndex = -1;
		CInt prefabInstanceCameraIndex = -1;
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
						for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames.size(); j++)
						{
							if (Cmp(szBuffer, g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_name))
							{
								Cpy(m_currentPackageName, g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_packageName);
								Cpy(m_currentPrefabName, g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_prefabName);
								for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_animationNames.size(); k++)
								{
									prefabInstanceAnimationIndex++;
									int index = prefabInstanceAnimationIndex;
									LVITEM lvItem;
									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = index;
									lvItem.iSubItem = 0;
									lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_animationNames[k].c_str();
									m_listPrefabInstanceAnimationNames.InsertItem(&lvItem);
									m_listPrefabInstanceAnimationNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

									m_listPrefabInstanceAnimationNames.EnsureVisible(index, FALSE);
									m_listPrefabInstanceAnimationNames.UpdateWindow();

									if (k == 0)
									{
										m_richSelectedAnimationName.SetWindowTextA(lvItem.pszText);
										CInt end = m_richSelectedAnimationName.GetWindowTextLengthA();
										m_richSelectedAnimationName.SetSel(0, end);
									}
								}

								for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_cameraNames.size(); k++)
								{
									prefabInstanceCameraIndex++;
									int index = prefabInstanceCameraIndex;
									LVITEM lvItem;
									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = index;
									lvItem.iSubItem = 0;
									lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_instancePrefabNames[j].m_cameraNames[k].c_str();
									m_listPrefabInstanceCameraNames.InsertItem(&lvItem);
									m_listPrefabInstanceCameraNames.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

									m_listPrefabInstanceCameraNames.EnsureVisible(index, FALSE);
									m_listPrefabInstanceCameraNames.UpdateWindow();

									if (k == 0)
									{
										m_richSelectedCameraName.SetWindowTextA(lvItem.pszText);
										CInt end = m_richSelectedCameraName.GetWindowTextLengthA();
										m_richSelectedCameraName.SetSel(0, end);
									}
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
			}
			if (foundTarget)
				break;
		}
		UpdatePreview();
	}
	else
	{
		m_richSelectedPrefabInstance.SetWindowTextA("");
		m_richSelectedPrefabInstance.SetSel(0, 0);

		m_richSelectedAnimationName.SetWindowTextA("");
		m_richSelectedAnimationName.SetSel(0, 0);

		m_richSelectedCameraName.SetWindowTextA("");
		m_richSelectedCameraName.SetSel(0, 0);

		HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
		if (hOldBitmap)
			DeleteObject(hOldBitmap);
	}

	if (m_listPrefabInstanceAnimationNames.GetItemCount())
	{
		m_listPrefabInstanceAnimationNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceAnimationNames.SetSelectionMark(0);
	}

	if (m_listPrefabInstanceCameraNames.GetItemCount())
	{
		m_listPrefabInstanceCameraNames.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listPrefabInstanceCameraNames.SetSelectionMark(0);
	}

	*pResult = 0;
}


void CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceAnimationName()
{
	CString s;
	m_richSelectedAnimationName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select an animation from the list (if exists)!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedAnimationName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstanceAnimations(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listPrefabInstanceAnimationNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabInstanceAnimationNames.GetNextSelectedItem(p);
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
		m_listPrefabInstanceAnimationNames.GetItem(&lvi);
		*pResult = 0;

		m_richSelectedAnimationName.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedAnimationName.GetWindowTextLengthA();
		m_richSelectedAnimationName.SetSel(0, end);
	}
	else
	{
		m_richSelectedAnimationName.SetWindowTextA("");
		m_richSelectedAnimationName.SetSel(0, 0);
	}
}


void CScriptUtilityPrefabInstances::OnLvnItemchangedListPrefabInstanceCameras(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listPrefabInstanceCameraNames.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listPrefabInstanceCameraNames.GetNextSelectedItem(p);
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
		m_listPrefabInstanceCameraNames.GetItem(&lvi);
		*pResult = 0;

		m_richSelectedCameraName.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedCameraName.GetWindowTextLengthA();
		m_richSelectedCameraName.SetSel(0, end);
	}
	else
	{
		m_richSelectedCameraName.SetWindowTextA("");
		m_richSelectedCameraName.SetSel(0, 0);
	}

	*pResult = 0;
}


void CScriptUtilityPrefabInstances::OnBnClickedButtonCopyPrefabInstanceCameraName()
{
	CString s;
	m_richSelectedCameraName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a camera from the list (if exists)!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedCameraName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}

CVoid CScriptUtilityPrefabInstances::UpdatePreview()
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
	sprintf(bitmapPath, "%s%s%s%s%s%s%s%s%s%s", docPath, "/Vanda/Packages/", m_currentPackageName, "/", m_currentPrefabName, "/", m_currentPackageName, "_", m_currentPrefabName, ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);
}
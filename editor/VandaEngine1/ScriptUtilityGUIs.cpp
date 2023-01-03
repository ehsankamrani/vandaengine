//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ScriptUtilityGUIs.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptUtilityGUIs.h"
#include "afxdialogex.h"


// CScriptUtilityGUIs dialog

IMPLEMENT_DYNAMIC(CScriptUtilityGUIs, CDialog)

CScriptUtilityGUIs::CScriptUtilityGUIs(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptUtilityGUIs::IDD, pParent)
{

}

CScriptUtilityGUIs::~CScriptUtilityGUIs()
{
}

void CScriptUtilityGUIs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_GUI_NAME, m_richGUIName);
	DDX_Control(pDX, IDC_LIST_GUIS, m_listGUI);
	DDX_Control(pDX, IDC_STATIC_PROJECT_VSCENE_NAME, m_textProjectVSceneName);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
	DDX_Control(pDX, IDC_LIST_GUI_ELEMENT, m_listSelectedGUIElement);
	DDX_Control(pDX, IDC_RICHED_GUI_ELEMENT, m_richSelectedGUIElement);
}


BEGIN_MESSAGE_MAP(CScriptUtilityGUIs, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_GUI_NAME, &CScriptUtilityGUIs::OnBnClickedButtonCopyGuiName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_GUIS, &CScriptUtilityGUIs::OnLvnItemchangedListGuis)
	ON_BN_CLICKED(IDC_BUTTON_COPY_GUI_ELEMENT_NAME, &CScriptUtilityGUIs::OnBnClickedButtonCopyGuiElementName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_GUI_ELEMENT, &CScriptUtilityGUIs::OnLvnItemchangedListGuiElement)
END_MESSAGE_MAP()


// CScriptUtilityGUIs message handlers


void CScriptUtilityGUIs::OnBnClickedButtonCopyGuiName()
{
	CString s;
	m_richGUIName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a GUI item from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richGUIName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityGUIs::OnLvnItemchangedListGuis(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	//Animations
	for (int nItem = m_listSelectedGUIElement.GetItemCount() - 1; nItem >= 0; nItem--)
	{
		m_listSelectedGUIElement.DeleteItem(nItem);
	}

	int nSelected = -1;
	POSITION p = m_listGUI.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUI.GetNextSelectedItem(p);
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
		m_listGUI.GetItem(&lvi);

		m_richGUIName.SetWindowTextA(szBuffer);
		CInt end = m_richGUIName.GetWindowTextLengthA();
		m_richGUIName.SetSel(0, end);

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
						for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames.size(); j++)
						{
							if (Cmp(szBuffer, g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_name))
							{
								Cpy(m_currentGUIPackageName, g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_guiPackageName);
								Cpy(m_currentGUIName, g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_guiPureName);

								CInt GUIElementsIndex = -1;

								for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_buttonNames.size(); k++)
								{
									GUIElementsIndex++;
									int index = GUIElementsIndex;
									LVITEM lvItem;
									lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
									lvItem.iItem = index;
									lvItem.iSubItem = 0;
									lvItem.iImage = 0;
									lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_buttonNames[k].c_str();
									m_listSelectedGUIElement.InsertItem(&lvItem);
									m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

									m_listSelectedGUIElement.EnsureVisible(index, FALSE);
									m_listSelectedGUIElement.UpdateWindow();

									if (GUIElementsIndex == 0)
									{
										m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
										CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
										m_richSelectedGUIElement.SetSel(0, end);
									}
								}

								for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_imageNames.size(); k++)
								{
									GUIElementsIndex++;
									int index = GUIElementsIndex;
									LVITEM lvItem;
									lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
									lvItem.iItem = index;
									lvItem.iSubItem = 0;
									lvItem.iImage = 1;
									lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_imageNames[k].c_str();
									m_listSelectedGUIElement.InsertItem(&lvItem);
									m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

									m_listSelectedGUIElement.EnsureVisible(index, FALSE);
									m_listSelectedGUIElement.UpdateWindow();

									if (GUIElementsIndex == 0)
									{
										m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
										CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
										m_richSelectedGUIElement.SetSel(0, end);
									}
								}

								for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_textNames.size(); k++)
								{
									GUIElementsIndex++;
									int index = GUIElementsIndex;
									LVITEM lvItem;
									lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
									lvItem.iItem = index;
									lvItem.iSubItem = 0;
									lvItem.iImage = 2;
									lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_textNames[k].c_str();
									m_listSelectedGUIElement.InsertItem(&lvItem);
									m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

									m_listSelectedGUIElement.EnsureVisible(index, FALSE);
									m_listSelectedGUIElement.UpdateWindow();

									if (GUIElementsIndex == 0)
									{
										m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
										CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
										m_richSelectedGUIElement.SetSel(0, end);
									}
								}

								break;
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

		UpdatePreview();

	}
	else
	{
		m_richGUIName.SetWindowTextA("");
		m_richGUIName.SetSel(0, 0);

		HBITMAP hOldBitmap = m_imageCtrl.SetBitmap(NULL);
		if (hOldBitmap)
			DeleteObject(hOldBitmap);
	}

	if (m_listSelectedGUIElement.GetItemCount())
	{
		m_listSelectedGUIElement.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listSelectedGUIElement.SetSelectionMark(0);
	}

	*pResult = 0;
}

BOOL CScriptUtilityGUIs::OnInitDialog()
{
	CDialog::OnInitDialog();

	CChar text[MAX_NAME_SIZE];
	sprintf(text, "Project: %s - VScene: %s", m_projectName, m_VSceneName);
	m_textProjectVSceneName.SetWindowTextA(text);

	RECT tempGUIElementRect;
	m_listSelectedGUIElement.GetClientRect(&tempGUIElementRect);
	m_listSelectedGUIElement.InsertColumn(0, "GUI Elements", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempGUIElementRect.right - tempGUIElementRect.left) * 90 / 100);
	m_listSelectedGUIElement.ShowWindow(SW_SHOW);
	m_listSelectedGUIElement.UpdateWindow();

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;

	m_GUIElementsImage.Create(32, 32, ILC_COLOR24, 10, 10);
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_GUI_BUTTON);
	m_GUIElementsImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_GUI_IMAGE);
	m_GUIElementsImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();
	cBmp.LoadBitmap(IDB_BITMAP_SCRIPT_UTILITY_GUI_TEXT);
	m_GUIElementsImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listSelectedGUIElement.SetImageList(&m_GUIElementsImage, LVSIL_SMALL);

	RECT tempRect;
	m_listGUI.GetClientRect(&tempRect);
	m_listGUI.InsertColumn(0, "GUIs", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listGUI.ShowWindow(SW_SHOW);
	m_listGUI.UpdateWindow();

	CInt GUIIndex = -1;
	CInt GUIElementsIndex = -1;

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
					for (CUInt j = 0; j < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames.size(); j++)
					{
						GUIIndex++;
						int index = GUIIndex;
						LVITEM lvItem;
						lvItem.mask = LVIF_TEXT;
						lvItem.iItem = index;
						lvItem.iSubItem = 0;
						lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_name;
						m_listGUI.InsertItem(&lvItem);
						m_listGUI.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

						m_listGUI.EnsureVisible(index, FALSE);
						m_listGUI.UpdateWindow();

						if (GUIIndex == 0)
						{
							for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_buttonNames.size(); k++)
							{
								GUIElementsIndex++;
								int index = GUIElementsIndex;
								LVITEM lvItem;
								lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
								lvItem.iItem = index;
								lvItem.iSubItem = 0;
								lvItem.iImage = 0;
								lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_buttonNames[k].c_str();
								m_listSelectedGUIElement.InsertItem(&lvItem);
								m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

								m_listSelectedGUIElement.EnsureVisible(index, FALSE);
								m_listSelectedGUIElement.UpdateWindow();

								if (GUIElementsIndex == 0)
								{
									m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
									CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
									m_richSelectedGUIElement.SetSel(0, end);
								}
							}

							for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_imageNames.size(); k++)
							{
								GUIElementsIndex++;
								int index = GUIElementsIndex;
								LVITEM lvItem;
								lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
								lvItem.iItem = index;
								lvItem.iSubItem = 0;
								lvItem.iImage = 1;
								lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_imageNames[k].c_str();
								m_listSelectedGUIElement.InsertItem(&lvItem);
								m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

								m_listSelectedGUIElement.EnsureVisible(index, FALSE);
								m_listSelectedGUIElement.UpdateWindow();

								if (GUIElementsIndex == 0)
								{
									m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
									CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
									m_richSelectedGUIElement.SetSel(0, end);
								}
							}

							for (CUInt k = 0; k < g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_textNames.size(); k++)
							{
								GUIElementsIndex++;
								int index = GUIElementsIndex;
								LVITEM lvItem;
								lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
								lvItem.iItem = index;
								lvItem.iSubItem = 0;
								lvItem.iImage = 2;
								lvItem.pszText = (CChar*)g_projects[pr]->m_vsceneObjectNames[vs].m_guiNames[j].m_textNames[k].c_str();
								m_listSelectedGUIElement.InsertItem(&lvItem);
								m_listSelectedGUIElement.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

								m_listSelectedGUIElement.EnsureVisible(index, FALSE);
								m_listSelectedGUIElement.UpdateWindow();

								if (GUIElementsIndex == 0)
								{
									m_richSelectedGUIElement.SetWindowTextA(lvItem.pszText);
									CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
									m_richSelectedGUIElement.SetSel(0, end);
								}
							}

							m_richGUIName.SetWindowTextA(lvItem.pszText);
							CInt end = m_richGUIName.GetWindowTextLengthA();
							m_richGUIName.SetSel(0, end);
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

	if (m_listGUI.GetItemCount())
	{
		m_listGUI.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listGUI.SetSelectionMark(0);
	}

	if (m_listSelectedGUIElement.GetItemCount())
	{
		m_listSelectedGUIElement.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listSelectedGUIElement.SetSelectionMark(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptUtilityGUIs::SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName)
{
	Cpy(m_projectName, projectName);
	Cpy(m_VSceneName, VSceneName);
}

CVoid CScriptUtilityGUIs::UpdatePreview()
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
	sprintf(bitmapPath, "%s%s%s%s%s%s%s%s%s%s", docPath, "/Vanda/GUIs/", m_currentGUIPackageName, "/", m_currentGUIName, "/", m_currentGUIPackageName, "_", m_currentGUIName, ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);

}

void CScriptUtilityGUIs::OnBnClickedButtonCopyGuiElementName()
{
	CString s;
	m_richSelectedGUIElement.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Please select a GUI element from the list!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richSelectedGUIElement.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "Item '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}


void CScriptUtilityGUIs::OnLvnItemchangedListGuiElement(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listSelectedGUIElement.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listSelectedGUIElement.GetNextSelectedItem(p);
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
		m_listSelectedGUIElement.GetItem(&lvi);
		*pResult = 0;

		m_richSelectedGUIElement.SetWindowTextA(szBuffer);
		CInt end = m_richSelectedGUIElement.GetWindowTextLengthA();
		m_richSelectedGUIElement.SetSel(0, end);
	}
	else
	{
		m_richSelectedGUIElement.SetWindowTextA("");
		m_richSelectedGUIElement.SetSel(0, 0);
	}
}

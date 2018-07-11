//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license


// GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "GUIDlg.h"
#include "afxdialogex.h"


// CGUIDlg dialog

IMPLEMENT_DYNAMIC(CGUIDlg, CDialog)

CGUIDlg::CGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGUIDlg::IDD, pParent)
{
	m_packageIndex = -1;
	m_guiIndex = -1;

}

CGUIDlg::~CGUIDlg()
{
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PACKAGES, m_listGUIPackages);
	DDX_Control(pDX, IDC_LIST_GUIS, m_listGUIs);
	DDX_Control(pDX, ID_INSERT, m_btnInsertGUI);
}


BEGIN_MESSAGE_MAP(CGUIDlg, CDialog)
	ON_BN_CLICKED(ID_INSERT, &CGUIDlg::OnBnClickedInsert)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PACKAGES, &CGUIDlg::OnLvnItemchangedListPackages)
	ON_BN_CLICKED(IDOK, &CGUIDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGUIDlg message handlers


void CGUIDlg::OnBnClickedInsert()
{
	if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		if (MessageBox("You can not insert GUIs in Play Mode. Exit from play mode?", "Vanda Engine Error", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			ex_pVandaEngine1Dlg->OnBnClickedBtnPlayActive();

		}
		else
		{
			return;
		}
	}

	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);
	if (g_editorMode == eMODE_GUI)
		ex_pVandaEngine1Dlg->OnMenuClickedOpenGUI();
	else if (g_editorMode == eMODE_VSCENE)
		ex_pVandaEngine1Dlg->OnMenuClickedInsertGUI();
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);

	g_multipleView->SetElapsedTimeFromBeginning();

}


BOOL CGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (g_editorMode == eMODE_GUI)
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU4);
		SetMenu(&menu);
		menu.Detach();
	}

	if (g_editorMode == eMODE_VSCENE)
	{
		m_btnInsertGUI.SetWindowTextA("Insert GUI");
	}
	else
	{
		m_btnInsertGUI.SetWindowTextA("Open GUI");
	}

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_packageListImage.Create(36, 36, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_PACKAGE);
	m_packageListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	RECT tempRect;
	m_listGUIPackages.GetClientRect(&tempRect);
	m_listGUIPackages.SetImageList(&m_packageListImage, LVSIL_SMALL);
	m_listGUIPackages.InsertColumn(0, "Packages", LVCFMT_CENTER | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listGUIPackages.ShowWindow(SW_SHOW);
	m_listGUIPackages.UpdateWindow();

	m_guiListImage.Create(80, 80, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_GUI);
	m_guiListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listGUIs.SetImageList(&m_guiListImage, LVSIL_NORMAL);

	m_listGUIs.GetClientRect(&tempRect);
	m_listGUIs.InsertColumn(0, "GUIs", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listGUIs.ShowWindow(SW_SHOW);
	m_listGUIs.UpdateWindow();

	//insert items
	for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_guiPackagesAndNames[i].front().c_str());
		InsertItemToPackageList(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CGUIDlg::InsertItemToPackageList(CChar* packageName)
{
	m_packageIndex++;
	int index = m_packageIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iImage = 0;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = packageName;
	m_listGUIPackages.InsertItem(&lvItem);

	m_listGUIPackages.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);
	m_listGUIPackages.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listGUIPackages.SetSelectionMark(index);
	m_listGUIPackages.EnsureVisible(index, FALSE);
	m_listGUIPackages.UpdateWindow();
}

CVoid CGUIDlg::InsertItemToGUIList(CChar* guiName)
{
	m_guiIndex++;
	int index = m_guiIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iImage = 0;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = guiName;
	m_listGUIs.InsertItem(&lvItem);

	m_listGUIs.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);
	m_listGUIs.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listGUIs.SetSelectionMark(index);
	m_listGUIs.EnsureVisible(index, FALSE);
	m_listGUIs.UpdateWindow();
}

void CGUIDlg::OnLvnItemchangedListPackages(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//remove the current contents of the gui list
	for (int nItem = m_listGUIs.GetItemCount() - 1; nItem >= 0; nItem--)
	{
		m_listGUIs.DeleteItem(nItem);
	}
	m_listGUIs.UpdateWindow();
	m_guiIndex = -1; //reset gui index

	int nSelected = -1;
	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);
		m_selectedGUIName = szBuffer;
	}
	else
	{
		return;
	}
	CInt index = -1;
	for (CInt i = 0; i < (CInt)g_guiPackagesAndNames.size(); i++)
	{
		if (Cmp(g_guiPackagesAndNames[i].front().c_str(), m_selectedGUIName.c_str()))
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		for (CUInt i = 0; i < g_guiPackagesAndNames[index].size(); i++)
		{
			if (i == 0) continue;
			CChar str[MAX_NAME_SIZE];
			Cpy(str, g_guiPackagesAndNames[index][i].c_str());
			InsertItemToGUIList(str);
		}
	}
	*pResult = 0;
}


BOOL CGUIDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	CBool OpenGUI = CFalse;
	if (wParam == ID_PACKAGE_NEW)
	{
		OnBnClickedNewPackage();
	}
	else if (wParam == ID_PACKAGE_DELETESELECTED)
	{
		OnBnClickedDeletePackage();
	}
	else if (wParam == ID_PACKAGE_RENAMESELECTED)
	{
		OnBnClickedRenamePackage();
	}
	else if (wParam == ID_GUI_NEW)
	{
		OnBnClickedNewGUI();
	}
	else if (wParam == ID_GUI_DELETESELECTED)
	{
		OnBnClickedDeleteGUI();
	}
	else if (wParam == ID_GUI_RENAMESELECTED)
	{
		OnBnClickedRenameGUI();
	}
	else if (wParam == ID_GUI_OPENSELECTED)
	{
		OpenGUI = CTrue;
		OnBnClickedInsert();
	}
	if (!OpenGUI)
		ex_pVandaEngine1Dlg->SaveGUIFiles();

	return CDialog::OnCommand(wParam, lParam);
}

void CGUIDlg::OnBnClickedNewPackage()
{
	m_guiNameDlg = CNew(CGUINameDlg);
	m_guiNameDlg->SetInitialData("\n", "\n", CTrue);
	if (IDOK == m_guiNameDlg->DoModal())
		InsertItemToPackageList(m_guiNameDlg->GetNewName());
	CDelete(m_guiNameDlg);
}

void CGUIDlg::OnBnClickedNewGUI()
{
	int nSelected = -1;
	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);
		m_selectedPackageName = szBuffer;
	}
	else
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}


	m_guiNameDlg = CNew(CGUINameDlg);
	m_guiNameDlg->SetInitialData(m_selectedPackageName, "\n", CFalse);
	if (IDOK == m_guiNameDlg->DoModal())
		InsertItemToGUIList(m_guiNameDlg->GetNewName());
	else
		return;

	CChar dlgGUIName[MAX_NAME_SIZE];
	Cpy(dlgGUIName, m_guiNameDlg->GetNewName());

	//Create All Directories
	CChar docPath[MAX_NAME_SIZE];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
	if (result != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
		return;
	}
	CChar newPackage[MAX_NAME_SIZE];
	sprintf(newPackage, "%s%s%s%s", docPath, "/Vanda/GUIs/", m_selectedPackageName.c_str(), "/");

	CChar newGUIName[MAX_NAME_SIZE];
	sprintf(newGUIName, "%s%s", newPackage, dlgGUIName);

	CChar newExternalTexturesPath[MAX_NAME_SIZE];
	sprintf(newExternalTexturesPath, "%s%s", newGUIName, "/Textures/");

	CChar newExternalBackgroundTexturesPath[MAX_NAME_SIZE];
	sprintf(newExternalBackgroundTexturesPath, "%s%s", newExternalTexturesPath, "Backgrounds/");

	CChar newExternalButtonTexturesPath[MAX_NAME_SIZE];
	sprintf(newExternalButtonTexturesPath, "%s%s", newExternalTexturesPath, "Buttons/");

	CChar newScriptPath[MAX_NAME_SIZE];
	sprintf(newScriptPath, "%s%s", newGUIName, "/Scripts/");

	CChar m_strNewPackageAndGUIName[MAX_NAME_SIZE];
	sprintf(m_strNewPackageAndGUIName, "%s%s%s", m_selectedPackageName.c_str(), "_", dlgGUIName);

	//create a new directory based on the save file name
	CreateWindowsDirectory(newPackage);
	CreateWindowsDirectory(newGUIName);
	CreateWindowsDirectory(newExternalTexturesPath);
	CreateWindowsDirectory(newExternalBackgroundTexturesPath);
	CreateWindowsDirectory(newExternalButtonTexturesPath);
	CreateWindowsDirectory(newScriptPath);

	//Save functions////////////////////////////////////
	CChar fileName[MAX_NAME_SIZE];
	sprintf(fileName, "%s%s%s%s", newGUIName, "/", m_strNewPackageAndGUIName, ".gui");
	FILE *filePtr;
	filePtr = fopen(fileName, "wb");
	if (!filePtr)
	{
		//fclose( filePtr );
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "Couldn't open the file '", fileName, "' to save data");
		MessageBox(temp, "Vanda Engine Error", MB_OK);
		return;
	}
	//save data here
	CUInt numberOfGUIButtons = 0;
	fwrite(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

	CUInt numberOfGUIBackgrounds = 0;
	fwrite(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

	CUInt numberOfGUITexts = 0;
	fwrite(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

	////////////////
	fclose(filePtr);

	//save functions////////////////////////////////////////

	CDelete(m_guiNameDlg);
}

void CGUIDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

CVoid CGUIDlg::OnBnClickedDeletePackage()
{
	int nSelected = -1;
	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		TCHAR szBuffer[1024];
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);

		m_selectedPackageName = szBuffer;

		for (CUInt i = 0; i < g_projects.size(); i++)
		{
			for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
			{
				//find pkg file
				CChar pkgPath[MAX_NAME_SIZE];
				CChar sceneWithoutDot[MAX_NAME_SIZE];
				Cpy(sceneWithoutDot, g_projects[i]->m_sceneNames[j].c_str());
				GetWithoutDot(sceneWithoutDot);
				sprintf(pkgPath, "%s%s%s%s%s", g_projectsPath, g_projects[i]->m_name, "/", sceneWithoutDot, "/guis.pkg");
				//copy package names
				FILE *PackageFilePtr;
				PackageFilePtr = fopen(pkgPath, "rb");
				if (!PackageFilePtr)
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf(temp, "%s%s%s", "Couldn't open the file '", pkgPath, "' to load data");
					MessageBox(temp, "Vanda Engine Error", MB_OK);
					ReleaseCapture();
					PrintInfo("Delete failed.", COLOR_RED);
					return;
				}
				CUInt size = -1;
				fread(&size, sizeof(CUInt), 1, PackageFilePtr);
				for (CUInt k = 0; k < size; k++)
				{
					CChar name[MAX_NAME_SIZE];
					CChar package_name[MAX_NAME_SIZE];
					CChar gui_name[MAX_NAME_SIZE];
					//write gui data
					fread(name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(package_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(gui_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);

					if (Cmp(package_name, m_selectedPackageName.c_str()))
					{
						CChar packageName[MAX_NAME_SIZE];
						sprintf(packageName, "This package is used by %s/%s.\nYou can not delete this package.", g_projects[i]->m_name, g_projects[i]->m_sceneNames[j].c_str());
						MessageBox(packageName, "Vanda Engine Error", MB_OK | MB_ICONERROR);
						fclose(PackageFilePtr);
						return;
					}
				}
				fclose(PackageFilePtr);
			}
		}

		CChar currentPackageName[MAX_NAME_SIZE];
		sprintf(currentPackageName, "%s", szBuffer);
		if (Cmp(g_currentGUIPackageName, currentPackageName))
		{
			MessageBox("current open GUI belongs to selected package. Please close current GUI scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}

		if (MessageBox("Are you sure you want to delete this package?", "Warning", MB_YESNO) == IDYES)
		{
			CChar PackagePath[MAX_NAME_SIZE];
			HRESULT doc_result_package = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, PackagePath);
			if (doc_result_package != S_OK)
			{
				PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
				return;
			}
			else
			{
				Append(PackagePath, "/Vanda/GUIs/");
			}
			CChar path[MAX_NAME_SIZE];
			sprintf(path, "%s%s", PackagePath, szBuffer);

			RemoveAllFilesAndFoldersInDirectory(path);

			//remove pkg file in PKG folder
			CChar PKG_old[MAX_URI_SIZE];
			sprintf(PKG_old, "%s%s%s%s", PackagePath, "PKG/", szBuffer, ".gui");
			DeleteFile(PKG_old);

			//delete items from std::vector
			for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
			{
				if (Cmp(g_guiPackagesAndNames[i].front().c_str(), m_selectedPackageName.c_str()))
				{
					g_guiPackagesAndNames[i].clear();
					g_guiPackagesAndNames.erase(g_guiPackagesAndNames.begin() + i);
					break;
				}
			}

			m_listGUIPackages.DeleteItem(nSelected);
			m_listGUIPackages.UpdateWindow();
			m_packageIndex--;
		}
	}
	else
	{
		MessageBox("Please select an item!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

}

void CGUIDlg::OnBnClickedDeleteGUI()
{
	int nSelected = -1;
	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	TCHAR szBuffer1[1024]; //package
	TCHAR szBuffer2[1024]; //GUI

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer1;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);
		m_selectedPackageName = szBuffer1;
	}
	else
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	nSelected = -1;
	p = m_listGUIs.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIs.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		CInt packageIndex = -1;
		for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
		{
			if (Cmp(g_guiPackagesAndNames[i].front().c_str(), m_selectedPackageName.c_str()))
			{
				packageIndex = i;
				break;
			}
		}

		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.pszText = szBuffer2;
		lvi.cchTextMax = cchBuf;
		m_listGUIs.GetItem(&lvi);

		m_selectedGUIName = szBuffer2;

		CChar currentPackageAndGUIName[MAX_NAME_SIZE];
		sprintf(currentPackageAndGUIName, "%s%s%s", szBuffer1, "_", szBuffer2);
		if (Cmp(g_currentPackageAndGUIName, currentPackageAndGUIName))
		{
			MessageBox("This GUI is already open. Please close current GUI scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}

		for (CUInt i = 0; i < g_projects.size(); i++)
		{
			for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
			{
				//find pkg file
				CChar pkgPath[MAX_NAME_SIZE];
				CChar sceneWithoutDot[MAX_NAME_SIZE];
				Cpy(sceneWithoutDot, g_projects[i]->m_sceneNames[j].c_str());
				GetWithoutDot(sceneWithoutDot);
				sprintf(pkgPath, "%s%s%s%s%s", g_projectsPath, g_projects[i]->m_name, "/", sceneWithoutDot, "/guis.pkg");
				//copy package names
				FILE *PackageFilePtr;
				PackageFilePtr = fopen(pkgPath, "rb");
				if (!PackageFilePtr)
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf(temp, "%s%s%s", "Couldn't open the file '", pkgPath, "' to save data");
					MessageBox(temp, "Vanda Engine Error", MB_OK);
					ReleaseCapture();
					PrintInfo("Delete failed.", COLOR_RED);
					return;
				}
				CUInt size = -1;
				fread(&size, sizeof(CUInt), 1, PackageFilePtr);
				for (CUInt k = 0; k < size; k++)
				{
					CChar name[MAX_NAME_SIZE];
					CChar package_name[MAX_NAME_SIZE];
					CChar gui_name[MAX_NAME_SIZE];
					//write gui data
					fread(name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(package_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(gui_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);

					if (Cmp(gui_name, m_selectedGUIName.c_str()))
					{
						CChar preafbName[MAX_NAME_SIZE];
						sprintf(preafbName, "This GUI is used by %s/%s.\nYou can not delete this GUI.", g_projects[i]->m_name, g_projects[i]->m_sceneNames[j].c_str());
						MessageBox(preafbName, "Vanda Engine Error", MB_OK | MB_ICONERROR);
						fclose(PackageFilePtr);
						return;
					}
				}
				fclose(PackageFilePtr);
			}
		}

		if (MessageBox("Are you sure you want to delete this GUI?", "Warning", MB_YESNO) == IDYES)
		{
			//remove GUI directory
			CChar PackagePath[MAX_NAME_SIZE];
			HRESULT doc_result_package = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, PackagePath);
			if (doc_result_package != S_OK)
			{
				PrintInfo("\nCouldn't get the documents folder to read data", COLOR_RED);
				return;
			}
			else
			{
				Append(PackagePath, "/Vanda/GUIs/");
			}
			CChar path[MAX_NAME_SIZE];
			sprintf(path, "%s%s%s%s", PackagePath, szBuffer1, "/", szBuffer2);
			RemoveAllFilesAndFoldersInDirectory(path);
			for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
			{
				if (i == 0) continue;
				if (Cmp(g_guiPackagesAndNames[packageIndex][i].c_str(), m_selectedGUIName.c_str()))
				{
					g_guiPackagesAndNames[packageIndex].erase(g_guiPackagesAndNames[packageIndex].begin() + i);
				}
			}

			m_guiIndex = -1;
			//delete all items of GUI list
			for (int nItem = m_listGUIs.GetItemCount() - 1; nItem >= 0; nItem--)
			{
				m_listGUIs.DeleteItem(nItem);
			}

			for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
			{
				if (i == 0) continue;
				CChar str[MAX_NAME_SIZE];
				Cpy(str, g_guiPackagesAndNames[packageIndex][i].c_str());
				InsertItemToGUIList(str);
			}
			m_listGUIs.UpdateWindow();
		}
	}
	else
	{
		MessageBox("Please select a GUI!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
}

CVoid CGUIDlg::OnBnClickedRenamePackage()
{
	int nSelected = -1;
	TCHAR szBuffer[1024];

	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);
		m_selectedPackageName = szBuffer;

	}
	else
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	CChar currentPackageName[MAX_NAME_SIZE];
	sprintf(currentPackageName, "%s", szBuffer);
	if (Cmp(g_currentGUIPackageName, currentPackageName))
	{
		MessageBox("current open GUI belongs to selected package. Please close current GUI scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	//then fill it with the VScenes of the selected project
	for (CUInt i = 0; i < g_projects.size(); i++)
	{
		for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
		{
			//find pkg file
			CChar pkgPath[MAX_NAME_SIZE];
			CChar sceneWithoutDot[MAX_NAME_SIZE];
			Cpy(sceneWithoutDot, g_projects[i]->m_sceneNames[j].c_str());
			GetWithoutDot(sceneWithoutDot);
			sprintf(pkgPath, "%s%s%s%s%s", g_projectsPath, g_projects[i]->m_name, "/", sceneWithoutDot, "/guis.pkg");
			//copy package names
			FILE *PackageFilePtr;
			PackageFilePtr = fopen(pkgPath, "rb");
			if (!PackageFilePtr)
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "%s%s%s", "Couldn't open the file '", pkgPath, "' to save data");
				MessageBox(temp, "Vanda Engine Error", MB_OK);
				ReleaseCapture();
				PrintInfo("\nRename failed.", COLOR_RED);
				return;
			}
			CUInt size = -1;
			fread(&size, sizeof(CUInt), 1, PackageFilePtr);
			for (CUInt k = 0; k < size; k++)
			{
				CChar name[MAX_NAME_SIZE];
				CChar package_name[MAX_NAME_SIZE];
				CChar gui_name[MAX_NAME_SIZE];
				//write gui data
				fread(name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
				fread(package_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
				fread(gui_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);

				if (Cmp(package_name, m_selectedPackageName.c_str()))
				{
					CChar packageName[MAX_NAME_SIZE];
					sprintf(packageName, "This package is used by %s/%s.\nYou can not rename this package.", g_projects[i]->m_name, g_projects[i]->m_sceneNames[j].c_str());
					MessageBox(packageName, "Vanda Engine Error", MB_OK | MB_ICONERROR);
					fclose(PackageFilePtr);
					return;
				}
			}
			fclose(PackageFilePtr);
		}
	}

	m_guiNameDlg = CNew(CGUINameDlg);
	m_guiNameDlg->SetInitialData(m_selectedPackageName, "\n", CTrue, CTrue);
	if (IDOK == m_guiNameDlg->DoModal())
	{
		m_listGUIPackages.SetItemText(nSelected, 0, m_guiNameDlg->GetNewName());

		CChar PackagePath[MAX_NAME_SIZE];

		HRESULT doc_result_package = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, PackagePath);
		if (doc_result_package != S_OK)
		{
			PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
			return;
		}
		else
		{
			Append(PackagePath, "/Vanda/GUIs/");
		}

		CChar old_path[MAX_NAME_SIZE];
		CChar new_path[MAX_NAME_SIZE];


		std::string new_name = m_guiNameDlg->GetNewName();

		sprintf(old_path, "%s%s", PackagePath, m_selectedPackageName.c_str());
		sprintf(new_path, "%s%s", PackagePath, new_name.c_str());

		rename(old_path, new_path);

		//rename gui files
		for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
		{
			if (Cmp(g_guiPackagesAndNames[i].front().c_str(), m_guiNameDlg->GetNewName()))
			{
				for (CUInt j = 0; j < g_guiPackagesAndNames[i].size(); j++)
				{
					if (j == 0)continue;
					CChar guiOldPath[MAX_NAME_SIZE];
					sprintf(guiOldPath, "%s%s%s%s%s%s%s%s%s", PackagePath, m_guiNameDlg->GetNewName(), "/", g_guiPackagesAndNames[i][j].c_str(), "/", szBuffer, "_", g_guiPackagesAndNames[i][j].c_str(), ".gui");

					CChar guiNewPath[MAX_NAME_SIZE];
					sprintf(guiNewPath, "%s%s%s%s%s%s%s%s%s", PackagePath, m_guiNameDlg->GetNewName(), "/", g_guiPackagesAndNames[i][j].c_str(), "/", m_guiNameDlg->GetNewName(), "_", g_guiPackagesAndNames[i][j].c_str(), ".gui");

					rename(guiOldPath, guiNewPath);
				}
				break;
			}
		}
		//rename the contents of PKG folder as well
		CChar PKG_old[MAX_URI_SIZE];
		CChar PKG_new[MAX_URI_SIZE];

		sprintf(PKG_old, "%s%s%s%s", PackagePath, "PKG/", szBuffer, ".gui");
		sprintf(PKG_new, "%s%s%s%s", PackagePath, "PKG/", m_guiNameDlg->GetNewName(), ".gui");
		rename(PKG_old, PKG_new);

		//save new data
		CChar docPath[MAX_NAME_SIZE];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
		if (result != S_OK)
		{
			PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
			return;
		}

		CChar newPackage[MAX_NAME_SIZE];
		sprintf(newPackage, "%s%s%s%s", docPath, "/Vanda/GUIs/", m_guiNameDlg->GetNewName(), "/");

		for (CUInt g = 0; g < g_guiPackagesAndNames.size(); g++)
		{
			if (Cmp(g_guiPackagesAndNames[g].front().c_str(), m_guiNameDlg->GetNewName()))
			{
				CChar newPackageName[MAX_NAME_SIZE];
				sprintf(newPackageName, "%s", g_guiPackagesAndNames[g].front().c_str());

				for (CUInt j = 0; j < g_guiPackagesAndNames[g].size(); j++)
				{
					if (j == 0)continue;

					std::vector<CGUIButton*> m_guiButtons;
					std::vector<CGUIBackground*> m_guiBackgrounds;
					std::vector<CGUIText*> m_guiTexts;

					CChar m_strNewGUIName[MAX_NAME_SIZE];
					Cpy(m_strNewGUIName, g_guiPackagesAndNames[g][j].c_str());

					CChar m_strNewPackageAndGUIName[MAX_NAME_SIZE];
					sprintf(m_strNewPackageAndGUIName, "%s%s%s", g_guiPackagesAndNames[g].front().c_str(), "_", m_strNewGUIName);

					CChar newGUIName[MAX_NAME_SIZE];
					sprintf(newGUIName, "%s%s", newPackage, g_guiPackagesAndNames[g][j].c_str());

					CChar newExternalTexturesPath[MAX_NAME_SIZE];
					sprintf(newExternalTexturesPath, "%s%s", newGUIName, "/Textures/");

					CChar newExternalBackgroundTexturesPath[MAX_NAME_SIZE];
					sprintf(newExternalBackgroundTexturesPath, "%s%s", newExternalTexturesPath, "Backgrounds/");

					CChar newExternalButtonTexturesPath[MAX_NAME_SIZE];
					sprintf(newExternalButtonTexturesPath, "%s%s", newExternalTexturesPath, "Buttons/");

					CChar newScriptPath[MAX_NAME_SIZE];
					sprintf(newScriptPath, "%s%s", newGUIName, "/Scripts/");

					CChar fileName[MAX_NAME_SIZE];
					sprintf(fileName, "%s%s%s%s", newGUIName, "/", m_strNewPackageAndGUIName, ".gui");
					FILE *filePtr;
					filePtr = fopen(fileName, "rb");
					if (filePtr)
					{
						CUInt numberOfGUIButtons;
						CUInt numberOfGUIBackgrounds;
						CUInt numberOfGUITexts;

						fread(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < numberOfGUIButtons; i++)
						{
							CChar name[MAX_NAME_SIZE];
							fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar packageName[MAX_NAME_SIZE];
							fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar guiName[MAX_NAME_SIZE];
							fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CVec2f pos;
							fread(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size;
							fread(&size, sizeof(CInt), 1, filePtr);

							CChar mainImagePath[MAX_NAME_SIZE];
							fread(mainImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//disable image
							CBool hasDisableImage;
							fread(&hasDisableImage, sizeof(CBool), 1, filePtr);

							CChar disableImagePath[MAX_NAME_SIZE];
							if (hasDisableImage)
								fread(disableImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//hover image
							CBool hasHoverImage;
							fread(&hasHoverImage, sizeof(CBool), 1, filePtr);

							CChar hoverImagePath[MAX_NAME_SIZE];
							if (hasHoverImage)
								fread(hoverImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//left click image
							CBool hasLeftClickImage;
							fread(&hasLeftClickImage, sizeof(CBool), 1, filePtr);

							CChar leftClickImagePath[MAX_NAME_SIZE];
							if (hasLeftClickImage)
								fread(leftClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//right click image
							CBool hasRightClickImage;
							fread(&hasRightClickImage, sizeof(CBool), 1, filePtr);

							CChar rightClickImagePath[MAX_NAME_SIZE];
							if (hasRightClickImage)
								fread(rightClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//left click script
							CBool hasLeftClickScript;
							fread(&hasLeftClickScript, sizeof(CBool), 1, filePtr);

							CChar leftClickScriptPath[MAX_NAME_SIZE];
							if (hasLeftClickScript)
								fread(leftClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//right click script
							CBool hasRightClickScript;
							fread(&hasRightClickScript, sizeof(CBool), 1, filePtr);

							CChar rightClickScriptPath[MAX_NAME_SIZE];
							if (hasRightClickScript)
								fread(rightClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//hover script
							CBool hasHoverScript;
							fread(&hasHoverScript, sizeof(CBool), 1, filePtr);

							CChar hoverScriptPath[MAX_NAME_SIZE];
							if (hasHoverScript)
								fread(hoverScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CGUIButton* guiButton = CNew(CGUIButton);

							guiButton->SetName(name);
							guiButton->SetPackageName(packageName);
							guiButton->SetGUIName(guiName);
							guiButton->SetPosition(pos);
							guiButton->SetSize(size);
							guiButton->SetMainImagePath(mainImagePath);

							if (hasDisableImage)
							{
								guiButton->SetDisableImagePath(disableImagePath);
								guiButton->SetHasDisableImage(CTrue);
							}
							else
							{
								guiButton->SetHasDisableImage(CFalse);
							}
							if (hasHoverImage)
							{
								guiButton->SetHoverImagePath(hoverImagePath);
								guiButton->SetHasHoverImage(CTrue);
							}
							else
							{
								guiButton->SetHasHoverImage(CFalse);
							}
							if (hasLeftClickImage)
							{
								guiButton->SetLeftClickImagePath(leftClickImagePath);
								guiButton->SetHasLeftClickImage(CTrue);
							}
							else
							{
								guiButton->SetHasLeftClickImage(CFalse);
							}
							if (hasRightClickImage)
							{
								guiButton->SetRightClickImagePath(rightClickImagePath);
								guiButton->SetHasRightClickImage(CTrue);
							}
							else
							{
								guiButton->SetHasRightClickImage(CFalse);
							}
							if (hasLeftClickScript)
							{
								guiButton->SetLeftClickScriptPath(leftClickScriptPath);
								guiButton->SetHasLeftClickScript(CTrue);
							}
							else
							{
								guiButton->SetHasLeftClickScript(CFalse);
							}
							if (hasRightClickScript)
							{
								guiButton->SetRightClickScriptPath(rightClickScriptPath);
								guiButton->SetHasRightClickScript(CTrue);
							}
							else
							{
								guiButton->SetHasRightClickScript(CFalse);
							}
							if (hasHoverScript)
							{
								guiButton->SetHoverScriptPath(hoverScriptPath);
								guiButton->SetHasHoverScript(CTrue);
							}
							else
							{
								guiButton->SetHasHoverScript(CFalse);
							}
							m_guiButtons.push_back(guiButton);
						}

						fread(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < numberOfGUIBackgrounds; i++)
						{
							CChar name[MAX_NAME_SIZE];
							fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar packageName[MAX_NAME_SIZE];
							fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar guiName[MAX_NAME_SIZE];
							fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CVec2f pos;
							fread(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size;
							fread(&size, sizeof(CInt), 1, filePtr);

							CChar imagePath[MAX_NAME_SIZE];
							fread(imagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CGUIBackground* guiBackground = CNew(CGUIBackground);
							guiBackground->SetName(name);
							guiBackground->SetPackageName(packageName);
							guiBackground->SetGUIName(guiName);
							guiBackground->SetPosition(pos);
							guiBackground->SetSize(size);
							guiBackground->SetImagePath(imagePath);
							m_guiBackgrounds.push_back(guiBackground);

						}

						fread(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < numberOfGUITexts; i++)
						{
							CChar name[MAX_NAME_SIZE];
							fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar packageName[MAX_NAME_SIZE];
							fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CChar guiName[MAX_NAME_SIZE];
							fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							CVec2f pos;
							fread(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size;
							fread(&size, sizeof(CInt), 1, filePtr);

							CChar text[MAX_URI_SIZE];
							fread(text, sizeof(CChar), MAX_URI_SIZE, filePtr);

							CVec3f color;
							fread(&color, sizeof(CVec3f), 1, filePtr);

							CFontType font;
							fread(&font, sizeof(CFontType), 1, filePtr);

							CGUIText* guiText = CNew(CGUIText);
							guiText->SetName(name);
							guiText->SetPackageName(packageName);
							guiText->SetGUIName(guiName);
							guiText->SetPosition(pos);
							guiText->SetSize(size);
							guiText->SetColor(color);
							guiText->SetText(text);
							guiText->SetType(font);

							m_guiTexts.push_back(guiText);

						}

						fclose(filePtr);
					}

					for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
					{
						m_guiBackgrounds[i]->SetUpdateImage(CFalse);

						CChar* srcFilePathAfterPath = GetAfterPath(m_guiBackgrounds[i]->GetImagePath());

						CChar newFilePath[MAX_NAME_SIZE];
						sprintf(newFilePath, "%s%s", newExternalBackgroundTexturesPath, srcFilePathAfterPath);

						m_guiBackgrounds[i]->SetImagePath(newFilePath);
					}

					for (CUInt i = 0; i < m_guiButtons.size(); i++)
					{
						//images
						m_guiButtons[i]->SetUpdateMainImage(CFalse);

						CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetMainImagePath());

						CChar newFilePath[MAX_NAME_SIZE];
						sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

						m_guiButtons[i]->SetMainImagePath(newFilePath);

						if (m_guiButtons[i]->GetHasLeftClickImage())
						{
							m_guiButtons[i]->SetUpdateLeftClickImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetLeftClickImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetLeftClickImagePath(newFilePath);

						}
						if (m_guiButtons[i]->GetHasRightClickImage())
						{
							m_guiButtons[i]->SetUpdateRightClickImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetRightClickImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetRightClickImagePath(newFilePath);

						}
						if (m_guiButtons[i]->GetHasHoverImage())
						{
							m_guiButtons[i]->SetUpdateHoverImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetHoverImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetHoverImagePath(newFilePath);

						}
						if (m_guiButtons[i]->GetHasDisableImage())
						{
							m_guiButtons[i]->SetUpdateDisableImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetDisableImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetDisableImagePath(newFilePath);

						}

						//scripts
						if (m_guiButtons[i]->GetHasLeftClickScript())
						{
							m_guiButtons[i]->SetUpdateLeftClickScript(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetLeftClickScriptPath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetLeftClickScriptPath(newFilePath);

						}
						if (m_guiButtons[i]->GetHasRightClickScript())
						{
							m_guiButtons[i]->SetUpdateRightClickScript(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetRightClickScriptPath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetRightClickScriptPath(newFilePath);
						}
						if (m_guiButtons[i]->GetHasHoverScript())
						{
							m_guiButtons[i]->SetUpdateHoverScript(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetHoverScriptPath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetHoverScriptPath(newFilePath);

						}

					}

					//Save functions////////////////////////////////////
					filePtr = fopen(fileName, "wb");
					if (!filePtr)
					{
						//fclose( filePtr );
						CChar temp[MAX_NAME_SIZE];
						sprintf(temp, "%s%s%s", "Couldn't open the file '", fileName, "' to save data");
						MessageBox(temp, "Vanda Engine Error", MB_OK);
						return;
					}
					//save data here
					CUInt numberOfGUIButtons = m_guiButtons.size();
					fwrite(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

					for (CUInt i = 0; i < m_guiButtons.size(); i++)
					{
						fwrite(m_guiButtons[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
						fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

						m_guiButtons[i]->SetPackageName(newPackageName);
						m_guiButtons[i]->SetGUIName(m_strNewGUIName);

						CVec2f pos = m_guiButtons[i]->GetPosition();
						fwrite(&pos, sizeof(CVec2f), 1, filePtr);

						CInt size = m_guiButtons[i]->GetSize();
						fwrite(&size, sizeof(CInt), 1, filePtr);

						fwrite(m_guiButtons[i]->GetMainImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//disable image
						CBool hasDisableImage = m_guiButtons[i]->GetHasDisableImage();
						fwrite(&hasDisableImage, sizeof(CBool), 1, filePtr);

						if (hasDisableImage)
							fwrite(m_guiButtons[i]->GetDisableImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//hover image
						CBool hasHoverImage = m_guiButtons[i]->GetHasHoverImage();
						fwrite(&hasHoverImage, sizeof(CBool), 1, filePtr);

						if (hasHoverImage)
							fwrite(m_guiButtons[i]->GetHoverImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//left click image
						CBool hasLeftClickImage = m_guiButtons[i]->GetHasLeftClickImage();
						fwrite(&hasLeftClickImage, sizeof(CBool), 1, filePtr);

						if (hasLeftClickImage)
							fwrite(m_guiButtons[i]->GetLeftClickImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//right click image
						CBool hasRightClickImage = m_guiButtons[i]->GetHasRightClickImage();
						fwrite(&hasRightClickImage, sizeof(CBool), 1, filePtr);

						if (hasRightClickImage)
							fwrite(m_guiButtons[i]->GetRightClickImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//left click script
						CBool hasLeftClickScript = m_guiButtons[i]->GetHasLeftClickScript();
						fwrite(&hasLeftClickScript, sizeof(CBool), 1, filePtr);

						if (hasLeftClickScript)
							fwrite(m_guiButtons[i]->GetLeftClickScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//right click script
						CBool hasRightClickScript = m_guiButtons[i]->GetHasRightClickScript();
						fwrite(&hasRightClickScript, sizeof(CBool), 1, filePtr);

						if (hasRightClickScript)
							fwrite(m_guiButtons[i]->GetRightClickScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						//hover script
						CBool hasHoverScript = m_guiButtons[i]->GetHasHoverScript();
						fwrite(&hasHoverScript, sizeof(CBool), 1, filePtr);

						if (hasHoverScript)
							fwrite(m_guiButtons[i]->GetHoverScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);
					}

					CUInt numberOfGUIBackgrounds = m_guiBackgrounds.size();
					fwrite(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

					for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
					{
						fwrite(m_guiBackgrounds[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
						fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

						m_guiBackgrounds[i]->SetPackageName(newPackageName);
						m_guiBackgrounds[i]->SetGUIName(m_strNewGUIName);

						CVec2f pos = m_guiBackgrounds[i]->GetPosition();
						fwrite(&pos, sizeof(CVec2f), 1, filePtr);

						CInt size = m_guiBackgrounds[i]->GetSize();
						fwrite(&size, sizeof(CInt), 1, filePtr);

						fwrite(m_guiBackgrounds[i]->GetImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);
					}

					CUInt numberOfGUITexts = m_guiTexts.size();
					fwrite(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

					for (CUInt i = 0; i < m_guiTexts.size(); i++)
					{
						fwrite(m_guiTexts[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

						fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
						fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

						m_guiTexts[i]->SetPackageName(newPackageName);
						m_guiTexts[i]->SetGUIName(m_strNewGUIName);

						CVec2f pos = m_guiTexts[i]->GetPosition();
						fwrite(&pos, sizeof(CVec2f), 1, filePtr);

						CInt size = m_guiTexts[i]->GetSize();
						fwrite(&size, sizeof(CInt), 1, filePtr);

						fwrite(m_guiTexts[i]->GetText(), sizeof(CChar), MAX_URI_SIZE, filePtr);

						CVec3f color = m_guiTexts[i]->GetColor();
						fwrite(&color, sizeof(CVec3f), 1, filePtr);

						CFontType font = m_guiTexts[i]->GetFontType();
						fwrite(&font, sizeof(CFontType), 1, filePtr);
					}

					for (CUInt i = 0; i < m_guiButtons.size(); i++)
						CDelete(m_guiButtons[i]);
					m_guiButtons.clear();

					for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
						CDelete(m_guiBackgrounds[i]);
					m_guiBackgrounds.clear();

					for (CUInt i = 0; i < m_guiTexts.size(); i++)
						CDelete(m_guiTexts[i]);
					m_guiTexts.clear();


					////////////////
					fclose(filePtr);

					//save functions////////////////////////////////////////

				}
				break;
			}
		}

	}
	CDelete(m_guiNameDlg);
}

CVoid CGUIDlg::OnBnClickedRenameGUI()
{
	TCHAR szBuffer1[1024]; //package
	TCHAR szBuffer2[1024]; //gui

	int nSelected = -1;
	POSITION p = m_listGUIPackages.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIPackages.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer1;
		lvi.cchTextMax = cchBuf;
		m_listGUIPackages.GetItem(&lvi);
		m_selectedPackageName = szBuffer1;
	}
	else
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	nSelected = -1;
	p = m_listGUIs.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listGUIs.GetNextSelectedItem(p);
	}
	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT | LVIF_IMAGE;
		lvi.pszText = szBuffer2;
		lvi.cchTextMax = cchBuf;
		m_listGUIs.GetItem(&lvi);

		m_selectedGUIName = szBuffer2;

		CChar currentPackageAndGUIName[MAX_NAME_SIZE];
		sprintf(currentPackageAndGUIName, "%s%s%s", szBuffer1, "_", szBuffer2);
		if (Cmp(g_currentPackageAndGUIName, currentPackageAndGUIName))
		{
			MessageBox("This GUI is already open. Please close current GUI scene and try again.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
		for (CUInt i = 0; i < g_projects.size(); i++)
		{
			for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
			{
				//find pkg file
				CChar pkgPath[MAX_NAME_SIZE];
				CChar sceneWithoutDot[MAX_NAME_SIZE];
				Cpy(sceneWithoutDot, g_projects[i]->m_sceneNames[j].c_str());
				GetWithoutDot(sceneWithoutDot);
				sprintf(pkgPath, "%s%s%s%s%s", g_projectsPath, g_projects[i]->m_name, "/", sceneWithoutDot, "/guis.pkg");
				//copy package names
				FILE *PackageFilePtr;
				PackageFilePtr = fopen(pkgPath, "rb");
				if (!PackageFilePtr)
				{
					CChar temp[MAX_NAME_SIZE];
					sprintf(temp, "%s%s%s", "Couldn't open the file '", pkgPath, "' to load data");
					MessageBox(temp, "Vanda Engine Error", MB_OK);
					ReleaseCapture();
					PrintInfo("Delete failed.", COLOR_RED);
					return;
				}
				CUInt size = -1;
				fread(&size, sizeof(CUInt), 1, PackageFilePtr);
				for (CUInt k = 0; k < size; k++)
				{
					CChar name[MAX_NAME_SIZE];
					CChar package_name[MAX_NAME_SIZE];
					CChar gui_name[MAX_NAME_SIZE];
					//write gui data
					fread(name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(package_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);
					fread(gui_name, sizeof(CChar), MAX_NAME_SIZE, PackageFilePtr);

					if (Cmp(gui_name, m_selectedGUIName.c_str()))
					{
						CChar preafbName[MAX_NAME_SIZE];
						sprintf(preafbName, "This GUI is used by %s/%s.\nYou can not delete this GUI.", g_projects[i]->m_name, g_projects[i]->m_sceneNames[j].c_str());
						MessageBox(preafbName, "Vanda Engine Error", MB_OK | MB_ICONERROR);
						fclose(PackageFilePtr);
						return;
					}
				}
				fclose(PackageFilePtr);
			}
		}

	}
	else
	{
		MessageBox("Please select an item!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	m_guiNameDlg = CNew(CGUINameDlg);
	m_guiNameDlg->SetInitialData(m_selectedPackageName, m_selectedGUIName, CFalse, CTrue);
	if (IDOK == m_guiNameDlg->DoModal())
	{
		CChar PackagePath[MAX_NAME_SIZE];
		HRESULT doc_result_package = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, PackagePath);
		if (doc_result_package != S_OK)
		{
			PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
			return;
		}
		else
		{
			Append(PackagePath, "/Vanda/GUIs/");
		}
		CChar old_path[MAX_NAME_SIZE];
		CChar new_path[MAX_NAME_SIZE];
		sprintf(old_path, "%s%s%s%s", PackagePath, szBuffer1, "/", szBuffer2);
		sprintf(new_path, "%s%s%s%s", PackagePath, szBuffer1, "/", m_guiNameDlg->GetNewName());
		rename(old_path, new_path);

		//rename vpf files
		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
		{
			if (Cmp(g_guiPackagesAndNames[i].front().c_str(), szBuffer1))
			{
				for (CUInt j = 0; j < g_guiPackagesAndNames[i].size(); j++)
				{
					if (j == 0) continue;
					if (Cmp(g_guiPackagesAndNames[i][j].c_str(), m_guiNameDlg->GetNewName()))
					{
						CChar guiOldPath[MAX_NAME_SIZE];
						sprintf(guiOldPath, "%s%s%s%s%s%s%s%s%s", PackagePath, g_guiPackagesAndNames[i].front().c_str(), "/", g_guiPackagesAndNames[i][j].c_str(), "/", g_guiPackagesAndNames[i].front().c_str(), "_", szBuffer2, ".gui");
						CChar guiNewPath[MAX_NAME_SIZE];
						sprintf(guiNewPath, "%s%s%s%s%s%s%s%s%s", PackagePath, g_guiPackagesAndNames[i].front().c_str(), "/", g_guiPackagesAndNames[i][j].c_str(), "/", g_guiPackagesAndNames[i].front().c_str(), "_", g_guiPackagesAndNames[i][j].c_str(), ".gui");
						rename(guiOldPath, guiNewPath);

						foundTarget = CTrue;
						break;
					}
				}
			}
			if (foundTarget)
				break;
		}

		//save new data
		CChar docPath[MAX_NAME_SIZE];
		HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
		if (result != S_OK)
		{
			PrintInfo("\nCouldn't get the documents folder to write data", COLOR_RED);
			return;
		}

		CChar newPackage[MAX_NAME_SIZE];
		sprintf(newPackage, "%s%s%s%s", docPath, "/Vanda/GUIs/", szBuffer1, "/");

		foundTarget = CFalse;

		for (CUInt g = 0; g < g_guiPackagesAndNames.size(); g++)
		{
			if (Cmp(g_guiPackagesAndNames[g].front().c_str(), szBuffer1))
			{
				CChar newPackageName[MAX_NAME_SIZE];
				sprintf(newPackageName, "%s", g_guiPackagesAndNames[g].front().c_str());

				for (CUInt j = 0; j < g_guiPackagesAndNames[g].size(); j++)
				{
					if (j == 0)continue;
					if (Cmp(g_guiPackagesAndNames[g][j].c_str(), m_guiNameDlg->GetNewName()))
					{
						std::vector<CGUIButton*> m_guiButtons;
						std::vector<CGUIBackground*> m_guiBackgrounds;
						std::vector<CGUIText*> m_guiTexts;

						CChar m_strNewGUIName[MAX_NAME_SIZE];
						Cpy(m_strNewGUIName, g_guiPackagesAndNames[g][j].c_str());

						CChar m_strNewPackageAndGUIName[MAX_NAME_SIZE];
						sprintf(m_strNewPackageAndGUIName, "%s%s%s", g_guiPackagesAndNames[g].front().c_str(), "_", m_strNewGUIName);

						CChar newGUIName[MAX_NAME_SIZE];
						sprintf(newGUIName, "%s%s", newPackage, g_guiPackagesAndNames[g][j].c_str());

						CChar newExternalTexturesPath[MAX_NAME_SIZE];
						sprintf(newExternalTexturesPath, "%s%s", newGUIName, "/Textures/");

						CChar newExternalBackgroundTexturesPath[MAX_NAME_SIZE];
						sprintf(newExternalBackgroundTexturesPath, "%s%s", newExternalTexturesPath, "Backgrounds/");

						CChar newExternalButtonTexturesPath[MAX_NAME_SIZE];
						sprintf(newExternalButtonTexturesPath, "%s%s", newExternalTexturesPath, "Buttons/");

						CChar newScriptPath[MAX_NAME_SIZE];
						sprintf(newScriptPath, "%s%s", newGUIName, "/Scripts/");

						CChar fileName[MAX_NAME_SIZE];
						sprintf(fileName, "%s%s%s%s", newGUIName, "/", m_strNewPackageAndGUIName, ".gui");
						FILE *filePtr;
						filePtr = fopen(fileName, "rb");
						if (filePtr)
						{
							CUInt numberOfGUIButtons;
							CUInt numberOfGUIBackgrounds;
							CUInt numberOfGUITexts;

							fread(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

							for (CUInt i = 0; i < numberOfGUIButtons; i++)
							{
								CChar name[MAX_NAME_SIZE];
								fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar packageName[MAX_NAME_SIZE];
								fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar guiName[MAX_NAME_SIZE];
								fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CVec2f pos;
								fread(&pos, sizeof(CVec2f), 1, filePtr);

								CInt size;
								fread(&size, sizeof(CInt), 1, filePtr);

								CChar mainImagePath[MAX_NAME_SIZE];
								fread(mainImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//disable image
								CBool hasDisableImage;
								fread(&hasDisableImage, sizeof(CBool), 1, filePtr);

								CChar disableImagePath[MAX_NAME_SIZE];
								if (hasDisableImage)
									fread(disableImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//hover image
								CBool hasHoverImage;
								fread(&hasHoverImage, sizeof(CBool), 1, filePtr);

								CChar hoverImagePath[MAX_NAME_SIZE];
								if (hasHoverImage)
									fread(hoverImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//left click image
								CBool hasLeftClickImage;
								fread(&hasLeftClickImage, sizeof(CBool), 1, filePtr);

								CChar leftClickImagePath[MAX_NAME_SIZE];
								if (hasLeftClickImage)
									fread(leftClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//right click image
								CBool hasRightClickImage;
								fread(&hasRightClickImage, sizeof(CBool), 1, filePtr);

								CChar rightClickImagePath[MAX_NAME_SIZE];
								if (hasRightClickImage)
									fread(rightClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//left click script
								CBool hasLeftClickScript;
								fread(&hasLeftClickScript, sizeof(CBool), 1, filePtr);

								CChar leftClickScriptPath[MAX_NAME_SIZE];
								if (hasLeftClickScript)
									fread(leftClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//right click script
								CBool hasRightClickScript;
								fread(&hasRightClickScript, sizeof(CBool), 1, filePtr);

								CChar rightClickScriptPath[MAX_NAME_SIZE];
								if (hasRightClickScript)
									fread(rightClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								//hover script
								CBool hasHoverScript;
								fread(&hasHoverScript, sizeof(CBool), 1, filePtr);

								CChar hoverScriptPath[MAX_NAME_SIZE];
								if (hasHoverScript)
									fread(hoverScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CGUIButton* guiButton = CNew(CGUIButton);

								guiButton->SetName(name);
								guiButton->SetPackageName(packageName);
								guiButton->SetGUIName(guiName);
								guiButton->SetPosition(pos);
								guiButton->SetSize(size);
								guiButton->SetMainImagePath(mainImagePath);

								if (hasDisableImage)
								{
									guiButton->SetDisableImagePath(disableImagePath);
									guiButton->SetHasDisableImage(CTrue);
								}
								else
								{
									guiButton->SetHasDisableImage(CFalse);
								}
								if (hasHoverImage)
								{
									guiButton->SetHoverImagePath(hoverImagePath);
									guiButton->SetHasHoverImage(CTrue);
								}
								else
								{
									guiButton->SetHasHoverImage(CFalse);
								}
								if (hasLeftClickImage)
								{
									guiButton->SetLeftClickImagePath(leftClickImagePath);
									guiButton->SetHasLeftClickImage(CTrue);
								}
								else
								{
									guiButton->SetHasLeftClickImage(CFalse);
								}
								if (hasRightClickImage)
								{
									guiButton->SetRightClickImagePath(rightClickImagePath);
									guiButton->SetHasRightClickImage(CTrue);
								}
								else
								{
									guiButton->SetHasRightClickImage(CFalse);
								}
								if (hasLeftClickScript)
								{
									guiButton->SetLeftClickScriptPath(leftClickScriptPath);
									guiButton->SetHasLeftClickScript(CTrue);
								}
								else
								{
									guiButton->SetHasLeftClickScript(CFalse);
								}
								if (hasRightClickScript)
								{
									guiButton->SetRightClickScriptPath(rightClickScriptPath);
									guiButton->SetHasRightClickScript(CTrue);
								}
								else
								{
									guiButton->SetHasRightClickScript(CFalse);
								}
								if (hasHoverScript)
								{
									guiButton->SetHoverScriptPath(hoverScriptPath);
									guiButton->SetHasHoverScript(CTrue);
								}
								else
								{
									guiButton->SetHasHoverScript(CFalse);
								}
								m_guiButtons.push_back(guiButton);
							}

							fread(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

							for (CUInt i = 0; i < numberOfGUIBackgrounds; i++)
							{
								CChar name[MAX_NAME_SIZE];
								fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar packageName[MAX_NAME_SIZE];
								fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar guiName[MAX_NAME_SIZE];
								fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CVec2f pos;
								fread(&pos, sizeof(CVec2f), 1, filePtr);

								CInt size;
								fread(&size, sizeof(CInt), 1, filePtr);

								CChar imagePath[MAX_NAME_SIZE];
								fread(imagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CGUIBackground* guiBackground = CNew(CGUIBackground);
								guiBackground->SetName(name);
								guiBackground->SetPackageName(packageName);
								guiBackground->SetGUIName(guiName);
								guiBackground->SetPosition(pos);
								guiBackground->SetSize(size);
								guiBackground->SetImagePath(imagePath);
								m_guiBackgrounds.push_back(guiBackground);

							}

							fread(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

							for (CUInt i = 0; i < numberOfGUITexts; i++)
							{
								CChar name[MAX_NAME_SIZE];
								fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar packageName[MAX_NAME_SIZE];
								fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CChar guiName[MAX_NAME_SIZE];
								fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

								CVec2f pos;
								fread(&pos, sizeof(CVec2f), 1, filePtr);

								CInt size;
								fread(&size, sizeof(CInt), 1, filePtr);

								CChar text[MAX_URI_SIZE];
								fread(text, sizeof(CChar), MAX_URI_SIZE, filePtr);

								CVec3f color;
								fread(&color, sizeof(CVec3f), 1, filePtr);

								CFontType font;
								fread(&font, sizeof(CFontType), 1, filePtr);

								CGUIText* guiText = CNew(CGUIText);
								guiText->SetName(name);
								guiText->SetPackageName(packageName);
								guiText->SetGUIName(guiName);
								guiText->SetPosition(pos);
								guiText->SetSize(size);
								guiText->SetColor(color);
								guiText->SetText(text);
								guiText->SetType(font);

								m_guiTexts.push_back(guiText);

							}

							fclose(filePtr);
						}

						for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
						{
							m_guiBackgrounds[i]->SetUpdateImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiBackgrounds[i]->GetImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalBackgroundTexturesPath, srcFilePathAfterPath);

							m_guiBackgrounds[i]->SetImagePath(newFilePath);
						}

						for (CUInt i = 0; i < m_guiButtons.size(); i++)
						{
							//images
							m_guiButtons[i]->SetUpdateMainImage(CFalse);

							CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetMainImagePath());

							CChar newFilePath[MAX_NAME_SIZE];
							sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

							m_guiButtons[i]->SetMainImagePath(newFilePath);

							if (m_guiButtons[i]->GetHasLeftClickImage())
							{
								m_guiButtons[i]->SetUpdateLeftClickImage(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetLeftClickImagePath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetLeftClickImagePath(newFilePath);

							}
							if (m_guiButtons[i]->GetHasRightClickImage())
							{
								m_guiButtons[i]->SetUpdateRightClickImage(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetRightClickImagePath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetRightClickImagePath(newFilePath);

							}
							if (m_guiButtons[i]->GetHasHoverImage())
							{
								m_guiButtons[i]->SetUpdateHoverImage(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetHoverImagePath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetHoverImagePath(newFilePath);

							}
							if (m_guiButtons[i]->GetHasDisableImage())
							{
								m_guiButtons[i]->SetUpdateDisableImage(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetDisableImagePath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetDisableImagePath(newFilePath);

							}

							//scripts
							if (m_guiButtons[i]->GetHasLeftClickScript())
							{
								m_guiButtons[i]->SetUpdateLeftClickScript(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetLeftClickScriptPath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetLeftClickScriptPath(newFilePath);

							}
							if (m_guiButtons[i]->GetHasRightClickScript())
							{
								m_guiButtons[i]->SetUpdateRightClickScript(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetRightClickScriptPath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetRightClickScriptPath(newFilePath);
							}
							if (m_guiButtons[i]->GetHasHoverScript())
							{
								m_guiButtons[i]->SetUpdateHoverScript(CFalse);

								CChar* srcFilePathAfterPath = GetAfterPath(m_guiButtons[i]->GetHoverScriptPath());

								CChar newFilePath[MAX_NAME_SIZE];
								sprintf(newFilePath, "%s%s", newExternalButtonTexturesPath, srcFilePathAfterPath);

								m_guiButtons[i]->SetHoverScriptPath(newFilePath);

							}

						}

						//Save functions////////////////////////////////////
						filePtr = fopen(fileName, "wb");
						if (!filePtr)
						{
							//fclose( filePtr );
							CChar temp[MAX_NAME_SIZE];
							sprintf(temp, "%s%s%s", "Couldn't open the file '", fileName, "' to save data");
							MessageBox(temp, "Vanda Engine Error", MB_OK);
							return;
						}
						//save data here
						CUInt numberOfGUIButtons = m_guiButtons.size();
						fwrite(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < m_guiButtons.size(); i++)
						{
							fwrite(m_guiButtons[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
							fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							m_guiButtons[i]->SetPackageName(newPackageName);
							m_guiButtons[i]->SetGUIName(m_strNewGUIName);

							CVec2f pos = m_guiButtons[i]->GetPosition();
							fwrite(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size = m_guiButtons[i]->GetSize();
							fwrite(&size, sizeof(CInt), 1, filePtr);

							fwrite(m_guiButtons[i]->GetMainImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//disable image
							CBool hasDisableImage = m_guiButtons[i]->GetHasDisableImage();
							fwrite(&hasDisableImage, sizeof(CBool), 1, filePtr);

							if (hasDisableImage)
								fwrite(m_guiButtons[i]->GetDisableImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//hover image
							CBool hasHoverImage = m_guiButtons[i]->GetHasHoverImage();
							fwrite(&hasHoverImage, sizeof(CBool), 1, filePtr);

							if (hasHoverImage)
								fwrite(m_guiButtons[i]->GetHoverImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//left click image
							CBool hasLeftClickImage = m_guiButtons[i]->GetHasLeftClickImage();
							fwrite(&hasLeftClickImage, sizeof(CBool), 1, filePtr);

							if (hasLeftClickImage)
								fwrite(m_guiButtons[i]->GetLeftClickImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//right click image
							CBool hasRightClickImage = m_guiButtons[i]->GetHasRightClickImage();
							fwrite(&hasRightClickImage, sizeof(CBool), 1, filePtr);

							if (hasRightClickImage)
								fwrite(m_guiButtons[i]->GetRightClickImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//left click script
							CBool hasLeftClickScript = m_guiButtons[i]->GetHasLeftClickScript();
							fwrite(&hasLeftClickScript, sizeof(CBool), 1, filePtr);

							if (hasLeftClickScript)
								fwrite(m_guiButtons[i]->GetLeftClickScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//right click script
							CBool hasRightClickScript = m_guiButtons[i]->GetHasRightClickScript();
							fwrite(&hasRightClickScript, sizeof(CBool), 1, filePtr);

							if (hasRightClickScript)
								fwrite(m_guiButtons[i]->GetRightClickScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							//hover script
							CBool hasHoverScript = m_guiButtons[i]->GetHasHoverScript();
							fwrite(&hasHoverScript, sizeof(CBool), 1, filePtr);

							if (hasHoverScript)
								fwrite(m_guiButtons[i]->GetHoverScriptPath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);
						}

						CUInt numberOfGUIBackgrounds = m_guiBackgrounds.size();
						fwrite(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
						{
							fwrite(m_guiBackgrounds[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
							fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							m_guiBackgrounds[i]->SetPackageName(newPackageName);
							m_guiBackgrounds[i]->SetGUIName(m_strNewGUIName);

							CVec2f pos = m_guiBackgrounds[i]->GetPosition();
							fwrite(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size = m_guiBackgrounds[i]->GetSize();
							fwrite(&size, sizeof(CInt), 1, filePtr);

							fwrite(m_guiBackgrounds[i]->GetImagePath(), sizeof(CChar), MAX_NAME_SIZE, filePtr);
						}

						CUInt numberOfGUITexts = m_guiTexts.size();
						fwrite(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

						for (CUInt i = 0; i < m_guiTexts.size(); i++)
						{
							fwrite(m_guiTexts[i]->GetName(), sizeof(CChar), MAX_NAME_SIZE, filePtr);

							fwrite(newPackageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);
							fwrite(m_strNewGUIName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

							m_guiTexts[i]->SetPackageName(newPackageName);
							m_guiTexts[i]->SetGUIName(m_strNewGUIName);

							CVec2f pos = m_guiTexts[i]->GetPosition();
							fwrite(&pos, sizeof(CVec2f), 1, filePtr);

							CInt size = m_guiTexts[i]->GetSize();
							fwrite(&size, sizeof(CInt), 1, filePtr);

							fwrite(m_guiTexts[i]->GetText(), sizeof(CChar), MAX_URI_SIZE, filePtr);

							CVec3f color = m_guiTexts[i]->GetColor();
							fwrite(&color, sizeof(CVec3f), 1, filePtr);

							CFontType font = m_guiTexts[i]->GetFontType();
							fwrite(&font, sizeof(CFontType), 1, filePtr);
						}

						for (CUInt i = 0; i < m_guiButtons.size(); i++)
							CDelete(m_guiButtons[i]);
						m_guiButtons.clear();

						for (CUInt i = 0; i < m_guiBackgrounds.size(); i++)
							CDelete(m_guiBackgrounds[i]);
						m_guiBackgrounds.clear();

						for (CUInt i = 0; i < m_guiTexts.size(); i++)
							CDelete(m_guiTexts[i]);
						m_guiTexts.clear();


						////////////////
						fclose(filePtr);

						//save functions////////////////////////////////////////
						foundTarget = CTrue;
						break;
					}
				}
			}
			if (foundTarget)
				break;

		}

		m_listGUIs.SetItemText(nSelected, 0, m_guiNameDlg->GetNewName());


	}
	CDelete(m_guiNameDlg);

}

//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditProjectVScenes.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "EditProjectVScenes.h"
#include "afxdialogex.h"


// CEditProjectVScenes dialog

IMPLEMENT_DYNAMIC(CEditProjectVScenes, CDialog)

CEditProjectVScenes::CEditProjectVScenes(CWnd* pParent /*=NULL*/)
	: CDialog(CEditProjectVScenes::IDD, pParent)
{
	m_VSceneIndex = -1;
	Cpy(m_name, "\n");
}

CEditProjectVScenes::~CEditProjectVScenes()
{
}

void CEditProjectVScenes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VSCENES, m_listVScenes);
	DDX_Control(pDX, ID_RENAME, m_btnRename);
	DDX_Control(pDX, ID_DELETE, m_btnDelete);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CEditProjectVScenes, CDialog)
	ON_BN_CLICKED(ID_DELETE, &CEditProjectVScenes::OnBnClickedDelete)
	ON_BN_CLICKED(ID_RENAME, &CEditProjectVScenes::OnBnClickedRename)
	ON_BN_CLICKED(IDOK, &CEditProjectVScenes::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditProjectVScenes message handlers


void CEditProjectVScenes::OnBnClickedDelete()
{
	int nSelected = -1;
	POSITION p = m_listVScenes.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listVScenes.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024]; //package

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listVScenes.GetItem(&lvi);
	}
	else
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (Cmp(g_currentVSceneName, szBuffer))
	{
		MessageBox("This VScene is already open. Please close it and try again.", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (nSelected >= 0)
	{
		if (MessageBox("Are you sure you want to delete this VScene?", "Warning", MB_YESNO) == IDYES)
		{
			CChar VSceneNameWithoutDot[MAX_NAME_SIZE];
			Cpy(VSceneNameWithoutDot, szBuffer);
			GetWithoutDot(VSceneNameWithoutDot);
			CChar VScenePath[MAX_URI_SIZE];
			sprintf(VScenePath, "%s%s", g_currentProjectPath, VSceneNameWithoutDot);
			if (!RemoveAllFilesAndFoldersInDirectory(VScenePath))
			{
				CChar message[MAX_URI_SIZE];
				sprintf(message, "Couldn't delete files in %s directory", VScenePath);
				MessageBox(message);
			}
			for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
			{
				if (Cmp(g_VSceneNamesOfCurrentProject[i].c_str(), szBuffer))
				{
					g_VSceneNamesOfCurrentProject.erase(g_VSceneNamesOfCurrentProject.begin() + i);
					break;
				}
			}
			for (CUInt i = 0; i < g_projects.size(); i++)
			{
				if (g_projects[i]->m_isActive)
				{
					for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
					{
						if (Cmp(g_projects[i]->m_sceneNames[j].c_str(), szBuffer))
						{
							g_projects[i]->m_sceneNames.erase(g_projects[i]->m_sceneNames.begin() + j);
							break;
						}
					}
					break;
				}
			}

			//save changes to projects.dat
			FILE *ProjectsFilePtr;
			CChar DATPath[MAX_NAME_SIZE];
			sprintf(DATPath, "%s%s", g_projectsPath, "projects.dat");

			DeleteFile(DATPath);
			ProjectsFilePtr = fopen(DATPath, "wb");
			if (!ProjectsFilePtr)
			{
				MessageBox("Couldn't open 'assets/Projects/projects.dat' to save data!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
				//return;
			}

			CInt numProjects = (CInt)g_projects.size();
			fwrite(&numProjects, sizeof(CInt), 1, ProjectsFilePtr);
			fclose(ProjectsFilePtr);

			for (CInt i = 0; i < numProjects; i++)
			{
				CChar filePath[MAX_URI_SIZE];
				sprintf(filePath, "%s%s%s%s", g_projectsPath, "PRJ/", g_projects[i]->m_name, ".prj");
				ProjectsFilePtr = fopen(filePath, "wb");

				fwrite(g_projects[i]->m_name, sizeof(CChar), MAX_NAME_SIZE, ProjectsFilePtr);
				CInt numScenes = (CInt)g_projects[i]->m_sceneNames.size();
				fwrite(&numScenes, sizeof(CInt), 1, ProjectsFilePtr);
				for (CInt j = 0; j < numScenes; j++)
				{
					CChar vsceneName[MAX_NAME_SIZE];
					Cpy(vsceneName, g_projects[i]->m_sceneNames[j].c_str());
					fwrite(vsceneName, sizeof(CChar), MAX_NAME_SIZE, ProjectsFilePtr);
				}
				fwrite(&g_projects[i]->m_isActive, sizeof(CBool), 1, ProjectsFilePtr);

				fclose(ProjectsFilePtr);

			}

			m_VSceneIndex = -1;
			//delete all items of prefab list
			for (int nItem = m_listVScenes.GetItemCount() - 1; nItem >= 0; nItem--)
			{
				m_listVScenes.DeleteItem(nItem);
			}


			CBitmap* cBmpMask = NULL;

			m_VSceneImage.DeleteImageList();
			m_VSceneImage.Create(182, 101, ILC_COLOR24, 1, g_VSceneNamesOfCurrentProject.size());

			for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
			{
				CChar VScene_str[MAX_NAME_SIZE];
				Cpy(VScene_str, g_VSceneNamesOfCurrentProject[i].c_str());
				GetWithoutDot(VScene_str);

				CChar BitmapPath[MAX_NAME_SIZE];
				sprintf(BitmapPath, "%s%s%s%s%s", g_currentProjectPath, VScene_str, "/", VScene_str, ".bmp");

				HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), BitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				if (hBmp != NULL)
				{
					CBitmap* cBmp = CBitmap::FromHandle(hBmp);
					if (cBmp != NULL)
						m_VSceneImage.Add(cBmp, cBmpMask);
					cBmp->DeleteObject();
				}
			}

			m_listVScenes.SetImageList(&m_VSceneImage, LVSIL_NORMAL);

			for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
			{
				CChar str[MAX_NAME_SIZE];
				Cpy(str, g_VSceneNamesOfCurrentProject[i].c_str());
				InsertItemToVSceneList(str, i);
			}

			PrintInfo("\nVScene removed successfully.");
		}
	}
}

void CEditProjectVScenes::OnBnClickedRename()
{
	int nSelected = -1;
	POSITION p = m_listVScenes.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listVScenes.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024]; //package

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listVScenes.GetItem(&lvi);
	}
	else
	{
		MessageBox("Please select a VScene!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (Cmp(g_currentVSceneName, szBuffer))
	{
		MessageBox("This VScene is already open. Please close it and try again.", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}
	if (nSelected >= 0)
	{
		CEditVSceneName* dlg = CNew(CEditVSceneName);
		CChar selectedName[MAX_NAME_SIZE];
		Cpy(selectedName, szBuffer);
		GetWithoutDot(selectedName);
		dlg->SetInitialData(CFalse, selectedName);
		CInt result = dlg->DoModal();
		if (result == IDCANCEL)
			return;
		CChar new_name[MAX_NAME_SIZE];
		Cpy(new_name, dlg->GetName());

		CChar oldVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy(oldVSceneNameWithoutDot, szBuffer);
		GetWithoutDot(oldVSceneNameWithoutDot);
		CChar oldPath[MAX_URI_SIZE];
		sprintf(oldPath, "%s%s", g_currentProjectPath, oldVSceneNameWithoutDot);

		CChar newVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy(newVSceneNameWithoutDot, new_name);
		GetWithoutDot(newVSceneNameWithoutDot);
		CChar newPath[MAX_URI_SIZE];
		sprintf(newPath, "%s%s", g_currentProjectPath, newVSceneNameWithoutDot);

		rename(oldPath, newPath);

		//rename vin file
		CChar oldVinPath[MAX_URI_SIZE];
		sprintf(oldVinPath, "%s%s%s%s", newPath, "/", oldVSceneNameWithoutDot, ".vin");

		CChar newVinPath[MAX_URI_SIZE];
		sprintf(newVinPath, "%s%s%s%s", newPath, "/", newVSceneNameWithoutDot, ".vin");

		rename(oldVinPath, newVinPath);

		//rename bmp file
		CChar oldBmpPath[MAX_URI_SIZE];
		sprintf(oldBmpPath, "%s%s%s%s", newPath, "/", oldVSceneNameWithoutDot, ".bmp");

		CChar newBmpPath[MAX_URI_SIZE];
		sprintf(newBmpPath, "%s%s%s%s", newPath, "/", newVSceneNameWithoutDot, ".bmp");

		rename(oldBmpPath, newBmpPath);

		//rename onm file
		CChar oldOnmPath[MAX_URI_SIZE];
		sprintf(oldOnmPath, "%s%s%s%s", newPath, "/", oldVSceneNameWithoutDot, ".onm");

		CChar newOnmPath[MAX_URI_SIZE];
		sprintf(newOnmPath, "%s%s%s%s", newPath, "/", newVSceneNameWithoutDot, ".onm");

		rename(oldOnmPath, newOnmPath);

		for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
		{
			if (Cmp(g_VSceneNamesOfCurrentProject[i].c_str(), szBuffer))
			{
				g_VSceneNamesOfCurrentProject[i] = new_name;
				break;
			}
		}
		for (CUInt i = 0; i < g_projects.size(); i++)
		{
			if (g_projects[i]->m_isActive)
			{
				for (CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++)
				{
					if (Cmp(g_projects[i]->m_sceneNames[j].c_str(), szBuffer))
					{
						g_projects[i]->m_sceneNames[j] = new_name;
						break;
					}
				}
				break;
			}
		}

		//save changes to projects.dat
		FILE *ProjectsFilePtr;
		CChar DATPath[MAX_NAME_SIZE];
		sprintf(DATPath, "%s%s", g_projectsPath, "projects.dat");

		DeleteFile(DATPath);
		ProjectsFilePtr = fopen(DATPath, "wb");
		if (!ProjectsFilePtr)
		{
			MessageBox("Couldn't open 'assets/Projects/projects.dat' to save data!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			//return;
		}

		CInt numProjects = (CInt)g_projects.size();
		fwrite(&numProjects, sizeof(CInt), 1, ProjectsFilePtr);
		fclose(ProjectsFilePtr);

		for (CInt i = 0; i < numProjects; i++)
		{
			CChar filePath[MAX_URI_SIZE];
			sprintf(filePath, "%s%s%s%s", g_projectsPath, "PRJ/", g_projects[i]->m_name, ".prj");
			ProjectsFilePtr = fopen(filePath, "wb");

			fwrite(g_projects[i]->m_name, sizeof(CChar), MAX_NAME_SIZE, ProjectsFilePtr);
			CInt numScenes = (CInt)g_projects[i]->m_sceneNames.size();
			fwrite(&numScenes, sizeof(CInt), 1, ProjectsFilePtr);
			for (CInt j = 0; j < numScenes; j++)
			{
				CChar vsceneName[MAX_NAME_SIZE];
				Cpy(vsceneName, g_projects[i]->m_sceneNames[j].c_str());
				fwrite(vsceneName, sizeof(CChar), MAX_NAME_SIZE, ProjectsFilePtr);
			}
			fwrite(&g_projects[i]->m_isActive, sizeof(CBool), 1, ProjectsFilePtr);

			fclose(ProjectsFilePtr);

		}

		m_listVScenes.SetItemText(nSelected, 0, new_name);
		if (dlg)
			CDelete(dlg);
		PrintInfo("\nVScene renamed successfully.");
	}

}

BOOL CEditProjectVScenes::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_open)
	{
		m_btnDelete.ShowWindow(SW_HIDE);
		m_btnRename.ShowWindow(SW_HIDE);
		m_btnOK.SetWindowTextA("Open");
	}
	else
	{
		m_btnDelete.ShowWindow(SW_SHOW);
		m_btnRename.ShowWindow(SW_SHOW);
		m_btnOK.ShowWindow(SW_HIDE);
		m_btnCancel.SetWindowTextA("OK");
	}

	RECT tempRect;
	m_listVScenes.GetClientRect(&tempRect);


	CBitmap* cBmpMask = NULL;

	m_VSceneImage.DeleteImageList();
	m_VSceneImage.Create(182, 101, ILC_COLOR24, 1, g_VSceneNamesOfCurrentProject.size());

	for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
	{
		CChar VScene_str[MAX_NAME_SIZE];
		Cpy(VScene_str, g_VSceneNamesOfCurrentProject[i].c_str());
		GetWithoutDot(VScene_str);

		CChar BitmapPath[MAX_NAME_SIZE];
		sprintf(BitmapPath, "%s%s%s%s%s", g_currentProjectPath, VScene_str, "/", VScene_str, ".bmp");

		HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), BitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hBmp != NULL)
		{
			CBitmap* cBmp = CBitmap::FromHandle(hBmp);
			if (cBmp != NULL)
				m_VSceneImage.Add(cBmp, cBmpMask);
			cBmp->DeleteObject();
		}
	}

	m_listVScenes.SetImageList(&m_VSceneImage, LVSIL_NORMAL);

	m_listVScenes.GetClientRect(&tempRect);
	m_listVScenes.InsertColumn(0, "VScenes", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 80 / 100);
	m_listVScenes.ShowWindow(SW_SHOW);
	m_listVScenes.UpdateWindow();

	//insert items
	m_listVScenes.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
	{
		CChar str[MAX_NAME_SIZE];
		Cpy(str, g_VSceneNamesOfCurrentProject[i].c_str());
		InsertItemToVSceneList(str, i);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CEditProjectVScenes::InsertItemToVSceneList(CChar* vsceneName, CUInt imgIndex)
{
	m_VSceneIndex++;
	int index = m_VSceneIndex;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iImage = imgIndex;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = vsceneName;
	m_listVScenes.InsertItem(&lvItem);

	m_listVScenes.SetItemState(index, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listVScenes.SetSelectionMark(index);
	m_listVScenes.EnsureVisible(index, FALSE);
	m_listVScenes.UpdateWindow();
}

void CEditProjectVScenes::SetState(CBool open)
{
	m_open = open;
}

void CEditProjectVScenes::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_open)
	{
		int nSelected = -1;
		POSITION p = m_listVScenes.GetFirstSelectedItemPosition();
		while (p)
		{
			nSelected = m_listVScenes.GetNextSelectedItem(p);
		}
		TCHAR szBuffer[1024]; //package

		if (nSelected >= 0)
		{
			DWORD cchBuf(1024);
			LVITEM lvi;
			lvi.iItem = nSelected;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_TEXT;
			lvi.pszText = szBuffer;
			lvi.cchTextMax = cchBuf;
			m_listVScenes.GetItem(&lvi);
			Cpy(m_name, szBuffer);
		}
		else
		{
			MessageBox("Please select a VScene!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
			return;
		}
	}
	CDialog::OnOK();
}

CChar* CEditProjectVScenes::GetName()
{
	return m_name;
}
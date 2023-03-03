//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// DeleteProject.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "DeleteProject.h"
#include "afxdialogex.h"


// CDeleteProject dialog

IMPLEMENT_DYNAMIC(CDeleteProject, CDialog)

CDeleteProject::CDeleteProject(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteProject::IDD, pParent)
{
	availableProjectIndex = -1;
}

CDeleteProject::~CDeleteProject()
{
}

void CDeleteProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AVAILABLE_PROJECTS, m_listAvailableProjects);
}


BEGIN_MESSAGE_MAP(CDeleteProject, CDialog)
	ON_BN_CLICKED(IDOK, &CDeleteProject::OnBnClickedOk)
END_MESSAGE_MAP()


// CDeleteProject message handlers


BOOL CDeleteProject::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rect;
	m_listAvailableProjects.GetClientRect(&rect);

	CBitmap cBmp;
	CBitmap* cBmpMask = NULL;
	m_projectListImage.Create(32, 32, ILC_COLOR24, 1, 1);

	cBmp.LoadBitmap(IDB_BITMAP_DEFAULT_PROJECT);
	m_projectListImage.Add(&cBmp, cBmpMask);
	cBmp.DeleteObject();

	m_listAvailableProjects.InsertColumn(0, "Available Projects", LVCFMT_LEFT, rect.right - rect.left, 0);
	m_listAvailableProjects.SetImageList(&m_projectListImage, LVSIL_SMALL);
	m_listAvailableProjects.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

	for (CUInt i = 0; i < g_projects.size(); i++)
	{
		CChar projectName[MAX_NAME_SIZE];
		Cpy(projectName, g_projects[i]->m_name);
		InserItemToAvailableProjectsList(projectName, g_projects[i]->m_isActive);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

CVoid CDeleteProject::InserItemToAvailableProjectsList(char * projectName, CBool isActive)
{
	availableProjectIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = availableProjectIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = projectName;
	m_listAvailableProjects.InsertItem(&lvItem);
	if (isActive)
	{
		m_listAvailableProjects.SetItemState(availableProjectIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listAvailableProjects.SetSelectionMark(availableProjectIndex);
	}
	m_listAvailableProjects.EnsureVisible(availableProjectIndex, FALSE);
	m_listAvailableProjects.UpdateWindow();
}



void CDeleteProject::OnBnClickedOk()
{
	int nSelected = -1;
	POSITION p = m_listAvailableProjects.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listAvailableProjects.GetNextSelectedItem(p);
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
		m_listAvailableProjects.GetItem(&lvi);

		for (CUInt i = 0; i < g_projects.size(); i++)
		{
			if (g_projects[i]->m_isActive)
			{
				if (Cmp(szBuffer, g_projects[i]->m_name))
				{
					MessageBox("This project is activate.\nPlease use 'File > Project > Set Project' menu to activate another project and try again.", "Error", MB_OK | MB_ICONERROR);
					return; // no need to take any actions
				}
			}
		}
		CChar warningMessage[MAX_NAME_SIZE];
		sprintf(warningMessage, "Delete project '%s' ?", szBuffer);

		if (MessageBox(warningMessage, "Warning", MB_YESNO | MB_ICONWARNING) == IDYES)
		{
			//delete selected project directory
			CChar selectedProjectPath[MAX_URI_SIZE];
			sprintf(selectedProjectPath, "%s%s", g_projectsPath, szBuffer);
			if (!RemoveAllFilesAndFoldersInDirectory(selectedProjectPath))
			{
				MessageBox("An error occured while deleting the project", "Error");
				return;
			}

			//delete prj file of selected project
			CChar prjFilePath[MAX_URI_SIZE];
			sprintf(prjFilePath, "%s%s%s%s", g_projectsPath, "PRJ/", szBuffer, ".prj");
			if (!DeleteFile(prjFilePath))
			{
				MessageBox("An error occured while deleting the PRJ file", "Warning");
			}

			//remove project name from g_projects vector
			for (CUInt pr = 0; pr < g_projects.size(); pr++)
			{
				if (Cmp(g_projects[pr]->m_name, szBuffer))
				{
					g_projects.erase(g_projects.begin() + pr);
					break;
				}
			}

			//save the changes to projects.dat
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

			//reload projects in list control
			m_listAvailableProjects.DeleteAllItems();
			m_listAvailableProjects.UpdateWindow();
			availableProjectIndex = -1;
			for (CUInt i = 0; i < g_projects.size(); i++)
			{
				CChar projectName[MAX_NAME_SIZE];
				Cpy(projectName, g_projects[i]->m_name);
				InserItemToAvailableProjectsList(projectName, g_projects[i]->m_isActive);
			}
		}
	}
	else
	{
		MessageBoxA("Please select a project");
	}
}

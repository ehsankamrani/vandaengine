//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SetCurrentProject.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "SetCurrentProject.h"
#include "afxdialogex.h"


// CSetCurrentProject dialog

IMPLEMENT_DYNAMIC(CSetCurrentProject, CDialog)

CSetCurrentProject::CSetCurrentProject(CWnd* pParent /*=NULL*/)
	: CDialog(CSetCurrentProject::IDD, pParent)
{
	availableProjectIndex = -1;	
}	

CSetCurrentProject::~CSetCurrentProject()
{
}

void CSetCurrentProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AVAILABLE_PROJECTS, m_listAvailableProjects);
}


// CSetCurrentProject message handlers
BEGIN_MESSAGE_MAP(CSetCurrentProject, CDialog)
END_MESSAGE_MAP()

BOOL CSetCurrentProject::OnInitDialog()
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

	m_listAvailableProjects.InsertColumn(0, "Available Projects", LVCFMT_LEFT, rect.right - rect.left, 0 );
	m_listAvailableProjects.SetImageList(&m_projectListImage, LVSIL_SMALL);
	m_listAvailableProjects.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);

	for( CUInt i = 0; i < g_projects.size(); i++ )
	{
		CChar projectName[MAX_NAME_SIZE];
		Cpy( projectName, g_projects[i]->m_name );
		InserItemToAvailableProjectsList( projectName, g_projects[i]->m_isActive );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

CVoid CSetCurrentProject::InserItemToAvailableProjectsList( char * projectName, CBool isActive )
{
	availableProjectIndex++;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = availableProjectIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = projectName;
	m_listAvailableProjects.InsertItem(&lvItem);
	if( isActive )
	{
		m_listAvailableProjects.SetItemState(availableProjectIndex, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
		m_listAvailableProjects.SetSelectionMark(availableProjectIndex);
	}
	m_listAvailableProjects.EnsureVisible(availableProjectIndex, FALSE);
	m_listAvailableProjects.UpdateWindow();
}

void CSetCurrentProject::OnOK()
{
	int nSelected = -1; 
	POSITION p = m_listAvailableProjects.GetFirstSelectedItemPosition();
	while(p)
	{
		nSelected = m_listAvailableProjects.GetNextSelectedItem(p);
	}
	if( nSelected >= 0 )
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

		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			if(g_projects[i]->m_isActive)
			{
				if( Cmp( szBuffer, g_projects[i]->m_name ) )
				{
					MessageBox("This project is already activated!", "Error", MB_OK | MB_ICONINFORMATION);
					return; // no need to switch projects
				}
			}
		}
		//switch projects
		//close curren open VScene
		if(!ex_pVandaEngineDlg->OnMenuClickedNew(CTrue))
			return;
	
		//fist of all, mark all as inactive
		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			g_projects[i]->m_isActive = CFalse;
		}
		//then find the selected project and mark it as active
		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			if( Cmp( szBuffer, g_projects[i]->m_name ) )
			{
				g_projects[i]->m_isActive = CTrue;
				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "Project ' %s ' set to current.", g_projects[i]->m_name);
				MessageBox(temp, "Report", MB_OK | MB_ICONINFORMATION);
				break;
			}
		}


		//change current directory
		Cpy( g_currentProjectPath, g_projectsPath );
		Append( g_currentProjectPath, szBuffer );
		Append( g_currentProjectPath, "/" );

		//clear VScene names
		g_VSceneNamesOfCurrentProject.clear();
		//then fill it with the VScenes of the selected project
		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			if( g_projects[i]->m_isActive )
			{
				for( CUInt j = 0; j < g_projects[i]->m_sceneNames.size(); j++ )
				{
					g_VSceneNamesOfCurrentProject.push_back( g_projects[i]->m_sceneNames[j].c_str() );
				}
			}
		}
		CChar m_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		if (Cmp(g_currentVSceneName, "\n"))
			Cpy(m_currentVSceneNameWithoutDot, "Untitled");
		else
		{
			Cpy(m_currentVSceneNameWithoutDot, g_currentVSceneName);
			GetWithoutDot(m_currentVSceneNameWithoutDot);
		}

		CChar temp[256];
		sprintf(temp, "%s%s%s%s%s", "Vanda Engine 2.9.4 (", szBuffer, " - ", m_currentVSceneNameWithoutDot, ")");
		ex_pVandaEngineDlg->SetWindowTextA(temp);
		//save the changes to projects.dat
		FILE *ProjectsFilePtr;
		CChar DATPath[MAX_NAME_SIZE];
		sprintf( DATPath, "%s%s", g_projectsPath, "projects.dat" );

		DeleteFile( DATPath );
		ProjectsFilePtr =  fopen( DATPath, "wb" );
		if( !ProjectsFilePtr )
		{
			MessageBox( "Couldn't open 'assets/Projects/projects.dat' to save data!", "Vanda Engine Error", MB_OK | MB_ICONERROR);
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


		CDialog::OnOK();
	}
	else
	{
		MessageBoxA( "Please select a project" );
	}

}
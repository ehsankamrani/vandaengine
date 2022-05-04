//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditProjectProperties.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditProjectProperties.h"
#include "afxdialogex.h"


// CEditProjectProperties dialog

IMPLEMENT_DYNAMIC(CEditProjectProperties, CDialog)

CEditProjectProperties::CEditProjectProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CEditProjectProperties::IDD, pParent)
	, m_strProjectName(_T(""))
{
	m_edit = CFalse;
}

CEditProjectProperties::~CEditProjectProperties()
{
}

CVoid CEditProjectProperties::SetName(CChar* name)
{
	m_strProjectName = name;
	m_strOldProjectName = name; //for editing
}


CVoid CEditProjectProperties::SetEdit(CBool edit)
{
	m_edit = edit;
}

void CEditProjectProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROJECT_NAME, m_editBoxProjectName);
}


BEGIN_MESSAGE_MAP(CEditProjectProperties, CDialog)
	ON_EN_CHANGE(IDC_PROJECT_NAME, &CEditProjectProperties::OnEnChangeProjectName)
END_MESSAGE_MAP()


// CEditProjectProperties message handlers


void CEditProjectProperties::OnOK()
{
	CChar strUp[MAX_NAME_SIZE];
	Cpy(strUp, (LPCTSTR)m_strProjectName);

	if (CmpIn(strUp, "/") || CmpIn(strUp, "\\") || CmpIn(strUp, "?") || CmpIn(strUp, "*")
		|| CmpIn(strUp, ">") || CmpIn(strUp, "<") || CmpIn(strUp, "\"") || CmpIn(strUp, ":")
		|| CmpIn(strUp, "|"))
	{
		MessageBox("You cannot use / \\ ? * > < \" : | characters in new directory name", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (Cmp(strUp, "Resources"))
	{
		MessageBox("'Resources' is a reserved name. Please select another name.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	StringToUpper(strUp);

	if (Cmp(strUp, "PRJ") || CmpIn(strUp, "VANDA_") && !g_admin)
	{
		MessageBox("VANDA_ and PRJ are reserved project names. Please choose another name.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if( m_strProjectName.IsEmpty() )
	{
		MessageBox( "Please choose a name for the new project!" );
		return;
	}
	else
	{
		CChar m_oldProjectPath[MAX_NAME_SIZE];

		CChar newProjectName[MAX_NAME_SIZE];
		Cpy(newProjectName, (LPCTSTR)m_strProjectName);

		//make sure project name doesn't exists
		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			if( Cmp(newProjectName, g_projects[i]->m_name ) )
			{
				MessageBox( "This name already exists. Please choose another name" );
				return;
			}
		}
		
		if( m_edit )
		{
			for( CUInt i = 0; i < g_projects.size(); i++ )
			{
				if( g_projects[i]->m_isActive )
				{
					if( Cmp(newProjectName, g_projects[i]->m_name ) ) //user didn't change anything, so we should return
					{
						CDialog::OnOK();
						return;
					}
				}
			}

			//close curren open VScene
			if(!ex_pVandaEngine1Dlg->OnMenuClickedNew(CTrue) )
				return;
			
			//rename current directory
			CChar newFileName[MAX_NAME_SIZE];
			Cpy( newFileName, g_projectsPath );
			Append( newFileName, newProjectName );
			rename(g_currentProjectPath, newFileName);

			//change current project path
			Cpy(m_oldProjectPath, g_currentProjectPath);

			Cpy( g_currentProjectPath, g_projectsPath );
			Append( g_currentProjectPath, newProjectName );
			Append( g_currentProjectPath, "/" );

			//change project name
			for( CUInt i = 0; i < g_projects.size(); i++ )
			{
				if( g_projects[i]->m_isActive )
				{
					Cpy(g_projects[i]->m_name, newProjectName);
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
			sprintf(temp, "%s%s%s%s%s", "Vanda Engine 1.8.5 (", newProjectName, " - ", m_currentVSceneNameWithoutDot, ")");
			ex_pVandaEngine1Dlg->SetWindowTextA(temp);

			//save changes to projects.dat
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
			fwrite( &numProjects, sizeof( CInt ), 1, ProjectsFilePtr  );
			fclose(ProjectsFilePtr);

			for(CInt i = 0; i < numProjects; i++ )
			{
				CChar filePath[MAX_URI_SIZE];
				sprintf(filePath, "%s%s%s%s", g_projectsPath, "PRJ/", g_projects[i]->m_name, ".prj");
				ProjectsFilePtr = fopen(filePath, "wb");

				fwrite( g_projects[i]->m_name, sizeof( CChar ), MAX_NAME_SIZE, ProjectsFilePtr  );
				CInt numScenes = (CInt)g_projects[i]->m_sceneNames.size();
				fwrite( &numScenes, sizeof( CInt ), 1, ProjectsFilePtr  );
				for( CInt j = 0; j < numScenes; j++ )
				{
					CChar vsceneName[MAX_NAME_SIZE];
					Cpy( vsceneName, g_projects[i]->m_sceneNames[j].c_str() );
					fwrite( vsceneName, sizeof( CChar ), MAX_NAME_SIZE, ProjectsFilePtr );
				}
				fwrite( &g_projects[i]->m_isActive, sizeof( CBool ), 1, ProjectsFilePtr  );

				fclose(ProjectsFilePtr);

			}
			//delete old project
			CChar filePath[MAX_URI_SIZE];
			sprintf(filePath, "%s%s%s%s", g_projectsPath, "PRJ/", m_strOldProjectName, ".prj");
			DeleteFile(filePath);
			////////////////


			CDialog::OnOK();
			return;
		}
		//close curren open VScene
		if(!ex_pVandaEngine1Dlg->OnMenuClickedNew(CTrue))
			return;

		//mark all of the previous projects as inactive
		for( CUInt i = 0; i < g_projects.size(); i++ )
		{
			g_projects[i]->m_isActive = CFalse;
		}

		//push new project to g_projects
		CProjects* newProject = CNew(CProjects);
		Cpy(newProject->m_name, newProjectName ); 
		newProject->m_isActive = CTrue;
		g_projects.push_back(newProject);

		//change current directory
		Cpy( g_currentProjectPath, g_projectsPath );
		Append( g_currentProjectPath, newProjectName );
		Append( g_currentProjectPath, "/" );

		CChar m_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		if (Cmp(g_currentVSceneName, "\n"))
			Cpy(m_currentVSceneNameWithoutDot, "Untitled");
		else
		{
			Cpy(m_currentVSceneNameWithoutDot, g_currentVSceneName);
			GetWithoutDot(m_currentVSceneNameWithoutDot);
		}

		CChar temp[256];
		sprintf(temp, "%s%s%s%s%s", "Vanda Engine 1.8.5 (", newProject->m_name, " - ", m_currentVSceneNameWithoutDot, ")");
		ex_pVandaEngine1Dlg->SetWindowTextA(temp);

		//create new directory
		CreateWindowsDirectory( g_currentProjectPath ); //default project directory

		//clear VScene names of current directory. By default, we have no VScene
		g_VSceneNamesOfCurrentProject.clear();

		//save to projects.dat
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
}


void CEditProjectProperties::OnEnChangeProjectName()
{
	m_editBoxProjectName.GetWindowTextA( m_strProjectName );
}


BOOL CEditProjectProperties::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editBoxProjectName.SetWindowTextA( m_strProjectName );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

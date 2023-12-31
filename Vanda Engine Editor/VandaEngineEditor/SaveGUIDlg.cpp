//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// SaveGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "SaveGUIDlg.h"
#include "afxdialogex.h"


// CSaveGUIDlg dialog

IMPLEMENT_DYNAMIC(CSaveGUIDlg, CDialog)

CSaveGUIDlg::CSaveGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveGUIDlg::IDD, pParent)
{
	m_guiNameDlg = NULL;
}

CSaveGUIDlg::~CSaveGUIDlg()
{
}

void CSaveGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GUI_NAME, m_editBoxGUIName);
	DDX_Control(pDX, IDC_COMB_GUI_PACKAGE, m_guiPackageList);
}


BEGIN_MESSAGE_MAP(CSaveGUIDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PACKAGE, &CSaveGUIDlg::OnBnClickedButtonAddPackage)
	ON_EN_CHANGE(IDC_GUI_NAME, &CSaveGUIDlg::OnEnChangeGuiName)
	ON_BN_CLICKED(IDOK, &CSaveGUIDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSaveGUIDlg message handlers


void CSaveGUIDlg::OnBnClickedButtonAddPackage()
{
	m_guiNameDlg = CNew(CGUINameDlg);
	m_guiNameDlg->SetInitialData("\n", "\n", CTrue);
	if (IDOK == m_guiNameDlg->DoModal())
	{
		m_guiPackageList.InsertString(m_guiPackageList.GetCount(), m_guiNameDlg->GetNewName());
		m_guiPackageList.SetCurSel(m_guiPackageList.GetCount() - 1);
		m_guiPackageList.UpdateWindow();
	}
	CDelete(m_guiNameDlg);
}


void CSaveGUIDlg::OnEnChangeGuiName()
{
	m_editBoxGUIName.GetWindowTextA(m_strGUIName);
}


BOOL CSaveGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
	{
		m_guiPackageList.InsertString(i, g_guiPackagesAndNames[i].front().c_str());
	}

	if (g_guiPackagesAndNames.size())
	{
		m_guiPackageList.SetCurSel(0);
		m_guiPackageList.UpdateWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSaveGUIDlg::OnBnClickedOk()
{
	CInt packageIndex;
	CChar new_name[MAX_NAME_SIZE];

	if (g_guiPackagesAndNames.size() == 0)
	{
		MessageBox("Please select a package!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if (m_strGUIName.IsEmpty())
	{
		MessageBox("Please choose a name for the new GUI element!");
		return;
	}
	else
	{
		packageIndex = m_guiPackageList.GetCurSel();

		strcpy(new_name, (LPCTSTR)m_strGUIName);
		//check the sub items of this package. Skip the first element. First one is the package name
		for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
		{
			if (i == 0) continue;
			if (Cmp(g_guiPackagesAndNames[packageIndex][i].c_str(), new_name))
			{
				MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
				return;
			}
		}
		//save gui
		g_guiPackagesAndNames[packageIndex].push_back(new_name);
	}
	CChar packageName[MAX_NAME_SIZE];
	sprintf(packageName, "%s", g_guiPackagesAndNames[packageIndex].front().c_str());
	m_strNewGUIPackageName = packageName;

	m_strNewGUIName = new_name;

	CChar packageAndGUIName[MAX_NAME_SIZE];
	sprintf(packageAndGUIName, "%s%s%s", g_guiPackagesAndNames[packageIndex].front().c_str(), "_", new_name);
	m_strNewPackageAndGUIName = packageAndGUIName;
	ex_pVandaEngineDlg->SaveGUIFiles();
	CDialog::OnOK();
}

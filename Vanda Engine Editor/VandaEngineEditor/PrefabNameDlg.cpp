//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// PrefabNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "PrefabNameDlg.h"
#include "afxdialogex.h"


// CPrefabNameDlg dialog

IMPLEMENT_DYNAMIC(CPrefabNameDlg, CDialog)

CPrefabNameDlg::CPrefabNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrefabNameDlg::IDD, pParent)
{
}

CPrefabNameDlg::~CPrefabNameDlg()
{
}

void CPrefabNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREFAB_NAME, m_editBoxName);
}

BEGIN_MESSAGE_MAP(CPrefabNameDlg, CDialog)
	ON_EN_CHANGE(IDC_PREFAB_NAME, &CPrefabNameDlg::OnEnChangePrefabName)
END_MESSAGE_MAP()


// CPrefabNameDlg message handlers


BOOL CPrefabNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_package && m_rename)
		m_editBoxName.SetWindowTextA(m_selectedPackageName.c_str());
	else if (!m_package && m_rename)
		m_editBoxName.SetWindowTextA(m_selectedPrefabName.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefabNameDlg::OnOK()
{
	CInt packageIndex = -1;
	CInt prefabIndex = -1;
	CBool renameItem = CFalse;
	m_editBoxName.GetWindowTextA(m_strName);
	CChar str[MAX_NAME_SIZE];
	Cpy(str, (LPCTSTR)m_strName);

	if (CmpIn(str, "/") || CmpIn(str, "\\") || CmpIn(str, "?") || CmpIn(str, "*")
		|| CmpIn(str, ">") || CmpIn(str, "<") || CmpIn(str, "\"") || CmpIn(str, ":")
		|| CmpIn(str, "|"))
	{
		MessageBox("You cannot use / \\ ? * > < \" : | characters in new directory name", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CChar strUp[MAX_NAME_SIZE];
	Cpy(strUp, str);
	StringToUpper(strUp);
	if (!g_admin)
	{
		if (Cmp(strUp, "PKG") || CmpIn(strUp, "VANDA_"))
		{
			MessageBox("VANDA_ and PKG are reserved names. Please choose another name.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}
	if (Cmp(str, "\n"))
	{
		MessageBoxA("Please enter a name!", "Vanda Engine Error", MB_ICONERROR);
		return;
	}
	for (CUInt i = 0; i < g_prefabPackagesAndNames.size(); i++)
	{
		if (Cmp(g_prefabPackagesAndNames[i].front().c_str(), m_selectedPackageName.c_str()))
		{
			packageIndex = i;
			break;
		}
	}

	//make sure that name is unique
	if (m_package) //prefab package
	{
		if (m_rename)
		{
			if (Cmp(str, m_selectedPackageName.c_str()))
			{
				renameItem = CFalse;
			}
			else
			{
				for (CUInt i = 0; i < g_prefabPackagesAndNames.size(); i++)
				{
					if (i != packageIndex)
					{
						if (Cmp(g_prefabPackagesAndNames[i].front().c_str(), str))
						{
							MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
							return;
						}
					}
				}
				renameItem = CTrue;
			}
		}
		else
		{
			for (CUInt i = 0; i < g_prefabPackagesAndNames.size(); i++)
			{
				if (Cmp(g_prefabPackagesAndNames[i].front().c_str(), str))
				{
					MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
					return;
				}
			}
		}
	}
	else //prefab
	{
		if (packageIndex != -1)
		{
			if (m_rename)
			{
				if (Cmp(str, m_selectedPrefabName.c_str()))
				{
					renameItem = CFalse;
				}
				else
				{
					//check the sub items of this package. Skip the first element. First one is the package name
					for (CUInt i = 0; i < g_prefabPackagesAndNames[packageIndex].size(); i++)
					{
						if (i == 0) continue;
						if (Cmp(g_prefabPackagesAndNames[packageIndex][i].c_str(), m_selectedPrefabName.c_str()))
						{
							prefabIndex = i;
						}
					}
					//check the sub items of this package. Skip the first element. First one is the package name
					for (CUInt i = 0; i < g_prefabPackagesAndNames[packageIndex].size(); i++)
					{
						if (i == 0) continue;
						if (i != prefabIndex)
						{
							if (Cmp(g_prefabPackagesAndNames[packageIndex][i].c_str(), str))
							{
								MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
								return;
							}
						}
					}
					renameItem = CTrue;
				}
			}
			else
			{
				//check the sub items of this package. Skip the first element. First one is the package name
				for (CUInt i = 0; i < g_prefabPackagesAndNames[packageIndex].size(); i++)
				{
					if (i == 0) continue;
					if (Cmp(g_prefabPackagesAndNames[packageIndex][i].c_str(), str))
					{
						MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
						return;
					}
				}
			}
		}
	}

	m_newName = str;
	if (m_package) //prefab package
	{
		if (m_rename)
		{
			if (renameItem)
			{
				g_prefabPackagesAndNames[packageIndex][0] = str;
			}
		}
		else
		{
			g_prefabPackagesAndNames.push_back(std::vector<std::string>());
			//push new name to last element
			g_prefabPackagesAndNames[g_prefabPackagesAndNames.size() - 1].push_back(m_newName);
		}
	}
	else //prefab item
	{
		if (packageIndex != -1)
		{
			if (m_rename)
			{
				if (renameItem)
				{
					g_prefabPackagesAndNames[packageIndex][prefabIndex] = str;
				}
			}
			else
			{
				g_prefabPackagesAndNames[packageIndex].push_back(m_newName);
			}
		}
		else
		{
			MessageBox("Package Index is -1!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
			return;
		}

	}

	CDialog::OnOK();
}

void CPrefabNameDlg::OnEnChangePrefabName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

CVoid CPrefabNameDlg::SetInitialData(std::string selectedPackageName, std::string selectedPrefabName, CBool package, CBool rename)
{
	m_selectedPackageName = selectedPackageName;
	m_selectedPrefabName = selectedPrefabName;

	m_package = package;
	m_rename = rename;
}

CChar* CPrefabNameDlg::GetNewName()
{
	return (CChar*)m_newName.c_str();
}


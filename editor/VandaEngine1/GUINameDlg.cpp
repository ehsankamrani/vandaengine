//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// GUINameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "GUINameDlg.h"
#include "afxdialogex.h"


// CGUINameDlg dialog

IMPLEMENT_DYNAMIC(CGUINameDlg, CDialog)

CGUINameDlg::CGUINameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGUINameDlg::IDD, pParent)
{

}

CGUINameDlg::~CGUINameDlg()
{
}

void CGUINameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GUI_NAME, m_editBoxName);
}


BEGIN_MESSAGE_MAP(CGUINameDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CGUINameDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_GUI_NAME, &CGUINameDlg::OnEnChangeGuiName)
END_MESSAGE_MAP()


// CGUINameDlg message handlers


BOOL CGUINameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_package && m_rename)
		m_editBoxName.SetWindowTextA(m_selectedPackageName.c_str());
	else if (!m_package && m_rename)
		m_editBoxName.SetWindowTextA(m_selectedGUIName.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CGUINameDlg::OnBnClickedOk()
{
	CInt packageIndex = -1;
	CInt guiIndex = -1;
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

	if (Cmp(str, "\n"))
	{
		MessageBoxA("Please enter a name!", "Vanda Engine Error", MB_ICONERROR);
		return;
	}
	for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
	{
		if (Cmp(g_guiPackagesAndNames[i].front().c_str(), m_selectedPackageName.c_str()))
		{
			packageIndex = i;
			break;
		}
	}

	//make sure that name is unique
	if (m_package) //gui package
	{
		if (m_rename)
		{
			if (Cmp(str, m_selectedPackageName.c_str()))
			{
				renameItem = CFalse;
			}
			else
			{
				for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
				{
					if (i != packageIndex)
					{
						if (Cmp(g_guiPackagesAndNames[i].front().c_str(), str))
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
			for (CUInt i = 0; i < g_guiPackagesAndNames.size(); i++)
			{
				if (Cmp(g_guiPackagesAndNames[i].front().c_str(), str))
				{
					MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
					return;
				}
			}
		}
	}
	else //GUI
	{
		if (packageIndex != -1)
		{
			if (m_rename)
			{
				if (Cmp(str, m_selectedGUIName.c_str()))
				{
					renameItem = CFalse;
				}
				else
				{
					//check the sub items of this package. Skip the first element. First one is the package name
					for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
					{
						if (i == 0) continue;
						if (Cmp(g_guiPackagesAndNames[packageIndex][i].c_str(), m_selectedGUIName.c_str()))
						{
							guiIndex = i;
						}
					}
					//check the sub items of this package. Skip the first element. First one is the package name
					for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
					{
						if (i == 0) continue;
						if (i != guiIndex)
						{
							if (Cmp(g_guiPackagesAndNames[packageIndex][i].c_str(), str))
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
				for (CUInt i = 0; i < g_guiPackagesAndNames[packageIndex].size(); i++)
				{
					if (i == 0) continue;
					if (Cmp(g_guiPackagesAndNames[packageIndex][i].c_str(), str))
					{
						MessageBox("This name already exists!", "Vanda Engine Error", MB_ICONERROR | MB_OK);
						return;
					}
				}
			}
		}
	}

	m_newName = str;
	if (m_package) //gui package
	{
		if (m_rename)
		{
			if (renameItem)
			{
				g_guiPackagesAndNames[packageIndex][0] = str;
			}
		}
		else
		{
			g_guiPackagesAndNames.push_back(std::vector<std::string>());
			//push new name to last element
			g_guiPackagesAndNames[g_guiPackagesAndNames.size() - 1].push_back(m_newName);
		}
	}
	else //gui item
	{
		if (packageIndex != -1)
		{
			if (m_rename)
			{
				if (renameItem)
				{
					g_guiPackagesAndNames[packageIndex][guiIndex] = str;
				}
			}
			else
			{
				g_guiPackagesAndNames[packageIndex].push_back(m_newName);
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

CVoid CGUINameDlg::SetInitialData(std::string selectedPackageName, std::string selectedGUIName, CBool package, CBool rename)
{
	m_selectedPackageName = selectedPackageName;
	m_selectedGUIName = selectedGUIName;

	m_package = package;
	m_rename = rename;
}

CChar* CGUINameDlg::GetNewName()
{
	return (CChar*)m_newName.c_str();
}


void CGUINameDlg::OnEnChangeGuiName()
{
	m_editBoxName.GetWindowTextA(m_strName);
}

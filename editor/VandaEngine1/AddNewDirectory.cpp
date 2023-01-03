//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license
// AddNewDirectory.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "AddNewDirectory.h"
#include "afxdialogex.h"


// CAddNewDirectory dialog

IMPLEMENT_DYNAMIC(CAddNewDirectory, CDialog)

CAddNewDirectory::CAddNewDirectory(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNewDirectory::IDD, pParent)
	, m_strNewDirectory(_T(""))
{

}

CAddNewDirectory::~CAddNewDirectory()
{
}

void CAddNewDirectory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIRECTORY_NAME, m_editNewDirectory);
}


BEGIN_MESSAGE_MAP(CAddNewDirectory, CDialog)
	ON_EN_CHANGE(IDC_DIRECTORY_NAME, &CAddNewDirectory::OnEnChangeDirectoryName)
	ON_BN_CLICKED(IDOK, &CAddNewDirectory::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddNewDirectory message handlers


void CAddNewDirectory::OnEnChangeDirectoryName()
{
	m_editNewDirectory.GetWindowTextA(m_strNewDirectory);
}


void CAddNewDirectory::OnBnClickedOk()
{
	Cpy(m_newDirectory, m_strNewDirectory.GetBuffer(m_strNewDirectory.GetLength()));
	if (CmpIn(m_newDirectory, "/") || CmpIn(m_newDirectory, "\\") || CmpIn(m_newDirectory, "?") || CmpIn(m_newDirectory, "*")
		|| CmpIn(m_newDirectory, ">") || CmpIn(m_newDirectory, "<") || CmpIn(m_newDirectory, "\"") || CmpIn(m_newDirectory, ":")
		|| CmpIn(m_newDirectory, "|"))
	{
		MessageBox("You cannot use / \\ ? * > < \" : | characters in new directory name", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (m_strNewDirectory.IsEmpty())
	{
		MessageBox("Please choose a name!", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
		return;
	}

	for (CInt i = 0; i < (CInt)g_projectResourceNames.size(); i++)
	{
		if (Cmp(g_projectResourceNames[i].front().c_str(), m_newDirectory))
		{
			MessageBox("This directory name already exists. Please enter another name.", "Vanda Engine Error", MB_OK | MB_ICONERROR);
			return;
		}
	}

	CDialog::OnOK();
}

CChar* CAddNewDirectory::GetDirectoryName()
{
	return m_newDirectory;
}

BOOL CAddNewDirectory::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

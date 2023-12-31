//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// BackupAllProjects.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "BackupAllProjects.h"
#include "afxdialogex.h"


// CBackupAllProjects dialog

IMPLEMENT_DYNAMIC(CBackupAllProjects, CDialog)

CBackupAllProjects::CBackupAllProjects(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupAllProjects::IDD, pParent)
{

}

CBackupAllProjects::~CBackupAllProjects()
{
}

void CBackupAllProjects::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DESTINATION, m_editBoxDestination);
}


BEGIN_MESSAGE_MAP(CBackupAllProjects, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DESTINATION, &CBackupAllProjects::OnBnClickedButtonDestination)
	ON_BN_CLICKED(IDOK, &CBackupAllProjects::OnBnClickedOk)
END_MESSAGE_MAP()


// CBackupAllProjects message handlers


void CBackupAllProjects::OnBnClickedButtonDestination()
{
	BROWSEINFO   bi;
	ZeroMemory(&bi, sizeof(bi));
	TCHAR   szDisplayName[MAX_PATH];
	szDisplayName[0] = _T('S');

	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = _T("Please select a folder");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lParam = NULL;
	bi.iImage = 0;

	LPITEMIDLIST   pidl = SHBrowseForFolder(&bi);
	TCHAR   szPathName[MAX_PATH];
	if (NULL != pidl)
	{
		BOOL bRet = SHGetPathFromIDList(pidl, szPathName);
		if (FALSE == bRet)
			return;
		m_strDestination = (CString)szPathName;
		m_editBoxDestination.SetWindowTextA(m_strDestination);
	}
}

CChar* CBackupAllProjects::GetSrcPath()
{
	return m_srcPath;
}

CChar* CBackupAllProjects::GetDstPath()
{
	return m_dstPath;
}

void CBackupAllProjects::OnBnClickedOk()
{
	if (m_strDestination.IsEmpty())
	{
		MessageBox("Please select destination path", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	CChar docPath[MAX_URI_SIZE];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
	if (result != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder", COLOR_RED);
		return;
	}
	sprintf(m_srcPath, "%s%s", docPath, "/Vanda/");

	sprintf(m_dstPath, "%s%s", (LPCSTR)m_strDestination, "/Vanda/");

	CreateWindowsDirectory(m_dstPath);

	CDialog::OnOK();
}

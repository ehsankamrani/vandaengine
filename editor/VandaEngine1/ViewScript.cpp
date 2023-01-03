//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// ViewScript.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ViewScript.h"
#include "afxdialogex.h"


// CViewScript dialog

IMPLEMENT_DYNAMIC(CViewScript, CDialog)

CViewScript::CViewScript(CWnd* pParent /*=NULL*/)
	: CDialog(CViewScript::IDD, pParent)
{

}

CViewScript::~CViewScript()
{
}

void CViewScript::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_VIEW_SCRIPT, m_richViewScript);
}


BEGIN_MESSAGE_MAP(CViewScript, CDialog)
END_MESSAGE_MAP()


// CViewScript message handlers


BOOL CViewScript::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CHARFORMAT cfDefault;
	cfDefault.cbSize = sizeof(cfDefault);
	cfDefault.dwEffects = CFE_PROTECTED;
	cfDefault.dwMask = CFM_BOLD | CFM_FACE | CFM_SIZE | CFM_CHARSET | CFM_PROTECTED | CFM_COLOR;
	cfDefault.yHeight = 11 * 20;
	cfDefault.crTextColor = RGB(0, 0, 0);
	cfDefault.bCharSet = 0;
	strcpy(cfDefault.szFaceName, _T("Consolas"));// or "Times New Roman" etc etc

	m_richViewScript.SetDefaultCharFormat(cfDefault);
	m_richViewScript.SetEventMask(ENM_CHANGE | ENM_SELCHANGE | ENM_PROTECTED);
	m_richViewScript.SetBackgroundColor(FALSE, RGB(255, 255, 255));

	LoadFile(m_scriptPath);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CViewScript::LoadFile(CChar* filePath)
{
	std::string buffer;
	std::ifstream file(filePath, std::ios::binary);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);

		std::ifstream::pos_type fileSize = file.tellg();

		buffer.resize(fileSize);
		file.seekg(0, std::ios::beg);
		file.read(&buffer[0], fileSize);
	}
	else
	{
		MessageBox("Couldn't open the file", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	CString c1(buffer.c_str());
	// writing the file to rich edit control
	m_richViewScript.SetWindowTextA(c1.GetBuffer());

	return;
}

//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// EditGUI.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditGUI.h"
#include "afxdialogex.h"


// CEditGUI dialog

IMPLEMENT_DYNAMIC(CEditGUI, CDialog)

CEditGUI::CEditGUI(CWnd* pParent /*=NULL*/)
	: CDialog(CEditGUI::IDD, pParent)
{

}

CEditGUI::~CEditGUI()
{
}

void CEditGUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHED_GUI_INSTANCE_NAME, m_richGUIInstanceName);
	DDX_Control(pDX, IDC_STATIC_GUI_INSTANCE_NAME, m_textGUIName);
	DDX_Control(pDX, IDC_PHOTO, m_imageCtrl);
}


BEGIN_MESSAGE_MAP(CEditGUI, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COPY_GUI_INSTANCE_NAME, &CEditGUI::OnBnClickedButtonCopyGuiInstanceName)
END_MESSAGE_MAP()


// CEditGUI message handlers


void CEditGUI::OnBnClickedButtonCopyGuiInstanceName()
{
	CString s;
	m_richGUIInstanceName.GetWindowTextA(s);
	if (s.IsEmpty())
		MessageBox("Couldn't find the GUI name!", "Error", MB_OK | MB_ICONERROR);
	else
	{
		m_richGUIInstanceName.Copy();
		CChar message[MAX_URI_SIZE];
		sprintf(message, "GUI name '%s' copied to clipboard", (LPCSTR)s);
		MessageBox(message, "Report", MB_OK | MB_ICONINFORMATION);
	}
}

CVoid CEditGUI::SetGUIInstance(CGUI* instance_gui)
{
	m_instanceGUI = instance_gui;
}

BOOL CEditGUI::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_instanceGUI)
	{
		//prefab instance name
		m_textGUIName.SetWindowTextA(m_instanceGUI->GetName());
		m_richGUIInstanceName.SetWindowTextA(m_instanceGUI->GetName());
		CInt end = m_richGUIInstanceName.GetWindowTextLengthA();
		m_richGUIInstanceName.SetSel(0, end);

		UpdatePreview();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CEditGUI::UpdatePreview()
{
	if (!m_instanceGUI)
		return;

	DeleteObject(m_hBitmap);
	//get document folder
	CChar docPath[MAX_URI_SIZE];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, docPath);
	if (result != S_OK)
	{
		PrintInfo("\nCouldn't get the documents folder", COLOR_RED);
		return;
	}

	CChar GUIPath[MAX_URI_SIZE];
	sprintf(GUIPath, "%s%s%s%s%s%s%s%s%s%s", docPath, "/Vanda/GUIs/", m_instanceGUI->GetPackageName(), "/", m_instanceGUI->GetGUIName(), "/", m_instanceGUI->GetPackageName(), "_", m_instanceGUI->GetGUIName(), ".bmp");
	m_hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), GUIPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_imageCtrl.SetBitmap(m_hBitmap);

}
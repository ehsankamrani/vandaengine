// CurrentSceneOptions.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "EditCurrentSceneOptions.h"
#include "afxdialogex.h"


// CEditCurrentSceneOptions dialog

IMPLEMENT_DYNAMIC(CEditCurrentSceneOptions, CDialog)

CEditCurrentSceneOptions::CEditCurrentSceneOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCurrentSceneOptions::IDD, pParent)
{
	setBanner = CFalse;
}

CEditCurrentSceneOptions::~CEditCurrentSceneOptions()
{
}

void CEditCurrentSceneOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BANNER, m_editBoxBanner);
	DDX_Control(pDX, IDC_CHECKBOX_SETASMENU, m_checkboxSetMenu);
	DDX_Control(pDX, IDC_EDIT_CURSOR_ICON, m_editBoxCursorIcon);
	DDX_Control(pDX, IDC_BTN_LOADING_CURSOR_ICON, m_btnCursorIcon);
	DDX_Control(pDX, IDC_EDIT_CURSOR_PERCENT, m_editBoxCursorSize);
}


BEGIN_MESSAGE_MAP(CEditCurrentSceneOptions, CDialog)
	ON_BN_CLICKED(IDC_BTN_LOADING_BANNER, &CEditCurrentSceneOptions::OnBnClickedBtnLoadingBanner)
	ON_BN_CLICKED(IDC_BTN_LOADING_CURSOR_ICON, &CEditCurrentSceneOptions::OnBnClickedBtnLoadingCursorIcon)
	ON_BN_CLICKED(IDC_CHECKBOX_SETASMENU, &CEditCurrentSceneOptions::OnBnClickedCheckboxSetasmenu)
	ON_EN_CHANGE(IDC_EDIT_CURSOR_PERCENT, &CEditCurrentSceneOptions::OnEnChangeEditCursorPercent)
END_MESSAGE_MAP()


// CEditCurrentSceneOptions message handlers


void CEditCurrentSceneOptions::OnBnClickedBtnLoadingBanner()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		setBanner = CTrue;
		m_strBanner = (CString)dlgOpen.GetPathName();
		m_editBoxBanner.SetWindowText(m_strBanner);
	}
}


BOOL CEditCurrentSceneOptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_editBoxBanner.SetWindowTextA(g_sceneBanner.GetBannerPath());
	m_editBoxBanner.GetWindowTextA(m_strBanner);

	if (g_currentVSceneProperties.m_isMenu)
	{
		m_checkboxSetMenu.SetCheck(BST_CHECKED);
		//m_editBoxCursorIcon.EnableWindow();
		//m_btnCursorIcon.EnableWindow();
		m_editBoxCursorSize.EnableWindow();
	}
	else
	{
		m_checkboxSetMenu.SetCheck(BST_UNCHECKED);
		//m_editBoxCursorIcon.EnableWindow(0);
		//m_btnCursorIcon.EnableWindow(0);
		//m_editBoxCursorIcon.SetWindowTextA("");
		m_editBoxCursorSize.EnableWindow(0);
	}

	m_cursorSize = g_currentVSceneProperties.m_cursorSize;
	m_strCursorSize.Format("%d", m_cursorSize);
	m_editBoxCursorSize.SetWindowTextA(m_strCursorSize);

	m_editBoxCursorIcon.SetWindowTextA(g_vsceneMenuCursor.GetCursorPath());
	m_editBoxCursorIcon.GetWindowTextA(m_strCursorImage);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditCurrentSceneOptions::OnOK()
{
	if (g_multipleView->IsPlayGameMode())
	{
		if (MessageBox("Exit from play mode?", "Vanda Engine", MB_YESNO | MB_ICONINFORMATION) == IDYES)
		{
			ex_pVandaEngine1Dlg->OnBnClickedBtnPlayActive();

		}
		else
		{
			return;
		}
	}

	CInt checkState;
	checkState = m_checkboxSetMenu.GetCheck();

	if (checkState == BST_CHECKED && m_strCursorImage.IsEmpty())
	{
		MessageBox("Please Choose Cursor Icon", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}
	if (checkState == BST_CHECKED && m_strCursorSize.IsEmpty())
	{
		MessageBox("Please Fill In Cursor Size", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (m_strBanner.IsEmpty())
	{
		MessageBox("Please Choose Banner", "Vanda Engine Error", MB_OK | MB_ICONERROR);
		return;
	}

	if (checkState == BST_CHECKED)
	{
		g_currentVSceneProperties.m_isMenu = CTrue;
		g_currentVSceneProperties.m_cursorSize = m_cursorSize;
	}
	else
	{
		g_currentVSceneProperties.m_isMenu = CFalse;
	}

	//Save Cursor Image
	Cpy(g_currentVSceneProperties.m_strCursorImage, m_strCursorImage.GetBuffer(m_strCursorImage.GetLength()));
	m_strCursorImage.ReleaseBuffer();

	g_vsceneMenuCursor.SetCursorPath((CChar*)m_strCursorImage.GetBuffer(m_strCursorImage.GetLength()));
	m_strCursorImage.ReleaseBuffer();
	//save functions/////////////////////////////////
	for (CUInt index = 0; index < g_VSceneNamesOfCurrentProject.size(); index++)
	{
		g_vsceneMenuCursor.IsInVSceneList(g_VSceneNamesOfCurrentProject[index], CFalse, CTrue); //Write to zip file and copy the texture
	}
	//save functions/////////////////////////////////
	Cpy(g_currentVSceneProperties.m_strCursorImage, g_vsceneMenuCursor.GetCursorPath());


	if (setBanner)
	{
		g_sceneBanner.SetBannerPath((CChar*)m_strBanner.GetBuffer(m_strBanner.GetLength()));
		m_strBanner.ReleaseBuffer();
		//save functions/////////////////////////////////
		for (CUInt index = 0; index < g_VSceneNamesOfCurrentProject.size(); index++)
		{
			g_sceneBanner.IsInVSceneList(g_VSceneNamesOfCurrentProject[index], CFalse, CTrue); //Write to zip file and copy the texture
		}
		//save functions/////////////////////////////////
		Cpy(g_currentVSceneProperties.m_strBanner, g_sceneBanner.GetBannerPath());
	}

	CDialog::OnOK();
}


void CEditCurrentSceneOptions::OnBnClickedBtnLoadingCursorIcon()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(TRUE, _T("*.dds"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		_T("DDS File (*.dds)|*.dds||"), NULL, NULL);
	if (IDOK == dlgOpen.DoModal())
	{
		m_strCursorImage = (CString)dlgOpen.GetPathName();
		m_editBoxCursorIcon.SetWindowText(m_strCursorImage);
	}
}


void CEditCurrentSceneOptions::OnBnClickedCheckboxSetasmenu()
{
	CInt checkState;
	checkState = m_checkboxSetMenu.GetCheck();
	if (checkState == BST_CHECKED)
	{
		g_currentVSceneProperties.m_isMenu = CTrue;
		//m_editBoxCursorIcon.EnableWindow();
		//m_btnCursorIcon.EnableWindow();
		m_editBoxCursorSize.EnableWindow();
	}
	else
	{
		g_currentVSceneProperties.m_isMenu = CFalse;
		//m_editBoxCursorIcon.EnableWindow(0);
		//m_btnCursorIcon.EnableWindow(0);
		m_editBoxCursorSize.EnableWindow(0);
	}
}


void CEditCurrentSceneOptions::OnEnChangeEditCursorPercent()
{
	m_editBoxCursorSize.GetWindowTextA(m_strCursorSize);
	m_cursorSize = atoi(m_strCursorSize);
}

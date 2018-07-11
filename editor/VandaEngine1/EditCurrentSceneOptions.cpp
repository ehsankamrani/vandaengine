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
}


BEGIN_MESSAGE_MAP(CEditCurrentSceneOptions, CDialog)
	ON_BN_CLICKED(IDC_BTN_LOADING_BANNER, &CEditCurrentSceneOptions::OnBnClickedBtnLoadingBanner)
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

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditCurrentSceneOptions::OnOK()
{
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

	}

	CDialog::OnOK();
}

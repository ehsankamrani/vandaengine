// ExitEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ExitEditorDlg.h"
#include "afxdialogex.h"


// CExitEditorDlg dialog

IMPLEMENT_DYNAMIC(CExitEditorDlg, CDialog)

CExitEditorDlg::CExitEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExitEditorDlg::IDD, pParent)
{

}

CExitEditorDlg::~CExitEditorDlg()
{
}

void CExitEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_OPEN_WEBSITE, m_btnVisitWebsite);
	DDX_Control(pDX, IDOK, m_btnExit);
	DDX_Control(pDX, IDC_EXIT_BUTTON_UNCHECK, m_btnUncheck);
	DDX_Control(pDX, IDC_EXIT_BUTTON_CHECK, m_btnCheck);
}


BEGIN_MESSAGE_MAP(CExitEditorDlg, CDialog)
	ON_BN_CLICKED(ID_OPEN_WEBSITE, &CExitEditorDlg::OnBnClickedOpenWebsite)
	ON_BN_CLICKED(IDOK, &CExitEditorDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_EXIT_BUTTON_CHECK, &CExitEditorDlg::OnBnClickedExitButtonCheck)
	ON_BN_CLICKED(IDC_EXIT_BUTTON_UNCHECK, &CExitEditorDlg::OnBnClickedExitButtonUncheck)
END_MESSAGE_MAP()


// CExitEditorDlg message handlers


void CExitEditorDlg::OnBnClickedOpenWebsite()
{
	ShellExecute(NULL, "open", "https://vanda3d.org", NULL, NULL, SW_SHOWNORMAL);
	CDialog::OnOK();
}


void CExitEditorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


HBRUSH CExitEditorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
		pDC->SetTextColor(RGB(222, 122, 5));
		pDC->SetBkColor(RGB(40, 40, 40));
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;

	default:
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		break;
	}
	return hbr;
}


BOOL CExitEditorDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(40, 40, 40));    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                       // CDialog::OnEraseBkgnd(pDC);

	return CDialog::OnEraseBkgnd(pDC);
}


void CExitEditorDlg::OnBnClickedExitButtonCheck()
{
	m_btnCheck.ShowWindow(SW_HIDE);
	m_btnCheck.UpdateWindow();

	m_btnUncheck.ShowWindow(SW_SHOW);
	m_btnUncheck.UpdateWindow();

	g_options.m_showExitDialog = CTrue;
}


void CExitEditorDlg::OnBnClickedExitButtonUncheck()
{
	m_btnUncheck.ShowWindow(SW_HIDE);
	m_btnUncheck.UpdateWindow();
	g_options.m_showExitDialog = CFalse;

	m_btnCheck.ShowWindow(SW_SHOW);
	m_btnCheck.UpdateWindow();
}


BOOL CExitEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnUncheck.LoadBitmaps(IDB_BITMAP_WELCOME_UNCHECK);
	m_btnUncheck.ShowWindow(SW_SHOW);
	m_btnUncheck.UpdateWindow();

	m_btnCheck.LoadBitmaps(IDB_BITMAP_WELCOME_CHECK);
	m_btnCheck.ShowWindow(SW_HIDE);
	m_btnCheck.UpdateWindow();

	m_btnCheck.ShowWindow(SW_HIDE);
	m_btnCheck.UpdateWindow();

	m_btnUncheck.ShowWindow(SW_SHOW);
	m_btnUncheck.UpdateWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

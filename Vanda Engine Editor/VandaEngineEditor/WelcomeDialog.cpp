//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// WelcomeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngineEditor.h"
#include "WelcomeDialog.h"


// CWelcomeDialog dialog

IMPLEMENT_DYNAMIC(CWelcomeDialog, CDialog)

CWelcomeDialog::CWelcomeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomeDialog::IDD, pParent)
{

}

CWelcomeDialog::~CWelcomeDialog()
{
}

void CWelcomeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_CHECK, m_btnCheck);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_UNCHECK, m_btnUncheck);
	DDX_Control(pDX, IDDONATE, m_btnDonateNow);
	DDX_Control(pDX, IDOFFICIALWEBSITE, m_btnWebsite);
	DDX_Control(pDX, IDEMAILME, m_btnEmailMe);
	DDX_Control(pDX, IDGITHUB, m_btnGitHub);
	DDX_Control(pDX, IDSOURCEFORGE, m_btnSourceforge);
	DDX_Control(pDX, IDFACEBOOK, m_btnFacebook);
}


BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_CHECK, &CWelcomeDialog::OnBnClickedWelcomeButtonCheck)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_UNCHECK, &CWelcomeDialog::OnBnClickedWelcomeButtonUncheck)
	ON_BN_CLICKED(IDDONATE, &CWelcomeDialog::OnBnClickedDonate)
	ON_BN_CLICKED(IDEMAILME, &CWelcomeDialog::OnBnClickedEmailme)
	ON_BN_CLICKED(IDOFFICIALWEBSITE, &CWelcomeDialog::OnBnClickedOfficialwebsite)
	ON_BN_CLICKED(IDGITHUB, &CWelcomeDialog::OnBnClickedGithub)
	ON_BN_CLICKED(IDSOURCEFORGE, &CWelcomeDialog::OnBnClickedSourceforge)
	ON_BN_CLICKED(IDFACEBOOK, &CWelcomeDialog::OnBnClickedFacebook)
END_MESSAGE_MAP()


// CWelcomeDialog message handlers

BOOL CWelcomeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnUncheck.LoadBitmaps( IDB_BITMAP_WELCOME_UNCHECK );
	m_btnUncheck.ShowWindow( SW_SHOW );
	m_btnUncheck.UpdateWindow();

	m_btnCheck.LoadBitmaps( IDB_BITMAP_WELCOME_CHECK );
	m_btnCheck.ShowWindow( SW_HIDE );
	m_btnCheck.UpdateWindow();

	m_btnOK.ShowWindow( SW_SHOW);
	m_btnOK.UpdateWindow();

	if (g_options.m_showStartupDialog)
	{
		m_btnCheck.ShowWindow(SW_HIDE);
		m_btnCheck.UpdateWindow();

		m_btnUncheck.ShowWindow(SW_SHOW);
		m_btnUncheck.UpdateWindow();
	}
	else
	{
		m_btnCheck.ShowWindow(SW_SHOW);
		m_btnCheck.UpdateWindow();

		m_btnUncheck.ShowWindow(SW_HIDE);
		m_btnUncheck.UpdateWindow();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWelcomeDialog::OnEraseBkgnd(CDC* pDC)
{
    CRect rect;
    GetClientRect(&rect);
    CBrush myBrush( RGB(40,40,40) );    // dialog background color
    CBrush *pOld = pDC->SelectObject(&myBrush);
    BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

    pDC->SelectObject(pOld);    // restore old brush

    return bRes;                       // CDialog::OnEraseBkgnd(pDC);

	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CWelcomeDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr  = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	  case IDC_STATIC:
		  pDC->SetTextColor(RGB(222, 122, 5));
		   pDC->SetBkColor (RGB(40,40,40)); 
		   hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		   break;

	  default:
		   hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
		   break;
	}
	return hbr;
}

void CWelcomeDialog::OnBnClickedWelcomeButtonCheck()
{
	m_btnCheck.ShowWindow( SW_HIDE );
	m_btnCheck.UpdateWindow();

	m_btnUncheck.ShowWindow( SW_SHOW );
	m_btnUncheck.UpdateWindow();

	g_options.m_showStartupDialog = CTrue;
}

void CWelcomeDialog::OnBnClickedWelcomeButtonUncheck()
{
	m_btnUncheck.ShowWindow( SW_HIDE );
	m_btnUncheck.UpdateWindow();
	g_options.m_showStartupDialog = CFalse;

	m_btnCheck.ShowWindow( SW_SHOW );
	m_btnCheck.UpdateWindow();
}

void CWelcomeDialog::OnBnClickedDonate()
{
	//ShellExecute(NULL, "open", "https://vanda3d.org/donate/", NULL, NULL, SW_SHOWNORMAL);
	ShellExecute(NULL, "open", "https://vanda3d.org/tutorials/", NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedEmailme()
{
	LPCTSTR addr = "mailto:opentechno@hotmail.com";
	ShellExecute(0, "open", addr, NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedOfficialwebsite()
{
	ShellExecute(NULL, "open", "https://vanda3d.org/", NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedGithub()
{
	ShellExecute(NULL, "open", "https://github.com/ehsankamrani/vandaengine", NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedSourceforge()
{
	ShellExecute(NULL, "open", "https://sourceforge.net/projects/vandaengine/", NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedFacebook()
{
	ShellExecute(NULL, "open", "http://facebook.com/vandaengine", NULL, NULL, SW_SHOWNORMAL);
}

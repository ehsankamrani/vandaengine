//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// WelcomeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
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
	DDX_Control(pDX, IDC_WELCOME_BUTTON_HELP, m_btnVisitHelp);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_CHECK, m_btnCheck);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_UNCHECK, m_btnUncheck);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_VIDEO, m_btnVideo);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_TUTORIALS, m_btnTutorials);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_VANDA_OVERVIEW, m_btnOverviewToVandaEngine1);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_RUN_DEMO_EDITOR, m_btnRunDemoInEditor);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_RUN_DEMO_PUBLISHED, m_btnRunPublishedDemo);
	DDX_Control(pDX, IDC_WELCOME_BUTTON_DONATE, m_btnDonate);
	DDX_Control(pDX, IDC_STATIC_INTRODUCTION, m_linkIntroduction);
	DDX_Control(pDX, IDC_STATIC_VE_STRUCTURE, m_linkVEStructure);
	DDX_Control(pDX, IDC_STATIC_TUTORIALS, m_linkTutorials);
	DDX_Control(pDX, IDC_STATIC_HELP, m_linkHelp);
	//DDX_Control(pDX, IDC_STATIC_RUN_DEMO_IN_EDITOR, m_linkRunDemoInEditor);
	//DDX_Control(pDX, IDC_STATIC_RUN_PUBLISHED_DEMO, m_linkPublishedDemo);
	DDX_Control(pDX, IDC_STATIC_DONATE, m_linkDonate);
	DDX_Control(pDX, IDDONATE, m_btnDonateNow);
	DDX_Control(pDX, IDOFFICIALWEBSITE, m_btnOpenWebsite);
	DDX_Control(pDX, IDEMAILME, m_btnEmailMe);
}


BEGIN_MESSAGE_MAP(CWelcomeDialog, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_HELP, &CWelcomeDialog::OnBnClickedWelcomeButtonHelp)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_CHECK, &CWelcomeDialog::OnBnClickedWelcomeButtonCheck)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_UNCHECK, &CWelcomeDialog::OnBnClickedWelcomeButtonUncheck)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_VIDEO, &CWelcomeDialog::OnBnClickedWelcomeButtonVideo)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_TUTORIALS, &CWelcomeDialog::OnBnClickedWelcomeButtonTutorials)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_VANDA_OVERVIEW, &CWelcomeDialog::OnBnClickedWelcomeButtonVandaOverview)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_RUN_DEMO_EDITOR, &CWelcomeDialog::OnBnClickedWelcomeButtonRunDemoEditor)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_RUN_DEMO_PUBLISHED, &CWelcomeDialog::OnBnClickedWelcomeButtonRunDemoPublished)
	ON_BN_CLICKED(IDC_WELCOME_BUTTON_DONATE, &CWelcomeDialog::OnBnClickedWelcomeButtonDonate)
	ON_STN_CLICKED(IDC_STATIC_RUN_DEMO_IN_EDITOR, &CWelcomeDialog::OnStnClickedStaticRunDemoInEditor)
	ON_STN_CLICKED(IDC_STATIC_RUN_PUBLISHED_DEMO, &CWelcomeDialog::OnStnClickedStaticRunPublishedDemo)
	ON_BN_CLICKED(IDDONATE, &CWelcomeDialog::OnBnClickedDonate)
	ON_BN_CLICKED(IDEMAILME, &CWelcomeDialog::OnBnClickedEmailme)
	ON_BN_CLICKED(IDOFFICIALWEBSITE, &CWelcomeDialog::OnBnClickedOfficialwebsite)
END_MESSAGE_MAP()


// CWelcomeDialog message handlers

BOOL CWelcomeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_btnVisitHelp.LoadBitmaps( IDB_BITMAP_WELCOME_VISIT_HELP_UP, IDB_BITMAP_WELCOME_VISIT_HELP_DOWN, IDB_BITMAP_WELCOME_VISIT_HELP_FOCUS );
	m_btnVisitHelp.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnVisitHelp.UpdateWindow();

	//m_btnVideo.LoadBitmaps( IDB_BITMAP_WELCOME_VIDEO_UP, IDB_BITMAP_WELCOME_VIDEO_DOWN, IDB_BITMAP_WELCOME_VIDEO_FOCUS );
	m_btnVideo.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnVideo.UpdateWindow();

	//m_btnOverviewToVandaEngine1.LoadBitmaps( IDB_BITMAP_OVERVIEW_UP, IDB_BITMAP_OVERVIEW_DOWN, IDB_BITMAP_OVERVIEW_FOCUS );
	m_btnOverviewToVandaEngine1.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnOverviewToVandaEngine1.UpdateWindow();

	//m_btnTutorials.LoadBitmaps( IDB_BITMAP_WELCOME_TUTORIAL_UP, IDB_BITMAP_WELCOME_TUTORIAL_DOWN, IDB_BITMAP_WELCOME_TUTORIAL_FOCUS );
	m_btnTutorials.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnTutorials.UpdateWindow();

	m_btnRunDemoInEditor.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnRunDemoInEditor.UpdateWindow();

	m_btnRunPublishedDemo.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnRunPublishedDemo.UpdateWindow();

	//m_btnDonate.LoadBitmaps( IDB_BITMAP_WELCOME_DONATE_UP, IDB_BITMAP_WELCOME_DONATE_DOWN, IDB_BITMAP_WELCOME_DONATE_FOCUS );
	m_btnDonate.LoadBitmaps( IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP, IDB_BITMAP_LINK_UP );
	m_btnDonate.UpdateWindow();


	m_btnUncheck.LoadBitmaps( IDB_BITMAP_WELCOME_UNCHECK );
	m_btnUncheck.ShowWindow( SW_SHOW );
	m_btnUncheck.UpdateWindow();

	m_btnCheck.LoadBitmaps( IDB_BITMAP_WELCOME_CHECK );
	m_btnCheck.ShowWindow( SW_HIDE );
	m_btnCheck.UpdateWindow();

	m_btnOK.ShowWindow( SW_SHOW);
	m_btnOK.UpdateWindow();

	m_linkIntroduction.SetColours(RGB(222, 122, 5), RGB(5, 122, 222));
	m_linkIntroduction.SetURL("Assets\\Engine\\Intro\\Introduction-to-VE.mp4");
	m_linkIntroduction.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	m_linkVEStructure.SetColours(RGB(222, 122, 5), RGB(5, 122, 222));
	m_linkVEStructure.SetURL("https://vanda3d.org/an-overview-to-vanda-engine/");
	m_linkVEStructure.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	m_linkTutorials.SetColours(RGB(222, 122, 5), RGB(5, 122, 222));
	m_linkTutorials.SetURL("https://vanda3d.org/tutorials/");
	m_linkTutorials.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	m_linkHelp.SetColours(RGB(222, 122, 5), RGB(5, 122, 222));
	m_linkHelp.SetURL("https://vanda3d.org/vandaengine/Doc/Reference/");
	m_linkHelp.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	//m_linkRunDemoInEditor.SetColours( RGB(222, 122, 5), RGB(222, 122, 5) );
	//m_linkRunDemoInEditor.SetURL( "" );
	//m_linkRunDemoInEditor.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	//m_linkPublishedDemo.SetColours( RGB(222, 122, 5), RGB(222, 122, 5) );
	//m_linkPublishedDemo.SetURL( "" );
	//m_linkPublishedDemo.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

	m_linkDonate.SetColours(RGB(222, 122, 5), RGB(222, 122, 5));
	m_linkDonate.SetURL( "https://vanda3d.org/donate/" );
	m_linkDonate.SetLinkCursor( LoadCursor( NULL, IDC_HAND ) );

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
	  case IDC_STATIC_RUN_DEMO_IN_EDITOR:
	  case IDC_STATIC_RUN_PUBLISHED_DEMO:
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

void CWelcomeDialog::OnBnClickedWelcomeButtonHelp()
{
		ShellExecute(NULL, "open", "Assets\\Doc\\vanda.chm", NULL, NULL, SW_SHOWNORMAL);
		//ShellExecute(NULL, "open", "https://vanda3d.org/vandaengine/Doc/Reference/", NULL, NULL, SW_SHOWNORMAL);
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


void CWelcomeDialog::OnBnClickedWelcomeButtonVideo()
{
	ShellExecute(NULL, "open", "Assets\\Engine\\Intro\\Introduction-to-VE.mp4", NULL, NULL, SW_SHOWNORMAL);
}

void CWelcomeDialog::OnBnClickedWelcomeButtonTutorials()
{
	ShellExecute(NULL, "open", "https://vanda3d.org/tutorials/", NULL, NULL, SW_SHOWNORMAL);
}

void CWelcomeDialog::OnBnClickedWelcomeButtonVandaOverview()
{
	ShellExecute(NULL, "open", "https://vanda3d.org/an-overview-to-vanda-engine/", NULL, NULL, SW_SHOWNORMAL);
}


void CWelcomeDialog::OnBnClickedWelcomeButtonRunDemoEditor()
{
	EndDialog(0);
	CChar DocumentPath[MAX_NAME_SIZE];
	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, DocumentPath);
	sprintf( g_fileNameInCommandLine, "%s%s", DocumentPath, "/Vanda/Projects/Default/Vanda1_3_3_Demo/Vanda1_3_3_Demo.vin");
	ex_pVandaEngine1Dlg->OnMenuClickedOpenVScene(CFalse);
}


void CWelcomeDialog::OnBnClickedWelcomeButtonRunDemoPublished()
{
	ShellExecute(NULL, "open", "Vanda_1_3_3_Demo.exe", NULL, "Assets\\Demo\\Vanda_1_3_3_Demo\\", SW_SHOWNORMAL);
}

void CWelcomeDialog::OnBnClickedWelcomeButtonDonate()
{
	ShellExecute(NULL, "open", "https://vanda3d.org/donate/", NULL, NULL, SW_SHOWNORMAL);
}



void CWelcomeDialog::OnStnClickedStaticRunDemoInEditor()
{
	OnBnClickedWelcomeButtonRunDemoEditor();
}


void CWelcomeDialog::OnStnClickedStaticRunPublishedDemo()
{
	OnBnClickedWelcomeButtonRunDemoPublished();
}


void CWelcomeDialog::OnBnClickedDonate()
{
	ShellExecute(NULL, "open", "https://vanda3d.org/donate/", NULL, NULL, SW_SHOWNORMAL);
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

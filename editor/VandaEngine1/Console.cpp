//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// Console.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "Console.h"
#include  "AFXPRIV.H"

// CConsole dialog

IMPLEMENT_DYNAMIC(CConsole, CDialog)

CConsole::CConsole(CWnd* pParent /*=NULL*/)
	: CDialog(CConsole::IDD, pParent)
{
}

CConsole::~CConsole()
{
}

void CConsole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT_CONSOLE, m_richEditConsole);
}

BEGIN_MESSAGE_MAP(CConsole, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(ID_REMOVE_TEXT, &CConsole::OnBnClickedRemoveText)
END_MESSAGE_MAP()

BOOL CConsole::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_richEditConsole.LimitText( 2000000 );
	m_richEditConsole.SetBackgroundColor( FALSE, RGB(50,50,60));

	/////==============Read===============
	CString sReadText; //Where the rich text will be streamed into
	EDITSTREAM esRead;
	esRead.dwCookie = (DWORD)&sReadText; // Pass a pointer to the CString to the callback function 
	esRead.pfnCallback = MEditStreamOutCallback; // Specify the pointer to the callback function.
	ex_pRichEdit->StreamOut(SF_RTF,esRead); // Perform the streaming
	//====================================

	m_richEditConsole.SetReadOnly(FALSE);
	m_richEditConsole.SetSel( 0, -1 );
	m_richEditConsole.ReplaceSel( sReadText.GetString() );
	m_richEditConsole.SetReadOnly(TRUE);
	return TRUE;
}

INT_PTR CConsole::DoModal()
{
	CDialogTemplate dlt;
	int nResult;
	// load dialog template
	if (!dlt.Load(MAKEINTRESOURCE(CConsole::IDD))) return -1;
	// set the font, for example "Arial", 10 pts.
	dlt.SetFont("Consolas", 9);
	// get pointer to the modified dialog template
	LPSTR pdata = (LPSTR)GlobalLock(dlt.m_hTemplate);
	// let MFC know that you are using your own template
	m_lpszTemplateName = NULL;
	InitModalIndirect(pdata);
	// display dialog box
	nResult = CDialog::DoModal();
	// unlock memory object
	GlobalUnlock(dlt.m_hTemplate);
	return nResult;
}


void CConsole::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CConsole::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}

void CConsole::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}


void CConsole::OnBnClickedRemoveText()
{
	if( MessageBox( "Remove the contents of information window?", "Warning", MB_YESNO ) == IDYES )
	{
		PrintInfo( "", COLOR_RED, CTrue ); //reset counter
		m_richEditConsole.SetWindowTextA("");
		ex_pRichEdit->SetWindowTextA("");
	}
}

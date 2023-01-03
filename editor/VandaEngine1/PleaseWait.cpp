//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// PealseWait.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "PleaseWait.h"
#include "afxdialogex.h"


// CPleaseWait dialog

IMPLEMENT_DYNAMIC(CPleaseWait, CDialog)

CPleaseWait::CPleaseWait(CWnd* pParent /*=NULL*/)
	: CDialog(CPleaseWait::IDD, pParent)
{

}

CPleaseWait::~CPleaseWait()
{
}

void CPleaseWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPleaseWait, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CPleaseWait message handlers


BOOL CPleaseWait::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(RGB(70, 70, 70));    // dialog background color
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                       // CDialog::OnEraseBkgnd(pDC);

	return CDialog::OnEraseBkgnd(pDC);
}


HBRUSH CPleaseWait::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
		pDC->SetTextColor(RGB(222, 122, 5));
		pDC->SetBkColor(RGB(70, 70, 70));
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;

	default:
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
		break;
	}
	return hbr;
}

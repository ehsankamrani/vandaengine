//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// NormalMapButton.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "CustomButton.h"


// CCustomButton

IMPLEMENT_DYNAMIC(CCustomButton, CButton)

CCustomButton::CCustomButton()
{

}

CCustomButton::~CCustomButton()
{
}


BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CCustomButton message handlers



void CCustomButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC); //Get device context object
	CRect rt;
	rt = lpDrawItemStruct->rcItem; //Get button rect
	UINT state = lpDrawItemStruct->itemState; //Get state of the button

	if ( (state & ODS_DISABLED) ) // If it is pressed
	{
		dc.FillSolidRect(rt, RGB(80, 80, 80)); 
		dc.SetTextColor(RGB(120,120,120)); 
	}
	else
	{
		dc.FillSolidRect(rt, RGB(80, 80, 80));
		dc.SetTextColor(RGB(180,150,0)); 
	}
	CString strTemp;
	GetWindowText(strTemp);
	dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 


	if ( (state & ODS_SELECTED) ) // If it is pressed
	{
		dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);
	}
	else
	{
		dc.DrawEdge(rt,EDGE_BUMP,BF_RECT); 
	}

	if ( (state & ODS_FOCUS ) ) // If the button is focused
	{
		// Draw a focus rect which indicates the user
		// that the button is focused
		int iChange = 3;
		rt.top += iChange;
		rt.left += iChange;
		rt.right -= iChange;
		rt.bottom -= iChange;
		dc.DrawFocusRect(rt);
	}
	dc.Detach();
}

BOOL CCustomButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default
	//::SetCursor( LoadCursor( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDC_POINTER ) ) );
	::SetCursor( AfxGetApp()->LoadStandardCursor(IDC_HAND) );
	return TRUE;

	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

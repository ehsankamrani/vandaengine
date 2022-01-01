//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// CustomRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "CustomRichEditCtrl.h"
#include <afxole.h>

// CCustomRichEditCtrl

IMPLEMENT_DYNAMIC(CCustomRichEditCtrl, CRichEditCtrl)

CCustomRichEditCtrl::CCustomRichEditCtrl()
{

}

CCustomRichEditCtrl::~CCustomRichEditCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomRichEditCtrl, CRichEditCtrl)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CCustomRichEditCtrl message handlers




void CCustomRichEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x56){  //"V" key
		if (GetKeyState(VK_CONTROL) & 0x8000){  //see if it's CTRL-V
			//Intercept CTRL-V so we can paste only CF_TEXT
			PasteSpecial(CF_TEXT);
			return;
		}
	}
	CRichEditCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

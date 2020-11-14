//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once


// CCustomBitmapButton

class CCustomBitmapButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CCustomBitmapButton)

public:
	CCustomBitmapButton();
	BOOL AutoLoad(UINT nID, CWnd* pParent); 
	void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual ~CCustomBitmapButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};



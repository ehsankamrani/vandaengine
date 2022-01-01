//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once


// CCustomRichEditCtrl

class CCustomRichEditCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CCustomRichEditCtrl)

public:
	CCustomRichEditCtrl();
	virtual ~CCustomRichEditCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};



//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CSelectAnimationClips dialog

class CSelectAnimationClips : public CDialog
{
	DECLARE_DYNAMIC(CSelectAnimationClips)

public:
	CSelectAnimationClips(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectAnimationClips();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECT_ANIMATION_CLIPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	std::vector<std::string>m_list;
	CUInt m_index;
	CChar m_selectedAnimation[MAX_NAME_SIZE];
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listAnimationClips;
	virtual BOOL OnInitDialog();
	CVoid InserItemToList(CChar* name);
	CVoid SetAnimationList(std::vector<std::string>list);
	CChar* GetSelectedAnimation();
	afx_msg void OnBnClickedOk();
};

//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CWaterAttachment dialog

class CWaterAttachment : public CDialog
{
	DECLARE_DYNAMIC(CWaterAttachment)

public:
	CWaterAttachment(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWaterAttachment();

// Dialog Data
	enum { IDD = IDD_DIALOG_WATER_ATTACHMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int waterObjectIndex;

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listBoxWaterObjects;
	CImageList m_waterListImage;
public:
	virtual BOOL OnInitDialog();
	CVoid InserItemToWaterList( char * objectName );
public:
	afx_msg void OnBnClickedAttach();
public:
	afx_msg void OnBnClickedDetach();
public:
	virtual INT_PTR DoModal();
};

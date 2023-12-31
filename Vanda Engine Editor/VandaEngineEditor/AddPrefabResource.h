//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAddPrefabResource dialog

class CAddPrefabResource : public CDialog
{
	DECLARE_DYNAMIC(CAddPrefabResource)

public:
	CAddPrefabResource(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPrefabResource();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_PREFAB_RESOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	std::vector<CPrefab*>m_prefabs;
	afx_msg void OnBnClickedButtonAddPrefab();
	afx_msg void OnBnClickedButtonRemovePrefab();
	afx_msg void OnBnClickedButtonCopyPrefabName();
	CListCtrl m_listPrefabNames;
	CRichEditCtrl m_richSelectedPrefab;
	CStatic m_imageCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListPrefabNames(NMHDR *pNMHDR, LRESULT *pResult);
	CVoid InsertItemToPrefabList(CChar* prefabName);
	void PushPrefab(CPrefab* prefab);
	CVoid UpdatePreview(CPrefab *prefab);
private:
	CInt m_prefabIndex;
	HBITMAP m_hBitmap;
public:
	afx_msg void OnBnClickedOk();
};

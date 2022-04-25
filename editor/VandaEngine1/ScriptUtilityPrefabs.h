//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CScriptUtilityPrefabs dialog

class CScriptUtilityPrefabs : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityPrefabs)

public:
	CScriptUtilityPrefabs(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityPrefabs();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_PREFABS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	std::vector<CPrefab*>m_prefabs;
	afx_msg void OnBnClickedButtonCopyPrefabName();
	afx_msg void OnLvnItemchangedListPrefabNames(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listPrefabNames;
	CRichEditCtrl m_richSelectedPrefab;
	CStatic m_imageCtrl;
	virtual BOOL OnInitDialog();
	CVoid InsertItemToPrefabList(CChar* prefabName);
	void PushPrefab(CPrefab* prefab);
	CVoid UpdatePreview(CPrefab *prefab);
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName);

private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_VSceneName[MAX_NAME_SIZE];

	CInt m_prefabIndex;
	HBITMAP m_hBitmap;
public:
	CStatic m_textProjectVSceneName;
};

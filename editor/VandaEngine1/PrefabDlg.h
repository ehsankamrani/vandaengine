//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "PrefabNameDlg.h"

// CPrefabDlg dialog

class CPrefabDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrefabDlg)

public:
	CPrefabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrefabDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PREFAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CBool m_prefabResourceMode;
	CPrefab* m_selectedPrefab;

public:
	std::string m_selectedPackageName;
	std::string m_selectedPrefabName;

	// //shows prefabs made in game engine
	void OnBnClickedOpen();
	void OnBnClickedDelete();
	void OnBnClickedNewPrefab();
	void OnBnClickedRenamePrefab();
	void OnBnClickedNewPackage();
	void OnBnClickedRenamePackage();
	void OnBnClickedDeletePackage();

	CListCtrl m_listPrefabPackages;
	CListCtrl m_listPrefabs;
	CImageList m_prefabListImage;
	CImageList m_packageListImage;
	CListCtrl m_listPrefabProperties;
	CSliderCtrl m_slideLod;
	CButton m_btnInsertPrefab;
	CPrefabNameDlg* m_prefabNameDlg;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedInsert();
	CVoid SetSelectForMainCharacter(CBool select);
	CVoid InsertItemToPackageList(CChar* packageName);
	CVoid InsertItemToPrefabList(CChar* prefabList, CInt imageIndex = -1);
	CInt m_packageIndex;
	CInt m_prefabIndex;
	CBool m_selectForMainCharacter;
	afx_msg void OnLvnItemchangedListPrefabsProjects(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CVoid InserItemToPropertiesList(char * properties);
	CButton m_btnDeletePrefabPackage;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CVoid SetPrefabResourceMode(CBool state) { m_prefabResourceMode = state; }
	CBool GetPrefabResourceMode() { return m_prefabResourceMode; }
	CPrefab* GetSelectedPrefab() { return m_selectedPrefab; }
};

//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CScriptUtilityPrefabInstances dialog

class CScriptUtilityPrefabInstances : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityPrefabInstances)

private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_VSceneName[MAX_NAME_SIZE];
public:
	CScriptUtilityPrefabInstances(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityPrefabInstances();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_PREFAB_INSTANCES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName);
	afx_msg void OnBnClickedButtonCopyPrefabInstanceName();
	CStatic m_textProjectVSceneName;
	virtual BOOL OnInitDialog();
	CRichEditCtrl m_richSelectedPrefabInstance;
	afx_msg void OnLvnItemchangedListPrefabInstances(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listPrefabInstanceNames;
	CRichEditCtrl m_richSelectedAnimationName;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceAnimationName();
	CListCtrl m_listPrefabInstanceAnimationNames;
	afx_msg void OnLvnItemchangedListPrefabInstanceAnimations(NMHDR *pNMHDR, LRESULT *pResult);
	CRichEditCtrl m_richSelectedCameraName;
	CListCtrl m_listPrefabInstanceCameraNames;
	afx_msg void OnLvnItemchangedListPrefabInstanceCameras(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCopyPrefabInstanceCameraName();
	CVoid UpdatePreview();
	CStatic m_imageCtrl;
	HBITMAP m_hBitmap;
	CChar m_currentPackageName[MAX_NAME_SIZE];
	CChar m_currentPrefabName[MAX_NAME_SIZE];
};

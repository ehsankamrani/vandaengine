//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CScriptUtility dialog

class CScriptUtility : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtility)

public:
	CScriptUtility(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtility();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPrefabInstances();
	afx_msg void OnBnClickedGameobjects();
	afx_msg void OnBnClickedImportedCameras();
	afx_msg void OnBnClickedResources();
	afx_msg void OnBnClickedCopyVsceneName();
	virtual BOOL OnInitDialog();
	CComboBox m_comboProject;
	CComboBox m_comboVScene;
	afx_msg void OnCbnSelchangeCombProjectName();
	afx_msg void OnCbnSelchangeCombVsceneName();
	CRichEditCtrl m_richVSceneName;
	afx_msg void OnBnClickedAllGuiItems();
	afx_msg void OnBnClickedGuis();
	CButton m_btnCopyVSceneName;
	CButton m_btnVScenePrefabInstances;
	CButton m_btnVSceneGameObjects;
	CButton m_btnVSceneImportedCameras;
	CButton m_btnVSceneGUIs;
	CStatic m_imageCtrl;
	HBITMAP m_hBitmap;
	CVoid UpdatePreview();
	afx_msg void OnBnClickedOk();
};

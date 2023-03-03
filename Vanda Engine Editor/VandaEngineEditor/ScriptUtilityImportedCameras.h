//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CScriptUtilityImportedCameras dialog

class CScriptUtilityImportedCameras : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityImportedCameras)

private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_VSceneName[MAX_NAME_SIZE];
	CImageList m_imageList;
public:
	CScriptUtilityImportedCameras(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityImportedCameras();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_IMPORTED_CAMERAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyImportedCameraName();
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListImportedCameras(NMHDR *pNMHDR, LRESULT *pResult);
	CRichEditCtrl m_richImportedCameraName;
	CListCtrl m_listImportedCameras;
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName);
	CStatic m_textProjectVSceneName;
};

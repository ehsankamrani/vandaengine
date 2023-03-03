//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CScriptUtilityGameObjects dialog

class CScriptUtilityGameObjects : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityGameObjects)

private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_VSceneName[MAX_NAME_SIZE];
	CImageList m_engineObjectListImage;
public:
	CScriptUtilityGameObjects(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityGameObjects();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_GAME_OBJECTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richGameObjectName;
	afx_msg void OnBnClickedButtonCopyGameObjectName();
	CListCtrl m_listGameObjectNames;
	virtual BOOL OnInitDialog();
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName);
	CStatic m_textProjectVSceneName;
	afx_msg void OnLvnItemchangedListGameObjects(NMHDR *pNMHDR, LRESULT *pResult);
};

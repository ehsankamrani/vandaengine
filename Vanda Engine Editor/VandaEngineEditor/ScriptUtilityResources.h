//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CScriptUtilityResources dialog

class CScriptUtilityResources : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityResources)
private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_projectFilePath[MAX_URI_SIZE];
	std::vector<std::vector<std::string>> m_projectResourceNames;

public:
	CScriptUtilityResources(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityResources();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_RESOURCES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyResourceFolder();
	afx_msg void OnBnClickedButtonCopyResourceFile();
	afx_msg void OnBnClickedButtonCopyResourceFolderFile();
	CListCtrl m_listResourceFiles;
	CComboBox m_comboResourceFolder;
	CStatic m_textProjectVSceneName;
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName);
	virtual BOOL OnInitDialog();
	CVoid InserItemToList(char * name);
	CRichEditCtrl m_richFolderName;
	CRichEditCtrl m_richFileName;
	CRichEditCtrl m_richFolderFileName;
	CInt m_listIndex;
	afx_msg void OnCbnSelchangeCombResourceFolder();
	afx_msg void OnLvnItemchangedListResourceFiles(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_btnFolderName;
	CButton m_btnFileName;
	CButton m_btnFolderFileName;
};

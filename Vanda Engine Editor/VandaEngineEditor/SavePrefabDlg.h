//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "PrefabNameDlg.h"

// CSavePrefabDlg dialog

class CSavePrefabDlg : public CDialog
{
	DECLARE_DYNAMIC(CSavePrefabDlg)

public:
	CSavePrefabDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSavePrefabDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_PREFAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangePrefabName();
	CEdit m_editBoxPrefabName;
	CString m_strPrefabName;

	virtual void OnOK();
	CComboBox m_prefabPackageList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddPackage();
	void CSavePrefabDlg::GenerateRandomPassword();
	CPrefabNameDlg* m_prefabNameDlg;
	std::string m_strNewPrefabPackageName;
	std::string m_strNewPrefabName; //package_prefab.vpf
	std::string m_strNewPackageAndPrefabName; //package_prefab.vpf

	std::string m_strPassword;
};

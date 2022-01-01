//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "GUINameDlg.h"

// CGUIDlg dialog

class CGUIDlg : public CDialog
{
	DECLARE_DYNAMIC(CGUIDlg)

public:
	CGUIDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGUIDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUI_EDITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CBool m_openForScriptUtility;
	CListCtrl m_listGUIPackages;
	CListCtrl m_listGUIs;
	afx_msg void OnBnClickedInsert();
	virtual BOOL OnInitDialog();
	CVoid InsertItemToPackageList(CChar* packageName);
	CVoid InsertItemToGUIList(CChar* guiName, CUInt imgIndex = -1);
	CButton m_btnInsertGUI;
	CImageList m_guiListImage;
	CImageList m_packageListImage;

	CInt m_packageIndex;
	CInt m_guiIndex;

	std::string m_selectedPackageName;
	std::string m_selectedGUIName;

	afx_msg void OnLvnItemchangedListPackages(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	CGUINameDlg* m_guiNameDlg;
	void OnBnClickedNewPackage();

	void OnBnClickedNewGUI();
	afx_msg void OnBnClickedOk();
	CVoid OnBnClickedDeletePackage();
	CVoid OnBnClickedRenamePackage();
	CVoid OnBnClickedDeleteGUI();
	CVoid OnBnClickedRenameGUI();
	CVoid OpenForScriptUtility(CBool set) { m_openForScriptUtility = set; }
	CButton m_btnCancel;
	CRichEditCtrl m_richGUIName;
	afx_msg void OnLvnItemchangedListGuis(NMHDR *pNMHDR, LRESULT *pResult);
};

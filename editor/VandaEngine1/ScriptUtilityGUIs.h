#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CScriptUtilityGUIs dialog

class CScriptUtilityGUIs : public CDialog
{
	DECLARE_DYNAMIC(CScriptUtilityGUIs)

private:
	CChar m_projectName[MAX_NAME_SIZE];
	CChar m_VSceneName[MAX_NAME_SIZE];

public:
	CScriptUtilityGUIs(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptUtilityGUIs();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_UTILITY_GUIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyGuiName();
	CRichEditCtrl m_richGUIName;
	CListCtrl m_listGUI;
	afx_msg void OnLvnItemchangedListGuis(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CStatic m_textProjectVSceneName;
	CVoid SetSelectedProjectAndVSceneNames(CChar* projectName, CChar* VSceneName);
	CVoid UpdatePreview();
	CStatic m_imageCtrl;
	HBITMAP m_hBitmap;
	CChar m_currentGUIPackageName[MAX_NAME_SIZE];
	CChar m_currentGUIName[MAX_NAME_SIZE];
};

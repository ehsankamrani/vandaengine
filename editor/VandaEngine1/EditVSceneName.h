#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEditVSceneName dialog

class CEditVSceneName : public CDialog
{
	DECLARE_DYNAMIC(CEditVSceneName)

public:
	CEditVSceneName(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditVSceneName();

// Dialog Data
	enum { IDD = IDD_DIALOG_VSCENE_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editName;
	afx_msg void OnBnClickedOk();
	void SetInitialData(CBool save, CChar* selectedName = NULL);
	CChar* GetName();
	CChar m_name[MAX_NAME_SIZE];
	CChar m_selectedName[MAX_NAME_SIZE];
	CBool m_save;
	CString m_strName;
	afx_msg void OnEnChangePrefabName();
	virtual BOOL OnInitDialog();
	CVoid InsertItemToVSceneList(CChar* vsceneName);
	CListCtrl m_listVScenes;
	CInt m_VSceneIndex;
	CImageList m_VSceneImage;
	afx_msg void OnLvnItemchangedListVscenes(NMHDR *pNMHDR, LRESULT *pResult);
};

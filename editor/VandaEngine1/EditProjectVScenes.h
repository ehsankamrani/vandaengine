#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditProjectVScenes dialog

class CEditProjectVScenes : public CDialog
{
	DECLARE_DYNAMIC(CEditProjectVScenes)

public:
	CEditProjectVScenes(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditProjectVScenes();

// Dialog Data
	enum { IDD = IDD_DIALOG_PROJECT_VSCENES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedRename();
	CVoid InsertItemToVSceneList(CChar* vsceneName);
	void SetState(CBool open);
	CBool m_open;
	CListCtrl m_listVScenes;
	CImageList m_VSceneImage;
	CInt m_VSceneIndex;
	CChar m_name[MAX_NAME_SIZE];
	virtual BOOL OnInitDialog();
	CButton m_btnRename;
	CButton m_btnDelete;
	CButton m_btnOK;
	CButton m_btnCancel;
	afx_msg void OnBnClickedOk();
	CChar* GetName();
};

#pragma once
#include "afxcmn.h"


// CDeleteProject dialog

class CDeleteProject : public CDialog
{
	DECLARE_DYNAMIC(CDeleteProject)

public:
	CDeleteProject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeleteProject();

// Dialog Data
	enum { IDD = IDD_DIALOG_DELETE_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CImageList m_projectListImage;
	CListCtrl m_listAvailableProjects;
	virtual BOOL OnInitDialog();
	CVoid InserItemToAvailableProjectsList(char * projectName, CBool isActive);
	CInt availableProjectIndex;
	afx_msg void OnBnClickedOk();
};

#pragma once
#include "afxcmn.h"


// CSetCurrentProject dialog

class CSetCurrentProject : public CDialog
{
	DECLARE_DYNAMIC(CSetCurrentProject)

public:
	CSetCurrentProject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetCurrentProject();

// Dialog Data
	enum { IDD = IDD_DIALOG_SET_CURRENT_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listAvailableProjects;
	CImageList m_projectListImage;
	virtual BOOL OnInitDialog();
	CVoid InserItemToAvailableProjectsList( char * projectName, CBool isActive );
	CInt availableProjectIndex;
	virtual void OnOK();
};

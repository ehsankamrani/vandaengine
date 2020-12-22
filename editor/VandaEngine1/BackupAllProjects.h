#pragma once
#include "afxcmn.h"


// CBackupAllProjects dialog

class CBackupAllProjects : public CDialog
{
	DECLARE_DYNAMIC(CBackupAllProjects)

public:
	CBackupAllProjects(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBackupAllProjects();

// Dialog Data
	enum { IDD = IDD_DIALOG_BACKUP_ALL_PROJECTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CChar m_srcPath[MAX_URI_SIZE];
	CChar m_dstPath[MAX_URI_SIZE];

public:
	afx_msg void OnBnClickedButtonDestination();
	CRichEditCtrl m_editBoxDestination;
	CString m_strDestination;
	afx_msg void OnBnClickedOk();

	CChar* GetSrcPath();
	CChar* GetDstPath();
};

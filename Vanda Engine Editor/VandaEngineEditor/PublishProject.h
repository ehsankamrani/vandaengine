//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPublishProject dialog

class CPublishProject : public CDialog
{
	DECLARE_DYNAMIC(CPublishProject)

public:
	CPublishProject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPublishProject();

// Dialog Data
	enum { IDD = IDD_DIALOG_PUBLISH_PROJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnDestination();
	afx_msg void OnBnClickedBtnIcon();
	CRichEditCtrl m_editBoxDestination;
	CRichEditCtrl m_editBoxIcon;
	CString m_strIcon;
	CString m_strDestination;
	CString m_strName;
	CString m_strSplash;
	CBool m_saveCurrentScene;

private:
	CBool m_publishDebug;
protected:
	virtual void OnOK();
public:
	CButton m_checkBoxSave;
	virtual BOOL OnInitDialog();
	CEdit m_editBoxName;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnBnClickedBtnSplashImage();
	CRichEditCtrl m_editBoxSplash;
	CListCtrl m_listBoxAvailableScenes;
	CListCtrl m_listBoxScenesToBePublished;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRemove();
	CInt availableSceneIndex;
	CInt sceneToBePublishedIndex;
	CVoid InserItemToAvailableScenesList( char * objectName );
	CBool m_setFirstScene;
	CVoid InserItemToScenesToBePublishedList( char * objectName );
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMarkAsFirstScene();
	CButton m_checkBoxDebug;
	CBool GetPublishDebug() { return m_publishDebug; }
	afx_msg void OnDestroy();
};

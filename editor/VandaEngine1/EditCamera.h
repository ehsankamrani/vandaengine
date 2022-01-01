//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditCamera dialog

class CEditCamera : public CDialog
{
	DECLARE_DYNAMIC(CEditCamera)
public:
	CEditCamera(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditCamera();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richEditFreeCameraFOV;
	CRichEditCtrl m_richEditFreeCameraNCP;
	CRichEditCtrl m_richEditFreeCameraFCP;

	CRichEditCtrl m_richEditPlayModeCameraFOV;
	CRichEditCtrl m_richEditPlayModeCameraMinFOV;
	CRichEditCtrl m_richEditPlayModeCameraMaxFOV;
	CRichEditCtrl m_richEditPlayModeCameraNCP;
	CRichEditCtrl m_richEditPlayModeCameraFCP;

	CRichEditCtrl m_richEditColladaCameraFOV;
	CRichEditCtrl m_richEditColladaCameraNCP;
	CRichEditCtrl m_richEditColladaCameraFCP;

	CString m_strFreeCameraFOV;
	CString m_strFreeCameraNCP;
	CString m_strFreeCameraFCP;

	CString m_strPlayModeCameraFOV;
	CString m_strPlayModeCameraMinFOV;
	CString m_strPlayModeCameraMaxFOV;
	CString m_strPlayModeCameraNCP;
	CString m_strPlayModeCameraFCP;

	CString m_strDAECameraFOV;
	CString m_strDAECameraNCP;
	CString m_strDAECameraFCP;

	CButton m_btnCheckColladaFOV;
	CButton m_btnCheckColladaNCP;
	CButton m_btnCheckColladaFCP;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonResetCameraProperties();
	afx_msg void OnBnClickedOptionsDaeCameraReadFovFromFile();
	afx_msg void OnBnClickedOptionsDaeCameraReadNCPFromFile();
	afx_msg void OnBnClickedOptionsDaeCameraReadFCPFromFile();
};

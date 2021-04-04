#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditPrefab dialog

class CEditPrefab : public CDialog
{
	DECLARE_DYNAMIC(CEditPrefab)

public:
	CEditPrefab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditPrefab();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_PREFAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listPrefabInstanceAnimationNames;
	CListCtrl m_listPrefabInstanceCameraNames;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceCameraName();
	CStatic m_imageCtrl;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceAnimationName();
	CRichEditCtrl m_richSelectedAnimationName;
	CRichEditCtrl m_richSelectedCameraName;

	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editPosZ;
	CString m_strPosX;
	CString m_strPosY;
	CString m_strPosZ;
	CFloat m_fPosX;
	CFloat m_fPosY;
	CFloat m_fPosZ;

	CEdit m_editRotX;
	CEdit m_editRotY;
	CEdit m_editRotZ;
	CString m_strRotX;
	CString m_strRotY;
	CString m_strRotZ;
	CFloat m_fRotX;
	CFloat m_fRotY;
	CFloat m_fRotZ;

	CEdit m_editScaleX;
	CEdit m_editScaleY;
	CEdit m_editScaleZ;
	CString m_strScaleX;
	CString m_strScaleY;
	CString m_strScaleZ;
	CFloat m_fScaleX;
	CFloat m_fScaleY;
	CFloat m_fScaleZ;

	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CStatic m_textPrefabInstanceName;
	afx_msg void OnBnClickedButtonCopyPrefabInstanceName();
	CRichEditCtrl m_richPrefabInstanceName;
	CVoid SetPrefabInstance(CInstancePrefab* instance_prefab);

private:
	CInstancePrefab* m_instancePrefab;
	HBITMAP m_hBitmap;

public:
	afx_msg void OnLvnItemchangedListPrefabInstanceAnimations(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPrefabInstanceCameras(NMHDR *pNMHDR, LRESULT *pResult);
	CVoid UpdatePreview();
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnEnChangeEditPosZ();
	afx_msg void OnEnChangeEditRotX();
	afx_msg void OnEnChangeEditRotY();
	afx_msg void OnEnChangeEditRotZ();
	afx_msg void OnEnChangeEditScaleX();
	afx_msg void OnEnChangeEditScaleY();
	afx_msg void OnEnChangeEditScaleZ();
};

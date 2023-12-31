//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"


// CEditLOD dialog
struct CEditLodMinMax
{
	CFloat min;
	CFloat max;
	CFloat minObjectCameraDistance;
};
class CEditLOD : public CDialog
{
	DECLARE_DYNAMIC(CEditLOD)

public:
	CEditLOD(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditLOD();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_LOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CRichEditCtrl m_lod1Max;
	CRichEditCtrl m_lod2Min;
	CRichEditCtrl m_lod2Max;
	CRichEditCtrl m_lod3Min;
	CRichEditCtrl m_lod3Max;
	CRichEditCtrl m_lod4ObjectCameraDistance;

	CString m_strLod1Max;
	CString m_strLod1MinObjectCameraDistance;
	CString m_strLod2Min;
	CString m_strLod2Max;
	CString m_strLod3Min;
	CString m_strLod3Max;
	CString m_strLod4ObjectCameraDistance;
	CString m_strWaterReflectionPercents;
	CString m_strWaterReflectionDistance;
	CString m_strWaterInvisiblePercents;
	CString m_strWaterInvisibleDistance;

private:
	CEditLodMinMax m_lod[3]; //3 LODs are supported. LOD4: Invisible Object
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReset();
	CRichEditCtrl m_lod1MinObjectCameraDistance;
	CRichEditCtrl m_waterReflectionPercents;
	CRichEditCtrl m_waterReflectionDistance;
	CRichEditCtrl m_waterInvisiblePercents;
	CRichEditCtrl m_waterInvisibleDistance;
};

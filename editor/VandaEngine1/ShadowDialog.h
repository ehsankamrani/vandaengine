//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditShadow dialog

class CEditShadow : public CDialog
{
	DECLARE_DYNAMIC(CEditShadow)

public:
	CEditShadow(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditShadow();

// Dialog Data
	enum { IDD = IDD_DIALOG_SHADOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxSplitWeight;
	afx_msg void OnEnChangeEditShadowSplitweight();

private:
	CFloat m_splitWeight;
	CFloat m_nearClipPlane;
	CFloat m_farClipPlane;
	CString m_strSplitWeight;
	CString m_strNearClipPlane;
	CString m_strFarClipPlane;
	CString m_strIntensity;
	CString m_currentLightName;

	CInt m_shadowType;
	CInt m_shadowSplits;
	CInt m_shadowResolution;

protected:
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditShadowFarclipplane();
	afx_msg void OnEnChangeEditShadowNearclipplane();
	afx_msg void OnCbnSelchangeComboShadowRenderingalgorithm();
	afx_msg void OnCbnSelchangeComboShadowSplits();
	afx_msg void OnCbnSelchangeComboShadowResolution();

	CEdit m_editBoxFarClipPlane;
	CEdit m_editBoxNearClipPlane;
	CComboBox m_comboResolution;
	CComboBox m_comboAlgorithm;
	CComboBox m_comboNumSplits;

	CVoid CEditShadow::GetInformation();
	CButton m_checkBoxEnableShadow;
	CEdit m_editBoxIntensity;
	CFloat m_intensity;
	afx_msg void OnEnChangeEditShadowIntensity();
	CComboBox m_comboDirectionalLight;
	afx_msg void OnCbnSelchangeComboShadowDirectionalLight();
};

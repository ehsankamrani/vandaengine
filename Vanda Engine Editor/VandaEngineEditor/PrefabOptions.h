//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPrefabOptions dialog

class CPrefabOptions : public CDialog
{
	DECLARE_DYNAMIC(CPrefabOptions)

public:
	CPrefabOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrefabOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_PREFAB_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_checkBoxPlayAnimation;
	CButton m_checkBoxLoopAnimation;
	CComboBox m_comboAnimationClip;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	afx_msg void OnCbnSelchangeComboAnimationClip();
	CInt m_currentAnimClip;
	CButton m_checkBoxAlwaysVisible;
	CButton m_checkBoxCastShadow;
	afx_msg void OnBnClickedBtnAddPrefabScript();
	afx_msg void OnBnClickedBtnRemovePrefabScript();
	CRichEditCtrl m_editBoxScriptPath;
private:
	CBool m_updateScript;
	CString m_strScriptName;
	CBool m_hasScript;
public:
	afx_msg void OnBnClickedButtonCopyAnimation();
	CRichEditCtrl m_richAnimationName;
	afx_msg void OnBnClickedButtonViewScript();
	CButton m_checkBoxTransformable;
	CButton m_checkBoxSelectable;
};

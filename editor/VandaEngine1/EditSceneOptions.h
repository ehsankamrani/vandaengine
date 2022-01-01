//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CEditSceneOptions dialog

class CEditSceneOptions : public CDialog
{
	DECLARE_DYNAMIC(CEditSceneOptions)

public:
	CEditSceneOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditSceneOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_IMPORT_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//CEdit m_editBoxMeshPath;
	//CEdit m_editBoxDiffuseTexture;
	//CEdit m_editBoxExtraTexture;
	//CEdit m_editBoxSkyTexture;
	//CEdit m_editBoxWaterTexture;
	//CEdit m_editBoxSoundPath;
	//afx_msg void OnEnChangeEditMeshPath();
	//afx_msg void OnEnChangeEditDiffuseTextures();
	//afx_msg void OnEnChangeEditExtraTextures();
	//afx_msg void OnEnChangeEditSkyTexture();
	//afx_msg void OnEnChangeEditWaterTextures();
	//afx_msg void OnEnChangeEditSoundPath();
	//afx_msg void OnEnChangeEditPhysxPath();

	//CString m_strMeshPath, m_strDiffuseTexture, m_strExtraTexture, m_strSkyTexture, m_strWaterTexture, m_strSoundPath, m_strPhysXPath;
	CString m_strDiffuseNameExcept, m_strNormalMapName, m_strGlossMapName, m_strDirtMapName;
	virtual BOOL OnInitDialog();
	//CEdit m_editBoxPhysXPath;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedOk();
	void AddSlash(CChar* string);
	CEdit m_editBoxNormalMapName;
	CEdit m_editBoxGlossMapName;
	CEdit m_editBoxDirtMapName;
	afx_msg void OnEnChangeEditNormalmapName();
	afx_msg void OnEnChangeEditGlossmapName();
	afx_msg void OnEnChangeEditDirtmapName();
	CEdit m_editBoxDiffuseExcept;
	afx_msg void OnEnChangeEditDiffuseExcept();
};

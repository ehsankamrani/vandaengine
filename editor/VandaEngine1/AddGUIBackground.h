//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddGUIBackground dialog

class CAddGUIBackground : public CDialog
{
	DECLARE_DYNAMIC(CAddGUIBackground)

public:
	CAddGUIBackground(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddGUIBackground();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUI_BACKGROUND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddMainImg();

	CEdit m_editImg;
	CEdit m_editPercentage;

	CString m_strName;
	CString m_strTempName;

	CString m_strImagePath;
	CString m_strImageName;

	CString m_strPercentage;
	CFloat m_fPercentage;

	CString m_strPosX;
	CFloat m_fPosX;

	CString m_strPosY;
	CFloat m_fPosY;

	CVoid SetName(CChar* name);
	CVoid SetPosition(CVec2f pos);
	CVoid SetImagePath(CChar* path);
	CVoid SetUpdateImage(CBool state);
	CVoid SetSize(CFloat size);

	CChar* GetName();
	CVec2f GetPosition();
	CChar* GetImagePath();
	CFloat GetSize();

	CBool GetUpdateImage();

	afx_msg void OnEnChangeEditPercentage();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditMainImg();
	CEdit m_editName;
	CEdit m_editPosX;
	CEdit m_editPosY;
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnEnChangeEditName();
	CVoid SetCreate(CBool create);
	CBool m_create;
	CBool m_updateImage;

};

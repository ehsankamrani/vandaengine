//Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddGUIText dialog

class CAddGUIText : public CDialog
{
	DECLARE_DYNAMIC(CAddGUIText)

public:
	CAddGUIText(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddGUIText();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUI_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editText;
	CEdit m_editSize;
	CComboBox m_comboType;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditSize();
	afx_msg void OnEnChangeEditText();
	virtual BOOL OnInitDialog();
	CVoid SetCreate(CBool create);

	CBool m_create;
	CString m_strText;
	CString m_strTextSize;
	CFloat m_fTextSize;
	afx_msg void OnBnClickedButtonColor();
	CEdit m_editColor;
	COLORREF m_color;
	CBrush m_brush;
	CFloat m_fColor[4];

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_editName;
	CEdit m_editPosX;
	CEdit m_editPosY;
	afx_msg void OnEnChangeEditName();
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();

	CString m_strName;
	CString m_strTempName;

	CString m_strPosX;
	CFloat m_fPosX;

	CString m_strPosY;
	CFloat m_fPosY;

	CFontType m_fontType;

	CVoid SetName(CChar* name);
	CVoid SetPosition(CVec2f pos);
	CVoid SetSize(CFloat size);
	CVoid SetColor(CVec3f color);
	CVoid SetFontType(CFontType type);
	CVoid SetText(CChar* text);

	CChar* GetName();
	CVec2f GetPosition();
	CFloat GetSize();
	CVec3f GetColor();
	CFontType GetFontType();
	CChar* GetText();
};

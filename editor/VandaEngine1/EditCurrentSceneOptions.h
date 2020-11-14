#pragma once
#include "afxwin.h"


// CEditCurrentSceneOptions dialog

class CEditCurrentSceneOptions : public CDialog
{
	DECLARE_DYNAMIC(CEditCurrentSceneOptions)

public:
	CEditCurrentSceneOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditCurrentSceneOptions();

// Dialog Data
	enum { IDD = IDD_DIALOG_CURRENT_SCENE_OPTIONS };

private:
	CString m_strCursorImage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxBanner;
	afx_msg void OnBnClickedBtnLoadingBanner();
	CString m_strBanner;
	CString m_strCursorSize;
	CInt m_cursorSize;
	CBool setBanner;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CButton m_checkboxSetMenu;
	CEdit m_editBoxCursorIcon;
	afx_msg void OnBnClickedBtnLoadingCursorIcon();
	afx_msg void OnBnClickedCheckboxSetasmenu();
	CButton m_btnCursorIcon;
	CEdit m_editBoxCursorSize;
	afx_msg void OnEnChangeEditCursorPercent();
};

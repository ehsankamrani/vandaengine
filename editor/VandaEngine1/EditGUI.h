#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "GUIEngine/GUI.h"

// CEditGUI dialog

class CEditGUI : public CDialog
{
	DECLARE_DYNAMIC(CEditGUI)

public:
	CEditGUI(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditGUI();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_GUI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCopyGuiInstanceName();
	CRichEditCtrl m_richGUIInstanceName;

	CVoid SetGUIInstance(CGUI* instance_gui);

private:
	CGUI* m_instanceGUI;
	HBITMAP m_hBitmap;
	CVoid UpdatePreview();

public:
	virtual BOOL OnInitDialog();
	CStatic m_textGUIName;
	CStatic m_imageCtrl;
};

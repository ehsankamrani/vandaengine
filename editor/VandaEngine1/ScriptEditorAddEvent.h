#pragma once
#include "afxcmn.h"


// CScriptEditorAddEvent dialog

class CScriptEditorAddEvent : public CDialog
{
	DECLARE_DYNAMIC(CScriptEditorAddEvent)

private:
	CInt m_index;
public:
	CScriptEditorAddEvent(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptEditorAddEvent();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_EDITOR_ADD_EVENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listEvents;
	CRichEditCtrl m_richEventName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListEvents(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CVoid InsertItem(CChar* name);

	CChar m_initEventName[MAX_URI_SIZE];
	CChar m_updateEventName[MAX_URI_SIZE];
	CChar m_onTriggerEnterEventName[MAX_URI_SIZE];
	CChar m_onTriggerStayEventName[MAX_URI_SIZE];
	CChar m_onTriggerExitEventName[MAX_URI_SIZE];
	CChar m_onSelectMouseLButtonDown[MAX_URI_SIZE];
	CChar m_onSelectMouseRButtonDown[MAX_URI_SIZE];
	CChar m_onSelectMouseEnter[MAX_URI_SIZE];
	CChar m_onSelectEventName[MAX_URI_SIZE];

	afx_msg void OnBnClickedCancel();
};

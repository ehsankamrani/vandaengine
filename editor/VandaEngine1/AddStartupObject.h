#pragma once
#include "afxwin.h"


// CAddStartupObject dialog

class CAddStartupObject : public CDialog
{
	DECLARE_DYNAMIC(CAddStartupObject)

public:
	CAddStartupObject(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddStartupObject();

// Dialog Data
	enum { IDD = IDD_DIALOG_STARTUP_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editName;
	CEdit m_editScript;
	afx_msg void OnBnClickedButtonAddScript();
	afx_msg void OnBnClickedButtonRemoveScript();
private:
	CString m_strName;
	CString m_strScript;
	CBool m_updateScript;
	CChar m_strOldName[MAX_NAME_SIZE];
	CBool m_create;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	inline CVoid SetName(CChar* name) { m_strName = name; }
	inline CChar* GetName() { return m_strName.GetBuffer(m_strName.GetLength()); }

	inline CVoid SetScriptPath(CChar* path) { m_strScript = path; }
	inline CChar* GetScriptPath() { return m_strScript.GetBuffer(m_strScript.GetLength()); }

	inline CVoid SetUpdateScript(CBool state) { m_updateScript = state; }
	inline CBool GetUpdateScript() { return m_updateScript; }

	inline CVoid SetOldName(CChar* name) { Cpy(m_strOldName, name); }
	inline CChar* GetOldName() { return m_strOldName; }
	afx_msg void OnEnChangeEditStartupName();
	afx_msg void OnEnChangeEditScript();

	CVoid SetCreate(CBool state);
	CBool GetCreate();
	afx_msg void OnBnClickedButtonViewScript();
};

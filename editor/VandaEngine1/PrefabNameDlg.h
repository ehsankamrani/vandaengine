#pragma once
#include "afxwin.h"


// CPrefabNameDlg dialog

class CPrefabNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrefabNameDlg)

public:
	CPrefabNameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrefabNameDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PREFAB_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CEdit m_editBoxName;
	afx_msg void OnEnChangePrefabName();
	CVoid SetInitialData(std::string selectedPackageName, std::string selectedPrefabName, CBool package, CBool rename = CFalse);
	std::string m_selectedPackageName;
	std::string m_selectedPrefabName;
	CString m_strName; //edit box field
	std::string m_newName;
	CBool m_package; //are we dealing with package or prefabs?
	CBool m_rename;
	CChar* GetNewName();
};

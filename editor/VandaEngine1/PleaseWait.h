#pragma once


// CPleaseWait dialog

class CPleaseWait : public CDialog
{
	DECLARE_DYNAMIC(CPleaseWait)

public:
	CPleaseWait(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPleaseWait();
	BOOL Create(UINT nID, CWnd * pWnd)
	{
		return CDialog::Create(nID, pWnd);
	}
// Dialog Data
	enum { IDD = IDD_DIALOG_PLEASE_WAIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

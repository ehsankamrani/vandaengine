#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CEditPhysX dialog

class CEditPhysX : public CDialog
{
	DECLARE_DYNAMIC(CEditPhysX)

public:
	CEditPhysX(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditPhysX();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_PHYSX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPhysx();
	afx_msg void OnBnClickedBtnDeletePhysx();
	CVoid SetPhysX( CInstanceGeometry* instanceGeo );
	CVoid RemovePhysXMesh();
	CString m_strPhysX;
	CFloat m_fDensity;
	CString m_strDensity;
	CString m_strPercentage;
	CInt m_iPercentage;
	CInstanceGeometry* m_instanceGeometry;
	CBool m_removePhysXBtnState;
	CBool m_physXBtnState;

	virtual BOOL OnInitDialog();
	CButton m_btnGeneratePhysX;
	CButton m_btnRemovePhysX;
	CComboBox m_comboPhysX;
	CRichEditCtrl m_editBoxPhysX;
	CButton m_checkBoxTrigger;
	CRichEditCtrl m_physXPercentage;
	CRichEditCtrl m_physXDensity;
	afx_msg void OnCbnSelchangeComboPhysx();
	afx_msg void OnEnChangeEditPhysxPercentage();
	afx_msg void OnEnChangeEditPhysxDensity();
	CButton m_checkBoxInvisible;
};

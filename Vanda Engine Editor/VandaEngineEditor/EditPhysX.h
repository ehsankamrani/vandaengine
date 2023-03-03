//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

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

private:
	//These are used for cancel click
	CString init_strPhysX;
	CPhysXAlgorithm init_algorithm;
	CFloat init_density;
	CInt init_percentage;
	CBool init_trigger;
	CBool init_invisible;

	CBool init_hasPhysicsMaterial;
	CFloat init_physicsRestitution;
	CFloat init_physicsStaticFriction;
	CFloat init_physicsDynamicFriction;
	CFloat init_physicsSkinWidth;

	CString m_strPhysicsRestitution;
	CString m_strPhysicsSkinWidth;
	CString m_strPhysicsStaticFriction;
	CString m_strPhysicsDynamicFriction;

	CFloat m_fPhysicsRestitution;
	CFloat m_fPhysicsSkinWidth;
	CFloat m_fPhysicsStaticFriction;
	CFloat m_fPhysicsDynamicFriction;

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
	afx_msg void OnEnChangeEditPhysx();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditPhysicsRestitution();
	afx_msg void OnEnChangeEditPhysicsStaticFriction();
	afx_msg void OnEnChangeEditPhysicsSkinWidth();
	afx_msg void OnEnChangeEditPhysicsDynamicFriction();
	CEdit m_editPhysicsRestitution;
	CEdit m_editPhysicsStaticFriction;
	CEdit m_editPhysicsDynamicFriction;
	CEdit m_editPhysicsSkinWidth;
	CButton m_checkBoxHasPhysicsMaterial;
	afx_msg void OnBnClickedCheckHasPhysicsMaterial();
	afx_msg void OnBnClickedOk();
};

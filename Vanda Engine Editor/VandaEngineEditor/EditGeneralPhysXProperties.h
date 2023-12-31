//Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CEditGeneralPhysXProperties dialog

class CEditGeneralPhysXProperties : public CDialog
{
	DECLARE_DYNAMIC(CEditGeneralPhysXProperties)

public:
	CEditGeneralPhysXProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditGeneralPhysXProperties();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_GENERAL_PHYSX_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBoxRestitution;
	CEdit m_editBoxStaticFriction;
	CEdit m_editBoxDynamicFriction;
	CEdit m_editBoxSkinWidth;
	CButton m_checkBoxDebugMode;
	CButton m_checkBoxApplyGravity;
	CEdit m_editBoxGravityX;
	CEdit m_editBoxGravityY;
	CEdit m_editBoxGravityZ;
	CEdit m_editBoxCameraCharacterDistance;
	CEdit m_editBoxCharacterPower;
	CButton m_checkBoxJumping;
	CEdit m_editBoxCapsuleRadius;
	CEdit m_editBoxCapsuleHeight;
	afx_msg void OnEnChangeEditDefaultRestitution();
	afx_msg void OnEnChangeEditDefaultStaticFriction();
	afx_msg void OnEnChangeEditDefaultSkinWidth();
	afx_msg void OnEnChangeEditDefaultDynamicFriction();
	afx_msg void OnEnChangeEditGravityX();
	afx_msg void OnEnChangeEditGravityY();
	afx_msg void OnEnChangeEditGravityZ();
	afx_msg void OnEnChangeEditCameraCharacterDistance();
	afx_msg void OnEnChangeEditCharacterRadius();
	afx_msg void OnEnChangeEditCharacterHeight();
	afx_msg void OnEnChangeEditCharacterPower();
	CString m_strDefaultRestitution;
	CString m_strDefaultStaticFriction;
	CString m_strDefaultSkinWidth;
	CString m_strDefaultDynamicFriction;
	CString m_strGravityX;
	CString m_strGravityY;
	CString m_strGravityZ;
	CString m_strCameraCharacterDistance;
	CString m_strCapsuleRadius;
	CString m_strCapsuleHeight;
	CString m_strCharacterPower;
	CString m_strJumpPower;
	CString m_strCharacterWalkSpeed;
	CString m_strCharacterRunSpeed;
	CString m_strCharacterSkinWidth;
	CString m_strCharacterStepOffset;
	CString m_strCharacterSlopeLimit;
	CString m_strGroundHeight;

	CFloat m_fDefaultRestitution;
	CFloat m_fDefaultStaticFriction;
	CFloat m_fDefaultSkinWidth;
	CFloat m_fDefaultDynamicFriction;
	CFloat m_fGravityX;
	CFloat m_fGravityY;
	CFloat m_fGravityZ;
	CFloat m_fCameraCharacterDistance;
	CFloat m_fCapsuleRadius;
	CFloat m_fCapsuleHeight;
	CFloat m_fCharacterPower;
	CFloat m_fJumpPower;
	CFloat m_fCharacterWalkSpeed;
	CFloat m_fCharacterRunSpeed;
	CFloat m_fCharacterSkinWidth;
	CFloat m_fCharacterStepOffset;
	CFloat m_fCharacterSlopeLimit;
	CFloat m_fGroundHeight;

	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditCharacterJumpPower();
	afx_msg void OnEnChangeEditCharacterWalkSpeed();
	afx_msg void OnEnChangeEditCharacterRunspeed();
	CEdit m_editBoxJumpPower;
	CEdit m_editBoxCharacterWalkSpeed;
	CEdit m_editBoxCharacterRunSpeed;
	CEdit m_editBoxCharacterSkinWidth;
	CEdit m_editBoxCharacterStepOffset;
	CEdit m_editBoxCharacterSlopeLimit;
	afx_msg void OnEnChangeEditCharacterSkinWidth();
	afx_msg void OnEnChangeEditCharacterStepOffset();
	afx_msg void OnEnChangeEditCharacterSlopeLimit();
	CButton m_checkBoxGroundPlane;
	CEdit m_editBoxGroundHeight;
	afx_msg void OnEnChangeEditGroundHeight();
	afx_msg void OnBnClickedButtonReset();
	CButton m_checkBoxKinematicDynamic;
	CButton m_checkBoxDynamicDynamic;
	CButton m_checkBoxDynamicStatic;
	CButton m_checkBoxDynamicGround;
	CButton m_checkBoxTriggerTrigger;
	CButton m_checkBoxTriggerKinematic;
	CButton m_checkBoxTriggerStatic;
	CButton m_checkBoxTriggerDynamic;
	CButton m_checkBoxTriggerGround;
};

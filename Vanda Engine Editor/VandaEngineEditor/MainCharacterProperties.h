//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CMainCharacterProperties dialog

class CMainCharacterProperties : public CDialog
{
	DECLARE_DYNAMIC(CMainCharacterProperties)

public:
	CMainCharacterProperties(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainCharacterProperties();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHARACTER_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editWalkSpeed;
	CEdit m_editRunSpeed;
	CEdit m_editBoxCameraCharacterDistance;
	CEdit m_editBoxCharacterPower;
	CEdit m_editBoxCapsuleRadius;
	CEdit m_editBoxCapsuleHeight;
	CEdit m_editBoxCharacterSkinWidth;
	CEdit m_editBoxCharacterStepOffset;
	CEdit m_editBoxJumpPower;
	CButton m_checkBoxJumping;
	afx_msg void OnEnChangeEditWalkCharacterSpeed();
	afx_msg void OnEnChangeEditCharacterRunSpeed();
	afx_msg void OnEnChangeEditCameraCharacterDistance();
	afx_msg void OnEnChangeEditCharacterPower();
	afx_msg void OnEnChangeEditCharacterRadius();
	afx_msg void OnEnChangeEditCharacterHeight();
	afx_msg void OnEnChangeEditCharacterSlopeLimit();
	afx_msg void OnEnChangeEditCharacterSkinWidth();
	afx_msg void OnEnChangeEditCharacterStepOffset();
	afx_msg void OnEnChangeEditCharacterJumpPower();
private:
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

	CString m_strIdleDelayIn;
	CString m_strWalkDelayIn;
	CString m_strRunDelayIn;
	CString m_strJumpDelayIn;
	CString m_strJumpDelayOut;

	//camera
	CString m_strDefaultFOV;
	CString m_strMinFOV;
	CString m_strMaxFOV;
	CString m_strDefaultTilt;
	CString m_strMinTilt;
	CString m_strMaxTilt;


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
	CFloat m_fIdleDelayIn;
	CFloat m_fWalkDelayIn;
	CFloat m_fRunDelayIn;
	CFloat m_fJumpDelayIn;
	CFloat m_fJumpDelayOut;

	//camera
	CFloat m_fDefaultFOV;
	CFloat m_fMinFOV;
	CFloat m_fMaxFOV;
	CFloat m_fDefaultTilt;
	CFloat m_fMinTilt;
	CFloat m_fMaxTilt;


public:
	CEdit m_editBoxCharacterSlopeLimit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CPhysXProperties m_physXProperties;
	inline CVoid SetPhysXProperties(CPhysXProperties properties) { m_physXProperties = properties; }

	CCharacterBlendingProperties m_characterBlendingProperties;
	CUpdateCamera* m_camera;
	inline CVoid SetCharacterBlendingProperties(CCharacterBlendingProperties properties) { m_characterBlendingProperties = properties; }
	CVoid SetCharacterCameraProperties(CUpdateCamera* properties);

	CButton m_checkBoxDebugMode;
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnEnChangeEditIdleDelayIn();
	afx_msg void OnEnChangeEditWalkDelayIn();
	afx_msg void OnEnChangeEditRunDelayIn();
	afx_msg void OnEnChangeEditJumpDelayIn();
	afx_msg void OnEnChangeEditJumpDelayOut();
	CEdit m_editBoxIdleDelayIn;
	CEdit m_editBoxWalkDelayIn;
	CEdit m_editBoxRunDelayIn;
	CEdit m_editBoxJumpDelayIn;
	CEdit m_editBoxJumpDelayOut;
	CEdit m_editBoxDefaultFOV;
	CEdit m_editBoxMinFOV;
	CEdit m_editBoxMaxFOV;
	CEdit m_editBoxDefaultTilt;
	CEdit m_editBoxMinTilt;
	CEdit m_editBoxMaxTilt;
	afx_msg void OnEnChangeEditCameraDefaultFov();
	afx_msg void OnEnChangeEditCameraMinFov();
	afx_msg void OnEnChangeEditCameraMaxFov();
	afx_msg void OnEnChangeEditCameraDefaultTilt();
	afx_msg void OnEnChangeEditCameraMinTilt();
	afx_msg void OnEnChangeEditCameraMaxTilt();
};

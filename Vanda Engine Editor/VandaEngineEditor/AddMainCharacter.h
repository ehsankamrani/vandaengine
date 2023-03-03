//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"

// CAddMainCharacter dialog

class CAddMainCharacter : public CDialog
{
	DECLARE_DYNAMIC(CAddMainCharacter)

public:
	CAddMainCharacter(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddMainCharacter();

// Dialog Data
	enum { IDD = IDD_DIALOG_ADD_CHARACTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSelectJump();
	afx_msg void OnBnClickedButtonSelectRun();
	afx_msg void OnBnClickedButtonSelectWalk();
	afx_msg void OnBnClickedButtonSelectIdle();
	afx_msg void OnBnClickedButtonSelectCharacter();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_comboIdle;
	CComboBox m_comboWalk;
	CComboBox m_comboRun;
	CComboBox m_comboJump;
	afx_msg void OnBnClickedButtonProperties();
	CEdit m_editCharacterModel;
	afx_msg void OnBnClickedButtonRemoveCharacter();
	afx_msg void OnBnClickedButtonRemoveIdle();
	afx_msg void OnBnClickedButtonRemoveWalk();
	afx_msg void OnBnClickedButtonRemoveRun();
	afx_msg void OnBnClickedButtonRemoveJump();
	CEdit m_editName;
	CString m_strName;
	CInt m_idleIndex;
	CInt m_walkIndex;
	CInt m_jumpIndex;
	CInt m_runIndex;
	CBool m_bRemoved;
	CBool m_bCharacterChanged;
	CChar m_oldName[MAX_NAME_SIZE];
	CInstancePrefab* m_instance;
	afx_msg void OnBnClickedButtonLoadProfile();
	afx_msg void OnBnClickedButtonSaveProfile();
	afx_msg void OnEnChangeEditName();
	CVoid SetCharacterCameraType(CPhysXCameraType m_characterType);
	CVoid SetCharacterName(CChar* name);
	CVoid SetCharacterPosition(CVec3f pos);
	CVoid SetCharacterScale(CFloat scale);
	CVoid SetCharacterPlayMoreIdlesEveryXSeconds(CFloat m_delayIdle);
	CVoid SetIdle(std::vector<std::string> idleName);
	CVoid SetWalk(std::vector<std::string> walkName);
	CVoid SetRun(std::vector<std::string> runName);
	CVoid SetJump(std::vector<std::string> jumpName);
	CVoid Init(CChar* oldName);
	CVoid Destroy();
	afx_msg void OnBnClickedCancel();
	CBool m_newCharacter;
private:
	CChar m_characterName[MAX_NAME_SIZE];
	std::vector<std::string> m_idleName;
	std::vector<std::string> m_walkName;
	std::vector<std::string> m_jumpName;
	std::vector<std::string> m_runName;

	CString m_strPosX;
	CString m_strPosY;
	CString m_strPosZ;
	CString m_strScale;

	CString m_strPlayMoreIdlesEveryXSeconds;

	CPhysXCameraType m_characterType;
	CVec3f m_position;
	CFloat m_scale;

	CFloat m_fPlayMoreIdlesEveryXSeconds;

public:
	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editPosZ;
	CEdit m_editScale;
	afx_msg void OnEnChangeEditPosX();
	afx_msg void OnEnChangeEditPosY();
	afx_msg void OnEnChangeEditPosZ();
	afx_msg void OnEnChangeEditPosScale();
	CPhysXProperties m_physXProperties;
	CCharacterBlendingProperties m_characterBlendingProperties;
	CCharacterSoundProperties m_characterSoundProperties;
	CBool m_clickedWalkSound;
	CBool m_clickedRunSound;
	CBool m_clickedJumpSound;
	CUpdateCamera* m_camera;
	CVoid SetPhysXProperties(CPhysXProperties properties);
	CVoid SetCharacterBlendingProperties(CCharacterBlendingProperties properties);
	CVoid SetCharacterCameraProperties(CUpdateCamera* properties);
	CVoid SetCharacterSoundProperties(CCharacterSoundProperties properties);
	CEdit m_editBoxPlayMoreIdlesEveryXSeconds;
	afx_msg void OnEnChangeEditDelayPlayMoreIdlesRandomly();
	afx_msg void OnBnClickedButtonSounds();

	CVoid SetClickedWalkSound(CBool state);
	CVoid SetClickedRunSound(CBool state);
	CVoid SetClickedJumpSound(CBool state);
	afx_msg void OnBnClickedBtnAddScript();
	afx_msg void OnBnClickedBtnRemoveScript();
	afx_msg void OnBnClickedButtonViewScript();
	CRichEditCtrl m_editBoxScript;

	private:
		CBool m_scriptUpdated;
		CString m_strScript;
		CBool m_hasScript;
};

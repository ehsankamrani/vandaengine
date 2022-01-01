//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSaveLoadCharacterProfile dialog

class CSaveLoadCharacterProfile : public CDialog
{
	DECLARE_DYNAMIC(CSaveLoadCharacterProfile)

public:
	CSaveLoadCharacterProfile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSaveLoadCharacterProfile();

// Dialog Data
	enum { IDD = IDD_DIALOG_SAVE_LOAD_CHARACTER_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCharacterProfiles;
	CEdit m_editName;
	CString m_strName;
	CInt m_profileIndex;
	CImageList m_profileImage;
	CBool m_save;
	CChar m_name[MAX_NAME_SIZE];
	CVoid SetCharacterCameraType(CPhysXCameraType type);
	CChar* GetName();
	CVoid SetIdleName(std::vector<std::string> idle);
	CVoid SetWalkName(std::vector<std::string> walk);
	CVoid SetJumpName(std::vector<std::string> jump);
	CVoid SetRunName(std::vector<std::string> run);
	CVoid SetCharacterName(CChar* name);
	CVoid SetPosition(CVec3f pos);
	CVoid SetScale(CFloat scale);
	CVoid SetPlayMoreIdlesEveryXSeconds(CFloat delayIdle);
	CVoid SetPhysXProperties(CPhysXProperties physXProperties);
	CVoid SetCharacterBlendingProperties(CCharacterBlendingProperties properties);
	CVoid SetCharacterCameraProperties(CUpdateCamera* m_camera);
	std::vector<std::string> m_idle;
	std::vector<std::string> m_walk;
	std::vector<std::string> m_jump;
	std::vector<std::string> m_run;
	CChar m_characterName[MAX_NAME_SIZE];
	CPhysXCameraType m_characterType;
	afx_msg void OnEnChangeProfileName();
	virtual BOOL OnInitDialog();
	CVoid SetSaveMode(CBool save);
	afx_msg void OnLvnItemchangedListCharacterProfiles(NMHDR *pNMHDR, LRESULT *pResult);
	CVoid InsertItemToProfileList(CChar* profileName);
	afx_msg void OnBnClickedOk();

private:
	CFloat m_scale;
	CFloat m_delayIdle;
	CVec3f m_position;
	CPhysXProperties m_physXProperties;
	CCharacterBlendingProperties m_characterBlendingProperties;
	CUpdateCamera* m_camera;
};

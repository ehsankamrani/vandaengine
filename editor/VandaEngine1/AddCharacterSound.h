//Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxwin.h"


// CAddCharacterSound dialog

class CAddCharacterSound : public CDialog
{
	DECLARE_DYNAMIC(CAddCharacterSound)

public:
	CAddCharacterSound(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddCharacterSound();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHARACTER_SOUNDS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editWalkSound;
	CEdit m_editRunSound;
	CEdit m_editJumpSound;

	CString m_strWalkSoundDataPath;
	CString m_strWalkSoundPureDataPath;
	CString m_strRunSoundDataPath;
	CString m_strRunSoundPureDataPath;
	CString m_strJumpSoundDataPath;
	CString m_strJumpSoundPureDataPath;

	CVoid SetCharacterSoundProperties(CCharacterSoundProperties properties);
	CCharacterSoundProperties m_characterSoundProperties;

	afx_msg void OnBnClickedButtonSelectWalk();
	afx_msg void OnBnClickedButtonSelectRun();
	afx_msg void OnBnClickedButtonSelectJump();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};

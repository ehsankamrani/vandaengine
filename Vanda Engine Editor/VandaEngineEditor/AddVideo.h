//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "afxdialogex.h"


// CAddVideo dialog

class CAddVideo : public CDialog
{
	DECLARE_DYNAMIC(CAddVideo)

public:
	CAddVideo(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddVideo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_VIDEO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonVideoData();
	afx_msg void OnBnClickedBtnAddScript();
	afx_msg void OnBnClickedBtnRemoveScript();
	afx_msg void OnBnClickedButtonViewScript();
	CEdit m_editBoxVideoData;
	CRichEditCtrl m_editBoxScript;
	CComboBox m_comboVideoPlay;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CBool m_create;
	CBool m_editMode;
	CString m_strVideoName;
	CString m_strVideoTempName;
	CString m_strVideoDataPath;
	CString m_strVideoDataFileName;
	CString m_strAudioVolume;
	CChar m_videoFileName[MAX_NAME_SIZE];

public:
	//Set
	CVoid SetPath(CChar* path)
	{
		m_strVideoDataPath = path;
	}
	CVoid SetEditMode(CBool editMode)
	{
		m_editMode = editMode;
	}
	CVoid SetCreate(CBool create)
	{
		if (create) m_create = CTrue;
		else m_create = CFalse;
	}
	CVoid SetVideoFileName(CChar* fileName)
	{
		Cpy(m_videoFileName, fileName);
	}
	CVoid SetLoop(CBool loop)
	{
		m_loop = loop;
	}

	CVoid SetPlay(CBool play)
	{
		m_play = play;
	}

	CVoid SetVolume(CFloat volume)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%.3f", volume);
		m_strAudioVolume = temp;
	}

	CVoid SetName(CChar* name)
	{
		m_strVideoName = name;
	}

	CVoid SetLastName(CChar* name)
	{
		Cpy(m_lastName, name);
	}

	CVoid SetExitWithEscKey(CBool set) { m_exitWithEscKey = set; }
	CVoid SetPlayAudio(CBool set) { m_playAudio = set; }

	CVoid SetHasScript(CBool hasScript) { m_hasScript = hasScript; }
	CVoid SetScriptPath(CChar* scriptPath) { m_strScript = scriptPath; }
	CVoid SetUpdateScript(CBool update) { m_scriptUpdated = update; }
	CVoid SetUpdateData(CBool update) { m_dataUpdated = update; }
	
	//Get
	CChar* GetName() { return (CChar*)m_strVideoName.GetBuffer(m_strVideoName.GetLength()); m_strVideoName.ReleaseBuffer(); }
	CChar* GetTempName() { return (CChar*)m_strVideoTempName.GetBuffer(m_strVideoTempName.GetLength()); m_strVideoTempName.ReleaseBuffer(); }
	CChar* GetLastName() { return m_lastName; }
	CChar* GetPath() { return (CChar*)m_strVideoDataPath.GetBuffer(m_strVideoDataPath.GetLength()); m_strVideoDataPath.ReleaseBuffer(); }
	CBool GetPlay() { return m_play; }
	CBool GetLoop() { return m_loop; }
	CFloat GetVolume() { return m_volume; }
	CChar* GetVideoFileName() { return m_videoFileName; }
	CBool GetHasScript() { return m_hasScript; }
	CChar* GetScriptPath() { return m_strScript.GetBuffer(m_strScript.GetLength()); }
	CBool GetUpdateScript() { return m_scriptUpdated; }
	CBool GetUpdateData() { return m_dataUpdated; }
	CBool GetExitWithEscKey() { return m_exitWithEscKey; }
	CBool GetPlayAudio() { return m_playAudio; }
private:
	CBool m_scriptUpdated;
	CBool m_dataUpdated;
	CString m_strScript;
	CBool m_hasScript;
	CChar m_lastName[MAX_NAME_SIZE];
	CBool m_loop, m_play;
	CFloat m_volume;
public:
	afx_msg void OnEnChangeEditVideoName();
	CEdit m_editBoxVideoName;
	CComboBox m_comboVideoLoop;
	afx_msg void OnCbnSelchangeComboVideoLoop();
	afx_msg void OnCbnSelchangeComboVideoPlay();
	CEdit m_editBoxAudioVolume;
	afx_msg void OnEnChangeEditAudioVolume();
private:
	CButton m_checkExitWithEscKey;
	CBool m_exitWithEscKey;
	CBool m_playAudio;
public:
	CButton m_checkPlaySound;
};

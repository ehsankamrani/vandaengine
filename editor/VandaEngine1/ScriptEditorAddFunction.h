#pragma once
#include "afxcmn.h"


// CScriptEditorAddFunction dialog

class CScriptEditorAddFunction : public CDialog
{
	DECLARE_DYNAMIC(CScriptEditorAddFunction)
private:
	CInt m_index;
public:
	CScriptEditorAddFunction(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptEditorAddFunction();

// Dialog Data
	enum { IDD = IDD_DIALOG_SCRIPT_EDITOR_ADD_FUNCTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listFunctions;
	CRichEditCtrl m_richFunctionName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListFunctions(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CVoid InsertItem(CChar* name);
private:
	CChar PlaySoundLoop[MAX_URI_SIZE];
	CChar PlaySoundOnce[MAX_URI_SIZE];
	CChar PauseSound[MAX_URI_SIZE];
	CChar StopSound[MAX_URI_SIZE];

	CChar BlendCycle[MAX_URI_SIZE];
	CChar ClearCycle[MAX_URI_SIZE];
	CChar ExecuteAction[MAX_URI_SIZE];
	CChar ReverseExecuteAction[MAX_URI_SIZE];
	CChar RemoveAction[MAX_URI_SIZE];
	CChar GetAnimationClipDuration[MAX_URI_SIZE];
	CChar PauseAnimations[MAX_URI_SIZE];

	CChar LoadVScene[MAX_URI_SIZE];
	CChar ExitGame[MAX_URI_SIZE];
	CChar SetCurrentVSceneAsMenu[MAX_URI_SIZE];

	CChar ActivateThirdPersonCamera[MAX_URI_SIZE];
	CChar ActivateFirstPersonCamera[MAX_URI_SIZE];
	CChar ActivateImportedCamera[MAX_URI_SIZE];
	CChar ActivateImportedCameraOfPrefab[MAX_URI_SIZE];
	CChar ActivateEngineCamera[MAX_URI_SIZE];

	CChar LoadResource[MAX_URI_SIZE];
	CChar DeleteAllResources[MAX_URI_SIZE];
	CChar PlayResourceSoundLoop[MAX_URI_SIZE];
	CChar PlayResourceSoundOnce[MAX_URI_SIZE];
	CChar StopResourceSound[MAX_URI_SIZE];
	CChar PauseResourceSound[MAX_URI_SIZE];
	CChar StopAllResourceSounds[MAX_URI_SIZE];
	CChar ShowCursorIcon[MAX_URI_SIZE];
	CChar HideCursorIcon[MAX_URI_SIZE];

	CChar AttachScriptToKey[MAX_URI_SIZE];
	CChar PrintConsole[MAX_URI_SIZE];

	CChar ShowGUI[MAX_URI_SIZE];
	CChar HideGUI[MAX_URI_SIZE];

	CChar SetPrefabInstanceVisible[MAX_URI_SIZE];
	CChar SetPrefabInstanceInvisible[MAX_URI_SIZE];

public:
	afx_msg void OnBnClickedCancel();
};

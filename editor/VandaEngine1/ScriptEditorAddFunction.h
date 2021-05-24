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
	CChar ActivateImportedCameraOfPrefabInstance[MAX_URI_SIZE];
	CChar ActivateEngineCamera[MAX_URI_SIZE];
	CChar SetPhysicsCameraAngle[MAX_URI_SIZE];
	CChar GetPhysicsCameraAngle[MAX_URI_SIZE];

	CChar LoadResource[MAX_URI_SIZE];
	CChar DeleteAllResources[MAX_URI_SIZE];
	CChar PlayResourceSoundLoop[MAX_URI_SIZE];
	CChar PlayResourceSoundOnce[MAX_URI_SIZE];
	CChar StopResourceSound[MAX_URI_SIZE];
	CChar PauseResourceSound[MAX_URI_SIZE];
	CChar StopAllResourceSounds[MAX_URI_SIZE];
	CChar ShowCursorIcon[MAX_URI_SIZE];
	CChar HideCursorIcon[MAX_URI_SIZE];

	CChar PrintConsole[MAX_URI_SIZE];

	CChar ShowGUI[MAX_URI_SIZE];
	CChar HideGUI[MAX_URI_SIZE];

	CChar IsKeyDown[MAX_URI_SIZE];

	CChar ShowPrefabInstance[MAX_URI_SIZE];
	CChar HidePrefabInstance[MAX_URI_SIZE];

	CChar SetSelectionDistance[MAX_URI_SIZE];
	CChar GetSelectionDistance[MAX_URI_SIZE];
	CChar SelectPrefabInstances[MAX_URI_SIZE];

	//get
	CChar GetScreenWidth[MAX_URI_SIZE];
	CChar GetScreenHeight[MAX_URI_SIZE];
	CChar GetCursorX[MAX_URI_SIZE];
	CChar GetCursorY[MAX_URI_SIZE];
	CChar GetElapsedTime[MAX_URI_SIZE];
	CChar IsMenuEnabled[MAX_URI_SIZE];

	CChar TranslatePrefabInstance[MAX_URI_SIZE];
	CChar RotatePrefabInstance[MAX_URI_SIZE];
	CChar ScalePrefabInstance[MAX_URI_SIZE];

	CChar GetPrefabInstanceTranslate[MAX_URI_SIZE];
	CChar GetPrefabInstanceRotate[MAX_URI_SIZE];
	CChar GetPrefabInstanceScale[MAX_URI_SIZE];

public:
	afx_msg void OnBnClickedCancel();
};

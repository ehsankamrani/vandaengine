// ScriptEditorAddFunction.cpp : implementation file
//

#include "stdafx.h"
#include "VandaEngine1.h"
#include "ScriptEditorAddFunction.h"
#include "afxdialogex.h"


// CScriptEditorAddFunction dialog

IMPLEMENT_DYNAMIC(CScriptEditorAddFunction, CDialog)

CScriptEditorAddFunction::CScriptEditorAddFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptEditorAddFunction::IDD, pParent)
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CFalse);

	m_index = -1;
	Cpy( PlaySoundLoop, "PlaySoundLoop(string gameObjectSoundName)");
	Cpy(PlaySoundOnce, "PlaySoundOnce(string gameObjectSoundName)");
	Cpy(PauseSound, "PauseSound(string gameObjectSoundName)");
	Cpy(StopSound, "StopSound(string gameObjectSoundName)");

	Cpy(BlendCycle, "BlendCycle(string prefabInstanceName, string animationClipName, float weightTarget, float delayIn)");
	Cpy(ClearCycle, "ClearCycle(string prefabInstanceName, string animationClipName, float delayOut)");
	Cpy(ExecuteAction, "ExecuteAction(string prefabInstanceName, string animationClipName, float delayIn, float delayOut, float weightTarget, bool lock)");
	Cpy(ReverseExecuteAction, "ReverseExecuteAction(string prefabInstanceName, string animationClipName)");
	Cpy(RemoveAction, "RemoveAction(string prefabInstanceName, string animationClipName)");
	Cpy(GetAnimationClipDuration, "GetAnimationClipDuration(string prefabInstanceName, string animationClipName)");
	Cpy(PauseAnimations, "PauseAnimations(string prefabInstanceName)");

	Cpy(LoadVScene, "LoadVScene(string VSceneName)");
	Cpy(ExitGame, "ExitGame()");
	Cpy(SetCurrentVSceneAsMenu, "SetCurrentVSceneAsMenu(bool isMenu, bool PauseOrResumeGame, float cursorSize)");

	Cpy(ActivateThirdPersonCamera, "ActivateThirdPersonCamera()");
	Cpy(ActivateFirstPersonCamera, "ActivateFirstPersonCamera()");
	Cpy(ActivateImportedCamera, "ActivateImportedCamera(string importedCameraFullName, float endTime[optional])");
	Cpy(ActivateImportedCameraOfPrefabInstance, "ActivateImportedCameraOfPrefabInstance(string prefabInstanceName, string prefabCameraName, float endTime[optional])");
	Cpy(ActivateEngineCamera, "ActivateEngineCamera(string gameObjectCameraName, float endTime[optional])");
	Cpy(SetPhysicsCameraAngle, "SetPhysicsCameraAngle(float angle)");
	Cpy(GetPhysicsCameraAngle, "GetPhysicsCameraAngle()");

	Cpy(LoadResource, "LoadResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteResource, "DeleteResource(string resourceDirectoryName, string resourceFileName)");
	Cpy(DeleteAllResources, "DeleteAllResources()");
	Cpy(PlayResourceSoundLoop, "PlayResourceSoundLoop(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PlayResourceSoundOnce, "PlayResourceSoundOnce(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(StopResourceSound, "StopResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(PauseResourceSound, "PauseResourceSound(string resourceDirectoryName_resourceFileName.ogg)");
	Cpy(StopAllResourceSounds, "StopAllResourceSounds()");
	Cpy(ShowCursorIcon, "ShowCursorIcon(string resourceDirectoryName_resourceFileName.dds, float cursorSize)");
	Cpy(HideCursorIcon, "HideCursorIcon(string resourceDirectoryName_resourceFileName.dds)");

	Cpy(PrintConsole, "PrintConsole(string message)");

	Cpy(ShowGUI, "ShowGUI(string guiName)");
	Cpy(HideGUI, "HideGUI(string guiName)");

	Cpy(IsKeyDown, "IsKeyDown(string DirectInputKeyCode)");

	Cpy(ShowPrefabInstance, "ShowPrefabInstance(string prefabInstanceName)");
	Cpy(HidePrefabInstance, "HidePrefabInstance(string prefabInstanceName)");

	Cpy(SetSelectionDistance, "SetSelectionDistance(float selectionDistance)");
	Cpy(GetSelectionDistance, "GetSelectionDistance()");
	Cpy(SelectPrefabInstances , "SelectPrefabInstances(double mousePositionX, double mousePositionY, double selectionWidthSize, double selectionHeightSize)");
	Cpy(GetScreenWidth, "GetScreenWidth()");
	Cpy(GetScreenHeight, "GetScreenHeight()");
	Cpy(GetCursorX, "GetCursorX()");
	Cpy(GetCursorY, "GetCursorY()");
	Cpy(IsMenuEnabled, "IsMenuEnabled()");
	Cpy(GetElapsedTime, "GetElapsedTime()");
	Cpy(GetPrefabInstanceNameFromActor, "GetPrefabInstanceNameFromActor(string physicsActorName)");

	Cpy(TranslatePrefabInstance, "TranslatePrefabInstance(string prefabInstanceName, float XPosition, float YPosition, float ZPosition)");
	Cpy(RotatePrefabInstance, "RotatePrefabInstance(string prefabInstanceName, float XRotationAngle, float YRotationAngle, float ZRotationAngle)");
	Cpy(ScalePrefabInstance, "ScalePrefabInstance(string prefabInstanceName, float XScale, float YScale, float ZScale)");

	Cpy(GetPrefabInstanceTranslate, "GetPrefabInstanceTranslate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceRotate, "GetPrefabInstanceRotate(string prefabInstanceName)");
	Cpy(GetPrefabInstanceScale, "GetPrefabInstanceScale(string prefabInstanceName)");

	Cpy(GetPrefabInstanceRadius, "GetPrefabInstanceRadius(string prefabInstanceName)");
	Cpy(GetDistanceOfPrefabInstanceFromPhysicsCamera, "GetDistanceOfPrefabInstanceFromPhysicsCamera(string prefabInstanceName)");

	Cpy(EnableDepthOfField, "EnableDepthOfField()");
	Cpy(DisableDepthOfField, "DisableDepthOfField()");
	Cpy(SetDepthOfFieldFocalDistance, "SetDepthOfFieldFocalDistance(float focalDistance)");
	Cpy(SetDepthOfFieldFocalRange, "SetDepthOfFieldFocalRange(float focalRange)");

	Cpy(EnableFog, "EnableFog()");
	Cpy(DisableFog, "DisableFog()");
	Cpy(SetFogColor, "SetFogColor(float red, float green, float blue)");
	Cpy(SetFogDensity, "SetFogDensity(float density)");

	Cpy(EnableBloom, "EnableBloom()");
	Cpy(DisableBloom, "DisableBloom()");
	Cpy(SetBloomColor, "SetBloomColor(float red, float green, float blue)");
	Cpy(SetBloomIntensity, "SetBloomIntensity(float intensity)");

	Cpy(EnableDirectionalShadow, "EnableDirectionalShadow()");
	Cpy(DisableDirectionalShadow, "DisableDirectionalShadow()");
	Cpy(SetDirectionalShadowAlgorithm, "SetDirectionalShadowAlgorithm(string shadowAlgorithmCode)");
	Cpy(SetDirectionalShadowNumberOfSplits, "SetDirectionalShadowNumberOfSplits(int numberOfSplits)");
	Cpy(SetDirectionalShadowWeightOfSplits, "SetDirectionalShadowWeightOfSplits(float weightOfSplits)");
	Cpy(SetDirectionalShadowNearClipPlane, "SetDirectionalShadowNearClipPlane(float nearClipPlane)");
	Cpy(SetDirectionalShadowFarClipPlane, "SetDirectionalShadowFarClipPlane(float farClipPlane)");
	Cpy(SetDirectionalShadowResolution, "SetDirectionalShadowResolution(int shadowResolution)");
	Cpy(SetDirectionalShadowIntensity, "SetDirectionalShadowIntensity(float shadowIntensity)");
	Cpy(SetDirectionalShadowLight, "SetDirectionalShadowLight(string directionalLightName)");

}

CScriptEditorAddFunction::~CScriptEditorAddFunction()
{
}

void CScriptEditorAddFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FUNCTIONS, m_listFunctions);
	DDX_Control(pDX, IDC_RICHED_FUNCTION_NAME, m_richFunctionName);
}


BEGIN_MESSAGE_MAP(CScriptEditorAddFunction, CDialog)
	ON_BN_CLICKED(IDOK, &CScriptEditorAddFunction::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FUNCTIONS, &CScriptEditorAddFunction::OnLvnItemchangedListFunctions)
	ON_BN_CLICKED(IDCANCEL, &CScriptEditorAddFunction::OnBnClickedCancel)
END_MESSAGE_MAP()


// CScriptEditorAddFunction message handlers


void CScriptEditorAddFunction::OnBnClickedOk()
{
	CString s;
	m_richFunctionName.GetWindowTextA(s);
	if (s.IsEmpty())
	{
		MessageBox("Please select an item from the list", "Error", MB_OK | MB_ICONERROR);
		return;
	}
	else
	{
		m_richFunctionName.Copy();
	}
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);

	CDialog::OnOK();
}


void CScriptEditorAddFunction::OnLvnItemchangedListFunctions(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nSelected = -1;
	POSITION p = m_listFunctions.GetFirstSelectedItemPosition();
	while (p)
	{
		nSelected = m_listFunctions.GetNextSelectedItem(p);
	}
	TCHAR szBuffer[1024];

	if (nSelected >= 0)
	{
		DWORD cchBuf(1024);
		LVITEM lvi;
		lvi.iItem = nSelected;
		lvi.iSubItem = 0;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuffer;
		lvi.cchTextMax = cchBuf;
		m_listFunctions.GetItem(&lvi);

		if (Cmp(szBuffer, "PlaySoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlaySoundLoop);
		}
		else if (Cmp(szBuffer, "PlaySoundOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlaySoundOnce);
		}
		else if (Cmp(szBuffer, "PauseSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseSound);
		}
		else if (Cmp(szBuffer, "StopSound"))
		{
			m_richFunctionName.SetWindowTextA(StopSound);
		}
		else if (Cmp(szBuffer, "BlendCycle"))
		{
			m_richFunctionName.SetWindowTextA(BlendCycle);
		}
		else if (Cmp(szBuffer, "ClearCycle"))
		{
			m_richFunctionName.SetWindowTextA(ClearCycle);
		}
		else if (Cmp(szBuffer, "ExecuteAction"))
		{
			m_richFunctionName.SetWindowTextA(ExecuteAction);
		}
		else if (Cmp(szBuffer, "ReverseExecuteAction"))
		{
			m_richFunctionName.SetWindowTextA(ReverseExecuteAction);
		}
		else if (Cmp(szBuffer, "RemoveAction"))
		{
			m_richFunctionName.SetWindowTextA(RemoveAction);
		}
		else if (Cmp(szBuffer, "GetAnimationClipDuration"))
		{
			m_richFunctionName.SetWindowTextA(GetAnimationClipDuration);
		}
		else if (Cmp(szBuffer, "PauseAnimations"))
		{
			m_richFunctionName.SetWindowTextA(PauseAnimations);
		}
		else if (Cmp(szBuffer, "LoadVScene"))
		{
			m_richFunctionName.SetWindowTextA(LoadVScene);
		}
		else if (Cmp(szBuffer, "ExitGame"))
		{
			m_richFunctionName.SetWindowTextA(ExitGame);
		}
		else if (Cmp(szBuffer, "SetCurrentVSceneAsMenu"))
		{
			m_richFunctionName.SetWindowTextA(SetCurrentVSceneAsMenu);
		}
		else if (Cmp(szBuffer, "ActivateThirdPersonCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateThirdPersonCamera);
		}
		else if (Cmp(szBuffer, "ActivateFirstPersonCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateFirstPersonCamera);
		}
		else if (Cmp(szBuffer, "ActivateImportedCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateImportedCamera);
		}
		else if (Cmp(szBuffer, "ActivateImportedCameraOfPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ActivateImportedCameraOfPrefabInstance);
		}
		else if (Cmp(szBuffer, "ActivateEngineCamera"))
		{
			m_richFunctionName.SetWindowTextA(ActivateEngineCamera);
		}
		else if (Cmp(szBuffer, "SetPhysicsCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(SetPhysicsCameraAngle);
		}
		else if (Cmp(szBuffer, "GetPhysicsCameraAngle"))
		{
			m_richFunctionName.SetWindowTextA(GetPhysicsCameraAngle);
		}
		else if (Cmp(szBuffer, "LoadResource"))
		{
			m_richFunctionName.SetWindowTextA(LoadResource);
		}
		else if (Cmp(szBuffer, "DeleteResource"))
		{
			m_richFunctionName.SetWindowTextA(DeleteResource);
		}
		else if (Cmp(szBuffer, "DeleteAllResources"))
		{
			m_richFunctionName.SetWindowTextA(DeleteAllResources);
		}
		else if (Cmp(szBuffer, "PlayResourceSoundLoop"))
		{
			m_richFunctionName.SetWindowTextA(PlayResourceSoundLoop);
		}
		else if (Cmp(szBuffer, "PlayResourceSoundOnce"))
		{
			m_richFunctionName.SetWindowTextA(PlayResourceSoundOnce);
		}
		else if (Cmp(szBuffer, "StopResourceSound"))
		{
			m_richFunctionName.SetWindowTextA(StopResourceSound);
		}
		else if (Cmp(szBuffer, "PauseResourceSound"))
		{
			m_richFunctionName.SetWindowTextA(PauseResourceSound);
		}
		else if (Cmp(szBuffer, "StopAllResourceSounds"))
		{
			m_richFunctionName.SetWindowTextA(StopAllResourceSounds);
		}
		else if (Cmp(szBuffer, "ShowCursorIcon"))
		{
			m_richFunctionName.SetWindowTextA(ShowCursorIcon);
		}
		else if (Cmp(szBuffer, "HideCursorIcon"))
		{
			m_richFunctionName.SetWindowTextA(HideCursorIcon);
		}
		else if (Cmp(szBuffer, "PrintConsole"))
		{
			m_richFunctionName.SetWindowTextA(PrintConsole);
		}
		else if (Cmp(szBuffer, "ShowGUI"))
		{
			m_richFunctionName.SetWindowTextA(ShowGUI);
		}
		else if (Cmp(szBuffer, "HideGUI"))
		{
			m_richFunctionName.SetWindowTextA(HideGUI);
		}
		else if (Cmp(szBuffer, "IsKeyDown"))
		{
			m_richFunctionName.SetWindowTextA(IsKeyDown);
		}
		else if (Cmp(szBuffer, "ShowPrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ShowPrefabInstance);
		}
		else if (Cmp(szBuffer, "HidePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(HidePrefabInstance);
		}
		else if (Cmp(szBuffer, "SetSelectionDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetSelectionDistance);
		}
		else if (Cmp(szBuffer, "GetSelectionDistance"))
		{
			m_richFunctionName.SetWindowTextA(GetSelectionDistance);
		}
		else if (Cmp(szBuffer, "SelectPrefabInstances"))
		{
			m_richFunctionName.SetWindowTextA(SelectPrefabInstances);
		}
		else if (Cmp(szBuffer, "GetScreenWidth"))
		{
			m_richFunctionName.SetWindowTextA(GetScreenWidth);
		}
		else if (Cmp(szBuffer, "GetScreenHeight"))
		{
			m_richFunctionName.SetWindowTextA(GetScreenHeight);
		}
		else if (Cmp(szBuffer, "GetCursorX"))
		{
			m_richFunctionName.SetWindowTextA(GetCursorX);
		}
		else if (Cmp(szBuffer, "GetCursorY"))
		{
			m_richFunctionName.SetWindowTextA(GetCursorY);
		}
		else if (Cmp(szBuffer, "IsMenuEnabled"))
		{
			m_richFunctionName.SetWindowTextA(IsMenuEnabled);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceNameFromActor"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceNameFromActor);
		}
		else if (Cmp(szBuffer, "GetElapsedTime"))
		{
			m_richFunctionName.SetWindowTextA(GetElapsedTime);
		}
		else if (Cmp(szBuffer, "TranslatePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(TranslatePrefabInstance);
		}
		else if (Cmp(szBuffer, "RotatePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(RotatePrefabInstance);
		}
		else if (Cmp(szBuffer, "ScalePrefabInstance"))
		{
			m_richFunctionName.SetWindowTextA(ScalePrefabInstance);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceTranslate"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceTranslate);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceRotate"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceRotate);
		}
		else if (Cmp(szBuffer, "GetPrefabInstanceScale"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceScale);
		}

		else if (Cmp(szBuffer, "GetPrefabInstanceRadius"))
		{
			m_richFunctionName.SetWindowTextA(GetPrefabInstanceRadius);
		}
		else if (Cmp(szBuffer, "GetDistanceOfPrefabInstanceFromPhysicsCamera"))
		{
			m_richFunctionName.SetWindowTextA(GetDistanceOfPrefabInstanceFromPhysicsCamera);
		}
		else if (Cmp(szBuffer, "EnableDepthOfField"))
		{
			m_richFunctionName.SetWindowTextA(EnableDepthOfField);
		}
		else if (Cmp(szBuffer, "DisableDepthOfField"))
		{
			m_richFunctionName.SetWindowTextA(DisableDepthOfField);
		}
		else if (Cmp(szBuffer, "SetDepthOfFieldFocalDistance"))
		{
			m_richFunctionName.SetWindowTextA(SetDepthOfFieldFocalDistance);
		}
		else if (Cmp(szBuffer, "SetDepthOfFieldFocalRange"))
		{
			m_richFunctionName.SetWindowTextA(SetDepthOfFieldFocalRange);
		}
		else if (Cmp(szBuffer, "EnableFog"))
		{
			m_richFunctionName.SetWindowTextA(EnableFog);
		}
		else if (Cmp(szBuffer, "DisableFog"))
		{
			m_richFunctionName.SetWindowTextA(DisableFog);
		}
		else if (Cmp(szBuffer, "SetFogColor"))
		{
			m_richFunctionName.SetWindowTextA(SetFogColor);
		}
		else if (Cmp(szBuffer, "SetFogDensity"))
		{
			m_richFunctionName.SetWindowTextA(SetFogDensity);
		}
		else if (Cmp(szBuffer, "EnableBloom"))
		{
			m_richFunctionName.SetWindowTextA(EnableBloom);
		}
		else if (Cmp(szBuffer, "DisableBloom"))
		{
			m_richFunctionName.SetWindowTextA(DisableBloom);
		}
		else if (Cmp(szBuffer, "SetBloomColor"))
		{
			m_richFunctionName.SetWindowTextA(SetBloomColor);
		}
		else if (Cmp(szBuffer, "SetBloomIntensity"))
		{
			m_richFunctionName.SetWindowTextA(SetBloomIntensity);
		}
		else if (Cmp(szBuffer, "EnableDirectionalShadow"))
		{
			m_richFunctionName.SetWindowTextA(EnableDirectionalShadow);
		}
		else if (Cmp(szBuffer, "DisableDirectionalShadow"))
		{
			m_richFunctionName.SetWindowTextA(DisableDirectionalShadow);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowAlgorithm"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowAlgorithm);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowNumberOfSplits"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowNumberOfSplits);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowWeightOfSplits"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowWeightOfSplits);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowNearClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowNearClipPlane);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowFarClipPlane"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowFarClipPlane);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowResolution"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowResolution);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowIntensity"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowIntensity);
		}
		else if (Cmp(szBuffer, "SetDirectionalShadowLight"))
		{
			m_richFunctionName.SetWindowTextA(SetDirectionalShadowLight);
		}

		CInt end = m_richFunctionName.GetWindowTextLengthA();
		m_richFunctionName.SetSel(0, end);
	}
	else
	{
		m_richFunctionName.SetWindowTextA("");
		m_richFunctionName.SetSel(0, 0);
	}

	*pResult = 0;
}


BOOL CScriptEditorAddFunction::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT tempRect;
	m_listFunctions.GetClientRect(&tempRect);
	m_listFunctions.InsertColumn(0, "Functions", LVCFMT_LEFT | LVS_SHOWSELALWAYS, (tempRect.right - tempRect.left) * 90 / 100);
	m_listFunctions.ShowWindow(SW_SHOW);
	m_listFunctions.UpdateWindow();

	InsertItem("PlaySoundLoop");
	InsertItem("PlaySoundOnce");
	InsertItem("PauseSound");
	InsertItem("StopSound");

	InsertItem("BlendCycle");
	InsertItem("ClearCycle");
	InsertItem("ExecuteAction");
	InsertItem("ReverseExecuteAction");
	InsertItem("RemoveAction");
	InsertItem("GetAnimationClipDuration");
	InsertItem("PauseAnimations");

	InsertItem("LoadVScene");
	InsertItem("ExitGame");
	InsertItem("SetCurrentVSceneAsMenu");

	InsertItem("ActivateThirdPersonCamera");
	InsertItem("ActivateFirstPersonCamera");
	InsertItem("ActivateImportedCamera");
	InsertItem("ActivateImportedCameraOfPrefabInstance");
	InsertItem("ActivateEngineCamera");
	InsertItem("SetPhysicsCameraAngle");
	InsertItem("GetPhysicsCameraAngle");
	
	InsertItem("LoadResource");
	InsertItem("DeleteResource");
	InsertItem("DeleteAllResources");
	InsertItem("PlayResourceSoundLoop");
	InsertItem("PlayResourceSoundOnce");
	InsertItem("StopResourceSound");
	InsertItem("PauseResourceSound");
	InsertItem("StopAllResourceSounds");
	InsertItem("ShowCursorIcon");
	InsertItem("HideCursorIcon");

	InsertItem("PrintConsole");

	InsertItem("ShowGUI");
	InsertItem("HideGUI");

	InsertItem("IsKeyDown");

	InsertItem("ShowPrefabInstance");
	InsertItem("HidePrefabInstance");

	InsertItem("SetSelectionDistance");
	InsertItem("GetSelectionDistance");
	InsertItem("SelectPrefabInstances");

	InsertItem("GetScreenWidth");
	InsertItem("GetScreenHeight");
	InsertItem("GetCursorX");
	InsertItem("GetCursorY");
	InsertItem("IsMenuEnabled");
	InsertItem("GetElapsedTime");
	InsertItem("GetPrefabInstanceNameFromActor");

	InsertItem("TranslatePrefabInstance");
	InsertItem("RotatePrefabInstance");
	InsertItem("ScalePrefabInstance");

	InsertItem("GetPrefabInstanceTranslate");
	InsertItem("GetPrefabInstanceRotate");
	InsertItem("GetPrefabInstanceScale");

	InsertItem("GetPrefabInstanceRadius");
	InsertItem("GetDistanceOfPrefabInstanceFromPhysicsCamera");

	InsertItem("EnableDepthOfField");
	InsertItem("DisableDepthOfField");
	InsertItem("SetDepthOfFieldFocalDistance");
	InsertItem("SetDepthOfFieldFocalRange");

	InsertItem("EnableFog");
	InsertItem("DisableFog");
	InsertItem("SetFogColor");
	InsertItem("SetFogDensity");

	InsertItem("EnableBloom");
	InsertItem("DisableBloom");
	InsertItem("SetBloomColor");
	InsertItem("SetBloomIntensity");

	InsertItem("EnableDirectionalShadow");
	InsertItem("DisableDirectionalShadow");
	InsertItem("SetDirectionalShadowAlgorithm");
	InsertItem("SetDirectionalShadowNumberOfSplits");
	InsertItem("SetDirectionalShadowWeightOfSplits");
	InsertItem("SetDirectionalShadowNearClipPlane");
	InsertItem("SetDirectionalShadowFarClipPlane");
	InsertItem("SetDirectionalShadowResolution");
	InsertItem("SetDirectionalShadowIntensity");
	InsertItem("SetDirectionalShadowLight");

	m_listFunctions.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listFunctions.SetSelectionMark(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CVoid CScriptEditorAddFunction::InsertItem(CChar* name)
{
	m_index++;
	int index = m_index;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = index;
	lvItem.iSubItem = 0;
	lvItem.pszText = name;
	m_listFunctions.InsertItem(&lvItem);

	m_listFunctions.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE | LVS_EX_LABELTIP);
	m_listFunctions.EnsureVisible(index, FALSE);
	m_listFunctions.UpdateWindow();
}

void CScriptEditorAddFunction::OnBnClickedCancel()
{
	if (g_multipleView->m_enableTimer)
		g_multipleView->EnableTimer(CTrue);
	CDialog::OnCancel();
}

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
	CChar SetPhysicsCameraTilt[MAX_URI_SIZE];
	CChar SetPhysicsCameraMaxTilt[MAX_URI_SIZE];
	CChar SetPhysicsCameraMinTilt[MAX_URI_SIZE];
	CChar GetPhysicsCameraTilt[MAX_URI_SIZE];
	CChar GetPhysicsCameraMaxTilt[MAX_URI_SIZE];
	CChar GetPhysicsCameraMinTilt[MAX_URI_SIZE];
	CChar SetPhysicsCameraYaw[MAX_URI_SIZE];
	CChar GetPhysicsCameraYaw[MAX_URI_SIZE];

	CChar LoadResource[MAX_URI_SIZE];
	CChar DeleteResource[MAX_URI_SIZE];
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
	CChar GetPrefabInstanceNameFromActor[MAX_URI_SIZE];

	CChar TranslatePrefabInstance[MAX_URI_SIZE];
	CChar RotatePrefabInstance[MAX_URI_SIZE];
	CChar ScalePrefabInstance[MAX_URI_SIZE];

	CChar GetPrefabInstanceTranslate[MAX_URI_SIZE];
	CChar GetPrefabInstanceRotate[MAX_URI_SIZE];
	CChar GetPrefabInstanceScale[MAX_URI_SIZE];

	CChar GetPrefabInstanceRadius[MAX_URI_SIZE];
	CChar GetDistanceOfPrefabInstanceFromPhysicsCamera[MAX_URI_SIZE];

	CChar EnableDepthOfField[MAX_URI_SIZE];
	CChar DisableDepthOfField[MAX_URI_SIZE];
	CChar SetDepthOfFieldFocalDistance[MAX_URI_SIZE];
	CChar SetDepthOfFieldFocalRange[MAX_URI_SIZE];

	CChar EnableFog[MAX_URI_SIZE];
	CChar DisableFog[MAX_URI_SIZE];
	CChar SetFogColor[MAX_URI_SIZE];
	CChar SetFogDensity[MAX_URI_SIZE];

	CChar EnableBloom[MAX_URI_SIZE];
	CChar DisableBloom[MAX_URI_SIZE];
	CChar SetBloomColor[MAX_URI_SIZE];
	CChar SetBloomIntensity[MAX_URI_SIZE];

	CChar EnableDirectionalShadow[MAX_URI_SIZE];
	CChar DisableDirectionalShadow[MAX_URI_SIZE];
	CChar SetDirectionalShadowAlgorithm[MAX_URI_SIZE];
	CChar SetDirectionalShadowNumberOfSplits[MAX_URI_SIZE];
	CChar SetDirectionalShadowWeightOfSplits[MAX_URI_SIZE];
	CChar SetDirectionalShadowNearClipPlane[MAX_URI_SIZE];
	CChar SetDirectionalShadowFarClipPlane[MAX_URI_SIZE];
	CChar SetDirectionalShadowResolution[MAX_URI_SIZE];
	CChar SetDirectionalShadowIntensity[MAX_URI_SIZE];
	CChar SetDirectionalShadowLight[MAX_URI_SIZE];

	CChar SetLightAmbient[MAX_URI_SIZE];
	CChar SetLightDiffuse[MAX_URI_SIZE];
	CChar SetLightSpecular[MAX_URI_SIZE];
	CChar SetLightShininess[MAX_URI_SIZE];

	CChar SetPrefabInstanceAmbient[MAX_URI_SIZE];
	CChar SetPrefabInstanceDiffuse[MAX_URI_SIZE];
	CChar SetPrefabInstanceSpecular[MAX_URI_SIZE];
	CChar SetPrefabInstanceEmission[MAX_URI_SIZE];
	CChar SetPrefabInstanceShininess[MAX_URI_SIZE];
	CChar SetPrefabInstanceTransparency[MAX_URI_SIZE];
	CChar EnablePrefabInstanceMaterial[MAX_URI_SIZE];
	CChar DisablePrefabInstanceMaterial[MAX_URI_SIZE];

	CChar SetPhysicsRestitution[MAX_URI_SIZE];
	CChar SetPhysicsSkinWidth[MAX_URI_SIZE];
	CChar SetPhysicsStaticFriction[MAX_URI_SIZE];
	CChar SetPhysicsDynamicFriction[MAX_URI_SIZE];
	CChar EnablePhysicsGravity[MAX_URI_SIZE];
	CChar DisablePhysicsGravity[MAX_URI_SIZE];
	CChar SetPhysicsGravity[MAX_URI_SIZE];
	CChar EnablePhysicsGroundPlane[MAX_URI_SIZE];
	CChar DisablePhysicsGroundPlane[MAX_URI_SIZE];
	CChar SetPhysicGroundHeight[MAX_URI_SIZE];
	CChar SetDistanceBetweenPhysicsCameraAndCharacterController[MAX_URI_SIZE];
	CChar SetCharacterControllerCapsuleRadius[MAX_URI_SIZE];
	CChar SetCharacterControllerCapsuleHeight[MAX_URI_SIZE];
	CChar SetCharacterControllerForcePower[MAX_URI_SIZE];
	CChar SetCharacterControllerWalkSpeed[MAX_URI_SIZE];
	CChar SetCharacterControllerRunSpeed[MAX_URI_SIZE];
	CChar SetCharacterControllerSkinWidth[MAX_URI_SIZE];
	CChar SetCharacterControllerStepOffset[MAX_URI_SIZE];
	CChar SetCharacterControllerSlopeLimit[MAX_URI_SIZE];
	CChar SetCharacterControllerJumpPower[MAX_URI_SIZE];
	CChar EnableCharacterControllerJump[MAX_URI_SIZE];
	CChar DisableCharacterControllerJump[MAX_URI_SIZE];
	CChar EnablePhysicsDebugMode[MAX_URI_SIZE];
	CChar DisablePhysicsDebugMode[MAX_URI_SIZE];
	CChar SetCharacterControllerPosition[MAX_URI_SIZE];
	CChar GetCharacterControllerPosition[MAX_URI_SIZE];

	CChar SetMaxMultisampling[MAX_URI_SIZE];
	CChar SetMaxAnisotropicFiltering[MAX_URI_SIZE];
	CChar EnableVSync[MAX_URI_SIZE];
	CChar DisableVSync[MAX_URI_SIZE];
	CChar EnableWaterReflection[MAX_URI_SIZE];
	CChar DisableWaterReflection[MAX_URI_SIZE];
	CChar SetScreenResolution[MAX_URI_SIZE];
	CChar SaveGeneralProperties[MAX_URI_SIZE];
	CChar GetMaxMultisampling[MAX_URI_SIZE];
	CChar GetMaxAnisotropicFiltering[MAX_URI_SIZE];
	CChar IsVSyncEnabled[MAX_URI_SIZE];
	CChar IsWaterReflectionEnabled[MAX_URI_SIZE];
	CChar GetScreenResolution[MAX_URI_SIZE];

public:
	afx_msg void OnBnClickedCancel();
};

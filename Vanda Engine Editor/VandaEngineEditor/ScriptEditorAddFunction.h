//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

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

	CChar SetPhysicsDefaultRestitution[MAX_URI_SIZE];
	CChar SetPhysicsDefaultSkinWidth[MAX_URI_SIZE];
	CChar SetPhysicsDefaultStaticFriction[MAX_URI_SIZE];
	CChar SetPhysicsDefaultDynamicFriction[MAX_URI_SIZE];
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

	CChar GetVSceneScriptStringVariable[MAX_URI_SIZE];
	CChar GetVSceneScriptBoolVariable[MAX_URI_SIZE];
	CChar GetVSceneScriptIntVariable[MAX_URI_SIZE];
	CChar GetVSceneScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetVSceneScriptStringVariable[MAX_URI_SIZE];
	CChar SetVSceneScriptBoolVariable[MAX_URI_SIZE];
	CChar SetVSceneScriptIntVariable[MAX_URI_SIZE];
	CChar SetVSceneScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetSkyScriptStringVariable[MAX_URI_SIZE];
	CChar GetSkyScriptBoolVariable[MAX_URI_SIZE];
	CChar GetSkyScriptIntVariable[MAX_URI_SIZE];
	CChar GetSkyScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetSkyScriptStringVariable[MAX_URI_SIZE];
	CChar SetSkyScriptBoolVariable[MAX_URI_SIZE];
	CChar SetSkyScriptIntVariable[MAX_URI_SIZE];
	CChar SetSkyScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetTerrainScriptStringVariable[MAX_URI_SIZE];
	CChar GetTerrainScriptBoolVariable[MAX_URI_SIZE];
	CChar GetTerrainScriptIntVariable[MAX_URI_SIZE];
	CChar GetTerrainScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetTerrainScriptStringVariable[MAX_URI_SIZE];
	CChar SetTerrainScriptBoolVariable[MAX_URI_SIZE];
	CChar SetTerrainScriptIntVariable[MAX_URI_SIZE];
	CChar SetTerrainScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetPrefabInstanceScriptStringVariable[MAX_URI_SIZE];
	CChar GetPrefabInstanceScriptBoolVariable[MAX_URI_SIZE];
	CChar GetPrefabInstanceScriptIntVariable[MAX_URI_SIZE];
	CChar GetPrefabInstanceScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetPrefabInstanceScriptStringVariable[MAX_URI_SIZE];
	CChar SetPrefabInstanceScriptBoolVariable[MAX_URI_SIZE];
	CChar SetPrefabInstanceScriptIntVariable[MAX_URI_SIZE];
	CChar SetPrefabInstanceScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetGUIButtonScriptStringVariable[MAX_URI_SIZE];
	CChar GetGUIButtonScriptBoolVariable[MAX_URI_SIZE];
	CChar GetGUIButtonScriptIntVariable[MAX_URI_SIZE];
	CChar GetGUIButtonScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetGUIButtonScriptStringVariable[MAX_URI_SIZE];
	CChar SetGUIButtonScriptBoolVariable[MAX_URI_SIZE];
	CChar SetGUIButtonScriptIntVariable[MAX_URI_SIZE];
	CChar SetGUIButtonScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetTriggerScriptStringVariable[MAX_URI_SIZE];
	CChar GetTriggerScriptBoolVariable[MAX_URI_SIZE];
	CChar GetTriggerScriptIntVariable[MAX_URI_SIZE];
	CChar GetTriggerScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetTriggerScriptStringVariable[MAX_URI_SIZE];
	CChar SetTriggerScriptBoolVariable[MAX_URI_SIZE];
	CChar SetTriggerScriptIntVariable[MAX_URI_SIZE];
	CChar SetTriggerScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetWaterScriptStringVariable[MAX_URI_SIZE];
	CChar GetWaterScriptBoolVariable[MAX_URI_SIZE];
	CChar GetWaterScriptIntVariable[MAX_URI_SIZE];
	CChar GetWaterScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetWaterScriptStringVariable[MAX_URI_SIZE];
	CChar SetWaterScriptBoolVariable[MAX_URI_SIZE];
	CChar SetWaterScriptIntVariable[MAX_URI_SIZE];
	CChar SetWaterScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetVideoScriptStringVariable[MAX_URI_SIZE];
	CChar GetVideoScriptBoolVariable[MAX_URI_SIZE];
	CChar GetVideoScriptIntVariable[MAX_URI_SIZE];
	CChar GetVideoScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetVideoScriptStringVariable[MAX_URI_SIZE];
	CChar SetVideoScriptBoolVariable[MAX_URI_SIZE];
	CChar SetVideoScriptIntVariable[MAX_URI_SIZE];
	CChar SetVideoScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetAmbientSoundScriptStringVariable[MAX_URI_SIZE];
	CChar GetAmbientSoundScriptBoolVariable[MAX_URI_SIZE];
	CChar GetAmbientSoundScriptIntVariable[MAX_URI_SIZE];
	CChar GetAmbientSoundScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetAmbientSoundScriptStringVariable[MAX_URI_SIZE];
	CChar SetAmbientSoundScriptBoolVariable[MAX_URI_SIZE];
	CChar SetAmbientSoundScriptIntVariable[MAX_URI_SIZE];
	CChar SetAmbientSoundScriptDoubleVariable[MAX_URI_SIZE];

	CChar Get3DSoundScriptStringVariable[MAX_URI_SIZE];
	CChar Get3DSoundScriptBoolVariable[MAX_URI_SIZE];
	CChar Get3DSoundScriptIntVariable[MAX_URI_SIZE];
	CChar Get3DSoundScriptDoubleVariable[MAX_URI_SIZE];
	CChar Set3DSoundScriptStringVariable[MAX_URI_SIZE];
	CChar Set3DSoundScriptBoolVariable[MAX_URI_SIZE];
	CChar Set3DSoundScriptIntVariable[MAX_URI_SIZE];
	CChar Set3DSoundScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetLightScriptStringVariable[MAX_URI_SIZE];
	CChar GetLightScriptBoolVariable[MAX_URI_SIZE];
	CChar GetLightScriptIntVariable[MAX_URI_SIZE];
	CChar GetLightScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetLightScriptStringVariable[MAX_URI_SIZE];
	CChar SetLightScriptBoolVariable[MAX_URI_SIZE];
	CChar SetLightScriptIntVariable[MAX_URI_SIZE];
	CChar SetLightScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetCameraScriptStringVariable[MAX_URI_SIZE];
	CChar GetCameraScriptBoolVariable[MAX_URI_SIZE];
	CChar GetCameraScriptIntVariable[MAX_URI_SIZE];
	CChar GetCameraScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetCameraScriptStringVariable[MAX_URI_SIZE];
	CChar SetCameraScriptBoolVariable[MAX_URI_SIZE];
	CChar SetCameraScriptIntVariable[MAX_URI_SIZE];
	CChar SetCameraScriptDoubleVariable[MAX_URI_SIZE];

	CChar GetMainCharacterScriptStringVariable[MAX_URI_SIZE];
	CChar GetMainCharacterScriptBoolVariable[MAX_URI_SIZE];
	CChar GetMainCharacterScriptIntVariable[MAX_URI_SIZE];
	CChar GetMainCharacterScriptDoubleVariable[MAX_URI_SIZE];
	CChar SetMainCharacterScriptStringVariable[MAX_URI_SIZE];
	CChar SetMainCharacterScriptBoolVariable[MAX_URI_SIZE];
	CChar SetMainCharacterScriptIntVariable[MAX_URI_SIZE];
	CChar SetMainCharacterScriptDoubleVariable[MAX_URI_SIZE];

	CChar ShowGUIButton[MAX_URI_SIZE];
	CChar HideGUIButton[MAX_URI_SIZE];
	CChar ShowGUIImage[MAX_URI_SIZE];
	CChar HideGUIImage[MAX_URI_SIZE];
	CChar ShowGUIText[MAX_URI_SIZE];
	CChar HideGUIText[MAX_URI_SIZE];
	CChar ScaleGUIButton[MAX_URI_SIZE];
	CChar ScaleGUIImage[MAX_URI_SIZE];

	CChar SetGUIButtonPosition[MAX_URI_SIZE];
	CChar SetGUIImagePosition[MAX_URI_SIZE];
	CChar SetGUITextPosition[MAX_URI_SIZE];
	CChar GetGUIButtonPosition[MAX_URI_SIZE];
	CChar GetGUIImagePosition[MAX_URI_SIZE];
	CChar GetGUITextPosition[MAX_URI_SIZE];

	CChar SetGUIPosition[MAX_URI_SIZE];
	CChar GetGUIPosition[MAX_URI_SIZE];

	CChar AddForceToCharacterController[MAX_URI_SIZE];
	CChar AddForceToPrefabInstance[MAX_URI_SIZE];
	CChar AddTorqueToPrefabInstance[MAX_URI_SIZE];

	CChar GetPhysicsActorGroup[MAX_URI_SIZE];
	CChar SetPhysicsCollisionFlags[MAX_URI_SIZE];

	CChar GeneratePrefabInstance[MAX_URI_SIZE];
	CChar DeletePrefabInstance[MAX_URI_SIZE];

	CChar AttachPrefabInstanceToWater[MAX_URI_SIZE];
	CChar DetachPrefabInstanceFromWater[MAX_URI_SIZE];

	CChar SetSoundVolume[MAX_URI_SIZE];
	CChar SetSoundPitch[MAX_URI_SIZE];
	CChar SetSoundPlay[MAX_URI_SIZE];
	CChar SetSoundLoop[MAX_URI_SIZE];
	CChar SetSoundPosition[MAX_URI_SIZE];
	CChar SetSoundRollOff[MAX_URI_SIZE];
	CChar SetSoundReferenceDistance[MAX_URI_SIZE];
	CChar SetSoundMaxDistance[MAX_URI_SIZE];

	CChar GetSoundVolume[MAX_URI_SIZE];
	CChar GetSoundPitch[MAX_URI_SIZE];
	CChar GetSoundPlay[MAX_URI_SIZE];
	CChar GetSoundLoop[MAX_URI_SIZE];
	CChar GetSoundPosition[MAX_URI_SIZE];
	CChar GetSoundRollOff[MAX_URI_SIZE];
	CChar GetSoundReferenceDistance[MAX_URI_SIZE];
	CChar GetSoundMaxDistance[MAX_URI_SIZE];

	CChar SetGlobalSoundVolume[MAX_URI_SIZE];
	CChar GetGlobalSoundVolume[MAX_URI_SIZE];

	CImageList m_image;

public:
	afx_msg void OnBnClickedCancel();
};

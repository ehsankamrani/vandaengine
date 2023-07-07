//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once
#include "..\PhysXEngine\Nx.h"
#include "..\InputEngine\input.h"
#include "..\timerEngine\timer.h"
#include "light.h"
#include "bloom.h"
#include "ShadowMap.h"
#include "camera.h"
#include "sky.h"
#include "dof.h"
#include "..\AudioEngine/openal.h"
#include "..\AudioEngine/OpenALSystem.h"
#include "..\AudioEngine/ambientSound.h"
#include "..\VideoEngine/Video.h"
#include "..\GraphicsEngine/SimpleFont.h"
#include "../MouseTranslationController.h"
#include "GUIEngine/GUI.h"
#include "..\\Icon.h"
#include "Defines.h"

// CMultipleWindows

struct CUpdateCamera
{
	CCamera *m_cameraManager; //Default camera of the scene, I don't use the external cameras of the COLLADA file

	NxVec3 m_perspectiveCameraPos;
	NxVec3 m_perspectiveCameraPosOfPreviousFrame;
	NxVec3 m_perspectiveCameraDir;
	NxVec3 m_perspectiveCharacterPos; //equals AtPos
	NxVec3 m_perspectiveCharacterPosOfPreviousFrame;
	CFloat m_perspectiveCameraYaw;
	CFloat m_perspectiveCameraPitch;
	CFloat m_perspectiveCameraTilt; //Currently m_tilt must  be passed directly to UpdateCameraPosDir(), I should find a way to calculate the tilt inside the GetCameraAndCharaterPosition().
	CFloat m_perspectiveCurrentCameraTilt;
	CFloat m_perspectiveCameraMinTilt;
	CFloat m_perspectiveCameraMaxTilt;
	CDouble m_perspectiveCameraZoom;
	CDouble m_perspectiveCurrentCameraZoom;
	CFloat m_cameraSpeed;

	//camera properties of the Lower right viewport 
	CFloat m_lowerRightMoveHorizantal;
	CFloat m_lowerRightMoveVertical;
	CFloat m_lowerRightZoom;

	//camera properties of the upper right viewport 
	CFloat m_upperRightMoveHorizantal;
	CFloat m_upperRightMoveVertical;
	CFloat m_upperRightZoom;

	//camera properties of the upper left viewport 
	CFloat m_upperLeftMoveHorizantal;
	CFloat m_upperLeftMoveVertical;
	CFloat m_upperLeftZoom;

	//Appropriate camera is activated based on the position of the mouse with left or right mouse button clicks
	//If one camera is activated, others are deactivated
	CBool m_activatePerspectiveCamera;
	CBool m_activateLowerRightCamera;
	CBool m_activateUpperLeftCamera;
	CBool m_activateUpperRightCamera;

	CUpdateCamera()
	{
		m_cameraManager = new CCamera();

		m_perspectiveCameraYaw = 0.0f;
		m_perspectiveCameraPitch = 0.0f;
		m_perspectiveCameraTilt = 0.0f;
		m_perspectiveCurrentCameraTilt = 0.0f;
		m_perspectiveCameraMinTilt = -0.5f;
		m_perspectiveCameraMaxTilt = 0.5f;
		m_perspectiveCameraZoom = 0.0;
		m_perspectiveCurrentCameraZoom = 0.0f;

		m_lowerRightMoveHorizantal = 0.0f;
		m_lowerRightMoveVertical = 0.0f;
		m_lowerRightZoom = 0.03f;

		m_upperRightMoveHorizantal = 0.0f;
		m_upperRightMoveVertical = 0.0f;
		m_upperRightZoom = 0.03f;

		m_upperLeftMoveHorizantal = 0.0f;
		m_upperLeftMoveVertical = 0.0f;
		m_upperLeftZoom = 0.03f;

		m_activatePerspectiveCamera = CFalse;
		m_activateLowerRightCamera = CFalse;
		m_activateUpperLeftCamera = CFalse;
		m_activateUpperRightCamera = CFalse;
		m_cameraSpeed = 5.0f;

	}
	~CUpdateCamera()
	{
		CDelete(m_cameraManager);
	}

	CVoid Reset()
	{
		m_perspectiveCameraYaw = 0.0f;
		m_perspectiveCameraPitch = 0.0f;
		m_perspectiveCameraTilt = 0.0f;
		m_perspectiveCurrentCameraTilt = 0.0f;
		m_perspectiveCameraMinTilt = -0.5f;
		m_perspectiveCameraMaxTilt = 0.5f;
		m_perspectiveCameraZoom = 0.0;
		m_perspectiveCurrentCameraZoom = 0.0f;

		m_lowerRightMoveHorizantal = 0.0f;
		m_lowerRightMoveVertical = 0.0f;
		m_lowerRightZoom = 0.03f;

		m_upperRightMoveHorizantal = 0.0f;
		m_upperRightMoveVertical = 0.0f;
		m_upperRightZoom = 0.03f;

		m_upperLeftMoveHorizantal = 0.0f;
		m_upperLeftMoveVertical = 0.0f;
		m_upperLeftZoom = 0.03f;

		m_activatePerspectiveCamera = CFalse;
		m_activateLowerRightCamera = CFalse;
		m_activateUpperLeftCamera = CFalse;
		m_activateUpperRightCamera = CFalse;
		m_cameraSpeed = 5.0f;

	}

};

struct CPhysXVariables
{
	CBool m_applyDirectionalForce;
	NxVec3 m_forceDirectionVector;
	CFloat m_forceSpeedValue;
	CFloat m_forceDecreaseValue;

	CPhysXVariables()
	{
		m_applyDirectionalForce = CFalse;
		m_forceDecreaseValue = 0.0f;
		m_forceSpeedValue = 0.0f;
		m_forceDirectionVector = NxVec3( 0.0f, 0.0f, 0.0f );
	}
	~CPhysXVariables()
	{
	}
};


class CMultipleWindows : public CWnd
{
	DECLARE_DYNAMIC(CMultipleWindows)

public:
	CMultipleWindows();
	virtual ~CMultipleWindows();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg CInt OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg CVoid OnSize(UINT nType, CInt cx, CInt cy);
	afx_msg CVoid OnDestroy();
	afx_msg CVoid OnPaint();
	afx_msg CVoid OnMouseMove(UINT nFlags, CPoint point);
	afx_msg CVoid OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg CVoid OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg CVoid OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg CVoid OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg CVoid OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg CVoid OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg CVoid OnTimer(UINT_PTR nIDEvent);

	CVoid ActivateCamera( CPoint point );
	CVoid DrawGrid( CVoid );
	CVoid RenderWindow();
	CVoid DrawGUI();
	CVoid DrawGUIMode();
	CVoid DrawUpperLeft();
	CVoid DrawUpperRight();
	CVoid DrawLowerRight();
	CVoid DrawPerspective();
	CVoid CalculateDistances(CBool force = CFalse);
	CVoid ResetData();
	CVoid DrawJustPerspectiveBorders();
	CVoid DrawBordersAndUI();
	CVoid RenderTerrain(CBool useFBO = CTrue);
	CVoid RenderQueries(CBool init = CFalse);
	CVoid RenderBakedOctree3DModels();
	CVoid Render3DModels(CBool sceneManager, CChar* parentTreeNameOfGeometries, CBool checkVisibility = CFalse, CBool drawGeometry = CTrue );
	CVoid Render3DModelsForWater(CWater* water, CBool sceneManager, CChar* parentTreeNameOfGeometries);
	CVoid Render3DAnimatedModels(CBool sceneManager);
	CVoid Render3DAnimatedModelsForWater(CWater* water, CBool sceneManager);
	CVoid Render3DModelsControlledByPhysX(CBool sceneManager = CTrue);
	CVoid Render3DModelsControlledByPhysXForWater(CWater* water, CBool sceneManager = CTrue);
	CVoid GenerateMenuCursorTexture(char* fileName);
	CVoid DeleteMenuCursorTexture();
	CVoid Render3DTransparentModels(CBool renderTop = CTrue);
	CVoid Render3DTransparentModelsForWater(CWater* water);
	CVoid RenderCharacter(CBool sceneManager);
	CVoid ManageLODs();
	CVoid Draw3DObjects();
	CVoid SetDefaultLight();
	CVoid UpdatePrefabInstanceBB();
	CVoid UpdateAnimations(CBool init = CFalse);
	CVoid UpdateDynamicPhysicsObjects();
	CVoid ResetPhysXCounts();
	CBool InitAll();
	CBool GenerateDefaultTextures();
	CUInt GetSelectedObject(CBool renderArrowOnly = CFalse);
	CVoid SetElapsedTimeFromBeginning();
	CVoid EnableTimer( CBool enable );
	CVoid ApplyForce( /*NxVec3 forceDirection, */CInt moveDirection, CFloat elapsedTime );
	CBool ManageCharacterBlends(CChar* animationType, CChar* IdleAnimationName = NULL);
	CBool IsJumping(CBool &isInList);
	CBool GetJumpCurrentEndDuration(CFloat& duration);
	CVoid SetSwapBuffers(CBool set) { m_swapBuffers = set; }
	CBool GetSwapBuffers() { return m_swapBuffers; }
	CFloat GetCursorX();
	CFloat GetCursorY();
	CFloat elapsedTime;
	CULong m_timerCounter;
	CFloat m_totalElapsedTime;
	CBool m_bQuery;
	CBool m_renderQuery;
	std::vector<CFloat> distance_vector;
	std::vector<CInstancePrefab*> sorted_prefabs;
	CBool m_calculateDistance;
	CImage* m_menuCursorImg;
	CChar m_strMenuCursorImg[MAX_NAME_SIZE];
	CImage* GetMenuCursorImage() { return m_menuCursorImg; }
	CUInt m_mFboID; //multisample FBO 
	CUInt m_rbDepthID; //attach a render buffer to the depth buffer of multisample FBO
	CUInt m_rbColorID[eGBUFFER_NUM_TEXTURES]; //attach a render buffer to the color buffers of multisample FBO

	CUInt m_fboID; //each texture has its own FBO ID
	CUInt m_textureTarget[eGBUFFER_NUM_TEXTURES];
	CUInt m_rbDepthID2; //It's used when multisampling is disabled

	CBool InitFBOs( CInt channels, CInt type );
	CVoid SetInstanceCamera( CInstanceCamera * inst, CFloat sWidth, CFloat sHeight, CFloat fov, CFloat zNear, CFloat zFar );
	CDOF m_dof;
	CBool m_lMouseDown, m_rMouseDown, m_mMouseDown, m_mouseMove;
	CBool m_selectObject;
	CMouseTranslationController* m_translationController;
	CPoint m_mousePosition; //Mouse position when the user clicks left mouse button
	CPoint m_mouseOldPosition;
	CPoint m_translateMousePosition;
	CBool m_loadData; //load initial data?
	CUInt m_selectedGUIIndex;
	CUInt m_previousSelectedGUIIndex;
	//shadow
	float cam_proj[16];
	float cam_modelview[16];
	float cam_inverse_modelview[16];
	float cam_pos[3];
	float cam_dir[3];
	float far_bound[MAX_SPLITS];
	CVec3f free_dae_cam_pos, free_dae_cam_at;

	//Audio variables 
	ALfloat m_ambientSourcePos[3];
	// Velocity of the source sound.
	ALfloat m_ambientSourceVel[3];
	// Position of the listener.
	ALfloat m_listenerPos[3];
	// Velocity of the listener.
	ALfloat m_listenerVel[3];
	// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
	ALfloat m_listenerOri[6];
	COpenALSystem* m_soundSystem;

	CPhysXVariables m_physXVariables;
	CNovodex* m_nx;
	CBool m_enableTimer;
	CSimpleFont m_simpleFont;
	CSimpleFont m_simpleFont2;
	CInputSystem* m_inputSystem;

	// Should we use multisampling?
	CBool m_multiSample;
	CInt m_numSamples;
	// To hold the pixel format of an OpenGL window in which doesn't use multisampling
	HGLRC	m_hRC;
	CDC*	m_pDC;
	HCURSOR m_currentCursor;
	
	CInt m_width, m_height;
	CInt m_grid;
	//After the user left clickes, we must check to see if there are any movements until he releases the mouse button
	//If there were no movement we send the selected name( If available )to the global selected name( defined  at stdafx.h )
	CBool m_tempMovement; 
	//It's used to hold the name until the user releases the button
	CUInt m_tempSelectedName;
	CUInt m_lastSelectedName;

	CBool m_lockInput;
	CBool m_lockDefaultFreeCamera;
	CBool m_lockEscape;
	CBool m_loadScene;
	CBool m_notFocus;
	CBool m_lockCharacterController;
	CBool m_updatePhysX;
	CBool m_isPlayingGame;
	CCameraType m_cameraType;
	CCameraType m_cameraTypeOfPreviousFrame;

	//this variable is used for bloom effect
	CBloom* m_bloom;
	CShadowMap* m_dynamicShadowMap;
	
	CIcon* m_cursorIcon;

	GLuint *ptr, minZ, selectedName, Buffer[MAX_NAME_SIZE], m_selectedPrefabName;//selection

	GLuint *m_guiPtr, m_guiMinZ, m_guiSelectedName, m_guiBuffer[MAX_NAME_SIZE];//gui selection

	CVoid InitObjectSelection();
	CVoid FinishObjectSelection();
	
	CVoid EnableIdleAnimations();

	CFloat m_previousCharacterRotation;
	CBool m_characterRotationTransition;
	CBool m_initError;

	CFloat m_forceSpeed;
	NxVec3 m_forceDirection;
	CFloat m_forceDecreaseValue;

	CBool m_renderBlending;
	CBool m_checkBlending;
	CBool m_pushTransparentGeometry;

	CVoid AddTransparentGeometry(CTransparentGeometry geometry) { m_transparentGeometries.push_back(geometry); }
	CVoid RemoveTransparentGeometries()
	{ 
		m_transparentGeometries.clear();
	}
	std::vector<CTransparentGeometry> m_transparentGeometries;

	CBool m_renderArrow;

	CVoid GetMouseMovement();

	CVoid PauseSounds();
	CVoid ResumeSounds();

	CVoid PauseGame();
	CVoid ResumeGame();

	CVoid PauseAllScriptUpdateEvents();
	CVoid ResumeAllScriptUpdateEvents();

	CVoid SetFixedTiming(CBool set) { m_fixedTiming = set; }
private:
	CChar m_previousCharacterAnimationType[MAX_NAME_SIZE];
	CBool m_playGameMode;

	CChar m_screenshotPath[MAX_URI_SIZE];
	CBool m_saveScreenshot;
	CBool m_swapBuffers;
	CFloat m_fSelectionDistance;
	CBool m_bSelectionDistance;
	CChar m_selectedPrefabInstanceName[MAX_NAME_SIZE];
	std::vector<CTransparentGeometry> m_sortedTransparentGoemetries;
	//mouse movements
	CInt m_dx, m_dy;
	CInt m_prev_dx, m_prev_dy;
	POINT m_point;
	CGUI* m_selectedGUI;
	CBool m_renderVideo;
	CBool m_updateScript;
	CBool m_fixedTiming;
public:
	CVoid ProcessInputs();
	CVoid InitDynamicShadowMap(CVec3f lightPos, CVec3f atPos );
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	CVoid SetInitError(CBool set) { m_initError = set; }
	CBool GetInitError() { return m_initError; }
	CBool IsPlayGameMode() { return m_playGameMode; }
	CVoid SetPlayGameMode(CBool set) { m_playGameMode = set; }
	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }
	CIcon* GetCursorIcon() { return m_cursorIcon; }
	CVoid InitGUISelection();
	CUInt GetSelectedGUI();
	CVoid FinishGUISelection();

	CVoid SetSaveScreenshot(CBool set) { m_saveScreenshot = set; }
	CBool GetSaveScreenshot() { return m_saveScreenshot; }

	CVoid SetScreenshotPath(CChar* path) { Cpy(m_screenshotPath, path); }
	CChar* GetScreenshotPath() { return m_screenshotPath; }

	CFloat GetElapsedTime() { return elapsedTime; }

	CFloat m_idleCounter;
	static CBool firstIdle;
	static CChar currentIdleName[MAX_NAME_SIZE];
	CChar* GetPreviousCharacterAnimationType() { return m_previousCharacterAnimationType; }
	CTimer timer;

	CVoid SetSelectionDistance(CFloat distance) { m_fSelectionDistance = distance;  m_bSelectionDistance = CTrue; }
	CFloat GetSelectionDistance() { return m_fSelectionDistance; }
	CChar* SelectPrefabInstances(CDouble mouseXPos, CDouble mouseYPos, CDouble selectionWidth, CDouble selectionHeight);
	CVoid InitPrefabSelection(CDouble mouseXPos, CDouble mouseYPos, CDouble selectionWidth, CDouble selectionHeight);
	CVoid FinishPrefabSelection();

	//This function is called inside OnBnClickedBtnDeactivatePlayMode()
	CVoid GeneratePrefabInstance(CPrefab* prefab, CChar* prefabInstanceName);
	CVoid DeletePrefabInstance(CChar* prefabInstanceName);
	CVoid UpdateCharacterTransformations();
	CVoid UpdatePrefabInstanceTransformations();
	CVoid CalculateAndSort3DTransparentModelDistances();
	CVoid RenderWaters();
	CBool DoesGeometryInstanceIntersectsWater(CInstanceGeometry* geometryInstance, CWater* water);

	CVoid DrawLightIconArrows();
	///////////
	CBool m_showMenuCursor;
	CBool m_pauseMainCharacterAnimations;
	CBool m_pauseAllAnimationsOfPrefabInstances;
	CBool m_pausePhysics;
	CBool m_pauseAllWaterAnimations;
	CBool m_pauseAllUpdateEvents;
	CBool m_pauseAllSounds;
};

extern CInt g_numLights;
extern CInt g_totalLights;

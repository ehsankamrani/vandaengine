//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

/******************************************************
***************VandaEngine MAIN FILE***************
******************************************************/

/*******************************************************
*******************MAIN INCLUDES************************
*******************************************************/
#define NOMINMAX
#include <windows.h>
#include "stdafx.h"
#include "VandaEngineWin32.h"
#include "main.h"
#include "inputEngine/input.h"
#include "timerEngine/timer.h"
#include "graphicsEngine/render.h"
#include "graphicsEngine/image.h"
#include "graphicsEngine/texture.h"
#include "main.h"

class COpenALSoundBuffer;
//Edition.MaxVersion.MinVersion.BugFixes;
CInt g_version = 295;
CChar g_edition[MAX_NAME_SIZE];
CScene* g_currentScene = NULL;
CInstancePrefab* g_currentInstancePrefab = NULL;
CWater* g_currentWater = NULL;
CLight* g_currentLight = NULL;
C3DSound* g_current3DSound = NULL;
CAmbientSound* g_currentAmbientSound = NULL;
CTrigger* g_currentTrigger = NULL;
CInstanceCamera* g_currentEngineCamera = NULL;
CVideo* g_currentVideo = NULL;

CMainCharacter* g_mainCharacter;
CChar g_currentVSceneName[MAX_NAME_SIZE]; //save functions
CChar g_currentPrefabPackagePath[MAX_NAME_SIZE];
CChar g_currentPrefabName[MAX_NAME_SIZE];
CChar g_currentVSceneNameViaScript[MAX_NAME_SIZE];
CChar g_currentPrefabAndSceneName[MAX_NAME_SIZE]; //save functions
CChar g_currentZipFileName[MAX_NAME_SIZE];
CChar g_currentInstancePrefabName[MAX_NAME_SIZE];
CBool g_loadSceneViaScript = CFalse;
CChar g_currentPassword[MAX_NAME_SIZE];
CWindow g_window;
CRender g_render; //extern
std::vector<CScene*> g_scene;
std::vector<CPrefab*> g_prefab;
std::vector<CPrefab*> g_resourcePrefab;
std::vector<CGeometry *> g_geometries;
std::vector<CInstancePrefab*>g_instancePrefab;
CLODProperties g_instancePrefabLODPercent;
CPrefabProperties g_prefabProperties;
CCameraProperties g_cameraProperties;

std::vector<CGUIButton*> g_guiButtons;
std::vector<CGUIImage*> g_guiImages;
std::vector<CGUIText*> g_guiTexts;
std::vector<CGUI*> g_guis;

std::vector<CInstanceLight*> g_engineLights;
std::vector<CTrigger*> g_triggers;
std::vector<CWater*> g_engineWaters;
std::vector<CImage*> g_images;
std::vector<CImage*>g_waterImages;
std::vector<C3DSound*>g_engine3DSounds;
std::vector<CAmbientSound*> g_engineAmbientSounds;
std::vector<CVideo*> g_engineVideos;
CBool g_useOldRenderingStyle = CFalse;
CUpdateCamera *g_camera = NULL;
CVSceneScript* g_VSceneScript = NULL;
CSkyDome *g_skyDome = NULL;
CTerrain *g_terrain = NULL;
CBool g_renderShadow = CFalse;
CFloat g_maxInstancePrefabRadius = -1.0f;
CBool g_clickedOpen = CFalse;
CBool g_clickedNew = CFalse;
CCameraType g_currentCameraType = eCAMERA_PHYSX;
CBool g_renderForWater = CFalse;
CBloom* g_bloom = NULL;
COctree* g_octree = NULL;
CBool g_updateOctree = CTrue;
CMain* g_main = NULL;
CBool g_useGlobalAmbientColor;
CColor4f g_globalAmbientColor;
COpenALSystem* g_soundSystem = NULL;
std::vector<CInstanceCamera*> g_importedCameraInstances;
std::vector<CInstanceCamera*> g_engineCameraInstances;
std::vector<CResourceFile*> g_resourceFiles;
GLuint g_shaderType;
//shadow
CShadowMap* g_dynamicShadowMap = NULL;
/////////
CInt g_numLights = 0;
CInt g_totalLights = 0;
CFloat g_elapsedTime;

bool g_fullScreen = true;             //Use Fullscreen
int g_width;                   //default g_width of our screen
int g_height;                   //default Height of our screen
int g_bits = 32;                      //Color Bits
bool g_renderScene = false;
bool g_loading = CTrue;
CInputSystem g_input;
CTimer* g_timer = NULL;
CNovodex* g_nx = NULL;
CFont* g_font = NULL;

CImage* m_loadingImg;

CChar m_strLoadingImg[MAX_NAME_SIZE];

CDatabaseVariables g_databaseVariables;
CShadowProperties g_shadowProperties;
CPhysXProperties g_physXProperties;
CPhysXCollisionFlags g_physXCollisionFlags;
CDOFProperties g_dofProperties;
CLightProperties g_lightProperties;
CCurrentVSceneProperties g_currentVSceneProperties;
CCharacterBlendingProperties g_characterBlendingProperties;
CFogProperties g_fogProperties;
CFogProperties g_waterFogProperties;
CBloomProperties g_bloomProperties;
CPathProperties g_pathProperties;
CExtraTexturesNamingConventions g_extraTexturesNamingConventions;
COptions g_options;
CVec4f g_defaultDirectionalLight;
CInstanceLight* g_currentInstanceLight = NULL;
CBool g_firstPass;
CInt g_sceneManagerObjectsPerSplit = 15;

HWND g_hwnd = NULL;
HINSTANCE g_instance = NULL;
bool g_done;       // flag saying when our app is complete 
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

void GenerateLoadingTexture(char* fileName)
{
	m_loadingImg = CNew(CImage);

	Cpy(m_strLoadingImg, fileName);

	if (!CTexture::LoadTexture(m_loadingImg, m_strLoadingImg, NULL, CTrue))
		MessageBox(NULL, _T("GenerateLoadingTexture>Couldn't load the texture"), _T("VandaEngine Error"), MB_OK);

	m_loadingImg->SetFileName(GetAfterPath(m_strLoadingImg));
}

void DeleteLoadingTexture()
{
	CDelete(m_loadingImg);
}

void ShowLoadingScene(CChar* message)
{
	glViewport(0, g_window.GetPadding(), g_width, g_height);
	glPushAttrib(GL_ENABLE_BIT);
	glUseProgram(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, g_width, 0, g_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_loadingImg->GetId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(g_width, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(g_width, g_height);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, g_height);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glPopAttrib();

	if (message)
	{
		g_font->StartRendering();
		g_font->Print(message, 10.0f, 40.0, 0.0f, 0.85f, 0.67f, 0.0f);
		g_font->EndRendering();

		glFlush();
		SwapBuffers(g_window.m_windowGL.hDC);
	}
}

GLvoid CleanUp()
{
	g_main->Reset();

	g_main->Release();

	CDelete(g_main);

	DeleteLoadingTexture();

}

int Initialize()
{
	g_main = CNew(CMain);
	if (!g_main->Init())
		return 0;
	return 1;
}

bool Render()
{
	static int loop = 0;
	if (g_loading)
	{
		static int load_fix = 0;
		static CChar temp[MAX_NAME_SIZE];

		if (load_fix == 0)
		{
			CChar afterPath[MAX_NAME_SIZE];
			CChar finalPath[MAX_NAME_SIZE];

			if (!g_render.ParsePublishFile("Assets/Save/publish.txt"))
			{
				MessageBox(NULL, _T("Couldn't load the publish file\nLoading 'Assets/save/VandaEngineDemo.vin'..."), _T("VandaEngineError"), MB_OK | MB_ICONERROR);
				Cpy(temp, "Assets/Save/VandaEngineDemo.vin");
			}
			else
			{
				Cpy(finalPath, g_render.m_savedFile.c_str());
				CChar* afterPathTemp = GetAfterPath(finalPath);
				Cpy(afterPath, afterPathTemp);
				Append(afterPath, ".vin");
				Append(finalPath, "/");
				Append(finalPath, afterPath);
				Cpy(temp, finalPath);
			}
			//Find the name of loading banner
			CChar currentSceneNameWithoutDot[MAX_NAME_SIZE];
			Cpy(currentSceneNameWithoutDot, afterPath);
			GetWithoutDot(currentSceneNameWithoutDot);

			CChar bannerPath[MAX_NAME_SIZE];
			sprintf(bannerPath, "%s%s%s", "assets/vscenes/", currentSceneNameWithoutDot, "/Banner/");

			HANDLE hFind;
			WIN32_FIND_DATAA data;
			CChar bannerTempPath[MAX_NAME_SIZE];
			sprintf(bannerTempPath, "%s%s", bannerPath, "*.*");
			hFind = FindFirstFileA(bannerTempPath, &data);
			CChar bannerNameAndPath[MAX_NAME_SIZE];
			do
			{
				sprintf(bannerNameAndPath, "%s%s", bannerPath, data.cFileName);
				if (!Cmp(data.cFileName, ".") && !Cmp(data.cFileName, ".."))
					break;
			} while (FindNextFileA(hFind, &data));
			FindClose(hFind);
			GenerateLoadingTexture(bannerNameAndPath);
			load_fix++;
		}
		if (load_fix < 5)
			ShowLoadingScene();
		else
		{
			if (loop == 0)
			{
				g_main->m_loadScene = CTrue; //lock input
				g_main->m_prevLoadScene = CTrue;
				if (!g_main->Load(temp))
					return CFalse;
				DeleteLoadingTexture();
				g_main->ResetTimer();

				g_main->m_tempPauseGame = g_currentVSceneProperties.m_pauseGame;
				g_main->m_tempPausePhysics = g_main->m_pausePhysics;

				g_currentVSceneProperties.m_pauseGame = CFalse;
				g_main->m_pausePhysics = CFalse;
			}
			if (loop < 5)
			{
				g_main->m_renderVideoEnabled = CFalse;
				g_main->Render();
				gPhysXscene->setGravity(NxVec3(0.0, 0.0, 0.0));
				g_nx->gControllers->reportSceneChanged();
				g_main->ApplyForce(IDLE, 1.f / 60.f);

				g_main->ResetPhysXCounts();
				loop++;
				return CTrue;
			}
			else
			{
				g_loading = CFalse;
				gPhysXscene->setGravity(NxVec3(g_nx->m_defaultGravity.x, g_nx->m_defaultGravity.y, g_nx->m_defaultGravity.z));
				g_nx->gControllers->reportSceneChanged();

				g_main->m_loadScene = CFalse; //unlock input
				g_main->m_renderVideoEnabled = CTrue;

				g_currentVSceneProperties.m_pauseGame = g_main->m_tempPauseGame;
				g_main->m_pausePhysics = g_main->m_tempPausePhysics;

				g_main->ResetPhysXCounts();

				loop = 0;
				return CTrue;
			}
		}
		load_fix++;
	}
	else if (g_loadSceneViaScript)
	{
		if (loop == 0)
		{
			g_main->m_loadScene = CTrue;
			g_main->m_prevLoadScene = CTrue;
			//find the scene
			GetWithoutDot(g_currentVSceneNameViaScript);

			CChar bannerPath[MAX_NAME_SIZE];
			sprintf(bannerPath, "%s%s%s", "assets/vscenes/", g_currentVSceneNameViaScript, "/Banner/");

			HANDLE hFind;
			WIN32_FIND_DATAA data;
			CChar bannerTempPath[MAX_NAME_SIZE];
			sprintf(bannerTempPath, "%s%s", bannerPath, "*.*");
			hFind = FindFirstFileA(bannerTempPath, &data);
			CChar bannerNameAndPath[MAX_NAME_SIZE];
			do
			{
				sprintf(bannerNameAndPath, "%s%s", bannerPath, data.cFileName);
				if (!Cmp(data.cFileName, ".") && !Cmp(data.cFileName, ".."))
					break;
			} while (FindNextFileA(hFind, &data));
			FindClose(hFind);
			GenerateLoadingTexture(bannerNameAndPath);

			glUseProgram(0);
			glDrawBuffer(GL_BACK);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			ShowLoadingScene();
			glFlush();
			SwapBuffers(g_window.m_windowGL.hDC);
			g_main->Reset();

			CChar RTIPath[MAX_NAME_SIZE];
			sprintf(RTIPath, "%s%s%s%s%s", "Assets\\VScenes\\", g_currentVSceneNameViaScript, "\\", g_currentVSceneNameViaScript, ".vin");
			if (!g_main->Load(RTIPath))
				return CFalse;

			DeleteLoadingTexture();
			g_main->ResetTimer();
			gPhysXscene->setGravity(NxVec3(0.0, 0.0, 0.0));

			g_main->m_tempPauseGame = g_currentVSceneProperties.m_pauseGame;
			g_main->m_tempPausePhysics = g_main->m_pausePhysics;

			g_currentVSceneProperties.m_pauseGame = CFalse;
			g_main->m_pausePhysics = CFalse;
		}
		if (loop < 5)
		{
			g_main->m_renderVideoEnabled = CFalse;
			g_main->Render();
			gPhysXscene->setGravity(NxVec3(0.0, 0.0, 0.0));
			g_nx->gControllers->reportSceneChanged();
			g_main->ApplyForce(IDLE, 1.f / 60.f);

			g_main->ResetPhysXCounts();
			loop++;
			return CTrue;
		}
		else
		{
			g_loadSceneViaScript = CFalse;
			gPhysXscene->setGravity(NxVec3(g_nx->m_defaultGravity.x, g_nx->m_defaultGravity.y, g_nx->m_defaultGravity.z));
			g_nx->gControllers->reportSceneChanged();

			g_main->m_loadScene = CFalse;
			g_main->m_renderVideoEnabled = CTrue;

			g_currentVSceneProperties.m_pauseGame = g_main->m_tempPauseGame;
			g_main->m_pausePhysics = g_main->m_tempPausePhysics;

			g_main->ResetPhysXCounts();
			loop = 0;
			return CTrue;
		}
	}
	else
	{
		if (!g_main->Render()) return CFalse;
	}
	g_main->ResetPhysXCounts();
	SwapBuffers(g_window.m_windowGL.hDC);

	return CTrue;
}

// the Windows Procedure event handlers
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LONG    lRet = 0;

	switch (message)
	{
	case WM_SYSCOMMAND:						// Intercept System Commands
	{
		switch (wParam)						// Check System Calls
		{
		case SC_SCREENSAVE:				// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;
		}
		break;							// Exit
	}

	case WM_CLOSE:					// windows is closing

		// send WM_QUIT to message queue
		PostQuitMessage(0);
		return 0;
		break;

	case WM_DESTROY:
		g_window.DestroyWindowGL(&g_window.m_windowGL);
		PostQuitMessage(0);
		return 0;
		break;

	case WM_SIZE:
		InvalidateRect(hwnd, NULL, true);
		g_window.ReshapeGL(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;
		break;

	case WM_PAINT: // paint
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	}

	default:
		break;
	}

	return (DefWindowProc(hwnd, message, wParam, lParam));
}

LRESULT CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HANDLE hBitmap;
	hBitmap = LoadImage(NULL, _T("Assets/Logo/Logo.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HWND hPic = GetDlgItem(hwnd, IDC_STATIC_LOGO);

	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(hPic, STM_SETIMAGE, IMAGE_BITMAP, LPARAM(hBitmap));
		if (g_options.m_useCurrentResolution)
		{
			DEVMODE dmScreenSettings;												// device mode
			EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);
			g_options.m_width = dmScreenSettings.dmPelsWidth;		// screen g_width
			g_options.m_height = dmScreenSettings.dmPelsHeight;		// screen g_height
			CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_CURRENT);
		}
		else
		{
			switch (g_options.m_width)
			{
			case 800:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_800);
				break;
			case 1024:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_1024);
				break;
			case 1280:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_1280);
				break;
			case 1920:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_1920);
				break;
			case 2560:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_2560);
				break;
			case 3840:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_3840);
				break;
			case 7680:
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_7680);
				break;
			default:
				DEVMODE dmScreenSettings;												// device mode
				EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);
				g_options.m_width = dmScreenSettings.dmPelsWidth;		// screen g_width
				g_options.m_height = dmScreenSettings.dmPelsHeight;		// screen g_height
				CheckRadioButton(hwnd, IDC_RES_CURRENT, IDC_RES_7680, IDC_RES_CURRENT);
				break;
			}
		}
		//load  multisampling from the config file

		switch (g_options.m_numSamples)
		{
		case 0:
			CheckRadioButton(hwnd, IDC_MSAMPLE_NO, IDC_MSAMPLE_16, IDC_MSAMPLE_NO);
			break;
		case 2:
			CheckRadioButton(hwnd, IDC_MSAMPLE_NO, IDC_MSAMPLE_16, IDC_MSAMPLE_2);
			break;
		case 4:
			CheckRadioButton(hwnd, IDC_MSAMPLE_NO, IDC_MSAMPLE_16, IDC_MSAMPLE_4);
			break;
		case 8:
			CheckRadioButton(hwnd, IDC_MSAMPLE_NO, IDC_MSAMPLE_16, IDC_MSAMPLE_8);
			break;
		case 16:
			CheckRadioButton(hwnd, IDC_MSAMPLE_NO, IDC_MSAMPLE_16, IDC_MSAMPLE_16);
			break;
		}

		//load  anisotropic filtering from the config file
		switch (g_options.m_anisotropy)
		{
		case 0:
			CheckRadioButton(hwnd, IDC_ISOTROP_NO, IDC_ISOTROP_16, IDC_ISOTROP_NO);
			break;
		case 2:
			CheckRadioButton(hwnd, IDC_ISOTROP_NO, IDC_ISOTROP_16, IDC_ISOTROP_2);
			break;
		case 4:
			CheckRadioButton(hwnd, IDC_ISOTROP_NO, IDC_ISOTROP_16, IDC_ISOTROP_4);
			break;
		case 8:
			CheckRadioButton(hwnd, IDC_ISOTROP_NO, IDC_ISOTROP_16, IDC_ISOTROP_8);
			break;
		case 16:
			CheckRadioButton(hwnd, IDC_ISOTROP_NO, IDC_ISOTROP_16, IDC_ISOTROP_16);
			break;
		}

		//load VSync data from the config file
		if (g_options.m_disableVSync == CTrue)
		{
			SendDlgItemMessage(hwnd, IDC_DVSYNC, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendDlgItemMessage(hwnd, IDC_DVSYNC, BM_SETCHECK, BST_UNCHECKED, 0);
		}

		//load water reflection data from the config file
		if (g_options.m_enableWaterReflection == CTrue)
		{
			SendDlgItemMessage(hwnd, IDC_WATER_REFLECTION, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendDlgItemMessage(hwnd, IDC_WATER_REFLECTION, BM_SETCHECK, BST_UNCHECKED, 0);
		}

		//load full screen data from the config file
		if (g_options.m_fullScreen == CTrue)
		{
			SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_SETCHECK, BST_UNCHECKED, 0);
		}

		//load  FBO data from the config file
		if (g_options.m_enableFBO == CTrue)
		{
			SendDlgItemMessage(hwnd, IDC_FBO, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendDlgItemMessage(hwnd, IDC_FBO, BM_SETCHECK, BST_UNCHECKED, 0);
		}

		//load  VBO data from the config file
		if (g_options.m_enableVBO == CTrue)
		{
			SendDlgItemMessage(hwnd, IDC_VBO, BM_SETCHECK, BST_CHECKED, 0);
		}
		else
		{
			SendDlgItemMessage(hwnd, IDC_VBO, BM_SETCHECK, BST_UNCHECKED, 0);
		}

		break; //case WM_INIT

	case WM_COMMAND:
	{
		if (wParam == IDCANCEL)
			EndDialog(hwnd, 0);
		else if (wParam == IDOK)
		{
			//configuration
			FILE *filePtr;
			filePtr = fopen("Assets/config/conf_win32.dat", "wb");
			fwrite(&g_options, sizeof(COptions), 1, filePtr);
			fclose(filePtr);
			////////////////

			EndDialog(hwnd, 1);
		}
		else if (wParam == IDC_RES_CURRENT)
		{
			DEVMODE dmScreenSettings;					// device mode
			EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmScreenSettings);
			g_options.m_width = dmScreenSettings.dmPelsWidth;		// screen g_width
			g_options.m_height = dmScreenSettings.dmPelsHeight;		// screen g_height

			g_options.m_useCurrentResolution = CTrue;
		}
		else if (wParam == IDC_RES_800)
		{
			g_options.m_width = 800;
			g_options.m_height = 600;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_1024)
		{
			g_options.m_width = 1024;
			g_options.m_height = 768;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_1280)
		{
			g_options.m_width = 1280;
			g_options.m_height = 720;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_1920)
		{
			g_options.m_width = 1920;
			g_options.m_height = 1080;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_2560)
		{
			g_options.m_width = 2560;
			g_options.m_height = 1440;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_3840)
		{
			g_options.m_width = 3840;
			g_options.m_height = 2160;

			g_options.m_useCurrentResolution = CFalse;
		}
		else if (wParam == IDC_RES_7680)
		{
			g_options.m_width = 7680;
			g_options.m_height = 4320;

			g_options.m_useCurrentResolution = CFalse;
		}

		//multisampling
		else if (wParam == IDC_MSAMPLE_NO)
			g_options.m_numSamples = 0;
		else if (wParam == IDC_MSAMPLE_2)
			g_options.m_numSamples = 2;
		else if (wParam == IDC_MSAMPLE_4)
			g_options.m_numSamples = 4;
		else if (wParam == IDC_MSAMPLE_8)
			g_options.m_numSamples = 8;
		else if (wParam == IDC_MSAMPLE_16)
			g_options.m_numSamples = 16;

		//Anisotropic filtering
		else if (wParam == IDC_ISOTROP_NO)
			g_options.m_anisotropy = 0;
		else if (wParam == IDC_ISOTROP_2)
			g_options.m_anisotropy = 2;
		else if (wParam == IDC_ISOTROP_4)
			g_options.m_anisotropy = 4;
		else if (wParam == IDC_ISOTROP_8)
			g_options.m_anisotropy = 8;
		else if (wParam == IDC_ISOTROP_16)
			g_options.m_anisotropy = 16;

		//VSync
		if (SendDlgItemMessage(hwnd, IDC_DVSYNC, BM_GETCHECK, 0, 0) == BST_CHECKED)
			g_options.m_disableVSync = CTrue;
		else if (SendDlgItemMessage(hwnd, IDC_DVSYNC, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			g_options.m_disableVSync = CFalse;

		//Water reflection
		if (SendDlgItemMessage(hwnd, IDC_WATER_REFLECTION, BM_GETCHECK, 0, 0) == BST_CHECKED)
			g_options.m_enableWaterReflection = CTrue;
		else if (SendDlgItemMessage(hwnd, IDC_WATER_REFLECTION, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			g_options.m_enableWaterReflection = CFalse;

		//fullscreen
		if (SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_GETCHECK, 0, 0) == BST_CHECKED)
			g_options.m_fullScreen = CTrue;
		else if (SendDlgItemMessage(hwnd, IDC_FULLSCREEN, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			g_options.m_fullScreen = CFalse;

		//FBO
		if (SendDlgItemMessage(hwnd, IDC_FBO, BM_GETCHECK, 0, 0) == BST_CHECKED)
			g_options.m_enableFBO = CTrue;
		else if (SendDlgItemMessage(hwnd, IDC_FBO, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			g_options.m_enableFBO = CFalse;

		//VBO
		if (SendDlgItemMessage(hwnd, IDC_VBO, BM_GETCHECK, 0, 0) == BST_CHECKED)
			g_options.m_enableVBO = CTrue;
		else if (SendDlgItemMessage(hwnd, IDC_VBO, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			g_options.m_enableVBO = CFalse;
		//if (SendDlgItemMessage (hwnd, IDC_SHOWDLG, BM_GETCHECK, 0, 0) == BST_CHECKED)
		//	g_options.m_showStartupDialog = CTrue;
		//else if (SendDlgItemMessage (hwnd, IDC_SHOWDLG, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
		//	g_options.m_showStartupDialog = CFalse;


	}break;
	}
	return 0;
}


// the main windows entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	g_instance = GetModuleHandle(NULL);
	MSG	msg;											// Window Message Structure
	//configuration
	FILE *filePtr;
	filePtr = fopen("Assets/config/conf_win32.dat", "rb");
	if (!filePtr)
	{
		filePtr = fopen("Assets/config/conf_win32.dat", "wb");
		fwrite(&g_options, sizeof(COptions), 1, filePtr);
	}
	else
	{
		fread(&g_options, sizeof(COptions), 1, filePtr);
	}
	fclose(filePtr);
	////////////////

	if (!DialogBox(hInstance, MAKEINTRESOURCE(IDD_INIT_DIALOG), NULL, (DLGPROC)DlgProc))
		return 0;

	g_width = g_options.m_width;
	g_height = g_options.m_height;

	// Fill Out Window
	ZeroMemory(&g_window.m_windowGL, sizeof(CWindowGL));		// Make Sure Memory Is Zeroed
	g_window.m_windowGL.init.className = _T("EhsanKamrani");
	g_window.m_windowGL.init.hInstance = g_instance;
	g_window.m_windowGL.init.title = _T("VandaEngine");						// Window Title
	g_window.m_windowGL.init.width = g_width;								// Window Width
	g_window.m_windowGL.init.height = g_height;								// Window Height
	g_window.m_windowGL.init.bitsPerPixel = g_bits;							// Bits Per Pixel
	g_window.m_windowGL.init.isFullScreen = g_options.m_fullScreen;			// Fullscreen?
	g_window.m_windowGL.init.testWindow = FALSE;
	g_window.m_windowGL.init.windowProc = WndProc;
	g_window.m_windowGL.multiSampling = false;

	if (!g_window.CreateWindowGL(&g_window.m_windowGL))
	{
		MessageBox(NULL, _T("Couldn't create the OpenGL window"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
		return false;
	}
	GLenum err = glewInit();
	if (err != GLEW_OK)
		MessageBox(NULL, _T("Couldn't initialize GLEW"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
	if (!GLEW_EXT_framebuffer_object || !GLEW_ARB_texture_non_power_of_two || !g_options.m_enableFBO)
	{
		//MessageBox( NULL, _T("Switching to old rendering style."), _T("VandaEngine Warning"), MB_OK | MB_ICONINFORMATION );
		g_useOldRenderingStyle = CTrue;
	}

	switch (g_options.m_numSamples)
	{
	case 2:
		g_window.m_numSamples = 2;
		break;
	case 4:
		g_window.m_numSamples = 4;
		break;
	case 8:
		g_window.m_numSamples = 8;
		break;
	case 16:
		g_window.m_numSamples = 16;
		break;
	default:
		g_window.m_numSamples = 0;
	}
	if (g_window.m_numSamples > 1 && !g_useOldRenderingStyle)
	{
		if (!GLEW_EXT_framebuffer_multisample)
		{
			MessageBox(NULL, _T("GL_EXT_framebuffer_multisample is not supported\nSwitching to old rendering style"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
			g_useOldRenderingStyle = CTrue; //See if we can we use multisampling with old rendering style?
		}
		else
			g_window.m_windowGL.multiSampling = true; //use new rendering style with multisampling
	}

	if (g_window.m_numSamples > 1 && g_useOldRenderingStyle && !WGLEW_ARB_multisample)
		MessageBox(NULL, _T("Your implementation doesn't support multisampling"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
	if (g_window.m_numSamples > 1 && WGLEW_ARB_multisample && g_useOldRenderingStyle)
	{
		if (!g_window.DestroyWindowGL(&g_window.m_windowGL))
		{
			MessageBox(NULL, _T("Couldn't destroy the OpenGL window to use multisampling"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
			return false;
		}
		g_window.m_windowGL.multiSampling = true;
		if (!g_window.CreateWindowGL(&g_window.m_windowGL))
		{
			MessageBox(NULL, _T("Couldn't create the OpenGL window with multisampling\n please disable multisampling"), _T("VandaEngine Error"), MB_OK | MB_ICONINFORMATION);
			return false;
		}
		if (g_window.m_windowGL.multiSampling && GLEW_NV_multisample_filter_hint)
		{
			glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
			glEnable(GL_MULTISAMPLE);
		}
	}

	if (WGLEW_EXT_swap_control && g_options.m_disableVSync)
		wglSwapIntervalEXT(0);
	else
		wglSwapIntervalEXT(1);

	//HANDLE hIcon = LoadImage(g_window.m_windowGL.init.hInstance, _T("pass of ico"), IMAGE_ICON, 64, 64, LR_LOADFROMFILE);
	//if (hIcon) {
	//	//Change both icons to the same icon handle.
	//	SendMessage(g_window.m_windowGL.hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	//	SendMessage(g_window.m_windowGL.hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

	//	//This will ensure that the application icon gets changed too.
	//	SendMessage(GetWindow(g_window.m_windowGL.hWnd, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	//	SendMessage(GetWindow(g_window.m_windowGL.hWnd, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	//}	

	if (!Initialize())
		return 0;

	// update the window
	// main message loop
	while (!g_done)
	{
		PeekMessage(& msg, g_hwnd, NULL, NULL, PM_REMOVE);

		TranslateMessage(&msg);		// translate and dispatch to event queue
		DispatchMessage(&msg);

		if (!Render()) g_done = true;

	}
	CleanUp();
	ShowCursor(TRUE);
	return (int)msg.wParam;
}
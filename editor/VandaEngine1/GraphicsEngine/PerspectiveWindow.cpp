//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

// PerspectiveWindow.cpp : implementation file
//

#include "stdafx.h"
#include "PerspectiveWindow.h"
#include "opengl.h"
#include "render.h"
#include "scene.h"
#include "fog.h"
#include "..\VandaEngine1.h"
#include "..\VandaEngine1Dlg.h"
#include "Animation.h"
// CMultipleWindows
CInt g_numLights = 0;
CInt g_totalLights = 0;
CBool g_fogBlurPass = CFalse;
IMPLEMENT_DYNAMIC(CMultipleWindows, CWnd)

//Vanda C Functions to be used in Lua scripts
CInt PlaySoundLoop(lua_State *L)
{
	if( g_testScript )
		return 0;
	int argc = lua_gettop(L);

	for ( int n=1; n<=argc; ++n )
	{
		CBool foundTarget = CFalse;
		for( CUInt i = 0 ; i < g_engineStaticSounds.size(); i++ )
		{
			if( Cmp( g_engineStaticSounds[i]->GetName(),  lua_tostring(L, n) ) )
			{
				g_engineStaticSounds[i]->m_source->SetLooping( CTrue );
				//g_engineStaticSounds[i]->SetLoop( CTrue );
				//g_engineStaticSounds[i]->SetPlay(CTrue);
				g_soundSystem->PlayALSound( *(g_engineStaticSounds[i]->m_source) );
				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nSound '", g_engineStaticSounds[i]->GetName(), "' will be played continiously.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCoudn't find Sound '", lua_tostring(L, n), "' to be played.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 0; // number of return values
}

CInt PlaySoundOnce(lua_State *L)
{
	if (g_testScript)
		return 0;
	int argc = lua_gettop(L);

	for (int n = 1; n <= argc; ++n)
	{
		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_engineStaticSounds.size(); i++)
		{
			if (Cmp(g_engineStaticSounds[i]->GetName(), lua_tostring(L, n)))
			{
				g_engineStaticSounds[i]->m_source->SetLooping( CFalse );
				//g_engineStaticSounds[i]->SetLoop( CFalse );
				//g_engineStaticSounds[i]->SetPlay(CTrue);
				g_soundSystem->PlayALSound( *(g_engineStaticSounds[i]->m_source) );
				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nSound '", g_engineStaticSounds[i]->GetName(), "' will be played once.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCoudn't find Sound '", lua_tostring(L, n), "' to be played.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 0; // number of return values
}


CInt PauseSound(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);

	for ( int n=1; n<=argc; ++n )
	{
		CBool foundTarget = CFalse;
		for( CUInt i = 0 ; i < g_engineStaticSounds.size(); i++ )
		{
			if( Cmp( g_engineStaticSounds[i]->GetName(),  lua_tostring(L, n) ) )
			{
				//g_engineStaticSounds[i]->SetPlay(CFalse);
				g_soundSystem->PauseALSound( *(g_engineStaticSounds[i]->m_source) );
				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nSound '", g_engineStaticSounds[i]->GetName(), "' will be paused.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCoudn't find Sound '", lua_tostring(L, n), "' to be paused.");
			PrintInfo(temp, COLOR_RED);
		}

	}
	return 0; // number of return values
}

CInt StopSound(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);

	for ( int n=1; n<=argc; ++n )
	{
		CBool foundTarget = CFalse;
		for( CUInt i = 0 ; i < g_engineStaticSounds.size(); i++ )
		{
			if( Cmp( g_engineStaticSounds[i]->GetName(),  lua_tostring(L, n) ) )
			{
				//g_engineStaticSounds[i]->SetPlay(CFalse);
				g_soundSystem->StopALSound( *(g_engineStaticSounds[i]->m_source) );
				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nSound '", g_engineStaticSounds[i]->GetName(), "' will be stopped.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCoudn't find Sound '", lua_tostring(L, n), "' to be stopped.");
			PrintInfo(temp, COLOR_RED);
		}

	}
	return 0; // number of return values
}

CInt BlendCycle(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);
	if( argc < 4 )
	{
		PrintInfo( "\nPlease specify 4 arguments for BlendCycle()", COLOR_RED );
		return 0;
	}
	CScene* scene = NULL;

	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CChar prefabName[MAX_NAME_SIZE];
		Cpy(prefabName, g_scene[i]->GetDocURI());
		StringToUpper(prefabName);

		CChar sceneName[MAX_NAME_SIZE];
		Cpy(sceneName, g_scene[i]->GetName());
		StringToUpper(sceneName);

		if (Cmp(prefabName, luaToString))
		{
			g_scene[i]->m_animationStatus = eANIM_PLAY;
			scene = g_scene[i];
			break;
		}
	}

	if( !scene )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the prefab instance '", luaToString, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy( luaToString2, lua_tostring(L, 2) );
	StringToUpper( luaToString2 );
	CBool foundTarget = CFalse;
	CInt index;
	for( CInt i = 0; i < scene->GetNumClips(); i++ )
	{
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, scene->m_animationClips[i]->GetName() );
		StringToUpper( animationName );
		if( Cmp( luaToString2, animationName ) )
		{
			index = i;
			foundTarget = CTrue;
			break;
		}
	}
	if( !foundTarget )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the animation clip '", luaToString2, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}
	scene->BlendCycle( index, (CFloat)lua_tonumber(L, 3), (CFloat)lua_tonumber( L, 4 ) );
	return 0;
}

CInt ClearCycle(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);
	if( argc < 3 )
	{
		PrintInfo( "\nPlease specify 3 arguments for ClearCycle()", COLOR_RED );
		return 0;
	}
	CScene* scene = NULL;

	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CChar prefabName[MAX_NAME_SIZE];
		Cpy(prefabName, g_scene[i]->GetDocURI());
		StringToUpper(prefabName);

		CChar sceneName[MAX_NAME_SIZE];
		Cpy(sceneName, g_scene[i]->GetName());
		StringToUpper(sceneName);

		if (Cmp(prefabName, luaToString))
		{
			g_scene[i]->m_animationStatus = eANIM_PLAY;
			scene = g_scene[i];
			break;
		}
	}

	if( !scene )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the prefab instance '", luaToString, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy( luaToString2, lua_tostring(L, 2) );
	StringToUpper( luaToString2 );
	CBool foundTarget = CFalse;
	CInt index;
	for( CInt i = 0; i < scene->GetNumClips(); i++ )
	{
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, scene->m_animationClips[i]->GetName() );
		StringToUpper( animationName );
		if( Cmp( luaToString2, animationName ) )
		{
			index = i;
			g_scene[i]->m_animationStatus = eANIM_PLAY;
			foundTarget = CTrue;
			break;
		}
	}
	if( !foundTarget )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the animation clip '", luaToString2, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}
	scene->ClearCycle( index, (CFloat)lua_tonumber(L, 3) );
	return 0;
}

CInt ExecuteAction(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);
	if( argc < 4 )
	{
		PrintInfo( "\nPlease specify at least 4 arguments for ExecuteAction()", COLOR_RED );
		return 0;
	}
	CScene* scene = NULL;

	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CChar prefabName[MAX_NAME_SIZE];
		Cpy(prefabName, g_scene[i]->GetDocURI());
		StringToUpper(prefabName);

		CChar sceneName[MAX_NAME_SIZE];
		Cpy(sceneName, g_scene[i]->GetName());
		StringToUpper(sceneName);

		if (Cmp(prefabName, luaToString))
		{
			g_scene[i]->m_animationStatus = eANIM_PLAY;
			scene = g_scene[i];
			break;
		}
	}

	if( !scene )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the prefab instance '", luaToString, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy( luaToString2, lua_tostring(L, 2) );
	StringToUpper( luaToString2 );
	CBool foundTarget = CFalse;
	CInt index;
	for( CInt i = 0; i < scene->GetNumClips(); i++ )
	{
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, scene->m_animationClips[i]->GetName() );
		StringToUpper( animationName );
		if( Cmp( luaToString2, animationName ) )
		{
			index = i;
			foundTarget = CTrue;
			break;
		}
	}
	if( !foundTarget )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the animation clip '", luaToString2, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}
	CFloat weight = 1.0f;
	CBool lock = CFalse;
	if( argc > 4 )
		weight = lua_tonumber(L,5);
	if( argc > 5 )
		lock = (CBool)lua_toboolean(L, 6);
	scene->ExecuteAction( index, (CFloat)lua_tonumber(L, 3), (CFloat)lua_tonumber(L,4), weight, lock);
	return 0;
}

CInt ReverseExecuteAction(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);
	if( argc < 2 )
	{
		PrintInfo( "\nPlease specify 2 arguments for ReverseExecuteAction()", COLOR_RED );
		return 0;
	}
	CScene* scene = NULL;

	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_scene.size(); i++)
	{
		CChar prefabName[MAX_NAME_SIZE];
		Cpy(prefabName, g_scene[i]->GetDocURI());
		StringToUpper(prefabName);

		CChar sceneName[MAX_NAME_SIZE];
		Cpy(sceneName, g_scene[i]->GetName());
		StringToUpper(sceneName);

		if (Cmp(prefabName, luaToString))
		{
			g_scene[i]->m_animationStatus = eANIM_PLAY;
			scene = g_scene[i];
			break;
		}
	}

	if( !scene )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the prefab instance '", luaToString, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy( luaToString2, lua_tostring(L, 2) );
	StringToUpper( luaToString2 );
	CBool foundTarget = CFalse;
	CInt index;
	for( CInt i = 0; i < scene->GetNumClips(); i++ )
	{
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, scene->m_animationClips[i]->GetName() );
		StringToUpper( animationName );
		if( Cmp( luaToString2, animationName ) )
		{
			index = i;
			foundTarget = CTrue;
			break;
		}
	}
	if( !foundTarget )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Couldn't find the animation clip '", luaToString2, "'" );
		PrintInfo( temp, COLOR_RED );
		return 0;
	}
	scene->ReverseExecuteAction( index );
	return 0;
}

CInt LoadVScene(lua_State *L)
{
	if( g_testScript )
		return 0;

	int argc = lua_gettop(L);
	if( argc < 1 )
	{
		PrintInfo( "\nPlease specify 1 argument for LoadVScene()", COLOR_RED );
		return 0;
	}
	//g_clickedNew = g_clickedOpen = CTrue;
	//g_multipleView->m_loadScene = CTrue;
	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy( luaToString, lua_tostring(L, 1) );

	CChar VSceneName[MAX_NAME_SIZE];
	sprintf(VSceneName, "%s%s", luaToString, ".vin");
	//GetWithoutDot(luaToString);
	//CChar RTIPath[MAX_NAME_SIZE];
	//SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, RTIPath);
	//sprintf( g_fileNameInCommandLine, "%s%s%s%s%s%s", RTIPath, "/Vanda/Projects/", luaToString, "/", luaToString, ".vin" );
	//ex_pVandaEngine1Dlg->OnMenuClickedOpenVScene(CFalse);
	//g_multipleView->m_loadScene = CFalse;
	//g_clickedNew = g_clickedOpen = CFalse;
	CBool foundTarget = CFalse;
	for (CUInt i = 0; i < g_VSceneNamesOfCurrentProject.size(); i++)
	{
		if (Cmp(VSceneName, g_VSceneNamesOfCurrentProject[i].c_str()))
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nVScene '", luaToString, ".vin' will be loaded.");
			PrintInfo(temp, COLOR_YELLOW);
			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "\nCoudn't find VScene '", VSceneName, "' to be loaded.");
		PrintInfo(temp, COLOR_RED);
	}

	return 0;
}

CInt ActivateCamera( lua_State* L )
{
	int argc = lua_gettop(L);

	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy( luaToString, lua_tostring(L, 1) );
	StringToUpper( luaToString );

	if( Cmp( "DEFAULT_PHYSX", luaToString ) )
	{
		//g_render.SetActiveInstanceCamera( NULL );
		//g_currentCameraType = eCAMERA_DEFAULT_PHYSX;
		PrintInfo("\nDefault PhysX Camera will be activated.", COLOR_YELLOW);
	}
	else if( Cmp( "DEFAULT_FREE", luaToString ) )
	{
		//g_render.SetActiveInstanceCamera( g_render.GetDefaultInstanceCamera() );
		//g_currentCameraType = eCAMERA_DEFAULT_FREE;
		PrintInfo("\nDefault free Camera will be activated.", COLOR_YELLOW);
	}
	else
	{
		CBool foundTarget = CFalse;
		for( CUInt i = 0; i < g_cameraInstances.size(); i++ )
		{
			CChar camera[MAX_NAME_SIZE];
			Cpy( camera, g_cameraInstances[i]->m_abstractCamera->GetName() );
			StringToUpper( camera );

			if( Cmp( camera, luaToString ) )
			{
				//g_render.SetActiveInstanceCamera(  g_cameraInstances[i] );
				//g_currentCameraType = eCAMERA_COLLADA;
				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "%s%s%s", "\nCamera '", g_cameraInstances[i]->m_abstractCamera->GetName(), "' will be activated.");
				PrintInfo(temp, COLOR_RED);

				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCoudn't find camera '", luaToString, "' to be activated.");
			PrintInfo(temp, COLOR_RED);
		}
	}
	return 0;
}

CInt LoadResource(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 2)
	{
		PrintInfo("\nPlease specify 2 arguments for LoadResource()", COLOR_RED);
		return 0;
	}

	CChar luaToString1[MAX_NAME_SIZE];
	Cpy(luaToString1, lua_tostring(L, 1));
	StringToUpper(luaToString1); //package name

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy(luaToString2, lua_tostring(L, 2));
	StringToUpper(luaToString2);

	CChar fileName[MAX_NAME_SIZE];
	Cpy(fileName, g_currentProjectPath);

	Append(fileName, "Resources/");
	Append(fileName, luaToString1);
	Append(fileName, "/");
	Append(fileName, luaToString2);

	CChar extension[MAX_NAME_SIZE];
	if (GetFileExtension(luaToString2))
		Cpy(extension, GetFileExtension(luaToString2));
	else
		return 0;

	CChar name[MAX_NAME_SIZE];
	Cpy(name, luaToString1);
	Append(name, "_");
	Append(name, luaToString2);
	StringToUpper(name);

	for (CUInt i = 0; i < g_resourceFiles.size(); i++)
	{
		CChar old_name[MAX_NAME_SIZE];
		Cpy(old_name, g_resourceFiles[i]->GetName());
		StringToUpper(old_name);

		if (Cmp(name, old_name))
			return 0;
	}
	if (Cmp(extension, ".OGG"))
	{
		CResourceFile* oggFile = CNew(CResourceFile);
		if (oggFile->LoadOGGFile(fileName))
		{
			oggFile->SetName(name);
			oggFile->GetSoundSource()->SetName(name);
			g_resourceFiles.push_back(oggFile);
		}
		else
		{
			CDelete(oggFile);
		}
	}
	else if (Cmp(extension, ".DDS"))
	{
		CResourceFile* ddsFile = CNew(CResourceFile);
		if (ddsFile->LoadDDSFile(fileName))
		{
			ddsFile->SetName(name);
			g_resourceFiles.push_back(ddsFile);
		}
		else
		{
			CDelete(ddsFile);
		}
	}
	else if (Cmp(extension, ".AVI"))
	{
		CResourceFile* aviFile = CNew(CResourceFile);
		if (aviFile->LoadAVIFile(fileName))
		{
			aviFile->SetName(name);
			g_resourceFiles.push_back(aviFile);
		}
		else
		{
			CDelete(aviFile);
		}
	}

	return 1;
}

CInt PlayResourceSoundLoop(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify at least 1 argument for PlayResourceSoundLoop()", COLOR_RED);
		return 0;
	}

	for (int n = 1; n <= argc; ++n)
	{
		CChar luaToString[MAX_NAME_SIZE];
		Cpy(luaToString, lua_tostring(L, n));
		StringToUpper(luaToString); //package name

		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_resourceFiles.size(); i++)
		{
			if (g_resourceFiles[i]->GetSoundSource())
			{
				CChar string[MAX_NAME_SIZE];
				Cpy(string, g_resourceFiles[i]->GetSoundSource()->GetName());
				StringToUpper(string); //package name

				if (Cmp(string, luaToString))
				{
					g_resourceFiles[i]->GetSoundSource()->GetSoundSource()->SetLooping(CTrue);
					g_soundSystem->PlayALSound(*(g_resourceFiles[i]->GetSoundSource()->GetSoundSource()));
					//CChar temp[MAX_NAME_SIZE];
					//sprintf(temp, "%s%s%s", "\nSound '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be played continiously.");
					//PrintInfo(temp, COLOR_YELLOW);
					foundTarget = CTrue;
					break;
				}
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCouldn't find the sound '", lua_tostring(L, n), "' to be played.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 1;
}

CInt PlayResourceSoundOnce(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify at least 1 argument for PlayResourceSoundLoop()", COLOR_RED);
		return 0;
	}

	for (int n = 1; n <= argc; ++n)
	{
		CChar luaToString[MAX_NAME_SIZE];
		Cpy(luaToString, lua_tostring(L, n));
		StringToUpper(luaToString); //package name

		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_resourceFiles.size(); i++)
		{
			if (g_resourceFiles[i]->GetSoundSource())
			{
				CChar string[MAX_NAME_SIZE];
				Cpy(string, g_resourceFiles[i]->GetSoundSource()->GetName());
				StringToUpper(string); //package name

				if (Cmp(string, luaToString))
				{
					g_resourceFiles[i]->GetSoundSource()->GetSoundSource()->SetLooping(CFalse);
					g_soundSystem->PlayALSound(*(g_resourceFiles[i]->GetSoundSource()->GetSoundSource()));
					//CChar temp[MAX_NAME_SIZE];
					//sprintf(temp, "%s%s%s", "\nSound '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be played once.");
					//PrintInfo(temp, COLOR_YELLOW);
					foundTarget = CTrue;
					break;
				}
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCouldn't find the sound '", lua_tostring(L, n), "' to be played once.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 1;
}

CInt StopResourceSound(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify at least 1 argument for StopResourceSound()", COLOR_RED);
		return 0;
	}

	for (int n = 1; n <= argc; ++n)
	{
		CChar luaToString[MAX_NAME_SIZE];
		Cpy(luaToString, lua_tostring(L, n));
		StringToUpper(luaToString); //package name

		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_resourceFiles.size(); i++)
		{ 
			if (g_resourceFiles[i]->GetSoundSource())
			{
				CChar string[MAX_NAME_SIZE];
				Cpy(string, g_resourceFiles[i]->GetSoundSource()->GetName());
				StringToUpper(string); //package name

				if (Cmp(string, luaToString))
				{
					g_soundSystem->StopALSound(*(g_resourceFiles[i]->GetSoundSource()->GetSoundSource()));
					//CChar temp[MAX_NAME_SIZE];
					//sprintf(temp, "%s%s%s", "\nSound '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be stopped.");
					//PrintInfo(temp, COLOR_YELLOW);
					foundTarget = CTrue;
					break;
				}
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCouldn't find the sound '", lua_tostring(L, n), "' to be stopped.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 1;
}

CInt StopAllResourceSounds(lua_State *L)
{
	if (g_testScript)
		return 0;

	for (CUInt i = 0; i < g_resourceFiles.size(); i++)
	{
		if (g_resourceFiles[i]->GetSoundSource())
		{
			g_soundSystem->StopALSound(*(g_resourceFiles[i]->GetSoundSource()->GetSoundSource()));
		}
	}

	return 1;
}

CInt PauseResourceSound(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify at least 1 argument for StopResourceSound()", COLOR_RED);
		return 0;
	}

	for (int n = 1; n <= argc; ++n)
	{
		CChar luaToString[MAX_NAME_SIZE];
		Cpy(luaToString, lua_tostring(L, n));
		StringToUpper(luaToString); //package name

		CBool foundTarget = CFalse;
		for (CUInt i = 0; i < g_resourceFiles.size(); i++)
		{
			if (g_resourceFiles[i]->GetSoundSource())
			{
				CChar string[MAX_NAME_SIZE];
				Cpy(string, g_resourceFiles[i]->GetSoundSource()->GetName());
				StringToUpper(string); //package name

				if (Cmp(string, luaToString))
				{
					g_soundSystem->PauseALSound(*(g_resourceFiles[i]->GetSoundSource()->GetSoundSource()));
					//CChar temp[MAX_NAME_SIZE];
					//sprintf(temp, "%s%s%s", "\nSound '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be paused.");
					//PrintInfo(temp, COLOR_YELLOW);
					foundTarget = CTrue;
					break;
				}
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nCouldn't find the sound '", lua_tostring(L, n), "' to be paused.");
			PrintInfo(temp, COLOR_RED);
		}
	}

	return 1;
}

CInt LoadGUI(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 2)
	{
		PrintInfo("\nPlease specify 2 arguments for LoadGUI()", COLOR_RED);
		return 0;
	}

	//find the scene
	CChar luaToString1[MAX_NAME_SIZE];
	Cpy(luaToString1, lua_tostring(L, 1));
	StringToUpper(luaToString1); //package name

	CChar luaToString2[MAX_NAME_SIZE];
	Cpy(luaToString2, lua_tostring(L, 2));
	StringToUpper(luaToString2);

	CChar packagePath[MAX_URI_SIZE];
	CChar packageName[MAX_NAME_SIZE];
	CChar guiName[MAX_NAME_SIZE];
	CChar guiAndPackageName[MAX_NAME_SIZE];
	CChar guiInstanceName[MAX_NAME_SIZE];
	CChar guiPath[MAX_URI_SIZE];

	if (g_editorMode == eMODE_VSCENE)
	{
		HRESULT doc_result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, packagePath);
		if (doc_result != S_OK)
		{
			PrintInfo("\nCouldn't get the documents folder", COLOR_RED);
			return 0;
		}
		else
		{
			Cpy(packageName, luaToString1);
			Cpy(guiName, luaToString2);
			Cpy(guiAndPackageName, luaToString1);
			Append(guiAndPackageName, "_");
			Append(guiAndPackageName, luaToString2);

			Cpy(guiInstanceName, "gui_");
			Append(guiInstanceName, luaToString1);
			Append(guiInstanceName, "_");
			Append(guiInstanceName, luaToString2);

			Append(packagePath, "/Vanda/GUIs/");
			Append(packagePath, luaToString1);
			Append(packagePath, "/");

			Cpy(guiPath, packagePath);
			Append(guiPath, luaToString2);
			Append(guiPath, "/");
			Append(guiPath, guiAndPackageName);
			Append(guiPath, ".gui");
		}

		for (CUInt i = 0; i < g_guis.size(); i++)
		{
			if (Cmp(g_guis[i]->GetName(), guiInstanceName))
			{
				//MessageBox(NULL, "You have already added an instance of this GUI.", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION);
				return 0;
			}
		}

		CGUI* new_gui = CNew(CGUI);

		FILE *filePtr = fopen(guiPath, "rb");
		if (filePtr)
		{
			CChar reportTemp[MAX_NAME_SIZE];
			sprintf(reportTemp, "\nLoading GUI file '%s'...", guiAndPackageName);
			PrintInfo(reportTemp, COLOR_RED_GREEN);

			SetCapture(NULL);
			SetCursor(LoadCursorFromFile("Assets/Engine/Icons/progress.ani"));

			Cpy(g_currentGUIName, luaToString2); //For save functions
			Cpy(g_currentGUIPackageName, luaToString1); //For save functions
			Cpy(g_currentPackageAndGUIName, guiAndPackageName); //For save functions
			Cpy(g_currentGUIPackagePath, packagePath);

			Cpy(ex_pVandaEngine1Dlg->m_strNewGUIName, luaToString2);
			Cpy(ex_pVandaEngine1Dlg->m_strNewGUIPackageName, luaToString1);
			Cpy(ex_pVandaEngine1Dlg->m_strNewPackageAndGUIName, guiAndPackageName);

			CUInt numberOfGUIButtons;
			CUInt numberOfGUIBackgrounds;
			CUInt numberOfGUITexts;

			fread(&numberOfGUIButtons, sizeof(CUInt), 1, filePtr);

			for (CUInt i = 0; i < numberOfGUIButtons; i++)
			{
				CChar name[MAX_NAME_SIZE];
				fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar packageName[MAX_NAME_SIZE];
				fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar guiName[MAX_NAME_SIZE];
				fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CVec2f pos;
				fread(&pos, sizeof(CVec2f), 1, filePtr);
				pos.x *= (CFloat)g_width;
				pos.y *= (CFloat)g_height;

				CInt size;
				fread(&size, sizeof(CInt), 1, filePtr);

				CChar mainImagePath[MAX_NAME_SIZE];
				fread(mainImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//disable image
				CBool hasDisableImage;
				fread(&hasDisableImage, sizeof(CBool), 1, filePtr);

				CChar disableImagePath[MAX_NAME_SIZE];
				if (hasDisableImage)
					fread(disableImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//hover image
				CBool hasHoverImage;
				fread(&hasHoverImage, sizeof(CBool), 1, filePtr);

				CChar hoverImagePath[MAX_NAME_SIZE];
				if (hasHoverImage)
					fread(hoverImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//left click image
				CBool hasLeftClickImage;
				fread(&hasLeftClickImage, sizeof(CBool), 1, filePtr);

				CChar leftClickImagePath[MAX_NAME_SIZE];
				if (hasLeftClickImage)
					fread(leftClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//right click image
				CBool hasRightClickImage;
				fread(&hasRightClickImage, sizeof(CBool), 1, filePtr);

				CChar rightClickImagePath[MAX_NAME_SIZE];
				if (hasRightClickImage)
					fread(rightClickImagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//left click script
				CBool hasLeftClickScript;
				fread(&hasLeftClickScript, sizeof(CBool), 1, filePtr);

				CChar leftClickScriptPath[MAX_NAME_SIZE];
				if (hasLeftClickScript)
					fread(leftClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//right click script
				CBool hasRightClickScript;
				fread(&hasRightClickScript, sizeof(CBool), 1, filePtr);

				CChar rightClickScriptPath[MAX_NAME_SIZE];
				if (hasRightClickScript)
					fread(rightClickScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				//hover script
				CBool hasHoverScript;
				fread(&hasHoverScript, sizeof(CBool), 1, filePtr);

				CChar hoverScriptPath[MAX_NAME_SIZE];
				if (hasHoverScript)
					fread(hoverScriptPath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CGUIButton* guiButton = CNew(CGUIButton);

				guiButton->SetName(name);
				guiButton->SetPackageName(packageName);
				guiButton->SetGUIName(guiName);
				guiButton->SetSize(size);
				guiButton->SetMainImagePath(mainImagePath);
				guiButton->LoadMainImage();
				guiButton->SetPosition(pos);
				if (hasDisableImage)
				{
					guiButton->SetDisableImagePath(disableImagePath);
					guiButton->SetHasDisableImage(CTrue);
					guiButton->LoadDisableImage();
				}
				else
				{
					guiButton->SetHasDisableImage(CFalse);
				}
				if (hasHoverImage)
				{
					guiButton->SetHoverImagePath(hoverImagePath);
					guiButton->SetHasHoverImage(CTrue);
					guiButton->LoadHoverImage();
				}
				else
				{
					guiButton->SetHasHoverImage(CFalse);
				}
				if (hasLeftClickImage)
				{
					guiButton->SetLeftClickImagePath(leftClickImagePath);
					guiButton->SetHasLeftClickImage(CTrue);
					guiButton->LoadLeftClickImage();
				}
				else
				{
					guiButton->SetHasLeftClickImage(CFalse);
				}
				if (hasRightClickImage)
				{
					guiButton->SetRightClickImagePath(rightClickImagePath);
					guiButton->SetHasRightClickImage(CTrue);
					guiButton->LoadRightClickImage();
				}
				else
				{
					guiButton->SetHasRightClickImage(CFalse);
				}
				if (hasLeftClickScript)
				{
					guiButton->SetLeftClickScriptPath(leftClickScriptPath);
					guiButton->SetHasLeftClickScript(CTrue);
				}
				else
				{
					guiButton->SetHasLeftClickScript(CFalse);
				}
				if (hasRightClickScript)
				{
					guiButton->SetRightClickScriptPath(rightClickScriptPath);
					guiButton->SetHasRightClickScript(CTrue);
				}
				else
				{
					guiButton->SetHasRightClickScript(CFalse);
				}
				if (hasHoverScript)
				{
					guiButton->SetHoverScriptPath(hoverScriptPath);
					guiButton->SetHasHoverScript(CTrue);
				}
				else
				{
					guiButton->SetHasHoverScript(CFalse);
				}
				new_gui->AddGUIButton(guiButton);
			}

			fread(&numberOfGUIBackgrounds, sizeof(CUInt), 1, filePtr);

			for (CUInt i = 0; i < numberOfGUIBackgrounds; i++)
			{
				CChar name[MAX_NAME_SIZE];
				fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar packageName[MAX_NAME_SIZE];
				fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar guiName[MAX_NAME_SIZE];
				fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CVec2f pos;
				fread(&pos, sizeof(CVec2f), 1, filePtr);
				pos.x *= (CFloat)g_width;
				pos.y *= (CFloat)g_height;

				CInt size;
				fread(&size, sizeof(CInt), 1, filePtr);

				CChar imagePath[MAX_NAME_SIZE];
				fread(imagePath, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CGUIBackground* guiBackground = CNew(CGUIBackground);
				guiBackground->SetName(name);
				guiBackground->SetPackageName(packageName);
				guiBackground->SetGUIName(guiName);
				guiBackground->SetSize(size);
				guiBackground->SetImagePath(imagePath);
				guiBackground->LoadBackgroundImage();
				guiBackground->SetPosition(pos);

				new_gui->AddGUIBackground(guiBackground);
			}

			fread(&numberOfGUITexts, sizeof(CUInt), 1, filePtr);

			for (CUInt i = 0; i < numberOfGUITexts; i++)
			{
				CChar name[MAX_NAME_SIZE];
				fread(name, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar packageName[MAX_NAME_SIZE];
				fread(packageName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CChar guiName[MAX_NAME_SIZE];
				fread(guiName, sizeof(CChar), MAX_NAME_SIZE, filePtr);

				CVec2f pos;
				fread(&pos, sizeof(CVec2f), 1, filePtr);
				pos.x *= (CFloat)g_width;
				pos.y *= (CFloat)g_height;

				CInt size;
				fread(&size, sizeof(CInt), 1, filePtr);

				CChar text[MAX_URI_SIZE];
				fread(text, sizeof(CChar), MAX_URI_SIZE, filePtr);

				CVec3f color;
				fread(&color, sizeof(CVec3f), 1, filePtr);

				CFontType font;
				fread(&font, sizeof(CFontType), 1, filePtr);

				CGUIText* guiText = CNew(CGUIText);
				guiText->SetName(name);
				guiText->SetPackageName(packageName);
				guiText->SetGUIName(guiName);
				guiText->SetPosition(pos);
				guiText->SetSize(size);
				guiText->SetColor(color);
				guiText->SetText(text);
				guiText->SetType(font);
				if (!guiText->SetFont())
				{
					CDelete(guiText);
				}

				new_gui->AddGUIText(guiText);
			}
			new_gui->SetName(guiInstanceName);
			new_gui->SetGUIName(g_currentGUIName);
			new_gui->SetPackageName(g_currentGUIPackageName);
			new_gui->SetVisible(CFalse);
			new_gui->SetLoadedFromScript(CTrue);

			g_guis.push_back(new_gui);

			CChar tempInstanceName[MAX_NAME_SIZE];
			sprintf(tempInstanceName, "%s%s%s", "\nGUI Instance ' ", new_gui->GetName(), " ' created successfully");
			PrintInfo(tempInstanceName, COLOR_GREEN);

			fclose(filePtr);
			ReleaseCapture();
		}
		else
		{
			CChar path[MAX_URI_SIZE];
			sprintf(path, "\nCouldn't open the file ' %s '", guiPath);
			PrintInfo(path, COLOR_RED);
			CDelete(new_gui);
			return 0;
		}
	}

	return 1;
}

CInt ShowGUI(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify 1 argument for ShowGUI()", COLOR_RED);
		return 0;
	}
	CBool foundTarget = CFalse;
	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_guis.size(); i++)
	{
		CChar gui[MAX_NAME_SIZE];
		Cpy(gui, g_guis[i]->GetName());
		StringToUpper(gui);

		if (Cmp(gui, luaToString))
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nGUI '", g_guis[i]->GetName(), "' was activated.");
			PrintInfo(temp, COLOR_GREEN);

			g_guis[i]->SetVisible(CTrue);

			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "\nCoudn't find the GUI '", luaToString, "' to be activated.");
		PrintInfo(temp, COLOR_RED);
	}

	return 1;
}

CInt HideGUI(lua_State* L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify 1 argument for HideGUI()", COLOR_RED);
		return 0;
	}
	CBool foundTarget = CFalse;
	//find the scene
	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString);

	for (CUInt i = 0; i < g_guis.size(); i++)
	{
		CChar gui[MAX_NAME_SIZE];
		Cpy(gui, g_guis[i]->GetName());
		StringToUpper(gui);

		if (Cmp(gui, luaToString))
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "%s%s%s", "\nGUI '", g_guis[i]->GetName(), "' was deactivated.");
			PrintInfo(temp, COLOR_GREEN);

			g_guis[i]->SetVisible(CFalse);

			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "\nCoudn't find the GUI '", luaToString, "' to be deactivated.");
		PrintInfo(temp, COLOR_RED);
	}

	return 1;
}

CInt ShowIcon(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 2)
	{
		PrintInfo("\nPlease specify 2 arguments for ShowIcon()", COLOR_RED);
		return 0;
	}

	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString); //package name

	CBool foundTarget = CFalse;
	for (CUInt i = 0; i < g_resourceFiles.size(); i++)
	{
		if (g_resourceFiles[i]->GetImage())
		{
			CChar string[MAX_NAME_SIZE];
			Cpy(string, g_resourceFiles[i]->GetName());
			StringToUpper(string); //package name

			if (Cmp(string, luaToString))
			{
				g_multipleView->m_icon->SetVisible(CTrue);
				g_multipleView->m_icon->SetName(string);
				g_multipleView->m_icon->SetImage(g_resourceFiles[i]->GetImage());
				g_multipleView->m_icon->SetSize(lua_tonumber(L, 2));

				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nMouse icon '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be shown.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "\nCouldn't find the image '", lua_tostring(L, 1), "' to be shown.");
		PrintInfo(temp, COLOR_RED);
	}

	return 1;
}

CInt HideIcon(lua_State *L)
{
	if (g_testScript)
		return 0;

	int argc = lua_gettop(L);
	if (argc < 1)
	{
		PrintInfo("\nPlease specify 1 argument for ShowIcon()", COLOR_RED);
		return 0;
	}

	CChar luaToString[MAX_NAME_SIZE];
	Cpy(luaToString, lua_tostring(L, 1));
	StringToUpper(luaToString); //package name

	CBool foundTarget = CFalse;
	for (CUInt i = 0; i < g_resourceFiles.size(); i++)
	{
		if (g_resourceFiles[i]->GetImage())
		{
			CChar string[MAX_NAME_SIZE];
			Cpy(string, g_resourceFiles[i]->GetName());
			StringToUpper(string); //package name

			if (Cmp(string, luaToString))
			{
				g_multipleView->m_icon->SetVisible(CFalse);
				//CChar temp[MAX_NAME_SIZE];
				//sprintf(temp, "%s%s%s", "\nMouse icon '", g_resourceFiles[i]->GetSoundSource()->GetName(), "' will be hidden.");
				//PrintInfo(temp, COLOR_YELLOW);
				foundTarget = CTrue;
				break;
			}
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "%s%s%s", "\nCouldn't find the image '", lua_tostring(L, 1), "' to be hidden.");
		PrintInfo(temp, COLOR_RED);
	}

	return 1;
}

CMultipleWindows::CMultipleWindows()
: m_multiSample(CFalse)
, m_grid( CTrue )
, m_numSamples( 8 )
, m_lMouseDown(CFalse)
,m_rMouseDown(CFalse)
,m_mMouseDown(CFalse)
,m_selectObject(CTrue)
,m_tempMovement(CFalse)
,m_tempSelectedName( -1 )
,m_lastSelectedName( -1 )
,m_loadData( CTrue )
,m_dynamicShadowMap(NULL)
,m_timerCounter(0)
,m_lockInput(CFalse)
,m_loadScene(CFalse)
,m_isPlayingGame(CFalse)
, m_renderQuery(CFalse)
, m_characterRotationTransition(CFalse)
, m_previousCharacterRotation(0.0f)
, m_firstIdleCounter(0)
, m_idleCounter(0.0f)
{
	m_selectedGUIIndex = -1;
	m_icon = CNew(CIcon);
}

CMultipleWindows::~CMultipleWindows()
{
	CDelete(m_icon);

	glDeleteTextures(eGBUFFER_NUM_TEXTURES, &m_textureTarget[0] );								
	glDeleteTextures(1, &m_textureTargetSwapLights);								
	glDeleteTextures(1, &m_textureTargetSumLighting);								
	glDeleteTextures(1, &m_textureFogDof);								

	glDeleteFramebuffersEXT( 1, &m_mFboID );
	glDeleteFramebuffersEXT( 1, &m_mFboID2 );
	glDeleteFramebuffersEXT( 1, &m_fboID );
	glDeleteFramebuffersEXT( 1, &m_fboID2 );
	glDeleteFramebuffersEXT( 1, &m_fboIDSum );
	glDeleteFramebuffersEXT( 1, &m_fboIDFogDof );
	glDeleteFramebuffersEXT( 1, &m_mFboIDFogDof );
	
	CDelete( g_translateArrow );
	CDelete( g_negativeZArrow );
	CDelete (g_scaleArrow);
	CDelete(g_rotateArrow);
	CDelete( g_centerArrowScene );
	CDelete( g_soundImg );
	CDelete( g_pointLightImg );
	CDelete( g_directionalLightImg );
	CDelete( g_spotLightImg );
	CDelete( g_pointLightCOLLADAImg );
	CDelete( g_directionalLightCOLLADAImg );
	CDelete( g_spotLightCOLLADAImg );
	CDelete( g_waterImg );
	CDelete( g_skyImg );
	CDelete( g_cameraImg );

	CDelete( m_translationController );
	CDelete(g_mainCharacter);
	//Release physX here
	if( m_nx )
	{
		m_nx->releaseNx();
		delete m_nx;
		m_nx = NULL;
	}
	//Release Audio
	CDelete( m_ambientSound );
	CDelete(m_soundSystem );

	//Release input here
	m_inputSystem->UnacquireAll();
	m_inputSystem->Shutdown();
	CDelete( m_inputSystem );

	CDelete( g_camera );
	CDelete( m_dynamicShadowMap );
	g_octree->ResetState();
	m_dof.DeleteFBOs();
	m_simpleFont.Release();
	m_simpleFont2.Release();
	distance_vector.clear();
	sorted_prefabs.clear();
	KillTimer( 1 );
}


BEGIN_MESSAGE_MAP(CMultipleWindows, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()

	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

// CMultipleWindows message handlers

CInt CMultipleWindows::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  Add your specialized creation code here
	// Can we put this in the constructor?
  
	CInt PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	memset (&pfd, 0, sizeof(pfd));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits	= 24;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits	= 32;
	pfd.cStencilBits = 0;

	//Get a DC for the Client Area
    m_pDC = new CClientDC(this);

    //Failure to Get DC
    if(m_pDC == NULL) {
        MessageBox(_T("Failure to Get DC"));
        return -1;
	}
	if( m_multiSample )
	{
		switch( g_options.m_numSamples )
		{
			case 2:
				m_numSamples = 2;
				break;
			case 4:
				m_numSamples = 4;
				break;
			case 8:
				m_numSamples = 8;
				break;
			case 16:
				m_numSamples = 16;
				break;
			default:
				m_numSamples = 0;
		}
		GLint samples;
		glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
		if( m_numSamples > (CInt)samples )
			m_numSamples = samples;
		if( WGLEW_ARB_pixel_format )
		{
			CFloat fAttributes[] = {0,0};
			UINT numFormats;
			CInt attributes[] = {
				WGL_DRAW_TO_WINDOW_ARB,GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB,GL_TRUE,
				WGL_ACCELERATION_ARB,WGL_FULL_ACCELERATION_ARB,
				WGL_COLOR_BITS_ARB,24,
				WGL_ALPHA_BITS_ARB,8,
				WGL_DEPTH_BITS_ARB,24,
				WGL_STENCIL_BITS_ARB,0,
				WGL_DOUBLE_BUFFER_ARB,GL_TRUE,
				WGL_SAMPLE_BUFFERS_ARB,1,
				WGL_SAMPLES_ARB, m_numSamples ,						// Check For m_numSamplesX Multisampling
				0,0
			};

			wglChoosePixelFormatARB( m_pDC->GetSafeHdc(), attributes, fAttributes, 1, &PixelFormat, &numFormats );
			if( numFormats == 0 )
			{
				AfxMessageBox( "Couldn't initialize your window with your desired samples");
				CInt temp = m_numSamples / 2;
				//Test for 2 samples
				while( numFormats == 0 )
				{
					if( temp < 2 )
					{
						m_multiSample = CFalse;
						break;
					}
					attributes[19] = temp;
					wglChoosePixelFormatARB( m_pDC->GetSafeHdc(), attributes, fAttributes, 1, &PixelFormat, &numFormats );
					temp = m_numSamples / 2 ;
				}
				if( numFormats == 0 )
					AfxMessageBox( "Couldn't support multisampling" );
				else
					AfxMessageBox( "I could enable multisampling with lower samples" );
			}
		}
		else
		{
			AfxMessageBox( "Couldn't support multisampling" );
			m_multiSample = CFalse;
		}

	}//if( multisampling )

	if( !m_multiSample )
	{
		PixelFormat = ChoosePixelFormat( m_pDC->GetSafeHdc(), &pfd);
		if (PixelFormat == 0)
		{	
			AfxMessageBox("Couldn't choose the pixel format.");
			delete m_pDC;
			m_pDC = NULL;
			return (-1);							
		}
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), PixelFormat, &pfd ) == FALSE)	
	{
		AfxMessageBox("Couldn't set the pixel format.");
		delete m_pDC;
		m_pDC = NULL;
		return (-1);							
	}
	m_hRC = wglCreateContext( m_pDC->GetSafeHdc() );
	if ( m_hRC == NULL)
	{
		AfxMessageBox("Couldn't create the OpenGL context.");
		delete m_pDC;
		m_pDC = NULL;
		return (-1);								
	}

	if (!wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))					
	{
		AfxMessageBox("Couldn't make a stream between HDC and HRC.");
		wglDeleteContext(m_hRC);
		delete m_pDC;
		m_pDC = NULL;
		m_hRC = NULL;
		return (-1);								
	}
	//if( !InitAll() )
	//	return (-1);
	return (1);
}

CBool CMultipleWindows::InitAll()
{
	for( CInt i = 0; i < 8; i++ )
	{
		glEnable(GL_LIGHT0 + i);	 //just for per vertex lighting 	

		//This is the properties of the camera light
		GLfloat light_pos0[4] = {0.0f, 0.0f, 0.0f, 0.0f };
		GLfloat light_ambient0[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		GLfloat light_diffuse0[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat light_specular0[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

		glLightfv( GL_LIGHT0 + i, GL_POSITION, light_pos0  );
		glLightfv( GL_LIGHT0 + i, GL_AMBIENT , light_ambient0 );
		glLightfv( GL_LIGHT0 + i, GL_DIFFUSE , light_diffuse0 );
		glLightfv( GL_LIGHT0 + i, GL_SPECULAR, light_specular0 );
		glLightf ( GL_LIGHT0 + i, GL_SPOT_CUTOFF,(GLfloat)180.0f );
		glLightf ( GL_LIGHT0 + i, GL_CONSTANT_ATTENUATION , (GLfloat)0.0f );
		glLightf ( GL_LIGHT0 + i, GL_LINEAR_ATTENUATION,	(GLfloat)0.0f );
		glLightf ( GL_LIGHT0 + i, GL_QUADRATIC_ATTENUATION, (GLfloat)0.0f );
	}
	glShadeModel(GL_SMOOTH);										// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);							// Black Background
	glClearDepth( 1.0 );

	//glEnable(GL_TEXTURE_2D);							
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK ); 
	glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR );
	GLfloat globalAmbientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbientLight );
	glEnable( GL_NORMALIZE );

	CFog fog;
	fog.SetColor( g_fogProperties.m_fogColor );
	fog.SetDensity( g_fogProperties.m_fogDensity );

	if( m_multiSample )
		glDisable( GL_MULTISAMPLE );
	//glDrawBuffer( GL_BACK );

	if( !m_dynamicShadowMap )
	{
		m_dynamicShadowMap = CNew( CShadowMap );
		g_dynamicShadowMap = m_dynamicShadowMap;
		if( m_dynamicShadowMap->Init() )
			g_render.m_useDynamicShadowMap = CTrue;
		else
		{
			g_render.m_useDynamicShadowMap = CFalse;
		}
	}

	// I use this variable to load the data once. We may destroy and create the window multiple times,
	// But we don't need to load and unload some data for multiple times
	if( m_loadData ) 
	{
		m_dof.InitFBOs( g_width, g_height );
		g_octree = CNew( COctree );
		//g_updateOctree = CTrue;
		//initialize audio
		// Position of the listener.
		m_listenerPos[0] = m_listenerPos[1] = m_listenerPos[2] = 0.0f;
		// Velocity of the listener.
		m_listenerVel[0] = m_listenerVel[1] = m_listenerVel[2] =  0.0f;
		// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
		m_listenerOri[0] = 0.0f;
		m_listenerOri[1] = 0.0f;
		m_listenerOri[2] = 1.0f;
		m_listenerOri[3] = 0.0f;
		m_listenerOri[4] = 1.0f;
		m_listenerOri[5] = 0.0f;

		g_soundSystem = m_soundSystem = CNew(COpenALSystem);
		m_soundSystem->Init();
		m_ambientSound = NULL;
		alDistanceModel( AL_INVERSE_DISTANCE );

		//initialize input
		m_inputSystem = new CInputSystem();
		m_inputSystem->AcquireAll();

		if( !m_inputSystem->Initialize( CWnd::m_hWnd, AfxGetInstanceHandle(), true, IS_USEKEYBOARD | IS_USEMOUSE ) )
		{
			MessageBox( "Couldn't initialize Input Engine", "Vanda Engine Error", MB_OK );
			return false;
		}
		else
			PrintInfo( "\nKeyboard and Mouse manager initialized successfully", COLOR_WHITE );

		//Initialize physX here

		m_nx = new CNovodex();

		if (!m_nx->initNx(0.0, g_physXProperties.m_fCapsuleHeight * 0.5f, 0.0, g_physXProperties.m_fGravityY, g_physXProperties.m_fCapsuleRadius, g_physXProperties.m_fCapsuleHeight, g_physXProperties.m_fCharacterSlopeLimit, g_physXProperties.m_fCharacterSkinWidth, g_physXProperties.m_fCharacterStepOffset))
		{
			MessageBox( "Couldn't initialize physX", "Vanda Engine Error", MB_OK );
			return false;
		}
		else
		{
			char temp[MAX_NAME_SIZE];
			sprintf( temp, "\nPhysX version %i.%i.%i initialized successfully", NX_SDK_VERSION_MAJOR, NX_SDK_VERSION_MINOR, NX_SDK_VERSION_BUGFIX );
			PrintInfo( temp, COLOR_WHITE );
		}

		if( !timer.Init() )
		{
			MessageBox( "Couldn't initialize timer.", "Vanda Engine Error", MB_OK | MB_ICONINFORMATION );
			return false; 
		}
		else
			PrintInfo( "\nTimer initialized successfully\n", COLOR_WHITE );

		if (!m_simpleFont.Init("Arial", 14))
		{
			MessageBox("Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
			return false;
		}
		if (!m_simpleFont2.Init("Arial", 13))
		{
			MessageBox("Couldn't initialize the font", "VandaEngine Error", MB_OK | MB_ICONINFORMATION);
			return false;
		}
		g_camera = new CUpdateCamera();
		m_loadData = CFalse;
	}
	SetTimer( 1, 1, 0 );
	m_enableTimer = CTrue;
	SetElapsedTimeFromBeginning(); //reset the timer
	g_translateArrow = CNew( CScene );
	//Load Default Arrows
	g_reportInfo = CFalse;

	g_shareGeometriesBetweenScenes = CFalse;
	if( !g_translateArrow->Load( "Assets/engine/Arrows/ArrowTranslate.dae", CFalse ) )
	{
		PrintInfo( "\nCouldn't load the arrows", COLOR_RED );
		//return false;
	}
	g_render.SetScene( g_translateArrow );
	g_translateArrow->Update();

	g_scaleArrow = CNew( CScene );
	if( !g_scaleArrow->Load( "Assets/engine/Arrows/ArrowScale.dae", CFalse ) )
	{
		PrintInfo("\nCouldn't load the Scale arrow", COLOR_RED);
		//return false;
	}
	g_render.SetScene(g_scaleArrow);
	g_scaleArrow->Update();

	g_rotateArrow = CNew(CScene);
	if (!g_rotateArrow->Load("Assets/engine/Arrows/ArrowRotate.dae", CFalse))
	{
		PrintInfo("\nCouldn't load the Rotate arrow", COLOR_RED);
		//return false;
	}
	g_render.SetScene(g_rotateArrow);
	g_rotateArrow->Update();

	g_negativeZArrow = CNew( CScene );
	if( !g_negativeZArrow->Load( "Assets/engine/Arrows/NegativeZArrow.dae", CFalse ) )
	{
		PrintInfo( "\nCouldn't load the negative Z arrow", COLOR_RED );
		return false;
	}
	g_render.SetScene( g_negativeZArrow );
	g_negativeZArrow->Update();

	g_centerArrowScene = CNew( CScene );
	//Load Default Arrows
	if( !g_centerArrowScene->Load( "Assets/engine/Arrows/ArrowCenter.dae", CFalse ) )
	{
		PrintInfo( "\nCouldn't load the arrows", COLOR_RED );
		return false;
	}
	g_render.SetScene( g_centerArrowScene );
	g_shareGeometriesBetweenScenes = CTrue;
	g_reportInfo = CTrue;

	g_centerArrowScene->Update();
	m_translationController = CNew( CMouseTranslationController );
	//Load Default Textures
	GenerateDefaultTextures();
	return true;

}

CBool CMultipleWindows::GenerateDefaultTextures()
{
	g_soundImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_soundImg, "Assets/Engine/Icons/sound.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the sound texture");
		return CFalse;
	}
	g_soundImg->SetFileName( "sound.dds" );

	//point light
	g_pointLightImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_pointLightImg, "Assets/Engine/Icons/point_light.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the point light texture");
		return CFalse;
	}
	g_pointLightImg->SetFileName( "point_light.dds" );

	//directional light
	g_directionalLightImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_directionalLightImg, "Assets/Engine/Icons/directional_light.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the directional light texture");
		return CFalse;
	}
	g_directionalLightImg->SetFileName( "directional_light.dds" );

	//spot light
	g_spotLightImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_spotLightImg, "Assets/Engine/Icons/spot_light.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the spot light texture");
		return CFalse;
	}
	g_spotLightImg->SetFileName( "spot_light.dds" );

	//COLLADA icons
	//point light
	g_pointLightCOLLADAImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_pointLightCOLLADAImg, "Assets/Engine/Icons/point_light_collada.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the point_light_collada texture");
		return CFalse;
	}
	g_pointLightCOLLADAImg->SetFileName( "point_light_collada.dds" );

	//directional light
	g_directionalLightCOLLADAImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_directionalLightCOLLADAImg, "Assets/Engine/Icons/directional_light_collada.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the directional_light_collada texture");
		return CFalse;
	}
	g_directionalLightCOLLADAImg->SetFileName( "directional_light_collada.dds" );

	//spot light
	g_spotLightCOLLADAImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_spotLightCOLLADAImg, "Assets/Engine/Icons/spot_light_collada.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the spot_light_collada texture");
		return CFalse;
	}
	g_spotLightCOLLADAImg->SetFileName( "spot_light_collada.dds" );
	//////////////////
	g_skyImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_skyImg, "Assets/Engine/Icons/sky.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the sky texture");
		return CFalse;
	}
	g_skyImg->SetFileName( "sky.dds" );

	g_waterImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_waterImg, "Assets/Engine/Icons/water.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the water texture");
		return CFalse;
	}
	g_waterImg->SetFileName( "water.dds" );
	//camera
	g_cameraImg = CNew( CImage );
	if(!CTexture::LoadDDSTexture( g_cameraImg, "Assets/Engine/Icons/camera.dds", NULL ) )
	{
		PrintInfo( "\nGenerateDefaultTextures>Couldn't load the camera texture");
		return CFalse;
	}
	g_cameraImg->SetFileName( "camera.dds" );

	return CTrue;
}

CVoid CMultipleWindows::OnSize(UINT nType, CInt cx, CInt cy)
{
	CWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_width = cx;
	m_height = cy;
}

CVoid CMultipleWindows::OnDestroy()
{

	wglMakeCurrent( NULL, NULL );
	if( m_hRC )
		wglDeleteContext( m_hRC );
	if( m_pDC )
		delete m_pDC;
	CWnd::OnDestroy();

}

CVoid CMultipleWindows::OnPaint()
{
	CPaintDC dc(this); // device context for paCInting
	// TODO: Add your message handler code here
	RenderWindow();
}

CVoid CMultipleWindows::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CWnd::OnTimer(nIDEvent);
	OnPaint();
}

CVoid CMultipleWindows::OnLButtonDown(UINT nFlags, CPoint point )
{
	if (g_editorMode == eMODE_GUI && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt k = 0; k < g_guiButtons.size(); k++)
		{
			if (g_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
			{
				if (g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_DISABLE)
				{
					if (g_guiButtons[k]->GetHasLeftClickImage())
					{
						g_multipleView->timer.GetElapsedSeconds2(CTrue);
						g_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_LEFT_CLICK);
					}
				}
			}
		}
	}
	if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt i = 0; i < g_guis.size(); i++)
		{
			for (CUInt k = 0; k < g_guis[i]->m_guiButtons.size(); k++)
			{
				if (g_guis[i]->m_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
				{
					if (g_guis[i]->m_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_DISABLE)
					{
						if (g_guis[i]->m_guiButtons[k]->GetHasLeftClickImage())
						{
							g_multipleView->timer.GetElapsedSeconds2(CTrue);
							g_guis[i]->m_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_LEFT_CLICK);
						}
					}
				}
			}
		}
	}

	if (g_editorMode == eMODE_GUI && g_currentCameraType != eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		m_lMouseDown = CTrue;
		m_mousePosition = point;  //It's used for selection
		m_mouseOldPosition = point;
		SetCapture();
		SetFocus();
		m_currentCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_MOVE));
		SetCursor(m_currentCursor);
		if (m_selectedGUIIndex != -1)
		{
			ex_pVandaEngine1Dlg->m_editX.EnableWindow(TRUE);
			ex_pVandaEngine1Dlg->m_editY.EnableWindow(TRUE);

			CBool foundTarget = CFalse;
			for (CUInt k = 0; k < g_guiBackgrounds.size(); k++)
			{
				if (g_guiBackgrounds[k]->GetIndex() == m_selectedGUIIndex)
				{
					COLORREF color = COLOR_WHITE;
					CHARFORMAT cf;
					cf.dwMask = CFM_COLOR/* | CFM_SIZE*/;
					cf.dwEffects = NULL;
					cf.crTextColor = color;

					ex_pStaticSelectedObject->SetWindowTextA("\n");
					CInt nSel = ex_pStaticSelectedObject->GetWindowTextLength();
					ex_pStaticSelectedObject->SetSel(nSel, nSel);

					ex_pStaticSelectedObject->SetSelectionCharFormat(cf);

					ex_pVandaEngine1Dlg->m_staticSelectedObject.ReplaceSel(g_guiBackgrounds[k]->GetName());

					CChar posX[MAX_NAME_SIZE];
					CChar posY[MAX_NAME_SIZE];
					CVec2f position = g_guiBackgrounds[k]->GetPosition();
					sprintf(posX, "%.0f", position.x);
					sprintf(posY, "%.0f", position.y);

					ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
					ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);

					foundTarget = CTrue;
				}
			}
			if (!foundTarget)
			{
				for (CUInt k = 0; k < g_guiButtons.size(); k++)
				{
					if (g_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
					{
						COLORREF color = COLOR_WHITE;
						CHARFORMAT cf;
						cf.dwMask = CFM_COLOR/* | CFM_SIZE*/;
						cf.dwEffects = NULL;
						cf.crTextColor = color;

						ex_pStaticSelectedObject->SetWindowTextA("\n");
						CInt nSel = ex_pStaticSelectedObject->GetWindowTextLength();
						ex_pStaticSelectedObject->SetSel(nSel, nSel);

						ex_pStaticSelectedObject->SetSelectionCharFormat(cf);

						ex_pVandaEngine1Dlg->m_staticSelectedObject.ReplaceSel(g_guiButtons[k]->GetName());

						CChar posX[MAX_NAME_SIZE];
						CChar posY[MAX_NAME_SIZE];
						CVec2f position = g_guiButtons[k]->GetPosition();
						sprintf(posX, "%.0f", position.x);
						sprintf(posY, "%.0f", position.y);

						ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
						ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);

						foundTarget = CTrue;
					}
				}
			}
			if (!foundTarget)
			{
				for (CUInt k = 0; k < g_guiTexts.size(); k++)
				{
					if (g_guiTexts[k]->GetIndex() == m_selectedGUIIndex)
					{
						COLORREF color = COLOR_WHITE;
						CHARFORMAT cf;
						cf.dwMask = CFM_COLOR/* | CFM_SIZE*/;
						cf.dwEffects = NULL;
						cf.crTextColor = color;

						ex_pStaticSelectedObject->SetWindowTextA("\n");
						CInt nSel = ex_pStaticSelectedObject->GetWindowTextLength();
						ex_pStaticSelectedObject->SetSel(nSel, nSel);

						ex_pStaticSelectedObject->SetSelectionCharFormat(cf);

						ex_pVandaEngine1Dlg->m_staticSelectedObject.ReplaceSel(g_guiTexts[k]->GetName());

						CChar posX[MAX_NAME_SIZE];
						CChar posY[MAX_NAME_SIZE];
						CVec2f position = g_guiTexts[k]->GetPosition();
						sprintf(posX, "%.0f", position.x);
						sprintf(posY, "%.0f", position.y);

						ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
						ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);

						foundTarget = CTrue;
					}
				}
			}
		}
		else
		{
			COLORREF color = COLOR_WHITE;
			CHARFORMAT cf;
			cf.dwMask = CFM_COLOR/* | CFM_SIZE*/;
			cf.dwEffects = NULL;
			cf.crTextColor = color;

			ex_pStaticSelectedObject->SetWindowTextA("\n");
			CInt nSel = ex_pStaticSelectedObject->GetWindowTextLength();
			ex_pStaticSelectedObject->SetSel(nSel, nSel);

			ex_pStaticSelectedObject->SetSelectionCharFormat(cf);

			ex_pVandaEngine1Dlg->m_staticSelectedObject.ReplaceSel("Nothing Selected");

			ex_pVandaEngine1Dlg->m_editX.SetWindowTextA("\n");
			ex_pVandaEngine1Dlg->m_editY.SetWindowTextA("\n");

			//ex_pVandaEngine1Dlg->m_editX.EnableWindow(FALSE);
			//ex_pVandaEngine1Dlg->m_editY.EnableWindow(FALSE);


		}
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}
	if (g_editorMode == eMODE_GUI)
	{
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}

	ActivateCamera( point );
	m_isPlayingGame = CTrue;
	SetCapture();
	SetFocus();
	if( !m_enableTimer )
	{
		SetElapsedTimeFromBeginning();
		SetTimer( 1, 1, 0 );
	}
	if( !g_menu.m_justPerspective )
	{
		m_translateMousePosition.x = point.x * 2;
		m_translateMousePosition.y =   ( 2 * point.y )  -  g_height;
	}
	else
		m_translateMousePosition = point;

	if (g_currentCameraType == eCAMERA_DEFAULT_FREE )
	{
		CUInt m_name;
		m_name = GetSelectedObject(CTrue);
		RenderWindow();
		//check arrows
		CScene* scene = NULL;
		if (g_currentTransformType == eCTranslate)
		{
			scene = g_translateArrow;
		}
		else if (g_currentTransformType == eCRotate)
		{
			scene = g_rotateArrow;
		}
		else if (g_currentTransformType == eCScale)
		{
			scene = g_scaleArrow;
		}
		for (CUInt j = 0; j < scene->m_geometries.size(); j++)
		{
			CGeometry* m_geometry = scene->m_geometries[j];
			if (g_menu.m_geometryBasedSelection)
			{
				CBool selected = CFalse;
				for (CUInt k = 0; k < scene->m_geometries[j]->m_instanceGeometries.size(); k++)
				{
					if (scene->m_geometries[j]->m_instanceGeometries[k]->m_nameIndex == m_name)
					{
						selected = CTrue;
						break;
					}
				}
				if (selected)
				{
					g_render.SetSelectedScene(scene);
					g_lastEngineObjectSelectedName = g_tempLastEngineObjectSelectedName;

					g_transformObject = CTrue; //we are in transformation mode ( not in selection mode )
					if (Cmp(scene->m_geometries[j]->GetName(), "geom-XAXIS"))
					{
						if (g_currentTransformType == eCTranslate || g_currentTransformType == eCScale)
						{
							g_transformDirection = XTRANS/*XYTRANS*/;
						}
						else
						{
							g_transformDirection = ZXTRANS;
						}
					}
					else if (Cmp(scene->m_geometries[j]->GetName(), "geom-YAXIS"))
					{
						if (g_currentTransformType == eCTranslate || g_currentTransformType == eCScale)
						{
							g_transformDirection = ZTRANS/*ZXTRANS*/;
						}
						else
						{
							g_transformDirection = XYTRANS;
						}
					}
					else if (Cmp(scene->m_geometries[j]->GetName(), "geom-ZAXIS"))
					{
						if (g_currentTransformType == eCTranslate || g_currentTransformType == eCScale)
						{
							g_transformDirection = YTRANS/*YZTRANS*/;
						}
						else
						{
							g_transformDirection = YZTRANS;
						}
					}
					else if (Cmp(scene->m_geometries[j]->GetName(), "geom-XYZ"))
					{
						g_transformDirection = FREETRANS;
					}

					SetDialogData(CTrue, NULL, scene->m_geometries[j], CTrue, CFalse);
				}
			}
			else //material based selection
			{
				for (CUInt k = 0; k < m_geometry->m_groups.size(); k++)
				{
					CPolyGroup* m_group = m_geometry->m_groups[k];
					if (m_group->m_nameIndex == m_name)
					{
						g_render.SetSelectedScene(scene);
						g_lastEngineObjectSelectedName = g_tempLastEngineObjectSelectedName;

						g_transformObject = CTrue; //we are in translation mode ( not in selection mode )
						if (Cmp(m_group->m_materialName, "XAXIS"))
						{
							g_transformDirection = XTRANS;
						}
						else if (Cmp(m_group->m_materialName, "YAXIS"))
						{
							g_transformDirection = ZTRANS;
						}
						else if (Cmp(m_group->m_materialName, "ZAXIS"))
						{
							g_transformDirection = YTRANS;
						}
						else if (Cmp(m_group->m_materialName, "XYZ"))
						{
							g_transformDirection = FREETRANS;
						}

						SetDialogData2(CTrue, scene->m_geometries[j]->m_groups[k], CTrue, CFalse);
					}
				}
			}
		}

		if (g_camera->m_activatePerspectiveCamera && g_transformObject && !m_translationController->Initialized())
		{
			m_translationController->Initialize((int)m_translateMousePosition.x, (int)m_translateMousePosition.y, g_transformDirection, g_arrowPosition);
		}
		m_selectObject = CTrue;
	}
	m_lMouseDown = CTrue;
	m_mousePosition = point;  //It's used for selection
	m_tempMovement = CFalse; //It's used for selection
	
	if( g_camera->m_activatePerspectiveCamera )
	{
		//if( g_camera->m_activatePerspectiveCamera && g_transformObject && !m_translationController->Initialized() )
		//	m_currentCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_UNAVAILABLE));
		//else
			m_currentCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_MOVE));
	}
	else
		m_currentCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CUSTOM_HAND));

	SetCursor( m_currentCursor );

	CWnd::OnLButtonDown(nFlags, point );
}

CVoid CMultipleWindows::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (g_editorMode == eMODE_GUI && g_currentCameraType != eCAMERA_DEFAULT_PHYSX)
	{
		if (GetCapture() == this)
			ReleaseCapture();
		m_lMouseDown = CFalse;

		CWnd::OnLButtonUp(nFlags, point);
	}
	m_isPlayingGame = CFalse;
	// TODO: Add your message handler code here and/or call default
	if( GetCapture() == this )
		ReleaseCapture();

	if (g_editorMode == eMODE_VSCENE)
	{
		if (g_transformObject && g_selectedName != -1)
		{
			for (CUInt i = 0; i < g_instancePrefab.size(); i++)
			{
				if (g_instancePrefab[i]->GetNameIndex() == g_selectedName)
				{
					g_instancePrefab[i]->CalculateDistance();
					g_multipleView->RenderQueries(CTrue);
				}
			}
		}
	}

	g_transformObject = CFalse;

	if (g_currentCameraType == eCAMERA_DEFAULT_FREE )
	{
		if (!m_tempMovement && g_camera->m_activatePerspectiveCamera)
		{

			g_lastEngineObjectSelectedName = -1;
			g_selectedName = m_tempSelectedName;
			if (g_selectedName == m_lastSelectedName)
			{
				m_lastSelectedName = g_selectedName = -1;
			}
			else
			{
				m_lastSelectedName = g_selectedName;
			}

			if (g_selectedName != -1)
			{
				CBool foundTarget = CFalse;
				if (g_editorMode == eMODE_PREFAB)
				{
					for (CUInt i = 0; i < g_scene.size(); i++)
					{
						for (CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++)
						{
							CGeometry* m_geometry = g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry;
							if (g_menu.m_geometryBasedSelection)
							{
								if (g_scene[i]->m_instanceGeometries[j]->m_nameIndex == g_selectedName)
								{
									foundTarget = CTrue;
									g_render.SetSelectedScene(g_scene[i]);
									SetDialogData(CTrue, g_scene[i]->m_instanceGeometries[j], m_geometry);
								}
							}
							else //material based selection
							{
								for (CUInt k = 0; k < m_geometry->m_groups.size(); k++)
								{
									CPolyGroup* m_group = m_geometry->m_groups[k];
									if (m_group->m_nameIndex == g_selectedName)
									{
										foundTarget = CTrue;
										g_render.SetSelectedScene(g_scene[i]);
										SetDialogData2(CTrue, g_scene[i]->m_instanceGeometries[j]->m_abstractGeometry->m_groups[k]);
									}
								}
							}
						}

					}
				}
				else
				{
					for (CUInt i = 0; i < g_instancePrefab.size(); i++)
					{
						if (g_instancePrefab[i]->GetNameIndex() == g_selectedName)
						{
							g_render.SetSelectedInstancePrefab(g_instancePrefab[i]);
							SetDialogData3(CTrue, g_instancePrefab[i]);
						}
					}

				}

				if (!foundTarget) //something like light, sound, sky or water has been selected
					SetDialogData(CFalse, NULL, NULL, CTrue);
			}
			else
			{
				if (g_editorMode == eMODE_PREFAB)
				{
					g_render.SetSelectedScene(NULL);

					if (g_menu.m_geometryBasedSelection)
					{
						SetDialogData(CFalse);
					}
					else
					{
						SetDialogData2(CFalse);
					}
				}
				else
				{
					g_render.SetSelectedInstancePrefab(NULL);
					SetDialogData3(CFalse);
				}
			}

		}
	}

	m_translationController->Finish();
	m_lMouseDown = CFalse;
	RenderWindow();
	if( !m_enableTimer )
		KillTimer(1);
	CWnd::OnLButtonUp(nFlags, point);
}

CVoid CMultipleWindows::EnableTimer( CBool enable )
{
	if( enable )
		SetTimer( 1, 1, 0 );
	else
		KillTimer( 1 );
}

CVoid CMultipleWindows::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (g_editorMode == eMODE_GUI && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt k = 0; k < g_guiButtons.size(); k++)
		{
			if (g_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
			{
				if (g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_DISABLE)
				{
					if (g_guiButtons[k]->GetHasRightClickImage())
					{
						g_multipleView->timer.GetElapsedSeconds2(CTrue);
						g_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_RIGHT_CLICK);
					}
				}
			}
		}
	}
	if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt i = 0; i < g_guis.size(); i++)
		{
			for (CUInt k = 0; k < g_guis[i]->m_guiButtons.size(); k++)
			{
				if (g_guis[i]->m_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
				{
					if (g_guis[i]->m_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_DISABLE)
					{
						if (g_guis[i]->m_guiButtons[k]->GetHasRightClickImage())
						{
							g_multipleView->timer.GetElapsedSeconds2(CTrue);
							g_guis[i]->m_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_RIGHT_CLICK);
						}
					}
				}
			}
		}
	}
	if (g_editorMode == eMODE_GUI)
	{
		CWnd::OnRButtonDown(nFlags, point);
		return;
	}


	m_isPlayingGame	= CTrue;
	ActivateCamera( point );

	if( !m_enableTimer )
	{
		SetElapsedTimeFromBeginning();
		SetTimer( 1, 1, 0 );
	}

	SetCapture();
	SetFocus();

	m_rMouseDown = CTrue;
	m_selectObject = CTrue;
	m_currentCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_ZOOMIN));

	SetCursor( m_currentCursor );
	CWnd::OnRButtonDown(nFlags, point);
}

CVoid CMultipleWindows::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_isPlayingGame = CFalse;
	// TODO: Add your message handler code here and/or call default
	if( GetCapture() == this )
		ReleaseCapture();
	m_rMouseDown = CFalse;

	if( !m_enableTimer )
		KillTimer(1);
	CWnd::OnRButtonUp(nFlags, point);
}

CVoid CMultipleWindows::OnMButtonDown(UINT nFlags, CPoint point)
{
	m_mMouseDown = CTrue;
	if(!m_isPlayingGame)
		OnLButtonDown( nFlags, point );
	else
		OnLButtonUp( nFlags, point );
	//CWnd::OnMButtonDown(nFlags, point);
}

CVoid CMultipleWindows::OnMButtonUp(UINT nFlags, CPoint point)
{
	m_mMouseDown = CFalse;

	// TODO: Add your message handler code here and/or call default
	//OnLButtonUp( nFlags, point );
	CWnd::OnMButtonUp(nFlags, point);
}

CVoid CMultipleWindows::OnMouseMove(UINT nFlags, CPoint point)
{
	if (g_editorMode == eMODE_GUI && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_mousePosition = point;

		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt k = 0; k < g_guiButtons.size(); k++)
		{
			if (g_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
			{
				if (g_guiButtons[k]->GetCurrentImageType() == eBUTTON_IMAGE_MAIN &&  g_guiButtons[k]->GetHasHoverImage())
				{
					if (g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_HOVER)
					{
						if (g_guiButtons[k]->GetHasHoverScript())
						{
							LuaLoadAndExecute(g_lua, g_guiButtons[k]->GetHoverScriptPath());
						}
					}
					g_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_HOVER);
				}
			}
			else
			{
				if (g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_DISABLE && g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_LEFT_CLICK && g_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_RIGHT_CLICK)
					g_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_MAIN);
			}
		}
		m_mouseOldPosition = m_mousePosition;
		CWnd::OnMouseMove(nFlags, point);
		return;

	}
	if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
	{
		m_selectedGUIIndex = GetSelectedGUI();
		for (CUInt i = 0; i < g_guis.size(); i++)
		{
			for (CUInt k = 0; k < g_guis[i]->m_guiButtons.size(); k++)
			{
				if (g_guis[i]->m_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
				{
					if (g_guis[i]->m_guiButtons[k]->GetCurrentImageType() == eBUTTON_IMAGE_MAIN && g_guis[i]->m_guiButtons[k]->GetHasHoverImage())
					{
						if (g_guis[i]->m_guiButtons[k]->GetCurrentImageType() != eBUTTON_IMAGE_HOVER)
						{
							if (g_guis[i]->m_guiButtons[k]->GetHasHoverScript())
							{
								LuaLoadAndExecute(g_lua, g_guis[i]->m_guiButtons[k]->GetHoverScriptPath());
							}
						}

						g_guis[i]->m_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_HOVER);
					}
				}
				else
				{
					g_guis[i]->m_guiButtons[k]->SetCurrentImageType(eBUTTON_IMAGE_MAIN);
				}
			}
		}
	}
	else if (g_editorMode == eMODE_GUI && g_currentCameraType != eCAMERA_DEFAULT_PHYSX)
	{
		if (m_selectedGUIIndex != -1 && m_lMouseDown)
		{ 
			m_mousePosition = point;

			CVec2f position;
			position.x = m_mousePosition.x - m_mouseOldPosition.x;
			position.y = m_mousePosition.y - m_mouseOldPosition.y;

			CBool foundTarget = CFalse;
			for (CUInt k = 0; k < g_guiBackgrounds.size(); k++)
			{
				if (g_guiBackgrounds[k]->GetIndex() == m_selectedGUIIndex)
				{
					g_guiBackgrounds[k]->SetPosition2(position);

					CChar posX[MAX_NAME_SIZE];
					CChar posY[MAX_NAME_SIZE];
					CVec2f position = g_guiBackgrounds[k]->GetPosition();
					sprintf(posX, "%.0f", position.x);
					sprintf(posY, "%.0f", position.y);

					ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
					ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);

					foundTarget = CTrue;
				}
			}
			if (!foundTarget)
			{
				for (CUInt k = 0; k < g_guiButtons.size(); k++)
				{
					if (g_guiButtons[k]->GetIndex() == m_selectedGUIIndex)
					{
						g_guiButtons[k]->SetPosition2(position);

						CChar posX[MAX_NAME_SIZE];
						CChar posY[MAX_NAME_SIZE];
						CVec2f position = g_guiButtons[k]->GetPosition();
						sprintf(posX, "%.0f", position.x);
						sprintf(posY, "%.0f", position.y);

						ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
						ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);

						foundTarget = CTrue;
					}
				}
			}
			if (!foundTarget)
			{
				for (CUInt k = 0; k < g_guiTexts.size(); k++)
				{
					if (g_guiTexts[k]->GetIndex() == m_selectedGUIIndex)
					{
						g_guiTexts[k]->SetPosition2(position);

						CChar posX[MAX_NAME_SIZE];
						CChar posY[MAX_NAME_SIZE];
						CVec2f position = g_guiTexts[k]->GetPosition();
						sprintf(posX, "%.0f", position.x);
						sprintf(posY, "%.0f", position.y);

						ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(posX);
						ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(posY);


						foundTarget = CTrue;
					}
				}
			}
			m_mouseOldPosition = m_mousePosition;
			CWnd::OnMouseMove(nFlags, point);
			return;

		}
	}
	m_mouseMove = CTrue;
	// TODO: Add your message handler code here and/or call default
	if (g_transformObject)
		m_tempMovement = CTrue;
	if (!g_menu.m_justPerspective)
	{
		m_translateMousePosition.x = point.x * 2;
		m_translateMousePosition.y = (2 * point.y) - g_height;
	}
	else
		m_translateMousePosition = point;

	m_mousePosition = point;


	CWnd::OnMouseMove(nFlags, point);

}

CVoid CMultipleWindows::ActivateCamera( CPoint point )
{
	if( g_menu.m_justPerspective || ( point.x < m_width / 2 && point.y > m_height / 2 ) ) //perspective window
	{
		g_camera->m_activatePerspectiveCamera = CTrue;
		g_camera->m_activateLowerRightCamera = CFalse;
		g_camera->m_activateUpperLeftCamera = CFalse;
		g_camera->m_activateUpperRightCamera = CFalse;
	}
	else if( ( point.x < m_width / 2 && point.y < m_height / 2 ) ) //upper left
	{
		g_camera->m_activatePerspectiveCamera = CFalse;
		g_camera->m_activateLowerRightCamera = CFalse;
		g_camera->m_activateUpperLeftCamera = CTrue;
		g_camera->m_activateUpperRightCamera = CFalse;
	}
	else if( ( point.x > m_width / 2 && point.y < m_height / 2 ) ) //upper right
	{
		g_camera->m_activatePerspectiveCamera = CFalse;
		g_camera->m_activateLowerRightCamera = CFalse;
		g_camera->m_activateUpperLeftCamera = CFalse;
		g_camera->m_activateUpperRightCamera = CTrue;
	}
	else if( ( point.x > m_width / 2 && point.y > m_height / 2 ) ) //lower right
	{
		g_camera->m_activatePerspectiveCamera = CFalse;
		g_camera->m_activateLowerRightCamera = CTrue;
		g_camera->m_activateUpperLeftCamera = CFalse;
		g_camera->m_activateUpperRightCamera = CFalse;
	}
}

CVoid CMultipleWindows::DrawGrid(CVoid)
{
	glUseProgram(0);
	glPushAttrib( GL_ENABLE_BIT | GL_CURRENT_BIT | GL_VIEWPORT_BIT);
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	//Draw the grid here
	glLineWidth( 1.0f );
	glColor3f( 0.4f, 0.5f, 0.4f );
	glBegin( GL_LINES );
	for( CInt index = -50; index <= 50; index += 2 )
	{
		glVertex3f( -50.0f, 0.0f, (CFloat)index );
		glVertex3f(  50.0f, 0.0f, (CFloat)index );

		glVertex3f( (CFloat)index, 0.0f, -50.0f );
		glVertex3f( (CFloat)index, 0.0f, 50.0f );
	}
	glEnd();
	glLineWidth( 3.0f );
	//Draw the axes here

	//glBegin( GL_LINES );

	//glColor3f( 1.0f, 0.0f, 0.0f );
	//glVertex3f( 0.0f, 0.0f, 0.0f );
	//glVertex3f( 1.0f, 0.0f, 0.0f );
	//
	//glColor3f( 0.0f, 1.0f, 0.0f );
	//glVertex3f( 0.0f, 0.0f, 0.0f );
	//glVertex3f( 0.0f, 1.0f, 0.0f );

	//glColor3f( 0.0f, 0.0f, 1.0f );
	//glVertex3f( 0.0f, 0.0f, 0.0f );
	//glVertex3f( 0.0f, 0.0f, 1.0f );

	//glEnd();

	glPopAttrib();
}

CVoid CMultipleWindows::DrawGUIMode()
{
	if (!g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
		g_render.BindForWriting(m_mFboID);
	else if (!g_useOldRenderingStyle && g_options.m_enableFBO)
		g_render.BindForWriting(m_fboID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (g_useOldRenderingStyle || !g_options.m_enableFBO)
	{
		if (m_multiSample) glDisable(GL_MULTISAMPLE);
	}
	else
	{
		if (m_multiSample && g_options.m_numSamples) glEnable(GL_MULTISAMPLE);
		else glDisable(GL_MULTISAMPLE);
	}

	glPushAttrib(GL_VIEWPORT_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	////Draw grids of the GUI window 
	glViewport(0, 0, m_width ,m_height );// resets the viewport to new dimensions.

	g_camera->m_cameraManager->Set2DOrtho(-100.0f, 100.0f, -100.0f, 100.0f);
	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	gluLookAt(0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.0f);
	g_render.m_useShader = CFalse;

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	for (CInt index = -100; index <= 100; index++)
	{
		CInt layer = -1;
		if (index == 0)
		{
			glColor3f(0.4f, 0.4f, 0.4f);
			layer = -49000;
		}
		else if (index % 20 == 0)
		{
			glColor3f(0.4f, 0.4f, 0.3f);
			layer = -49000;
		}
		else if (index % 5 == 0)
		{
			glColor3f(0.2f, 0.2f, 0.2f);
			layer = -49000;
		}

		if (index % 5 == 0)
		{
			glVertex3f(0.0f + (CFloat)index, -100.0f, layer);
			glVertex3f(0.0f + (CFloat)index, 100.0f, layer);

			glVertex3f(-100.0f, (CFloat)index, layer);
			glVertex3f(100.0f, (CFloat)index, layer);
		}
	}
	glEnd();

	glLineWidth(2.0f);
	g_camera->m_cameraManager->Set2DOrtho(0.0f, 1024.0f, 0.0, 768.0f);

	glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 1, 49999.0);
	glVertex3f(1024 - 1, 1, 49999.0);
	glVertex3f(1024 - 1, 768 - 1, 49999.0);
	glVertex3f(1, 768 - 1, 49999.0);
	glEnd();

	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	for (CUInt k = 0; k < g_guiBackgrounds.size(); k++)
	{
		g_guiBackgrounds[k]->Render();
	}
	for (CUInt k = 0; k < g_guiButtons.size(); k++)
	{
		g_guiButtons[k]->Render();
	}
	for (CUInt k = 0; k < g_guiTexts.size(); k++)
	{
		g_guiTexts[k]->Render();
	}

	glPopAttrib();


	if (!g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		g_render.BindForReading(m_mFboID);
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting(m_fboID);
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

		g_render.SetReadBuffer(eGBUFFER_TEXTURE_TYPE_DEFAULT);

		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (!g_useOldRenderingStyle && g_options.m_enableFBO)
	{
		glViewport(0, 0, m_width, m_height);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glUseProgram(0);
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT);
		glPushAttrib(GL_ENABLE_BIT);
		glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
		gluOrtho2D(0, g_width, 0, g_height);
		glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		glBindTexture(GL_TEXTURE_2D, m_textureTarget[0]);

		glEnable(GL_TEXTURE_2D);
		glClearColor(0.37f, 0.37f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_QUADS);
		glTexCoord2d(0, 0);	glVertex2d(0, 0);
		glTexCoord2d(1, 0);	glVertex2d(g_width, 0);
		glTexCoord2d(1, 1);	glVertex2d(g_width, g_height);
		glTexCoord2d(0, 1);	glVertex2d(0, g_height);
		glEnd();
		glUseProgram(0);

		glPopAttrib();
		glMatrixMode(GL_PROJECTION); glPopMatrix();
		glMatrixMode(GL_MODELVIEW); glPopMatrix();
	}


}

CVoid CMultipleWindows::DrawUpperLeft()
{
	glPushAttrib( GL_VIEWPORT_BIT );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	////Draw grids of the upper left window 
	glViewport( 0, m_height / 2 , m_width / 2 , m_height / 2 );// resets the viewport to new dimensions.
	g_camera->m_cameraManager->Set2DOrtho( -m_width * g_camera->m_upperLeftZoom , m_width * g_camera->m_upperLeftZoom, -m_height * g_camera->m_upperLeftZoom, m_height * g_camera->m_upperLeftZoom ); 
	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	gluLookAt( g_camera->m_upperLeftMoveHorizantal , g_camera->m_upperLeftMoveVertical, 1.0f,
		g_camera->m_upperLeftMoveHorizantal, g_camera->m_upperLeftMoveVertical,
		0.0f, 0.0f, 1.0f, 0.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glLineWidth( 1.0f );
	g_render.m_useShader = CFalse;

	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
	glBegin( GL_LINES );
	for( CInt index = -100; index <= 100; index++ )
	{
		CInt layer = -1;
		if( index == 0 )
		{
			glColor3f( 0.0f, 0.0f, 0.0f );
			layer = -49000;
		}
		else if( index % 5 ==  0 ) 
		{
			glColor3f( 0.2f, 0.2f, 0.2f );
			layer = -49000;
		}
		else
		{
			glColor3f( 0.45f, 0.45f, 0.45f );
			layer = -49001;
		}

		if( g_camera->m_upperLeftZoom > 0.05 )
		{
			if( index % 5 == 0 )
			{
				glVertex3f( 0.0f + (CFloat)index, -100.0f, layer );
				glVertex3f( 0.0f + (CFloat)index, 100.0f, layer );

				glVertex3f( -100.0f ,(CFloat)index, layer );
				glVertex3f( 100.0f,(CFloat)index, layer );
			}
		}
		else
		{
			glVertex3f( 0.0f + (CFloat)index, -100.0f, layer );
			glVertex3f( 0.0f + (CFloat)index, 100.0f, layer );

			glVertex3f( -100.0f ,(CFloat)index, layer );
			glVertex3f( 100.0f,(CFloat)index, layer );
		}
	}
	glEnd();
	glPopAttrib();

	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
			{
				if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
					continue;
			}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene)
			{
				if (prefab && prefab->GetHasLod(2))
					scene = g_instancePrefab[i]->GetScene(2);
				else if (prefab && prefab->GetHasLod(1))
					scene = g_instancePrefab[i]->GetScene(1);
				else if (prefab && prefab->GetHasLod(0))
					scene = g_instancePrefab[i]->GetScene(0);
			}
			if (!scene)
				continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);

				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(*(g_instancePrefab[i]->GetInstanceMatrix()));
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.PopMatrix();

				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);

				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}
		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);
			//g_render.GetScene()->Update();

			if (!g_scene[i]->m_isTrigger)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);
				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}
		}
	}
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	m_simpleFont.StartRendering();
	m_simpleFont.Print("Front", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
	m_simpleFont.EndRendering();
	glPopAttrib();
}

CVoid CMultipleWindows::DrawUpperRight()
{
	glPushAttrib( GL_VIEWPORT_BIT );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	//Draw grids of the upper right window 
	glViewport( m_width / 2, m_height / 2 , m_width / 2 , m_height / 2 );// resets the viewport to new dimensions.
	g_camera->m_cameraManager->Set2DOrtho( -m_width * g_camera->m_upperRightZoom, m_width * g_camera->m_upperRightZoom, -m_height * g_camera->m_upperRightZoom, m_height * g_camera->m_upperRightZoom ); 

	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	gluLookAt( 1.0, g_camera->m_upperRightMoveVertical, g_camera->m_upperRightMoveHorizantal,
		0.0f, g_camera->m_upperRightMoveVertical, g_camera->m_upperRightMoveHorizantal,
		0.0f, 1.0f, 0.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	g_render.m_useShader = CFalse;

	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );
	glLineWidth( 1.0f );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
	glBegin( GL_LINES );
	for( CInt index = -100; index <= 100; index++ )
	{
		CInt layer = -1;
		if( index == 0 )
		{
			glColor3f( 0.0f, 0.0f, 0.0f );
			layer = -49000;
		}
		else if( index % 5 ==  0 ) 
		{
			glColor3f( 0.2f, 0.2f, 0.2f );
			layer = -49000;
		}
		else
		{
			glColor3f(0.45f, 0.45f, 0.45f);
			layer = -49001;
		}

		if( g_camera->m_upperRightZoom > 0.05f )
		{
			if( index % 5 == 0 )
			{
				glVertex3f( layer, -100.f, (CFloat)index );
				glVertex3f( layer, 100.f, (CFloat)index );

				glVertex3f( layer,(CFloat)index, -100.f );
				glVertex3f( layer,(CFloat)index, 100.f );
			}
		}
		else
		{
			glVertex3f( layer, -100.f, (CFloat)index );
			glVertex3f( layer, 100.f, (CFloat)index);

			glVertex3f(  layer,(CFloat)index, -100.f );
			glVertex3f( layer,(CFloat)index, 100.f );
		}
	}
	glEnd();
	glPopAttrib();

	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
			{
				if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
					continue;
			}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene)
			{
				if (prefab && prefab->GetHasLod(2))
					scene = g_instancePrefab[i]->GetScene(2);
				else if (prefab && prefab->GetHasLod(1))
					scene = g_instancePrefab[i]->GetScene(1);
				else if (prefab && prefab->GetHasLod(0))
					scene = g_instancePrefab[i]->GetScene(0);
			}
			if (!scene)
				continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);

				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(*(g_instancePrefab[i]->GetInstanceMatrix()));
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.PopMatrix();

				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);

				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}
		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);
			//g_render.GetScene()->Update();
			if (!g_scene[i]->m_isTrigger)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);
				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}
		}
	}
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	m_simpleFont.StartRendering();
	m_simpleFont.Print( "Side", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f );
	m_simpleFont.EndRendering();
	glPopAttrib();
}

CVoid CMultipleWindows::DrawLowerRight()
{
	glPushAttrib( GL_VIEWPORT_BIT );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	//Draw grids of the lower right window 
	glViewport( m_width / 2, 0 , m_width / 2 , m_height / 2 );// resets the viewport to new dimensions.
	g_camera->m_cameraManager->Set2DOrtho( -m_width * g_camera->m_lowerRightZoom, m_width * g_camera->m_lowerRightZoom, -m_height * g_camera->m_lowerRightZoom, m_height * g_camera->m_lowerRightZoom ); 

	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	gluLookAt( g_camera->m_lowerRightMoveHorizantal, 1.0, g_camera->m_lowerRightMoveVertical,
		g_camera->m_lowerRightMoveHorizantal, 0.0f, g_camera->m_lowerRightMoveVertical,
		0.0f, 0.0f , 1.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	g_render.m_useShader = CFalse;

	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );
	glLineWidth( 1.0f );
	glBegin( GL_LINES );
	for( CInt index = -100; index <= 100; index++ )
	{
		CInt layer = -1;
		if( index == 0 )
		{
			glColor3f( 0.0f, 0.0f, 0.0f );
			layer = -49000;
		}
		else if( index % 5 ==  0 ) 
		{
			glColor3f( 0.2f, 0.2f, 0.2f );
			layer = -49000;
		}
		else
		{
			glColor3f(0.45f, 0.45f, 0.45f);
			layer = -49001;
		}

		if( g_camera->m_lowerRightZoom > 0.05 )
		{
			if( index % 5 == 0 )
			{
				glVertex3f( -100.0f, layer, (CFloat)index );
				glVertex3f(  100.0f, layer, (CFloat)index );

				glVertex3f( (CFloat)index, layer, -100.0f );
				glVertex3f( (CFloat)index, layer, 100.0f );
			}
		}
		else
		{
			glVertex3f( -100.0f, layer, (CFloat)index );
			glVertex3f(  100.0f, layer, (CFloat)index );

			glVertex3f( (CFloat)index, layer, -100.0f );
			glVertex3f( (CFloat)index, layer, 100.0f );
		}
	}
	glEnd();
	glPopAttrib();

	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
			{
				if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
					continue;
			}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene)
			{
				if (prefab && prefab->GetHasLod(2))
					scene = g_instancePrefab[i]->GetScene(2);
				else if (prefab && prefab->GetHasLod(1))
					scene = g_instancePrefab[i]->GetScene(1);
				else if (prefab && prefab->GetHasLod(0))
					scene = g_instancePrefab[i]->GetScene(0);
			}
			if (!scene)
				continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);

				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(*(g_instancePrefab[i]->GetInstanceMatrix()));
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.PopMatrix();

				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);

				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}
		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);
			//g_render.GetScene()->Update();

			if (!g_scene[i]->m_isTrigger)
			{
				g_render.GetScene()->Render(CFalse, NULL, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CTrue);
				g_render.GetScene()->RenderAnimatedModels(CFalse, CFalse);
				g_render.GetScene()->RenderModelsControlledByPhysX(CFalse);
			}

		}
	}
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	m_simpleFont.StartRendering();
	m_simpleFont.Print( "Top", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f );
	m_simpleFont.EndRendering();
	glPopAttrib();
}

CVoid CMultipleWindows::SetElapsedTimeFromBeginning()
{
	elapsedTime = timer.GetElapsedSeconds( CTrue ); //start from the beginning
	timer.GetFps( 1, CTrue );
	g_elapsedTime = elapsedTime;
	m_timerCounter  = 0;
	m_totalElapsedTime = 0;
}

CVoid CMultipleWindows::DrawPerspective()
{

	g_numVerts = 0; //debug info
	g_multipleView->UpdateAnimations();

	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
		g_render.BindForWriting(m_mFboID);
	else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
		g_render.BindForWriting( m_fboID );
	//if( !g_useOldRenderingStyle )
	//{
	//	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
	//	GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT};
	//	glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);
	//}
	//else
		glDrawBuffer( GL_BACK );

	m_cameraTypeOfPreviousFrame = m_cameraType;

	if( g_currentCameraType == eCAMERA_DEFAULT_FREE )
	{
		CInstanceCamera *instanceCamera = g_render.GetDefaultInstanceCamera();
		if (instanceCamera)
		{
			m_cameraType = eCAMERA_DEFAULT_FREE;
			SetInstanceCamera(instanceCamera, m_width / 2., m_height / 2.);
			m_lockInput = CFalse;
		}
		else
		{
			g_currentCameraType = eCAMERA_DEFAULT_PHYSX;
		}
	}
	CInstanceCamera *instanceCamera = g_render.GetActiveInstanceCamera();
	if( g_currentCameraType == eCAMERA_COLLADA )
	{
		if( instanceCamera )		
		{
			m_cameraType = eCAMERA_COLLADA;

			m_lockInput = CTrue;
			SetInstanceCamera(instanceCamera, m_width / 2., m_height / 2.);
		}
		else
		{
			g_currentCameraType = eCAMERA_DEFAULT_PHYSX;
		}
	}
	if( g_currentCameraType == eCAMERA_DEFAULT_PHYSX )
	{
		m_cameraType = eCAMERA_DEFAULT_PHYSX;

		m_lockInput = CFalse;
		g_camera->m_cameraManager->SetPerspective( g_camera->m_cameraManager->GetAngle(), m_width / 2. , m_height / 2., 0.01, 1000.0 );

		if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
		{
			//shadow
			glGetFloatv(GL_PROJECTION_MATRIX, cam_proj);
		}

		//previous position of character controller
		g_camera->m_perspectiveCharacterPosOfPreviousFrame = g_camera->m_perspectiveCharacterPos;
		m_nx->GetCameraAndCharacterPositions( g_camera->m_perspectiveCameraPitch,
			g_camera->m_perspectiveCameraYaw,
			g_camera->m_perspectiveCameraPos,
			g_camera->m_perspectiveCharacterPos,
			g_camera->m_perspectiveCameraDir );

		//Update camera position and orientation
		g_camera->m_cameraManager->UpdateCameraPosDir( g_camera->m_perspectiveCameraPos,
			g_camera->m_perspectiveCharacterPos,
			g_camera->m_perspectiveCameraDir,
			g_camera->m_perspectiveCurrentCameraTilt );

		//if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
		//{
			// store the inverse of the resulting modelview matrix for the shadow computation
			glGetFloatv(GL_MODELVIEW_MATRIX, cam_modelview);
			g_camera->m_cameraManager->GetInverseMatrix( cam_inverse_modelview );
		//}
	}


	const float bias[16] = {	0.5f, 0.0f, 0.0f, 0.0f, 
								0.0f, 0.5f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.5f, 0.0f,
								0.5f, 0.5f, 0.5f, 1.0f	};
	if (!g_useOldRenderingStyle && g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader)
	{
		//shadow
		float light_dir[4] = {g_defaultDirectionalLight.x, g_defaultDirectionalLight.y, g_defaultDirectionalLight.z , 1.0f };

		if( !instanceCamera )
		{
			cam_pos[0] = g_camera->m_perspectiveCameraPos.x;
			cam_pos[1] = g_camera->m_perspectiveCameraPos.y + g_physXProperties.m_fCapsuleHeight;
			cam_pos[2] = g_camera->m_perspectiveCameraPos.z;

			cam_dir[0] = g_camera->m_perspectiveCharacterPos.x - cam_pos[0];
			cam_dir[1] = g_camera->m_perspectiveCharacterPos.y + (g_physXProperties.m_fCapsuleHeight / 2.f ) + g_camera->m_perspectiveCurrentCameraTilt - cam_pos[1];
			cam_dir[2] = g_camera->m_perspectiveCharacterPos.z - cam_pos[2];
		}
		if( !Cmp( g_shadowProperties.m_directionalLightName, "\n" ) && g_shadowProperties.m_enable && g_render.UsingShadowShader())
			m_dynamicShadowMap->MakeShadowMap( cam_pos, cam_dir, light_dir ); 
	}

	g_camera->m_cameraManager->UpdateFrustum();

	m_calculateDistance = CFalse;
	if ( m_cameraType != m_cameraTypeOfPreviousFrame )
	{
		m_calculateDistance = CTrue;
	}
	//calculate distance between geometries and main camera
	else if( !(g_camera->m_perspectiveCharacterPosOfPreviousFrame.x - g_camera->m_perspectiveCharacterPos.x == 0.0f &&
		g_camera->m_perspectiveCharacterPosOfPreviousFrame.y - g_camera->m_perspectiveCharacterPos.y == 0.0f &&
		g_camera->m_perspectiveCharacterPosOfPreviousFrame.z - g_camera->m_perspectiveCharacterPos.z == 0.0f ) )
	{
		m_calculateDistance = CTrue;
	}
	else if( instanceCamera )
	{
		if( !(g_camera->m_perspectiveCameraPosOfPreviousFrame.x - g_camera->m_perspectiveCameraPos.x == 0.0f &&
			g_camera->m_perspectiveCameraPosOfPreviousFrame.y - g_camera->m_perspectiveCameraPos.y == 0.0f &&
			g_camera->m_perspectiveCameraPosOfPreviousFrame.z - g_camera->m_perspectiveCameraPos.z == 0.0f ) )
		{
			m_calculateDistance = CTrue;
		}
	}
	if (g_editorMode == eMODE_VSCENE/* && g_currentCameraType == eCAMERA_DEFAULT_PHYSX*/)
		UpdatePrefabInstanceBB();

	if (m_calculateDistance)
	{
		for( CUInt i = 0; i < g_scene.size(); i++ )
		{
			g_scene[i]->CalculateDistances();
		}
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			g_instancePrefab[i]->CalculateDistance();
		}
		for (CUInt i = 0; i < g_engineLights.size(); i++)
		{
			g_engineLights[i]->CalculateDistance();
		}

	}
	//audio
	m_ambientSourcePos[0] = m_listenerPos[0] = g_camera->m_perspectiveCameraPos.x;
	m_ambientSourcePos[1] = m_listenerPos[1] = g_camera->m_perspectiveCameraPos.y;
	m_ambientSourcePos[2] = m_listenerPos[2] = g_camera->m_perspectiveCameraPos.z;

	m_listenerOri[0] = -g_camera->m_perspectiveCameraDir.x;
	m_listenerOri[1] = g_camera->m_perspectiveCameraDir.y;
	m_listenerOri[2] = -g_camera->m_perspectiveCameraDir.z;

	m_soundSystem->SetListenerPosition( m_listenerPos );
	//m_soundSystem->SetListenerVelocity( m_listenerVel );
	m_soundSystem->SetListenerOrientation( m_listenerOri );
	//set ambient sound
	if(	g_menu.m_insertAmbientSound )
		m_ambientSound->GetSoundSource()->SetSoundPosition( m_ambientSourcePos );

	if( g_polygonMode == ePOLYGON_LINE )
	{
		g_render.m_useShader = CFalse;
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glDisable(GL_LIGHTING );
		glDisable(GL_CULL_FACE );
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_MULTISAMPLE );
		glLineWidth(0.5f);
	}
	else if( g_polygonMode == ePOLYGON_POINT )
	{
		g_render.m_useShader = CFalse;
		glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
		glDisable(GL_LIGHTING );
		glDisable(GL_CULL_FACE );
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_MULTISAMPLE );
		glPointSize(1.0);
	}
	else if( g_polygonMode == ePOLYGON_FILL )
	{
		g_render.m_useShader = CTrue;
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	glPushAttrib(GL_LIGHTING_BIT);

	//create all the water textures here
	if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		for( CUInt i = 0 ; i < g_engineWaters.size(); i++ )
		{
			CVec3f waterPoints[4];
			waterPoints[0].x = g_engineWaters[i]->m_sidePoint[0].x;waterPoints[0].y = g_engineWaters[i]->m_sidePoint[0].y;waterPoints[0].z = g_engineWaters[i]->m_sidePoint[0].z;
			waterPoints[1].x = g_engineWaters[i]->m_sidePoint[1].x;waterPoints[1].y = g_engineWaters[i]->m_sidePoint[1].y;waterPoints[1].z = g_engineWaters[i]->m_sidePoint[1].z;
			waterPoints[2].x = g_engineWaters[i]->m_sidePoint[2].x;waterPoints[2].y = g_engineWaters[i]->m_sidePoint[2].y;waterPoints[2].z = g_engineWaters[i]->m_sidePoint[2].z;
			waterPoints[3].x = g_engineWaters[i]->m_sidePoint[3].x;waterPoints[3].y = g_engineWaters[i]->m_sidePoint[3].y;waterPoints[3].z = g_engineWaters[i]->m_sidePoint[3].z;

			if( g_camera->m_cameraManager->IsBoxInFrustum( waterPoints, 4 ) )
			{
				g_engineWaters[i]->CreateReflectionTexture(g_waterTextureSize );
				//g_engineWaters[i]->CreateRefractionDepthTexture(g_waterTextureSize );
			}
		}
	}
	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
		g_render.BindForWriting(m_mFboID);
	else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
		g_render.BindForWriting( m_fboID );

	//glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	if( g_useOldRenderingStyle || !g_options.m_enableFBO)
		glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
	else
		glClearColor( 0.0f, 0.0f, 0.f, 1.0f );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );



	//Draw grids of the lower left window (perspective)
	if( g_menu.m_justPerspective )
	{
		glViewport( 0, 0 , m_width , m_height );// resets the viewport to new dimensions.
		if( m_multiSample && g_options.m_numSamples ) glEnable( GL_MULTISAMPLE );
		else glDisable( GL_MULTISAMPLE );
	}
	else
	{
		if( g_useOldRenderingStyle || !g_options.m_enableFBO)
		{
			if( m_multiSample ) glDisable( GL_MULTISAMPLE );
			glViewport( 0, 0 , m_width /2 , m_height /2 );// resets the viewport to new dimensions.
		}
		else
		{
			glViewport( 0, 0 , m_width, m_height );// resets the viewport to new dimensions.
			if( m_multiSample && g_options.m_numSamples ) glEnable( GL_MULTISAMPLE );
			else glDisable( GL_MULTISAMPLE );
		}
	}
	if( g_camera->m_activatePerspectiveCamera && g_transformObject && m_translationController->Initialized() )
	{
		m_translationController->Update((int)m_translateMousePosition.x,(int)m_translateMousePosition.y );		
	}
	//Update timer	
	if( !m_selectObject )
		elapsedTime = timer.GetElapsedSeconds();
	else
		elapsedTime = timer.GetElapsedSeconds( CTrue ); //start from the beginning
	g_elapsedTime = elapsedTime;
	m_totalElapsedTime += elapsedTime;
	//Process  inputs
 	if( !m_translationController->Initialized()  )
		ProcessInputs();

	if( m_selectObject  )
	{
		if (g_camera->m_activatePerspectiveCamera)
		{
			CUInt selected = -1;
			selected = GetSelectedObject();

			//CChar temp[ MAX_NAME_SIZE];
			//sprintf( temp, "%d\n", selected );
			//PrintInfo2( temp );
		}

		m_selectObject = CFalse;
	}
	//render waters here
	CVec3f cameraPos( g_camera->m_perspectiveCameraPos.x, g_camera->m_perspectiveCameraPos.y, g_camera->m_perspectiveCameraPos.z );

	if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
 		for( CUInt i = 0 ; i < g_engineWaters.size(); i++ )
		{
			CVec3f waterPoints[4];
			waterPoints[0].x = g_engineWaters[i]->m_sidePoint[0].x;waterPoints[0].y = g_engineWaters[i]->m_sidePoint[0].y;waterPoints[0].z = g_engineWaters[i]->m_sidePoint[0].z;
			waterPoints[1].x = g_engineWaters[i]->m_sidePoint[1].x;waterPoints[1].y = g_engineWaters[i]->m_sidePoint[1].y;waterPoints[1].z = g_engineWaters[i]->m_sidePoint[1].z;
			waterPoints[2].x = g_engineWaters[i]->m_sidePoint[2].x;waterPoints[2].y = g_engineWaters[i]->m_sidePoint[2].y;waterPoints[2].z = g_engineWaters[i]->m_sidePoint[2].z;
			waterPoints[3].x = g_engineWaters[i]->m_sidePoint[3].x;waterPoints[3].y = g_engineWaters[i]->m_sidePoint[3].y;waterPoints[3].z = g_engineWaters[i]->m_sidePoint[3].z;

			if( g_camera->m_cameraManager->IsBoxInFrustum( waterPoints, 4 ) )
			{
				glUseProgram( g_render.m_waterProgram );
				g_engineWaters[i]->RenderWater(cameraPos, elapsedTime );
				glUseProgram( 0 );
			}
		}
	}

	if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
	{
		glActiveTexture(GL_TEXTURE6 );
		glBindTexture(GL_TEXTURE_2D_ARRAY_EXT, m_dynamicShadowMap->depth_tex_ar);
		if( g_shadowProperties.m_shadowType > 3 || g_shadowProperties.m_shadowType == 0 /* 0 is debug state*/)
			glTexParameteri( GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		else 
			glTexParameteri( GL_TEXTURE_2D_ARRAY_EXT, GL_TEXTURE_COMPARE_MODE, GL_NONE);

		for(int i=m_dynamicShadowMap->cur_num_splits; i<MAX_SPLITS; i++)
			far_bound[i] = 0;

		// for every active split
		for(int i=0; i<m_dynamicShadowMap->cur_num_splits; i++)
		{
			float light_m[16];

			// f[i].fard is originally in eye space - tell's us how far we can see.
			// Here we compute it in camera homogeneous coordinates. Basically, we calculate
			// cam_proj * (0, 0, f[i].fard, 1)^t and then normalize to [0; 1]
			far_bound[i] = 0.5f*(-m_dynamicShadowMap->f[i].fard*cam_proj[10]+cam_proj[14])/m_dynamicShadowMap->f[i].fard + 0.5f;

			// compute a matrix that transforms from camera eye space to light clip space
			// and pass it to the shader through the OpenGL texture matrices, since we
			// don't use them now
			glActiveTexture(GL_TEXTURE0 + (GLenum)i);
			glMatrixMode(GL_TEXTURE);
			glLoadMatrixf(bias);
			glMultMatrixf(m_dynamicShadowMap->shad_cpm[i]);
			// multiply the light's (bias*crop*proj*modelview) by the inverse camera modelview
			// so that we can transform a pixel as seen from the camera
			glMultMatrixf(cam_inverse_modelview);
			
			// compute a normal matrix for the same thing (to transform the normals)
			// Basically, N = ((L)^-1)^-t
			glGetFloatv(GL_TEXTURE_MATRIX, light_m);
			matrix4<float> nm;
			nm.set_value(light_m);
			nm = inverse(nm);
			nm = transpose(nm);

			glActiveTexture(GL_TEXTURE0 + (GLenum)(i+4));
			glMatrixMode(GL_TEXTURE);
			glLoadMatrixf(nm._array);
		}
		glMatrixMode( GL_MODELVIEW );
	}
	if (g_camera->m_activatePerspectiveCamera && g_transformObject && m_translationController->Initialized())
	{
		if (g_currentTransformType == eCTranslate)
		{
			g_arrowPosition += m_translationController->GetDisplacement();
		}
		else if (g_currentTransformType == eCRotate)
		{
			g_arrowRotate += m_translationController->GetDisplacement() * 2.0f;
		}
		else if (g_currentTransformType == eCScale)
		{
			g_arrowScale += m_translationController->GetDisplacement();
			g_arrowScale.x *= 0.3f;
			g_arrowScale.y *= 0.3f;
			g_arrowScale.z *= 0.3f;
		}
		m_translationController->DrawPlane();
	}

	//render the scene
	g_numLights = 0;
	if (g_polygonMode == ePOLYGON_FILL)
		glEnable(GL_LIGHTING);   //just for per vertex lighting

	ManageLODs();
	if (g_editorMode == eMODE_PREFAB)
		COLLADALightPass();
	else
		EngineLightPass();

	g_totalLights = g_engineLights.size();

	if ((g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_FREE ) || g_editorMode == eMODE_PREFAB || g_totalLights == 0)
		DefaultLightPass();
	FixedFunctionLightPass();

	if (g_menu.m_showBoundingBox && g_editorMode == eMODE_PREFAB)
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);
			g_render.GetScene()->RenderAABBWithLines(g_render.GetScene()->m_hasAnimation);
		}
	}
	else if (g_menu.m_showBoundingBox)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			CVector lineColor(1.0, 1.0, 1.0);
			CVector min(g_instancePrefab[i]->GetMinAABB().x, g_instancePrefab[i]->GetMinAABB().y, g_instancePrefab[i]->GetMinAABB().z);
			CVector max(g_instancePrefab[i]->GetMaxAABB().x, g_instancePrefab[i]->GetMaxAABB().y, g_instancePrefab[i]->GetMaxAABB().z);
			g_glUtil.DrawCWBoxWithLines(min, max, lineColor);
		}
	}

	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
		g_render.BindForWriting( m_mFboID );
	else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
		g_render.BindForWriting( m_fboID );

	g_currentInstanceLight = NULL;

	CBool useFog;
	if( ( g_dofProperties.m_enable && g_dofProperties.m_debug ) || ( g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
		useFog = CFalse;
	else 
		useFog = CTrue;

	if( ( g_fogProperties.m_enable && useFog ) || g_dofProperties.m_enable )
	{
		if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
			g_render.BindForWriting(m_mFboIDFogDof);
		else if(!g_useOldRenderingStyle && g_options.m_enableFBO )
			g_render.BindForWriting( m_fboIDFogDof );
		glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		g_fogBlurPass = CTrue;
		if (g_editorMode == eMODE_PREFAB)
			g_octree->Render();
		else
			g_multipleView->Render3DModels(CTrue, NULL);
		g_multipleView->Render3DAnimatedModels( CTrue);
		g_multipleView->Render3DModelsControlledByPhysX();
		g_multipleView->RenderCharacter(CFalse);


		//render water
		if ( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
		{
 			for( CUInt i = 0 ; i < g_engineWaters.size(); i++ )
			{
				CVec3f waterPoints[4];
				waterPoints[0].x = g_engineWaters[i]->m_sidePoint[0].x;waterPoints[0].y = g_engineWaters[i]->m_sidePoint[0].y;waterPoints[0].z = g_engineWaters[i]->m_sidePoint[0].z;
				waterPoints[1].x = g_engineWaters[i]->m_sidePoint[1].x;waterPoints[1].y = g_engineWaters[i]->m_sidePoint[1].y;waterPoints[1].z = g_engineWaters[i]->m_sidePoint[1].z;
				waterPoints[2].x = g_engineWaters[i]->m_sidePoint[2].x;waterPoints[2].y = g_engineWaters[i]->m_sidePoint[2].y;waterPoints[2].z = g_engineWaters[i]->m_sidePoint[2].z;
				waterPoints[3].x = g_engineWaters[i]->m_sidePoint[3].x;waterPoints[3].y = g_engineWaters[i]->m_sidePoint[3].y;waterPoints[3].z = g_engineWaters[i]->m_sidePoint[3].z;

				if( g_camera->m_cameraManager->IsBoxInFrustum( waterPoints, 4 ) )
				{
					glUseProgram( g_render.m_waterFogBlurProgram );
					glUniform1f(glGetUniformLocation( g_render.m_waterFogBlurProgram , "focalDistance"), m_dof.m_focalDistance);
					glUniform1f(glGetUniformLocation( g_render.m_waterFogBlurProgram , "focalRange"), m_dof.m_focalRange);
					if( g_fogProperties.m_enable && useFog )
						glUniform1i(glGetUniformLocation( g_render.m_waterFogBlurProgram , "enableFog"), CTrue );
					else
						glUniform1i(glGetUniformLocation( g_render.m_waterFogBlurProgram , "enableFog"), CFalse );
					g_engineWaters[i]->RenderWater(cameraPos, elapsedTime );
					glUseProgram( 0 );
				}
			}
		}

		g_fogBlurPass = CFalse;
		BlendFogWithScene();
	}


	if( g_updateOctree && g_scene.size() > 0 )
	{
		PrintInfo( "\nUpdating Octree...", COLOR_GREEN );
		//Force Update
		for( CUInt i = 0 ; i < g_scene.size(); i++ )
		{
			g_render.SetScene( g_scene[i] );
			g_render.GetScene()->m_update = CTrue;
		}

		Render3DModels( CTrue, NULL );
		g_octree->ResetState();
		//g_octree->Init();
		g_octree->GetWorldDimensions();
		g_octree->SetName( "octree_root" );
		g_octree->SetLevel(0);
		g_octree->AttachGeometriesToNode();
		//g_octree->AttachLightsToGeometries();
		g_updateOctree = CFalse;
		PrintInfo( "\nOctree updated successfully", COLOR_RED_GREEN );
		PrintInfo( "\nReady", COLOR_GREEN );

	}
	if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
	{
		//reset matrice
		for( CUInt i = 0; i < 8; i++ )
		{
			glActiveTexture(GL_TEXTURE0 + i );
			glMatrixMode( GL_TEXTURE );
			glLoadIdentity();
		}
		glActiveTexture(GL_TEXTURE0);
		glMatrixMode( GL_MODELVIEW );
	}
	
	if( g_menu.m_insertAndShowSky )
	{
		g_skyDome->RenderDome();
		if( g_menu.m_showSkyIcon && !g_dofProperties.m_debug )
			g_skyDome->RenderIcon();
	}

	//render water icons after the scene rendering
	if ( g_menu.m_showWaterIcons && g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader && !g_dofProperties.m_debug)
	{
		for( CUInt i = 0 ; i < g_engineWaters.size(); i++ )
			g_engineWaters[i]->RenderIcon();
	}
	//Render light icons after the scene rendering
	//Engine lights
	if( !g_dofProperties.m_debug )
	{
		for( CUInt i = 0; i < g_engineLights.size(); i++ )
		{
			g_engineLights[i]->RenderIcon();
			g_engineLights[i]->RenderExtents();
		}
	}
	//render character's camera icon
	if (g_currentCameraType == eCAMERA_DEFAULT_FREE && g_menu.m_showCameraIcons && g_menu.m_insertCharacter)
	{
		CFloat pitch = 0.0f;
		CFloat yaw = 0.0f;
		NxVec3 cameraPos, characterPos, cameraDirection;
		g_multipleView->m_nx->GetCameraAndCharacterPositions(pitch, yaw, cameraPos, characterPos, cameraDirection);
		g_glUtil.Billboarding(cameraPos.x, cameraPos.y, cameraPos.z, g_cameraImg->GetId(), 0.4, 0.4);
	}

	if( !g_dofProperties.m_debug )
	{
		//COLLADA Lights. Not recommended
		for( CUInt i = 0 ; i < g_scene.size(); i++ )
		{
			g_render.SetScene( g_scene[i] );
			
			//set all the lights here
			for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
			{
				CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
				if( instanceLight )
				{
					instanceLight->RenderIcon();
					instanceLight->RenderExtents();
				}
			}
		}
	}
	if( !g_dofProperties.m_debug )
	{
		for( CUInt i = 0; i < g_cameraInstances.size(); i++ )
		{
			CInstanceCamera * instanceCamera = g_cameraInstances[i];
			if( instanceCamera )
				instanceCamera->RenderIcon();
		}
	}

	if( g_physXProperties.m_bDebugMode )
		m_nx->debugMode = CTrue;
	else
		m_nx->debugMode = CFalse;

	if( m_nx->debugMode )
		m_nx->debugRenderer();

	if( g_menu.m_showPerspectiveGrids && !g_dofProperties.m_debug)
		DrawGrid();
	if( g_menu.m_showSoundIcons && !g_dofProperties.m_debug)
	{
		for( CUInt i = 0; i < g_engineStaticSounds.size(); i++ )
		{
			 g_engineStaticSounds[i]->RenderIcon();
		}
	}
	g_render.m_useShader = CFalse;
	glUseProgram(0);
	if( g_showArrow && g_currentCameraType != eCAMERA_DEFAULT_PHYSX)
	{
		CFloat distance = sqrt( pow( g_camera->m_perspectiveCameraPos.x - g_arrowPosition.x, 2 ) + 
			pow( g_camera->m_perspectiveCameraPos.y - g_arrowPosition.y, 2 ) + 
			pow( g_camera->m_perspectiveCameraPos.z - g_arrowPosition.z, 2 ) );
		if( distance < 10.0f )
			distance = 10.0f;

		CUInt m_name = g_selectedName;
		static CUInt selectedName;
		if (!g_transformObject && !m_lMouseDown)
		{
			selectedName = g_selectedName = GetSelectedObject(CTrue);
		}
		else
		{
			g_selectedName = selectedName;
		}

		glDisable(GL_DEPTH_TEST);
		glPushMatrix();
		glTranslatef( g_arrowPosition.x, g_arrowPosition.y, g_arrowPosition.z );
		glScalef( distance * 0.15f , distance * 0.15f, distance * 0.15f);
		if (g_currentTransformType == eCTranslate)
		{
			g_translateArrow->Render(CFalse);
		}
		else if (g_currentTransformType == eCRotate)
		{
			g_rotateArrow->Render(CFalse);
		}
		else if (g_currentTransformType == eCScale)
		{
			g_scaleArrow->Render(CFalse);
		}
		g_selectedName = m_name;
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);
	}

	if (g_camera->m_activatePerspectiveCamera && g_transformObject && m_translationController->Initialized())
	{
		m_translationController->DrawPlane();
	}

	if (g_menu.m_showPerspectiveGrids)
	{
		g_render.PushMatrix();
		glScalef(0.5f, 0.5f, 0.5f);
		g_centerArrowScene->Render(CTrue);
		g_render.PopMatrix();
	}
	g_render.m_useShader = CTrue;

	glDisable( GL_LIGHT0 );

	for( CInt i = 0; i <g_numLights; i++ )
	{
		glDisable( GL_LIGHT0 + i );
	}
	glDisable( GL_LIGHTING ); //just for per vertex lighting'
	glMatrixMode( GL_MODELVIEW );

	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i] );
		if( !g_render.GetScene()->m_isTrigger )
		{
			for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
			{
				g_scene[i]->m_instanceGeometries[j]->m_renderCount = 0;
			}
		}
		if( g_render.GetScene()->m_hasAnimation )
		{
			g_render.GetScene()->m_updateAnimation = CTrue;
		}
	}

	glPopAttrib(); //lighting

	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		g_render.BindForReading( m_mFboID );
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting( m_fboID );
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

		g_render.SetReadBuffer( eGBUFFER_TEXTURE_TYPE_DEFAULT );

		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		//g_render.BindForReading( m_mFboID );
		//glReadBuffer(GL_COLOR_ATTACHMENT1_EXT);
		//g_render.BindForWriting( m_fboID );
		//glDrawBuffer(GL_COLOR_ATTACHMENT1_EXT);

		//g_render.SetReadBuffer( eGBUFFER_TEXTURE_TYPE_POSITION );
		//glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		//g_render.BindForReading( m_mFboID );
		//glReadBuffer(GL_COLOR_ATTACHMENT2_EXT);
		//g_render.BindForWriting( m_fboID );
		//glDrawBuffer(GL_COLOR_ATTACHMENT2_EXT);

		//g_render.SetReadBuffer( eGBUFFER_TEXTURE_TYPE_NORMAL );
		//glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		//g_render.BindForReading( m_mFboID );
		//glReadBuffer(GL_COLOR_ATTACHMENT3_EXT);
		//g_render.BindForWriting( m_fboID );
		//glDrawBuffer(GL_COLOR_ATTACHMENT3_EXT);

		//g_render.SetReadBuffer( eGBUFFER_TEXTURE_TYPE_DIFFUSE_SHADOW_DIRT );
		//glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		//g_render.BindForReading( m_mFboID );
		//glReadBuffer(GL_COLOR_ATTACHMENT4_EXT);
		//g_render.BindForWriting( m_fboID );
		//glDrawBuffer(GL_COLOR_ATTACHMENT4_EXT);

		//g_render.SetReadBuffer( eGBUFFER_TEXTURE_TYPE_GLOSSMAP );
		//glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		//g_render.BindForReading( m_mFboID );
		//glReadBuffer(GL_COLOR_ATTACHMENT5_EXT);
		//g_render.BindForWriting( m_fboID );
		//glDrawBuffer(GL_COLOR_ATTACHMENT5_EXT);


	}
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	if( !g_useOldRenderingStyle && g_options.m_enableFBO)
	{
		if( g_dofProperties.m_enable )
		{
			glUseProgram(g_render.m_dofProgram[1]);
			if( g_dofProperties.m_debug )
				glUniform1i(glGetUniformLocation( g_render.m_dofProgram[1] , "debugMode"), CTrue);
			else
				glUniform1i(glGetUniformLocation( g_render.m_dofProgram[1] , "debugMode"), CFalse);

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			/* Second pass: downsampling */
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_dof.m_fbo[0]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D, m_textureTarget[0]);
			glUseProgram(g_render.m_dofProgram[0]);
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[0], "Tex0"), 0 );
			glViewport(0, 0, g_width/2, g_height/2);
			m_dof.DrawQuad();

			/* Third pass: Gaussian filtering along the X axis */
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_dof.m_fbo[1]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D, m_dof.m_texid[0]);
			glUseProgram(g_render.m_dofProgram[1]);
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[1], "Tex0"), 0 );
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[1], "Width"), g_width );
			m_dof.DrawQuad();

			/* Fourth pass: Gaussian filtering along the Y axis */
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_dof.m_fbo[2]);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(g_render.m_dofProgram[2]);
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[2], "Tex0"), 0 );
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[2], "Height"), g_height );
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D, m_dof.m_texid[1]);
			m_dof.DrawQuad();

			/* Fifth pass: final compositing */
			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_dof.m_fbo[3]);
			////glDrawBuffer(GL_BACK);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_textureTarget[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_dof.m_texid[2]);
			glUseProgram(g_render.m_dofProgram[3]);
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[3], "Tex0"), 0 );
			glUniform1i( glGetUniformLocation(g_render.m_dofProgram[3], "Tex1"), 1 );

			glViewport(0, 0, g_width, g_height);

			glBegin(GL_QUADS);
				glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
				glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 0.0f);
				glVertex2d(-1, -1);
				glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f);
				glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 0.0f);
				glVertex2d(1, -1);
				glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f);
				glMultiTexCoord2f(GL_TEXTURE1, 1.0f, 1.0f);
				glVertex2d(1, 1);
				glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f);
				glMultiTexCoord2f(GL_TEXTURE1, 0.0f, 1.0f);
				glVertex2d(-1, 1);
			glEnd();

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}

		if( !g_menu.m_justPerspective )
			glViewport( 0, 0 , m_width / 2, m_height / 2 );// resets the viewport to new dimensions.

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glUseProgram(0);
		glDrawBuffer( GL_BACK );
		glClear( GL_COLOR_BUFFER_BIT );
		glPushAttrib( GL_ENABLE_BIT );
		glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
		gluOrtho2D(0, g_width, 0, g_height );
		glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
		glDisable( GL_LIGHTING );
		glDisable(GL_DEPTH_TEST);
		glActiveTextureARB(GL_TEXTURE0_ARB);
		CBool found = CFalse;
		glBindTexture( GL_TEXTURE_2D, m_textureTarget[0] );

		if( !found )
			if( g_dofProperties.m_enable )
			{
				glBindTexture( GL_TEXTURE_2D, m_dof.m_texid[3] );
				found = CTrue;
			}

		glEnable( GL_TEXTURE_2D);
		glClearColor(0.37f, 0.37f, 0.37f, 1.0f);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//if( !found ) //render default texture with deferred shader
		//{
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, m_textureTarget[1]);
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, m_textureTarget[2]);
		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, m_textureTarget[3]);
		//glUseProgram(g_render.m_deferredProgram);
		//glUniform1i( glGetUniformLocation(g_render.m_deferredProgram, "tPosition"), 0 );
		//glUniform1i( glGetUniformLocation(g_render.m_deferredProgram, "tNormals"), 1 );
		//glUniform1i( glGetUniformLocation(g_render.m_deferredProgram, "tDiffuse"), 2 );
		//CFloat cameraPos[3] = { g_camera->m_perspectiveCameraPos.x, g_camera->m_perspectiveCameraPos.y, g_camera->m_perspectiveCameraPos.z };
		//glUniform3fv(glGetUniformLocation(g_render.m_deferredProgram, "cameraPosition"), 1, cameraPos);
		//}

		glBegin(GL_QUADS); 
		glTexCoord2d(0,	0);	glVertex2d(0, 0); 
		glTexCoord2d(1, 0);	glVertex2d(g_width, 0);
		glTexCoord2d(1, 1);	glVertex2d(g_width, g_height );
		glTexCoord2d(0, 1);	glVertex2d(0, g_height);
		glEnd();
		glUseProgram(0);

		CBool useBloom;
		if( (g_dofProperties.m_enable && g_dofProperties.m_debug ) || g_materialChannels != eCHANNELS_ALL || g_polygonMode != ePOLYGON_FILL)
			useBloom = CFalse;
		else
			useBloom = CTrue;

		if( g_render.m_useBloom && useBloom && g_bloomProperties.m_enable)
		{
			g_bloom->CreateRuntimeTexture( g_width, g_height, m_textureTarget[0]  );

			glPushAttrib( GL_CURRENT_BIT );

			glEnable( GL_TEXTURE_2D );

			glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glColor4f( g_bloomProperties.m_bloomColor[0], g_bloomProperties.m_bloomColor[1], g_bloomProperties.m_bloomColor[2], g_bloomProperties.m_bloomIntensity );
			glActiveTexture(GL_TEXTURE0);
			glBindTexture( GL_TEXTURE_2D, g_bloom->m_bloomTexture );
			glBegin(GL_QUADS); 
			glTexCoord2d(0,	0);	glVertex2d(0, 0); 
			glTexCoord2d(1, 0);	glVertex2d(g_width, 0);
			glTexCoord2d(1, 1);	glVertex2d(g_width, g_height );
			glTexCoord2d(0, 1);	glVertex2d(0, g_height);
			glEnd();
			glDisable( GL_BLEND );
			glPopAttrib();
		}

		if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_menu.m_showDynamicShadowDepthTexture && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
 			m_dynamicShadowMap->ShowDepthTex();
	
		DrawGUI();
		glPopAttrib();
		glMatrixMode(GL_PROJECTION); glPopMatrix();
		glMatrixMode(GL_MODELVIEW); glPopMatrix();
	}
	else
	{
		DrawGUI();
	}
	RenderQueries();

	glFlush();
}

CVoid CMultipleWindows::DrawJustPerspectiveBorders()
{
	//Draw black borders here
    glMatrixMode(GL_PROJECTION);    // Sets the projection matrix.
	glPushMatrix();
    glLoadIdentity();               // Reset the modelview matrix.

    // calculate the aspect ratio of the window.
	glOrtho( 0, 1024, 0, 768, -50000, 50000 );
	

	glPushAttrib( GL_VIEWPORT_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

	//main borders
    glMatrixMode(GL_MODELVIEW);     // Sets the model view matrix.
	glPushMatrix();
    glLoadIdentity();               // Reset the modelview matrix.

	glColor4f( 0.4f, 0.4f, 0.4f, 0.0f );
	glLineWidth( 3.0f );

	glBegin( GL_LINE_LOOP );
	glVertex3f( 0 , 0, 49999.0 ); 
	glVertex3f( 1024 , 0, 49999.0 ); 
	glVertex3f( 1024 , 768, 49999.0 ); 
	glVertex3f( 0, 768, 49999.0 ); 
	glEnd();
	glPopAttrib();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

CVoid CMultipleWindows::DrawBordersAndUI()
{
	//Draw black borders here
    glMatrixMode(GL_PROJECTION);    // Sets the projection matrix.
	glPushMatrix();
    glLoadIdentity();               // Reset the modelview matrix.

    // calculate the aspect ratio of the window.
	glOrtho( 0, 1024, 0, 768, -50000, 50000 );
	
    glMatrixMode(GL_MODELVIEW);     // Sets the model view matrix.
	glPushMatrix();
    glLoadIdentity();               // Reset the modelview matrix.

	glPushAttrib( GL_VIEWPORT_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT );
	glDisable( GL_TEXTURE_2D );
	glEnable( GL_DEPTH_TEST );

	//main borders

	glViewport( 0, 0, m_width, m_height );
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho( 0.0, 1024.0, 0.0, 768.0, -50000.0, 50000.0 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glColor4f( 0.157f, 0.157f, 0.157f, 0.0f );
	glLineWidth( 5.0f );

	glBegin( GL_LINES );
	glVertex3f( 1024 / 2 , 0, 49999.0 ); 
	glVertex3f( 1024 / 2 , 768, 49999.0 ); 
	glVertex3f( 0 , 768 / 2, 49999.0 ); 
	glVertex3f( 1024, 768 / 2, 49999.0 ); 
	glEnd();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	glLineWidth( 2.0f );
	//perspective borders
	glViewport(0, 0, m_width / 2, m_height / 2);// resets the viewport to new dimensions.
	if( g_camera->m_activatePerspectiveCamera )
		glColor4f( 1.0f, 0.6f, 0.0f, 0.0f );
	else
		glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 2, 2, 49999.0 ); 
	glVertex3f( 1024 - 6, 2, 49999.0 ); 
	glVertex3f( 1024 - 6, 768 - 8, 49999.0 ); 
	glVertex3f( 2, 768 - 8, 49999.0 ); 
	glEnd();

	//Lower right borders
	glLineWidth( 2.0f );

	glViewport(m_width / 2, 0, m_width / 2 , m_height / 2);// resets the viewport to new dimensions.
	if( g_camera->m_activateLowerRightCamera )
		glColor4f( 1.0f, 0.6f, 0.0f, 0.0f );
	else
		glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 5, 2, 49999.0 ); 
	glVertex3f( 1024 - 2, 2, 49999.0 ); 
	glVertex3f( 1024 - 2, 768 - 8, 49999.0 ); 
	glVertex3f( 5, 768 - 8, 49999.0 ); 
	glEnd();

	//Axes of lower right window
	glLineWidth( 1.0f );
	glColor4f( 0.7f, 0.0f, 0.0f, 0.0f );
	glBegin( GL_LINES );
	glVertex2i( 31 , 39 ); 
	glVertex2i( 77 , 39 ); 
	glColor4f( 0.0f, 0.0f, 1.0f, 0.0f );
	glVertex2i( 77 , 39 ); 
	glVertex2i( 77 , 100 ); 
	glEnd();

	m_simpleFont.StartRendering();
	m_simpleFont.Print( "y", 60.0f, 40.0f, 0.0f, 0.00f, 0.7f, 0.0f );
	m_simpleFont.Print( "z", 55.0f, 140.0f, 0.0f, 0.0f, 0.0f, 1.0f );
	m_simpleFont.Print( "x", 15.0f, 35.0f, 0.0f, 0.7f, 0.0f, 0.0f );
	m_simpleFont.EndRendering();

	//Upper left borders
	glLineWidth( 2.0f );

	glViewport(0, m_height / 2 , m_width / 2 , m_height / 2 );// resets the viewport to new dimensions.
	if( g_camera->m_activateUpperLeftCamera )
		glColor4f( 1.0f, 0.6f, 0.0f, 0.0f );
	else
		glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 2, 6, 49999.0 ); 
	glVertex3f( 1024 - 6, 6, 49999.0 ); 
	glVertex3f( 1024 - 6, 768 - 2, 49999.0 ); 
	glVertex3f( 2, 768 - 2, 49999.0 ); 
	glEnd();

	//Axes of upper left window
	glLineWidth( 1.0f );
	glColor4f( 0.7f, 0.0f, 0.0f, 0.0f );
	glBegin( GL_LINES );
	glVertex2i( 31 , 39 ); 
	glVertex2i( 77 , 39 ); 
	glColor4f( 0.0f, 0.7f, 0.0f, 0.0f );
	glVertex2i( 31 , 39 ); 
	glVertex2i( 31 , 100 ); 
	glEnd();

	m_simpleFont.StartRendering();
	m_simpleFont.Print( "x", 60.0f, 40.0f, 0.0f, 0.7f, 0.0f, 0.0f );
	m_simpleFont.Print( "y", 20.0f, 140.0f, 0.0f, 0.0f, 0.7f, 0.0f );
	m_simpleFont.Print( "z", 15.0f, 35.0f, 0.0f, 0.0f, 0.0f, 1.0f );
	m_simpleFont.EndRendering();

	//Upper right borders
	glLineWidth( 2.0f );

	glViewport(m_width / 2, m_height / 2 , m_width / 2 , m_height / 2 );// resets the viewport to new dimensions.
	if( g_camera->m_activateUpperRightCamera )
		glColor4f( 1.0f, 0.6f, 0.0f, 0.0f );
	else
		glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f( 5, 6, 49999.0 ); 
	glVertex3f( 1024 - 2, 6, 49999.0 ); 
	glVertex3f( 1024 - 2, 768 - 2, 49999.0 ); 
	glVertex3f( 5, 768 - 2, 49999.0 ); 
	glEnd();
	//Axes of upper right window
	glLineWidth( 1.0f );
	glColor4f( 0.0f, 0.0f, 1.0f, 0.0f );
	glBegin( GL_LINES );
	glVertex2i( 31 , 39 ); 
	glVertex2i( 77 , 39 ); 
	glColor4f( 0.0f, 0.7f, 0.0f, 0.0f );
	glVertex2i( 77 , 39 ); 
	glVertex2i( 77 , 100 ); 
	glEnd();

    glMatrixMode(GL_PROJECTION);    // Sets the projection matrix.
	glPopMatrix();
    glMatrixMode(GL_MODELVIEW);     // Sets the model view matrix.
	glPopMatrix();

	m_simpleFont.StartRendering();
	m_simpleFont.Print( "x", 60.0f, 40.0f, 0.0f, 0.7f, 0.0f, 0.0f );
	m_simpleFont.Print( "y", 55.0f, 140.0f, 0.0f, 0.0f, 0.7f, 0.0f );
	m_simpleFont.Print( "z", 15.0f, 35.0f, 0.0f, 0.0f, 0.0f, 1.0f );
	m_simpleFont.EndRendering();


	glPopAttrib();
}

CVoid CMultipleWindows::RenderWindow()
{
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (g_editorMode == eMODE_GUI)
	{
		DrawGUIMode();
	}
	else
	{
		DrawPerspective();
		if (!g_menu.m_justPerspective)
		{
			CPolygonMode tempMode = g_polygonMode;
			g_polygonMode = ePOLYGON_FILL; //to enable texturing. It's not a good way though!
			glDisable(GL_MULTISAMPLE);
			DrawUpperLeft();
			DrawUpperRight();
			DrawLowerRight();
			DrawBordersAndUI();
			g_polygonMode = tempMode;
		}
		else
		{
			DrawJustPerspectiveBorders();
		}
		ResetPhysXCounts();
	}
	SwapBuffers(m_pDC->m_hDC);
}

CVoid CMultipleWindows::ResetPhysXCounts()
{
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		for( CUInt j = 0; j < g_scene[i]->m_instanceGeometries.size(); j++ )
			g_scene[i]->m_instanceGeometries[j]->m_physXCount = 0;
	}
}

BOOL CMultipleWindows::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

		if( pMsg->message == WM_KEYDOWN )
		{
			return TRUE;
		}

	return CWnd::PreTranslateMessage(pMsg);
}

//void CMultipleWindows::ApplyForce( NxVec3 forceDirection, CInt moveDirection, CFloat elapsedTime )
//{
//	if( m_physXVariables.m_applyDirectionalForce )
//	{
//		if( m_physXVariables.m_forceSpeedValue >= 0.0f )
//		{
//			m_nx->bPushCharacter = CTrue;
//			m_nx->runPhysics( forceDirection, m_physXVariables.m_forceSpeedValue, moveDirection, elapsedTime );
//		}
//		else 
//		{
//			m_nx->bPushCharacter = CFalse;
//			m_physXVariables.m_applyDirectionalForce = CFalse;
//		}
//		m_physXVariables.m_forceSpeedValue -= elapsedTime * m_physXVariables.m_forceDecreaseValue;
//	}
//	else
//		m_nx->runPhysics( NxVec3( 0.0f, 0.0f, 0.0f ), 0.0f, moveDirection, elapsedTime );
//}

CVoid CMultipleWindows::ApplyForce( CInt direction, CFloat elapsedTime )
{
	m_nx->runPhysics( NxVec3( 0.0f, 0.0f, 0.0f ), 0.0f, direction, elapsedTime );
}

CBool CMultipleWindows::UpdateCharacterBlendCycleTimer()
{
	if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX) return CFalse;

	if (!g_mainCharacter)
		return CFalse;
	g_currentInstancePrefab = g_mainCharacter->GetInstancePrefab();
	if (!g_currentInstancePrefab)
		return CFalse;
	CScene* scene = NULL;

	CPrefab* prefab = g_currentInstancePrefab->GetPrefab();
	for (CUInt j = 0; j < 3; j++)
	{
		if (prefab && prefab->GetHasLod(j) && g_currentInstancePrefab->GetSceneVisible(j))
		{
			scene = g_currentInstancePrefab->GetScene(j);
			break;
		}
	}
	if (!scene) return CFalse;

	if (!g_currentInstancePrefab->GetVisible()) return CFalse;

	CInt index = -1;

	for (CUInt i = 0; i < scene->m_blendCycleList.size(); i++)
	{
		CChar blendCycleName[MAX_NAME_SIZE];
		Cpy(blendCycleName, scene->m_blendCycleList[i].c_str());
		StringToUpper(blendCycleName);

		std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, idleName[0].c_str());
		StringToUpper(animationName);

		StringToUpper((CChar*)idleName[0].c_str());
		if (Cmp(animationName, blendCycleName))
		{
			index = i;
		}

		CInt clipIndex = 0;
		//Find the animation clip 
		for (CInt ac = 0; ac < scene->GetNumClips(); ac++)
		{
			CChar animationName2[MAX_NAME_SIZE];
			Cpy(animationName2, scene->m_animationClips[ac]->GetName());
			StringToUpper(animationName2);

			if (Cmp(animationName2, blendCycleName))
			{
				clipIndex = ac;
				break;
			}
			if (index != -1 && Cmp(animationName, animationName2))
			{
				index = ac;
			}


		}

		if (scene->m_animationClips[clipIndex]->GetCurrentTime() > scene->m_animationClips[clipIndex]->GetEnd())
		{
			scene->m_animationClips[clipIndex]->SetCurrentTime(scene->m_animationClips[clipIndex]->GetCurrentTime() - scene->m_animationClips[clipIndex]->GetEnd() + scene->m_animationClips[clipIndex]->GetStart());
			if (index != -1 && clipIndex == index)
			{
				m_firstIdleCounter++;
			}
		}
	}
	if (index == -1)
	{
		m_firstIdleCounter = 0;
	}

	return CTrue;
}

CBool CMultipleWindows::ManageCharacterBlends(CChar* animationType, CChar* IdleAnimationName)
{
	if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX) return CFalse;

	if (!g_mainCharacter)
		return CFalse;
	g_currentInstancePrefab = g_mainCharacter->GetInstancePrefab();
	if (!g_currentInstancePrefab)
		return CFalse;
	if (!g_currentInstancePrefab->GetVisible()) return CFalse;

	std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
	std::vector<std::string> walkName = g_mainCharacter->GetWalkName();
	std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();
	std::vector<std::string> runName = g_mainCharacter->GetRunName();

	CScene* scene = NULL;

	CPrefab* prefab = g_currentInstancePrefab->GetPrefab();
	for (CUInt j = 0; j < 3; j++)
	{
		if (prefab && prefab->GetHasLod(j) && g_currentInstancePrefab->GetSceneVisible(j))
		{
			scene = g_currentInstancePrefab->GetScene(j);
			break;
		}
	}
	if (!scene) return CFalse;

	CBool foundTarget = CFalse;
	CUInt index = -1;
	if (IdleAnimationName)
		StringToUpper(IdleAnimationName);
	if (Cmp(animationType, "idle"))
	{
		if (IdleAnimationName)
		{
			for (CInt j = 0; j < scene->GetNumClips(); j++)
			{
				CChar animationName[MAX_NAME_SIZE];
				Cpy(animationName, scene->m_animationClips[j]->GetName());
				StringToUpper((CChar*)animationName);
				for (CUInt k = 0; k < idleName.size(); k++)
				{
					StringToUpper((CChar*)idleName[k].c_str());

					if (Cmp(idleName[k].c_str(), animationName))
					{
						if (scene->m_animationClips[j]->GetAnimationStatus() == eANIM_BLEND_CYCLE)
						{
							if (k == 0 && m_firstIdleCounter >= 1)
							{
								continue;
							}
							if (scene->m_animationClips[j]->GetCurrentTime() < scene->m_animationClips[j]->GetEnd())
							{
								return CFalse;
							}
						}
					}
				}
			}
		}

		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			CChar animationName[MAX_NAME_SIZE];
			Cpy(animationName, scene->m_animationClips[i]->GetName());
			StringToUpper(animationName);
			for (CUInt j = 0; j < idleName.size(); j++)
			{
				StringToUpper((CChar*)idleName[j].c_str());

				if (IdleAnimationName)
					if (!Cmp(IdleAnimationName, idleName[j].c_str()))
						continue;

				if (Cmp(idleName[j].c_str(), animationName))
				{
					index = i;
					foundTarget = CTrue;
					break;
				}
			}
			if (foundTarget)
				break;
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Couldn't find the animation clip '", idleName[0].c_str(), "'");
			PrintInfo(temp, COLOR_RED);
			return CFalse;
		}
		scene->BlendCycle(index, 1.0f, g_characterBlendingProperties.m_idleDelayIn);

		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			if (i != index)
			{
				scene->ClearCycle(i, g_characterBlendingProperties.m_idleDelayIn);

			}
		}

	}
	else if (Cmp(animationType, "walk"))
	{
		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			CChar animationName[MAX_NAME_SIZE];
			Cpy(animationName, scene->m_animationClips[i]->GetName());
			StringToUpper(animationName);
			StringToUpper((CChar*)walkName[0].c_str());
			if (Cmp(walkName[0].c_str(), animationName))
			{
				index = i;
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Couldn't find the animation clip '", walkName[0].c_str(), "'");
			PrintInfo(temp, COLOR_RED);
			return CFalse;
		}
		scene->BlendCycle(index, 1.0f, g_characterBlendingProperties.m_walkDelayIn);

		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			if (i != index)
			{
				scene->ClearCycle(i, g_characterBlendingProperties.m_walkDelayIn);
			}
		}

	}
	else if (Cmp(animationType, "run"))
	{
		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			CChar animationName[MAX_NAME_SIZE];
			Cpy(animationName, scene->m_animationClips[i]->GetName());
			StringToUpper(animationName);
			StringToUpper((CChar*)runName[0].c_str());
			if (Cmp(runName[0].c_str(), animationName))
			{
				index = i;
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Couldn't find the animation clip '", runName[0].c_str(), "'");
			PrintInfo(temp, COLOR_RED);
			return CFalse;
		}
		scene->BlendCycle(index, 1.0f, g_characterBlendingProperties.m_runDelayIn);
		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			if (i != index)
			{
				scene->ClearCycle(i, g_characterBlendingProperties.m_runDelayIn);
			}
		}

	}
	else if (Cmp(animationType, "jump"))
	{
		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			CChar animationName[MAX_NAME_SIZE];
			Cpy(animationName, scene->m_animationClips[i]->GetName());
			StringToUpper(animationName);
			StringToUpper((CChar*)jumpName[0].c_str());
			if (Cmp(jumpName[0].c_str(), animationName))
			{
				index = i;
				foundTarget = CTrue;
				break;
			}
		}
		if (!foundTarget)
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Couldn't find the animation clip '", jumpName[0].c_str(), "'");
			PrintInfo(temp, COLOR_RED);
			return CFalse;
		}
		scene->ExecuteAction(index, g_characterBlendingProperties.m_jumpDelayIn, g_characterBlendingProperties.m_jumpDelayOut);

		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			if (i != index)
			{
				scene->ClearCycle(i, g_characterBlendingProperties.m_jumpDelayIn);
			}
		}

	}
	else //reset
	{
		for (CInt i = 0; i < scene->GetNumClips(); i++)
		{
			scene->ClearCycle(i, 0.0f);
			scene->m_animationClips[i]->SetCurrentTime(0.0f);
		}
	}

	return CTrue;

}

CBool CMultipleWindows::IsJumping(CBool &isInList)
{
	if (!g_mainCharacter)
		return CFalse;
	g_currentInstancePrefab = g_mainCharacter->GetInstancePrefab();
	if (!g_currentInstancePrefab)
		return CFalse;
	if (!g_currentInstancePrefab->GetVisible()) return CFalse;

	std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();

	CScene* scene = NULL;

	CPrefab* prefab = g_currentInstancePrefab->GetPrefab();
	for (CUInt j = 0; j < 3; j++)
	{
		if (prefab && prefab->GetHasLod(j) && g_currentInstancePrefab->GetSceneVisible(j))
		{
			scene = g_currentInstancePrefab->GetScene(j);
			break;
		}
	}
	if (!scene) return CFalse;
	CBool foundTarget = CFalse;
	for (CUInt j = 0; j < jumpName.size(); j++)
	{
		for (CUInt i = 0; i < scene->m_executeActionList.size(); i++)
		{
			if (Cmp(scene->m_executeActionList[i].c_str(), jumpName[j].c_str()))
			{
				foundTarget = CTrue;
				break;
			}
		}
	}
	if (foundTarget)
		isInList = CTrue;
	else
		isInList = CFalse;
	return CTrue;
}

CBool CMultipleWindows::GetJumpCurrentEndDuration(CFloat& duration)
{
	if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX) return CFalse;

	if (!g_mainCharacter)
		return CFalse;
	g_currentInstancePrefab = g_mainCharacter->GetInstancePrefab();
	if (!g_currentInstancePrefab)
		return CFalse;
	if (!g_currentInstancePrefab->GetVisible()) return CFalse;

	std::vector<std::string> jumpName = g_mainCharacter->GetJumpName();

	CScene* scene = NULL;

	CPrefab* prefab = g_currentInstancePrefab->GetPrefab();
	for (CUInt j = 0; j < 3; j++)
	{
		if (prefab && prefab->GetHasLod(j) && g_currentInstancePrefab->GetSceneVisible(j))
		{
			scene = g_currentInstancePrefab->GetScene(j);
			break;
		}
	}
	if (!scene) return CFalse;

	CBool foundTarget = CFalse;
	CUInt index = -1;

	for (CInt i = 0; i < scene->GetNumClips(); i++)
	{
		CChar animationName[MAX_NAME_SIZE];
		Cpy(animationName, scene->m_animationClips[i]->GetName());
		StringToUpper(animationName);
		StringToUpper((CChar*)jumpName[0].c_str());
		if (Cmp(jumpName[0].c_str(), animationName))
		{
			index = i;
			foundTarget = CTrue;
			break;
		}
	}
	if (!foundTarget)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s%s", "Couldn't find the animation clip '", jumpName[0].c_str(), "'");
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}
	duration = scene->m_animationClips[index]->GetEnd() - scene->m_animationClips[index]->GetCurrentTime();
	return CTrue;
}

CVoid CMultipleWindows::ProcessInputs()
{
	if( m_lockInput || m_loadScene ) return;
	m_inputSystem->Update();

	if( g_currentCameraType == eCAMERA_DEFAULT_PHYSX )
	{
		CBool forceApplied = false;
		CBool move = CFalse;

		if( m_lMouseDown )
		{
			//if( m_inputSystem->KeyDown( DIK_LCONTROL ) && m_inputSystem->KeyDown( DIK_W ) )
			//{
			//	g_multipleView->m_nx->gCharacterWalkSpeed += 1.0f;
			//}
			//else 	if( m_inputSystem->KeyDown( DIK_LCONTROL ) && m_inputSystem->KeyDown( DIK_S ) )
 		//	{
			//	g_multipleView->m_nx->gCharacterWalkSpeed -= 1.0f;
			//	if(	g_multipleView->m_nx->gCharacterWalkSpeed <= 0.0 )
			//		g_multipleView->m_nx->gCharacterWalkSpeed += 1.0f;

			//}
			//else	if( m_inputSystem->KeyDown( DIK_LCONTROL ) && m_inputSystem->KeyDown( DIK_LSHIFT ) )
			//{
			//	g_multipleView->m_nx->gCharacterWalkSpeed = g_physXProperties.m_fCharacterWalkSpeed;
			//}
			//else	if( m_inputSystem->KeyDown( DIK_LCONTROL ) && m_inputSystem->KeyDown( DIK_Z ) )
			//{
			//	g_camera->m_cameraManager->SetAngle( DEFAULT_CAMERA_ANGLE );
			//}
			/*else*/	if( (m_inputSystem->KeyDown( DIK_W ) || m_inputSystem->KeyDown( DIK_UP )) && (m_inputSystem->KeyDown( DIK_D ) || m_inputSystem->KeyDown( DIK_RIGHT )) )
			{
				ApplyForce( MOVE_FRONT_RIGHT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			else	if( (m_inputSystem->KeyDown( DIK_W ) || m_inputSystem->KeyDown( DIK_UP )) && (m_inputSystem->KeyDown( DIK_A ) || m_inputSystem->KeyDown( DIK_LEFT )) )
			{
				ApplyForce( MOVE_FRONT_LEFT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			else if( (m_inputSystem->KeyDown( DIK_S ) || m_inputSystem->KeyDown( DIK_DOWN )) && (m_inputSystem->KeyDown( DIK_D ) || m_inputSystem->KeyDown( DIK_RIGHT )) )
			{
				ApplyForce( MOVE_BACK_RIGHT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			else if( (m_inputSystem->KeyDown( DIK_S ) || m_inputSystem->KeyDown( DIK_DOWN )) && (m_inputSystem->KeyDown( DIK_A ) || m_inputSystem->KeyDown( DIK_LEFT )) )
			{
				ApplyForce( MOVE_BACK_LEFT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}

			else	if( m_inputSystem->KeyDown( DIK_W ) || m_inputSystem->KeyDown( DIK_UP ) )
			{
				ApplyForce( MOVE_FRONT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			else if( m_inputSystem->KeyDown( DIK_S ) || m_inputSystem->KeyDown( DIK_DOWN ) )
			{
				ApplyForce( MOVE_BACK, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			else if( m_inputSystem->KeyDown( DIK_A ) || m_inputSystem->KeyDown( DIK_LEFT ) )
			{
				ApplyForce( MOVE_LEFT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}
			}
			else if( m_inputSystem->KeyDown( DIK_D ) || m_inputSystem->KeyDown( DIK_RIGHT ) )
			{
				ApplyForce( MOVE_RIGHT, elapsedTime );
				forceApplied = true;
				m_tempMovement = CTrue;
				if (!g_multipleView->m_nx->gJump)
					move = CTrue;
				if (move)
				{
					if (m_inputSystem->KeyDown(DIK_LSHIFT))
					{
						ManageCharacterBlends("run");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						}
					}
					else
					{
						ManageCharacterBlends("walk");
						if (g_mainCharacter)
						{
							g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
							g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));
						}
					}
				}

			}
			//else if( m_inputSystem->KeyDown( DIK_Q ) )
			//{
			//	ApplyForce( MOVE_UP, elapsedTime );
			//	forceApplied = true;
			//	m_tempMovement = CTrue;
			//}
			//else if( m_inputSystem->KeyDown( DIK_E ) )
			//{
			//	ApplyForce( MOVE_DOWN, elapsedTime );
			//	forceApplied = true;
			//	m_tempMovement = CTrue;
			//}
		}
		static CBool firstIdle = CTrue;
		if (!forceApplied || !move)
		{
			if (!forceApplied)
				ApplyForce(IDLE, elapsedTime);
			if (!move && g_mainCharacter)
			{
				CBool idle = CFalse;
				if (!g_multipleView->m_nx->gJump)
					idle = CTrue;
				CBool jumping = CFalse;
				if (IsJumping(jumping) && jumping)
				{
					CFloat duration = 1.0f;
					if (GetJumpCurrentEndDuration(duration) && duration <= g_characterBlendingProperties.m_jumpDelayOut)
						idle = CTrue;
				}
				if (idle)
				{
					g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
					g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));

					std::vector<std::string> idleName = g_mainCharacter->GetIdleName();
					if (firstIdle)
						m_idleCounter += elapsedTime;

					if (idleName.size() > 1 && m_idleCounter >= g_mainCharacter->GetIdleDelayForRandomPlay() && firstIdle)
					{
						CInt index = rand() % idleName.size();
						if (index == 0 && idleName.size() > 1)
							index = 1;
						if (ManageCharacterBlends("idle", (CChar*)idleName[index].c_str()))
						{
							m_idleCounter = 0.0f;
							firstIdle = CFalse;
						}
					}
					else if (ManageCharacterBlends("idle", (CChar*)idleName[0].c_str()))
					{
						firstIdle = CTrue;
					}
				}
			}
		}
		if (forceApplied)
			m_idleCounter = 0.0f;

		UpdateCharacterBlendCycleTimer();

		if( g_physXProperties.m_bApplyGravity && g_physXProperties.m_bJumping)
			if( g_multipleView->m_inputSystem->KeyDown( DIK_SPACE ) )
				if (!g_multipleView->m_nx->gJump)
				{
					CBool jumping = CFalse;
					if (IsJumping(jumping) && !jumping)
					{
						ManageCharacterBlends("jump");
						g_multipleView->m_nx->StartJump(g_physXProperties.m_fJumpPower);
						g_multipleView->m_soundSystem->PlayALSound(*(g_mainCharacter->m_jumpSound->GetSoundSource()));
						g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_walkSound->GetSoundSource()));
						g_multipleView->m_soundSystem->StopALSound(*(g_mainCharacter->m_runSound->GetSoundSource()));

					}
					else if (!g_mainCharacter)
					{
						g_multipleView->m_nx->StartJump(g_physXProperties.m_fJumpPower);
					}
				}


		if( m_lMouseDown || m_rMouseDown )
		{
			CInt dx, dy;
			m_inputSystem->GetMouseMovement( dx, dy );

			if( !m_selectObject )
			{
				//perspective viewport
				if( g_camera->m_activatePerspectiveCamera )
				{
					if( m_lMouseDown )
					{
						if( dx > 0 ) 
						{
							g_camera->m_perspectiveCameraYaw -= (CFloat)dx * 0.004f;
							m_tempMovement = CTrue;
						}
						else if( dx < 0 )
						{
							g_camera->m_perspectiveCameraYaw -= (CFloat)dx * 0.004f;
							m_tempMovement = CTrue;
						}
						if( dy > 0 ) 
						{
							g_camera->m_perspectiveCurrentCameraTilt -= (CFloat)dy * 0.01f;
							if (g_camera->m_perspectiveCurrentCameraTilt > g_camera->m_perspectiveCameraMaxTilt)
								g_camera->m_perspectiveCurrentCameraTilt = g_camera->m_perspectiveCameraMaxTilt;
							else if (g_camera->m_perspectiveCurrentCameraTilt < g_camera->m_perspectiveCameraMinTilt)
								g_camera->m_perspectiveCurrentCameraTilt = g_camera->m_perspectiveCameraMinTilt;
							m_tempMovement = CTrue;

						}
						else if( dy < 0 )
						{
							g_camera->m_perspectiveCurrentCameraTilt -= (CFloat)dy * 0.01f;
							if (g_camera->m_perspectiveCurrentCameraTilt > g_camera->m_perspectiveCameraMaxTilt)
								g_camera->m_perspectiveCurrentCameraTilt = g_camera->m_perspectiveCameraMaxTilt;
							else if (g_camera->m_perspectiveCurrentCameraTilt < g_camera->m_perspectiveCameraMinTilt)
								g_camera->m_perspectiveCurrentCameraTilt = g_camera->m_perspectiveCameraMinTilt;
							m_tempMovement = CTrue;
						}
					}
					else if( m_rMouseDown )
					{  
						if( dy > 0 ) 
							g_camera->m_cameraManager->SetZoomOut( elapsedTime * 50.0f );
						else if( dy < 0 )
							g_camera->m_cameraManager->SetZoomIn( elapsedTime * 50.0f );
					}
				}
				//lower left viewport
				else if( g_camera->m_activateLowerRightCamera )
				{
					if( m_lMouseDown )
					{
						if( dx > 0 ) 
							g_camera->m_lowerRightMoveHorizantal += (CFloat)dx * g_camera->m_lowerRightZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_lowerRightMoveHorizantal += (CFloat)dx * g_camera->m_lowerRightZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_lowerRightMoveVertical += (CFloat)dy * g_camera->m_lowerRightZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_lowerRightMoveVertical += (CFloat)dy * g_camera->m_lowerRightZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_lowerRightZoom <  0.2f ) 
							g_camera->m_lowerRightZoom += (CFloat)dy * g_camera->m_lowerRightZoom * 0.004f;
						else if( dy < 0 && g_camera->m_lowerRightZoom > 0.001f )
							g_camera->m_lowerRightZoom += (CFloat)dy * g_camera->m_lowerRightZoom * 0.004f;
					}
				}
				//upper left viewport
				else if( g_camera->m_activateUpperLeftCamera )
				{
					if( m_lMouseDown ) //move horizontal or vertical
					{
						if( dx > 0 ) 
							g_camera->m_upperLeftMoveHorizantal -= (CFloat)dx * g_camera->m_upperLeftZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_upperLeftMoveHorizantal -= (CFloat)dx * g_camera->m_upperLeftZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_upperLeftMoveVertical += (CFloat)dy * g_camera->m_upperLeftZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_upperLeftMoveVertical += (CFloat)dy * g_camera->m_upperLeftZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_upperLeftZoom < 0.2f ) 
							g_camera->m_upperLeftZoom += (CFloat)dy * g_camera->m_upperLeftZoom * 0.004f;
						else if( dy < 0 && g_camera->m_upperLeftZoom > 0.001f )
							g_camera->m_upperLeftZoom += (CFloat)dy * g_camera->m_upperLeftZoom * 0.004f;
					}
				}
				//upper right viewport
				else if( g_camera->m_activateUpperRightCamera )
				{
					if( m_lMouseDown )
					{
						if( dx > 0 ) 
							g_camera->m_upperRightMoveHorizantal += (CFloat)dx * g_camera->m_upperRightZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_upperRightMoveHorizantal += (CFloat)dx * g_camera->m_upperRightZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_upperRightMoveVertical += (CFloat)dy * g_camera->m_upperRightZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_upperRightMoveVertical += (CFloat)dy * g_camera->m_upperRightZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_upperRightZoom < 0.2f ) 
							g_camera->m_upperRightZoom += (CFloat)dy * g_camera->m_upperRightZoom * 0.004f;
						else if( dy < 0 && g_camera->m_upperRightZoom > 0.001f )
							g_camera->m_upperRightZoom += (CFloat)dy * g_camera->m_upperRightZoom * 0.004f;
					}
				}
			}
		}
	}
	else if( g_currentCameraType == eCAMERA_DEFAULT_FREE )
	{
		//add keyboard input here
		if( m_lMouseDown )
		{
			if (m_inputSystem->KeyDown( DIK_S ))
			{
				// UI code to move the camera closer
				g_render.GetDefaultInstanceCamera()->MoveTransform(elapsedTime * g_camera->m_cameraSpeed, 0.0f, 0.0f);
			}

			if (m_inputSystem->KeyDown( DIK_W ))
			{
				// UI code to move the camera farther away
				g_render.GetDefaultInstanceCamera()->MoveTransform(-elapsedTime* g_camera->m_cameraSpeed, 0.0f, 0.0f);
			}

			if (m_inputSystem->KeyDown( DIK_Q ))
			{
				// UI code to move the camera farther up
				g_render.GetDefaultInstanceCamera()->MoveTransform(0.0f, 0.0f, elapsedTime* g_camera->m_cameraSpeed);
			}

			if (m_inputSystem->KeyDown( DIK_E ))
			{
				// UI code to move the camera farther down
				g_render.GetDefaultInstanceCamera()->MoveTransform(0.0f, 0.0f, -elapsedTime* g_camera->m_cameraSpeed);
			}

			if (m_inputSystem->KeyDown( DIK_D ))
			{
				// UI code to move the camera farther right
				g_render.GetDefaultInstanceCamera()->MoveTransform(0.0f, -elapsedTime* g_camera->m_cameraSpeed, 0.0f);
			}

			if (m_inputSystem->KeyDown( DIK_A ))
			{
				// UI code to move the camera farther left
				g_render.GetDefaultInstanceCamera()->MoveTransform(0.0f, elapsedTime* g_camera->m_cameraSpeed, 0.0f);
			}
		}
		if( m_lMouseDown || m_rMouseDown )
		{
			CInt dx, dy;
			m_inputSystem->GetMouseMovement( dx, dy );

			if( !m_selectObject )
			{
				//perspective viewport
				if( g_camera->m_activatePerspectiveCamera )
				{
					if( m_lMouseDown )
					{
						g_render.GetDefaultInstanceCamera()->SetPanAndTilt( -(CFloat)dx * 0.2f, -(CFloat)dy * 0.2f );
						if( dx != 0 || dy != 0 )
							m_tempMovement = CTrue;
					}
					else if( m_rMouseDown )
					{  
						g_render.GetDefaultInstanceCamera()->ZoomTransform( dy * 0.04 );
					}
				}
				//lower left viewport
				else if( g_camera->m_activateLowerRightCamera )
				{
					if( m_lMouseDown )
					{
						if( dx > 0 ) 
							g_camera->m_lowerRightMoveHorizantal += (CFloat)dx * g_camera->m_lowerRightZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_lowerRightMoveHorizantal += (CFloat)dx * g_camera->m_lowerRightZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_lowerRightMoveVertical += (CFloat)dy * g_camera->m_lowerRightZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_lowerRightMoveVertical += (CFloat)dy * g_camera->m_lowerRightZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_lowerRightZoom <  0.2f ) 
							g_camera->m_lowerRightZoom += (CFloat)dy * g_camera->m_lowerRightZoom * 0.004f;
						else if( dy < 0 && g_camera->m_lowerRightZoom > 0.001f )
							g_camera->m_lowerRightZoom += (CFloat)dy * g_camera->m_lowerRightZoom * 0.004f;
					}
				}
				//upper left viewport
				else if( g_camera->m_activateUpperLeftCamera )
				{
					if( m_lMouseDown ) //move horizontal or vertical
					{
						if( dx > 0 ) 
							g_camera->m_upperLeftMoveHorizantal -= (CFloat)dx * g_camera->m_upperLeftZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_upperLeftMoveHorizantal -= (CFloat)dx * g_camera->m_upperLeftZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_upperLeftMoveVertical += (CFloat)dy * g_camera->m_upperLeftZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_upperLeftMoveVertical += (CFloat)dy * g_camera->m_upperLeftZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_upperLeftZoom < 0.2f ) 
							g_camera->m_upperLeftZoom += (CFloat)dy * g_camera->m_upperLeftZoom * 0.004f;
						else if( dy < 0 && g_camera->m_upperLeftZoom > 0.001f )
							g_camera->m_upperLeftZoom += (CFloat)dy * g_camera->m_upperLeftZoom * 0.004f;
					}
				}
				//upper right viewport
				else if( g_camera->m_activateUpperRightCamera )
				{
					if( m_lMouseDown )
					{
						if( dx > 0 ) 
							g_camera->m_upperRightMoveHorizantal += (CFloat)dx * g_camera->m_upperRightZoom * 2.0f;
						else if( dx < 0 )
							g_camera->m_upperRightMoveHorizantal += (CFloat)dx * g_camera->m_upperRightZoom * 2.0f;

						if( dy > 0 ) 
							g_camera->m_upperRightMoveVertical += (CFloat)dy * g_camera->m_upperRightZoom * 2.0f;
						else if( dy < 0 )
							g_camera->m_upperRightMoveVertical += (CFloat)dy * g_camera->m_upperRightZoom * 2.0f;
					}
					else if( m_rMouseDown ) //zoom in and out
					{
						if( dy > 0 && g_camera->m_upperRightZoom < 0.2f ) 
							g_camera->m_upperRightZoom += (CFloat)dy * g_camera->m_upperRightZoom * 0.004f;
						else if( dy < 0 && g_camera->m_upperRightZoom > 0.001f )
							g_camera->m_upperRightZoom += (CFloat)dy * g_camera->m_upperRightZoom * 0.004f;
					}
				}
			}
		}
	}
}

CVoid CMultipleWindows::InitObjectSelection()
{
	GLint viewport[4];
	glSelectBuffer( MAX_NAME_SIZE , Buffer );
	(void)glRenderMode( GL_SELECT );
	g_render.ProjectionMatrix();
	g_render.PushMatrix();
	g_render.IdentityMatrix();
	glGetIntegerv(GL_VIEWPORT,viewport);

	if( g_menu.m_justPerspective )
	{
		gluPickMatrix( (CDouble)m_mousePosition.x - 3.0,  (CDouble)m_height - (CDouble)m_mousePosition.y - 3.0 , 6.0, 6.0, viewport );
	}
	else
	{
		gluPickMatrix( (CInt)m_mousePosition.x - 5,  m_height - (CInt)m_mousePosition.y - 5 , 10.0, 10.0, viewport );
	}
	if( g_currentCameraType == eCAMERA_COLLADA || g_currentCameraType == eCAMERA_DEFAULT_FREE )
		gluPerspective( g_render.GetActiveInstanceCamera()->m_abstractCamera->GetYFov(), CDouble( m_width ) / CDouble (m_height ) , 0.1, 2000.0 );
	else
		gluPerspective( g_camera->m_cameraManager->GetAngle(), CDouble( m_width ) / CDouble (m_height ) , 0.1, 2000.0 );
	g_render.ModelViewMatrix();
	glInitNames();
}

CVoid CMultipleWindows::FinishObjectSelection()
{
	g_render.ProjectionMatrix();
	g_render.PopMatrix();
	g_render.ModelViewMatrix();
	glFlush();
	GLint hits = glRenderMode( GL_RENDER );

	CScene* scene = NULL;
	if (g_currentTransformType == eCTranslate)
	{
		scene = g_translateArrow;
	}
	else if (g_currentTransformType == eCRotate)
	{
		scene = g_rotateArrow;
	}
	else if (g_currentTransformType == eCScale)
	{
		scene = g_scaleArrow;
	}

	if( hits > 0 )
	{
		ptr = Buffer;
		for (CInt j = 0; j < hits; j++)
		{	
			ptr++; //skip the first info ( number of names which is one in my engine )and move to the min depth info


			CBool foundTarget = CFalse;
			for (CUInt i = 0; i < scene->m_instanceGeometries.size(); i++)
			{
				if (scene->m_instanceGeometries[i]->m_nameIndex == *(ptr + 2))
				{
					selectedName = *(ptr + 2);
					foundTarget = CTrue;
					break;
				}
			}
			if (!foundTarget)
			{
				if (*ptr < minZ)
				{
					minZ = *ptr;

					selectedName = *(ptr + 2); //name of the object
				}
			}
			else
				break;
			ptr += 3; //move to the next hit
		}
	}
}
//Returns -1 if no selection occurs
CUInt CMultipleWindows::GetSelectedObject(CBool renderArrowOnly)
{
	minZ = 0xffffffff;
	selectedName = -1;
	glPushAttrib(GL_VIEWPORT_BIT);
	if (g_menu.m_justPerspective)
	{
		glViewport(0, 0, m_width, m_height);// resets the viewport to new dimensions.
	}
	else
	{
		glViewport(0, 0, m_width / 2, m_height / 2);// resets the viewport to new dimensions.
	}

	if (!renderArrowOnly)
	{
		if (g_menu.m_insertAndShowSky)
		{
			InitObjectSelection();
			g_skyDome->RenderIcon(CTrue);
			FinishObjectSelection();
		}

		InitObjectSelection();
		//Render light icons after the scene rendering
		//Engine lights
		for (CUInt i = 0; i < g_engineLights.size(); i++)
		{
			g_engineLights[i]->RenderIcon(CTrue);
		}
		//COLLADA Lights. Not recommended
		//for( CUInt i = 0 ; i < g_scene.size(); i++ )
		//{
		//	g_render.SetScene( g_scene[i] );
		//	
		//	//set all the lights here
		//	for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
		//	{
		//		CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
		//		if( instanceLight )
		//			instanceLight->RenderIcon(CTrue);
		//	}
		//}
		FinishObjectSelection();

		InitObjectSelection();
		if (g_menu.m_showSoundIcons)
		{
			for (CUInt i = 0; i < g_engineStaticSounds.size(); i++)
			{
				g_engineStaticSounds[i]->RenderIcon(CTrue);
			}
		}
		FinishObjectSelection();

		if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
		{
			for (CUInt i = 0; i < g_engineWaters.size(); i++)
			{
				InitObjectSelection();
				g_engineWaters[i]->RenderIcon(CTrue); //render in selection mode
				FinishObjectSelection();
			}
		}

		if (g_editorMode == eMODE_PREFAB)
		{
			for (CUInt i = 0; i < g_scene.size(); i++)
			{
				if (!g_scene[i]->m_isVisible) continue;
				InitObjectSelection();
				//g_scene[i]->RenderAABBWithQuads(); //Here's the code to "draw" the objects in selection mode
				g_render.SetScene(g_scene[i]);
				//g_render.GetScene()->Update();
				g_render.GetScene()->RenderSelectionMode();
				FinishObjectSelection();
			}
		}
		else
		{
			g_render.m_useShader = CFalse;
			for (CUInt i = 0; i < g_instancePrefab.size(); i++)
			{
				if (!g_instancePrefab[i]->GetVisible()) continue;
				g_currentInstancePrefab = g_instancePrefab[i];
				CScene* scene = NULL;

				CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
				scene = g_instancePrefab[i]->GetScene(0);

				if (!scene) continue;
				InitObjectSelection();
				glPushName(g_instancePrefab[i]->GetNameIndex());
				//g_scene[i]->RenderAABBWithQuads(); //Here's the code to "draw" the objects in selection mode
				g_render.SetScene(scene);
				//g_render.GetScene()->Update();
				if (!g_render.GetScene()->m_isTrigger /*&& g_render.GetScene()->m_hasAnimation*/)
				{
					g_render.GetScene()->Render(CTrue, NULL, CFalse);
					if (g_currentInstancePrefab)
					{
						g_render.ModelViewMatrix();
						g_render.PushMatrix();
						g_render.MultMatrix(*(g_currentInstancePrefab->GetInstanceMatrix()));
					}
					g_render.GetScene()->RenderAnimatedModels(CTrue, CTrue);
					if (g_currentInstancePrefab)
					{
						g_render.PopMatrix();
					}
					g_render.GetScene()->RenderAnimatedModels(CTrue, CFalse);

					g_render.GetScene()->RenderModelsControlledByPhysX(CTrue);
				}

				glPopName();
				FinishObjectSelection();
			}
			if (g_render.UsingShader())
				g_render.m_useShader = CTrue;
		}
	}
	else if (g_showArrow)
	{
		CScene* scene = NULL;
		if (g_currentTransformType == eCTranslate)
		{
			scene = g_translateArrow;
		}
		else if (g_currentTransformType == eCRotate)
		{
			scene = g_rotateArrow;
		}
		else if (g_currentTransformType == eCScale)
		{
			scene = g_scaleArrow;
		}
		g_render.SetScene(scene);
		CFloat distance = sqrt(pow(g_camera->m_perspectiveCameraPos.x - g_arrowPosition.x, 2) +
			pow(g_camera->m_perspectiveCameraPos.y - g_arrowPosition.y, 2) +
			pow(g_camera->m_perspectiveCameraPos.z - g_arrowPosition.z, 2));
		if (distance < 10.0f)
			distance = 10.0f;
		InitObjectSelection();
		//glDisable(GL_DEPTH_TEST);
		glPushMatrix();
		glTranslatef(g_arrowPosition.x, g_arrowPosition.y, g_arrowPosition.z);
		glScalef(distance * 0.15f, distance * 0.15f, distance * 0.15f);
		scene->RenderSelectionMode();
		glPopMatrix();
		//glEnable(GL_DEPTH_TEST);
		FinishObjectSelection();
	}

	glPopAttrib();

	if(!renderArrowOnly)
		m_tempSelectedName = (CUInt)selectedName;
	return selectedName;
}

CBool CMultipleWindows::InitFBOs( CInt channels, CInt type )
{
	//glGetIntegerv( GL_MAX_DRAW_BUFFERS, &g_numBuffers );

	CUInt numSamples;
	GLenum status;
	if( m_multiSample ) //initialize 2 separate FBOs
	{
		switch( g_options.m_numSamples  )
		{
		case 2:
			numSamples = 2;
			break;
		case 4:
			numSamples = 4;
			break;
		case 8:
			numSamples = 8;
			break;
		case 16:
			numSamples = 16;
			break;
		default:
			numSamples = 0;
		}
		GLint samples;
		glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
		if( numSamples > (CUInt)samples )
			numSamples = samples;
		m_mFboID = g_render.GenerateFBO();
		g_render.BindFBO( m_mFboID );
		//g_render.BindForWriting( m_mFboID );
		//g_render.Attach2DTextureToFBOColor( m_bloomTexture );
		m_rbDepthID = g_render.GenerateRenderBuffer();
		g_render.BindRenderBuffer( m_rbDepthID );
		g_render.RenderbufferDepthStorageMultisample( numSamples, g_width, g_height );
		g_render.AttachRenderBufferToFBODepth( m_rbDepthID );

		for( CInt i = 0; i < eGBUFFER_NUM_TEXTURES; i++ )
		{
			m_rbColorID[i] = g_render.GenerateRenderBuffer();
			g_render.BindRenderBuffer( m_rbColorID[i] );
			g_render.RenderbufferColorStorageMultisample( numSamples, type, g_width, g_height );
			g_render.AttachRenderBufferToFBOColor( m_rbColorID[i], i );
		}
		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
		GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT};
		glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			default:
				PrintInfo("\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
				break;
		}

		g_render.BindFBO(0);
		g_render.BindRenderBuffer(0);

		//second multisample FBO for multi light passes
		m_mFboID2 = g_render.GenerateFBO();
		g_render.BindFBO( m_mFboID2 );
		m_rbDepthMID2 = g_render.GenerateRenderBuffer();
		g_render.BindRenderBuffer( m_rbDepthMID2 );
		g_render.RenderbufferDepthStorageMultisample( numSamples, g_width, g_height );
		g_render.AttachRenderBufferToFBODepth( m_rbDepthMID2 );

		m_rbColorID2 = g_render.GenerateRenderBuffer();
		g_render.BindRenderBuffer( m_rbColorID2 );
		g_render.RenderbufferColorStorageMultisample( numSamples, type, g_width, g_height );
		g_render.AttachRenderBufferToFBOColor( m_rbColorID2, 0 );

		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			default:
				PrintInfo("\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
				break;
		}

		g_render.BindFBO(0);
		g_render.BindRenderBuffer(0);

	}

	for( CInt i = 0; i < eGBUFFER_NUM_TEXTURES; i++ )
	{
		glGenTextures(1, &m_textureTarget[i] );								
		glBindTexture(GL_TEXTURE_2D, m_textureTarget[i] );					
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		if( i == eGBUFFER_TEXTURE_TYPE_POSITION || i == eGBUFFER_TEXTURE_TYPE_NORMAL ) //vertex or normal
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, g_width, g_height, 0, GL_RGBA, GL_FLOAT, NULL);	
		else
    		glTexImage2D(GL_TEXTURE_2D, 0, channels, g_width, g_height, 0, type, GL_UNSIGNED_BYTE, NULL );
	}

	m_fboID = g_render.GenerateFBO();
	g_render.BindFBO( m_fboID );
	//g_render.BindForWriting( m_fboID );


	for( CInt i = 0; i < eGBUFFER_NUM_TEXTURES; i++ )
	{
		g_render.Attach2DTextureToFBOColor( m_textureTarget[i], i );
	}

	m_rbDepthID2 = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbDepthID2 );
	g_render.RenderbufferStorage( g_width, g_height );
	g_render.AttachRenderBufferToFBODepth( m_rbDepthID2 );

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
	GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT};
	glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;
		default:
			PrintInfo( "\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
			break;
	}

	//second FBO for multi light passes
	glGenTextures(1, &m_textureTargetSwapLights );								
	glBindTexture(GL_TEXTURE_2D, m_textureTargetSwapLights );					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, g_width, g_height, 0, GL_RGBA, GL_FLOAT, NULL);	
  	glTexImage2D(GL_TEXTURE_2D, 0, channels, g_width, g_height, 0, type, GL_UNSIGNED_BYTE, NULL );

	m_fboID2 = g_render.GenerateFBO();
	g_render.BindFBO( m_fboID2 );

	g_render.Attach2DTextureToFBOColor( m_textureTargetSwapLights, 0 );

	m_rbDepthIDSwapLights = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbDepthIDSwapLights );
	g_render.RenderbufferStorage( g_width, g_height );
	g_render.AttachRenderBufferToFBODepth( m_rbDepthIDSwapLights );

	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;
		default:
			PrintInfo( "\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
			break;
	}

	//Final FBO for multi light passes
	glGenTextures(1, &m_textureTargetSumLighting );								
	glBindTexture(GL_TEXTURE_2D, m_textureTargetSumLighting );					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, g_width, g_height, 0, GL_RGBA, GL_FLOAT, NULL);	
   	glTexImage2D(GL_TEXTURE_2D, 0, channels, g_width, g_height, 0, type, GL_UNSIGNED_BYTE, NULL );

	m_fboIDSum = g_render.GenerateFBO();
	g_render.BindFBO( m_fboIDSum );
	g_render.Attach2DTextureToFBOColor( m_textureTargetSumLighting, 0 );

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;
		default:
			PrintInfo( "\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
			break;
	}

	g_render.BindFBO( 0 );

	glBindTexture(GL_TEXTURE_2D, 0);



	// FBO for fog and depth of field
	glGenTextures(1, &m_textureFogDof );								
	glBindTexture(GL_TEXTURE_2D, m_textureFogDof );					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, g_width, g_height, 0, GL_RGBA, GL_FLOAT, NULL);	
   	glTexImage2D(GL_TEXTURE_2D, 0, channels, g_width, g_height, 0, type, GL_UNSIGNED_BYTE, NULL );

	m_fboIDFogDof = g_render.GenerateFBO();
	g_render.BindFBO( m_fboIDFogDof );
	g_render.Attach2DTextureToFBOColor( m_textureFogDof, 0 );
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	m_rbDepthIDFogDof = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbDepthIDFogDof );
	g_render.RenderbufferStorage( g_width, g_height );
	g_render.AttachRenderBufferToFBODepth( m_rbDepthIDFogDof );
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;
		default:
			PrintInfo( "\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
			break;
	}

	//Multisample FBO for depth and DOF
	m_mFboIDFogDof = g_render.GenerateFBO();
	g_render.BindFBO( m_mFboIDFogDof );

	m_rbColorIDFogDof = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbColorIDFogDof );
	g_render.RenderbufferColorStorageMultisample( numSamples, type, g_width, g_height );
	g_render.AttachRenderBufferToFBOColor( m_rbColorIDFogDof, 0 );

	m_rbMDepthIDFogDof = g_render.GenerateRenderBuffer();
	g_render.BindRenderBuffer( m_rbMDepthIDFogDof );
	g_render.RenderbufferDepthStorageMultisample( numSamples, g_width, g_height );
	g_render.AttachRenderBufferToFBODepth( m_rbMDepthIDFogDof );

	glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status)
	{
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			break;
		default:
			PrintInfo("\nCMain::InitFBo(): An error occured while creating the FBO", COLOR_RED );
			break;
	}

	//g_render.BindFBO(0);
	g_render.BindFBO( 0 );
	g_render.BindRenderBuffer(0);

	glBindTexture(GL_TEXTURE_2D, 0);

	return CTrue;
}

CVoid CMultipleWindows::SetInstanceCamera( CInstanceCamera * inst, CFloat sWidth, CFloat sHeight )
{
	//previous position of the perspective camera (used while instanced camera is enabled)
	g_camera->m_perspectiveCameraPosOfPreviousFrame = g_camera->m_perspectiveCameraPos;

	// Get the camera from the instance and set the projection matrix from it
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(inst->m_abstractCamera->GetYFov(),
					( sWidth / sHeight ),
					/*inst->m_abstractCamera->GetZNear()*/0.1,
					/*inst->m_abstractCamera->GetZFar()*/10000);

	if( g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
	{
		//shadow
		glGetFloatv(GL_PROJECTION_MATRIX, cam_proj);
	}

	// Now get the node from the instance, and set the modelview matrix to the inverse of 
	// the node's matrix.
	glMatrixMode(GL_MODELVIEW);
	CMatrix mat;
	const CMatrix *ltow;
	ltow = inst->m_parent->GetLocalToWorldMatrix();
	CMatrixCopy(*ltow, mat); 
	//CMatrix3x4Invert( mat, mat);
	//LoadMatrix( mat );
	CVec3f at(0,0,-1),pos( 0,0,0), tAt, tPos;
	CMatrixTransform( mat, at, tAt );
	CMatrixTransform( mat, pos, tPos );
	g_camera->m_perspectiveCameraPos.x = tPos.x;
	g_camera->m_perspectiveCameraPos.y = tPos.y;
	g_camera->m_perspectiveCameraPos.z = tPos.z;

	//it's used for OpenAL
	g_camera->m_perspectiveCameraDir.x = -(tAt.x - tPos.x);
	g_camera->m_perspectiveCameraDir.y = tAt.y - tPos.y;
	g_camera->m_perspectiveCameraDir.z = -(tAt.z - tPos.z);

	//shadow 
	cam_pos[0] = g_camera->m_perspectiveCameraPos.x;
	cam_pos[1] = g_camera->m_perspectiveCameraPos.y;
	cam_pos[2] = g_camera->m_perspectiveCameraPos.z;

	cam_dir[0] = -g_camera->m_perspectiveCameraDir.x;
	cam_dir[1] = g_camera->m_perspectiveCameraDir.y;
	cam_dir[2] = -g_camera->m_perspectiveCameraDir.z;

	g_render.ModelViewMatrix();
	g_render.IdentityMatrix();
	gluLookAt( tPos.x , tPos.y, tPos.z, tAt.x, tAt.y, tAt.z, 0.0, 1.0, 0.0 );
	//if( g_shadowProperties.m_enable && g_render.UsingShadowShader()  && g_render.m_useDynamicShadowMap && g_options.m_enableShader )
	//{
		// store the inverse of the resulting modelview matrix for the shadow computation
		glGetFloatv(GL_MODELVIEW_MATRIX, cam_modelview);
		g_camera->m_cameraManager->GetInverseMatrix( cam_inverse_modelview );
	//}

}
CVoid CMultipleWindows::UpdateAnimations(CBool init)
{
	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && (g_instancePrefab[i]->GetSceneVisible(j) || init))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene)
			{
				for (CUInt j = 0; j < 3; j++)
				{
					if (prefab && prefab->GetHasLod(j))
					{
						for (CUInt k = 0; k < g_instancePrefab[i]->GetScene(j)->m_cameraInstances.size(); k++)
						{
							if (Cmp(g_instancePrefab[i]->GetScene(j)->m_cameraInstances[k]->m_abstractCamera->GetName(), g_render.GetActiveInstanceCamera()->m_abstractCamera->GetName()))
							{
								scene = g_instancePrefab[i]->GetScene(j);
								break;
							}
						}
					}
				}
			}
			if (!scene) continue;
			if (!scene->m_isVisible && !init) continue;
			g_render.SetScene(scene);
			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
				{
					if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY && g_render.GetScene()->UpdateAnimationLists())
					{
						if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
							g_render.GetScene()->Update(elapsedTime, CTrue, CFalse);
						else
							g_render.GetScene()->Update(elapsedTime);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
						g_render.GetScene()->SetUpdateBB(CTrue);
					} //if
					else if (init)
					{
						g_render.GetScene()->Update(0.0f);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
					}
					else if (g_render.GetScene()->m_update)
					{
						g_render.GetScene()->Update();
						g_render.GetScene()->m_update = CFalse;
					} //else

				} //if
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				} //else
			} //if
		} //for
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);
			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
				{
					if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY && g_render.GetScene()->UpdateAnimationLists())
					{
						g_render.GetScene()->Update(elapsedTime);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
					} //if
					else if (init)
					{
						g_render.GetScene()->Update(0.0f);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
					}
					else if (g_render.GetScene()->m_update)
					{
						g_render.GetScene()->Update();
						g_render.GetScene()->m_update = CFalse;
					} //else

				} //if
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				} //else
			} //if
		} //for

	}
}

CVoid CMultipleWindows::Render3DModelsControlledByPhysX(CBool sceneManager)
{
	//3D Model data
	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			//if (m_bQuery)
			//{
			//	if (g_instancePrefab[i]->GetResult() == 0)
			//	{
			//		if (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() >(g_instancePrefab[i]->GetRadius() + 20.0f))
			//			continue;
			//	}
			//}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene) continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				g_render.GetScene()->RenderModelsControlledByPhysX(sceneManager);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}

			}
			if (g_editorMode == eMODE_VSCENE && g_currentCameraType != eCAMERA_DEFAULT_PHYSX)
				g_instancePrefab[i]->UpdateArrow();
		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				g_render.GetScene()->RenderModelsControlledByPhysX(sceneManager);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}
			}
		}
	}

}

CVoid CMultipleWindows::Render3DModelsControlledByPhysXForWater(CWater* water, CBool sceneManager)
{
	//3D Model data
	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < water->m_instancePrefab.size(); i++)
		{
			if (!water->m_instancePrefab[i]->GetVisible()) continue;

			CScene* scene = NULL;

			CPrefab* prefab = water->m_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && water->m_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = water->m_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene) continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				g_render.GetScene()->RenderModelsControlledByPhysX(sceneManager);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}

			}
			water->m_instancePrefab[i]->UpdateArrow();
		}
	}

}

CVoid CMultipleWindows::RenderCharacter(CBool sceneManager)
{
	if (g_mainCharacter && g_mainCharacter->GetType() == eCHARACTER_FIRST_PERSON && g_currentCameraType == eCAMERA_DEFAULT_PHYSX) return;

	if (!g_menu.m_insertCharacter)
		return;
	//3D Model data
	if (g_editorMode == eMODE_VSCENE)
	{
		if (!g_mainCharacter)
			return;
		g_currentInstancePrefab = g_mainCharacter->GetInstancePrefab();
		if (!g_currentInstancePrefab->GetVisible()) return;

		//if (m_bQuery)
		//{
		//	if (g_instancePrefab[i]->GetResult() == 0)
		//	{
		//		if (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() >(g_instancePrefab[i]->GetRadius() + 20.0f))
		//			continue;
		//	}
		//}
		static CFloat lerpFactor = 0.0f;

		g_multipleView->m_nx->gCharacterPos = g_multipleView->m_nx->GetFilteredCharacterPos();
		CFloat y = (CFloat)g_multipleView->m_nx->gCharacterPos.y - (g_physXProperties.m_fCapsuleHeight * 0.5f);
		CVec3f trans(g_multipleView->m_nx->gCharacterPos.x, y, g_multipleView->m_nx->gCharacterPos.z);

		g_mainCharacter->GetInstancePrefab()->SetTranslate(trans);
		if (g_multipleView->m_nx->m_pushCharacter)
		{
			CFloat y = NxMath::radToDeg(atan2(g_multipleView->m_nx->m_horizontalDisp.x, g_multipleView->m_nx->m_horizontalDisp.z));
			if (y < 0.0f)
				y = 360.0f + y;
			if (y == 360.0f)
				y = 0.0f;
			if (g_multipleView->m_nx->m_previousMoveDirection != g_multipleView->m_nx->m_currentMoveDirection)
			{
				m_characterRotationTransition = CTrue;
				lerpFactor = 0.0f;
			}
			else if (!m_characterRotationTransition)
			{
				g_mainCharacter->SetCurrentRotation(y);
			}
			if (m_characterRotationTransition)
			{
				//find the shortest path to rotate
				if (g_mainCharacter->GetCurrentRotation() > y)
				{
					if (g_mainCharacter->GetCurrentRotation() - y > 360 + y - g_mainCharacter->GetCurrentRotation())
						y = y + 360.0f;
				}
				else if (g_mainCharacter->GetCurrentRotation() < y)
				{
					if (y - g_mainCharacter->GetCurrentRotation() > 360 + g_mainCharacter->GetCurrentRotation() - y )
						g_mainCharacter->SetCurrentRotation(g_mainCharacter->GetCurrentRotation() + 360.0f);
				}

				g_mainCharacter->SetCurrentRotation(Lerp(g_mainCharacter->GetCurrentRotation(), y, lerpFactor));
				lerpFactor += 2.0 * elapsedTime; //total: 0.5
				//if it's equal to y, stop the transition
				if (fabs(g_mainCharacter->GetCurrentRotation() - y) <= elapsedTime)
				{
					m_characterRotationTransition = CFalse;
					lerpFactor = 0.0f;
				}
			}

			CVec4f rot(0.0f, g_mainCharacter->GetCurrentRotation(), 0.0f, 0.0f);

			m_previousCharacterRotation = y;
			g_mainCharacter->GetInstancePrefab()->SetRotate(rot);
		}
		CScene* scene = NULL;

		CPrefab* prefab = g_currentInstancePrefab->GetPrefab();
		for (CUInt j = 0; j < 3; j++)
		{
			if (prefab && prefab->GetHasLod(j) )
			{
				scene = g_currentInstancePrefab->GetScene(j);
				break;
			}
		}
		if (!scene) return;
		g_render.SetScene(scene);
		if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
		{
			if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
			{
				if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY  && g_render.GetScene()->UpdateAnimationLists())
				{
					g_render.GetScene()->Update(elapsedTime);
					g_render.GetScene()->m_updateAnimation = CFalse;
					g_render.GetScene()->m_update = CFalse;
					g_render.GetScene()->SetUpdateBB(CTrue);
				}
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}

			}
			else if (g_render.GetScene()->m_update)
			{
				g_render.GetScene()->Update();
				g_render.GetScene()->m_update = CFalse;
			}
			if (g_currentInstancePrefab)
			{
				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(*(g_currentInstancePrefab->GetInstanceMatrix()));
			}
			//disable self shadow to prevent artifacts
			CBool useShadow = g_render.m_useDynamicShadowMap;
			g_render.m_useDynamicShadowMap = CFalse;
			g_render.GetScene()->RenderAnimatedModels(sceneManager, CTrue); //render controller
			g_render.m_useDynamicShadowMap = useShadow;

			if (g_currentInstancePrefab)
			{
				g_render.PopMatrix();
			}

			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
			{
				glUseProgram(0);
			}

		}
		g_currentInstancePrefab->UpdateArrow();
	}

}

CVoid CMultipleWindows::Render3DAnimatedModels(CBool sceneManager)
{
	//3D Model data
	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
				continue;

			//if (m_bQuery)
			//{
			//	if (g_instancePrefab[i]->GetResult() == 0)
			//	{
			//		if (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() >(g_instancePrefab[i]->GetRadius() + 20.0f))
			//			continue;
			//	}
			//}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene) continue;
			g_render.SetScene(scene);
			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
				{
					if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY  && g_render.GetScene()->UpdateAnimationLists())
					{
						g_render.GetScene()->Update(elapsedTime);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
						g_render.GetScene()->SetUpdateBB(CTrue);
					}
					else if (g_render.GetScene()->m_update)
					{
						g_render.GetScene()->Update();
						g_render.GetScene()->m_update = CFalse;
					}

				}
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				if (g_currentInstancePrefab)
				{
					g_render.ModelViewMatrix();
					g_render.PushMatrix();
					g_render.MultMatrix(*(g_instancePrefab[i]->GetInstanceMatrix()));
				}
				g_render.GetScene()->RenderAnimatedModels(sceneManager, CTrue); //render controller
				if (g_currentInstancePrefab)
				{
					g_render.PopMatrix();
				}
				g_render.GetScene()->RenderAnimatedModels(sceneManager, CFalse); //render animated models

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}
				
			}
			g_instancePrefab[i]->UpdateArrow();
		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
				{
					if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY  && g_render.GetScene()->UpdateAnimationLists())
					{
						g_render.GetScene()->Update(elapsedTime);
						g_render.GetScene()->m_updateAnimation = CFalse;
						g_render.GetScene()->m_update = CFalse;
					}
					else if (g_render.GetScene()->m_update)
					{
						g_render.GetScene()->Update();
						g_render.GetScene()->m_update = CFalse;
					}

				}
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}

				g_render.GetScene()->RenderAnimatedModels(sceneManager, CTrue);
				g_render.GetScene()->RenderAnimatedModels(sceneManager, CFalse);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}

			}
		}

	}

}

CVoid CMultipleWindows::Render3DAnimatedModelsForWater(CWater* water, CBool sceneManager)
{
	//3D Model data
	for (CUInt i = 0; i < water->m_instancePrefab.size(); i++)
	{
		if (!water->m_instancePrefab[i]->GetVisible()) continue;
		g_currentInstancePrefab = water->m_instancePrefab[i];
		CScene* scene = NULL;

		CPrefab* prefab = water->m_instancePrefab[i]->GetPrefab();
		for (CUInt j = 0; j < 3; j++)
		{
			if (prefab && prefab->GetHasLod(j) && water->m_instancePrefab[i]->GetSceneVisible(j))
			{
				scene = water->m_instancePrefab[i]->GetScene(j);
				break;
			}
		}
		if (!scene) continue;
		g_render.SetScene(scene);
		if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
		{
			if (g_render.GetScene()->m_hasAnimation && g_render.GetScene()->m_updateAnimation)
			{
				if (m_enableTimer && g_render.GetScene()->m_animationStatus == eANIM_PLAY  && g_render.GetScene()->UpdateAnimationLists())
				{
					g_render.GetScene()->Update(elapsedTime);
					g_render.GetScene()->m_updateAnimation = CFalse;
					g_render.GetScene()->m_update = CFalse;
					g_render.GetScene()->SetUpdateBB(CTrue);
				}
				else if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}

			}
			else if (g_render.GetScene()->m_update)
			{
				g_render.GetScene()->Update();
				g_render.GetScene()->m_update = CFalse;
			}
			if (g_currentInstancePrefab)
			{
				g_render.ModelViewMatrix();
				g_render.PushMatrix();
				g_render.MultMatrix(*(water->m_instancePrefab[i]->GetInstanceMatrix()));
			}
			g_render.GetScene()->RenderAnimatedModels(sceneManager, CTrue); //render controller
			if (g_currentInstancePrefab)
			{
				g_render.PopMatrix();
			}
			g_render.GetScene()->RenderAnimatedModels(sceneManager, CFalse); //render animated models

			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
			{
				glUseProgram(0);
			}

		}
		water->m_instancePrefab[i]->UpdateArrow();
	}

}

CVoid CMultipleWindows::RenderQueries(CBool init)
{
	if (m_bQuery || init)
	{
		m_renderQuery = CTrue;
		glDepthFunc(GL_LEQUAL);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		//glDepthMask(GL_FALSE);
		if (!g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
			g_render.BindForWriting(m_mFboID);
		else if (!g_useOldRenderingStyle && g_options.m_enableFBO)
			g_render.BindForWriting(m_fboID);
		glClear(GL_DEPTH_BUFFER_BIT);

		g_render.m_useShader = CFalse;
		glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		//glDisable(GL_DEPTH_TEST);
		for (CUInt i = 0; i < 8; i++)
		{
			glActiveTexture(GL_TEXTURE0 + (GLenum)i);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		g_render.ModelViewMatrix();
		//for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		//{
		//	if (!g_instancePrefab[i]->GetVisible()) continue;
		//	g_currentInstancePrefab = g_instancePrefab[i];

		//	glBeginQuery(GL_SAMPLES_PASSED, g_instancePrefab[i]->GetQueryIndex());
		//	COpenGLUtility glUtil;
		//	CVector min(g_instancePrefab[i]->GetMinAABB().x, g_instancePrefab[i]->GetMinAABB().y, g_instancePrefab[i]->GetMinAABB().z);
		//	CVector max(g_instancePrefab[i]->GetMaxAABB().x, g_instancePrefab[i]->GetMaxAABB().y, g_instancePrefab[i]->GetMaxAABB().z);
		//	Point p(g_instancePrefab[i]->GetCenter().x, g_instancePrefab[i]->GetCenter().y, g_instancePrefab[i]->GetCenter().z);
		//	if (g_camera->m_cameraManager->IsSphereInFrustum(p, g_instancePrefab[i]->GetRadius()))
		//		glUtil.DrawCCWBox(min, max, CFalse, CFalse);
		//	glEndQuery(GL_SAMPLES_PASSED);
		//}
		if (m_calculateDistance || init)
		{
			distance_vector.clear();
			sorted_prefabs.clear();

			CFloat distance;
			for (CUInt i = 0; i < g_instancePrefab.size(); i++)
			{
				if (g_instancePrefab[i]->GetIsTrigger() || Cmp(g_instancePrefab[i]->GetName(), "VANDA_MAIN_CHARACTER"))
					continue;

				distance = g_instancePrefab[i]->GetDistanceFromCamera();
				distance_vector.push_back(distance);
			}
			std::sort(distance_vector.begin(), distance_vector.end());
			for (CUInt i = 0; i < distance_vector.size(); i++)
			{
				for (CUInt j = 0; j < g_instancePrefab.size(); j++)
				{
					if (g_instancePrefab[i]->GetIsTrigger() || Cmp(g_instancePrefab[i]->GetName(), "VANDA_MAIN_CHARACTER"))
						continue;

					if (distance_vector[i] == g_instancePrefab[j]->GetDistanceFromCamera())
					{
						sorted_prefabs.push_back(g_instancePrefab[j]);
						break;
					}
				}
			}
		}
		for (CUInt i = 0; i < sorted_prefabs.size(); i++)
		{
			if (!sorted_prefabs[i]->GetVisible()) continue;

			g_currentInstancePrefab = sorted_prefabs[i];
			glBeginQuery(GL_SAMPLES_PASSED, sorted_prefabs[i]->GetQueryIndex());

			CScene* scene = NULL;

			CPrefab* prefab = sorted_prefabs[i]->GetPrefab();
			if (prefab && prefab->GetHasLod(0))
				scene = sorted_prefabs[i]->GetScene(0);
			if (!scene) continue;
			g_render.SetScene(scene);
			if (g_render.GetScene() && !g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
			}
			g_render.GetScene()->Render(CTrue);
			if (g_currentInstancePrefab)
			{
				g_render.PushMatrix();
				g_render.MultMatrix(*(sorted_prefabs[i]->GetInstanceMatrix()));
			}
			g_render.GetScene()->RenderAnimatedModels(CTrue, CTrue); //render controller
			if (g_currentInstancePrefab)
			{
				g_render.PopMatrix();
			}
			g_render.GetScene()->RenderAnimatedModels(CTrue, CFalse); //render animated models
			g_render.GetScene()->RenderModelsControlledByPhysX(CTrue);
			glEndQuery(GL_SAMPLES_PASSED);
		}
		g_render.m_useShader = CTrue;
		glDisable(GL_CULL_FACE);

		glDepthMask(GL_FALSE);
		//render engine lights here
		if ( g_engineLights.size() > 0)
		{
			//set all the lights here
			for (CUInt j = 0; j < g_engineLights.size(); j++)
			{
				if (Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName()))
					continue;

				CInstanceLight *instanceLight = g_engineLights[j];

				CVec3f  Position;
				if (instanceLight->m_parent)
				{
					float *matrix = (float *)instanceLight->m_parent->GetLocalToWorldMatrix();
					Position.x = matrix[12]; Position.y = matrix[13]; Position.z = matrix[14];
				}
				else
				{
					Position.x = instanceLight->m_abstractLight->GetPosition()[0];
					Position.y = instanceLight->m_abstractLight->GetPosition()[1];
					Position.z = instanceLight->m_abstractLight->GetPosition()[2];
				}
				glBeginQuery(GL_SAMPLES_PASSED, instanceLight->GetQueryIndex());
				COpenGLUtility glUtil;
				CFloat color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
				CFloat pos[3]; pos[0] = Position.x; pos[1] = Position.y; pos[2] = Position.z;
				glUtil.DrawSolidSphere(instanceLight->GetRadius(), 10, 10, pos, color);
				glEndQuery(GL_SAMPLES_PASSED);
			}
		}
		glDepthMask(CTrue);
		glPopAttrib();
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		//glDepthMask(GL_TRUE);
		m_renderQuery = CFalse;
		g_render.BindFBO(0);
	}
}

CVoid CMultipleWindows::Render3DModels(CBool sceneManager, CChar* parentTreeNameOfGeometries)
{
	//3D Model data
	if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (!g_instancePrefab[i]->GetVisible()) continue;
			g_currentInstancePrefab = g_instancePrefab[i];
			if (Cmp(g_currentInstancePrefab->GetName(), "VANDA_MAIN_CHARACTER"))
				continue;
			//if (m_bQuery)
			//{
			//	if (g_instancePrefab[i]->GetResult() == 0)
			//	{
			//		if (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() >(g_instancePrefab[i]->GetRadius() + 20.0f))
			//			continue;
			//	}
			//}

			CScene* scene = NULL;

			CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
			for (CUInt j = 0; j < 3; j++)
			{
				if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
				{
					scene = g_instancePrefab[i]->GetScene(j);
					break;
				}
			}
			if (!scene) continue;
			g_render.SetScene(scene);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				g_render.GetScene()->Render(sceneManager, parentTreeNameOfGeometries);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}

			}

			if (g_instancePrefab[i]->GetNameIndex() == g_selectedName)
			{
				CVector lineColor(1.0, 1.0, 1.0);
				CVector min(g_instancePrefab[i]->GetMinAABB().x, g_instancePrefab[i]->GetMinAABB().y, g_instancePrefab[i]->GetMinAABB().z);
				CVector max(g_instancePrefab[i]->GetMaxAABB().x, g_instancePrefab[i]->GetMaxAABB().y, g_instancePrefab[i]->GetMaxAABB().z);
				g_glUtil.DrawCWBoxWithLines(min, max, lineColor);
			}
			g_instancePrefab[i]->UpdateArrow();

		}
	}
	else
	{
		for (CUInt i = 0; i < g_scene.size(); i++)
		{
			if (!g_scene[i]->m_isVisible) continue;
			g_render.SetScene(g_scene[i]);

			if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
			{
				if (g_render.GetScene()->m_update)
				{
					g_render.GetScene()->Update();
					g_render.GetScene()->m_update = CFalse;
				}
				g_render.GetScene()->Render(sceneManager, parentTreeNameOfGeometries);

				if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				{
					glUseProgram(0);
				}

			}
		}
	}

	////render grass
	//if (g_editorMode == eMODE_VSCENE)
	//{
	//	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	//	{
	//		if (!g_instancePrefab[i]->GetVisible()) continue;
	//		g_currentInstancePrefab = g_instancePrefab[i];
	//		GLint resultAvailable = GL_FALSE, result;
	//		glGetQueryObjectiv(g_instancePrefab[i]->GetQueryIndex(), GL_QUERY_RESULT_AVAILABLE, &resultAvailable);
	//		if (resultAvailable == GL_TRUE)
	//		{
	//			glGetQueryObjectiv(g_instancePrefab[i]->GetQueryIndex(), GL_QUERY_RESULT, &result);
				//glGetQueryObjectiv(g_instancePrefab[i]->GetQueryIndex(), GL_QUERY_RESULT, &result);
				//if (result == 0)
				//{
				//	if (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() > (g_instancePrefab[i]->GetRadius() + 20.0f))
				//		continue;
				//}
	//		}

	//		CScene* scene = NULL;

	//		CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
	//		for (CUInt j = 0; j < 3; j++)
	//		{
	//			if (prefab && prefab->GetHasLod(j) && g_instancePrefab[i]->GetSceneVisible(j))
	//			{
	//				scene = g_instancePrefab[i]->GetScene(j);
	//				break;
	//			}
	//		}
	//		if (!scene) continue;
	//		g_render.SetScene(scene);

	//		if (g_render.GetScene()->m_isGrass)
	//		{
	//			if (g_render.GetScene()->m_update)
	//			{
	//				g_render.GetScene()->Update();
	//				g_render.GetScene()->m_update = CFalse;
	//			}
	//			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	//				glUseProgram(g_render.m_grassProgram);
	//			g_render.GetScene()->RenderGrass(sceneManager, parentTreeNameOfGeometries);
	//			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	//				glUseProgram(0);
	//			//if( g_menu.m_showBoundingBox )
	//			//	g_render.GetScene()->RenderAABBWithLines();
	//		}
	//		g_instancePrefab[i]->UpdateArrow();
	//	}

	//}
	//else
	//{
	//	for (CUInt i = 0; i < g_scene.size(); i++)
	//	{
	//		g_render.SetScene(g_scene[i]);

	//		if (g_render.GetScene()->m_isGrass)
	//		{
	//			if (g_render.GetScene()->m_update)
	//			{
	//				g_render.GetScene()->Update();
	//				g_render.GetScene()->m_update = CFalse;
	//			}
	//			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	//				glUseProgram(g_render.m_grassProgram);
	//			g_render.GetScene()->RenderGrass(sceneManager, parentTreeNameOfGeometries);
	//			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	//				glUseProgram(0);
	//			//if( g_menu.m_showBoundingBox )
	//			//	g_render.GetScene()->RenderAABBWithLines();
	//		}
	//	}
	//}

}

CVoid CMultipleWindows::Render3DModelsForWater(CWater* water, CBool sceneManager, CChar* parentTreeNameOfGeometries)
{
	//3D Model data
	for (CUInt i = 0; i < water->m_instancePrefab.size(); i++)
	{
		if (!water->m_instancePrefab[i]->GetVisible()) continue;

		CScene* scene = NULL;

		CPrefab* prefab = water->m_instancePrefab[i]->GetPrefab();
		for (CUInt j = 0; j < 3; j++)
		{
			if (prefab && prefab->GetHasLod(j) && water->m_instancePrefab[i]->GetSceneVisible(j))
			{
				scene = water->m_instancePrefab[i]->GetScene(j);
				break;
			}
		}
		if (!scene) continue;
		g_render.SetScene(scene);

		if (!g_render.GetScene()->m_isTrigger && !g_render.GetScene()->m_isGrass)
		{
			if (g_render.GetScene()->m_update)
			{
				g_render.GetScene()->Update();
				g_render.GetScene()->m_update = CFalse;
			}
			g_render.GetScene()->Render(sceneManager, parentTreeNameOfGeometries);

			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
			{
				glUseProgram(0);
			}

		}

		if (water->m_instancePrefab[i]->GetNameIndex() == g_selectedName)
		{
			CVector lineColor(1.0, 1.0, 1.0);
			CVector min(water->m_instancePrefab[i]->GetMinAABB().x, water->m_instancePrefab[i]->GetMinAABB().y, water->m_instancePrefab[i]->GetMinAABB().z);
			CVector max(water->m_instancePrefab[i]->GetMaxAABB().x, water->m_instancePrefab[i]->GetMaxAABB().y, water->m_instancePrefab[i]->GetMaxAABB().z);
			g_glUtil.DrawCWBoxWithLines(min, max, lineColor);
		}
		water->m_instancePrefab[i]->UpdateArrow();

	}

	//render grass
	for (CUInt i = 0; i < water->m_instancePrefab.size(); i++)
	{
		if (!water->m_instancePrefab[i]->GetVisible()) continue;
		g_currentInstancePrefab = water->m_instancePrefab[i];

		CScene* scene = NULL;

		CPrefab* prefab = water->m_instancePrefab[i]->GetPrefab();
		for (CUInt j = 0; j < 3; j++)
		{
			if (prefab && prefab->GetHasLod(j) && water->m_instancePrefab[i]->GetSceneVisible(j))
			{
				scene = water->m_instancePrefab[i]->GetScene(j);
				break;
			}
		}
		if (!scene) continue;
		g_render.SetScene(scene);

		if (g_render.GetScene()->m_isGrass)
		{
			if (g_render.GetScene()->m_update)
			{
				g_render.GetScene()->Update();
				g_render.GetScene()->m_update = CFalse;
			}
			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				glUseProgram(g_render.m_grassProgram);
			g_render.GetScene()->RenderGrass(sceneManager, parentTreeNameOfGeometries);
			if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
				glUseProgram(0);
			//if( g_menu.m_showBoundingBox )
			//	g_render.GetScene()->RenderAABBWithLines();
		}
		water->m_instancePrefab[i]->UpdateArrow();
	}

}

CVoid CMultipleWindows::DrawGUI()
{
	m_timerCounter++;
	m_simpleFont.StartRendering();
	if( g_menu.m_justPerspective )
	{
		if (g_editorMode == eMODE_PREFAB && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
			m_simpleFont.Print("Perspective : Prefab : Play Mode", 5.0f, 1000.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		else if ( g_editorMode == eMODE_PREFAB)
			m_simpleFont.Print( "Perspective : Prefab", 5.0f, 1000.0f, 0.0f, 0.85f, 0.67f, 0.0f );
		else if ( g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
			m_simpleFont.Print("Perspective : VScene : Play Mode", 5.0f, 1000.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		else
			m_simpleFont.Print("Perspective : VScene", 5.0f, 1000.0f, 0.0f, 0.85f, 0.67f, 0.0f);

		if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && !g_mainCharacter)
			m_simpleFont.Print("Warning: Please insert the player", 5.0f, 50.0f, 0.0f, 0.85f, 0.1f, 0.1f);

		if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && g_totalLights == 0)
			m_simpleFont.Print("Warning: Please insert at least one light", 5.0f, 20.0f, 0.0f, 0.85f, 0.1f, 0.1f);
		else if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && g_numLights == 0)
			m_simpleFont.Print("Warning: No visible light", 5.0f, 20.0f, 0.0f, 0.85f, 0.1f, 0.1f);

		if (g_menu.m_showStatistics)
		{
			CChar temp[MAX_NAME_SIZE];

			CInt fps = (CInt)timer.GetFps(m_timerCounter);

			sprintf(temp, "FPS : %.2f", fps);
			m_simpleFont2.Print(temp, 5.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
			sprintf( temp, "Rendered Vertexes : %i", g_numVerts );
			m_simpleFont2.Print(temp, 5.0f, 940.0f, 0.0f, 0.85f, 0.67f, 0.0f);
			sprintf( temp, "Rendered Triangles : %i", g_numVerts / 3 );
			m_simpleFont2.Print(temp, 5.0f, 910.0f, 0.0f, 0.85f, 0.67f, 0.0f);
			m_simpleFont2.Print("Object -------------------- Samples", 5.0f, 880.0f, 0.0f, 0.85f, 0.67f, 0.0f);
			for (CUInt i = 0; i < sorted_prefabs.size(); i++)
			{
				if (i <= 25)
				{
					char temp[MAX_NAME_SIZE];
					sprintf(temp, "%s : %i", sorted_prefabs[i]->GetName(), sorted_prefabs[i]->GetResult());
					m_simpleFont2.Print(temp, 5.0f, 880.0f - (i + 1) * 30, 0.0f, 0.85f, 0.67f, 0.0f);
				}
				else
				{
					break;
				}
			}

			//for (CUInt i = 0; i < g_engineLights.size(); i++)
			//{
			//	char temp[200];
			//	sprintf(temp, "%s : %i", g_engineLights[i]->m_abstractLight->GetName(), g_engineLights[i]->GetVisible());
			//	m_simpleFont.Print(temp, 10.0f, 910.0f - (g_instancePrefab.size() + i + 1) * 30, 0.0f, 0.65f, 0.5f, 0.5f);
			//}


		}
	}
	else
	{
		if (g_editorMode == eMODE_PREFAB && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
		{
			m_simpleFont.Print("Perspective : Prefab : Play Mode", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		}
		else if (g_editorMode == eMODE_PREFAB)
		{
			m_simpleFont.Print("Perspective : Prefab", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		}
		else if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX)
		{
			m_simpleFont.Print("Perspective : VScene : Play Mode", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		}
		else
		{
			m_simpleFont.Print("Perspective : VScene", 10.0f, 970.0f, 0.0f, 0.85f, 0.67f, 0.0f);
		}

		if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && !g_mainCharacter)
			m_simpleFont2.Print("Warning: Please insert the player", 10.0f, 100.0f, 0.0f, 0.85f, 0.1f, 0.1f);

		if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && g_totalLights == 0)
			m_simpleFont2.Print("Warning: Please insert at least one light", 10.0f, 50.0f, 0.0f, 0.85f, 0.1f, 0.1f);
		else if (g_editorMode == eMODE_VSCENE && g_currentCameraType == eCAMERA_DEFAULT_PHYSX && g_numLights == 0)
			m_simpleFont2.Print("Warning: No visible light", 10.0f, 50.0f, 0.0f, 0.85f, 0.1f, 0.1f);

		if( g_menu.m_showStatistics )
		{
			CChar temp[MAX_NAME_SIZE];
			CInt fps = (CInt)(timer.GetFps(m_timerCounter));
			sprintf( temp, "FPS : %i", fps );
			m_simpleFont2.Print( temp, 10.0f, 920.0f, 0.0f, 0.85f, 0.67f, 0.0f );
			sprintf( temp, "Rendered Vertexes : %i", g_numVerts );
			m_simpleFont2.Print( temp, 10.0f, 870.0f, 0.0f, 0.85f, 0.67f, 0.0f );
			sprintf( temp, "Rendered Triangles : %i", g_numVerts / 3 );
			m_simpleFont2.Print( temp, 10.0f, 820.0f, 0.0f, 0.85f, 0.67f, 0.0f );
		}
	}
	m_simpleFont.EndRendering();

	if (g_transformObject && g_currentTransformType == eCTranslate)
	{
		CFloat val;
		CChar temp1[MAX_NAME_SIZE];
		val = roundf(g_arrowPosition.x * 100) / 100;
		sprintf(temp1, "%.02f", val);
		ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(temp1);

		CChar temp2[MAX_NAME_SIZE];
		val = roundf(g_arrowPosition.y * 100) / 100;
		sprintf(temp2, "%.02f", val);
		ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(temp2);

		CChar temp3[MAX_NAME_SIZE];
		val = roundf(g_arrowPosition.z * 100) / 100;
		sprintf(temp3, "%.02f", val);
		ex_pVandaEngine1Dlg->m_editZ.SetWindowTextA(temp3);
	}
	else if (g_transformObject && (g_currentTransformType == eCRotate || g_currentTransformType == eCScale))
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (g_instancePrefab[i]->GetNameIndex() == g_selectedName)
			{
				if (g_currentTransformType == eCRotate)
				{
					CInstancePrefab* instancePrefab = g_instancePrefab[i];
					CFloat val;
					CChar temp1[MAX_NAME_SIZE];
					CFloat rotate;
					CVec4f rot;

					rotate = instancePrefab->GetRotate().x;
					if (rotate >= 360.0f)
						rotate -= 360.0f;
					else if (rotate < 0)
						rotate = 360 + rotate;
					rot.x = rotate; rot.y = instancePrefab->GetRotate().y; rot.z = instancePrefab->GetRotate().z; rot.w = instancePrefab->GetRotate().w;
					instancePrefab->SetRotate(rot);

					val = roundf(instancePrefab->GetRotate().x * 100) / 100;
					sprintf(temp1, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(temp1);

					rotate = instancePrefab->GetRotate().y;
					if (rotate >= 360.0f)
						rotate -= 360.0f;
					else if (rotate < 0)
						rotate = 360 + rotate;
					rot.x = instancePrefab->GetRotate().x; rot.y = rotate; rot.z = instancePrefab->GetRotate().z; rot.w = instancePrefab->GetRotate().w;
					instancePrefab->SetRotate(rot);

					CChar temp2[MAX_NAME_SIZE];
					val = roundf(instancePrefab->GetRotate().y * 100) / 100;
					sprintf(temp2, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(temp2);

					if (g_mainCharacter && g_mainCharacter->GetInstancePrefab() == g_instancePrefab[i])
					{
						g_mainCharacter->SetCurrentRotation(val);
					}


					rotate = instancePrefab->GetRotate().z;
					if (rotate >= 360.0f)
						rotate -= 360.0f;
					else if (rotate < 0)
						rotate = 360 + rotate;
					rot.x = instancePrefab->GetRotate().x; rot.y = instancePrefab->GetRotate().y; rot.z = rotate; rot.w = instancePrefab->GetRotate().w;
					instancePrefab->SetRotate(rot);

					CChar temp3[MAX_NAME_SIZE];
					val = roundf(instancePrefab->GetRotate().z * 100) / 100;
					sprintf(temp3, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editZ.SetWindowTextA(temp3);
					break;
				}
				else if (g_currentTransformType == eCScale)
				{
					CFloat val;
					CChar temp1[MAX_NAME_SIZE];
					val = roundf(g_instancePrefab[i]->GetScale().x * 100) / 100;
					sprintf(temp1, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editX.SetWindowTextA(temp1);

					CChar temp2[MAX_NAME_SIZE];
					val = roundf(g_instancePrefab[i]->GetScale().y * 100) / 100;
					sprintf(temp2, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editY.SetWindowTextA(temp2);

					CChar temp3[MAX_NAME_SIZE];
					val = roundf(g_instancePrefab[i]->GetScale().z * 100) / 100;
					sprintf(temp3, "%.02f", val);
					ex_pVandaEngine1Dlg->m_editZ.SetWindowTextA(temp3);
					break;
				}

			}
		}
	}
	if( m_totalElapsedTime >= 5 ) //Every 5 seconds update the FPS
	{
		SetElapsedTimeFromBeginning();
	}

	for (CUInt i = 0; i < g_guis.size(); i++)
	{
		if (g_guis[i]->GetVisible())
		{
			for (CUInt j = 0; j < g_guis[i]->m_guiBackgrounds.size(); j++)
			{
				g_guis[i]->m_guiBackgrounds[j]->Render();
			}
			for (CUInt j = 0; j < g_guis[i]->m_guiButtons.size(); j++)
			{
				g_guis[i]->m_guiButtons[j]->Render();
			}
			for (CUInt j = 0; j < g_guis[i]->m_guiTexts.size(); j++)
			{
				g_guis[i]->m_guiTexts[j]->Render();
			}
		}
	}
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(&p);
	CVec2f pos(p.x, g_height - p.y);
	m_icon->Render(pos);
}

CVoid CMultipleWindows::BlendFogWithScene()
{
	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		g_render.BindForReading( m_mFboID );
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting( m_fboID );
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		g_render.BindForReading( m_mFboIDFogDof );
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting( m_fboIDFogDof );
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, m_textureTarget[0]);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, m_textureFogDof);

	g_render.BindForWriting( m_fboIDSum );

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(g_render.m_blendTexturesProgram);
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "tex_unit_0"), 0 );
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "tex_unit_1"), 1 );
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "blendLights"), CFalse );


	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2i(0,	0);	glVertex2i(0, 0); 
	glTexCoord2i(1, 0);	glVertex2i(g_width, 0);
	glTexCoord2i(1, 1);	glVertex2i(g_width, g_height);
	glTexCoord2i(0, 1);	glVertex2i(0, g_height);
	glEnd();
	glFlush();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	g_render.BindFBO(0);

	//copy  sum to the default FBO
	g_render.BindForReading( m_fboIDSum );
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		g_render.BindForWriting( m_mFboID );
	}
	else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
	{
		g_render.BindForWriting( m_fboID );
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
		glBlitFramebufferEXT(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

}

CVoid CMultipleWindows::BlendLights(CUInt lightIndex)
{
	if( lightIndex == 0 ) return;
	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		g_render.BindForReading( m_mFboID );
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting( m_fboID );
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		g_render.BindForReading( m_mFboID2 );
		glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
		g_render.BindForWriting( m_fboID2 );
		glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
		glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, m_textureTarget[0]);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, m_textureTargetSwapLights);

	g_render.BindForWriting( m_fboIDSum );

	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(g_render.m_blendTexturesProgram);
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "tex_unit_0"), 0 );
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "tex_unit_1"), 1 );
	glUniform1i( glGetUniformLocation(g_render.m_blendTexturesProgram, "blendLights"), CTrue );


	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2i(0,	0);	glVertex2i(0, 0); 
	glTexCoord2i(1, 0);	glVertex2i(g_width, 0);
	glTexCoord2i(1, 1);	glVertex2i(g_width, g_height);
	glTexCoord2i(0, 1);	glVertex2i(0, g_height);
	glEnd();
	glFlush();

	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();
	//glActiveTextureARB(GL_TEXTURE0_ARB);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glActiveTextureARB(GL_TEXTURE1_ARB);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	g_render.BindFBO(0);

	//copy light sum to the default FBO
	g_render.BindForReading( m_fboIDSum );
	glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
	if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
	{
		if( lightIndex % 2  == 0 )
		{
			g_render.BindForWriting( m_mFboID );
		}
		else
		{
			g_render.BindForWriting( m_mFboID2 );
		}
	}
	else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
	{
		if( lightIndex % 2  == 0 )
			g_render.BindForWriting( m_fboID );
		else
			g_render.BindForWriting( m_fboID2 );
	}
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
		glBlitFramebufferEXT(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

}

CVoid CMultipleWindows::ManageLODs()
{
	CInt m_numSamples;
	CInt width, height;
	if (g_menu.m_justPerspective)
	{
		width = g_multipleView->m_width;
		height = g_multipleView->m_height;
	}
	else
	{
		width = g_multipleView->m_width / 2;
		height = g_multipleView->m_height / 2;

	}

	if (g_multipleView->m_multiSample)
		m_numSamples = width * height * g_options.m_numSamples;
	else
		m_numSamples = width * height;

	//CInt index = 0;
	//m_bQuery = CFalse;
	//for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	//{
	//	GLint resultAvailable = GL_FALSE;
	//	glGetQueryObjectiv(g_instancePrefab[i]->GetQueryIndex(), GL_QUERY_RESULT_AVAILABLE, &resultAvailable);

	//	if (resultAvailable)
	//		index++;
	//}
	//CInt numLights = 0;

	//for (CUInt i = 0; i < g_engineLights.size(); i++)
	//{
	//	if (Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[i]->m_abstractLight->GetName()))
	//		continue;
	//	numLights++;
	//	GLint resultAvailable = GL_FALSE;
	//	glGetQueryObjectiv(g_engineLights[i]->GetQueryIndex(), GL_QUERY_RESULT_AVAILABLE, &resultAvailable);

	//	if (resultAvailable)
	//		index++;
	//}

	//if (index == g_instancePrefab.size() + numLights)
	//{
		//all results are available
		m_bQuery = CTrue;
	//}
	if (m_bQuery)
	{
		for (CUInt i = 0; i < g_instancePrefab.size(); i++)
		{
			if (g_instancePrefab[i]->GetIsTrigger() || Cmp(g_instancePrefab[i]->GetName(), "VANDA_MAIN_CHARACTER"))
				continue;

			GLint result;
			glGetQueryObjectiv(g_instancePrefab[i]->GetQueryIndex(), GL_QUERY_RESULT, &result);
			g_instancePrefab[i]->SetResult(result);

			if (result == 0 && g_instancePrefab[i]->GetNameIndex() != g_selectedName)
			{
				g_instancePrefab[i]->SetSceneVisible(0, CFalse);
				g_instancePrefab[i]->SetSceneVisible(1, CFalse);
				g_instancePrefab[i]->SetSceneVisible(2, CFalse);
				continue;
			}

			CFloat percentage;
			percentage = ((CFloat)result / (CFloat)m_numSamples) * 100.0f;
			if (percentage >= 12.0f || (g_instancePrefab[i]->GetDistanceFromCamera() - g_instancePrefab[i]->GetRadius() <= (g_instancePrefab[i]->GetRadius() + 20.0f)))
			{
				if (g_instancePrefab[i]->GetElapsedTime() >= 0.01f)
				{
					if (g_instancePrefab[i]->GetSceneVisible(1) && g_instancePrefab[i]->GetScene(1) && g_instancePrefab[i]->GetScene(1)->m_hasAnimation)
					{
						for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(1)->m_animationClips.size(); j++)
						{
							if (g_instancePrefab[i]->GetScene(0))
							{
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentDelayInTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentDelayOutTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentWeight());
							}
						}
					}
					else if (g_instancePrefab[i]->GetSceneVisible(2) && g_instancePrefab[i]->GetScene(2) && g_instancePrefab[i]->GetScene(2)->m_hasAnimation)
					{
						for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(2)->m_animationClips.size(); j++)
						{
							if (g_instancePrefab[i]->GetScene(0))
							{
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentDelayInTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentDelayOutTime());
								g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentWeight());
							}
						}
					}

					g_instancePrefab[i]->SetSceneVisible(0, CTrue);
					g_instancePrefab[i]->SetSceneVisible(1, CFalse);
					g_instancePrefab[i]->SetSceneVisible(2, CFalse);
					g_instancePrefab[i]->ResetElapsedTime();
				}
			}
			else if (percentage >= 1.5f && percentage < 10.0f)
			{
				if (g_instancePrefab[i]->GetElapsedTime() >= 0.01f)
				{
					if (g_instancePrefab[i]->GetSceneVisible(0) && g_instancePrefab[i]->GetScene(0) && g_instancePrefab[i]->GetScene(0)->m_hasAnimation)
					{
						for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(0)->m_animationClips.size(); j++)
						{
							if (g_instancePrefab[i]->GetScene(1))
							{
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentDelayInTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentDelayOutTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentWeight());
							}
						}
					}
					else if (g_instancePrefab[i]->GetSceneVisible(2) && g_instancePrefab[i]->GetScene(2) && g_instancePrefab[i]->GetScene(2)->m_hasAnimation)
					{
						for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(2)->m_animationClips.size(); j++)
						{
							if (g_instancePrefab[i]->GetScene(1))
							{
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentDelayInTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentDelayOutTime());
								g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->GetCurrentWeight());
							}
						}
					}

					if (g_instancePrefab[i]->GetPrefab()->GetHasLod(1))
					{
						g_instancePrefab[i]->SetSceneVisible(0, CFalse);
						g_instancePrefab[i]->SetSceneVisible(1, CTrue);
						g_instancePrefab[i]->SetSceneVisible(2, CFalse);
						g_instancePrefab[i]->ResetElapsedTime();
					}
				}
			}
			else if (percentage > 0.003f && percentage < 1.4f)
			{
				if (g_instancePrefab[i]->GetElapsedTime() >= 0.01f)
				{
					if (!g_instancePrefab[i]->GetSceneVisible(0) && !g_instancePrefab[i]->GetSceneVisible(1) && !g_instancePrefab[i]->GetSceneVisible(2))
					{
						if (g_instancePrefab[i]->GetPrefab()->GetHasLod(2))
						{
							g_instancePrefab[i]->SetSceneVisible(0, CFalse);
							g_instancePrefab[i]->SetSceneVisible(1, CFalse);
							g_instancePrefab[i]->SetSceneVisible(2, CTrue);
							g_instancePrefab[i]->ResetElapsedTime();
						}
						else if (g_instancePrefab[i]->GetPrefab()->GetHasLod(1))
						{
							g_instancePrefab[i]->SetSceneVisible(0, CFalse);
							g_instancePrefab[i]->SetSceneVisible(1, CTrue);
							g_instancePrefab[i]->SetSceneVisible(2, CFalse);
							g_instancePrefab[i]->ResetElapsedTime();
						}
						else if (g_instancePrefab[i]->GetPrefab()->GetHasLod(0))
						{
							g_instancePrefab[i]->SetSceneVisible(0, CTrue);
							g_instancePrefab[i]->SetSceneVisible(1, CFalse);
							g_instancePrefab[i]->SetSceneVisible(2, CFalse);
							g_instancePrefab[i]->ResetElapsedTime();
						}
					}
					if (g_instancePrefab[i]->GetPrefab()->GetHasLod(2))
					{
						if (g_instancePrefab[i]->GetSceneVisible(1))
						{
							if (g_instancePrefab[i]->GetScene(1) && g_instancePrefab[i]->GetScene(1)->m_hasAnimation)
							{
								for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(1)->m_animationClips.size(); j++)
								{
									if (g_instancePrefab[i]->GetScene(2))
									{
										g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentTime());
										g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentDelayInTime());
										g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentDelayOutTime());
										g_instancePrefab[i]->GetScene(2)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->GetCurrentWeight());
									}
								}
							}

							g_instancePrefab[i]->SetSceneVisible(0, CFalse);
							g_instancePrefab[i]->SetSceneVisible(1, CFalse);
							g_instancePrefab[i]->SetSceneVisible(2, CTrue);
							g_instancePrefab[i]->ResetElapsedTime();
						}
					}
					else if (g_instancePrefab[i]->GetSceneVisible(0))
					{
						if (g_instancePrefab[i]->GetPrefab()->GetHasLod(1))
						{
							if (g_instancePrefab[i]->GetScene(0) && g_instancePrefab[i]->GetScene(0)->m_hasAnimation)
							{
								for (CUInt j = 0; j < g_instancePrefab[i]->GetScene(0)->m_animationClips.size(); j++)
								{
									if (g_instancePrefab[i]->GetScene(1))
									{
										g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentTime());
										g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayInTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentDelayInTime());
										g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentDelayOutTime(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentDelayOutTime());
										g_instancePrefab[i]->GetScene(1)->m_animationClips[j]->SetCurrentWeight(g_instancePrefab[i]->GetScene(0)->m_animationClips[j]->GetCurrentWeight());
									}
								}
							}

							g_instancePrefab[i]->SetSceneVisible(0, CFalse);
							g_instancePrefab[i]->SetSceneVisible(1, CTrue);
							g_instancePrefab[i]->SetSceneVisible(2, CFalse);
							g_instancePrefab[i]->ResetElapsedTime();
						}
					}

				}
			}

			g_instancePrefab[i]->SetElapsedTime(g_elapsedTime);
		}

		for (CUInt i = 0; i < g_engineLights.size(); i++)
		{
			if (Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[i]->m_abstractLight->GetName()))
				continue;

			GLint result;
			glGetQueryObjectiv(g_engineLights[i]->GetQueryIndex(), GL_QUERY_RESULT, &result);

			if (result == 0 && g_engineLights[i]->GetDistanceFromCamera() > g_engineLights[i]->GetRadius())
				g_engineLights[i]->SetVisible(CFalse);
			else
				g_engineLights[i]->SetVisible(CTrue);
		}

	}
}

CVoid CMultipleWindows::EngineLightPass()
{
	if( !g_useOldRenderingStyle && g_options.m_enableFBO && g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader && g_engineLights.size() > 0 )
	{
		//set all the lights here
		for( CUInt j = 0; j < g_engineLights.size(); j++ )
		{
			CInstanceLight *instanceLight = g_engineLights[j];
			g_currentInstanceLight = instanceLight;

			CVec3f  Position;
			if( instanceLight->m_parent )
			{
				float *matrix = (float *)instanceLight->m_parent->GetLocalToWorldMatrix();
				Position.x = matrix[12]; Position.y = matrix[13]; Position.z =  matrix[14]; 
			}
			else
			{
				Position.x = instanceLight->m_abstractLight->GetPosition()[0];
				Position.y = instanceLight->m_abstractLight->GetPosition()[1];
				Position.z = instanceLight->m_abstractLight->GetPosition()[2];
			}
			CBool visible = CFalse;
			if (Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName()))
				visible = CTrue;
			else
				visible = instanceLight->GetVisible();
			if (g_camera->m_cameraManager->IsSphereInFrustum(Position.x, Position.y, Position.z, (CFloat)instanceLight->GetRadius()) && visible)
			{
				if( Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName() ) )
				{
					g_firstPass = CTrue;
				//	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
				//	GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT};
				//	glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);
				}
				else
				{
					g_firstPass = CFalse;
				}
				glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );

				if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
				{
					if( g_numLights % 2 == 0 )
						g_render.BindForWriting( m_mFboID );
					else
						g_render.BindForWriting( m_mFboID2 );
				}
				else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
				{
					if( g_numLights % 2 == 0 )
						g_render.BindForWriting( m_fboID );
					else
						g_render.BindForWriting( m_fboID2 );
				}
				if( g_numLights != 0 )
				{
					glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
					glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
				}
				glViewport( 0, 0, m_width, m_height );

				if( g_numLights < 8 ) // 8 lights are supported
				{
					CBool defaultLight;
					if( Cmp(g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName() ) || ( Cmp(g_shadowProperties.m_directionalLightName, "\n" ) && g_engineLights[j]->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL ))
						defaultLight = CTrue;
					else
						defaultLight = CFalse;
					if( g_render.SetInstanceLight(g_engineLights[j],0, defaultLight) )
					{
						if( defaultLight )
							Cpy( g_shadowProperties.m_directionalLightName, g_engineLights[j]->m_abstractLight->GetName() );
						if (g_editorMode == eMODE_PREFAB)
							g_octree->Render();
						else
							g_multipleView->Render3DModels(CTrue, NULL);
						g_multipleView->Render3DAnimatedModels(CTrue);
						g_multipleView->Render3DModelsControlledByPhysX();
						g_multipleView->RenderCharacter(CFalse);

						BlendLights(g_numLights);
						++g_numLights;
						if (g_editorMode == eMODE_PREFAB)
							g_octree->ResetOctreeGeoCount();
					}
				}
			}
		}
		if( g_numLights > 1 && (g_numLights % 2 == 0) )
		{
			if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
				g_render.BindForReading( m_mFboID2 );
			else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
				g_render.BindForReading( m_fboID2 );

			glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

			if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
				g_render.BindForWriting( m_mFboID );
			else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
				g_render.BindForWriting( m_fboID );

			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
			if ( g_render.UsingFBOs() && g_options.m_enableFBO )
			{
				glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
				glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST );
			}
		}
	} //if !g_useOldRenderingStyle
	else if( g_engineLights.size() > 0 && ( g_useOldRenderingStyle || !g_options.m_enableFBO ) && g_render.UsingShader() && g_render.m_useShader )//old rendering style
	{
		glDrawBuffer( GL_BACK );
		//set all the lights here
		for( CUInt j = 0; j < g_engineLights.size(); j++ )
		{
			if( j == 0 )
			if( g_numLights < 1 ) // 1 lights is supported
			{
				if( g_render.SetInstanceLight(g_engineLights[j],0, CTrue) )
				{
					if (g_editorMode == eMODE_PREFAB)
						g_octree->Render();
					else
						g_multipleView->Render3DModels(CTrue, NULL);
					g_multipleView->Render3DAnimatedModels(CTrue);
					g_multipleView->Render3DModelsControlledByPhysX();
					g_multipleView->RenderCharacter(CFalse);

					if (g_editorMode == eMODE_PREFAB)
						g_octree->ResetOctreeGeoCount();
					++g_numLights;
					break;
				}
			}
		}
	}
	else
	{
		for( CUInt j = 0; j < g_engineLights.size(); j++ )
		{
			if( g_numLights < 8 ) // 8 lights are supported
			{
				if( g_render.SetInstanceLight(g_engineLights[j],g_numLights, CTrue) )
				{
					++g_numLights;
				}
			}
		}
	}
}

CVoid CMultipleWindows::COLLADALightPass()
{
	if( !g_useOldRenderingStyle && g_options.m_enableFBO && g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		//COLLADA Lights. Not recommended
		for( CUInt i = 0 ; i < g_scene.size(); i++ )
		{
			g_render.SetScene( g_scene[i] );
			
			//set all the lights here
			for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
			{
				CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
				if( instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_AMBIENT )
					continue;
				g_currentInstanceLight = instanceLight;

				CVec3f  Position;
				if( instanceLight->m_parent )
				{
					float *matrix = (float *)instanceLight->m_parent->GetLocalToWorldMatrix();
					Position.x = matrix[12]; Position.y = matrix[13]; Position.z =  matrix[14]; 
				}
				else
				{
					Position.x = instanceLight->m_abstractLight->GetPosition()[0];
					Position.y = instanceLight->m_abstractLight->GetPosition()[1];
					Position.z = instanceLight->m_abstractLight->GetPosition()[2];
				}

				if( g_camera->m_cameraManager->IsSphereInFrustum( Position.x, Position.y, Position.z, (CFloat)instanceLight->GetRadius() ) )
				{
					if( Cmp(g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName() ) )
					{
						g_firstPass = CTrue;
					//	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_COLOR_ATTACHMENT3_EXT,
					//	GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT};
					//	glDrawBuffers(eGBUFFER_NUM_TEXTURES, DrawBuffers);
					}
					else
					{
						g_firstPass = CFalse;
					}
					glDrawBuffer( GL_COLOR_ATTACHMENT0_EXT );

					if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
					{
						if( g_numLights % 2 == 0 )
							g_render.BindForWriting( m_mFboID );
						else
							g_render.BindForWriting( m_mFboID2 );
					}
					else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
					{
						if( g_numLights % 2 == 0 )
							g_render.BindForWriting( m_fboID );
						else
							g_render.BindForWriting( m_fboID2 );
					}
					if( g_numLights != 0 ) //clear m_fboID2 or m_mFboID2
					{
						glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
						glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
					}
					glViewport( 0, 0, m_width, m_height );

					if( g_numLights < 8 ) // 8 lights are supported
					{
						if( instanceLight )
						{
							CBool defaultLight;
							if( Cmp(g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName() ) || ( Cmp(g_shadowProperties.m_directionalLightName, "\n" ) && instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL ))
								defaultLight = CTrue;
							else
								defaultLight = CFalse;
							if( g_render.SetInstanceLight(instanceLight,0, defaultLight) )
							{
								if( defaultLight )
									Cpy( g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName() );
								if (g_editorMode == eMODE_PREFAB)
									g_octree->Render();
								else
									g_multipleView->Render3DModels(CTrue, NULL);
								g_multipleView->Render3DAnimatedModels(CTrue);
								g_multipleView->Render3DModelsControlledByPhysX();
								g_multipleView->RenderCharacter(CFalse);

								BlendLights(g_numLights);
								++g_numLights;
								if (g_editorMode == eMODE_PREFAB)
									g_octree->ResetOctreeGeoCount();
								g_render.SetScene( g_scene[i] );
							}
						}
					}
				}
			}
		}
		if( g_numLights > 1 && (g_numLights % 2 == 0) )
		{
			if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
				g_render.BindForReading( m_mFboID2 );
			else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
				g_render.BindForReading( m_fboID2 );

			glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

			if( !g_useOldRenderingStyle && m_multiSample && g_options.m_numSamples && g_options.m_enableFBO)
				g_render.BindForWriting( m_mFboID );
			else if( !g_useOldRenderingStyle && g_options.m_enableFBO)
				g_render.BindForWriting( m_fboID );

			glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

			if ( g_render.UsingFBOs() && g_options.m_enableFBO )
			{
				glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
				glBlitFramebufferEXT(0, 0, g_width, g_height, 0, 0, g_width, g_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST );
			}
		}
	} //if !g_useOldRenderingStyle
	else if( ( g_useOldRenderingStyle || !g_options.m_enableFBO ) && g_render.UsingShader() && g_render.m_useShader )//old rendering style
	{
		for( CUInt i = 0 ; i < g_scene.size(); i++ )
		{
			g_render.SetScene( g_scene[i] );
			
			//set all the lights here
			for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
			{
				if( j == 0 )
				{
					if( g_numLights < 1 ) // 1 lights is supported
					{
						CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
						if( instanceLight )
						{
							if( g_render.SetInstanceLight(instanceLight,0, CTrue) )
							{
								if (g_editorMode == eMODE_PREFAB)
									g_octree->Render();
								else
									g_multipleView->Render3DModels(CTrue, NULL);
								g_multipleView->Render3DAnimatedModels(CTrue);
								g_multipleView->Render3DModelsControlledByPhysX();
								g_multipleView->RenderCharacter(CFalse);

								if (g_editorMode == eMODE_PREFAB)
									g_octree->ResetOctreeGeoCount();
								++g_numLights;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		for( CUInt i = 0 ; i < g_scene.size(); i++ )
		{
			g_render.SetScene( g_scene[i] );
			
			//set all the lights here
			for( CUInt j = 0; j < g_render.GetScene()->GetLightInstanceCount(); j++ )
			{
				if( g_numLights < 8 ) // 8 lights are supported
				{
					CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(j);
					if( instanceLight )
					{
						if( g_render.SetInstanceLight(instanceLight,g_numLights, CTrue) )
						{
							++g_numLights;
						}
					}
				}
			}
		}
	}
}

CVoid CMultipleWindows::FixedFunctionLightPass()
{
	if( !g_render.UsingShader() || !g_render.m_useShader || !g_options.m_enableShader || g_numLights == 0)
	{
		if (g_editorMode == eMODE_PREFAB)
			g_octree->Render();
		else
			g_multipleView->Render3DModels(CTrue, NULL);
		g_multipleView->Render3DAnimatedModels(CTrue);
		g_multipleView->Render3DModelsControlledByPhysX();
		g_multipleView->RenderCharacter(CFalse);


	}
}

CVoid CMultipleWindows::DefaultLightPass()
{
	if( g_numLights == 0 )
	{
		//glViewport( 0, 0, m_width, m_height );

		glEnable(GL_LIGHT0);	 //just for per vertex lighting 	

		//This is the properties of the camera light
		GLfloat light_pos0[4] = {g_camera->m_perspectiveCameraPos.x,g_camera->m_perspectiveCameraPos.y, g_camera->m_perspectiveCameraPos.z, 1.0f };
		//g_defaultDirectionalLight.x = light_pos0[0]; g_defaultDirectionalLight.y = light_pos0[1]; g_defaultDirectionalLight.z = light_pos0[2]; g_defaultDirectionalLight.w = 0.0f;

		GLfloat light_ambient0[4] = { 0.5f, 0.5f, 0.5f, 0.0f };
		GLfloat light_diffuse0[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat light_specular0[4] = { 0.6f, 0.6f, 0.6f, 1.0f };
		GLfloat light_shininess0 = 5.0f;

		glLightfv( GL_LIGHT0, GL_POSITION, light_pos0  );
		glLightfv( GL_LIGHT0, GL_AMBIENT , light_ambient0 );
		glLightfv( GL_LIGHT0, GL_DIFFUSE , light_diffuse0 );
		glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular0 );
		glLightf ( GL_LIGHT0, GL_SHININESS, light_shininess0 );
		//glLightf ( GL_LIGHT0, GL_SPOT_CUTOFF,(GLfloat)180.0f );
		glLightf ( GL_LIGHT0, GL_CONSTANT_ATTENUATION , (GLfloat)1.0f );
		glLightf ( GL_LIGHT0, GL_LINEAR_ATTENUATION,	(GLfloat)0.0f );
		glLightf ( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (GLfloat)0.0f );

		if (g_editorMode == eMODE_PREFAB)
			g_octree->Render();
		else
			g_multipleView->Render3DModels(CTrue, NULL);
		g_multipleView->Render3DAnimatedModels(CTrue);
		g_multipleView->Render3DModelsControlledByPhysX();
		g_multipleView->RenderCharacter(CFalse);


		if( g_options.m_enableShader  && g_render.UsingShader()  && g_render.m_useShader && g_editorMode == eMODE_PREFAB)
			g_octree->ResetOctreeGeoCount();
		g_numLights++;
	}
}

CVoid CMultipleWindows::UpdatePrefabInstanceBB()
{
	for (CUInt i = 0; i < g_instancePrefab.size(); i++)
	{
		if (!g_instancePrefab[i]->GetVisible()) continue;
		g_currentInstancePrefab = g_instancePrefab[i];
		CBool foundTarget = CFalse;
		CScene* scene = NULL;

		CPrefab* prefab = g_instancePrefab[i]->GetPrefab();
		for (CUInt j = 0; j < 3; j++)
		{
			if (prefab && prefab->GetHasLod(j))
			{
				scene = g_instancePrefab[i]->GetScene(j);

				if (!scene) continue;
				if (scene->GetUpdateBB())
				{
					g_instancePrefab[i]->UpdateBoundingBox(CFalse);
					scene->SetUpdateBB(CFalse);
					foundTarget = CTrue;
					break;
				}
			}
		}
		if (foundTarget)
			continue;
	}
}

void CMultipleWindows::OnMouseHover(UINT nFlags, CPoint point)
{
	m_mousePosition = point;
	CWnd::OnMouseHover(nFlags, point);
}


CVoid CMultipleWindows::InitGUISelection()
{
	GLint viewport[4];
	glSelectBuffer(MAX_NAME_SIZE, m_guiBuffer);
	(void)glRenderMode(GL_SELECT);
	g_render.ProjectionMatrix();
	g_render.PushMatrix();
	g_render.IdentityMatrix();
	glGetIntegerv(GL_VIEWPORT, viewport);

	gluPickMatrix((CDouble)m_mousePosition.x - 3.0, (CDouble)m_height - (CDouble)m_mousePosition.y - 3.0, 6.0, 6.0, viewport);

	glOrtho(0.0, g_width, 0.0, g_height, -100.0, 100.0);

	g_render.ModelViewMatrix();
	g_render.PushMatrix();
	g_render.IdentityMatrix();

	glInitNames();
}

CVoid CMultipleWindows::FinishGUISelection()
{
	g_render.ProjectionMatrix();
	g_render.PopMatrix();
	g_render.ModelViewMatrix();
	g_render.PopMatrix();
	glFlush();
	GLint hits = glRenderMode(GL_RENDER);

	if (hits > 0)
	{
		m_guiPtr = m_guiBuffer;
		for (CInt j = 0; j < hits; j++)
		{
			m_guiPtr++; //skip the first info ( number of names which is one in my engine )and move to the min depth info

			if (*m_guiPtr < m_guiMinZ)
			{
				m_guiMinZ = *m_guiPtr;

				m_guiSelectedName = *(m_guiPtr + 2); //name of the object
			}
			m_guiPtr += 3; //move to the next hit
		}
	}
}
//Returns -1 if no selection occurs
CUInt CMultipleWindows::GetSelectedGUI()
{
	m_guiMinZ = 0xffffffff;
	m_guiSelectedName = -1;
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0, 0, g_width, g_height);// resets the viewport to new dimensions.

	InitGUISelection();

	if (g_editorMode == eMODE_GUI)
	{
		//render here
		for (CUInt i = 0; i < g_guiBackgrounds.size(); i++)
		{
			g_guiBackgrounds[i]->Render(CTrue);
		}

		//render here
		for (CUInt i = 0; i < g_guiButtons.size(); i++)
		{
			g_guiButtons[i]->Render(CTrue);
		}

		//render here
		for (CUInt i = 0; i < g_guiTexts.size(); i++)
		{
			g_guiTexts[i]->Render(CTrue);
		}
	}
	else if (g_editorMode == eMODE_VSCENE)
	{
		for (CUInt i = 0; i < g_guis.size(); i++)
		{
			if (g_guis[i]->GetVisible())
			{
				for (CUInt j = 0; j < g_guis[i]->m_guiBackgrounds.size(); j++)
				{
					g_guis[i]->m_guiBackgrounds[j]->Render(CTrue);
				}
				for (CUInt j = 0; j < g_guis[i]->m_guiButtons.size(); j++)
				{
					g_guis[i]->m_guiButtons[j]->Render(CTrue);
				}
				for (CUInt j = 0; j < g_guis[i]->m_guiTexts.size(); j++)
				{
					g_guis[i]->m_guiTexts[j]->Render(CTrue);
				}
			}
		}
	}
	FinishGUISelection();

	glPopAttrib();

	return m_guiSelectedName;
}

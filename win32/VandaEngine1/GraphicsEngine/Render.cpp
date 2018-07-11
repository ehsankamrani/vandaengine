/*
 * Copyright 2006 Sony Computer Entertainment Inc.
 *
 * Licensed under the SCEA Shared Source License, Version 1.0 (the "License"); you may not use this 
 * file except in compliance with the License. You may obtain a copy of the License at:
 * http://research.scea.com/scea_shared_source_license.html
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License 
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
 * implied. See the License for the specific language governing permissions and limitations under the 
 * License. 
 */

#include "stdafx.h"
#include "render.h"

using namespace std;
CVoid CRender::Init()
{
	m_activeInstanceCamera = NULL;

	//InitMembers();
	m_VBOsAvailable = CFalse;
	m_shaderAvailable = CFalse;
	m_FBOsAvailable = CFalse;

	m_scene = NULL;
	m_selectedScene = NULL;
	m_shaderProgram = 0;
	m_waterProgram = 0;
	m_glowProgram = 0;
	m_grassProgram = 0;
	m_blurProgram = 0;
	m_shad_single_hl_prog = 0;
	m_shad_single_prog = 0;
	m_shad_multi_prog = 0;
	m_shad_multi_noleak_prog = 0;
    m_shad_pcf_prog = 0;
    m_shad_pcf_trilin_prog = 0;
    m_shad_pcf_4tap_prog = 0;
    m_shad_pcf_8tap_prog = 0;
    m_shad_pcf_gaussian_prog = 0;
	m_shad_view_depth = 0;

	for( CUInt i = 0; i < 4; i++ )
		m_dofProgram[i] = 0;
	//m_cgInitialized = InitCg();
	CheckForVBOs();
	CheckForFBOs();
	m_shadowShaderAvailable = CTrue;
	std::string infoLog;

	if (!glewIsSupported("GL_VERSION_3_0")) //GLSL 1.3 is required
	{
		MessageBox( NULL, _T( "Your implementation does not support OpenGL 3.0. Shaders disabled"), _T( "VandaEngine Error" ), MB_OK );
		m_shaderAvailable = CFalse;
		return;
	}

	if( !GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader )
	{
		MessageBox( NULL, _T("GL_ARB_vertex_shader and GL_ARB_fragment_shader is not supported. Shader has been disabled"), _T( "VandaEngine Error" ), MB_OK );
		m_shaderAvailable = CFalse;
	}
	else
	{
		m_shaderProgram = LoadShaderProgram( "Assets/Engine/shaders/default.glsl", infoLog);
		if( m_shaderProgram == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T("Couldn't load shader : Assets/Engine/shaders/default.glsl"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "Default shader loaded successfully\n", COLOR_WHITE );
			m_shaderAvailable = CTrue;
		}

		m_shader_normalProgram = LoadShaderProgram("Assets/Engine/shaders/default_normal.glsl", infoLog);
		if (m_shader_normalProgram == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/default_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nDefault_Normal shader loaded successfully", COLOR_WHITE);
			//m_shaderAvailable = CTrue;
		}

		m_spotShaderProgram = LoadShaderProgram( "Assets/Engine/shaders/default_spot.glsl", infoLog);
		if( m_spotShaderProgram == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/default_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nDefault_Spot shader loaded successfully", COLOR_WHITE );
			//m_shaderAvailable = CTrue;
		}

		m_spot_normalShaderProgram = LoadShaderProgram("Assets/Engine/shaders/default_spot_normal.glsl", infoLog);
		if (m_spot_normalShaderProgram == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/default_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nDefault_Spot_Normal shader loaded successfully", COLOR_WHITE);
			//m_shaderAvailable = CTrue;
		}

		m_waterProgram = LoadShaderProgram( "Assets/Engine/shaders/water.glsl", infoLog);
		if( m_waterProgram == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T("Couldn't load shader : Assets/Engine/shaders/water.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "water shader loaded successfully\n", COLOR_WHITE );
		}

		m_blurProgram = LoadShaderProgram( "Assets/Engine/shaders/blur.glsl", infoLog);
		if( m_blurProgram == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/blur.glsl"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "blur shader loaded successfully\n", COLOR_WHITE );
		}

		m_glowProgram = LoadShaderProgram( "Assets/Engine/shaders/glow.glsl", infoLog);
		if( m_glowProgram == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/glow.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}
		m_grassProgram = LoadShaderProgram( "Assets/Engine/shaders/grass.glsl", infoLog);
		if( m_grassProgram == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/grass.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}

		m_dofProgram[0] = LoadShaderProgram( "Assets/Engine/shaders/dof/second.glsl", infoLog);
		if( m_dofProgram[0] == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/dof/second.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}

		m_dofProgram[1] = LoadShaderProgram( "Assets/Engine/shaders/dof/third.glsl", infoLog);
		if( m_dofProgram[1] == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/dof/third.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}

		m_dofProgram[2] = LoadShaderProgram( "Assets/Engine/shaders/dof/fourth.glsl", infoLog);
		if( m_dofProgram[2] == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/dof/fourth.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}
		m_dofProgram[3] = LoadShaderProgram( "Assets/Engine/shaders/dof/fifth.glsl", infoLog);
		if( m_dofProgram[3] == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/dof/fifth.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "glow shader loaded successfully\n", COLOR_WHITE );
		}

		m_fogBlurProgram = LoadShaderProgram( "Assets/Engine/shaders/fog_blur.glsl", infoLog);
		if( m_fogBlurProgram == 0 )
		{
			MessageBoxA( NULL, "Couldn't load shader : Assets/Engine/shaders/fog_blur.glsl", "Vanda Engine 1 Error", MB_OK | MB_ICONERROR);
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nfog_blur shader loaded successfully", COLOR_WHITE );
		}

		//water fog blur
		m_waterFogBlurProgram = LoadShaderProgram( "Assets/Engine/shaders/water_fog_blur.glsl", infoLog);
		if( m_waterFogBlurProgram == 0 )
		{
			MessageBoxA( NULL, "Couldn't load shader : Assets/Engine/shaders/water_fog_blur.glsl", "Vanda Engine 1 Error", MB_OK | MB_ICONERROR);
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/water_fog_blur.glsl", COLOR_RED );
		}

		m_blendTexturesProgram = LoadShaderProgram( "Assets/Engine/shaders/BlendTextures.glsl", infoLog);
		if( m_blendTexturesProgram == 0 )
		{
			MessageBoxA(NULL, "Couldn't load shader : Assets/Engine/shaders/BlendTextures.glsl", "Vanda Engine 1 Error", MB_OK | MB_ICONERROR );
			infoLog.erase();
			m_shaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nBlendTextures shader loaded successfully", COLOR_WHITE );
		}

		//shadow
		m_shad_single_hl_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_single_hl.glsl", infoLog);
		if( m_shad_single_hl_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_single_hl.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;

			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_single_hl shader loaded successfully\n", COLOR_WHITE );
		}
	 
		m_shad_multi_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_multi_leak.glsl", infoLog);
		if( m_shad_multi_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_multi_leak.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_multi_leak shader loaded successfully\n", COLOR_WHITE );
		}

		m_shad_single_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_single.glsl", infoLog);
		if( m_shad_single_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_single.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_single shader loaded successfully\n", COLOR_WHITE );
		}

		m_shad_multi_noleak_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_multi_noleak.glsl", infoLog);
		if( m_shad_multi_noleak_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_multi_noleak.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_multi_noleak shader loaded successfully\n", COLOR_WHITE );
		}

		m_shad_pcf_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_pcf.glsl", infoLog);
		if( m_shad_pcf_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_pcf.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_pcf shader loaded successfully\n", COLOR_WHITE );
		}
	
		m_shad_pcf_trilin_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_pcf_trilinear.glsl", infoLog);
		if( m_shad_pcf_trilin_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_pcf_trilinear.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_pcf_trilinear shader loaded successfully\n", COLOR_WHITE );
		}
	
		m_shad_pcf_4tap_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_pcf_4tap.glsl", infoLog);
		if( m_shad_pcf_4tap_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_pcf_4tap.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_pcf_4tap shader loaded successfully\n", COLOR_WHITE );
		}
		
		m_shad_pcf_8tap_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_pcf_8tap_random.glsl", infoLog);
		if( m_shad_pcf_8tap_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_pcf_8tap_random.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_pcf_8tap_random shader loaded successfully\n", COLOR_WHITE );
		}
		
		m_shad_pcf_gaussian_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/shadow_pcf_gaussian.glsl", infoLog);
		if( m_shad_pcf_gaussian_prog == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/shadow_pcf_gaussian.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/shadow_pcf_gaussian shader loaded successfully\n", COLOR_WHITE );
		}

		m_shad_view_depth = LoadShaderProgram( "Assets/Engine/shaders/shadow/view_depth.glsl", infoLog);
		if( m_shad_view_depth == 0 )
		{
			if( infoLog.c_str() )
			MessageBox( NULL, _T( "Couldn't load shader : Assets/Engine/shaders/shadow/view_depth.glsl\n"), _T( "VandaEngine Error" ), MB_OK );
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "shadow/view_depth shader loaded successfully\n", COLOR_WHITE );
		}

		//shadow + normal map
		m_shad_single_hl_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_single_hl_normal.glsl", infoLog);
		if (m_shad_single_hl_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_single_hl_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_single_hl_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_multi_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_multi_leak_normal.glsl", infoLog);
		if (m_shad_multi_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_multi_leak_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_multi_leak_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_single_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_single_normal.glsl", infoLog);
		if (m_shad_single_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_single_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_single_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_multi_noleak_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_multi_noleak_normal.glsl", infoLog);
		if (m_shad_multi_noleak_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_multi_noleak_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_multi_noleak_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_normal.glsl", infoLog);
		if (m_shad_pcf_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_pcf_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_trilin_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_trilinear_normal.glsl", infoLog);
		if (m_shad_pcf_trilin_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_trilinear_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_pcf_trilinear_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_4tap_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_4tap_normal.glsl", infoLog);
		if (m_shad_pcf_4tap_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_4tap_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_pcf_4tap_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_8tap_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_8tap_random_normal.glsl", infoLog);
		if (m_shad_pcf_8tap_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_8tap_random_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_pcf_8tap_random_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_gaussian_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_gaussian_normal.glsl", infoLog);
		if (m_shad_pcf_gaussian_normal_prog == 0)
		{
			if (infoLog.c_str())
				MessageBox(NULL, _T("Couldn't load shader : Assets/Engine/shaders/shadow/shadow_normal/shadow_pcf_gaussian_normal.glsl\n"), _T("VandaEngine Error"), MB_OK);
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/shadow_normal/shadow_pcf_gaussian_normal shader loaded successfully", COLOR_WHITE);
		}
		///////////////////////

		///////Shadow Spot/////////////////////////
		m_shad_single_hl_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_single_hl_spot.glsl", infoLog);
		if( m_shad_single_hl_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
				//PrintShaderLog( "\n" );
				//PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_single_hl_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_single_hl_spot shader loaded successfully", COLOR_WHITE );
		}
	 
		m_shad_multi_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_multi_leak_spot.glsl", infoLog);
		if( m_shad_multi_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_multi_leak_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_multi_leak_spot shader loaded successfully", COLOR_WHITE );
		}

		m_shad_single_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_single_spot.glsl", infoLog);
		if( m_shad_single_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_single_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_single_spot shader loaded successfully", COLOR_WHITE );
		}

		m_shad_multi_noleak_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_multi_noleak_spot.glsl", infoLog);
		if( m_shad_multi_noleak_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_multi_noleak_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_multi_noleak_spot shader loaded successfully", COLOR_WHITE );
		}

		m_shad_pcf_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_pcf_spot.glsl", infoLog);
		if( m_shad_pcf_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_pcf_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_pcf_spot shader loaded successfully", COLOR_WHITE );
		}
	
		m_shad_pcf_trilin_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_pcf_trilinear_spot.glsl", infoLog);
		if( m_shad_pcf_trilin_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_pcf_trilinear_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_pcf_trilinear_spot shader loaded successfully", COLOR_WHITE );
		}
	
		m_shad_pcf_4tap_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_pcf_4tap_spot.glsl", infoLog);
		if( m_shad_pcf_4tap_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_pcf_4tap_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_pcf_4tap_spot shader loaded successfully", COLOR_WHITE );
		}
		
		m_shad_pcf_8tap_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_pcf_8tap_random_spot.glsl", infoLog);
		if( m_shad_pcf_8tap_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_pcf_8tap_random_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_pcf_8tap_random_spot shader loaded successfully", COLOR_WHITE );
		}
		
		m_shad_pcf_gaussian_spot_prog = LoadShaderProgram( "Assets/Engine/shaders/shadow/spot/shadow_pcf_gaussian_spot.glsl", infoLog);
		if( m_shad_pcf_gaussian_spot_prog == 0 )
		{
			//if( infoLog.c_str() )
			//{
			//	PrintShaderLog( "\n" );
			//	PrintShaderLog( infoLog.c_str() );
			//}
			//PrintInfo( "\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/shadow_pcf_gaussian_spot.glsl", COLOR_RED );
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo( "\nshadow/spot/shadow_pcf_gaussian_spot shader loaded successfully", COLOR_WHITE );
		}

		/////////////////////////////////////////////

		//shadow spot + normal map
		m_shad_single_hl_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_single_hl_spot_normal.glsl", infoLog);
		if (m_shad_single_hl_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_single_hl_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_single_hl_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_multi_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_multi_leak_spot_normal.glsl", infoLog);
		if (m_shad_multi_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_multi_leak_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_multi_leak_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_single_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_single_spot_normal.glsl", infoLog);
		if (m_shad_single_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_single_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_single_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_multi_noleak_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_multi_noleak_spot_normal.glsl", infoLog);
		if (m_shad_multi_noleak_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_multi_noleak_spot_normal", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_multi_noleak_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_spot_normal.glsl", infoLog);
		if (m_shad_pcf_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_pcf_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_trilin_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_trilinear_spot_normal.glsl", infoLog);
		if (m_shad_pcf_trilin_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_trilinear_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_pcf_trilinear_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_4tap_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_4tap_spot_normal.glsl", infoLog);
		if (m_shad_pcf_4tap_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_4tap_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_pcf_4tap_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_8tap_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_8tap_random_spot_normal.glsl", infoLog);
		if (m_shad_pcf_8tap_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_8tap_random_spot_normal.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_pcf_8tap_random_spot_normal shader loaded successfully", COLOR_WHITE);
		}

		m_shad_pcf_gaussian_spot_normal_prog = LoadShaderProgram("Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_gaussian_spot_normal.glsl", infoLog);
		if (m_shad_pcf_gaussian_spot_normal_prog == 0)
		{
			//if (infoLog.c_str())
			//{
			//	PrintShaderLog("\n");
			//	PrintShaderLog(infoLog.c_str());
			//}
			//PrintInfo("\nCouldn't load shader : Assets/Engine/shaders/shadow/spot/spot_normal/shadow_pcf_gaussian_spot_normal.glsl.glsl", COLOR_RED);
			infoLog.erase();
			m_shaderAvailable = CTrue;
			m_shadowShaderAvailable = CFalse;
			return;
		}
		else
		{
			//PrintInfo("\nshadow/spot/spot_normal/shadow_pcf_gaussian_spot_normal.glsl shader loaded successfully", COLOR_WHITE);
		}

		//////////////////////////

		infoLog.erase();
		m_shaderAvailable = CTrue;
	}
	//initialize default free camera
	CCamera * default_camera = CNew( CCamera ); 
	default_camera->SetName( "default_camera" );	
	default_camera->SetZNear(1.0);
	default_camera->SetZFar(10000.0);
		
	// new CNode
	CNode * camNode = CNew( CNode ); 

	// new CInstanceCamera
	CInstanceCamera *instanceCamera = CNew(CInstanceCamera);
	instanceCamera->m_abstractCamera = default_camera;
	instanceCamera->m_parent = camNode;
	instanceCamera->MoveTransform2(5, 5, 5 );
	instanceCamera->SetPanAndTilt2(43, -25 );

	g_render.m_defaultInstanceCamera = instanceCamera;

}

CBool CRender::InitCg()
{
	//// Create a context for the CG programs we are going to load and validate it was successful
	//m_cgContext = cgCreateContext();
	//if (m_cgContext == NULL)
	//{
	//	MessageBox(NULL, _T("Failed To Create Cg Context"), _T(" VandaEngine Error"), MB_OK );
	//	return CFalse;
	//}
	//// Register GL states (ugly crashes if you don't do this)
	//cgGLRegisterStates(m_cgContext);

	//// Get The Latest GL Vertex Profile
	//m_cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);				
	//m_cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
 //   
	//// Validate Our Profile Determination Was Successful
	//if (m_cgVertexProfile == CG_PROFILE_UNKNOWN || m_cgFragmentProfile == CG_PROFILE_UNKNOWN)
	//{
	//	MessageBox(NULL, _T("Invalid profile type"), _T("Error"), MB_OK);
	//	return CFalse;			
	//}

	//// Set The Current Profile
	//cgGLSetOptimalOptions(m_cgVertexProfile);
	//cgGLSetOptimalOptions(m_cgFragmentProfile);

	//// Check for errors
	//if(!CheckForCgError())
	//	return CFalse;
	////PrintInfo( "Cg context created successfully\n", COLOR_WHITE );
	return CTrue; 
}

CBool CRender::CheckForCgError()
{
	//CGerror Error = cgGetError();
	//if ( Error != CG_NO_ERROR )
	//{    
	//	// Show A Message Box Explaining What Went Wrong
	//	//CChar tempChar[ MAX_NAME_SIZE];
	//	//sprintf( tempChar, "Cg Error : %s\n", (char *)cgGetErrorString(Error) );
	//	//PrintInfo( tempChar );
	//	MessageBox(NULL, (CWChar *)cgGetErrorString(Error), _T("VandaEngine Error"), MB_OK);
	//	MessageBox( NULL, _T("Switching to Fixed Function OpenGL"), _T("VandaEngine Error"), MB_OK);

	//	DisableCgProfiles();
	//	DisableCg(); 

	//	return CFalse; 
	//}
	return CTrue;
}

CBool CRender::DisableCgProfiles()
{
	//if ( m_cgInitialized )
	//{
	//	// Disable Vertex & fragment Profiles
	//	cgGLDisableProfile(m_cgVertexProfile);	
	//	cgGLDisableProfile(m_cgFragmentProfile);	
		return CTrue; 
	//}
	//return CFalse;
}

CVoid CRender::DisableCg()
{
	//m_cgInitialized = CFalse;
} 


CVoid CRender::Destroy()
{
	//if ( m_cgInitialized )
	//	DestroyCg(); 
	glDeleteProgram(m_shaderProgram);
	glDeleteProgram(m_shader_normalProgram);
	glDeleteProgram(m_spotShaderProgram);
	glDeleteProgram(m_spot_normalShaderProgram);
	glDeleteProgram(m_waterProgram);
	glDeleteProgram(m_blurProgram);
	glDeleteProgram(m_glowProgram);
	glDeleteProgram(m_grassProgram);
	glDeleteProgram(m_fogBlurProgram);
	glDeleteProgram(m_waterFogBlurProgram);
	glDeleteProgram(m_dofProgram[0]);
	glDeleteProgram(m_dofProgram[1]);
	glDeleteProgram(m_dofProgram[2]);
	glDeleteProgram(m_dofProgram[3]);

	glDeleteProgram(m_shad_single_hl_prog);
	glDeleteProgram(m_shad_single_prog);
	glDeleteProgram(m_shad_multi_prog);
	glDeleteProgram(m_shad_multi_noleak_prog);
	glDeleteProgram(m_shad_pcf_prog);
	glDeleteProgram(m_shad_pcf_trilin_prog);
	glDeleteProgram(m_shad_pcf_4tap_prog);
	glDeleteProgram(m_shad_pcf_8tap_prog);
	glDeleteProgram(m_shad_pcf_gaussian_prog);

	glDeleteProgram(m_shad_single_hl_normal_prog);
	glDeleteProgram(m_shad_single_normal_prog);
	glDeleteProgram(m_shad_multi_normal_prog);
	glDeleteProgram(m_shad_multi_noleak_normal_prog);
	glDeleteProgram(m_shad_pcf_normal_prog);
	glDeleteProgram(m_shad_pcf_trilin_normal_prog);
	glDeleteProgram(m_shad_pcf_4tap_normal_prog);
	glDeleteProgram(m_shad_pcf_8tap_normal_prog);
	glDeleteProgram(m_shad_pcf_gaussian_normal_prog);

	glDeleteProgram(m_shad_view_depth);

	glDeleteProgram(m_shad_single_hl_spot_prog);
	glDeleteProgram(m_shad_single_spot_prog);
	glDeleteProgram(m_shad_multi_spot_prog);
	glDeleteProgram(m_shad_multi_noleak_spot_prog);
	glDeleteProgram(m_shad_pcf_spot_prog);
	glDeleteProgram(m_shad_pcf_trilin_spot_prog);
	glDeleteProgram(m_shad_pcf_4tap_spot_prog);
	glDeleteProgram(m_shad_pcf_8tap_spot_prog);
	glDeleteProgram(m_shad_pcf_gaussian_spot_prog);

	glDeleteProgram(m_shad_single_hl_spot_normal_prog);
	glDeleteProgram(m_shad_single_spot_normal_prog);
	glDeleteProgram(m_shad_multi_spot_normal_prog);
	glDeleteProgram(m_shad_multi_noleak_spot_normal_prog);
	glDeleteProgram(m_shad_pcf_spot_normal_prog);
	glDeleteProgram(m_shad_pcf_trilin_spot_normal_prog);
	glDeleteProgram(m_shad_pcf_4tap_spot_normal_prog);
	glDeleteProgram(m_shad_pcf_8tap_spot_normal_prog);
	glDeleteProgram(m_shad_pcf_gaussian_spot_normal_prog);

	glDeleteProgram(m_blendTexturesProgram);

}

CBool CRender::DestroyCg()
{
	// Destroy Our Cg Context And All Programs Contained Within It
	//cgDestroyContext(m_cgContext);
	//m_cgContext = NULL;

	return CTrue; 
}

CVoid CRender::LoadMatrix( CFloat * mat )
{
	glLoadMatrixf(mat);
}

CVoid CRender::PushMatrix()
{
	glPushMatrix();
}

CVoid CRender::MultMatrix( CFloat * mat )
{
	glMultMatrixf(mat);
}

CVoid CRender::PopMatrix()
{
	glPopMatrix();
}

CVoid CRender::ProjectionMatrix()
{
	glMatrixMode( GL_PROJECTION );
}

CVoid CRender::IdentityMatrix()
{
	glLoadIdentity();
}

CVoid CRender::ModelViewMatrix()
{
	glMatrixMode( GL_MODELVIEW );
}



CBool CRender::CheckForVBOs()
{
	if( GLEW_ARB_vertex_buffer_object )
	{
		m_VBOsAvailable = CTrue;
		m_useVBOs = CTrue;
	}
	else
	{
		m_VBOsAvailable = CFalse;
		m_useVBOs = CFalse;
		MessageBox( NULL, _T("VBO is not supported."), _T("VandaEngine Error"), MB_OK );
	}
	return CTrue; //To disable warning
}

CUInt CRender::GenerateVBO()
{
	if ( m_VBOsAvailable )
	{
		CUInt vboId; 
		glGenBuffers( 1, &vboId );					
		return vboId; 
	}
	return -1; //No VBO
}


CBool CRender::BindVBO( CUInt type, CUInt vboId )
{
	if ( m_VBOsAvailable )
	{
		glBindBuffer(type, vboId );
		return CTrue;
	}
	else 
		return CFalse; 
}

CBool CRender::CopyVBOData( CUInt type, CUInt vboId, CVoid * data, CInt size )
{
	if ( m_VBOsAvailable && vboId > 0 )
	{		
		glBindBuffer( type, vboId );			
		glBufferData( type, size, data, GL_STATIC_DRAW );
		return CTrue; 
	}
	return CFalse; 
}

CBool CRender::CopyVBOSubData( CUInt type, CUInt vboId, CVoid * data, CUInt offset, CInt size )
{
	if ( m_VBOsAvailable && vboId > 0 )
	{		
		glBindBuffer( type, vboId );			
		glBufferSubData( type, offset, size, data );
		return CTrue; 
	}
	return CFalse; 
}

CVoid CRender::FreeVBO( CUInt vboId )
{
	if( m_VBOsAvailable && vboId > 0 )
	{
		glDeleteBuffers( 1, &vboId );
	}
}

CBool CRender::CheckForFBOs()
{
	if( GLEW_EXT_framebuffer_object )
	{
		m_FBOsAvailable = CTrue;
		m_useFBOs = CTrue;
	}
	else
	{
		m_FBOsAvailable = CFalse;
		m_useFBOs = CFalse;
		MessageBox( NULL, _T("FBO is not supported."), _T("VandaEngine Error"), MB_OK );
	}
	return CTrue; //To disable warning
}

CUInt CRender::GenerateFBO()
{
	if ( m_FBOsAvailable )
	{
		CUInt fboId; 
		glGenFramebuffersEXT( 1, &fboId );					
		return fboId; 
	}
	return -1; //No FBO
}

CBool CRender::BindFBO( CUInt fboId )
{
	if ( m_FBOsAvailable )
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fboId );
		return CTrue;
	}
	else 
		return CFalse; 
}

CVoid CRender::FreeFBO( CUInt fboId )
{
	if( m_FBOsAvailable && fboId > 0 )
	{
		glDeleteFramebuffersEXT( 1, &fboId );
	}
}

CVoid CRender::Attach2DTextureToFBOColor( CUInt textureId, CInt colorBufferId )
{
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + colorBufferId, GL_TEXTURE_2D, textureId, 0);
}

CVoid CRender::AttachRenderBufferToFBOColor( CUInt m_rbColorID, CInt colorBufferId )
{
   glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT + colorBufferId, GL_RENDERBUFFER_EXT, m_rbColorID);

}

CUInt CRender::GenerateRenderBuffer()
{
	if ( m_FBOsAvailable )
	{
		CUInt rbId;
		glGenRenderbuffersEXT( 1, &rbId );
		return rbId;
	}
	return -1;
}

CBool CRender::BindRenderBuffer( CUInt rbId )
{
	if ( m_FBOsAvailable )
	{
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbId );
		return CTrue;
	}
	else 
		return CFalse; 
}

CVoid CRender::RenderbufferStorage( CUInt width, CUInt height )
{
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, width, height );
}

CVoid CRender::RenderbufferDepthStorageMultisample( CInt numSamples, CUInt width, CUInt height )
{
	GLint samples;
	glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
	if( numSamples < samples )
		glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, numSamples, GL_DEPTH_COMPONENT24, width, height);
	else
		glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, GL_DEPTH_COMPONENT24, width, height);
}

CVoid CRender::RenderbufferColorStorageMultisample( CInt numSamples, CInt type, CUInt width, CUInt height )
{
	GLint samples;
	glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
	if( numSamples < samples )
		glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, numSamples, type, width, height);
	else
		glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, samples, type, width, height);
}

CVoid CRender::AttachDepthToFBO( CUInt rbId )
{
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbId );
}

CVoid CRender::FreeRenderBuffer( CUInt rbId )
{
	if( m_FBOsAvailable && rbId > 0 )
	{
		glDeleteRenderbuffersEXT( 1, &rbId );
	}
}

CVoid CRender::SetMaterial( CMaterial * mat, CBool isSelected, CBool hasDiffuse )
{
	CEffect *effect = mat->GetEffect();
	assert(effect);  // In COLLADA 1.4 a material is required to have a reference to an effect
	
	CColor4f emission = effect->GetEmission();
	CColor4f ambient;
	CColor4f diffuse;;
	diffuse.a = effect->m_transparency;
	if( isSelected )
		ambient = diffuse = CColor4f( 0.7f, 0.0f, 0.6f, 1.0f );
	else
	{
		if( g_useGlobalAmbientColor )
			ambient = g_globalAmbientColor;
		else
			ambient = effect->GetAmbient();
		diffuse = effect->GetDiffuse();
	}
	CColor4f specular =	effect->GetSpecular();
	CFloat	shininess = effect->GetShininess();
	if (shininess < 1.0) shininess = (CFloat) (shininess * 100.0); // if the scale is 0.0 to 1.0, make it 0.0 to 100.0


	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION , (GLfloat*)&emission );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT  , (GLfloat*)&ambient );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE  , (GLfloat*)&diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR , (GLfloat*)&specular );
	glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS, (GLfloat )shininess );

	//if	( !hasDiffuse && effect->m_textures.empty() )
	//{
	//	if( g_render.UsingShader() && g_render.m_useShader && g_options.m_enableShader )
	//		glUniform1i(glGetUniformLocation( g_render.m_shaderProgram , "enableColorMap"), CFalse );
	//	glDisable(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	for (CUInt i=0; i<effect->m_textures.size(); i++)
	//	{
	//		SetTexture( effect->m_textures[i], hasDiffuse ); 
	//		break; //It means that I just support one color map right now
	//	}
	//}

	SetCurrentMaterial( mat );
}

CBool CRender::SetTexture( CImage * texObj, CBool hasDiffuse )
{
	if ((CInt) texObj->GetId() == -1 )
	{
		glDisable(GL_TEXTURE_2D);	
		if( g_render.UsingShader() && g_render.m_useShader && g_options.m_enableShader )
			glUniform1i(glGetUniformLocation( g_render.m_shaderProgram , "enableColorMap"), CFalse );
		return CFalse; 
	}
	else
	{
		if( !hasDiffuse )
		{
			// Enable Texture Mapping
			glActiveTexture( GL_TEXTURE0 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture(GL_TEXTURE_2D, texObj->GetId());
			if(  g_render.UsingShader() && g_render.m_useShader && g_options.m_enableShader)
			{
				glUniform1i(glGetUniformLocation( g_render.m_shaderProgram , "colorMap"), 0);
				glUniform1i(glGetUniformLocation( g_render.m_shaderProgram , "enableColorMap"), CTrue );
			}
		}
	}

	return CTrue; 
}

//This function opens the cfg file and parses it
CBool CRender::ParsePublishFile( CStringW strFilename )
{
	CBool foundTarget = CFalse;
	// open the model configuration file
	std::ifstream file;
	file.open( strFilename, std::ios::in );
	//We may use uincode strings for our strFilename, but we don't use unicode strings 
	//inside our txt file( we use pure english ).m_report is used for representing texts
	//inside the txt file.

	if(!file)
	{
		//strFileName may contanin unicode strings
		MessageBox( NULL, _T( "Couldn't open the VPF file"), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
 		file.close();
		return false;
	}

	// parse all lines from the publish file
	int line;
	for(line = 1; ; line++)
	{
		// read the next model configuration line
		std::string strBuffer;
		std::getline(file, strBuffer);

		// stop if we reached the end of file
		if(file.eof()) break;

		// check if an error happend while reading from the file
		if(!file)
		{
			MessageBox( NULL, _T( "Couldn't open the VPF file"), _T("VandaEngine Error"), MB_OK | MB_ICONERROR );
			return false;
		}

		// find the first non-whitespace character
		std::string::size_type pos;
		pos = strBuffer.find_first_not_of(" \t");

		// check for empty lines
		if((pos == std::string::npos) || (strBuffer[pos] == '\n') || (strBuffer[pos] == '\r') || (strBuffer[pos] == 0)) continue;

		// check for comment lines
		if(strBuffer[pos] == '#') continue;

		// get the key
		std::string strKey;
		strKey = strBuffer.substr(pos, strBuffer.find_first_of(" =\t\n\r", pos) - pos);
		pos += strKey.size();

		// get the '=' character
		pos = strBuffer.find_first_not_of(" \t", pos);
		if((pos == std::string::npos) || (strBuffer[pos] != '='))
		{
			return false;
		}

		// find the first non-whitespace character after the '=' character
		pos = strBuffer.find_first_not_of(" \t", pos + 1);

		// get the data
		std::string strData;
		strData = strBuffer.substr(pos, strBuffer.find_first_of("\n\r", pos) - pos);

		// handle the model creation
		if(strKey == "file")
        {
            // set the new path for the data files if one hasn't been set already
			foundTarget = CTrue;
            m_savedFile = strData;
        }
		else
		{
			// everything else is ignored
		}
	}

	// explicitely close the file
	file.close();
	if( foundTarget )
		return CTrue;
	else
		return CFalse;
}

GLuint CRender::LinkShaders(GLuint vertShader, GLuint fragShader)
{
    // Links the compiled vertex and/or fragment shaders into an executable
    // shader program. Returns the executable shader object. If the shaders
    // failed to link into an executable shader program, then a std::string
    // object is thrown containing the info log.

    GLuint program = glCreateProgram();

    if (program)
    {
        GLint linked = 0;

        if (vertShader)
            glAttachShader(program, vertShader);

        if (fragShader)
            glAttachShader(program, fragShader);

		glBindFragDataLocation(program, 0, "myVec40");

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &linked);

        if (!linked)
        {
            GLsizei infoLogSize = 0;
            std::string infoLog;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogSize);
            infoLog.resize(infoLogSize);
            glGetProgramInfoLog(program, infoLogSize, &infoLogSize, &infoLog[0]);

            throw infoLog;
        }

        // Mark the two attached shaders for deletion. These two shaders aren't
        // deleted right now because both are already attached to a shader
        // program. When the shader program is deleted these two shaders will
        // be automatically detached and deleted.

        if (vertShader)
            glDeleteShader(vertShader);

        if (fragShader)
            glDeleteShader(fragShader);
    }

    return program;
}

GLuint CRender::CompileShader(GLenum type, const GLchar *pszSource, GLint length)
{
    // Compiles the shader given it's source code. Returns the shader object.
    // A std::string object containing the shader's info log is thrown if the
    // shader failed to compile.
    //
    // 'type' is either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
    // 'pszSource' is a C style string containing the shader's source code.
    // 'length' is the length of 'pszSource'.

    GLuint shader = glCreateShader(type);

    if (shader)
    {
        GLint compiled = 0;

        glShaderSource(shader, 1, &pszSource, &length);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLsizei infoLogSize = 0;
            std::string infoLog;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
            infoLog.resize(infoLogSize);
            glGetShaderInfoLog(shader, infoLogSize, &infoLogSize, &infoLog[0]);

            throw infoLog;
        }
    }

    return shader;
}

GLuint CRender::LoadShaderProgram(const char *pszFileName, std::string &infoLog)
{
	if( !pszFileName )
		return 0;
    infoLog.clear();

    GLuint program = 0;
    std::string buffer;

    // Read the text file containing the GLSL shader program.
    // This file contains 1 vertex shader and 1 fragment shader.
    ReadTextFile(pszFileName, buffer);

    // Compile and link the vertex and fragment shaders.
    if (buffer.length() > 0)
    {
        const GLchar *pSource = 0;
        GLint length = 0;
        GLuint vertShader = 0;
        GLuint fragShader = 0;

        std::string::size_type vertOffset = buffer.find("[vert]");
        std::string::size_type fragOffset = buffer.find("[frag]");

        try
        {
            // Get the vertex shader source and compile it.
            // The source is between the [vert] and [frag] tags.
            if (vertOffset != std::string::npos)
            {
                vertOffset += 6;        // skip over the [vert] tag
                pSource = reinterpret_cast<const GLchar *>(&buffer[vertOffset]);
                length = static_cast<GLint>(fragOffset - vertOffset);
                vertShader = CompileShader(GL_VERTEX_SHADER, pSource, length);
            }

            // Get the fragment shader source and compile it.
            // The source is between the [frag] tag and the end of the file.
            if (fragOffset != std::string::npos)
            {
                fragOffset += 6;        // skip over the [frag] tag
                pSource = reinterpret_cast<const GLchar *>(&buffer[fragOffset]);
                length = static_cast<GLint>(buffer.length() - fragOffset - 1);
                fragShader = CompileShader(GL_FRAGMENT_SHADER, pSource, length);
            }
			if( buffer.length() )
				buffer.erase(); //we no longer need buffer.
            // Now link the vertex and fragment shaders into a shader program.
            program = LinkShaders(vertShader, fragShader);
        }
        catch (const std::string &errors)
        {
            infoLog = errors;
        }
    }

    return program;
}

CVoid CRender::ReadTextFile(const char *pszFilename, std::string &buffer)
{
    std::ifstream file(pszFilename, std::ios::binary);

    if (file.is_open())
    {
        file.seekg(0, std::ios::end);

        std::ifstream::pos_type fileSize = file.tellg();

        buffer.resize(fileSize);
        file.seekg(0, std::ios::beg);
        file.read(&buffer[0], fileSize);
    }
}

CBool CRender::SetInstanceLight( CInstanceLight * lightInstance, CInt lightNumber, CBool markDefaultDirectionalLight   )
{
	CVec4f  Position;
	if( lightInstance->m_parent )
	{
		float *matrix = (float *)lightInstance->m_parent->GetLocalToWorldMatrix();
		Position.x = matrix[12]; Position.y = matrix[13]; Position.z =  matrix[14]; Position.w = 1.0f; 
	}
	CColor4f color = lightInstance->m_abstractLight->GetColor();
	switch(lightInstance->m_abstractLight->GetType())
	{
		case eLIGHTTYPE_AMBIENT:
			//glLightfv( GL_LIGHT0+lightNumber, GL_AMBIENT , (GLfloat*)&color);
			return CFalse;
		case eLIGHTTYPE_DIRECTIONAL:
			glEnable(GL_LIGHT0+lightNumber);

			if( lightInstance->m_parent )
			{
				CVec3f  olddirection(0.0f, 0.0f, 1.0f);
				CVec3f  newdirection;//(0.0f, -1.0f, 0.0f);
				float * localmatrix = (float *) lightInstance->m_parent->GetLocalToWorldMatrix();
				CMatrixRotate(localmatrix, olddirection, newdirection);
				GLfloat lightDir[4] = { newdirection.x, newdirection.y, newdirection.z, 0.0f };
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION, lightDir );
				if( markDefaultDirectionalLight )
				{
					g_defaultDirectionalLight.x = lightDir[0]; g_defaultDirectionalLight.y = lightDir[1]; g_defaultDirectionalLight.z = lightDir[2]; g_defaultDirectionalLight.w = 1.0f;
				}
			}
			else
			{
				float * position = lightInstance->m_abstractLight->GetPosition();
				position[3] = 0.0f; //directioal light
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION, position );
				if( markDefaultDirectionalLight )
				{
					g_defaultDirectionalLight.x = position[0]; g_defaultDirectionalLight.y = position[1]; g_defaultDirectionalLight.z = position[2]; g_defaultDirectionalLight.w = 0.0f;
				}
			}

			glLightfv( GL_LIGHT0+lightNumber, GL_AMBIENT , lightInstance->m_abstractLight->GetAmbient() );
			glLightfv( GL_LIGHT0+lightNumber, GL_DIFFUSE , lightInstance->m_abstractLight->GetDiffuse() );
			glLightfv( GL_LIGHT0+lightNumber, GL_SPECULAR, lightInstance->m_abstractLight->GetSpecular() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SPOT_CUTOFF, (GLfloat)180.0f );
			glLightf ( GL_LIGHT0+lightNumber, GL_CONSTANT_ATTENUATION , (GLfloat)lightInstance->m_abstractLight->GetConstantAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_LINEAR_ATTENUATION,	(GLfloat)lightInstance->m_abstractLight->GetLinearAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_QUADRATIC_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetQuadraticAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SHININESS, (GLfloat)lightInstance->m_abstractLight->GetShininess() );

			return true;
		case eLIGHTTYPE_POINT:
			glEnable(GL_LIGHT0+lightNumber);

			if( lightInstance->m_parent )
			{
				if( Position.x == 0.0 && Position.z == 0.0 )
					Position.x = Position.z = EPSILON;
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION, (GLfloat*)&Position );
				//if( markDefaultDirectionalLight )
				//{
				//	g_defaultDirectionalLight.x = Position.x; g_defaultDirectionalLight.y = Position.y; g_defaultDirectionalLight.z = Position.z; g_defaultDirectionalLight.w = 1.0f;
				//}
			}
			else
			{
				float * position = lightInstance->m_abstractLight->GetPosition();
				if( position[0] == 0.0 && position[2] == 0.0 )
					position[0] = position[2] = EPSILON;
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION, position );

				//if( markDefaultDirectionalLight )
				//{
				//	g_defaultDirectionalLight.x = position[0]; g_defaultDirectionalLight.y = position[1]; g_defaultDirectionalLight.z = position[2]; g_defaultDirectionalLight.w = 1.0f;
				//}
			}
			glLightfv( GL_LIGHT0+lightNumber, GL_AMBIENT , lightInstance->m_abstractLight->GetAmbient() );
			glLightfv( GL_LIGHT0+lightNumber, GL_DIFFUSE , lightInstance->m_abstractLight->GetDiffuse() );
			glLightfv( GL_LIGHT0+lightNumber, GL_SPECULAR, lightInstance->m_abstractLight->GetSpecular() );
			//glLightf ( GL_LIGHT0+lightNumber, GL_SPOT_CUTOFF, (GLfloat)180.0f );
			glLightf ( GL_LIGHT0+lightNumber, GL_CONSTANT_ATTENUATION , (GLfloat)lightInstance->m_abstractLight->GetConstantAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_LINEAR_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetLinearAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_QUADRATIC_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetQuadraticAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SHININESS, (GLfloat)lightInstance->m_abstractLight->GetShininess() );

			return true;
		case eLIGHTTYPE_SPOT:
			glEnable(GL_LIGHT0+lightNumber);
			if( lightInstance->m_parent )
			{
				CVec3f  olddirection(0.0f, 0.0f, -1.0f);
				CVec3f  newdirection;//(0.0f, -1.0f, 0.0f);
				float * localmatrix = (float *) lightInstance->m_parent->GetLocalToWorldMatrix();
				CMatrixRotate(localmatrix, olddirection, newdirection);
		
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION,		(GLfloat*)&Position );
				glLightfv( GL_LIGHT0+lightNumber, GL_SPOT_DIRECTION, (GLfloat*) &newdirection );
			}
			else
			{
				glLightfv( GL_LIGHT0+lightNumber, GL_POSITION, lightInstance->m_abstractLight->GetPosition() );
				glLightfv( GL_LIGHT0+lightNumber, GL_SPOT_DIRECTION, lightInstance->m_abstractLight->GetSpotDirection() );
			}
			glLightfv( GL_LIGHT0+lightNumber, GL_AMBIENT , lightInstance->m_abstractLight->GetAmbient() );
			glLightfv( GL_LIGHT0+lightNumber, GL_DIFFUSE, lightInstance->m_abstractLight->GetDiffuse() );
			glLightfv( GL_LIGHT0+lightNumber, GL_SPECULAR, lightInstance->m_abstractLight->GetSpecular() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SPOT_CUTOFF, (GLfloat ) lightInstance->m_abstractLight->GetSpotCutoff() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SPOT_EXPONENT, (GLfloat ) lightInstance->m_abstractLight->GetSpotExponent() );
			glLightf ( GL_LIGHT0+lightNumber, GL_CONSTANT_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetConstantAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_LINEAR_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetLinearAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_QUADRATIC_ATTENUATION, (GLfloat)lightInstance->m_abstractLight->GetQuadraticAttenuation() );
			glLightf ( GL_LIGHT0+lightNumber, GL_SHININESS, (GLfloat)lightInstance->m_abstractLight->GetShininess() );

			return true;
		default:
			return false;
	}
}


void CRender::DrawSphere( GLdouble radius, GLint slices, GLint stacks, CFloat* pos, CFloat* diffuseColor )
{
	glPushMatrix();
	glTranslatef( pos[0], pos[1], pos[2] );
	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
	glDisable( GL_LIGHTING );
	glLineWidth( 1.0f );
	glColor4f( diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3] );
	glutWireSphere( radius, slices, stacks);
	glPopAttrib();
	glPopMatrix();
}

GLvoid CRender::DrawSolidSphere(GLdouble radius, GLint slices, GLint stacks, CFloat* pos, CFloat* diffuseColor)
{
	glUseProgram(0);

	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
	glDisable(GL_LIGHTING);
	glColor4f(diffuseColor[0], diffuseColor[1], diffuseColor[2], diffuseColor[3]);
	glutSolidSphere(radius, slices, stacks);
	glPopAttrib();
	glPopMatrix();
}

void CRender::DrawCube( GLdouble size, CFloat* pos )
{
	glPushMatrix();
	glTranslatef( pos[0], pos[1], pos[2] );
	glPushAttrib( GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LINE_BIT);
	glDisable( GL_LIGHTING );
	glLineWidth( 1.0f );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glutWireCube( size );
	glPopAttrib();
	glPopMatrix();
}

CBool CRender::BindForWriting(CUInt fboId)
{
	if ( m_FBOsAvailable )
	{
	    glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, fboId);
		return CTrue;
	}
	else
		return CFalse;
}

CBool CRender::BindForReading(CUInt fboId)
{
	if ( m_FBOsAvailable )
	{
	    glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, fboId);
		return CTrue;
	}
	else
		return CFalse;
}

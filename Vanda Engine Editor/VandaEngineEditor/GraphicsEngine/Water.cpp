//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "water.h"
#include "texture.h"
#include "render.h"
#include "scene.h"
#include "../VandaEngineEditorDlg.h"
#include "PerspectiveWindow.h"

const float kNormalMapScale = 0.25f;

CWater::CWater()
{
	m_instancePrefab.clear();
	SetIndex();
	m_isVisible = CTrue;
	m_shadow = CTrue;
	m_sunReflection = CTrue;
	m_move = 0.0f;
	if (GLEW_NV_occlusion_query)
	{
		glGenQueries(1, &m_queryIndex);
	}
	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");

	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CWater::~CWater()
{
	glDeleteTextures( MAX_WATER_TEXTURES, m_waterTexture );
	glDeleteFramebuffersEXT( MAX_WATER_TEXTURES, m_fboID );
	glDeleteRenderbuffersEXT(MAX_WATER_TEXTURES, m_rbID );
	glDeleteQueries(1, &m_queryIndex);
	m_VSceneList.clear(); //save functions
	m_instanceName.clear();
	LuaClose(m_lua);
}

CVoid CWater::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CWater::LoadLuaFile()
{
	ResetLua();

	if (!m_hasScript)
	{
		return CFalse;
	}

	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

GLuint CWater::GetQueryIndex()
{
	return m_queryIndex;
}

CFloat CWater::GetDistanceFromCamera()
{
	return m_distanceFromCamera;
}

CVoid CWater::CalculateDistance()
{
	if (g_camera)
	{
		CVec3f center(m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2]);
		CFloat x = g_camera->m_perspectiveCameraPos.x - center.x;
		CFloat y = g_camera->m_perspectiveCameraPos.y - center.y;
		CFloat z = g_camera->m_perspectiveCameraPos.z - center.z;

		m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
}

void CWater::CreateRenderTexture( CInt size, CInt channels, CInt type, CInt textureID)										
{

	glGenTextures(1, &m_waterTexture[textureID]);								
	glBindTexture(GL_TEXTURE_2D, m_waterTexture[textureID]);					
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
	{
		glGenerateMipmapEXT( GL_TEXTURE_2D );
		glTexImage2D(GL_TEXTURE_2D, 0, channels, size, size, 0, type, GL_UNSIGNED_BYTE, NULL );
		m_fboID[textureID] = g_render.GenerateFBO();
		g_render.BindFBO( m_fboID[textureID] );
		g_render.Attach2DTextureToFBOColor( m_waterTexture[textureID] );
		m_rbID[textureID] = g_render.GenerateRenderBuffer();
		g_render.BindRenderBuffer( m_rbID[textureID] );
		g_render.RenderbufferStorage( size, size );
		g_render.AttachRenderBufferToFBODepth( m_rbID[textureID] );
		g_render.BindFBO(0);
		g_render.BindRenderBuffer(0);

		GLenum status;
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		switch(status)
		{
			case GL_FRAMEBUFFER_COMPLETE_EXT:
				break;
			default:
				PrintInfo( "\nAn error occured while creating the FBO for water", COLOR_RED );
				break;
		}
	}
	else
	{
		glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST );
		CUInt *pTexture = NULL;											
		pTexture = CNewData( CUInt, size * size * channels );
		memset(pTexture, 0, size * size * channels * sizeof(CUInt));	
		glTexImage2D(GL_TEXTURE_2D, 0, channels, size, size, 0, type, GL_UNSIGNED_BYTE, pTexture);
		CDeleteData( pTexture );																					
	}
	glBindTexture(GL_TEXTURE_2D, 0);


}

CFloat CWater::GetRadius()
{
	CVec3f center(m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2]);
	return (m_sidePoint[0] - center).Size();
}

void CWater::SetSideVertexPositions()
{
	m_sidePoint[0].x = m_fWaterCPos[0] -m_fWaterScaleX/2.0f;
	m_sidePoint[0].y = m_fWaterCPos[1];
	m_sidePoint[0].z = m_fWaterCPos[2]-m_fWaterScaleZ/2.0f;

	m_sidePoint[1].x = m_fWaterCPos[0]-m_fWaterScaleX/2.0f;
	m_sidePoint[1].y = m_fWaterCPos[1];
	m_sidePoint[1].z = m_fWaterCPos[2]+m_fWaterScaleZ/2.0f;

	m_sidePoint[2].x = m_fWaterCPos[0]+m_fWaterScaleX/2.0f;
	m_sidePoint[2].y = m_fWaterCPos[1];
	m_sidePoint[2].z = m_fWaterCPos[2]+m_fWaterScaleZ/2.0f;

	m_sidePoint[3].x = m_fWaterCPos[0]+m_fWaterScaleX/2.0f;
	m_sidePoint[3].y = m_fWaterCPos[1];
	m_sidePoint[3].z = m_fWaterCPos[2]-m_fWaterScaleZ/2.0f;

	CVec3f m_sidePointV[4];

	CMatrix transform;
	CMatrixLoadIdentity(transform);
	CMatrixTranslate(transform, m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2]);
	CMatrix4x4RotateAngleAxis(transform, 0.0f, 1.0f, 0.0f, m_fWaterRotateY);
	CMatrixTranslate(transform, -m_fWaterCPos[0], -m_fWaterCPos[1], -m_fWaterCPos[2]);

	CMatrixTransform(transform, m_sidePoint[0], m_sidePointV[0]);
	CMatrixTransform(transform, m_sidePoint[1], m_sidePointV[1]);
	CMatrixTransform(transform, m_sidePoint[2], m_sidePointV[2]);
	CMatrixTransform(transform, m_sidePoint[3], m_sidePointV[3]);

	m_sidePointNoRotate[0] = m_sidePoint[0];
	m_sidePointNoRotate[1] = m_sidePoint[1];
	m_sidePointNoRotate[2] = m_sidePoint[2];
	m_sidePointNoRotate[3] = m_sidePoint[3];

	m_sidePoint[0] = m_sidePointV[0];
	m_sidePoint[1] = m_sidePointV[1];
	m_sidePoint[2] = m_sidePointV[2];
	m_sidePoint[3] = m_sidePointV[3];
}

CBool CWater::IsPointInWater(CVec3f point)
{
	CVec3f pointV;
	CMatrix transform;
	CMatrixLoadIdentity(transform);
	CMatrixTranslate(transform, m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2]);
	CMatrix4x4RotateAngleAxis(transform, 0.0f, 1.0f, 0.0f, -m_fWaterRotateY);
	CMatrixTranslate(transform, -m_fWaterCPos[0], -m_fWaterCPos[1], -m_fWaterCPos[2]);
	CMatrixTransform(transform, point, pointV);

	CFloat xmin, xmax, zmin, zmax;

	xmin = m_sidePointNoRotate[0].x; zmin = m_sidePointNoRotate[0].z;
	xmax = m_sidePointNoRotate[2].x; zmax = m_sidePointNoRotate[2].z;

	if (pointV.x > xmin && pointV.x < xmax && pointV.z > zmin && pointV.z < zmax)
		return CTrue;

	return CFalse;
}

CBool CWater::IsPointAboveWater(CVec3f point)
{
	CVec4f waterPlane(0.0f, 1.0f, 0.0f, m_fWaterCPos[1]);

	if (point.x * waterPlane.x + point.y * waterPlane.y + point.z * waterPlane.z - waterPlane.w >= 0.0f)
		return CTrue;
	else
		return CFalse;
}

//Important note: call this function after the gluLookAt function
void CWater::CreateReflectionTexture(int textureSize)
{
	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
		g_render.BindForWriting(m_fboID[ WATER_REFLECTION_ID ]);

    glViewport(0,0, textureSize, textureSize);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_render.PushMatrix();

	// Translate the world, then flip it upside down
	glTranslatef(0.0f, m_fWaterCPos[1]*2.0f, 0.0f);
	glScalef(1.0, -1.0, 1.0);

	// Since the world is updside down we need to change the culling to FRONT
	glCullFace(GL_FRONT);
	
	// Set our plane equation and turn clipping on
	CDouble plane[4] = {0.0, 1.0, 0.0, -m_fWaterCPos[1]};
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, plane);

	// Render the world upside down and clipped (only render the top flipped).
	// If we don't turn OFF caustics for the reflection texture we get horrible
	// artifacts in the water.  That is why we set bRenderCaustics to FALSE.
	if( g_menu.m_insertAndShowSky )
	{
		g_skyDome->RenderDome();
	}
	
	g_renderForWater = CTrue;
	g_multipleView->RenderTerrain(CFalse);
	g_renderForWater = CFalse;

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

	CFloat percentage;
	percentage = ((CFloat)GetResult() / (CFloat)m_numSamples) * 100.0f;
	//glEnable(GL_CLIP_DISTANCE0);

	if (GetDistanceFromCamera() < g_instancePrefabLODPercent.m_waterReflectionCameraDistance + GetRadius()
		|| percentage > g_instancePrefabLODPercent.m_waterReflectionPercents)
	{

		//3D Model data
		if (g_render.m_useWaterReflection && g_options.m_enableWaterReflection)
		{
			if (g_engineLights.size() == 0)
				g_multipleView->SetDefaultLight();

			g_renderForWater = CTrue;

			g_multipleView->m_checkBlending = CTrue;
			g_multipleView->m_renderBlending = CFalse;
			g_multipleView->m_pushTransparentGeometry = CTrue;

			g_multipleView->Render3DModelsForWater(this, CFalse, NULL);
			g_multipleView->Render3DAnimatedModelsForWater(this, CFalse);
			g_multipleView->Render3DModelsControlledByPhysXForWater(this, CFalse);

			g_multipleView->m_renderBlending = CTrue;
			g_multipleView->m_pushTransparentGeometry = CFalse;

			g_multipleView->CalculateAndSort3DTransparentModelDistances();
			g_multipleView->Render3DTransparentModelsForWater(this);

			g_multipleView->m_checkBlending = CFalse;
			g_multipleView->RemoveTransparentGeometries();

			g_renderForWater = CFalse;
		}

	}
	// Turn clipping off
	glDisable(GL_CLIP_PLANE0);

	// Restore back-face culling
	glCullFace(GL_BACK);
	g_render.PopMatrix();
	//glDisable( GL_CLIP_DISTANCE0 );

	glFlush();

	// Restore the previous matrix
	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
	{
		g_render.BindFBO(0);
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, m_waterTexture[WATER_REFLECTION_ID] );
		glFlush();
	    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, textureSize, textureSize);
		glBindTexture( GL_TEXTURE_2D, 0 );
	}
	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
	{
		glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_REFLECTION_ID]);
		glGenerateMipmapEXT(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

}

void CWater::CreateRefractionDepthTexture(int textureSize)
{
	// To create the refraction and depth textures we do the same thing
	// we did for the reflection texture, except we don't need to turn
	// the world upside down.  We want to find the depth of the water,
	// not the depth of the sky and above water terrain.
	
    glViewport(0,0, textureSize, textureSize);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

	// If the camera is above water, render the data below the water
	double plane[4] = {0.0, -1.0, 0.0, m_fWaterCPos[1]}; 
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, plane);
	//RenderWorld(true); I need to add some extra code to specify the objects that are under water
	glDisable(GL_CLIP_PLANE0);

	g_render.PopMatrix();
	glFlush();

    // Bind the current scene to our refraction texture
    glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_REFRACTION_ID]);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, textureSize, textureSize);

    // Bind the current scene to our depth texture
    glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_DEPTH_ID]);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, textureSize, textureSize, 0);

}

void CWater::RenderWater(CVec3f cameraPos, CFloat elapsedTime )
{
	if (g_multipleView->IsPlayGameMode())
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

		CFloat percentage;
		percentage = ((CFloat)GetResult() / (CFloat)m_numSamples) * 100.0f;

		if (GetDistanceFromCamera() > g_instancePrefabLODPercent.m_waterInvisibleCameraDistance + GetRadius()
			|| percentage < g_instancePrefabLODPercent.m_waterInvisiblePercent)
			return;
	}

	//if camera is above water?
	CBool renderAboveWater = CTrue;

	if (IsPointInWater(cameraPos))
	{
		if (!IsPointAboveWater(cameraPos))
		{
			renderAboveWater = CFalse;
		}
	}

	if (renderAboveWater && m_fWaterTransparency < 1.0f)
	{
		glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
		glEnable(GL_BLEND);
		glBlendColor(1.0f, 1.0f, 1.0f, m_fWaterTransparency);
	}

	glDisable( GL_CULL_FACE );
 	// Turn on the first texture unit and bind the REFLECTION texture
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_REFLECTION_ID]);

	// Turn on the second texture unit and bind the REFRACTION texture
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_REFRACTION_ID]);

	// Turn on the third texture unit and bind the NORMAL MAP texture
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, m_normalMapImg->GetId() );

	// Turn on the fourth texture unit and bind the DUDV MAP texture
	glActiveTexture(GL_TEXTURE3);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_dudvMapImg->GetId() );

	// Turn on the fifth texture unit and bind the DEPTH texture
	glActiveTexture(GL_TEXTURE4);
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, m_waterTexture[WATER_DEPTH_ID]);

	// Set the variable "reflection" to correspond to the first texture unit
	GLint uniform = glGetUniformLocationARB(g_render.m_waterProgram, "reflection"); 
	glUniform1iARB(uniform, 0); //second paramter is the texture unit 

	// Set the variable "refraction" to correspond to the second texture unit
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "refraction");
	glUniform1iARB(uniform, 1); 

	// Set the variable "normalMap" to correspond to the third texture unit
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "normalMap");
	glUniform1iARB(uniform, 2);

	// Set the variable "dudvMap" to correspond to the fourth texture unit
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "dudvMap"); 
	glUniform1iARB(uniform, 3);

	// Set the variable "depthMap" to correspond to the fifth texture unit
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "depthMap");
	glUniform1iARB(uniform, 4); 

	// Give the variable "waterColor" a blue color
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "waterColor");
	glUniform4fARB(uniform, m_fWaterColor[0], m_fWaterColor[1], m_fWaterColor[2], 1.0f);

	// We don't use lighting, but we do need to calculate
	// the diffuse and specular lighting on the water to increase realism.
	// position the light so it's near the light in the sky box texture.
	CVec3f lightPos(m_fWaterLPos[0], m_fWaterLPos[1], m_fWaterLPos[2]);

	// Give the variable "lightPos" our hard coded light position
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "lightPos");
	glUniform4fARB(uniform, lightPos.x, lightPos.y, lightPos.z, 1.0f); 

	// Give the variable "cameraPos" our camera position
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "cameraPos");
	glUniform4fARB(uniform, cameraPos.x, cameraPos.y, cameraPos.z, 1.0f); 
	
	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "renderAboveWater");
	glUniform1i(uniform, renderAboveWater);

	uniform = glGetUniformLocationARB(g_render.m_waterProgram, "enableSunReflection");
	glUniform1i(uniform, m_sunReflection);

	glUniform1f(glGetUniformLocation(g_render.m_waterProgram, "focalDistance"), g_multipleView->m_dof.m_focalDistance);
	glUniform1f(glGetUniformLocation(g_render.m_waterProgram, "focalRange"), g_multipleView->m_dof.m_focalRange);

	CBool useFog;
	if (g_polygonMode != ePOLYGON_FILL || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
		useFog = CFalse;
	else
		useFog = CTrue;

	if ((g_fogProperties.m_enable && useFog) || (g_waterFogProperties.m_enable && useFog))
		glUniform1i(glGetUniformLocation(g_render.m_waterProgram, "enableFog"), CTrue);
	else
		glUniform1i(glGetUniformLocation(g_render.m_waterProgram, "enableFog"), CFalse);


	// Use this variable for the normal map and make it slower
	// than the refraction map's speed.  We want the refraction
	// map to be jittery, but not the normal map's waviness.
	float move2 = m_move * kNormalMapScale;

	// Set the refraction map's UV coordinates to our global g_WaterUV
	float refrUV = m_fWaterUV;

	// Set our normal map's UV scale and shrink it by kNormalMapScale
	float normalUV = m_fWaterUV * kNormalMapScale;

	// Move the water by our global speed
	CBool isMoving = CTrue;
	if (g_currentVSceneProperties.m_pauseGame || g_multipleView->m_pauseAllWaterAnimations)
		isMoving = CFalse;

	if (isMoving)
		m_move += m_fWaterSpeed * elapsedTime;

	float sizey = (m_sidePoint[0] - m_sidePoint[1]).Size();
	float sizex = (m_sidePoint[2] - m_sidePoint[1]).Size();

	float texturePosX = 1.0f;
	float texturePosY = 1.0f;

	if(sizey < sizex)
		texturePosY = sizey / sizex;
	else if(sizex < sizey)
		texturePosX = sizex / sizey;

	glUseProgram( g_render.m_waterProgram );

	// Draw our water quad

	glBegin(GL_QUADS);

	// The back left vertex for the water
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, m_fWaterUV);				// Reflection texture				
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, (refrUV  * texturePosY) - m_move);			// Refraction texture
	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, (normalUV * texturePosY) + move2);		// Normal map texture
	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
	glVertex3f(m_sidePoint[0].x, m_sidePoint[0].y, m_sidePoint[0].z);

	// The front left vertex for the water
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);					// Reflection texture
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 0.0f - m_move);			// Refraction texture
	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 0.0f + move2);			// Normal map texture
	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
	glVertex3f(m_sidePoint[1].x, m_sidePoint[1].y, m_sidePoint[1].z);

	// The front right vertex for the water
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_fWaterUV, 0.0f);				// Reflection texture
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, refrUV * texturePosX, 0.0f - m_move);			// Refraction texture
	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, normalUV * texturePosX, 0.0f + move2);		// Normal map texture
	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
	glVertex3f(m_sidePoint[2].x, m_sidePoint[2].y, m_sidePoint[2].z);

	// The back right vertex for the water
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_fWaterUV, m_fWaterUV);		// Reflection texture
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB, refrUV * texturePosX, (refrUV * texturePosY) - m_move);		// Refraction texture
	glMultiTexCoord2fARB(GL_TEXTURE2_ARB, normalUV * texturePosX, (normalUV * texturePosY )+ move2);	// Normal map texture
	glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
	glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
	glVertex3f(m_sidePoint[3].x, m_sidePoint[3].y, m_sidePoint[3].z);

	glEnd();

	// Turn the fifth multi-texture pass off
	glActiveTexture(GL_TEXTURE4);		
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);

	// Turn the fourth multi-texture pass off
	glActiveTexture(GL_TEXTURE3);		
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);

	// Turn the third multi-texture pass off
	glActiveTexture(GL_TEXTURE2);
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);

	// Turn the second multi-texture pass off
	glActiveTexture(GL_TEXTURE1);
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);

	// Turn the first multi-texture pass off
	glActiveTexture(GL_TEXTURE0);	
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable(GL_TEXTURE_2D);

	glEnable( GL_CULL_FACE );
	glDisable(GL_TEXTURE_2D);

	if (renderAboveWater && m_fWaterTransparency < 1.0f)
	{
		glDisable(GL_BLEND);
	}
}

CVoid CWater::SetDuDvMap( CString fileName, CBool updateSharedImages ) { 
	Cpy( m_strDuDvMap, (char*)fileName.GetBuffer(fileName.GetLength()) );
	fileName.ReleaseBuffer();

	CImage* image = NULL; // GetWaterImage(GetAfterPath(m_strDuDvMap));
	if( image == NULL )
	{
		image = CNew (CImage);
		CTexture::LoadDDSTexture( image, m_strDuDvMap, NULL );
		image->SetName( GetAfterPath( m_strDuDvMap ) );
		g_waterImages.push_back( image );
	}
	else if( updateSharedImages )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Updating Image '", GetAfterPath(m_strDuDvMap), "' ..." );
		PrintInfo( temp, COLOR_YELLOW );

		image->Destroy();
		CTexture::LoadDDSTexture( image, m_strDuDvMap, NULL );
		image->SetName( GetAfterPath( m_strDuDvMap ) );
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(m_strDuDvMap), "' already exists." );
		PrintInfo( temp, COLOR_YELLOW );
	}
	m_dudvMapImg = image;
};
CVoid CWater::SetNormalMap( CString fileName, CBool updateSharedImages ) { 
	Cpy( m_strNormalMap, (char*)fileName.GetBuffer(fileName.GetLength()) );
	fileName.ReleaseBuffer();

	CImage* image = NULL; // GetWaterImage(GetAfterPath(m_strNormalMap));
	if( image == NULL )
	{
		image = CNew (CImage);
		CTexture::LoadDDSTexture( image, m_strNormalMap, NULL );
		image->SetName( GetAfterPath( m_strNormalMap ) );
		g_waterImages.push_back( image );
	}
	else if( updateSharedImages )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Updating Image '", GetAfterPath(m_strNormalMap), "' ..." );
		PrintInfo( temp, COLOR_YELLOW );

		image->Destroy();
		CTexture::LoadDDSTexture( image, m_strNormalMap, NULL );
		image->SetName( GetAfterPath( m_strNormalMap ) );
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(m_strNormalMap), "' already exists." );
		PrintInfo( temp, COLOR_YELLOW );
	}
	m_normalMapImg = image;

};

CVoid CWater::SetName( CString name  ) { 
	Cpy( m_strWaterName, (char*)name.GetBuffer(name.GetLength()) );
	name.ReleaseBuffer();
}

CVoid CWater::SetLastName(CChar* name)
{
	Cpy(m_lastName, name);
}

CVoid CWater::SetResult(GLint result)
{
	m_result = result;
}

GLint CWater::GetResult()
{
	return m_result;
}

CChar* CWater::GetName() { 
	return m_strWaterName;
}

CChar* CWater::GetLastName()
{
	return m_lastName;
}

CChar* CWater::GetDuDvMapName() { 
	return m_strDuDvMap;
}

CChar* CWater::GetNormalMapName() { 
	return m_strNormalMap;
}

CVoid CWater::SetNormalMapName(CChar* name) { 
	Cpy(m_strNormalMap, name );
}
CVoid CWater::SetDuDvMapName(CChar* name) { 
	Cpy(m_strDuDvMap, name);
}

CVoid CWater::RenderIcon(CBool selectionMode)
{
	if (selectionMode)
	{
		glPushName(m_nameIndex);
	}
	if (!selectionMode)
	{
		if (m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName)
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;
			if (g_currentTransformType == eCTranslate && g_transformObject)
			{
				m_fWaterCPos[0] = g_arrowPosition.x;
				m_fWaterCPos[1] = g_arrowPosition.y;
				m_fWaterCPos[2] = g_arrowPosition.z;
			}
			else if (g_currentTransformType == eCRotate && g_transformObject)
			{
				g_arrowPosition.x = m_fWaterCPos[0];
				g_arrowPosition.y = m_fWaterCPos[1];
				g_arrowPosition.z = m_fWaterCPos[2];
				if (g_transformDirection == XYTRANS || g_transformDirection == ZTRANS)
				{
					m_fWaterRotateY -= g_arrowRotate.x;
					g_arrowRotate.x = g_arrowRotate.y = g_arrowRotate.z = 0.0f;
				}
			}
			else if (g_currentTransformType == eCScale && g_transformObject)
			{
				g_arrowPosition.x = m_fWaterCPos[0];
				g_arrowPosition.y = m_fWaterCPos[1];
				g_arrowPosition.z = m_fWaterCPos[2];

				if (g_transformDirection == FREETRANS)
				{
					CFloat size = g_arrowScale.Size();
					if (size > 0.0f)
					{
						if (g_arrowScale.x != 0)
						{
							g_arrowScale.z = g_arrowScale.y = g_arrowScale.x;
						}
						else if (g_arrowScale.z != 0)
						{
							g_arrowScale.x = g_arrowScale.y = g_arrowScale.z;
						}
					}
				}

				m_fWaterScaleX += g_arrowScale.x;
				m_fWaterScaleZ += g_arrowScale.z;

				if (m_fWaterScaleX <= 0.01f)
					m_fWaterScaleX = 0.01f;
				if (m_fWaterScaleZ <= 0.01f)
					m_fWaterScaleZ = 0.01f;
				g_arrowScale.x = g_arrowScale.y = g_arrowScale.z = 0.0f;
			}
			else if(!g_transformObject)
			{
				g_arrowPosition.x = m_fWaterCPos[0];
				g_arrowPosition.y = m_fWaterCPos[1];
				g_arrowPosition.z = m_fWaterCPos[2];
			}
			g_glUtil.Billboarding(m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 1.0f, 1.0f, 1.0, 0.0, 0.0);
			SetSideVertexPositions();
			for (CUInt i = 0; i < m_instancePrefab.size(); i++)
			{
				m_instancePrefab[i]->UpdateBoundingBox();
				g_instancePrefab[i]->UpdateIsStaticOrAnimated();
			}
			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding(m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 1.0f, 1.0f);
	}
	else
		g_glUtil.Billboarding(m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 1.0f, 1.0f);
	if (selectionMode)
		glPopName();

}

CImage *CWater::GetWaterImage( const CChar * name )
{
	if (name == NULL) return NULL;
	for(CUInt i=0; i<g_waterImages.size(); i++)
	{
		if ( ICmp(GetAfterPath(g_waterImages[i]->GetName()), name ) )
			return g_waterImages[i];
	}
	return NULL;
}

CUInt CWater::GetNumPrefabInstanceNames()
{
	return m_instanceName.size();
}

CVoid CWater::AddPrefabInstanceName(CChar* name)
{
	m_instanceName.push_back(name);
}

const CChar* CWater::GetPrefabInstanceName(CUInt index)
{
	return m_instanceName[index].c_str();
}

CUInt CWater::GetNumPrefabInstances()
{
	return m_instancePrefab.size();
}

CVoid CWater::AddPrefabInstance(CInstancePrefab* instance)
{
	m_instancePrefab.push_back(instance);
}

CVoid CWater::RemovePrefabInstance(CUInt index)
{
	m_instancePrefab.erase(m_instancePrefab.begin() + index);
}

CInstancePrefab* CWater::GetPrefabInstance(CUInt index)
{
	return m_instancePrefab[index];
}

CChar* CWater::GetScriptStringVariable(CChar* variableName)
{
	CChar *s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CWater::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CWater::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CWater::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CWater::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CWater::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CWater::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CWater::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CWater::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CWater::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}
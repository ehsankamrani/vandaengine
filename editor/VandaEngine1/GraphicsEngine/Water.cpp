//Copyright (C) 2018 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "water.h"
#include "texture.h"
#include "render.h"
#include "scene.h"
#include "../VandaEngine1Dlg.h"


const float kNormalMapScale = 0.25f;



CWater::CWater()
{
	m_instancePrefab.clear();
	SetIndex();
}

CWater::~CWater()
{
	glDeleteTextures( MAX_WATER_TEXTURES, m_waterTexture );
	glDeleteFramebuffersEXT( MAX_WATER_TEXTURES, m_fboID );
	glDeleteRenderbuffersEXT(MAX_WATER_TEXTURES, m_rbID );
	m_VSceneList.clear(); //save functions
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

void CWater::SetSideVertexPositions()
{
	m_sidePoint[0].x = m_fWaterCPos[0] -m_fWaterScale/2.0f;
	m_sidePoint[0].y = m_fWaterCPos[1];
	m_sidePoint[0].z = m_fWaterCPos[2]-m_fWaterScale/2.0f;

	m_sidePoint[1].x = m_fWaterCPos[0]-m_fWaterScale/2.0f;
	m_sidePoint[1].y = m_fWaterCPos[1];
	m_sidePoint[1].z = m_fWaterCPos[2]+m_fWaterScale/2.0f;

	m_sidePoint[2].x = m_fWaterCPos[0]+m_fWaterScale/2.0f;
	m_sidePoint[2].y = m_fWaterCPos[1];
	m_sidePoint[2].z = m_fWaterCPos[2]+m_fWaterScale/2.0f;

	m_sidePoint[3].x = m_fWaterCPos[0]+m_fWaterScale/2.0f;
	m_sidePoint[3].y = m_fWaterCPos[1];
	m_sidePoint[3].z = m_fWaterCPos[2]-m_fWaterScale/2.0f;
}
//Important note: call this function after the gluLookAt function
void CWater::CreateReflectionTexture(int textureSize)
{
	if ( g_render.UsingFBOs() && g_options.m_enableFBO )
		g_render.BindFBO(m_fboID[ WATER_REFLECTION_ID ]);

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
	//glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, plane);

	// Render the world upside down and clipped (only render the top flipped).
	// If we don't turn OFF caustics for the reflection texture we get horrible
	// artifacts in the water.  That is why we set bRenderCaustics to FALSE.
	//Currently I just render the sky
	if( g_menu.m_insertAndShowSky )
	{
		g_skyDome->RenderDome();
	}
	CInt numLights = 0;

	//Engine lights
	for( CUInt i = 0; i < g_engineLights.size(); i++ )
	{
		if( numLights < 8 ) // 8 lights are supported
		{
			if( g_render.SetInstanceLight(g_engineLights[i],numLights) )
				++numLights;
		}
	}
	//COLLADA Lights. Not recommended
	for( CUInt i = 0 ; i < g_scene.size(); i++ )
	{
		g_render.SetScene( g_scene[i] );
		
		//set all the lights here
		for( CUInt i = 0; i < g_render.GetScene()->GetLightInstanceCount(); i++ )
		{
			if( numLights < 8 ) // 8 lights are supported
			{
				CInstanceLight *instanceLight = g_render.GetScene()->GetLightInstances(i);
				if( g_render.SetInstanceLight(instanceLight,numLights) )
					++numLights;
			}
		}
	}

	if( numLights == 0 )
	{
		glEnable(GL_LIGHT0);	 //just for per vertex lighting 	

		//This is the properties of the camera light
		GLfloat light_pos0[4] = {g_camera->m_perspectiveCameraPos.x,g_camera->m_perspectiveCameraPos.y, g_camera->m_perspectiveCameraPos.z, 0.0f };
		GLfloat light_ambient0[4] = { 0.1f, 0.1f, 0.1f, 0.0f };
		GLfloat light_diffuse0[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat light_specular0[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

		glLightfv( GL_LIGHT0, GL_POSITION, light_pos0  );
		glLightfv( GL_LIGHT0, GL_AMBIENT , light_ambient0 );
		glLightfv( GL_LIGHT0, GL_DIFFUSE , light_diffuse0 );
		glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular0 );
		glLightf ( GL_LIGHT0, GL_SPOT_CUTOFF,(GLfloat)180.0f );
		glLightf ( GL_LIGHT0, GL_CONSTANT_ATTENUATION , (GLfloat)0.5f );
		glLightf ( GL_LIGHT0, GL_LINEAR_ATTENUATION,	(GLfloat)0.0f );
		glLightf ( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, (GLfloat)0.0f );
		numLights++;
	}

	glEnable( GL_CLIP_DISTANCE0 );

	//3D Model data
	if(	g_render.m_useWaterReflection && g_options.m_enableWaterReflection)
	{
		if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
		{
			glUseProgram(g_shaderType);
			glUniform4fv(glGetUniformLocation(g_shaderType, "plane_equation"), 1, (GLfloat*)plane);
		}
		g_multipleView->Render3DModelsForWater(this, CTrue, NULL);
		g_multipleView->Render3DAnimatedModelsForWater(this, CTrue);
		g_multipleView->Render3DModelsControlledByPhysXForWater(this, CTrue);
	}

	// Turn clipping off
	glDisable(GL_CLIP_PLANE0);

	// Restore back-face culling
	glCullFace(GL_BACK);
	g_render.PopMatrix();
	glDisable( GL_CLIP_DISTANCE0 );

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
	if( g_fogBlurPass )
	{
		glDisable( GL_CULL_FACE );
		glBegin( GL_QUADS );
		glVertex3f(m_sidePoint[0].x, m_sidePoint[0].y, m_sidePoint[0].z);
		glVertex3f(m_sidePoint[1].x, m_sidePoint[1].y, m_sidePoint[1].z);
		glVertex3f(m_sidePoint[2].x, m_sidePoint[2].y, m_sidePoint[2].z);
		glVertex3f(m_sidePoint[3].x, m_sidePoint[3].y, m_sidePoint[3].z);
		glEnd();
		glEnable( GL_CULL_FACE );
	}
	else
	{
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
		glUniform4fARB(uniform, 0.1f, 0.2f, 0.3f, 1.0f); 

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
	
		// Create a static variable for the movement of the water
		static float move = 0.0f;

		// Use this variable for the normal map and make it slower
		// than the refraction map's speed.  We want the refraction
		// map to be jittery, but not the normal map's waviness.
		float move2 = move * kNormalMapScale;

		// Set the refraction map's UV coordinates to our global g_WaterUV
		float refrUV = m_fWaterUV;

		// Set our normal map's UV scale and shrink it by kNormalMapScale
		float normalUV = m_fWaterUV * kNormalMapScale;

		// Move the water by our global speed
		move += m_fWaterSpeed * elapsedTime;

		glUseProgram( g_render.m_waterProgram );

	   // Draw our huge water quad
		glBegin(GL_QUADS);

		// The back left vertex for the water
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, m_fWaterUV);				// Reflection texture				
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, refrUV - move);			// Refraction texture
		glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, normalUV + move2);		// Normal map texture
		glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
		glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
		glVertex3f(m_sidePoint[0].x, m_sidePoint[0].y, m_sidePoint[0].z);

		// The front left vertex for the water
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);					// Reflection texture
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 0.0f - move);			// Refraction texture
		glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0.0f, 0.0f + move2);			// Normal map texture
		glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
		glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
		glVertex3f(m_sidePoint[1].x, m_sidePoint[1].y, m_sidePoint[1].z);

		// The front right vertex for the water
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_fWaterUV, 0.0f);				// Reflection texture
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, refrUV, 0.0f - move);			// Refraction texture
		glMultiTexCoord2fARB(GL_TEXTURE2_ARB, normalUV, 0.0f + move2);		// Normal map texture
		glMultiTexCoord2fARB(GL_TEXTURE3_ARB, 0, 0);						// DUDV map texture
		glMultiTexCoord2fARB(GL_TEXTURE4_ARB, 0, 0);						// Depth texture
		glVertex3f(m_sidePoint[2].x, m_sidePoint[2].y, m_sidePoint[2].z);

		// The back right vertex for the water
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_fWaterUV, m_fWaterUV);		// Reflection texture
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, refrUV, refrUV - move);		// Refraction texture
		glMultiTexCoord2fARB(GL_TEXTURE2_ARB, normalUV, normalUV + move2);	// Normal map texture
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
	}

}

CVoid CWater::SetDuDvMap( CString fileName, CBool updateSharedImages ) { 
	Cpy( m_strDuDvMap, (char*)fileName.GetBuffer(fileName.GetLength()) );
	fileName.ReleaseBuffer();

	CImage* image = GetWaterImage( GetAfterPath( m_strDuDvMap ) );
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

	CImage* image = GetWaterImage( GetAfterPath( m_strNormalMap ) );
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

CChar* CWater::GetName() { 
	return m_strWaterName;
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

CVoid CWater::RenderIcon( CBool selectionMode )
{
	glUseProgram(0);

	if( selectionMode )
	{
		glPushName( m_nameIndex );
	}
	if( !selectionMode )
	{
		if( m_nameIndex == g_selectedName || m_nameIndex == g_lastEngineObjectSelectedName )
		{
			g_tempLastEngineObjectSelectedName = m_nameIndex;
			if( g_transformObject )
			{
				m_fWaterCPos[0] = g_arrowPosition.x; 
				m_fWaterCPos[1] = g_arrowPosition.y; 
				m_fWaterCPos[2] = g_arrowPosition.z; 
			}
			else
			{
				g_arrowPosition.x = m_fWaterCPos[0]; 
				g_arrowPosition.y = m_fWaterCPos[1]; 
				g_arrowPosition.z = m_fWaterCPos[2]; 
			}
			g_glUtil.Billboarding( m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 0.5f, 0.5f, 1.0, 0.0, 0.0 );
			SetSideVertexPositions();
			g_showArrow = CTrue;
		}
		else
			g_glUtil.Billboarding( m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 0.5f, 0.5f );
	}
	else
		g_glUtil.Billboarding( m_fWaterCPos[0], m_fWaterCPos[1], m_fWaterCPos[2], g_waterImg->GetId(), 0.5f, 0.5f );
	if( selectionMode )
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
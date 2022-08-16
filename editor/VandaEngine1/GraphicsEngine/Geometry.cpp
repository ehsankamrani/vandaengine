//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2022 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "geometry.h"
#include "scene.h"
#include "matrix.h"
#include "render.h"
#include "node.h"
//#include "cfxLoader.h"
//#include "cfxEffect.h"
//#include "cfxMaterial.h"
//#include "cfxPlatform.h"
#include "../common/utility.h"
//#include "perspectiveWindow.h"
//#include "../VandaEngine1Dlg.h"
#include "../sceneManagerEngine/lod.h"
CFloat ticker = 0.0f;

CInputType CPolyGroup::SetType( CChar * s )
{
	if ( CmpIn( s, "VERTEX" ) )
		return ePOINT_SOURCE;
	if ( CmpIn( s, "NORMAL" ) )
		return eNORMAL_SOURCE;
	if ( CmpIn( s, "TEXCOORD" )|| CmpIn( s, "UV" )) // until the schema is locked down got to suppor both
		return eTEXCOORD0_SOURCE;
	if ( CmpIn( s, "TEXTANGENT" ) ) // I'm not sure if TANGENT is also used? Shuld be checked
		return eTANGENT_SOURCE;
	if( CmpIn( s, "TEXBINORMAL" ) )
		return eBINORMAL_SOURCE;

	return eUNKNOWN;
}

CVoid CPolyGroup::EnableShader()
{
	if (g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader)
	{
		CBool useShadowShader = CFalse;

		if (g_materialChannels != eCHANNELS_ALL)//render layers in editor (View | Layers menu). this piece of code is not available in Win32 project
		{
			switch (g_materialChannels)
			{
			case eCHANNELS_DIFFUSE:
				g_shaderType = g_render.m_shaderColorMapLayerProgram;
				break;
			case eCHANNELS_NORMALMAP:
				g_shaderType = g_render.m_shaderNormalMapLayerProgram;
				break;
			case eCHANNELS_DIRTMAP:
				g_shaderType = g_render.m_shaderDirtMapLayerProgram;
				break;
			case eCHANNELS_GLOSSMAP:
				g_shaderType = g_render.m_shaderGlossMapLayerProgram;
				break;
			case eCHANNELS_ALPHAMAP:
				g_shaderType = g_render.m_shaderAlphaMapLayerProgram;
				break;
			case eCHANNELS_POSITION:
				g_shaderType = g_render.m_shaderPositionLayerProgram;
				break;
			case eCHANNELS_NORMAL:
				g_shaderType = g_render.m_shaderNormalLayerProgram;
				break;
			}
		}
		else if (g_renderForWater)
		{
			g_shaderType = g_render.m_waterShaderProgram; //currently I support low quality water reflection
		}
		else if (g_shadowProperties.m_enable && g_render.UsingShadowShader() && g_render.m_useDynamicShadowMap && !Cmp(g_shadowProperties.m_directionalLightName, "\n"))
		{
			useShadowShader = CTrue;

			if (m_hasNormalMap)
			{
				switch (g_shadowProperties.m_shadowType)
				{
				case eSHADOW_SINGLE_HL:
					g_shaderType = g_render.m_shad_single_hl_normal_prog;
					break;
				case eSHADOW_SINGLE:
					g_shaderType = g_render.m_shad_single_normal_prog;
					break;
				case eSHADOW_MULTI_LEAK:
					g_shaderType = g_render.m_shad_multi_normal_prog;
					break;
				case eSHADOW_MULTI_NOLEAK:
					g_shaderType = g_render.m_shad_multi_noleak_normal_prog;
					break;
				case eSHADOW_PCF:
					g_shaderType = g_render.m_shad_pcf_normal_prog;
					break;
				case eSHADOW_PCF_TRILIN:
					g_shaderType = g_render.m_shad_pcf_trilin_normal_prog;
					break;
				case eSHADOW_PCF_4TAP:
					g_shaderType = g_render.m_shad_pcf_4tap_normal_prog;
					break;
				case eSHADOW_PCF_8TAP:
					g_shaderType = g_render.m_shad_pcf_8tap_normal_prog;
					break;
				case eSHADOW_PCF_GAUSSIAN:
					g_shaderType = g_render.m_shad_pcf_gaussian_normal_prog;
					break;
				}
			}
			else
			{
				switch (g_shadowProperties.m_shadowType)
				{
				case eSHADOW_SINGLE_HL:
					g_shaderType = g_render.m_shad_single_hl_prog;
					break;
				case eSHADOW_SINGLE:
					g_shaderType = g_render.m_shad_single_prog;
					break;
				case eSHADOW_MULTI_LEAK:
					g_shaderType = g_render.m_shad_multi_prog;
					break;
				case eSHADOW_MULTI_NOLEAK:
					g_shaderType = g_render.m_shad_multi_noleak_prog;
					break;
				case eSHADOW_PCF:
					g_shaderType = g_render.m_shad_pcf_prog;
					break;
				case eSHADOW_PCF_TRILIN:
					g_shaderType = g_render.m_shad_pcf_trilin_prog;
					break;
				case eSHADOW_PCF_4TAP:
					g_shaderType = g_render.m_shad_pcf_4tap_prog;
					break;
				case eSHADOW_PCF_8TAP:
					g_shaderType = g_render.m_shad_pcf_8tap_prog;
					break;
				case eSHADOW_PCF_GAUSSIAN:
					g_shaderType = g_render.m_shad_pcf_gaussian_prog;
					break;
				}
			}
		}
		else if (m_hasNormalMap)
			g_shaderType = g_render.m_shader_normalProgram;
		else
			g_shaderType = g_render.m_shaderProgram;

		glUseProgram(g_shaderType);

		if (useShadowShader)
		{
			glUniform1i(glGetUniformLocation(g_shaderType, "stex"), 7); // depth-maps
			glUniform4fv(glGetUniformLocation(g_shaderType, "far_d"), 1, g_multipleView->far_bound);
			glUniform1f(glGetUniformLocation(g_shaderType, "shadow_intensity"), g_shadowProperties.m_intensity);
		}

		CInt num_point_lights = 0;
		CInt num_spot_lights = 0;
		CInt num_dir_lights = 0;
		//I support up to NR_DIR_LIGHTS directional light, up to NR_POINT_LIGHTS point lights, and up to NR_SPOT_LIGHTS spot lights for each object
		if (g_engineLights.size() == 0 || g_editorMode == eMODE_PREFAB)
		{
			glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), 1000000);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), 0);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), 1);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), 0);

		}
		else
		{
			for (CUInt i = 0; i < g_currentInstancePrefab->GetTotalLights(); i++)
			{
				CInstanceLight *instanceLight = g_currentInstancePrefab->GetActiveLight(i);
				g_currentInstanceLight = instanceLight;

				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_DIRECTIONAL)
				{
					if (Cmp(g_shadowProperties.m_directionalLightName, instanceLight->m_abstractLight->GetName()))
						glUniform1i(glGetUniformLocation(g_shaderType, "defaultDirLightIndex"), i);

					num_dir_lights++;
				}
				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_POINT)
				{
					num_point_lights++;
					if (num_point_lights == 1)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[0]"), g_currentInstanceLight->GetRadius());
					else if (num_point_lights == 2)
						glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[1]"), g_currentInstanceLight->GetRadius());
					//else if (num_point_lights == 3)
					//	glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[2]"), g_currentInstanceLight->GetRadius());
					//else if (num_point_lights == 4)
					//	glUniform1f(glGetUniformLocation(g_shaderType, "point_light_radius[3]"), g_currentInstanceLight->GetRadius());
				}

				if (instanceLight->m_abstractLight->GetType() == eLIGHTTYPE_SPOT)
				{
					num_spot_lights++;
					if (num_spot_lights == 1)
						glUniform1f(glGetUniformLocation(g_shaderType, "spot_light_radius[0]"), g_currentInstanceLight->GetRadius());
				}

			}
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_dir_lights"), num_dir_lights);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_point_lights"), num_point_lights);
			glUniform1i(glGetUniformLocation(g_shaderType, "nr_spot_lights"), num_spot_lights);
		}

		glUniform1f(glGetUniformLocation(g_shaderType, "focalDistance"), g_multipleView->m_dof.m_focalDistance);
		glUniform1f(glGetUniformLocation(g_shaderType, "focalRange"), g_multipleView->m_dof.m_focalRange);

		CBool useFog;
		if (g_polygonMode != ePOLYGON_FILL || (g_dofProperties.m_enable && g_dofProperties.m_debug) || (g_shadowProperties.m_shadowType == eSHADOW_SINGLE_HL && g_shadowProperties.m_enable && g_render.UsingShadowShader()))
			useFog = CFalse;
		else
			useFog = CTrue;

		if ((g_fogProperties.m_enable && useFog) || (g_waterFogProperties.m_enable && useFog))
			glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CTrue);
		else
			glUniform1i(glGetUniformLocation(g_shaderType, "enableFog"), CFalse);

	}
	else
	{
		if (!g_multipleView->m_renderArrow)
			glUseProgram(0);
	}

}

CBool CPolyGroup::SetupGlossTexture(CNode *parentNode, CInstance * instance )
{
	CBool found = CFalse;
	// resolve instance material
	for ( CUInt  j=0; j < instance->m_materialInstances.size(); j++ )
	{
		CInstanceMaterial* thisInstanceMaterial = instance->m_materialInstances[j];
		if (thisInstanceMaterial)
		{
			std::string symbol = thisInstanceMaterial->m_symbol;
			std::string target = thisInstanceMaterial->m_target;
			if (symbol == std::string(m_materialName)) {
				if (thisInstanceMaterial->m_targetMaterial)	// common material
				{
					CEffect *effect = thisInstanceMaterial->m_targetMaterial->GetEffect();
					for (CUInt i=0; i<effect->m_textures.size(); i++)
					{
						CChar temp[MAX_NAME_SIZE];
						Cpy( temp, effect->m_textures[i]->GetFileName() );
						CChar* nameOnly;
						if( g_useOriginalPathOfDAETextures )
						{
							nameOnly = CNewData(CChar, MAX_NAME_SIZE);
							Cpy(nameOnly, temp );
						}
						else
						{
							nameOnly = GetAfterPath( temp );
						}
						GetWithoutDot( nameOnly );

						CChar finalName[MAX_NAME_SIZE];
						if( !Cmp( g_extraTexturesNamingConventions.m_diffuseNameExcept, "" ) )
						{
							std::string name = nameOnly;
							std::string removeString = g_extraTexturesNamingConventions.m_diffuseNameExcept;
							if( name.compare( name.length() - removeString.length(), removeString.length(), removeString ) == 0 )
								name.erase( name.length() - removeString.length(), removeString.length() );
							Cpy( finalName ,name.c_str() );
						}
						else
						{
							Cpy( finalName, nameOnly );
						}

						Append( finalName, g_extraTexturesNamingConventions.m_glossMapName);
						if( SetGlossMap( finalName, CTrue ) )
							found = CTrue;

						if( g_useOriginalPathOfDAETextures )
						{
							CDeleteData( nameOnly );
						}

						if ( found )
							break;
					}
					if( found )
						return CTrue;
				}
			}
		}
	}
	return CFalse;
}

CBool CPolyGroup::SetupDirtTexture(CNode *parentNode, CInstance * instance )
{
	CBool found = CFalse;
	// resolve instance material
	for ( CUInt  j=0; j < instance->m_materialInstances.size(); j++ )
	{
		CInstanceMaterial* thisInstanceMaterial = instance->m_materialInstances[j];
		if (thisInstanceMaterial)
		{
			std::string symbol = thisInstanceMaterial->m_symbol;
			std::string target = thisInstanceMaterial->m_target;
			if (symbol == std::string(m_materialName)) {
				if (thisInstanceMaterial->m_targetMaterial)	// common material
				{
					CEffect *effect = thisInstanceMaterial->m_targetMaterial->GetEffect();
					for (CUInt i=0; i<effect->m_textures.size(); i++)
					{
						CChar temp[MAX_NAME_SIZE];
						Cpy( temp, effect->m_textures[i]->GetFileName() );
						CChar* nameOnly;
						if( g_useOriginalPathOfDAETextures )
						{
							nameOnly = CNewData(CChar, MAX_NAME_SIZE);
							Cpy(nameOnly, temp );
						}
						else
						{
							nameOnly = GetAfterPath( temp );
						}
						GetWithoutDot( nameOnly );

						CChar finalName[MAX_NAME_SIZE];
						if( !Cmp( g_extraTexturesNamingConventions.m_diffuseNameExcept, "" ) )
						{
							std::string name = nameOnly;
							std::string removeString = g_extraTexturesNamingConventions.m_diffuseNameExcept;
							if( name.compare( name.length() - removeString.length(), removeString.length(), removeString ) == 0 )
								name.erase( name.length() - removeString.length(), removeString.length() );
							Cpy( finalName ,name.c_str() );
						}
						else
						{
							Cpy( finalName, nameOnly );
						}

						Append( finalName, g_extraTexturesNamingConventions.m_dirtMapName);
						if( SetDirtMap( finalName, CTrue ) )
							found = CTrue;

						if( g_useOriginalPathOfDAETextures )
						{
							CDeleteData( nameOnly );
						}

						if (found)
							break;
					}
					if( found )
						return CTrue;
				}
			}
		}
	}
	return CFalse;
}

CBool CPolyGroup::SetupNormalTexture(CNode *parentNode, CInstance * instance )
{
	CBool found = CFalse;
	// resolve instance material
	for ( CUInt  j=0; j < instance->m_materialInstances.size(); j++ )
	{
		CInstanceMaterial* thisInstanceMaterial = instance->m_materialInstances[j];
		if (thisInstanceMaterial)
		{
			std::string symbol = thisInstanceMaterial->m_symbol;
			std::string target = thisInstanceMaterial->m_target;
			if (symbol == std::string(m_materialName)) {
				if (thisInstanceMaterial->m_targetMaterial)	// common material
				{
					CEffect *effect = thisInstanceMaterial->m_targetMaterial->GetEffect();
					for (CUInt i=0; i<effect->m_textures.size(); i++)
					{
						CChar temp[MAX_NAME_SIZE];
						Cpy( temp, effect->m_textures[i]->GetFileName() );
						CChar* nameOnly;
						if( g_useOriginalPathOfDAETextures )
						{
							nameOnly = CNewData(CChar, MAX_NAME_SIZE);
							Cpy(nameOnly, temp );
						}
						else
						{
							nameOnly = GetAfterPath( temp );
						}
						GetWithoutDot( nameOnly );

						CChar finalName[MAX_NAME_SIZE];
						if( !Cmp( g_extraTexturesNamingConventions.m_diffuseNameExcept, "" ) )
						{
							std::string name = nameOnly;
							std::string removeString = g_extraTexturesNamingConventions.m_diffuseNameExcept;
							if( name.compare( name.length() - removeString.length(), removeString.length(), removeString ) == 0 )
								name.erase( name.length() - removeString.length(), removeString.length() );
							Cpy( finalName ,name.c_str() );
						}
						else
						{
							Cpy( finalName, nameOnly );
						}

						Append( finalName, g_extraTexturesNamingConventions.m_normalMapName);
						if( SetNormalMap( finalName, -.03f, .06f, CTrue ) ) //test
							found = CTrue;
						if( g_useOriginalPathOfDAETextures )
						{
							CDeleteData( nameOnly );
						}

						if (found)
							break;
					}
					if( found )
						return CTrue;
				}
			}
		}
	}
	return CFalse;
}

CBool CPolyGroup::SetupDiffuseTexture(CNode *parentNode, CInstance * instance )
{
	CBool found = CFalse;
	// resolve instance material
	for ( CUInt  j=0; j < instance->m_materialInstances.size(); j++ )
	{
		CInstanceMaterial* thisInstanceMaterial = instance->m_materialInstances[j];
		if (thisInstanceMaterial)
		{
			std::string symbol = thisInstanceMaterial->m_symbol;
			std::string target = thisInstanceMaterial->m_target;
			if (symbol == std::string(m_materialName)) {
				if (thisInstanceMaterial->m_targetMaterial)	// common material
				{
					CEffect *effect = thisInstanceMaterial->m_targetMaterial->GetEffect();
					for (CUInt i=0; i<effect->m_textures.size(); i++)
					{
						CChar temp[MAX_NAME_SIZE];
						Cpy( temp, effect->m_textures[i]->GetFileName() );
						CChar* nameOnly;
						if( g_useOriginalPathOfDAETextures )
						{
							nameOnly = CNewData(CChar, MAX_NAME_SIZE);
							Cpy(nameOnly, temp );
						}
						else
						{
							nameOnly = GetAfterPath( temp );
						}
						GetWithoutDot( nameOnly );
						if( SetDiffuse( nameOnly, CTrue ) )
							found = CTrue;

						if( g_useOriginalPathOfDAETextures )
						{
							CDeleteData( nameOnly );
						}

						if (found)
							break;
					}
					if( found )
						return CTrue;
				}
			}
		}
	}
	return CFalse;
}

CVoid CPolyGroup::SaveMaterialValues(CMaterial * mat)
{
	CEffect *effect = mat->GetEffect();
	assert(effect);  // In COLLADA 1.4 a material is required to have a reference to an effect

	CColor4f ambient = effect->GetAmbient();
	CColor4f diffuse = effect->GetDiffuse();
	CColor4f specular = effect->GetSpecular();
	CColor4f emission = effect->GetEmission();

	CFloat shininess = effect->GetShininess();
	if (shininess < 1.0) shininess = (CFloat)(shininess * 100.0); // if the scale is 0.0 to 1.0, make it 0.0 to 100.0

	m_fAmbientColor[0] = ambient.r; m_fAmbientColor[1] = ambient.g; m_fAmbientColor[2] = ambient.b; m_fAmbientColor[3] = ambient.a;
	m_fDiffuseColor[0] = diffuse.r; m_fDiffuseColor[1] = diffuse.g; m_fDiffuseColor[2] = diffuse.b; m_fDiffuseColor[3] = effect->m_transparency;
	m_fSpecularColor[0] = specular.r; m_fSpecularColor[1] = specular.g; m_fSpecularColor[2] = specular.b; m_fSpecularColor[3] = specular.a;
	m_fEmissionColor[0] = emission.r; m_fEmissionColor[1] = emission.g; m_fEmissionColor[2] = emission.b; m_fEmissionColor[3] = emission.a;

	m_fTransparency = effect->m_transparency;
	m_fShininess = shininess;
}

CVoid CPolyGroup::SetupMaterialForDrawFromGameEngine(CGeometryColor color)
{
	if (g_editorMode == eMODE_VSCENE && g_currentInstancePrefab && g_currentInstancePrefab->IsMaterialEnabled())
	{
		g_render.SetMaterialFromGameEngine(g_currentInstancePrefab->GetAmbient(), g_currentInstancePrefab->GetDiffuse(), g_currentInstancePrefab->GetSpecular(), g_currentInstancePrefab->GetEmission(), g_currentInstancePrefab->GetShininess(), g_currentInstancePrefab->GetTransparency(), color);
	}
	else
	{
		g_render.SetMaterialFromGameEngine(m_fAmbientColor, m_fDiffuseColor, m_fSpecularColor, m_fEmissionColor, m_fShininess, m_fTransparency, color);
	}
}

/*cfxMaterial* */ CVoid CPolyGroup::SetupMaterialForDrawFromCOLLADA(CNode *parentNode, CInstance * instance, CGeometryColor color, CBool hasDiffuse )
{
	// This method contains code that is common to both Draw and DrawSkinned.  Was going to combine
	// Draw and DrawSkinned into one function, but decided to retain the two seperate functions so the
	// use of parameters would be properly checked.
	//cfxMaterial* currentMaterial = 0;

	// resolve instance material
	for ( CUInt  j=0; j < instance->m_materialInstances.size(); j++ )
	{
		CInstanceMaterial* thisInstanceMaterial = instance->m_materialInstances[j];
		if (thisInstanceMaterial)
		{
			std::string symbol = thisInstanceMaterial->m_symbol;
			std::string target = thisInstanceMaterial->m_target;
			if (symbol == std::string(m_materialName)) {
				if (thisInstanceMaterial->m_targetMaterial)	// common material
				{
					g_render.SetMaterialFromCOLLADA(thisInstanceMaterial->m_targetMaterial, color, hasDiffuse ); 
					SaveMaterialValues(thisInstanceMaterial->m_targetMaterial);
					return /*NULL*/;
				}//else if (thisInstanceMaterial->m_targetcfxMaterial) // fx material
				//{
					//TODO: we might have to reset FXMaterial back to 0 after we draw this.
					//currentMaterial = thisInstanceMaterial->m_targetcfxMaterial;
				//}
			}
		}
	}

//	if(currentMaterial)
//	{
//		// Pushes the setparam values into cgFX for this material
//		currentMaterial->setParameterValues();
//
//		// Get the effect pointer
//		cfxEffect* currentEffect = currentMaterial->getEffect();
//
//		// See if there are any common semantic Parameters we need to set
//		CGparameter worldviewprojectionParam = currentEffect->getParameterBySemantic("WORLDVIEWPROJECTION");
//		CGparameter viewinverseParam = currentEffect->getParameterBySemantic("VIEWINVERSE");
//		CGparameter worldParam = currentEffect->getParameterBySemantic("WORLD");
//		CGparameter worldinversetransposeParam = currentEffect->getParameterBySemantic("WORLDINVERSETRANSPOSE");
//		CGparameter lightPositionParam = currentEffect->getParameterBySemantic("LIGHTPOSITION");
//		CGparameter timeParam = currentEffect->getParameterBySemantic("TIME");
//
//		// WORLDVIEWPROJECTION is the world+view+projection matrix of this object which we get from GL
//		if (worldviewprojectionParam)
//		{
//			cgGLSetStateMatrixParameter(worldviewprojectionParam, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
//		}
//
//		// VIEWINVERSE is the inverse of the view matrix which is the same as the camera's LocalToWorldMatrix
//		if(viewinverseParam)
//		{
//			CInstanceCamera *inst = g_render.GetActiveInstanceCamera();
//			cgGLSetMatrixParameterfc( viewinverseParam, (const CFloat *)(inst->m_parent->GetLocalToWorldMatrix())); 
//		}
//
//		// WORLD is the localtoworld matrix for this object which we get from the scene graph
//		if (worldParam)
//		{
//			cgGLSetMatrixParameterfc( worldParam, (const CFloat *)(parentNode->GetLocalToWorldMatrix()));
//		}
//
//		// WORLDINVERSETRANSPOSE is inversetransposelocaltoworld matrix for this object from the scene graph
//		if (worldinversetransposeParam)
//		{
//			cgGLSetMatrixParameterfc( worldinversetransposeParam, (const CFloat *)(parentNode->GetInverseTransposeLocalToWorldMatrix()));
//		}
//
//		// LIGHTPOSITION gets the position of the primary (nearist) light
//		if (lightPositionParam)
//		{
//			assert(g_render.GetScene()->GetLightInstanceCount());  // There should always be one
//#if 0
//			//EXPERIMENTAL this gets the closest light instance, need some way to get the parent node of this polygroup
//			//EXPERIMENTAL may want to check to make sure NearistInstanceLight isn't null
//			CInstanceLight *instanceLight = ??? parentnode->NearistInstanceLight;
//#else
//			CInstanceLight *instanceLight =g_render.GetScene()->GetLightInstances(0);
//#endif
//			// Get the light position from the light instance's parent node's LocalToWorldMatrix
//			// REFACTOR IN PROGRESS we should have an accessor for getting the position
//			CFloat *lightMatrix = (CFloat *)instanceLight->m_parent->GetLocalToWorldMatrix();
//
//			CGtype lighttype = cgGetParameterType(lightPositionParam);
//			if (lighttype == CG_FLOAT3)
//			{
//				cgSetParameter3f(lightPositionParam, lightMatrix[12], lightMatrix[13], lightMatrix[14]);
//			}
//			else if (lighttype == CG_FLOAT4)
//			{
//				cgSetParameter4f(lightPositionParam, lightMatrix[12], lightMatrix[13], lightMatrix[14], 0);
//			}
//		}
//
//		// TIME gets a tickcount for driving animated shaders
//		if (timeParam)
//		{
//			cgSetParameter1f(timeParam, ticker);
//		}
//
//		// Setup the state for the cfxMaterial
//		currentMaterial->setEffectPassState(0,0);
//		return currentMaterial;
//	}
	return /*NULL*/;
}

CVoid CPolyGroup::Draw(CNode *parentNode, CInstance * instance, CGeometryColor color, CBool hasDiffuse )
{
	CFloat transparency = m_fTransparency; //default value is the transparency of polygroup

	if (g_editorMode == eMODE_VSCENE && g_currentInstancePrefab && g_currentInstancePrefab->IsMaterialEnabled())
	{
		transparency = g_currentInstancePrefab->GetTransparency();
	}

	if (g_multipleView->m_checkBlending)
	{
		if (transparency < 1.0f && !g_multipleView->m_renderBlending)
			return;
		else if (transparency >= 1.0f && g_multipleView->m_renderBlending)
			return;
	}

	if (m_setMatFromCollada)
	{
		/*cfxMaterial* currentMaterial = */SetupMaterialForDrawFromCOLLADA(parentNode, instance, color, hasDiffuse);
		m_setMatFromCollada = CFalse;
	}
	else
	{
		SetupMaterialForDrawFromGameEngine(color);
	}

	if (transparency < 1.0f)
	{
		glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
		glEnable(GL_BLEND);
		glBlendColor(1.0f, 1.0f, 1.0f, transparency);
	}

	Render();

	if (transparency < 1.0f)
	{
		glDisable(GL_BLEND);
	}

	if (color == eCOLOR_WHITE)
	{
		GLint currProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
		glUseProgram(0);
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (CUInt i = 0; i < 8; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glDisable(GL_TEXTURE_2D);
		}
		glDisable(GL_LIGHTING);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glLineWidth(0.5f);
		Render();
		glPopAttrib();
		glUseProgram(currProgram);
	}
	else if (color == eCOLOR_GREEN)
	{
		GLint currProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
		glUseProgram(0);
		glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_CURRENT_BIT | GL_TEXTURE_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_LIGHTING);
		for (CUInt i = 0; i < 8; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glDisable(GL_TEXTURE_2D);
		}

		glColor4f(0.0, 0.7, 0.2, 0.0);
		glLineWidth(0.5f);
		Render();
		glPopAttrib();
		glUseProgram(currProgram);
	}

	// Restore the old material state
	//if(currentMaterial)
	//{
	//	currentMaterial->resetEffectPassState(0,0);
	//}
}

CImage* CPolyGroup::GetImage( const CChar * name )
{
	if ( name == NULL )
		return NULL;

	for( CUInt i = 0; i < g_images.size(); i++ )
	{
		if (ICmp(GetAfterPath(g_images[i]->GetFileName()), name))
			return g_images[i];
	}
	return NULL;
}

CVoid CGeometry::CalculateLODInfo( CPhysXAlgorithm algorithm)
{
	List<int> permutation;
	m_lod = CNew( CLOD);
	m_lod->SetAlgorithm( algorithm );
	m_lod->ProgressiveMesh(this, permutation);
	m_lod->PermuteVertices(this, permutation);
	CDelete( m_lod );
}

CVoid CGeometry::DrawAABBWithLines()
{
	CVector color( 1.0, 1.0, 1.0 );
	g_glUtil.DrawCWBoxWithLines( m_minAABB, m_maxAABB, color );
}
CVoid CGeometry::DrawAABBWithQuads()
{
	g_glUtil.DrawCWBoxWithQuads( m_minAABB, m_maxAABB );
}

CImage* CGeometry::GetImage( const CChar * name )
{
	if ( name == NULL )
		return NULL;

	for( CUInt i = 0; i < g_images.size(); i++ )
	{
		if (ICmp(GetAfterPath(g_images[i]->GetFileName()), name))
			return g_images[i];
	}
	return NULL;
}

CVoid CPolyGroup::TrimOriginalPath(CChar* path ) //save functions
{
	GetWithoutDot(path);
	Append( path, ".dds" );
	//replace %20 with space using std::string
	std::string s(path);
	size_t i = 0;
	for (;;) {
		i = s.find("%20", i);
		if (i == string::npos) {
			break;
		}
		s.replace(i, 3, " ");
	}
	s.begin();
	i = 0;
	for (;;) {
		i = s.find("file:/", i);
		if (i == string::npos) {
			break;
		}
		s.replace(i, 6, "");
	}

	strcpy(path, s.c_str());
}

CBool CPolyGroup::SetDiffuse( CString path, CBool test )
{
	if( path.IsEmpty() )
		return CFalse;
	Cpy( m_strOriginalDiffusePath, (char*)path.GetBuffer(path.GetLength()) ); //save functions
	TrimOriginalPath( m_strOriginalDiffusePath );

	path.ReleaseBuffer();

	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_diffuseImg );
	CChar* m_strNameAfterPath = GetAfterPath(m_strTemp);
	GetWithoutDot( m_strNameAfterPath );
	CChar m_strTemp2[MAX_NAME_SIZE];
	sprintf( m_strTemp2, "%s%s", m_strNameAfterPath, ".dds" );
	CImage* tempImg = GetImage( m_strTemp2 );
	CBool foundTarget = CFalse;
	if( g_updateTextureViaEditor )
	{
		if( tempImg )
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
			PrintInfo( temp, COLOR_YELLOW );
			tempImg->Destroy();
			foundTarget = CTrue;
		}
		g_currentScene->IsInTextureList( m_strTemp2 );
	}
	else if( g_useOriginalPathOfDAETextures ) //save functions
	{
		if( !g_currentScene->IsInTextureList( m_strTemp2 ))
			if( tempImg )
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
				PrintInfo( temp, COLOR_YELLOW );
				tempImg->Destroy();
				foundTarget = CTrue;
			}
	}
	else
	{
		g_currentScene->IsInTextureList( m_strTemp2 );
	}

	if( tempImg == NULL || foundTarget)
	{
		if(!foundTarget)
			tempImg = CNew( CImage );
		CChar m_strTemp3[MAX_NAME_SIZE];
		if( g_useOriginalPathOfDAETextures || g_updateTextureViaEditor)
		{
			Cpy( m_strTemp3, m_strTemp );
		}
		else
		{
			//save functions. it should be copied in WIN32 Project as well
			if (g_editorMode == eMODE_VSCENE && !g_importPrefab)
			{
				CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(g_currentVSceneNameWithoutDot, g_currentVSceneName);
				GetWithoutDot(g_currentVSceneNameWithoutDot);

				sprintf(m_strTemp3, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp2);
			}
			else //prefab
			{
				sprintf(m_strTemp3, "%s%s%s%s", g_currentPrefabPackagePath, g_currentPrefabName, "/Textures/", m_strTemp2);
			}
		}
		CBool reportError = CFalse;
		if( foundTarget )
			reportError = CTrue;
		else
			reportError = !test;
		if( !CTexture::LoadDDSTexture( tempImg, m_strTemp3, "LoadDiffuseOfDAE", reportError ) )
		{
			if( test )
			{
				m_hasDiffuse = CFalse;
				Cpy(m_strDiffuse, "\n");
				m_updateDiffuse = CFalse;
			}
			else
			{
				m_hasDiffuse = CTrue;
				m_loadedDiffuse = CFalse;
				Cpy( m_strDiffuse, m_strTemp2 );
				GetWithoutDot( m_strDiffuse );
			}
			m_diffuseImg = NULL;
			if( !foundTarget )
				CDelete( tempImg );
			return CFalse;
		}
	
		m_diffuseImg = tempImg;
		Cpy( m_strDiffuse, m_strTemp2 );
		GetWithoutDot( m_strDiffuse );
		if( g_useOriginalPathOfDAETextures || g_updateTextureViaEditor )
			m_diffuseImg->SetFileName( m_strOriginalDiffusePath );
		else
			m_diffuseImg->SetFileName( m_strTemp2 );
		m_hasDiffuse = CTrue;
		m_loadedDiffuse = CTrue;
		if(!foundTarget)
		{
			m_images.push_back( m_diffuseImg );
			g_images.push_back( m_diffuseImg );

			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Image '", GetAfterPath(m_diffuseImg->GetFileName()), "' loaded successfully.");
			PrintInfo(temp, COLOR_GREEN);

		}
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(tempImg->GetFileName()), "' already exists." );
		PrintInfo( temp, COLOR_YELLOW );
		numWarnings += 1;

		m_diffuseImg = tempImg;
		m_hasDiffuse = CTrue;
		m_loadedDiffuse = CTrue;
		Cpy( m_strDiffuse, m_strTemp2 );
		GetWithoutDot( m_strDiffuse );

	}
	m_updateDiffuse = CTrue;
	return CTrue;
}

CBool CPolyGroup::SetGlossMap( CString path, CBool test )
{
	if( path.IsEmpty() )
		return CFalse;
	Cpy( m_strOriginalGlossMapPath, (char*)path.GetBuffer(path.GetLength()) ); //save functions
	TrimOriginalPath( m_strOriginalGlossMapPath);
	path.ReleaseBuffer();

	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_glossImg );
	CChar* m_strNameAfterPath = GetAfterPath(m_strTemp);
	GetWithoutDot( m_strNameAfterPath );
	CChar m_strTemp2[MAX_NAME_SIZE];
	sprintf( m_strTemp2, "%s%s", m_strNameAfterPath, ".dds" );
	CImage* tempImg = GetImage( m_strTemp2 );
	CBool foundTarget = CFalse;
	if( g_updateTextureViaEditor )
	{
		if( tempImg )
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
			PrintInfo( temp, COLOR_YELLOW );
			tempImg->Destroy();
			foundTarget = CTrue;
		}
		g_currentScene->IsInTextureList( m_strTemp2 );
	}
	else if( g_useOriginalPathOfDAETextures ) //save functions
	{
		if( !g_currentScene->IsInTextureList( m_strTemp2 ))
			if( tempImg )
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
				PrintInfo( temp, COLOR_YELLOW );
				tempImg->Destroy();
				foundTarget = CTrue;
			}
	}
	else
	{
		g_currentScene->IsInTextureList( m_strTemp2 );
	}

	if( tempImg == NULL || foundTarget )
	{
		if(!foundTarget)
			tempImg = CNew( CImage );
		CChar m_strTemp3[MAX_NAME_SIZE];
		if( g_useOriginalPathOfDAETextures || g_updateTextureViaEditor)
		{
			Cpy( m_strTemp3, m_strTemp );
		}
		else
		{
			//save functions. it should be copies in WIN32 Project as well
			if (g_editorMode == eMODE_VSCENE && !g_importPrefab)
			{
				CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(g_currentVSceneNameWithoutDot, g_currentVSceneName);
				GetWithoutDot(g_currentVSceneNameWithoutDot);

				sprintf(m_strTemp3, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp2);
			}
			else //prefab
			{
				sprintf(m_strTemp3, "%s%s%s%s", g_currentPrefabPackagePath, g_currentPrefabName, "/Textures/", m_strTemp2);
			}
		}
		CBool reportError = CFalse;
		if( foundTarget )
			reportError = CTrue;
		else
			reportError = !test;

		if( !CTexture::LoadDDSTexture( tempImg, m_strTemp3, "LoadGlossMapOfDAE", reportError ) )
		{
			if( test )
			{
				m_hasGlossMap = CFalse;
				Cpy(m_strGlossMap, "\n");
				m_updateGlossMap = CFalse;
			}
			else
			{
				m_hasGlossMap = CTrue;
				m_loadedGlossMap = CFalse;
				Cpy( m_strGlossMap, m_strTemp2 );
				GetWithoutDot( m_strGlossMap );
			}
			m_glossMapImg = NULL;
			if( !foundTarget )
				CDelete( tempImg );
			return CFalse;
		}
	
		m_glossMapImg = tempImg;
		Cpy( m_strGlossMap, m_strTemp2 );
		GetWithoutDot( m_strGlossMap );
		m_glossMapImg->SetFileName( m_strTemp2 );
		m_hasGlossMap = CTrue;
		m_loadedGlossMap = CTrue;
		if(!foundTarget)
		{
			m_images.push_back( m_glossMapImg );
			g_images.push_back( m_glossMapImg );
			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Image '", GetAfterPath(m_glossMapImg->GetFileName()), "' loaded successfully.");
			PrintInfo(temp, COLOR_GREEN);

		}
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(tempImg->GetFileName()), "' already exists" );
		PrintInfo( temp, COLOR_YELLOW );
		numWarnings += 1;

		m_glossMapImg = tempImg;
		m_hasGlossMap = CTrue;
		m_loadedGlossMap = CTrue;
		Cpy( m_strGlossMap, m_strTemp2 );
		GetWithoutDot( m_strGlossMap );

	}
	m_updateGlossMap = CTrue;
	return CTrue;
}

CBool CPolyGroup::SetDirtMap( CString path, CBool test )
{ 
	if( path.IsEmpty() )
		return CFalse;
	Cpy( m_strOriginalDirtMapPath, (char*)path.GetBuffer(path.GetLength()) ); //save functions
	TrimOriginalPath( m_strOriginalDirtMapPath);
	path.ReleaseBuffer();

	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_dirtImg );
	CChar* m_strNameAfterPath = GetAfterPath(m_strTemp);
	GetWithoutDot( m_strNameAfterPath );
	CChar m_strTemp2[MAX_NAME_SIZE];
	sprintf( m_strTemp2, "%s%s", m_strNameAfterPath, ".dds" );
	CImage* tempImg = GetImage( m_strTemp2 );
	CBool foundTarget = CFalse;
	if( g_updateTextureViaEditor )
	{
		if( tempImg )
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
			PrintInfo( temp, COLOR_YELLOW );
			tempImg->Destroy();
			foundTarget = CTrue;
		}
		g_currentScene->IsInTextureList( m_strTemp2 );
	}
	else if( g_useOriginalPathOfDAETextures ) //save functions
	{
		if( !g_currentScene->IsInTextureList( m_strTemp2 ))
			if( tempImg )
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
				PrintInfo( temp, COLOR_YELLOW );
				tempImg->Destroy();
				foundTarget = CTrue;
			}
	}
	else
	{
		g_currentScene->IsInTextureList( m_strTemp2 );
	}

	if( tempImg == NULL || foundTarget )
	{
		if( !foundTarget )
			tempImg = CNew( CImage );
		CChar m_strTemp3[MAX_NAME_SIZE];
		if( g_useOriginalPathOfDAETextures || g_updateTextureViaEditor)
		{
			Cpy( m_strTemp3, m_strTemp );
		}
		else
		{
			//save functions. it should be copies in WIN32 Project as well
			if (g_editorMode == eMODE_VSCENE && !g_importPrefab)
			{
				CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(g_currentVSceneNameWithoutDot, g_currentVSceneName);
				GetWithoutDot(g_currentVSceneNameWithoutDot);

				sprintf(m_strTemp3, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp2);
			}
			else //prefab
			{
				sprintf(m_strTemp3, "%s%s%s%s", g_currentPrefabPackagePath, g_currentPrefabName, "/Textures/", m_strTemp2);
			}
		}
		CBool reportError = CFalse;
		if( foundTarget )
			reportError = CTrue;
		else
			reportError = !test;

		if( !CTexture::LoadDDSTexture( tempImg, m_strTemp3, "LoadDirtMapOfDAE", reportError ) )
		{
			if( test )
			{
				m_hasDirtMap = CFalse;
				Cpy(m_strDirtMap, "\n");
				m_updateDirtMap = CFalse;
			}
			else
			{
				m_hasDirtMap = CTrue;
				m_loadedDirtMap = CFalse;
				Cpy( m_strDirtMap, m_strTemp2 );
				GetWithoutDot( m_strDirtMap );
			}
			m_dirtMapImg = NULL;
			if( !foundTarget )
				CDelete( tempImg );
			return CFalse;
		}
	
		m_dirtMapImg = tempImg;
		Cpy( m_strDirtMap, m_strTemp2 );
		GetWithoutDot( m_strDirtMap );
		m_dirtMapImg->SetFileName( m_strTemp2 );
		m_hasDirtMap = CTrue;
		m_loadedDirtMap = CTrue;
		if(!foundTarget )
		{
			m_images.push_back( m_dirtMapImg );
			g_images.push_back( m_dirtMapImg );

			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Image '", GetAfterPath(m_dirtMapImg->GetFileName()), "' loaded successfully.");
			PrintInfo(temp, COLOR_GREEN);

		}
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(tempImg->GetFileName()), "' already exists" );
		PrintInfo( temp, COLOR_YELLOW );
		numWarnings += 1;

		m_dirtMapImg = tempImg;
		m_hasDirtMap = CTrue;
		m_loadedDirtMap = CTrue;
		Cpy( m_strDirtMap, m_strTemp2 );
		GetWithoutDot( m_strDirtMap );

	}
	m_updateDirtMap = CTrue;
	return CTrue;
}

CBool CPolyGroup::SetNormalMap( CString path, CFloat bias, CFloat scale, CBool test )
{ 
	m_parallaxMapBias = bias;
	m_parallaxMapScale = scale;
	if( path.IsEmpty() )
		return CFalse;
	Cpy( m_strOriginalNormalMapPath, (char*)path.GetBuffer(path.GetLength()) ); //save functions
	TrimOriginalPath( m_strOriginalNormalMapPath);
	path.ReleaseBuffer();

	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_normalImg );
	CChar* m_strNameAfterPath = GetAfterPath(m_strTemp);
	GetWithoutDot( m_strNameAfterPath );
	CChar m_strTemp2[MAX_NAME_SIZE];
	sprintf( m_strTemp2, "%s%s", m_strNameAfterPath, ".dds" );
	CImage* tempImg = GetImage( m_strTemp2 );

	CBool foundTarget = CFalse;
	if( g_updateTextureViaEditor )
	{
		if( tempImg )
		{
			CChar temp[MAX_NAME_SIZE];
			sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
			PrintInfo( temp, COLOR_YELLOW );
			tempImg->Destroy();
			foundTarget = CTrue;
		}
		g_currentScene->IsInTextureList( m_strTemp2 );
	}
	else if( g_useOriginalPathOfDAETextures ) //save functions
	{
		if( !g_currentScene->IsInTextureList( m_strTemp2 ))
			if( tempImg )
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf( temp, "\n%s%s%s", "Updating image '", GetAfterPath(tempImg->GetFileName()), "' ..." );
				PrintInfo( temp, COLOR_YELLOW );
				tempImg->Destroy();
				foundTarget = CTrue;
			}
	}
	else
	{
		g_currentScene->IsInTextureList( m_strTemp2 );
	}

	if( tempImg == NULL || foundTarget )
	{
		if( !foundTarget )
			tempImg = CNew( CImage );
		CChar m_strTemp3[MAX_NAME_SIZE];
		if( g_useOriginalPathOfDAETextures || g_updateTextureViaEditor)
		{
			Cpy( m_strTemp3, m_strTemp );
		}
		else
		{
			//save functions. it should be copies in WIN32 Project as well
			if (g_editorMode == eMODE_VSCENE && !g_importPrefab)
			{
				CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
				Cpy(g_currentVSceneNameWithoutDot, g_currentVSceneName);
				GetWithoutDot(g_currentVSceneNameWithoutDot);

				sprintf(m_strTemp3, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp2);
			}
			else //prefab
			{
				sprintf(m_strTemp3, "%s%s%s%s", g_currentPrefabPackagePath, g_currentPrefabName, "/Textures/", m_strTemp2);
			}
		}
		CBool reportError = CFalse;
		if( foundTarget )
			reportError = CTrue;
		else
			reportError = !test;
		if( !CTexture::LoadDDSTexture( tempImg, m_strTemp3, "LoadNormalMapOfDAE", reportError ) )
		{
			if( test )
			{
				m_hasNormalMap = CFalse;
				Cpy(m_strNormalMap, "\n");
				m_updateNormalMap = CFalse;
			}
			else
			{
				m_hasNormalMap = CTrue;
				m_loadedNormalMap = CFalse;
				Cpy( m_strNormalMap, m_strTemp2 );
				GetWithoutDot( m_strNormalMap );
			}
			m_normalMapImg = NULL;
			if( !foundTarget )
				CDelete( tempImg );
			return CFalse;
		}
	
		m_normalMapImg = tempImg;
		Cpy( m_strNormalMap, m_strTemp2 );
		GetWithoutDot( m_strNormalMap );
		m_normalMapImg->SetFileName( m_strTemp2 );
		m_hasNormalMap = CTrue;
		m_loadedNormalMap = CTrue;
		if( !foundTarget ) //save functions
		{
			m_images.push_back( m_normalMapImg );
			g_images.push_back( m_normalMapImg );

			CChar temp[MAX_NAME_SIZE];
			sprintf(temp, "\n%s%s%s", "Image '", GetAfterPath(m_normalMapImg->GetFileName()), "' loaded successfully.");
			PrintInfo(temp, COLOR_GREEN);

		}
	}
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Image '", GetAfterPath(tempImg->GetFileName()), "' already exists" );
		PrintInfo( temp, COLOR_YELLOW );
		numWarnings += 1;

		m_normalMapImg = tempImg;
		m_hasNormalMap = CTrue;
		m_loadedNormalMap = CTrue;
		Cpy( m_strNormalMap, m_strTemp2 );
		GetWithoutDot( m_strNormalMap );

	}
	m_updateNormalMap = CTrue;
	return CTrue;
}

CVoid CGeometry::SetDiffuse( CString path )
{ 
	Cpy( m_strDiffuse, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_diffuseImg );
	
	CChar m_strTemp[MAX_NAME_SIZE];
	sprintf( m_strTemp, "%s%s", m_strDiffuse, ".dds" );
	m_diffuseImg = GetImage( m_strTemp );
	if( m_diffuseImg == NULL )
	{
		m_diffuseImg = CNew( CImage );
		//save functions. it should be copies in WIN32 Project as well
		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
		GetWithoutDot( g_currentVSceneNameWithoutDot );
		sprintf( m_strDiffuse, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp );

		CTexture::LoadDDSTexture( m_diffuseImg, m_strDiffuse, NULL );
		Cpy( m_strDiffuse, m_strTemp );
		GetWithoutDot( m_strDiffuse );
		m_diffuseImg->SetFileName( m_strTemp );
		m_images.push_back( m_diffuseImg );
		g_images.push_back( m_diffuseImg );
	}
	m_hasDiffuse = CTrue;
};

CVoid CGeometry::SetNormalMap( CString path )
{ 
	Cpy( m_strNormalMap, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_normalMapImg );
	
	CChar m_strTemp[MAX_NAME_SIZE];
	sprintf( m_strTemp, "%s%s", m_strNormalMap, ".dds" );

	m_normalMapImg = GetImage( m_strTemp );
	if( m_normalMapImg == NULL )
	{
		m_normalMapImg = CNew( CImage );
		//save functions. it should be copies in WIN32 Project as well
		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
		GetWithoutDot( g_currentVSceneNameWithoutDot );
		sprintf( m_strNormalMap, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp );
		CTexture::LoadDDSTexture( m_normalMapImg, m_strNormalMap, NULL );
		Cpy( m_strNormalMap, m_strTemp );
		GetWithoutDot( m_strNormalMap );
		m_normalMapImg->SetFileName( m_strTemp );
		m_images.push_back( m_normalMapImg );
		g_images.push_back( m_normalMapImg );
	}
	m_hasNormalMap = CTrue;
	//m_hasHeightMap = CTrue; //Currently the alpha channel of normal map consists of height map
};

CVoid CGeometry::SetDirtMap( CString path ) { 
	Cpy( m_strDirtMap, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();

	//CTexture::DeleteTexture( m_dirtMapImg );
	CChar m_strTemp[MAX_NAME_SIZE];
	sprintf( m_strTemp, "%s%s", m_strDirtMap, ".dds" );
	m_dirtMapImg = GetImage( m_strTemp );
	if( m_dirtMapImg == NULL )
	{
		m_dirtMapImg = CNew( CImage );
		//save functions. it should be copies in WIN32 Project as well
		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
		GetWithoutDot( g_currentVSceneNameWithoutDot );
		sprintf( m_strDirtMap, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp );
		CTexture::LoadDDSTexture( m_dirtMapImg, m_strDirtMap, NULL );
		Cpy( m_strDirtMap, m_strTemp );
		GetWithoutDot( m_strDirtMap );
		m_dirtMapImg->SetFileName( m_strTemp );
		m_images.push_back( m_dirtMapImg );
		g_images.push_back( m_dirtMapImg );
	}

	m_hasDirtMap = CTrue;
};

CVoid CGeometry::SetGlossMap( CString path ) {
	Cpy( m_strGlossMap, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_glossMapImg );
	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, m_strGlossMap );
	m_glossMapImg = GetImage( m_strTemp );
	Cpy( m_strTemp, m_strGlossMap );
	if( m_glossMapImg == NULL )
	{
		m_glossMapImg = CNew( CImage );
		//save functions. it should be copies in WIN32 Project as well
		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
		GetWithoutDot( g_currentVSceneNameWithoutDot );
		sprintf( m_strGlossMap, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp );
		CTexture::LoadDDSTexture( m_glossMapImg, m_strGlossMap, NULL );
		Cpy( m_strGlossMap, m_strTemp );
		GetWithoutDot( m_strGlossMap );
		m_glossMapImg->SetFileName( m_strTemp );
		m_images.push_back( m_glossMapImg );
		g_images.push_back( m_glossMapImg );
	}
	m_hasGlossMap = CTrue;
}

CVoid CGeometry::SetHeightMap( CString path ) {
	Cpy( m_strHeightMap, (char*)path.GetBuffer(path.GetLength()) );
	path.ReleaseBuffer();
	//CTexture::DeleteTexture( m_heightMapImg );
	CChar m_strTemp[MAX_NAME_SIZE];
	Cpy( m_strTemp, m_strHeightMap );
	m_heightMapImg = GetImage( m_strTemp );
	Cpy( m_strTemp, m_strHeightMap );
	if( m_heightMapImg == NULL )
	{
		m_heightMapImg = CNew( CImage );
		//save functions. it should be copies in WIN32 Project as well
		CChar g_currentVSceneNameWithoutDot[MAX_NAME_SIZE];
		Cpy( g_currentVSceneNameWithoutDot, g_currentVSceneName );
		GetWithoutDot( g_currentVSceneNameWithoutDot );
		sprintf( m_strHeightMap, "%s%s%s%s", g_currentProjectPath, g_currentVSceneNameWithoutDot, "/Textures/", m_strTemp );
		CTexture::LoadDDSTexture( m_heightMapImg, m_strHeightMap, NULL );
		Cpy( m_strHeightMap, m_strTemp );
		Cpy( m_strHeightMap, m_strTemp );
		GetWithoutDot( m_strHeightMap );
		m_heightMapImg->SetFileName( m_strTemp );
		m_hasHeightMap = CTrue;
		m_images.push_back( m_heightMapImg );
		g_images.push_back( m_heightMapImg );
	}
}

CVoid CGeometry::SetSkins(CInt nbrJoints )
{
	(CVoid) nbrJoints;
	for(CUInt v = 0; v < m_vertexcount; v++)
	{//	CInt v = indexes[p];
		CInt nbrInf = m_weights[v].m_numInfluences; 
		if( nbrInf )
		{
			CVec3f BSMVert; 
			CVec3f BSMNorm; 
			CVec3f transVert; 
			CVec3f weightVert;
			CVec3f transNorm; 
			CVec3f weightNorm; 
			CInt joint = 0; 
			CFloat weight = 0; 
			CFloat weightTotal = 0; 
			CFloat weightNormalized = 0; 	
			//moved the bind shape multiplication to CScene::ReadGeometry. 
			BSMVert = m_bindPoints[v];
			BSMNorm = m_bindNormals[v];

			for( CInt j = 0; j < nbrInf ; j++)
			{
				joint =  m_weights[v].m_joints[j];				
				weight = m_weights[v].m_weights[j];

				assert( weight >= 0 && weight < 1.01f ); 
				assert( joint > -1 && joint < nbrJoints ); 

				CMatrix3x4TransformSkin( m_skinMatrixStack[joint], BSMVert, transVert );
				CMatrix3x4RotateSkin( m_skinMatrixStack[joint], BSMNorm, transNorm ); 

				transVert.x *= weight;
				transVert.y *= weight; 
				transVert.z *= weight; 

				transNorm.x *= weight; 
				transNorm.y *= weight; 
				transNorm.z *= weight; 

				weightVert.x += transVert.x;  
				weightVert.y += transVert.y;  
				weightVert.z += transVert.z;

				weightNorm.x += transNorm.x;
				weightNorm.y += transNorm.y; 
				weightNorm.z += transNorm.z; 

				weightTotal += m_weights[v].m_weights[j];
			}

			if (weightTotal != 1.0f)
			{
				weightNormalized = 1.0f/weightTotal;
				weightVert.x *= weightNormalized;
				weightVert.y *= weightNormalized; 
				weightVert.z *= weightNormalized; 
				weightNorm.x *= weightNormalized; 
				weightNorm.y *= weightNormalized; 
				weightNorm.z *= weightNormalized; 
			}

			m_points[v] = weightVert;
			if ( m_normals )
				m_normals[v] = weightNorm; 

			if( m_upAxis == eCZUp )
			{
				CVec3f tempv;
				CMatrix TransformZUpRotationForSkins;
				CMatrixLoadIdentity( TransformZUpRotationForSkins );
				CVec4f rot( 1.0, 0.0, 0.0, 90.0 );
				CMatrix4x4RotateAngleAxis( TransformZUpRotationForSkins, rot );

				tempv = m_points[v];
				CMatrixTransform(TransformZUpRotationForSkins, tempv, m_points[v] );

				if ( m_normals )
				{
					tempv = m_normals[v];
					CMatrixTransform(TransformZUpRotationForSkins, tempv, m_normals[v] );
				}
			}
		}
		else
		{
			if (m_skinData->m_bindShapeMats)
			{
				CMatrix3x4TransformSkin( m_skinData->m_bindShapeMats, m_bindPoints[v], m_points[v] );
				CMatrix3x4TransformSkin( m_skinData->m_bindShapeMats, m_bindNormals[v], m_normals[v] );
			}

			//PrintInfo("\nCGeometry::SetSkins:: No Influences", COLOR_RED ); 
		}
	}
};

CChar * CGeometry::GetSkinName()
{
	if ( m_skinData )
		return m_skinData->GetName();
	return 	NULL;
}


CVoid CGeometry::DrawSkinned(CNode *parentNode, CInstance * instance )
{	
	if ( m_skinData )
	{
		if (m_updateSkin)
		{
			// copy the skinned matrices from the joint nodes 
			m_skinData->UpdateCombinedMats();

			// use the gemetry normals 
			if (!m_skinData->GetBindNormals() && !m_bindNormals)
			{
				m_bindNormals = CNewData(CVec3f, m_vertexcount);
				memcpy(m_bindNormals, m_normals, m_vertexcount * sizeof(CVec3f));
				m_bindPoints = CNewData(CVec3f, m_vertexcount);
				memcpy(m_bindPoints, m_points, m_vertexcount * sizeof(CVec3f));
			}

			m_skinMatrixStack = m_skinData->m_skinningMats;
			m_skinMatrixStack3x4 = m_skinData->m_skinningMats3x4;
			SetSkins(m_skinData->GetJointCount());

			if (g_render.UsingVBOs() && g_options.m_enableVBO)
			{
				//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints],m_points, m_vertexcount*3*sizeof(CFloat));
				//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals],m_normals, m_vertexcount*3*sizeof(CFloat));
				//glBufferSubData is faster than glBufferData, since it doesn't need freeing and reallocating the memory
				g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints], m_points, 0, m_vertexcount * 3 * sizeof(CFloat));
				g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals], m_normals, 0, m_vertexcount * 3 * sizeof(CFloat));
			}

			m_updateSkin = CFalse;
		}

		if (g_renderShadow)
		{
			for (CUInt i = 0; i < m_groups.size(); i++)
			{
				CPolyGroup* group = m_groups[i];
				if (g_renderShadow && (!g_render.m_useShader || !g_render.UsingShader() || !g_options.m_enableShader) && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
				{
					glEnable(GL_ALPHA_TEST);
					glAlphaFunc(GL_GREATER, 0.5);

					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, group->m_diffuseImg->GetId());
					glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
				}

				m_groups[i]->Render();

				if (g_renderShadow && (!g_render.m_useShader || !g_render.UsingShader() || !g_options.m_enableShader) && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
				{
					glDisable(GL_ALPHA_TEST);
				}

			}
			return;
		}
		CGeometryColor color;
		for (CUInt i = 0; i < m_instanceGeometries.size(); i++ )
		{
			if( g_selectedName == m_instanceGeometries[i]->m_nameIndex )
			{
				if( m_instanceGeometries[i]->m_nameIndex == m_currentInstanceGeometry->m_nameIndex )
				{
					color = eCOLOR_WHITE;
					break;
				}
				else
				{
					color = eCOLOR_GREEN;
				}
			}
			else{
				color = eCOLOR_MATERIAL;
			}
		}
		for (CUInt i = 0; i < m_instanceControllers.size(); i++ )
		{
			if( g_selectedName == m_instanceControllers[i]->m_instanceGeometry->m_nameIndex )
			{
				if( m_instanceControllers[i]->m_instanceGeometry->m_nameIndex == m_currentInstanceGeometry->m_nameIndex )
				{
					color = eCOLOR_WHITE;
					break;
				}
				else
				{
					color = eCOLOR_GREEN;
				}
			}
			else{
				color = eCOLOR_MATERIAL;
			}
		}

		for (CUInt i = 0; i < m_groups.size(); i++ )
		{
			if (g_multipleView->m_renderQuery && m_groups[i]->m_diffuseImg && m_groups[i]->m_diffuseImg->GetFormat() == 4)
				glDepthMask(GL_FALSE);

			m_groups[i]->EnableShader();

			SetGroupRender( m_groups[i] );
			if( g_menu.m_geometryBasedSelection )
			{
				m_groups[i]->Draw(parentNode, instance, color, m_groups[i]->m_hasDiffuse );
			}
			else
			{
				if( m_groups[i]->m_nameIndex == g_selectedName )
					m_groups[i]->Draw(parentNode, instance, eCOLOR_WHITE, m_groups[i]->m_hasDiffuse );
				else 
					m_groups[i]->Draw(parentNode, instance, eCOLOR_MATERIAL, m_groups[i]->m_hasDiffuse );
			}
			if (g_multipleView->m_renderQuery && m_groups[i]->m_diffuseImg && m_groups[i]->m_diffuseImg->GetFormat() == 4)
				glDepthMask(GL_TRUE);
			ResetGroupStates( m_groups[i] );
		}		
	}
}

CVoid CGeometry::DrawSkinnedSelectionMode(CNode *parentNode, CInstance * instance )
{	
	if ( m_skinData )
	{
		// copy the skinned matrices from the joint nodes 
		m_skinData->UpdateCombinedMats(); 
		
		// use the gemetry normals 
		if ( !m_skinData->GetBindNormals() && !m_bindNormals )
		{
			m_bindNormals = CNewData( CVec3f, m_vertexcount );  	
			memcpy(m_bindNormals, m_normals, m_vertexcount * sizeof( CVec3f ));  
			m_bindPoints = CNewData( CVec3f, m_vertexcount );  	
			memcpy(m_bindPoints, m_points, m_vertexcount * sizeof( CVec3f ));  
		}

		m_skinMatrixStack = m_skinData->m_skinningMats; 
		m_skinMatrixStack3x4 = m_skinData->m_skinningMats3x4; 
		SetSkins(m_skinData->GetJointCount());

		if (g_render.UsingVBOs() && g_options.m_enableVBO )
		{
			//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints],m_points, m_vertexcount*3*sizeof(CFloat));
			//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals],m_normals, m_vertexcount*3*sizeof(CFloat));
			//glBufferSubData is faster than glBufferData, since it doesn't need freeing and reallocating the memory
			g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints],m_points, 0, m_vertexcount*3*sizeof(CFloat));
			g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals],m_normals, 0, m_vertexcount*3*sizeof(CFloat));
		}

		for (CUInt i = 0; i < m_groups.size(); i++ )
		{
			if( !g_menu.m_geometryBasedSelection )
				glPushName( m_groups[i]->m_nameIndex );
			m_groups[i]->Draw(parentNode, instance, eCOLOR_MATERIAL, m_groups[i]->m_hasDiffuse );
			if( !g_menu.m_geometryBasedSelection )
				glPopName();
		}		
	}
}

CVoid CGeometry::Draw(CNode *parentNode, CInstance * instance)
{
	if (g_multipleView->m_pushTransparentGeometry)
	{
		CInt numTransparentPolys = 0;
		for (CUInt i = 0; i < m_groups.size(); i++)
		{
			CFloat transparency = m_groups[i]->m_fTransparency;

			if (g_editorMode == eMODE_VSCENE && g_currentInstancePrefab && g_currentInstancePrefab->IsMaterialEnabled())
			{
				transparency = g_currentInstancePrefab->GetTransparency();
			}

			if (transparency < 1.0f)
			{
				numTransparentPolys++;
			}
		}
		if (numTransparentPolys > 0) //push prefab instance and geometry
		{
			CTransparentGeometry transparent_geometry;

			if (g_editorMode == eMODE_VSCENE)
			{
				if (g_currentInstancePrefab)
				{
					transparent_geometry.m_instancePrefab = g_currentInstancePrefab;
					transparent_geometry.m_scene = g_render.GetScene();
					transparent_geometry.m_instanceGeometry = m_currentInstanceGeometry;
					g_multipleView->AddTransparentGeometry(transparent_geometry);
				}
			}
			else if (g_editorMode == eMODE_PREFAB)
			{
				if (g_render.GetScene())
				{
					transparent_geometry.m_scene = g_render.GetScene();
					transparent_geometry.m_instanceGeometry = m_currentInstanceGeometry;
					g_multipleView->AddTransparentGeometry(transparent_geometry);
				}
			}
		}

		if (numTransparentPolys == m_groups.size()) //this geometry is transparent
		{
			if (m_skinData && m_updateSkin)
			{
				if (m_updateSkin)
				{
					// copy the skinned matrices from the joint nodes 
					m_skinData->UpdateCombinedMats();

					// use the gemetry normals 
					if (!m_skinData->GetBindNormals() && !m_bindNormals)
					{
						m_bindNormals = CNewData(CVec3f, m_vertexcount);
						memcpy(m_bindNormals, m_normals, m_vertexcount * sizeof(CVec3f));
						m_bindPoints = CNewData(CVec3f, m_vertexcount);
						memcpy(m_bindPoints, m_points, m_vertexcount * sizeof(CVec3f));
					}

					m_skinMatrixStack = m_skinData->m_skinningMats;
					m_skinMatrixStack3x4 = m_skinData->m_skinningMats3x4;
					SetSkins(m_skinData->GetJointCount());

					if (g_render.UsingVBOs() && g_options.m_enableVBO)
					{
						//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints],m_points, m_vertexcount*3*sizeof(CFloat));
						//g_render.CopyVBOData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals],m_normals, m_vertexcount*3*sizeof(CFloat));
						//glBufferSubData is faster than glBufferData, since it doesn't need freeing and reallocating the memory
						g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints], m_points, 0, m_vertexcount * 3 * sizeof(CFloat));
						g_render.CopyVBOSubData(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals], m_normals, 0, m_vertexcount * 3 * sizeof(CFloat));
					}

					m_updateSkin = CFalse;
				}
			}
			return;
		}
	}

	SetRender();
  	if ( m_skinData )
	{
		DrawSkinned(parentNode, instance ); 	
	}
	else
	{
		CGeometryColor color = eCOLOR_MATERIAL;
		for (CUInt i = 0; i < m_instanceGeometries.size(); i++ )
		{
			if( g_selectedName == m_instanceGeometries[i]->m_nameIndex )
			{
				if (Cmp(this->GetName(), "geom-XAXIS") || Cmp(this->GetName(), "geom-YAXIS") || Cmp(this->GetName(), "geom-ZAXIS") || Cmp(this->GetName(), "geom-XYZ"))
				{
					color = eCOLOR_YELLOW;
					break;
				}
				if( m_instanceGeometries[i]->m_nameIndex == m_currentInstanceGeometry->m_nameIndex )
				{
					color = eCOLOR_WHITE;
					break;
				}
				else
				{
					color = eCOLOR_GREEN;
					break;
				}
			}
		}
		for (CUInt i = 0; i < m_instanceControllers.size(); i++ )
		{
			if( g_selectedName == m_instanceControllers[i]->m_instanceGeometry->m_nameIndex )
			{
				if( m_instanceControllers[i]->m_instanceGeometry->m_nameIndex == m_currentInstanceGeometry->m_nameIndex )
				{
					color = eCOLOR_WHITE;
					break;
				}
				else
				{
					color = eCOLOR_GREEN;
					break;
				}
			}
		}

		for (CUInt i = 0; i < m_groups.size(); i++ )
		{
			if (g_multipleView->m_renderQuery && m_groups[i]->m_diffuseImg && m_groups[i]->m_diffuseImg->GetFormat() == 4)
				glDepthMask(GL_FALSE);

			m_groups[i]->EnableShader();

			SetGroupRender( m_groups[i] );
			if( g_menu.m_geometryBasedSelection )
			{
				m_groups[i]->Draw(parentNode, instance, color, m_groups[i]->m_hasDiffuse ); 
			}
			else
			{
				if( m_groups[i]->m_nameIndex == g_selectedName )
					m_groups[i]->Draw(parentNode, instance, eCOLOR_WHITE, m_groups[i]->m_hasDiffuse ); 
				else
					m_groups[i]->Draw(parentNode, instance, eCOLOR_MATERIAL, m_groups[i]->m_hasDiffuse ); 
			}
			if (g_multipleView->m_renderQuery && m_groups[i]->m_diffuseImg && m_groups[i]->m_diffuseImg->GetFormat() == 4)
				glDepthMask(GL_TRUE);

			ResetGroupStates( m_groups[i] );
		}			
	}
	ResetStates();
};

CVoid CGeometry::DrawSelectionMode(CNode *parentNode, CInstance * instance)
{
	SetRender();
  	if ( m_skinData )
	{
		DrawSkinnedSelectionMode(parentNode, instance ); 	
	}
	else
	{
		for (CUInt i = 0; i < m_groups.size(); i++ )
		{
			if( !g_menu.m_geometryBasedSelection )
				glPushName( m_groups[i]->m_nameIndex );
			m_groups[i]->Draw(parentNode, instance, eCOLOR_MATERIAL, m_groups[i]->m_hasDiffuse ); 
			if( !g_menu.m_geometryBasedSelection )
				glPopName();
		}
	}
	ResetStates();
}

CVoid	CGeometry::GetJointsForWeights( CJoint *& Joints, CInt & NumJoints )
{	
	if ( m_skinData )
	{
		Joints = m_skinData->GetJoints();
		NumJoints = m_skinData->GetJointCount(); 
	}
};

CVoid CGeometry::ResetStates()
{
	glActiveTextureARB(GL_TEXTURE7_ARB);
	glDisable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, 0);

    glClientActiveTexture(GL_TEXTURE0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		glClientActiveTexture(GL_TEXTURE1);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glClientActiveTexture(GL_TEXTURE2);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glClientActiveTexture(GL_TEXTURE3);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture( GL_TEXTURE7);
		glBindTexture( GL_TEXTURE_2D, 0 );
		glDisable( GL_TEXTURE_2D );

	}

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState( GL_VERTEX_ARRAY );

	g_render.BindVBO(GL_ARRAY_BUFFER, 0 );

}

CVoid CGeometry::SetGroupRender( CPolyGroup* group )
{
	if (g_polygonMode != ePOLYGON_FILL)
	{
		glUseProgram(0);
		// Disable the texture units.
		glActiveTextureARB(GL_TEXTURE5_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE4_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE3_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
		return;
	}

	if( !g_renderShadow && !g_multipleView->m_renderQuery && group->m_loadedDiffuse && group->m_hasDiffuse && group->m_diffuseImg && g_polygonMode == ePOLYGON_FILL)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable( GL_TEXTURE_2D );
		glBindTexture(GL_TEXTURE_2D, group->m_diffuseImg->GetId() );
		if ((!g_render.m_useShader || !g_render.UsingShader() || !g_options.m_enableShader) && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
		{
			glEnable( GL_ALPHA_TEST );
			glAlphaFunc( GL_GREATER, 0 );
		}
	}
	if (g_renderShadow && (!g_render.m_useShader || !g_render.UsingShader() || !g_options.m_enableShader) && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5);

		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, group->m_diffuseImg->GetId());
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}

	if( g_render.UsingShader() && g_render.m_useShader && g_options.m_enableShader)
	{
		if( group->m_loadedGlossMap && group->m_hasGlossMap  && group->m_glossMapImg && g_polygonMode == ePOLYGON_FILL)
		{
			glActiveTexture( GL_TEXTURE3 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, group->m_glossMapImg->GetId() );
		}

		if( group->m_loadedDirtMap && group->m_hasDirtMap  && group->m_dirtMapImg &&  g_polygonMode == ePOLYGON_FILL)
		{
			glActiveTexture( GL_TEXTURE5 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, group->m_dirtMapImg->GetId() );
		}

		if( group->m_loadedNormalMap && group->m_hasNormalMap  && group->m_normalMapImg && g_polygonMode == ePOLYGON_FILL)
		{
			glActiveTexture( GL_TEXTURE1 );
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, group->m_normalMapImg->GetId() );
		}

		if( group->m_loadedDiffuse && group->m_hasDiffuse && group->m_diffuseImg)
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "colorMap"), 0);
			glUniform1i(glGetUniformLocation( g_shaderType , "enableColorMap"), CTrue );
		}
		else
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "enableColorMap"), CFalse );
		}

		if( group->m_loadedNormalMap && group->m_hasNormalMap && group->m_normalMapImg)
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "normalMap"), 1);
			glUniform1i(glGetUniformLocation( g_shaderType , "enableNormalMap"), CTrue );

			if( group->m_normalMapImg->GetFormat() == 4 )
			{
				glUniform1i(glGetUniformLocation( g_shaderType , "enableParallaxMap"), CTrue );
				glUniform1f(glGetUniformLocation( g_shaderType , "parallaxMapBias"), group->m_parallaxMapBias );
				glUniform1f(glGetUniformLocation( g_shaderType , "parallaxMapScale"), group->m_parallaxMapScale );
			}
			else 
				glUniform1i(glGetUniformLocation( g_shaderType , "enableParallaxMap"), CFalse );
		}
		else
			glUniform1i(glGetUniformLocation( g_shaderType , "enableNormalMap"), CFalse );

		if( group->m_loadedDirtMap && group->m_hasDirtMap && group->m_dirtMapImg && m_texCoords[1] )
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "dirtMap"), 5);
			glUniform1i(glGetUniformLocation( g_shaderType , "enableDirtMap"), CTrue );
		}
		else
			glUniform1i(glGetUniformLocation( g_shaderType , "enableDirtMap"), CFalse );

		if (group->m_loadedDiffuse && group->m_hasDiffuse && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "alphaMap"), 0);
			glUniform1i(glGetUniformLocation(g_shaderType, "enableAlphaMap"), CTrue);
		}
		else
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "enableAlphaMap"), CFalse );
		}

		if( group->m_loadedGlossMap && group->m_hasGlossMap && group->m_glossMapImg )
		{
			glUniform1i(glGetUniformLocation( g_shaderType , "glossMap"), 3);
			glUniform1i(glGetUniformLocation( g_shaderType , "enableGlossMap"), CTrue );
		}
		else
			glUniform1i(glGetUniformLocation( g_shaderType , "enableGlossMap"), CFalse );

	}
}

CVoid CGeometry::ResetGroupStates( CPolyGroup* group )
{
	if( g_render.UsingShader() && g_render.m_useShader && g_options.m_enableShader)
	{
		if( group->m_hasDirtMap )
		{
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		if( group->m_hasNormalMap )
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}

		if( group->m_hasGlossMap )
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisable(GL_TEXTURE_2D);
		}
	}

	if( group->m_hasDiffuse )
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		if ((!g_render.m_useShader || !g_render.UsingShader() || !g_options.m_enableShader) && group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
		{
			glDisable( GL_ALPHA_TEST );
		}
	}


}

CVoid CGeometry::SetRender()
{

	if( m_cullFaces && g_polygonMode == ePOLYGON_FILL)
		glEnable( GL_CULL_FACE );
	else
		glDisable( GL_CULL_FACE );

	if (g_render.UsingVBOs() && g_options.m_enableVBO && g_renderShadow)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints]);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		for (CUInt i = 0; i < m_groups.size(); i++)
		{
			CPolyGroup* group = m_groups[i];
			if (group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
			{
				//Used For Alpha Blending
				if (m_texCoords[0]) {
					glClientActiveTexture(GL_TEXTURE0);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoTexCoord0]);
					glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				}
				break;
			}
		}
		return;
	}
	else if (g_renderShadow)
	{
		g_render.BindVBO(GL_ARRAY_BUFFER, 0); //disable VBOs
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, m_points);

		for (CUInt i = 0; i < m_groups.size(); i++)
		{
			CPolyGroup* group = m_groups[i];
			if (group->m_diffuseImg && group->m_diffuseImg->GetFormat() == 4)
			{
				//Used For Alpha Blending
				if (m_texCoords[0]) {
					glClientActiveTexture(GL_TEXTURE0);
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoTexCoord0]);
					glTexCoordPointer(2, GL_FLOAT, 0, NULL);
				}
				break;
			}
		}

		return;
	}

	if (g_render.UsingVBOs() && g_options.m_enableVBO )
	{
		glEnableClientState(GL_VERTEX_ARRAY); 
		g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoPoints]);
		glVertexPointer( 3, GL_FLOAT, 0, NULL);				

		if (m_normals) {
			glEnableClientState(GL_NORMAL_ARRAY);
			g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoNormals]);
			glNormalPointer( GL_FLOAT, 0, NULL);
		}
		if (m_texCoords[0]) {
			glClientActiveTexture(GL_TEXTURE0);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoTexCoord0]);
			glTexCoordPointer( 2, GL_FLOAT, 0, NULL);
		}
		if( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
		{
			if (m_texCoords[1] && m_hasDirtMap ) {
				glClientActiveTexture(GL_TEXTURE3);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoTexCoord1]);
				glTexCoordPointer( 2, GL_FLOAT, 0, NULL );
			}
		}

		if( g_options.m_enableShader && g_render.UsingShader()  && m_hasNormalMap && g_render.m_useShader )
		{
			glClientActiveTexture(GL_TEXTURE1);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoTangents]);
			glTexCoordPointer(3, GL_FLOAT,0, NULL );
			
			glClientActiveTexture(GL_TEXTURE2);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			g_render.BindVBO(GL_ARRAY_BUFFER, m_VBOIDs[eGeoBiNormals]);
			glTexCoordPointer(3, GL_FLOAT,0, NULL );

		}

		return;
	}
	g_render.BindVBO(GL_ARRAY_BUFFER, 0 ); //disable VBOs
	glEnableClientState(GL_VERTEX_ARRAY); 
	glVertexPointer ( 3, GL_FLOAT, 0, m_points );

	if (m_normals) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer( GL_FLOAT, 0, m_normals );
	}
	if (m_texCoords[0]) {
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer( 2, GL_FLOAT, 0, m_texCoords[0] );
	}
	if( g_options.m_enableShader && g_render.UsingShader() && m_hasNormalMap && g_render.m_useShader )
	{
		glClientActiveTexture(GL_TEXTURE1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT,0, m_tangents );

		glClientActiveTexture(GL_TEXTURE2);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(3, GL_FLOAT,0, m_bNormals );
	}
	if( g_options.m_enableShader && g_render.UsingShader() && g_render.m_useShader )
	{
		if (m_texCoords[1] && m_hasDirtMap ) {
			glClientActiveTexture(GL_TEXTURE3);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer( 2, GL_FLOAT, 0, m_texCoords[1]);
		}
	}

}

CTriangles::CTriangles()
{
	m_VBOID = 0;
}
CTriangles::~CTriangles()
{
	if (m_VBOID!=0)
	{
		g_render.FreeVBO(m_VBOID);
		m_VBOID=0;
	}
	CDeleteData(m_indexes);
}
CVoid CTriangles::Render()
{
	if ( g_render.UsingVBOs() && g_options.m_enableVBO )
	{
		g_render.BindVBO(GL_ELEMENT_ARRAY_BUFFER, m_VBOID);
		glDrawElements( GL_TRIANGLES, m_count * 3, GL_UNSIGNED_INT, 0);
		g_render.BindVBO(GL_ELEMENT_ARRAY_BUFFER, 0 );
	}
	else
	{
		g_render.BindVBO(GL_ELEMENT_ARRAY_BUFFER, 0 ); // Disable VBOs
		glDrawElements( GL_TRIANGLES, m_count * 3, GL_UNSIGNED_INT, m_indexes);
	}
}

CVoid CTriangles::SetVBOs()
{
	m_VBOID = g_render.GenerateVBO();
	g_render.CopyVBOData(GL_ELEMENT_ARRAY_BUFFER, m_VBOID, m_indexes, m_count * 3 * sizeof(CFloat));
}

CGeometry::~CGeometry()
{
	m_instanceGeometries.clear();
	m_instanceControllers.clear();
	while(!m_physx_triangles.empty())
	{
		CDelete(m_physx_triangles[0]);
		m_physx_triangles.erase(m_physx_triangles.begin());
	}
	while(!m_physx_points.empty())
	{
		CDelete(m_physx_points[0]);
		m_physx_points.erase(m_physx_points.begin());
	}
	while(!m_groups.empty())
	{
		CDelete(m_groups[0]);
		m_groups.erase(m_groups.begin());
	}
	
	CDeleteData(m_points);
	CDeleteData(m_normals);

	for( CInt i = 0; i < MAX_TEX_COORDS; i++ )
	{
		if( m_texCoords[i] )
			CDeleteData(m_texCoords[i]);
	}

	CDeleteData(m_tangents);
	CDeleteData(m_bNormals);
	CDeleteData(m_skinIndex);
	CDeleteData(m_weights);

	//Delete external image data 
	//CDelete(m_normalMapImg);

	//Clear all the images
	//for( std::vector<CImage*>::iterator it = m_images.begin(); it != m_images.end(); it++ )
	//{
	//	CDelete( *it );
	//}
	//Clear the vector objects
	m_images.clear();

	//CDelete(m_dirtMapImg);
	//CDelete(m_glossMapImg);
	//CDelete(m_heightMapImg);
	//CDelete(m_dudvMapImg);

	if( g_render.UsingVBOs() )
	{
		if (m_VBOIDs[eGeoPoints]!=0)
		{
			g_render.FreeVBO(m_VBOIDs[eGeoPoints]);
			m_VBOIDs[eGeoPoints]=0;
		}
		if( m_VBOIDs[eGeoNormals] != 0 )
		{
			g_render.FreeVBO(m_VBOIDs[eGeoNormals]);
			m_VBOIDs[eGeoNormals]=0;
		}

		for( int i = 0; i < MAX_TEX_COORDS; i++ )
		{
			if( m_VBOIDs[eGeoTexCoord0 + i ] != 0 )
			{
				g_render.FreeVBO(m_VBOIDs[eGeoTexCoord0 + i ]);
				m_VBOIDs[eGeoTexCoord0 + i ]= 0;
			}
		}

		if( m_VBOIDs[eGeoTangents] != 0 )
		{
			g_render.FreeVBO(m_VBOIDs[eGeoTangents]);
			m_VBOIDs[eGeoTangents]=0;
		}
		if( m_VBOIDs[eGeoBiNormals] != 0 )
		{
			g_render.FreeVBO(m_VBOIDs[eGeoBiNormals]);
			m_VBOIDs[eGeoBiNormals]=0;
		}
	}
}

CVoid CInstanceGeometry::CalculateDistance()
{
	if (g_camera)
	{
		CFloat x = g_camera->m_perspectiveCameraPos.x - m_center.x;
		CFloat y = g_camera->m_perspectiveCameraPos.y - m_center.y;
		CFloat z = g_camera->m_perspectiveCameraPos.z - m_center.z;

		m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
}
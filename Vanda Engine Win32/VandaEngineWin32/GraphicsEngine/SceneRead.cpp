//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2024 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "scene.h"
#include "render.h"
//#include "Utils.h"
//#include "Render.h"
//#include "Matrix.h"
//#include "Node.h"
//#include "Geometry.h"

//#include <cfxEffect.h>
//#include <cfxMaterial.h>
//#include <cfxSurface.h>

// COLLADA_DOM includes 

#include "dae.h"
#include "dae/daeSIDResolver.h"
#include "dom/domCOLLADA.h"
#include "dom/domProfile_COMMON.h"
#include "dae/domAny.h"
#include "dom/domElements.h"
#include "Animation.h"
#include <stdio.h>
#include <map>
#include <string>
using namespace std;

class CShaderElements
{
public:
	CShaderElements() :
	    m_emission(NULL),
		m_ambient(NULL),
		m_diffuse(NULL),
		m_specular(NULL),
		m_shininess(NULL),
		m_reflective(NULL),
		m_reflectivity(NULL),
		m_transparent(NULL),
		m_transarency(NULL),
		m_index_of_refaction(NULL){};

	~CShaderElements() {};

	domCommon_color_or_texture_type *m_emission;
	domCommon_color_or_texture_type *m_ambient;
	domCommon_color_or_texture_type *m_diffuse;
	domCommon_color_or_texture_type *m_specular;
	domCommon_float_or_param_type   *m_shininess;

	domCommon_color_or_texture_type *m_reflective;
	domCommon_float_or_param_type   *m_reflectivity;
	domCommon_color_or_texture_type_complexType *m_transparent;
	domCommon_float_or_param_type   *m_transarency;
	domCommon_float_or_param_type   *m_index_of_refaction;
}; 


CFloat ReadFloatOrParamType(CEffect * effect, domCommon_float_or_param_typeRef float_or_param)
{
	(CVoid) effect;
	if (float_or_param->getFloat())
	{
		return (CFloat)  float_or_param->getFloat()->getValue();
	}
	return (CFloat) 0;
}

CColor4f ReadColorOrTextureType(CEffect * effect, domCommon_color_or_texture_type_complexType * color_or_texture)
{
	(CVoid) effect;
	if (color_or_texture->getColor())
	{
		domFx_color_common & color = color_or_texture->getColor()->getValue();

		return CColor4f((CFloat) color[0], (CFloat) color[1], (CFloat) color[2], (CFloat) color[3]);
	}
	return CColor4f();
}

CVoid ReadPhong(CEffect * effect, CShaderElements * shader, domProfile_COMMON::domTechnique::domPhong *phong)
{
	shader->m_emission = phong->getEmission();
	if (shader->m_emission ) {
		effect->m_emission = ReadColorOrTextureType(effect, shader->m_emission);
	}
	shader->m_ambient = phong->getAmbient();
	if (shader->m_ambient ) {
		effect->m_ambient = ReadColorOrTextureType(effect, shader->m_ambient);
	}
	shader->m_diffuse = phong->getDiffuse();
	if (shader->m_diffuse) {
		effect->m_diffuse = ReadColorOrTextureType(effect, shader->m_diffuse);
	}
	shader->m_specular = phong->getSpecular();
	if (shader->m_specular) {
		effect->m_specular = ReadColorOrTextureType(effect, shader->m_specular);
	}
	shader->m_shininess = phong->getShininess();
	if (shader->m_shininess) {
		effect->m_shininess = ReadFloatOrParamType(effect, shader->m_shininess);
	}
	shader->m_reflective = phong->getReflective();
	if (shader->m_reflective) {
		effect->m_reflective = ReadColorOrTextureType(effect, shader->m_reflective);
	}
	shader->m_reflectivity = phong->getReflectivity();
	if (shader->m_reflectivity) {
		effect->m_reflectivity = ReadFloatOrParamType(effect, shader->m_reflectivity);
	}
	shader->m_transparent = phong->getTransparent();
	if (shader->m_transparent) {
		effect->m_transparent = ReadColorOrTextureType(effect, shader->m_transparent);
	}
	shader->m_transarency = phong->getTransparency();
	if (shader->m_transarency) {
		effect->m_transparency = ReadFloatOrParamType(effect, shader->m_transarency);
	}
	shader->m_index_of_refaction = phong->getIndex_of_refraction();
	if (shader->m_index_of_refaction) {
		effect->m_refractiveIndex = ReadFloatOrParamType(effect, shader->m_index_of_refaction);
	}
}

CVoid ReadConstant(CEffect * effect, CShaderElements * shader, domProfile_COMMON::domTechnique::domConstant *constant)
{
	shader->m_emission = constant->getEmission();
	if (shader->m_emission ) {
		effect->m_emission = ReadColorOrTextureType(effect, shader->m_emission);
	}
	shader->m_reflective = constant->getReflective();
	if (shader->m_reflective) {
		effect->m_reflective = ReadColorOrTextureType(effect, shader->m_reflective);
	}
	shader->m_reflectivity = constant->getReflectivity();
	if (shader->m_reflectivity) {
		effect->m_reflectivity = ReadFloatOrParamType(effect, shader->m_reflectivity);
	}
	shader->m_transparent = constant->getTransparent();
	if (shader->m_transparent) {
		effect->m_transparent = ReadColorOrTextureType(effect, shader->m_transparent);
	}
	shader->m_transarency = constant->getTransparency();
	if (shader->m_transarency) {
		effect->m_transparency = ReadFloatOrParamType(effect, shader->m_transarency);
	}
	shader->m_index_of_refaction = constant->getIndex_of_refraction();
	if (shader->m_index_of_refaction) {
		effect->m_refractiveIndex = ReadFloatOrParamType(effect, shader->m_index_of_refaction);
	}
}

CVoid ReadLambert(CEffect * effect, CShaderElements * shader, domProfile_COMMON::domTechnique::domLambert *lambert)
{
	shader->m_emission = lambert->getEmission();
	if (shader->m_emission ) {
		effect->m_emission = ReadColorOrTextureType(effect, shader->m_emission);
	}
	shader->m_ambient = lambert->getAmbient();
	if (shader->m_ambient ) {
		effect->m_ambient = ReadColorOrTextureType(effect, shader->m_ambient);
	}
	shader->m_diffuse = lambert->getDiffuse();
	if (shader->m_diffuse) {
		effect->m_diffuse = ReadColorOrTextureType(effect, shader->m_diffuse);
	}
	shader->m_reflective = lambert->getReflective();
	if (shader->m_reflective) {
		effect->m_reflective = ReadColorOrTextureType(effect, shader->m_reflective);
	}
	shader->m_reflectivity = lambert->getReflectivity();
	if (shader->m_reflectivity) {
		effect->m_reflectivity = ReadFloatOrParamType(effect, shader->m_reflectivity);
	}
	shader->m_transparent = lambert->getTransparent();
	if (shader->m_transparent) {
		effect->m_transparent = ReadColorOrTextureType(effect, shader->m_transparent);
	}
	shader->m_transarency = lambert->getTransparency();
	if (shader->m_transarency) {
		effect->m_transparency = ReadFloatOrParamType(effect, shader->m_transarency);
	}
	shader->m_index_of_refaction = lambert->getIndex_of_refraction();
	if (shader->m_index_of_refaction) {
		effect->m_refractiveIndex = ReadFloatOrParamType(effect, shader->m_index_of_refaction);
	}
}

CVoid ReadBlinn(CEffect * effect, CShaderElements * shader, domProfile_COMMON::domTechnique::domBlinn *blinn)
{
	shader->m_emission = blinn->getEmission();
	if (shader->m_emission ) {
		effect->m_emission = ReadColorOrTextureType(effect, shader->m_emission);
	}
	shader->m_ambient = blinn->getAmbient();
	if (shader->m_ambient ) {
		effect->m_ambient = ReadColorOrTextureType(effect, shader->m_ambient);
	}
	shader->m_diffuse = blinn->getDiffuse();
	if (shader->m_diffuse) {
		effect->m_diffuse = ReadColorOrTextureType(effect, shader->m_diffuse);
	}
	shader->m_specular = blinn->getSpecular();
	if (shader->m_specular) {
		effect->m_specular = ReadColorOrTextureType(effect, shader->m_specular);
	}
	shader->m_shininess = blinn->getShininess();
	if (shader->m_shininess) {
		effect->m_shininess = ReadFloatOrParamType(effect, shader->m_shininess);
	}
	shader->m_reflective = blinn->getReflective();
	if (shader->m_reflective) {
		effect->m_reflective = ReadColorOrTextureType(effect, shader->m_reflective);
	}
	shader->m_reflectivity = blinn->getReflectivity();
	if (shader->m_reflectivity) {
		effect->m_reflectivity = ReadFloatOrParamType(effect, shader->m_reflectivity);
	}
	shader->m_transparent = blinn->getTransparent();
	if (shader->m_transparent) {
		effect->m_transparent = ReadColorOrTextureType(effect, shader->m_transparent);
	}
	shader->m_transarency = blinn->getTransparency();
	if (shader->m_transarency) {
		effect->m_transparency = ReadFloatOrParamType(effect, shader->m_transarency);
	}
	shader->m_index_of_refaction = blinn->getIndex_of_refraction();
	if (shader->m_index_of_refaction) {
		effect->m_refractiveIndex = ReadFloatOrParamType(effect, shader->m_index_of_refaction);
	}
}

CBool CScene::ReadImageLibrary( domLibrary_imagesRef lib )
{
	//PrintInfo( _T("Reading Image Library...\n") );	
	for ( CUInt i = 0; i < lib->getImage_array().getCount(); i++)
	{
		ReadImage( lib->getImage_array()[i] ); 
	}
	return CTrue; 	 
}

CImage *CScene::ReadImage( domImageRef lib )
{
	if ( lib == NULL )
		return NULL;
	if ( lib->getId() == NULL )
		return NULL;

	domImage* imageElement = (domImage*)(domElement*)lib;
	imageElement->getInit_from()->getValue().validate();
	CChar * file = (char*)imageElement->getInit_from()->getValue().str().c_str();
	
	//CImage * image = GetImage(lib->getID(), lib->getDocumentURI()->getURI());
	CImage * image = GetImage(imageElement->getId() );
	if ( image )	// image is found
	{
		//PrintInfo( "This image has been loaded previously\n", COLOR_RED );
		return image;
	}

	//PrintInfo( "Add new image %s \n", lib->getId() );

	
	if ( imageElement )
	{
		CImage * newImage = CNew( CImage );
		//CAssert( "No memory\n", newImage != NULL );
		newImage->SetName( imageElement->getId() );
		newImage->SetDocURI( imageElement->getDocumentURI()->getURI() ); 
	//CChar * file = (char*)imageElement->getInit_from()->getValue().getFile();	Collada DOM 1.3		
		newImage->SetFileName( file );

		if ( newImage->LoadImageFile( (CChar *)m_fileName ) )
		{
			if ((CInt32) newImage->GetId() == -1) return NULL;
			//cfxSurface::addImage( newImage->GetName(), newImage->GetId() );
			// add the newImage to the runtime 
			m_images.push_back(newImage);
			g_images.push_back(newImage);
			return newImage;
		}
		else
		{
			CDelete( newImage ); 
			return NULL; 
		}
	}
	return NULL; 	
}

CImage* CScene::GetImage( const CChar * name )
{
	if ( name == NULL )
		return NULL;
	for (CUInt i = 0; i < g_images.size(); i++)
	{
		if (g_images[i]->GetName())
		{
			//if ( ICmp( g_images[i]->GetName(), name ) && ICmp( g_images[i]->GetDocURI(), DocURI ) )
			if (ICmp(GetAfterPath(g_images[i]->GetName()), name))
				return g_images[i];
		}
	}
	return NULL;
}

CBool CScene::ReadEffectLibrary( domLibrary_effectsRef lib )
{
	//PrintInfo( _T( "Reading Effect Library...\n") );	
	for ( CUInt i = 0; i < lib->getEffect_array().getCount(); i++)
	{
		ReadEffect( lib->getEffect_array()[i] ); 
	}
	return CTrue; 	
}


CEffect *CScene::ReadEffect( domEffectRef lib )
{
	if (lib->getId() == NULL) return NULL;
	CEffect* effect = GetEffect(lib->getID(), lib->getDocumentURI()->getURI());
	if (effect)	// effect is found
		return effect;
	//PrintInfo( "Adding new Effect: '" );  
	//PrintInfo( lib->getId(), COLOR_RED_BLUE );
	//PrintInfo( "'\n" ); 
	// Get a pointer to the effect element
	domEffect * EffectElement = (domEffect*)(domElement*)lib; 

	if ( EffectElement )
	{
		//for (CUInt i = 0; i < EffectElement->getImage_array().getCount(); i++ )
		//{
		//	ReadImage( EffectElement->getImage_array()[i] );
		//}
		// Make a CEffect to put this in and set the name
		CEffect * newEffect = CNew(CEffect);

		//CAssert("No memory\n", newEffect!=NULL);

		newEffect->SetName( EffectElement->getId());
		newEffect->SetDocURI( EffectElement->getDocumentURI()->getURI() ); 
		
		// How many profiles are there
		CUInt numProfiles = (CUInt) EffectElement->getFx_profile_abstract_array().getCount(); 

		// Scan the profiles to find the profile_COMMON
		for ( CUInt p = 0; p < numProfiles;  p++ )
		{
			CChar * typeName = (CChar *) EffectElement->getFx_profile_abstract_array()[p]->getTypeName(); 
			
			if ( Cmp("profile_COMMON", typeName ) )
			{
				// Found the common profile, get the technique from it as well
				domProfile_COMMON * common = (domProfile_COMMON *)(domFx_profile_abstract*)EffectElement->getFx_profile_abstract_array()[p]; 

				// Get all images in profile_COMMON
				//for (CUInt i = 0; i < common->getImage_array().getCount(); i++ )
				//{
				//	ReadImage( common->getImage_array()[i] );
				//}

				// Get all images in profile_COMMON
				domProfile_COMMON::domTechnique *technique = common->getTechnique(); 
				if ( technique == NULL )
					break; 

				//for (CUInt i = 0; i < technique->getImage_array().getCount(); i++ )
				//{
				//	ReadImage( technique->getImage_array()[i] );
				//}				

				// This support is really basic, since the shader models don't descend from a common type
				// we have to handle each one individually.  There can only be one in the technique.
				// All of them assume the texture is in the diffuse component for now.

				CShaderElements shader;
				domProfile_COMMON::domTechnique::domConstant *constant = technique->getConstant();
				if (constant)
					ReadConstant(newEffect, &shader, constant);
				domProfile_COMMON::domTechnique::domLambert *lambert = technique->getLambert();
				if (lambert)
					ReadLambert(newEffect, &shader, lambert);
				domProfile_COMMON::domTechnique::domPhong *phong = technique->getPhong();
				if (phong)
					ReadPhong(newEffect, &shader, phong);
				domProfile_COMMON::domTechnique::domBlinn *blinn = technique->getBlinn();
				if(blinn)
					ReadBlinn(newEffect, &shader, blinn);

				domCommon_newparam_type_Array newparam_array = common->getNewparam_array();
				std::map<string, domCommon_newparam_type*> NewParams;
				for (CUInt i = 0; i < newparam_array.getCount(); i++)
				{
					NewParams[newparam_array[i]->getSid()] = newparam_array[i];
				}
				
				//take only the texture from diffuse for now
				//CImage * image = NULL;
				//image = GetTextureFromShader(NewParams, shader.m_diffuse);
				//if (image)
				//{
				//	//PrintInfo( "Attaching image '" );PrintInfo( image->GetFileName(), COLOR_RED_BLUE );
				//	//PrintInfo( "' to this effect \n " ); 
				//	newEffect->m_textures.push_back(image);
				//}
				// Handle an effect with no texture
				m_effects.push_back(newEffect);
				//PrintInfo( "Effect added successfully\n", COLOR_WHITE );
				return newEffect; 	
			}
			else
			{
				CDelete( newEffect );
				//CChar tempChar[ MAX_NAME_SIZE ];
				//sprintf( tempChar, "Couldn't add the effect : %s . It's not supported\n", typeName );
				//PrintInfo( tempChar );
			}
		}
	}
	return NULL; 	
}

CEffect* CScene::GetEffect( const CChar* name, const CChar* DocURI)
{
	if ( name == NULL ) return NULL;
	for( CUInt i = 0; i < m_effects.size(); i++)
	{
		if ( ICmp( m_effects[i]->GetName(), name )  && ICmp( m_effects[i]->GetDocURI(), DocURI ) )
			return m_effects[i];
	}
	return NULL;
}

CAnimation* CScene::GetAnimation( const CChar* name, const CChar* DocURI)
{
	if ( name == NULL ) return NULL;
	for( CUInt i = 0; i < m_animations.size(); i++)
	{
		if ( ICmp( m_animations[i]->GetName(), name )  && ICmp( m_animations[i]->GetDocURI(), DocURI ) )
			return m_animations[i];
	}
	return NULL;
}

CBool CScene::ReadMaterialLibrary( domLibrary_materialsRef lib )
{
	//PrintInfo("Reading Material Library...\n" );	
	
	for ( CUInt i = 0; i < lib->getMaterial_array().getCount(); i++)
	{
		ReadMaterial( lib->getMaterial_array()[i] ); 
	}

	return CTrue; 	
};

CMaterial *CScene::ReadMaterial( domMaterialRef lib )
{
	if (lib->getId()==NULL) return NULL;
	CMaterial* material = GetMaterial(lib->getID(), lib->getDocumentURI()->getURI());
	if (material)	// material is found
		return material;
	//PrintInfo( "Adding new Material: ' " );  
	//PrintInfo( lib->getId(), COLOR_RED_BLUE );
	//PrintInfo( " '\n" );
	
	domMaterial * materialElement = (domMaterial*)(domElement*)lib; 

	if ( materialElement ) 
	{
		if ( !materialElement->getInstance_effect() )
			return NULL; 

		domElement * element = (domElement *) materialElement->getInstance_effect()->getUrl().getElement(); 
		if (element==NULL)
			return NULL;
		
		// find the effect that the material is refering too 
		CEffect* effect = ReadEffect((domEffect *) element);

		//CChar tempChar[MAX_NAME_SIZE];
		if (effect) 
		{
			CMaterial* newMat = CNew(CMaterial); 
			//CAssert("No memory\n", newMat!=NULL);
			newMat->SetName( materialElement->getId() ); 
			newMat->SetDocURI( materialElement->getDocumentURI()->getURI() ); 
			newMat->SetEffect( effect ); 
			//PrintInfo( "Attaching effect '" );PrintInfo( effect->GetName(), COLOR_RED_BLUE );
			//PrintInfo( "' to Material ' " );PrintInfo( newMat->GetName(),COLOR_RED_BLUE );PrintInfo( "\n" ); 
			m_materials.push_back(newMat);
			//PrintInfo( "Material added successfully\n", COLOR_WHITE );
			return newMat; 	
		}
		else
		{
			//sprintf( tempChar, "No effect ' %s ' for old-style matrial ' %s '\n", element->getID(), lib->getId() ); 
			//PrintInfo( tempChar, COLOR_RED );
			return NULL;
		}
	}
	return NULL; 	
};

CMaterial* CScene::GetMaterial( const CChar * name, const CChar * DocURI)
{
	if (name == NULL) return NULL;
	for(CUInt i = 0; i < m_materials.size(); i++)
	{
		if ( ICmp(m_materials[i]->GetName(), name ) && ICmp(m_materials[i]->GetDocURI(), DocURI ) )
			return m_materials[i];
	}
	return NULL;
}

CImage* CScene::GetTextureFromShader( std::map<string, domCommon_newparam_type*> &NewParams, domCommon_color_or_texture_type* shader)
{
	if (shader==NULL) return NULL;
	domCommon_color_or_texture_type::domTexture *textureElement = shader->getTexture();
	if (textureElement==NULL) return NULL;

	string sampler2D_SID = textureElement->getTexture();
	if (NewParams[sampler2D_SID]==0)
	{
		xsIDREF idref(sampler2D_SID.c_str());
		idref.setContainer(shader);
		idref.resolveElement();
		domImage* image_element = (domImage*)(domElement*)idref.getElement();
		return ReadImage(image_element);
	}
	string surface_SID = NewParams[sampler2D_SID]->getSampler2D()->getSource()->getValue();

	xsIDREF& idRef = NewParams[surface_SID]->getSurface()->getFx_surface_init_common()->getInit_from_array()[0]->getValue();
	idRef.resolveElement();
	domImage* image_element = (domImage*)(domElement*) idRef.getElement();
	return ReadImage(image_element);
}

CBool CScene::ReadAnimationLibrary(domLibrary_animationsRef lib, CBool loadTempAnimations)
{
	// See if we want to read animations or not
	if ( !m_loadAnimation )
		return CFalse; 

	//PrintInfo("Reading Animation Library...\n" );	
	if (loadTempAnimations)
		m_tempAnimations.clear();

	// Read in each animation in the library
	for ( CUInt i = 0; i < lib->getAnimation_array().getCount(); i++)
	{
		ReadAnimation(lib->getAnimation_array()[i], loadTempAnimations);

		domAnimationRef tempAnim = (domAnimation *)lib->getAnimation_array()[i];
		for (CUInt j = 0; j < tempAnim->getAnimation_array().getCount(); j++)
		{
			ReadAnimation((domAnimation *)tempAnim->getAnimation_array()[j], loadTempAnimations);
		}

	}
	return CTrue; 	
};

CBool CScene::ReadAnimationClipLibrary( domLibrary_animationClipsRef lib )
{
	// See if we want to read animations or not
	if ( !m_loadAnimation )
		return CFalse; 

	//PrintInfo("Reading Animation Clips...\n" );	

	// Read in each animation clip in the library
	for ( CUInt i = 0; i < lib->getAnimation_clip_array().getCount(); i++)
	{
		ReadAnimationClip( lib->getAnimation_clip_array()[i] );
	}
	return CTrue; 	
};

CVoid CScene::ReadAnimationClip( domAnimationClipRef animationClip )
{
	domAnimation_clip * animationClipElement = (domAnimation_clip*)(domElement*)animationClip; 
	if ( animationClipElement ) 
	{
		//PrintInfo( "Adding new animation clip: ' " );
		//if( animationClipElement->getId() ) PrintInfo( animationClipElement->getId(), COLOR_RED_BLUE );  
		//else PrintInfo( "" );
		//PrintInfo( " '\n" );
		CAnimationClip * newAnimClip = CNew(CAnimationClip); 
		//CAssert("No memory\n", newAnimClip!=NULL);
		if( animationClipElement->getId() ) newAnimClip->SetName( animationClipElement->getId() );
		newAnimClip->SetDocURI( animationClipElement->getDocumentURI()->getURI() ); 
		newAnimClip->SetStart( animationClipElement->getStart() );
		newAnimClip->SetEnd( animationClipElement->getEnd() );
		newAnimClip->SetIndex( m_numClips );
		for ( CUInt i = 0; i < animationClipElement->getInstance_animation_array().getCount(); i++)
		{
			if ( !animationClipElement->getInstance_animation_array()[i] )
				return; 

			domElement * element = (domElement *) animationClipElement->getInstance_animation_array()[i]->getUrl().getElement(); 
			if (element==NULL)
				return;

			// find the animation that the this instance is referring to 
			CAnimation* animation = ReadAnimation((domAnimation *) element);
			if( animation )
			{
				//PrintInfo( "Attaching animation ' ", COLOR_WHITE );PrintInfo( animation->GetName(), COLOR_RED_BLUE );
				//PrintInfo( " ' to the clip ' ", COLOR_WHITE  );PrintInfo(  animationClipElement->getId(), COLOR_RED_BLUE );
				//PrintInfo( " '\n"  , COLOR_WHITE  );

				animation->SetClipTarget( newAnimClip );

				newAnimClip->m_animations.push_back( animation );
			}
		}
		m_animationClips.push_back( newAnimClip );
		m_numClips += 1;
	}
}

CAnimation *CScene::ReadAnimation(domAnimationRef animation, CBool loadTempAnimations)
{
	if (animation == NULL) return NULL;
	CAnimation* m_animation = NULL;
	if (!Cmp(g_currentZipFileName, "\n"))
		m_animation = GetAnimation(animation->getID(), g_currentZipFileName);
	else
		m_animation = GetAnimation(animation->getID(), animation->getDocumentURI()->getURI());
	if (m_animation)	// animation is found
		return m_animation;

	if ( animation )
	{
		//PrintInfo( "Adding new Animation: ' " );
		//if( animation->getId() ) PrintInfo( animation->getId(), COLOR_RED_BLUE );  
		//else PrintInfo( "" );
		//PrintInfo( " '\n" );

		CAnimation * newAnim = CNew(CAnimation ); 
		//CAssert("No memory\n", newAnim!=NULL);
		// get the animation name - target - keys and time 
		if( animation->getId() ) newAnim->SetName( animation->getId() );
		if (!Cmp(g_currentZipFileName, "\n"))
			newAnim->SetDocURI(g_currentZipFileName);
		else
			newAnim->SetDocURI(animation->getDocumentURI()->getURI());

		// get the number of sources 
		domSource_Array & source_array = animation->getSource_array();
		for ( CUInt i = 0; i < source_array.getCount(); i++ )
		{
			CAnimSrc * source = ReadAnimationSource(source_array[i]);
			if (source) newAnim->m_sources[source->m_id] = source;
		}

		domSampler_Array & sampler_array = animation->getSampler_array();
		for (CUInt s=0; s<sampler_array.getCount(); s++)
		{
			CAnimSampler * anim_sampler = ReadAnimationSampler(newAnim, sampler_array[s]);
			if (anim_sampler) newAnim->m_samplers[sampler_array[s]->getID()] = anim_sampler;
		}

		domChannel_Array & channel_array = animation->getChannel_array();
		for (CUInt i=0; i<channel_array.getCount(); i++)
		{
			CAnimChannel * channel = ReadAnimationChannel(newAnim, channel_array[i]);
			newAnim->m_channels.push_back(channel);
			newAnim->ResolveChannel(channel->GetSampler(), channel->GetTarget());
		}

		if (channel_array.getCount() > 0) 
		{
			newAnim->GenerateKeys(); 
		}
		if (loadTempAnimations)
		{
			m_tempAnimations.push_back(newAnim);
		}
		m_animations.push_back(newAnim);
		
		// also get it's last key time and first key time 
		if( newAnim->GetEndTime() > m_lastKeyTime )
			m_lastKeyTime = newAnim->GetEndTime(); 

		return newAnim;
	}
	return NULL;
};

CAnimSrc *CScene::ReadAnimationSource( domSourceRef source )
{
	if (source==NULL) return NULL;
	CAnimSrc * newSource = new CAnimSrc();

	// Set the source name
	newSource->m_id =  source->getId();
	newSource->SetName( newSource->m_id.c_str() ); 
	newSource->SetDocURI( source->getDocumentURI()->getURI()); 
		
	// Copy over the CFloat array data if any 
	if (source->getFloat_array()) // for CFloat array
	{
		newSource->m_count = (CUInt) source->getFloat_array()->getCount();
		newSource->m_array.resize(newSource->m_count);

		daeDoubleArray& floatArray = source->getFloat_array()->getValue();
		
		// copy the array data 
		for ( CUInt a = 0; a < floatArray.getCount(); a++)
		{
			newSource->m_array[a] = (CFloat)floatArray[a];
		}	
	}
	else if (source->getName_array())
	{
		//PrintInfo( "Animation source : ' " );  
		//PrintInfo( newSource->m_id, COLOR_RED_BLUE );
		//PrintInfo( " ' is not supported\n" );
	}
	return newSource;
}

CAnimSampler *CScene::ReadAnimationSampler( CAnimation * animation, domSamplerRef sampler)
{
	if (sampler==NULL) return NULL;
	CAnimSampler * newSampler = new CAnimSampler();
	domInputLocal_Array & inputArray = sampler->getInput_array();
	for (CUInt i=0; i<inputArray.getCount(); i++)
	{
		domSource * source = (domSource*) (domElement*) inputArray[i]->getSource().getElement();
		newSampler->m_inputs[inputArray[i]->getSemantic()] = animation->m_sources[source->getID()];
	}
	return newSampler;
}

CAnimChannel *CScene::ReadAnimationChannel(CAnimation * animation, domChannelRef channel)
{
	if (channel==NULL) return NULL;
	CAnimChannel * newChannel = new CAnimChannel();
	domSampler * sampler = (domSampler*) (domElement*) channel->getSource().getElement();
	std::string target = channel->getTarget();
	newChannel->SetSampler(animation->m_samplers[sampler->getID()]);
	newChannel->SetTarget(target.c_str());
	CAnimSrc * inputSource = animation->m_sources[newChannel->m_sampler->m_inputs["INPUT"]->m_id];
	CAnimSrc * outputSource = animation->m_sources[newChannel->m_sampler->m_inputs["OUTPUT"]->m_id];
	newChannel->SetInputSrc(inputSource);
	newChannel->SetOutputSrc(outputSource);
	return newChannel;
}

CBool CScene::ReadScene( domVisual_sceneRef scene, CUpAxis up )
{
	// create the scene root 
	m_sceneRoot = CNew(CNode);
	m_sceneRoot->SetUpAxis(up);
	//CAssert("No memory\n", SceneRoot!=NULL);
	// get the scene name 
	//if ( scene->getName() ) 
	//{
		m_sceneRoot->SetName( "vanda_engine_scene_root"/*scene->getName()*/ ); 
	//}
	//CChar tempChar[MAX_NAME_SIZE];
	//sprintf( tempChar, "\nReading Collada Scene ' %s ' ...\n", scene->getName() );
	//PrintInfo(tempChar); 	

	// recurse through the scene, read and add nodes 
	for ( CUInt i = 0; i < scene->getNode_array().getCount(); i++)
	{
		CNode * node = ReadNode( scene->getNode_array()[i], m_sceneRoot );
		if (node)
		{
			m_nodes[node->GetId()] = node;
			m_allNodes.push_back(node);
		}
	}

	//see what geometries have animation
	for(std::map<std::string, CNode*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++ )
	{
		CBool foundTarget = CFalse;
		CNode* currentNode =  (*it).second;
		if( currentNode->GetNumAnimations() > 0 )
		{
			foundTarget = CTrue;
		}
		else
		{
			while ( currentNode->GetNodeParent() )
			{
				currentNode =  currentNode->GetNodeParent();
				if( currentNode->GetNumAnimations() > 0 )
				{
					foundTarget = CTrue;
					break;
				}
			}
		}
		currentNode =  (*it).second; //return back to the original node and change its properties

		if( foundTarget )
		{
			for(std::vector<CInstanceGeometry*>::iterator it2 = currentNode->m_instanceGeometries.begin(); it2 != currentNode->m_instanceGeometries.end(); it2++ )
			{
				CInstanceGeometry* currentInstanceGeometry = (*it2);
				currentInstanceGeometry->m_abstractGeometry->m_hasAnimation = CTrue;
			}
		}
		//instance controllers have animation.
		for(std::vector<CInstanceController*>::iterator it3 = currentNode->m_instanceControllers.begin(); it3 != currentNode->m_instanceControllers.end(); it3++ )
		{
			CInstanceController* currentInstanceController = (*it3);
			currentInstanceController->m_instanceGeometry->m_abstractGeometry->m_hasAnimation = CTrue;
		}
	}

	// for each skin controller find the nodes needed for skinning 
	//	CController * ctrls = m_controllers;
	for (CUInt i=0; i  < m_controllers.size(); i++)
	{
		m_controllers[i]->FindJointNodes( m_sceneRoot ); 			
	}
	return CTrue; 
}

CNode * CScene::ReadNode( domNodeRef node, CNode * parentNode )
{
	CNode * findnode = GetNode(node->getId());
	if (findnode) return findnode;

	//PrintInfo( "Reading Scene Node ' ");
	//PrintInfo( node->getId(), COLOR_RED_BLUE );
	//PrintInfo( " ' \n" );

	CNode * tempNode = CNew( CNode );
	// Create a new node and initialize it with name and parent pointer
	//CAssert("No memory\n", CNode!=NULL);
	if ( node->getName() ) tempNode->SetName( node->getName() ); 
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%s%d", "Vanda_Engine_Node_", g_nodeIndex );
		tempNode->SetName( temp ); 
		g_nodeIndex++;
	}
	if ( node->getId() ) tempNode->SetId( node->getId() ); 
	else
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "%s%d", "Vanda_Engine_Node_ID_", g_nodeIndex );
		tempNode->SetId( temp ); 
		g_nodeIndex++;
	}

	if ( node->getSid() ) tempNode->SetSid( node->getSid() ); 

	// see if this node is the target for any of the animations we have loaded 
	for(CUInt i=0; i<m_animations.size(); i++)
	{
		CAnimation * anim = m_animations[i];
		for( CUInt j = 0; j < anim->m_channels.size(); j++ )
		{
			if ( Cmp( tempNode->GetId(), anim->m_channels[j]->GetTarget() ) )
			{
				//PrintInfo( "Attaching animation ' ", COLOR_WHITE );PrintInfo( anim->GetName(), COLOR_RED_BLUE );
				//PrintInfo( " ' to the node ' ", COLOR_WHITE  );PrintInfo( tempNode->GetName(), COLOR_RED_BLUE );
				//PrintInfo( " '\n", COLOR_WHITE  );

				//anim->SetFoundTarget();
				tempNode->SetAnimation( anim );
				// don't want to break, though there maybe be multiple anim targets 
				m_numAnimatedNodes++;
			}
		}
	}
	tempNode->SetParent( parentNode ); 

	// future support method that will support any rot/trans/scale matrix combination 
	ReadNodeTransforms( tempNode, node );
 	// Process Instance Geometries
	for (CUInt i = 0; i < node->getInstance_geometry_array().getCount(); i++)
	{
		CInstanceGeometry * instanceGeometry = ReadInstanceGeometry(node->getInstance_geometry_array()[i]);
		if ( instanceGeometry == NULL ) continue;
		instanceGeometry->m_parent = tempNode;
		tempNode->m_instanceGeometries.push_back(instanceGeometry);
		instanceGeometry->m_node = tempNode;
		m_instanceGeometries.push_back( instanceGeometry );
		instanceGeometry->m_abstractGeometry->m_instanceGeometries.push_back(instanceGeometry);
		//PrintInfo( "Geometry added successfully\n", COLOR_WHITE );
	}

	// Process Instance Controllers 
	for (CUInt i = 0; i < node->getInstance_controller_array().getCount(); i++)
	{
		domInstance_controller *icontroller  = node->getInstance_controller_array()[i];
		CInstanceController * instanceController = ReadInstanceController(icontroller);
		if (instanceController==NULL) //if instance Controller can not be created, skip to the next one
			continue;

		instanceController->m_parent = tempNode;
		tempNode->m_instanceControllers.push_back(instanceController);
		instanceController->m_instanceGeometry->m_node = tempNode;
		instanceController->m_instanceGeometry->m_isController = CTrue;
		m_instanceGeometries.push_back( instanceController->m_instanceGeometry );
		instanceController->m_instanceGeometry->m_abstractGeometry->m_instanceControllers.push_back(instanceController);
		//PrintInfo( "Controller added successfully\n", COLOR_WHITE );
	}

	// Process Instance Lights 
	for (CUInt i = 0; i < node->getInstance_light_array().getCount(); i++)
	{
		CInstanceLight * instanceLight = ReadInstanceLight(node->getInstance_light_array()[i]);
		if (instanceLight)
		{
			instanceLight->m_parent = tempNode;
			instanceLight->SetIndex(); //selection
			tempNode->m_instanceLights.push_back(instanceLight);
			m_lightInstances.push_back(instanceLight);
			//PrintInfo( "Light added successfully\n", COLOR_WHITE );
		}
	}

	//Process Instance Cameras 
	for (CUInt i = 0; i < node->getInstance_camera_array().getCount(); i++)
	{	
		CInstanceCamera *instanceCamera = ReadInstanceCamera(node->getInstance_camera_array()[i]);
		if (instanceCamera)
		{
			CBool foundCamera = CFalse;
			//if camera name exists, skip
			for (CUInt j = 0; j < g_importedCameraInstances.size(); j++)
			{
				if (Cmp(instanceCamera->m_abstractCamera->GetName(), g_importedCameraInstances[j]->m_abstractCamera->GetName()))
				{
					foundCamera = CTrue;
					break;
				}
			}
			if (foundCamera)
				continue;

			instanceCamera->m_parent = tempNode;
			m_cameraInstances.push_back(instanceCamera);
			g_importedCameraInstances.push_back(instanceCamera);
			//g_render.SetActiveInstanceCamera( instanceCamera );
			//PrintInfo( "Camera added successfully\n", COLOR_WHITE );
		}
	}


	// add to parent 
	parentNode->AddChild( tempNode ); 
	// read children 
	for (CUInt i = 0; i < node->getNode_array().getCount(); i++)
	{
		// read in each child an recursively it's children 
		//PrintInfo( "   # Childern of node: ' "  );
		//PrintInfo( tempNode->GetId(), COLOR_RED_BLUE );
		//PrintInfo( " ' : " );
		CNode * readnode  = ReadNode( node->getNode_array()[i], tempNode );
		if (readnode)
		{
			m_nodes[readnode->GetId()] = readnode;
			m_allNodes.push_back(readnode);
		}
	}

	// read children <instance_nodes>, can be 0 or more 
	for (CUInt i = 0; i < node->getInstance_node_array().getCount(); i++)
	{
		// read in each child an recursively it's children 
		domInstance_node * instance_node = node->getInstance_node_array()[i];
		domNode * urlnode = (domNode*) (domElement*) instance_node->getUrl().getElement();
		if (urlnode) {
			CNode * readnode = ReadNode( urlnode, tempNode );
			if (readnode)
			{
				m_nodes[readnode->GetId()] = readnode;
				m_allNodes.push_back(readnode);
			}
		}
	}
	tempNode->SetScene( this );
	return tempNode; 
}

CBool CScene::ReadNodeTransforms( CNode * tempNode, domNodeRef node )
{
	// load the node transformations as they are to be able to 
	// handle any matrix stack configurations independant of the tools 
	for ( CUInt i = 0; i < node->getContents().getCount(); i++)
	{
		for( CInt j = 0; j <=  m_numClips + 2; j++ )
		{
			tempNode->m_transforms.resize(m_numClips + 3);

			// get the component type string
			CTransform * transform = NULL;
			CChar * sid = NULL;
			CChar * typeName = (CChar *)node->getContents()[i]->getTypeName(); 
			CTFormType type = CTransform::GetType( typeName ); 
			// set the type of the transform and switch on it 
			switch( type )
			{
			case eCRotate:
			{
				// need to create the transforms to store the node transform stack 
				transform = CNew( CTransform );
				//CAssert("No Free memory\n", transform!=NULL);
				transform->SetSid( "" ); 
				transform->SetType( type ); 
				// load rotation
				domRotateRef rotateArray = (domRotate * )(domElement * )node->getContents()[i];

				//assert( rotateArray->getValue().getCount() == 4 ); 
				// get the rotation data 
				CVec4f rot;
				rot.x = (CFloat)rotateArray->getValue()[0];
				rot.y = (CFloat)rotateArray->getValue()[1];
				rot.z = (CFloat)rotateArray->getValue()[2];
				rot.w = (CFloat)rotateArray->getValue()[3];
				
				transform->SetRotate( rot );

				// this will be used to bind to an animation later 
				sid = (CChar *)(rotateArray->getSid());
				if ( sid )
					transform->SetSid( sid );

				if( j ==  m_numClips + 1 )
				{
					tempNode->m_sumTransforms.push_back( transform );
					tempNode->m_sumWeights.push_back( 1.0f );
				}
				else
				{
					tempNode->m_transforms[j].push_back(transform);
				}

			}
				break;
			case eCTranslate:
			{
				// need to create the Ctransforms to store the node transform stack 
				transform = CNew( CTransform );
				//CAssert("No Free memory\n", transform!=NULL);
				transform->SetSid( ""); 
				transform->SetType( type ); 
				// load rotation
				domTranslateRef translateArray = (domTranslate * )(domElement * )node->getContents()[i];
				assert( translateArray->getValue().getCount() == 3 ); 
				
				// get the transation data 
				CVec4f trans;
				trans.x = (CFloat)translateArray->getValue()[0];
				trans.y = (CFloat)translateArray->getValue()[1];
				trans.z = (CFloat)translateArray->getValue()[2];			

				transform->SetTranslate( trans ); 
				// this will be used to bind to an animation later 
				sid = (CChar *)translateArray->getSid();
				if ( sid )
					transform->SetSid( sid ); 

				if( j ==  m_numClips + 1 )
				{
					tempNode->m_sumTransforms.push_back( transform );
					tempNode->m_sumWeights.push_back( 1.0f );
				}
				else
				{
					tempNode->m_transforms[j].push_back(transform);
				}
				
			}
				break;
			case eCScale:
			{
				// need to create the Ctransforms to store the node transform stack 
				transform = CNew( CTransform );
				//CAssert("No Free memory\n", transform!=NULL);
				transform->SetSid( ""); 
				transform->SetType( type ); 
				// load scale 
				domScaleRef scaleArray = (domScale * )(domElement * )node->getContents()[i];
				assert( scaleArray->getValue().getCount() == 3 ); 
				
				// get the rotation data 
				CVec4f scale;
				scale.x = (CFloat)scaleArray->getValue()[0];
				scale.y = (CFloat)scaleArray->getValue()[1];
				scale.z = (CFloat)scaleArray->getValue()[2];
					
				transform->SetScale( scale ); 
				
				// this will be used to bind to an animation later 
				sid = (CChar *)scaleArray->getSid();
				if ( sid )
					transform->SetSid( sid );
		
				if( j ==  m_numClips + 1 )
				{
					tempNode->m_sumTransforms.push_back( transform );
					tempNode->m_sumWeights.push_back( 1.0f );
				}
				else
				{
					tempNode->m_transforms[j].push_back(transform);
				}

			}
				break;

			case eCLookAt:
			{
				// need to create the Ctransforms to store the node transform stack 
				transform = CNew( CTransform );
				//CAssert("No Free memory\n", transform!=NULL);
				transform->SetSid( ""); 
				transform->SetType( type ); 
				// load rotation
				domLookatRef lookatArray = (domLookat * )(domElement * )node->getContents()[i];
		
				assert( lookatArray->getValue().getCount() == 9); 
				// get the lkatation data 
				CVec3f lkat[3];
				lkat[0].x = (CFloat)lookatArray->getValue()[0];
				lkat[0].y = (CFloat)lookatArray->getValue()[1];
				lkat[0].z = (CFloat)lookatArray->getValue()[2];

				lkat[1].x = (CFloat)lookatArray->getValue()[3];
				lkat[1].y = (CFloat)lookatArray->getValue()[4];
				lkat[1].z = (CFloat)lookatArray->getValue()[5];

				lkat[2].x = (CFloat)lookatArray->getValue()[6];
				lkat[2].y = (CFloat)lookatArray->getValue()[7];
				lkat[2].z = (CFloat)lookatArray->getValue()[8];
				transform->SetLookAt(lkat); 
							
				sid = (CChar *)lookatArray->getSid();
				if ( sid )
					transform->SetSid( sid ); 

				if( j ==  m_numClips + 1 )
				{
					tempNode->m_sumTransforms.push_back( transform );
					tempNode->m_sumWeights.push_back( 1.0f );
				}
				else
				{
					tempNode->m_transforms[j].push_back(transform);
				}

			}
				break; 
			case eCMatrix:
			{
				// need to create the Ctransforms to store the node transform stack 
				transform = CNew( CTransform );
				//CAssert("No Free memory\n", transform!=NULL);
				transform->SetSid( ""); 
				transform->SetType( type ); 
				// beware, RT is row major, collada spec is column major
				domMatrixRef matrixArray = (domMatrix * )(domElement * )node->getContents()[i];
				CVec4f mat[4];
				mat[0].x = (CFloat) matrixArray->getValue()[0];
				mat[1].x = (CFloat) matrixArray->getValue()[1];
				mat[2].x = (CFloat) matrixArray->getValue()[2];
				mat[3].x = (CFloat) matrixArray->getValue()[3];

				mat[0].y = (CFloat) matrixArray->getValue()[4];
				mat[1].y = (CFloat) matrixArray->getValue()[5];
				mat[2].y = (CFloat) matrixArray->getValue()[6];
				mat[3].y = (CFloat) matrixArray->getValue()[7];

				mat[0].z = (CFloat) matrixArray->getValue()[8];
				mat[1].z = (CFloat) matrixArray->getValue()[9];
				mat[2].z = (CFloat) matrixArray->getValue()[10];
				mat[3].z = (CFloat) matrixArray->getValue()[11];

				mat[0].w = (CFloat) matrixArray->getValue()[12];
				mat[1].w = (CFloat) matrixArray->getValue()[13];
				mat[2].w = (CFloat) matrixArray->getValue()[14];
				mat[3].w = (CFloat) matrixArray->getValue()[15];
				transform->SetMatrix(mat);
				sid = (CChar *)matrixArray->getSid();
				if ( sid )
					transform->SetSid( sid ); 

				if( j ==  m_numClips + 1 )
				{
					tempNode->m_sumTransforms.push_back( transform );
					tempNode->m_sumWeights.push_back( 1.0f );
				}
				else
				{
					tempNode->m_transforms[j].push_back(transform);
				}

			}
				break;
			case eCSkew:
				//PrintInfo("Skew transforms isn't supported\n");
				continue;
			case eCTFormUnknown:
				// If it's not a transform, it's an instance or something else that will be handled later.
				continue; 
			}

			for (CUInt i=0; i<m_animations.size(); i++)
			{
				CAnimation * anim = m_animations[i];
				//if (anim->HasFoundTarget())
				//	continue;
				//CBool foundTarget = CFalse;
				for (CUInt j=0; j<anim->m_channels.size(); j++)
				{
					if ( sid && ICmp(anim->m_channels[j]->GetTarget(), tempNode->GetId()) && //Some transformations have no Sid
						ICmp(anim->m_channels[j]->GetTargetElementString(), sid) )
					{
						//anim->SetFoundTarget(); 
						transform->SetAnimation(anim); 
						transform->AddChannelId(j);
						//foundTarget = CTrue;
						//break;
					}
				}
				//if (foundTarget)
				//	break;
			}
		}
	}	
	return CTrue; 
}




CNode * CScene::GetNode( const CChar * name )
{
	if (name == NULL) return NULL;
	if (m_nodes.empty()) return NULL;
	return m_nodes[name];
}

CInstanceMaterial *CScene::ReadInstanceMaterial( domInstance_materialRef lib)
{
	// Make a new CInstanceMaterial and add it to the list in newInstanceGeometry
	CInstanceMaterial *newInstanceMaterial = CNew(CInstanceMaterial);
	//CAssert("No memory\n", newCInstanceMaterial!=NULL);
	newInstanceMaterial->m_symbol = lib->getSymbol();
	newInstanceMaterial->m_target = lib->getTarget().getID();

	// resolve bind target for fx materials
	//std::map<std::string, cfxMaterial*>::iterator iter;
	//for(iter = m_cfxMaterials.begin(); iter != m_cfxMaterials.end(); iter++)
	//{
	//	std::string id = (*iter).first;
	//	if (id==newInstanceMaterial->m_target)
	//	{
	//		newInstanceMaterial->m_targetcfxMaterial = (*iter).second;
	//		break;
	//	}
	//}

	//if (newInstanceMaterial->m_targetcfxMaterial==NULL)
	//{   // can't resolve fx materials, try common materials
		domElement * element = lib->getTarget().getElement();
		if (element)
		{
			CMaterial * material = ReadMaterial((domMaterial *) element);
			if (material) // material added or found
			{
				newInstanceMaterial->m_targetMaterial = material;				
			} else
			{
				//CChar temp[ MAX_NAME_SIZE ];
				//sprintf( "CScene::ReadInstanceMaterial : Couldn't find instance Materials for binding: %s\n",newInstanceMaterial->m_target.c_str() );
				//PrintInfo( temp, COLOR_RED );
			}
		}
	//}

	return newInstanceMaterial;
}

CInstanceGeometry *CScene::ReadInstanceGeometry( domInstance_geometryRef lib)
{
	// Find the <geometry> the <instance_geometry> is pointing at (there can be only one)
	// by searching the Geometries list in the scene.
	xsAnyURI & urltype  = lib->getUrl();
	urltype.resolveElement();
	domElement * element = (domElement* ) urltype.getElement();
	if (element==NULL) // this instance geometry is not found skip to the next one
		return NULL;

	CGeometry * geo = ReadGeometry((domGeometry* ) element);
	if (geo==NULL)			// couldn't find from existing pool of geometries
		return NULL;

	CInstanceGeometry *newInstanceGeometry = CNew(CInstanceGeometry);
	//CAssert("No memory\n", newCInstanceGeometry!=NULL);
	newInstanceGeometry->m_abstractGeometry = geo;
	newInstanceGeometry->m_nameIndex = g_nameIndex++; // To specify the name index in selection mode

	domBind_material *bindMaterial =  lib->getBind_material();
	if(bindMaterial)
	{
		// Get the <technique_common>
		domBind_material::domTechnique_common *techniqueCommon = bindMaterial->getTechnique_common();
		if(techniqueCommon)
		{
			// Get the <instance_material>s
			domInstance_material_Array &instanceMaterialArray = techniqueCommon->getInstance_material_array();
			for(CUInt j = 0; j < instanceMaterialArray.getCount(); j++)
			{
				CInstanceMaterial * newiMaterial = ReadInstanceMaterial(instanceMaterialArray[j]);
				newInstanceGeometry->m_materialInstances.push_back(newiMaterial);
			}
		}
	}
 	return newInstanceGeometry;
}

CGeometry *CScene::GetGeometry( const CChar * name, const CChar * DocURI)
{
	if (name == NULL) return NULL;
	for(CUInt i=0; i<m_geometries.size(); i++)
	{
		if ( ICmp(m_geometries[i]->GetName(), name )  &&
			 ICmp(m_geometries[i]->GetDocURI(), DocURI ) )
			return m_geometries[i];
	}
	return NULL;
}

CGeometry *CScene::ReadGeometry( domGeometryRef lib , CController * controller)
{
	if (lib->getId()==NULL) return NULL;
	CGeometry* geometry = NULL;

	CChar DocURI[MAX_URI_SIZE];
	Cpy(DocURI, g_currentPrefabAndSceneName);

	if (!controller)
		geometry = GetGeometryFromScenes(lib->getID(), DocURI);
	else
		geometry = GetGeometry(lib->getID(), DocURI);

	if (geometry)	// geometry is found
		return geometry;

	//CChar tempChar[ MAX_NAME_SIZE];
	//PrintInfo( "Adding new Geometry ' " );
	//PrintInfo( lib->getId(), COLOR_RED_BLUE );
	//PrintInfo( " '\n" );

	// See what kind of data is in the geometry (there can be only one)
	domAsset *assetElement = lib->getAsset();
	domMesh	*meshElement = lib->getMesh();
	domConvex_mesh *convexMeshElement = lib->getConvex_mesh();
	domExtra_Array &extraElement = lib->getExtra_array();
	domSpline *splineElement = lib->getSpline();
	domMesh *mesh = lib->getMesh();
	//we only support meshes
	if(assetElement)
	{
		//sprintf( tempChar, "CScene::ReadGeometry: Item %s has an <asset> which engine doesn't supports it\n", lib->getId() );
		//PrintInfo( tempChar, COLOR_RED );
		return NULL;
	}
	else if (convexMeshElement)
	{
		//sprintf( tempChar, "CScene::ReadGeometry: Item %s has an <convex_mesh> which engine doesn't support supports it\n", lib->getId() );
		//PrintInfo( tempChar, COLOR_RED );
		return NULL;
	}
	else if (extraElement.getCount())
	{
		//sprintf( tempChar, "CScene::ReadGeometry: Item %s has an <extra> which engine doesn't supports it\n", lib->getId() );
		//PrintInfo( tempChar, COLOR_RED );
	}
	else if (splineElement)
	{
		//sprintf( tempChar, "CScene::ReadGeometry: Item %s has an <spline> which engine doesn't supports it\n", lib->getId() );
		//PrintInfo( tempChar, COLOR_RED );
	}

	if( mesh )
	{
		// Allocate space for the new geometry object 
		CGeometry * newGeo   = CNew(CGeometry);
		//CAssert("No memory\n", newGeo!=NULL);
		newGeo->SetName( lib->getId() );
		newGeo->SetDocURI(DocURI);
		newGeo->m_upAxis = upAxis;

		//not sure if we should get primitives by groups or by whatever comes first, I think it shouldn't matter, let's confirm later.
		//CUInt numPolylistGroups = (CUInt)meshElement->getPolylist_array().getCount();
		//for (CUInt i=0; i< numPolylistGroups; i++)
		//{
		//	CPolyGroup *newprimitives = BuildPolygons(meshElement->getPolylist_array()[i], newGeo);
		//	newGeo->Groups.push_back(newprimitives);
		//}

		//CUInt numPolygonGroups = (CUInt)meshElement->getPolygons_array().getCount();
		//for (CUInt i=0; i< numPolygonGroups; i++)
		//{
		//	CPolyGroup *newprimitives = BuildPolygons(meshElement->getPolygons_array()[i], newGeo);
		//	newGeo->Groups.push_back(newprimitives);
		//}

		//CUInt numTriStripsGroups = (CUInt)meshElement->getTristrips_array().getCount();
		//for (CUInt i=0; i< numTriStripsGroups ; i++)
		//{
		//	CPolyGroup *newprimitives = BuildTriStrips(meshElement->getTristrips_array()[i], newGeo);
		//	newGeo->Groups.push_back(newprimitives);
		//}

		//CUInt numLinesGroups = (CUInt)meshElement->getLines_array().getCount();
		//for (CUInt i=0; i< numLinesGroups ; i++)
		//{
		//	CPolyGroup *newprimitives = BuildLines(meshElement->getLines_array()[i], newGeo);
		//	newGeo->Groups.push_back(newprimitives);
		//}

		//CUInt numLineStripsGroups = (CUInt)meshElement->getLinestrips_array().getCount();
		//for (CUInt i=0; i< numLineStripsGroups ; i++)
		//{
		//	CPolyGroup *newprimitives = BuildLineStrips(meshElement->getLinestrips_array()[i], newGeo);
		//	newGeo->Groups.push_back(newprimitives);
		//}

		//we use triangulate option in openCollada exporter, so we just use this option
		if( controller )
			newGeo->m_skinIndex = CNewData( CUInt, newGeo->m_vertexcountmax);
		CUInt numTriangleGroups = (CUInt)meshElement->getTriangles_array().getCount();
		for (CUInt i=0; i< numTriangleGroups; i++)
		{
			CPolyGroup *newprimitives = BuildTriangles(meshElement->getTriangles_array()[i], newGeo, controller, i );
			newGeo->m_groups.push_back(newprimitives);
		}
		//Generate tangent vectors
		CalculateTangentArray(newGeo);
		//// set controller, we shouldn't need to set controller from geometry, only geometry to controller
		//// it is setting it two ways now, we will fix this later.
		if (controller)
		{
			newGeo->SetController(controller);
			controller->m_geometry = newGeo;
			newGeo->m_weights = CNewData( CWeight, newGeo->m_vertexcount );
			for (CUInt p=0; p< newGeo->m_vertexcount; p++)
			{
				newGeo->m_weights[p].Copy( &controller->m_weights[newGeo->m_skinIndex[p]] );
				if ( newGeo->m_skinData )
				{
					CMatrix temp;
					CMatrixLoadIdentity(temp);
					CMatrixTranspose( newGeo->m_skinData->m_bindShapeMats, temp );
					if (newGeo->m_skinData->m_bindShapeMats)
					{
						CVec3f normal, point;
						normal = newGeo->m_normals[p];
						point = newGeo->m_points[p];
						CMatrix3x4TransformSkin( temp, point, newGeo->m_points[p] );
						CMatrix3x4RotateSkin( temp, normal, newGeo->m_normals[p] );
					}
				}

			}
		}

		if (g_render.UsingVBOs() )
		{
			for (CUInt i=0; i<newGeo->m_groups.size() ; i++)
				newGeo->m_groups[i]->SetVBOs();

			newGeo->m_VBOIDs[eGeoPoints] = g_render.GenerateVBO();
			g_render.CopyVBOData(GL_ARRAY_BUFFER, newGeo->m_VBOIDs[eGeoPoints],newGeo->m_points, newGeo->m_vertexcount*3*sizeof(CFloat));

			newGeo->m_VBOIDs[eGeoNormals] = g_render.GenerateVBO();
			g_render.CopyVBOData(GL_ARRAY_BUFFER, newGeo->m_VBOIDs[eGeoNormals],newGeo->m_normals, newGeo->m_vertexcount*3*sizeof(CFloat));

			for( int i = 0; i < MAX_TEX_COORDS; i++ )
			{
				if( newGeo->m_texCoords[i] )
				{
					newGeo->m_VBOIDs[eGeoTexCoord0 + i ] = g_render.GenerateVBO();
					g_render.CopyVBOData(GL_ARRAY_BUFFER, newGeo->m_VBOIDs[eGeoTexCoord0 + i ],newGeo->m_texCoords[i], newGeo->m_vertexcount*2*sizeof(CFloat));
				}
			}

			if( newGeo->m_tangents )
			{
				newGeo->m_VBOIDs[eGeoTangents] = g_render.GenerateVBO();
				g_render.CopyVBOData(GL_ARRAY_BUFFER, newGeo->m_VBOIDs[eGeoTangents],newGeo->m_tangents, newGeo->m_vertexcount*3*sizeof(CFloat));
			}
			if( newGeo->m_bNormals )
			{

				newGeo->m_VBOIDs[eGeoBiNormals] = g_render.GenerateVBO();
				g_render.CopyVBOData(GL_ARRAY_BUFFER, newGeo->m_VBOIDs[eGeoBiNormals],newGeo->m_bNormals, newGeo->m_vertexcount*3*sizeof(CFloat));
			}
		}
		newGeo->ComputeAABB_Center(); //compute the bounding box
		newGeo->m_nameIndex = g_nameIndex++; // To specify the name index in selection mode
		m_geometries.push_back(newGeo);
		g_geometries.push_back(newGeo);
		return newGeo; 	
	}
	return NULL;
};

class COffsets
{
public:
	COffsets(domInputLocalOffset_Array & inputs)
	{
		max_offset = 0;
		position_offset = -1;
		normal_offset = -1;

		tangent_offset = -1;
		binormal_offset = -1;
		position_floats = NULL;
		normal_floats = NULL;
		tangent_floats = NULL;
		binormal_floats = NULL;

		for ( int i = 0; i < MAX_TEX_COORDS; i++ )
		{
			texture_floats[i] = NULL;
			texture_offset[i] = -1;
			texture_stride[i] = 2; // By default: S and T
		}

		SetInputs(inputs);
	};
	~COffsets(){};
	CInt max_offset;

	CInt position_offset;
	CInt normal_offset;
	CInt texture_offset[MAX_TEX_COORDS]; // currently 8 textures are supported
	CInt texture_stride[MAX_TEX_COORDS];
	CInt tangent_offset;
	CInt binormal_offset;

	domListOfFloats * position_floats;
	domListOfFloats * normal_floats;
	domListOfFloats * texture_floats[MAX_TEX_COORDS];
	domListOfFloats * tangent_floats; // It's used for normal and parallax mapping
	domListOfFloats * binormal_floats; // It's used for normal and parallax mapping

private:
	CVoid SetInputs(domInputLocalOffset_Array & inputs)
	{
		CInt texture_count = -1;
		CInt tangent_count = -1;
		CInt biNormal_count = -1;
		// inputs with offsets
		for(CUInt i=0; i<inputs.getCount(); i++)
		{
			CInt thisoffset  = (CUInt) inputs[i]->getOffset();
			if (max_offset < thisoffset) max_offset++;

			domSource * source = (domSource*) (domElement*) inputs[i]->getSource().getElement();
			if(Cmp("VERTEX", inputs[i]->getSemantic())) {
				position_offset = thisoffset;
			} else if(Cmp("NORMAL", inputs[i]->getSemantic())) {
				normal_offset = thisoffset;
				normal_floats = & source->getFloat_array()->getValue();
			} else if(Cmp("TEXCOORD", inputs[i]->getSemantic())) {
				texture_count++;
				texture_offset[texture_count] = thisoffset;
				texture_floats[texture_count] = & source->getFloat_array()->getValue();
				texture_stride[texture_count] = source->getTechnique_common()->getAccessor()->getStride();
			} else if(Cmp( "TEXTANGENT", inputs[i]->getSemantic())) { 
				tangent_count++;
				if( tangent_count < 1 )
				{
					tangent_offset = thisoffset;
					tangent_floats = & source->getFloat_array()->getValue();
				}
			} else if(Cmp( "TEXBINORMAL", inputs[i]->getSemantic())) { 
				biNormal_count++;
				if( biNormal_count < 1 )
				{
					binormal_offset = thisoffset;
					binormal_floats = & source->getFloat_array()->getValue();
				}
			}
		}
		max_offset++;

		// inputs without offsets in vertices
		domMesh * mesh = (domMesh*) inputs[0]->getParentElement()->getParentElement();
		domVertices * vertices = mesh->getVertices();
		domInputLocal_Array& vertices_inputs = vertices->getInput_array();
		for(CUInt i=0; i<vertices_inputs.getCount(); i++)
		{
			domSource * source = (domSource*) (domElement*) vertices_inputs[i]->getSource().getElement();
			if(Cmp("POSITION", vertices_inputs[i]->getSemantic())) {
				position_floats = & source->getFloat_array()->getValue();
			} else if(Cmp("NORMAL", vertices_inputs[i]->getSemantic())) {
				normal_floats = & source->getFloat_array()->getValue();
				normal_offset = position_offset;
			} else if(Cmp("TEXCOORD", vertices_inputs[i]->getSemantic())) {
				texture_count++;
				texture_offset[texture_count] = position_offset;
				texture_floats[texture_count] = & source->getFloat_array()->getValue();
				texture_stride[texture_count] = source->getTechnique_common()->getAccessor()->getStride();
			} else if(Cmp( "TEXTANGENT", inputs[i]->getSemantic())) { 
				tangent_count++;
				if( tangent_count < 1 )
				{
					tangent_floats = & source->getFloat_array()->getValue();
					tangent_offset = position_offset;
				}
			} else if(Cmp( "TEXBINORMAL", inputs[i]->getSemantic())) { 
				biNormal_count++;
				if( biNormal_count < 1 )
				{
					binormal_floats = & source->getFloat_array()->getValue();
					binormal_offset = position_offset;
				}
			}
		}
	}
};

template <class T>
CVoid GrowData(T **old_data, CUInt count, CUInt max)
{
	T * new_data = new T[max];
	memcpy(new_data, *old_data, sizeof(T) * count);
	delete [] *old_data; 
	*old_data = new_data;
}
CInt GrowVertexData( COffsets offsets, CGeometry * geometry, CUInt size, CController* controller )
{
	CUInt memory_need = geometry->m_vertexcount + size;
	if (memory_need < geometry->m_vertexcountmax) return 0;
	geometry->m_vertexcountmax = memory_need/*geometry->m_vertexcountmax * ((memory_need / geometry->m_vertexcountmax) + 1)*/;
	GrowData(&(geometry->m_points), geometry->m_vertexcount, geometry->m_vertexcountmax);

	if( offsets.normal_offset != -1 )
		GrowData(&(geometry->m_normals), geometry->m_vertexcount, geometry->m_vertexcountmax);

	for( CInt i = 0; i < MAX_TEX_COORDS; i++ )
		if( offsets.texture_offset[i] != -1 )
			GrowData(&(geometry->m_texCoords[i]), geometry->m_vertexcount, geometry->m_vertexcountmax);

	if( offsets.tangent_offset != -1 )
		GrowData(&(geometry->m_tangents), geometry->m_vertexcount, geometry->m_vertexcountmax);
	if( offsets.binormal_offset != -1 )
		GrowData(&(geometry->m_bNormals), geometry->m_vertexcount, geometry->m_vertexcountmax);
	if( controller )
		GrowData(&(geometry->m_skinIndex), geometry->m_vertexcount, geometry->m_vertexcountmax);
	return 0;
}

CInt SetVertexData(COffsets& offset, CGeometry * geometry, domListOfUInts &values, CUInt i, CController* controller )
{
	domUint index;
	index = values[i*offset.max_offset + offset.position_offset];
	if( controller )
		geometry->m_skinIndex[geometry->m_vertexcount] = (CUInt) index;

	geometry->m_points[geometry->m_vertexcount].x = (CFloat) (*offset.position_floats)[(size_t)index*3+0];
	geometry->m_points[geometry->m_vertexcount].y = (CFloat) (*offset.position_floats)[(size_t)index*3+1];
	geometry->m_points[geometry->m_vertexcount].z = (CFloat) (*offset.position_floats)[(size_t)index*3+2];

	if (offset.normal_offset != -1)
	{
		index = values[i*offset.max_offset + offset.normal_offset];
		geometry->m_normals[geometry->m_vertexcount].x = (CFloat) (*offset.normal_floats)[(size_t)index*3+0];
		geometry->m_normals[geometry->m_vertexcount].y = (CFloat) (*offset.normal_floats)[(size_t)index*3+1];
		geometry->m_normals[geometry->m_vertexcount].z = (CFloat) (*offset.normal_floats)[(size_t)index*3+2];
	}

	for( CInt j = 0; j < MAX_TEX_COORDS; j++ )
	{
		if( offset.texture_offset[j] != -1 )
		{
			index = values[i*offset.max_offset + offset.texture_offset[j]];
			geometry->m_texCoords[j][geometry->m_vertexcount].x = (CFloat) (*offset.texture_floats[j])[(size_t)index*offset.texture_stride[j]+0];
			geometry->m_texCoords[j][geometry->m_vertexcount].y = (CFloat) (*offset.texture_floats[j])[(size_t)index*offset.texture_stride[j]+1];
		}
	}

	if (offset.tangent_offset != -1)
	{
		index = values[i*offset.max_offset + offset.tangent_offset];
		geometry->m_tangents[geometry->m_vertexcount].x = (CFloat) (*offset.tangent_floats)[(size_t)index*3+0];
		geometry->m_tangents[geometry->m_vertexcount].y = (CFloat) (*offset.tangent_floats)[(size_t)index*3+1];
		geometry->m_tangents[geometry->m_vertexcount].z = (CFloat) (*offset.tangent_floats)[(size_t)index*3+2];
	}

	if (offset.binormal_offset != -1)
	{
		index = values[i*offset.max_offset + offset.binormal_offset];
		geometry->m_bNormals[geometry->m_vertexcount].x = (CFloat) (*offset.binormal_floats)[(size_t)index*3+0];
		geometry->m_bNormals[geometry->m_vertexcount].y = (CFloat) (*offset.binormal_floats)[(size_t)index*3+1];
		geometry->m_bNormals[geometry->m_vertexcount].z = (CFloat) (*offset.binormal_floats)[(size_t)index*3+2];
	}
	geometry->m_vertexcount++;
	return geometry->m_vertexcount-1;
}

CTriangles * CScene::BuildTriangles(domTriangles * dom_triangles, CGeometry * geometry, CController* controller, CUInt i )
{
	CTriangles * triangles = CNew(CTriangles);
	//CUInt vertexCount = geometry->m_vertexcount;
	// prepare data
	triangles->m_geometry = geometry;

	domInputLocalOffset_Array & inputs = dom_triangles->getInput_array();
	COffsets offsets(inputs);

	if( i == 0 )
	{
		//allocate memory for all the UV set
		for( CInt j = 0; j < MAX_TEX_COORDS; j++ )
			if( offsets.texture_offset[j] != -1 )
				geometry->m_texCoords[j] = CNewData( CVec2f, geometry->m_vertexcountmax );

		if( offsets.binormal_offset != -1 )
			geometry->m_bNormals = CNewData( CVec3f, geometry->m_vertexcountmax );
		if( offsets.tangent_offset != -1 )
			geometry->m_tangents = CNewData( CVec3f, geometry->m_vertexcountmax );
		// triangles count
	}//if i == 0

	triangles->m_count = (CUInt) dom_triangles->getCount();

	GrowVertexData( offsets, geometry, triangles->m_count * 3, controller );
	// resolve Material	
	daeString str_material = dom_triangles->getMaterial();
	if (str_material)
		Cpy(triangles->m_materialName, str_material);
	
	
	// set index, they all have the same index since we process deindexer conditioner
	domListOfUInts P = dom_triangles->getP()->getValue();
	triangles->m_indexes = CNewData(CUInt, triangles->m_count * 3);
	for (CUInt ivertex=0; ivertex< triangles->m_count * 3; ivertex++)
	{
		triangles->m_indexes[ivertex] = SetVertexData(offsets, geometry, P, ivertex, controller );
	}

	//DeindexMesh( vertexCount, geometry, triangles );


	return triangles;

}

CInstanceLight *CScene::ReadInstanceLight( domInstance_lightRef lib)
{
	xsAnyURI & urltype  = lib->getUrl();
	domElement * element = (domElement* ) urltype.getElement();
	if (element==NULL) // this instance light is not found skip to the next one
	{
		//CChar tempChar[ MAX_NAME_SIZE ];
		//sprintf("Can't find the light ' %s '\n", urltype.getURI() );
		//PrintInfo( tempChar );
		return NULL;
	}

	CLight * light = ReadLight((domLight *) element);
	if (light)
	{
		CInstanceLight *instanceLight = CNew(CInstanceLight);
		//CAssert("No memory\n", instanceLight!=NULL);
		instanceLight->m_abstractLight = light;
		return instanceLight;
	}
	return NULL;
}

CLight *CScene::ReadLight( domLightRef lib )
{
	if (lib->getId()==NULL) return NULL;
	CLight * light = GetLight(lib->getID(), lib->getDocumentURI()->getURI());
	if (light)	// light is found
		return light;

	//PrintInfo( "Adding new light ' " );  
	//PrintInfo( lib->getId(), COLOR_RED_BLUE );
	//PrintInfo( " '\n" );


	domLight* LightElement = (domLight*)(domLight*)lib;

	if ( LightElement )
	{
		// Create the CLight
		CLight * newLight = CNew(CLight);
		//CAssert("No memory\n", newLight != NULL);
		// Set its name to the light's id
		newLight->SetName( LightElement->getId() ); 
		newLight->SetDocURI( LightElement->getDocumentURI()->getURI() ); 
		// Get the common technique for this light
		domLight::domTechnique_common * commonTechnique	= LightElement->getTechnique_common();
		// Only one of these light types can be present
		domLight::domTechnique_common::domAmbient *ambientElement = commonTechnique->getAmbient();
		domLight::domTechnique_common::domDirectional *directionalElement = commonTechnique->getDirectional();
		domLight::domTechnique_common::domPoint *pointElement = commonTechnique->getPoint();
		domLight::domTechnique_common::domSpot *spotElement = commonTechnique->getSpot();

		if(ambientElement)
		{
			newLight->SetType(eLIGHTTYPE_AMBIENT);
			domFloat3 &color = ambientElement->getColor()->getValue();
			newLight->SetColor( CColor4f((CFloat)(color[0]), (CFloat)(color[1]), (CFloat)(color[2]), 1.0f) );
		}
		else if(directionalElement)
		{
			newLight->SetType(eLIGHTTYPE_DIRECTIONAL);
			domFloat3 &color = directionalElement->getColor()->getValue();
			newLight->SetColor( CColor4f((CFloat)(color[0]), (CFloat)(color[1]), (CFloat)(color[2]), 1.0f) );
		}
		else if(pointElement)
		{
			newLight->SetType(eLIGHTTYPE_POINT);
			domFloat3 &color = pointElement->getColor()->getValue();
			newLight->SetColor( CColor4f((CFloat)(color[0]), (CFloat)(color[1]), (CFloat)(color[2]), 1.0f) );

			if ( pointElement->getConstant_attenuation()) 
				newLight->SetConstantAttenuation( (CFloat)(pointElement->getConstant_attenuation()->getValue()) );
			if ( pointElement->getLinear_attenuation()) 
				newLight->SetLinearAttenuation( (CFloat)(pointElement->getLinear_attenuation()->getValue()) );
			if ( pointElement->getQuadratic_attenuation()) 
				newLight->SetQuadraticAttenuation( (CFloat)(pointElement->getQuadratic_attenuation()->getValue()) );
		}
		else if(spotElement)
		{
			newLight->SetType(eLIGHTTYPE_SPOT);	
			domFloat3 &color = spotElement->getColor()->getValue();
			newLight->SetColor( CColor4f((CFloat)(color[0]), (CFloat)(color[1]), (CFloat)(color[2]), 1.0f) );
			if (spotElement->getConstant_attenuation())
				newLight->SetConstantAttenuation( (CFloat)(spotElement->getConstant_attenuation()->getValue()) );
			if (spotElement->getLinear_attenuation())
				newLight->SetLinearAttenuation( (CFloat)(spotElement->getLinear_attenuation()->getValue()) );
			if (spotElement->getQuadratic_attenuation())
				newLight->SetQuadraticAttenuation( (CFloat)(spotElement->getQuadratic_attenuation()->getValue()) );
			if (spotElement->getFalloff_angle())
				newLight->SetSpotCutoff( (CFloat)(spotElement->getFalloff_angle()->getValue()) );
			if (spotElement->getFalloff_exponent())
				newLight->SetSpotExponent( (CFloat)(spotElement->getFalloff_exponent()->getValue()) );
		}

		m_lights.push_back(newLight);
		return newLight; 	
	}
	return NULL; 	
}

CLight *CScene::GetLight( const CChar * name, const CChar * DocURI)
{
	if (name == NULL) return NULL;
	for(CUInt i=0; i<m_lights.size(); i++)
	{
		if ( ICmp(m_lights[i]->GetName(), name )  &&
			 ICmp(m_lights[i]->GetDocURI(), DocURI ) )
			return m_lights[i];
	}
	return NULL;
}


CInstanceCamera *CScene::ReadInstanceCamera( domInstance_cameraRef lib)
{
	xsAnyURI & urltype  = lib->getUrl();
	domElement * element = (domElement* ) urltype.getElement();
	if (element==NULL) // this instance light is not found skip to the next one
	{
		//CChar tempChar[ MAX_NAME_SIZE ];
		//sprintf("Can't find the camera ' %s '\n", urltype.getURI() );
		//PrintInfo( tempChar );
		return NULL;
	}

	CCamera * camera = ReadCamera((domCamera *) element);
	if (camera)
	{
		CInstanceCamera *instanceCamera = CNew(CInstanceCamera);
		//CAssert("No memory\n", instanceCamera!=NULL);
		instanceCamera->m_abstractCamera = camera;
		return instanceCamera;
	}
	return NULL;
}

CCamera *CScene::ReadCamera( domCameraRef lib )
{
	if (lib->getId()==NULL) return NULL;
	CCamera * camera = GetCamera(lib->getID(), lib->getDocumentURI()->getURI());
	if (camera)	// camera is found
		return camera;
	//PrintInfo( "Adding new camera ' " );  
	//PrintInfo( lib->getId(), COLOR_RED_BLUE );
	//PrintInfo( " '\n" );

	domCamera * CameraElement = (domCamera*)(domElement*)lib; 
	if ( CameraElement )
	{	
		// Make the camera
		CCamera * newCam = CNew( CCamera ); 
		//CAssert("No memory\n", newCam!=NULL);

		// Set its name to the id of the collada element
		CChar camName[MAX_NAME_SIZE];
		sprintf(camName, "%s%s%s", g_currentInstancePrefabName, "_", CameraElement->getId());
		newCam->SetName(camName);

		newCam->SetPureName(CameraElement->getId());

		newCam->SetDocURI(CameraElement->getDocumentURI()->getURI());
		
		// Get the optics
		domCamera::domOptics *cameraOptics = CameraElement->getOptics();
		
		// Get the optics common profile technique
		domCamera::domOptics::domTechnique_common *cameraCommonTechnique = cameraOptics->getTechnique_common();
		
		// Get the get the perspective and orthographic common profiles (if they exist)
		domCamera::domOptics::domTechnique_common::domPerspective *cameraPerspective = cameraCommonTechnique->getPerspective();
		domCamera::domOptics::domTechnique_common::domOrthographic *cameraOrthographic = cameraCommonTechnique->getOrthographic();
		
		// Setup camera parameters, note we have to check if a parameter is there before doing getValue
		// Parameters not in the COLLADA data will be left at the CCamera defaults
		if(cameraPerspective)
		{
			//PrintInfo( "Reading a perspective camera\n" );
			if(cameraPerspective->getXfov())
				newCam->SetXFov((CFloat)(cameraPerspective->getXfov()->getValue()));
			if(cameraPerspective->getYfov())
				newCam->SetYFov((CFloat)(cameraPerspective->getYfov()->getValue()));
			if(cameraPerspective->getAspect_ratio())
				newCam->SetAspect((CFloat)(cameraPerspective->getAspect_ratio()->getValue()));
			if(cameraPerspective->getZnear())
				newCam->SetZNear((CFloat)(cameraPerspective->getZnear()->getValue()));
			if(cameraPerspective->getZfar())
				newCam->SetZFar((CFloat)(cameraPerspective->getZfar()->getValue()));
			//force Znear to be >= 1.0 to avoid rendering problems
			if( newCam->GetZNear() < 1.0f)
				newCam->SetZNear(1.0f);
		}
		if(cameraOrthographic)
		{
			//PrintInfo( "Reading an orthographic camera\n" );

			// Setup orthographic camera
			if(cameraOrthographic->getXmag())
				newCam->SetXMag((CFloat)(cameraOrthographic->getXmag()->getValue()));
			if(cameraOrthographic->getYmag())
				newCam->SetYMag((CFloat)(cameraOrthographic->getYmag()->getValue()));
			if(cameraOrthographic->getAspect_ratio())
				newCam->SetAspect((CFloat)(cameraOrthographic->getAspect_ratio()->getValue()));
			if(cameraOrthographic->getZnear())
				newCam->SetZNear((CFloat)(cameraOrthographic->getZnear()->getValue()));
			if(cameraOrthographic->getZfar())
				newCam->SetZFar((CFloat)(cameraOrthographic->getZfar()->getValue()));
			// !!!GAC force Znear to be >= 1.0 to avoid rendering problems
			if( newCam->GetZNear() < 1.0f)
				newCam->SetZNear(1.0f);
		}
		m_cameras.push_back(newCam);
		return newCam; 	
	}
	return NULL;
};

CCamera *CScene::GetCamera( const CChar * name, const CChar * DocURI)
{
	if (name == NULL) return NULL;
	for(CUInt i=0; i<m_cameras.size(); i++)
	{
		if ( ICmp(m_cameras[i]->GetName(), name )  &&
			 ICmp(m_cameras[i]->GetDocURI(), DocURI ) )
			return m_cameras[i];
	}
	return NULL;
}

CInstanceController *CScene::ReadInstanceController( domInstance_controllerRef lib)
{
	xsAnyURI & urltype  = lib->getUrl();
	domElement * element = urltype.getElement();
	domController * controller = (domController *) element;
	CController * ctrl = ReadController(controller);
	if (ctrl==NULL)		// controller not found
		return NULL;

	CInstanceController *newiController = CNew(CInstanceController);
	//CAssert("No memory\n", newiController!=NULL);
	newiController->m_abstractController = ctrl;
	newiController->m_instanceGeometry->m_abstractGeometry = ctrl->m_geometry;
	newiController->m_instanceGeometry->m_nameIndex = g_nameIndex++;

	domBind_materialRef bind_material = lib->getBind_material();
	if(bind_material)
	{
		// Get the <technique_common>
		domBind_material::domTechnique_common *techniqueCommon = bind_material->getTechnique_common();
		if(techniqueCommon)
		{
			// Get the <instance_material>s
			domInstance_material_Array &instance_material_array = techniqueCommon->getInstance_material_array();
			for(CUInt j = 0; j < instance_material_array.getCount(); j++)
			{
				CInstanceMaterial * newiMaterial = ReadInstanceMaterial(instance_material_array[j]);
				newiController->m_materialInstances.push_back(newiMaterial);
			}
		}
	}

	return newiController;
}

CController	*CScene::ReadController( domControllerRef lib )
{
	if (lib->getId()==NULL) return NULL;
	//PrintInfo( "Adding new controller ' " );PrintInfo( lib->getId(), COLOR_RED_BLUE );PrintInfo( " '\n" );

	domSkin *skinElement	= lib->getSkin();
	if (skinElement==NULL) // no skin in this controller DO LATER, we will support non-skin controller later
		return NULL;

	// Make a CController to hold this info
	CController *newController = CNew( CController );
	//CAssert("No memory\n", newController!=NULL);
	// Get the <skin> from the <controller> (there can be only one)
	domElement* element = skinElement->getSource().getElement(); 

	// Get the targetid from the <skin> and set it in newController
	char *targetID = (char *)skinElement->getSource().getID(); 
	newController->SetTargetId( targetID ); 
	newController->SetName( lib->getId() ); 
	newController->SetDocURI( lib->getDocumentURI()->getURI() ); 

	if (skinElement->getBind_shape_matrix())
	{
		for (CUInt m=0; m<16; m++)
		{
			newController->m_bindShapeMats[m] = (CFloat)skinElement->getBind_shape_matrix()->getValue()[m];
		}
	}
	// Find the <joints> and <vertex_weights> elements inside <skin>
	domSkin::domJoints *jointsElement = skinElement->getJoints();
	domSkin::domVertex_weights *vertexWeightsElement = skinElement->getVertex_weights();

	// we are not using the accessors in the sources, but we really should.
	// Find the inputs we want from <joints>
	char *jointNamesID = NULL;
	domSource *jointNamesSource = NULL;
	char *invBindMatsID = NULL;
	domSource *invBindMatsSource = NULL;

	// Scan the <joint> looking for specific <input> semantics and remember where they are
	for(CUInt input = 0; input < jointsElement->getInput_array().getCount(); input++)
	{
		if(ICmp(jointsElement->getInput_array()[input]->getSemantic(),"JOINT"))
		{
			// Found the JOint input semantic
			jointNamesID = (char *)jointsElement->getInput_array()[input]->getSource().getID();
			jointNamesSource = (domSource *)((daeElement *)jointsElement->getInput_array()[input]->getSource().getElement());
		}
		else if(ICmp(jointsElement->getInput_array()[input]->getSemantic(),"INV_BIND_MATRIX"))
		{
			// Found the INV_BIND_MATRIX semantic
			invBindMatsID = (char *)jointsElement->getInput_array()[input]->getSource().getID();
			invBindMatsSource = (domSource *)((daeElement *)jointsElement->getInput_array()[input]->getSource().getElement());
		}
	}

	// Find the inputs we want from <vertex_weights>
	char *weightsID = NULL;
	domSource *weightsSource = NULL;

	// Scan the <vertex_weights> looking for specific <input> semantics and remember them
	for(CUInt input = 0; input < vertexWeightsElement->getInput_array().getCount(); input++)
	{
		if(ICmp(vertexWeightsElement->getInput_array()[input]->getSemantic(),"WEIGHT"))
		{
			// Found the WEIGHT semantic
			weightsID = (char *)vertexWeightsElement->getInput_array()[input]->getSource().getID();
			weightsSource = (domSource *)((daeElement *)vertexWeightsElement->getInput_array()[input]->getSource().getElement());
		}
	}

	// Allocate space for the joint names and copy them

	CJoint *jointNames = 0;
	CUInt jointCount=0;
	// TODO: remove after SIGGRAPH demo //hack to avoid a broken maya export, it should be getName_array instead of getIDREF_array
	if (jointNamesSource->getName_array())
	{
		jointCount = (CUInt) jointNamesSource->getName_array()->getCount();
		jointNames = CNewData(CJoint, jointCount);
		//CAssert("No memory\n", jointNames!=NULL);
		for (CUInt n = 0; n< jointCount; n++)
		{
			Cpy( jointNames[n].m_name, jointNamesSource->getName_array()->getValue()[n] );
		}
		newController->m_jointsType = CJoint::CJointsType_ID;
	}
	else if (jointNamesSource->getIDREF_array())
	{
		jointCount = (CUInt) jointNamesSource->getIDREF_array()->getCount();
		jointNames = CNewData(CJoint, jointCount);
		//CAssert("No memory\n", jointNames!=NULL);
		for (CUInt n = 0; n< jointCount; n++)
		{
			Cpy( jointNames[n].m_name, jointNamesSource->getIDREF_array()->getValue()[n].getID() );
		}
		newController->m_jointsType = CJoint::CJointsType_SID;;
	} 
	else
	{
		//PrintInfo( "CScene::ReadController: Critical document problem, Coudn't find the compatible array type for the joints.", COLOR_RED );
		//CAssert("Should never assert here\n", false);
	}

	// Allocate space for the inverse bind matrices and copy them
	CUInt 	invBindMatsCount = (CUInt) invBindMatsSource->getFloat_array()->getCount();
	CMatrix	*inverseBindMats = CNewData( CMatrix, invBindMatsCount/16 );
	//CAssert("No memory\n", inverseBindMats!=NULL);

	CFloat *iBMfloat = (CFloat *)inverseBindMats; 
    for (CUInt m = 0; m < invBindMatsCount; m++)
	{
		iBMfloat[m] = (CFloat)invBindMatsSource->getFloat_array()->getValue()[m];
	}

	// Invert all of the matrices 
	for (CUInt m = 0; m < invBindMatsCount/16; m++)
	{
		CMatrixTranspose(inverseBindMats[m],inverseBindMats[m]); 
	}

	// Allocate space for the joint weights
	CUInt vertexWeightsCount = (CUInt) vertexWeightsElement->getCount(); 
	CSkinWeight	*weights = CNewData( CSkinWeight, vertexWeightsCount );
	//CAssert("No memory\n", weights!=NULL);

	// <vcount> tells how many bones are associated with each vertex, this indicates how many
	// pairs of joint/weight indices to process out of the <v> array for this vertex.
	// get pointers to the vcount and v arrays

	domSkin::domVertex_weights::domVcount *vcountElement = vertexWeightsElement->getVcount();
	domSkin::domVertex_weights::domV *vElement = vertexWeightsElement->getV();

	CUInt vPos = 0;

	// For each vertex in <vcount>
	for(CUInt vertex = 0; vertex < vertexWeightsCount; vertex++)
	{
		// Find number of bones (joints/weights) this vertex influences and allocate space to store them
		CUInt numInfluences	= (CUInt) vcountElement->getValue()[vertex];
		weights[vertex].m_numWeights = numInfluences;
		weights[vertex].m_weights = CNewData( CFloat, numInfluences );
		//CAssert("No memory\n", weights[vertex].Weights!=NULL);
		weights[vertex].m_joints = CNewData( CUInt, numInfluences ); 
		//CAssert("No memory\n", weights[vertex].Joints!=NULL);
		// For each bone, copy in the joint number and the actual CFloat value in the weights (indexed by the 
		// second value in the <v> array
		for(CUInt inf = 0; inf < numInfluences; inf++)
		{
			weights[vertex].m_joints[inf] = (CUInt) vElement->getValue()[vPos++];
			weights[vertex].m_weights[inf] = (CFloat)weightsSource->getFloat_array()->getValue()[(size_t)(vElement->getValue()[vPos++])];
		}
		weights[vertex].SortWeights(); 
	}

	// Copy the finished data into our newController

	// set the JointNames 
	newController->m_joints = jointNames; 
	newController->m_jointCount	= jointCount; 
	
	// set the InverseBindMats
	newController->AddIBindMats( inverseBindMats, invBindMatsCount/16 );
	newController->m_iBindMatCount = invBindMatsCount/16; 
	
	// set the Weight
	newController->m_weights = weights;
	newController->m_weightCount = vertexWeightsCount;

	// set the geometry
	CGeometry * geometry = ReadGeometry((domGeometry *) element, newController );
	if (geometry==NULL)	{		// target skin is not found
		CDelete(newController);
		return NULL;
	}

	newController->m_geometry = geometry;
	//PrintInfo( "Geometry added successfully\n", COLOR_WHITE );
	m_controllers.push_back(newController);
	return newController;
}

CVoid CScene::CalculateTangentArray(CGeometry* geometry)
{
	if( geometry->m_tangents || !geometry->m_texCoords[0])
		return;
	geometry->m_bNormals = CNewData( CVec3f, geometry->m_vertexcountmax );
	geometry->m_tangents = CNewData( CVec3f, geometry->m_vertexcountmax );

	CVec3f* tangentTemp = CNewData( CVec3f, geometry->m_vertexcountmax );

	for (CUInt i = 0; i < geometry->m_groups.size(); i++ )
	{
		CPolyGroup* triangle =  geometry->m_groups[i];
		for (CUInt a = 0; a < triangle->m_count; a++)
		{
		    CUInt i1 = triangle->m_indexes[a*3];
		    CUInt i2 = triangle->m_indexes[1+ a*3];
		    CUInt i3 = triangle->m_indexes[2+ a*3];
        
			const CVec3f v1 = geometry->m_points[i1];
		    const CVec3f v2 = geometry->m_points[i2];
		    const CVec3f v3 = geometry->m_points[i3];
        
			const CVec2f w1 = geometry->m_texCoords[0][i1];
			const CVec2f w2 = geometry->m_texCoords[0][i2];
		    const CVec2f w3 = geometry->m_texCoords[0][i3];
        
			float x1 = v2.x - v1.x;
			float x2 = v3.x - v1.x;
			float y1 = v2.y - v1.y;
			float y2 = v3.y - v1.y;
			float z1 = v2.z - v1.z;
			float z2 = v3.z - v1.z;
        
			float s1 = w2.x - w1.x;
			float s2 = w3.x - w1.x;
			float t1 = w2.y - w1.y;
			float t2 = w3.y - w1.y;
        
			float r = 1.0F / (s1 * t2 - s2 * t1);
			CVec3f sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
					(t2 * z1 - t1 * z2) * r);

		    tangentTemp[i1] += sdir;
		    tangentTemp[i2] += sdir;
			tangentTemp[i3] += sdir;
		}
	}
    
	for (CUInt a = 0; a < geometry->m_vertexcount; a++)
    {
		const CVec3f& n = geometry->m_normals[a];
        const CVec3f& t = tangentTemp[a];
		CVec3f dotProduct;
        geometry->m_tangents[a] = (t - n * dotProduct.DotProduct(&n, &t)).Normalize();
		CVec3f crossProduct;
		geometry->m_bNormals[a] = crossProduct.CrossProduct( &n, &geometry->m_tangents[a] );
    }
	CDeleteData(tangentTemp);
}

CVoid CScene::DeindexMesh( CUInt initialVertexCount, CUInt totalVertexCount, CGeometry* geometry, CPolyGroup* triangles )
{
	//deindex. Remove unnecessary data for PhysX meshes
	CTriangles* physx_triangles = CNew( CTriangles );
	physx_triangles->m_indexes = CNewData(CUInt, triangles->m_count * 3);
	physx_triangles->m_count = triangles->m_count;
	geometry->m_physx_triangles.push_back( physx_triangles );
	for( CUInt i = 0; i < triangles->m_count * 3; i++ )
		physx_triangles->m_indexes[i] = triangles->m_indexes[i];

	//CVec3f *temp_normals = CNewData( CVec3f, geometry->m_vertexcount);
	//CVec2f *temp_texCoords[MAX_TEX_COORDS];

	//for( CInt j = 0; j < MAX_TEX_COORDS; j++ )
	//{
	//	if( geometry->m_texCoords[j])
	//		temp_texCoords[j] = CNewData( CVec2f, geometry->m_vertexcount);
	//	else
	//		temp_texCoords[j] = NULL;
	//}

	for( CUInt ivertex=initialVertexCount; ivertex< totalVertexCount; ivertex++ )
	{
		CBool foundTarget=CFalse;
		CBool skip = CFalse;
		for( CUInt jvertex=initialVertexCount; jvertex< totalVertexCount; jvertex++ )
		{
			if( ivertex != jvertex )
			{
				if( geometry->m_points[ivertex] == geometry->m_points[jvertex] )
				{
					if( ivertex < jvertex )
					{
						if( !foundTarget )
						{
							CUInt index = 0;
							for( CUInt i = 0 ; i < geometry->m_physx_points.size(); i++ )
							{
								if( *(geometry->m_physx_points[i]) == geometry->m_points[ivertex] )
								{
									index = i;
									break;
								}
								index++;
							}

							physx_triangles->m_indexes[ivertex - initialVertexCount] = index;
							if( index == geometry->m_physx_points.size() )
							{
								CVec3f* temp_vertex = CNew(CVec3f);
								temp_vertex->x = geometry->m_points[ivertex].x;
								temp_vertex->y = geometry->m_points[ivertex].y;
								temp_vertex->z = geometry->m_points[ivertex].z;

								geometry->m_physx_points.push_back( temp_vertex);
							}
							//temp_normals[index] = geometry->m_normals[ivertex];
							//for( CInt j = 0; j < MAX_TEX_COORDS; j++ )
							//{
							//	if(  geometry->m_texCoords[j] )
							//		temp_texCoords[j][index] = geometry->m_texCoords[j][ivertex];
							//}

							foundTarget = CTrue;
						}

						physx_triangles->m_indexes[jvertex-initialVertexCount] = physx_triangles->m_indexes[ivertex-initialVertexCount];
					}
					else
					{
						//we have already found this element
						skip = CTrue;
						break;
					}
				}
			}
		}
		if( !foundTarget && !skip)
		{
			CUInt index = 0;
			for( CUInt i = 0 ; i < geometry->m_physx_points.size(); i++ )
			{
				if( *(geometry->m_physx_points[i]) == geometry->m_points[ivertex] )
				{
					index = i;
					break;
				}
				index++;
			}

			physx_triangles->m_indexes[ivertex-initialVertexCount] = index;
			if( index == geometry->m_physx_points.size() )
			{
				CVec3f* temp_vertex = CNew(CVec3f);
				temp_vertex->x = geometry->m_points[ivertex].x;
				temp_vertex->y = geometry->m_points[ivertex].y;
				temp_vertex->z = geometry->m_points[ivertex].z;

				geometry->m_physx_points.push_back( temp_vertex);
			}
		}

	}
}
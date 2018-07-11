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
#pragma once 

#include "base.h"
#include "image.h"
#include "..\common\utility.h"
#include <vector>

class CImage;

class CEffect : public CBase 
{
	CInt32	m_type;
	
public:
	CColor4f m_emission;
	CColor4f m_ambient;
	CColor4f m_diffuse;
	CColor4f m_specular;
	CFloat m_shininess;
	CFloat m_transparency;
	CColor4f m_reflective;
	CColor4f m_transparent;
	CColor4f m_absorption;
	CFloat m_reflectivity;
	CFloat m_refractiveIndex;
	
	std::vector<CImage*> m_textures;
	CUInt m_idx; 

public:
	CEffect();
	~CEffect();
protected:
	friend class CScene; 

public:
	inline CColor4f	GetEmission(){ return m_emission; }
	inline CColor4f	GetAmbient(){ return m_ambient; }
	inline CColor4f	GetDiffuse(){ return m_diffuse; }
	inline CColor4f	GetSpecular(){ return m_specular; }
	inline CFloat GetShininess(){ if(m_shininess>0) return m_shininess; else return  0.1f; }
	inline CFloat GetTransparency(){ return m_transparency; }
	inline CInt	GetIdx(){ return m_idx; } 

	inline CColor4f	GetReflective() { return m_reflective; }
	inline CColor4f	GetTransparent() { return m_transparent; }
	inline CColor4f	GetAbsorption() { return m_absorption; }
	inline CVoid SetIdx( CInt i) { m_idx = i; }
	
};

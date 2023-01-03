//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

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

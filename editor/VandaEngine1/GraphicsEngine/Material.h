//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#pragma once

#include "base.h"
#include "..\common\utility.h"

class CEffect;

class CMaterial : public CBase 
{
	CInt32 m_type;
	
public:
	CInt m_passCount; 	
	CColor3f m_emission;
	CColor3f m_ambient;
	CColor3f m_diffuse;
	CColor3f m_specular;
	CFloat m_shininess;
	CFloat m_transparency;
	CColor3f m_reflective;
	CColor3f m_transparent;
	CColor3f m_absorption;
	CFloat m_reflectivity;
	CFloat m_refractiveIndex;
	CEffect* m_effect; 
	CInt m_idx; 
public:
	CMaterial();
	~CMaterial();

protected:
friend class CScene; 
	inline CVoid	SetEffect( CEffect * effect) { m_effect = effect; }; 
public:
	inline CColor3f	GetEmission(){ return m_emission; }
	inline CColor3f	GetAmbient(){ return m_ambient; }
	inline CColor3f	GetDiffuse(){ return m_diffuse; }
	inline CColor3f	GetSpecular(){ return m_specular; }
	inline CFloat GetShininess(){ return m_shininess; }
	inline CFloat GetTransparency(){ return m_transparency; }
	inline CInt GetIdx(){ return m_idx; } 
	inline CColor3f	GetReflective(){ return m_reflective; }
	inline CColor3f	GetTransparent(){ return m_transparent; }
	inline CColor3f	GetAbsorption(){ return m_absorption; }
	inline CEffect *GetEffect(){ return m_effect; }
	inline CVoid SetIdx( CInt i) { m_idx = i; }
};




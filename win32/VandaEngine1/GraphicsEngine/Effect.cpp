//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
{
	m_shininess = 0;
	m_reflectivity = 0; 
	m_transparency = 0;
	m_refractiveIndex = 0; 
	m_idx = 0; 

	m_type = 0; 

	m_emission = CColor3f(0.0f, 0.0f, 0.0f ); 
	m_ambient = CColor3f(0.0f, 0.0f, 0.0f ); 
	m_diffuse = CColor3f(0.0f, 0.0f, 0.0f );
	m_specular = CColor3f(0.0f, 0.0f, 0.0f );
	m_shininess = 40.0f;
	m_transparency = 1.0f;
}

CEffect::~CEffect()
{
	//I assume that all the images have are erased in CImage destructor
	m_textures.clear();

    Destroy(); 
}

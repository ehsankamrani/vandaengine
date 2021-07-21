//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "material.h"

CMaterial::CMaterial()
{
	m_shininess = 0;
	m_reflectivity = 0; 
	m_transparency = 0;
	m_refractiveIndex = 0; 
	m_idx = 0; 
	m_effect = NULL; 
	m_type = 0; 
	m_emission = CColor3f(.0f, .0f, .0f ); 
	m_ambient = CColor3f(.25f, .25f, .25f ); 
	m_diffuse = CColor3f(1.0f, 1.0f, 1.0f );
	m_specular = CColor3f(.95f, .95f, .95f );
	m_shininess = 40.0f;
	m_transparency = 1.0f;
}

CMaterial::~CMaterial()
{
    Destroy(); 
}
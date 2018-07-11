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

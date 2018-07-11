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
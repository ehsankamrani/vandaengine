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
#include "orient.h"

COrient::COrient()
{
	m_updateLocalMatrix = CTrue;
	m_updateLocalToWorldMatrix = CTrue;

	CMatrixLoadIdentity(m_localMatrix);
	CMatrixLoadIdentity(m_localToWorldMatrix);
	CMatrixLoadIdentity(m_inverseLocalToWorldMatrix);
	CMatrixLoadIdentity(m_inverseTransposeLocalToWorldMatrix);
	CMatrixLoadIdentity(m_inverseBindMatrix);
	CMatrixLoadIdentity(m_combinedSkinMatrix);
}

COrient::~COrient()
{
	for (size_t i=0; i<m_transforms[0].size(); i++)
	{
		CDelete(m_sumTransforms[i]);
	}
	m_sumTransforms.clear();
	m_sumWeights.clear();

	for( size_t index = 0; index < MAX_ANIMATION_CLIPS; index ++ )
	{
		for (size_t i=0; i<m_transforms[index].size(); i++)
		{
			CDelete(m_transforms[index][i]);
		}
		m_transforms[index].clear();
	}
}

//Copyright (C) 2020 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

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
	for (size_t i = 0; i<m_sumTransforms.size(); i++)
	{
		CDelete(m_sumTransforms[i]);
	}
	m_sumTransforms.clear();
	m_sumWeights.clear();

	for (size_t index = 0; index < m_transforms.size(); index++)
	{
		for (size_t i = 0; i<m_transforms[index].size(); i++)
		{
			CDelete(m_transforms[index][i]);
		}
		m_transforms[index].clear();
	}
	m_transforms.clear();
}
